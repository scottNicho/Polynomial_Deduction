#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<cmath>
#include"FileScholar.h"
#include"PolynomialGenerator.h"

class CurveAnalysis {
public:
	CurveAnalysis() :adjustedVector{startingSet}{};

	void curveDeduction() {
		coefficientSign = (startingSet[startingSet.size() - 1] >= startingSet[startingSet.size() - 2]) ? 1 : -1;
		while (!endOfDifferentiation) {
			curveAnalyser();
			updateAdjustedCurve();
		}
		findSetConstant();
		//curveGenerator.generateOutputSet();
		printCurveCoefficients();
		curveGenerator.setCoefficientsRange(curveCoefficients, 0, 10);
		curveGenerator.setStringPolynomial();
		char userYN;
		std::string derivedPolyString = curveGenerator.getStringPolynomial();
		std::cout << "This is the polynomial that generated the chosen set" << std::endl;
		std::cout << derivedPolyString << std::endl;
		std::cout<< "would you like to save this result? \n please press y/Y for yes" << std::endl;
		std::cin >> userYN;
		if (userYN == 'y' || userYN == 'Y') {
				curveReader.savePolynomialToFile(derivedPolyString);
		}
	}

	void curveDeducerNoUserInput() {
		coefficientSign = (startingSet[startingSet.size() - 1] >= startingSet[startingSet.size() - 2]) ? 1 : -1;
		while (!endOfDifferentiation) {
			curveAnalyser();
			updateAdjustedCurve();
		}
		findSetConstant();
		//curveGenerator.generateOutputSet();
		printCurveCoefficients();
		curveGenerator.setCoefficientsRange(curveCoefficients, 0, 10);
		curveGenerator.setStringPolynomial();
		std::string derivedPolyString = curveGenerator.getStringPolynomial();
		curveReader.savePolynomialToFile(derivedPolyString);
		startingSet.clear();
		adjustedVector.clear();
		startKnown = false;
		rangeStartpoint = 0;
		rangeEndPoint = 0;
	}

	void curveAnalyser() {
		CurveOrder = 0;
		std::vector<int> runningVector = adjustedVector;
		coefficientSign = (adjustedVector[adjustedVector.size() - 1] >= adjustedVector[adjustedVector.size() - 2]) ? 1 : -1;
		while (!uniformVectorCheck(runningVector)) {
			runningVector = differenceBetweenTerms(runningVector);
			CurveOrder += 1;
		}
		if (CurveOrder > 4) { std::cout << "curve order too high probable input error";}
		for (auto xi : runningVector) {
			std::cout << xi << std::endl;
		}
		if (CurveOrder == 0) {
			endOfDifferentiation = true;
			return;
		}
		std::cout << CurveOrder << std::endl;

		updateCurveCoefficient();
		printCurveCoefficients();
	}

	

	void DeducePolynomial() {
		char userInput;
		while (true) {
			std::cout << "Hi please enter the letter of the output set you would like the polynomial for?" << std::endl;
			std::cin >> userInput;
			if (static_cast<int>(userInput) >= 65 && static_cast<int>(userInput) <= 70) {
				break;
			}
			if (static_cast<int>(userInput) >= 97 && static_cast<int>(userInput) <= 102) {
				userInput = userInput - 32;
				break;
			}
			std::cout << "Sorry Please enter a character form A - F" << std::endl;
		}
		std::fstream polynomialFile;
		polynomialFile.open("Polynomial_Outputs.txt", std::ios::in);
		if (polynomialFile.is_open()) {
			std::string line;
			std::string outputSet; 
			bool capture = false;
			int count = 0;
			while (std::getline(polynomialFile,line)) {
				if (capture) {
					if (count >= 2) { break; }
					if (count == 0) { 
						outputSet = line;
						count++;
						continue;
					}
					outputSet += line;
					count++;
				}
				if (curveReader.findLetter(line, userInput)) {
					curveReader.GetStartEnd(line);//gets the range
					capture = true;
					continue;
				}
			}
			startingSet = curveReader.extractOutputSet(outputSet);
			adjustedVector = startingSet;
			if (curveReader.getStartEndRange().empty()) { startKnown = false; }
			else
			{
				startKnown = true;
				rangeStartpoint = curveReader.getStartEndRange()[0];
				rangeEndPoint = curveReader.getStartEndRange()[1];
			}
		}
		polynomialFile.close();
		if (startKnown) {
			curveDeduction();
		}
	}

	void readAndSaveBatch() {
		updateUserInputVec();
		for (auto xi : userInputVec) {
			char userInput = xi;
			std::fstream polynomialFile;
			polynomialFile.open("Polynomial_Outputs.txt", std::ios::in);
			if (polynomialFile.is_open()) {
				std::string line;
				std::string outputSet;
				bool capture = false;
				int count = 0;
				while (std::getline(polynomialFile, line)) {
					if (capture) {
						if (count >= 2) { break; }
						if (count == 0) {
							outputSet = line;
							count++;
							continue;
						}
						outputSet += line;
						count++;
					}
					if (curveReader.findLetter(line, userInput)) {
						curveReader.GetStartEnd(line);//gets the range
						capture = true;
						continue;
					}
				}
				startingSet = curveReader.extractOutputSet(outputSet);
				adjustedVector = startingSet;
				if (curveReader.getStartEndRange().empty()) { startKnown = false; }
				else
				{
					startKnown = true;
					rangeStartpoint = curveReader.getStartEndRange()[0];
					rangeEndPoint = curveReader.getStartEndRange()[1];
				}
			}
			polynomialFile.close();
			if (startKnown) {
				endOfDifferentiation = false;
				curveCoefficients = { 0,0,0,0,0 };
				curveDeducerNoUserInput();
			}
		}
		
	}

	//test function
	void printCurveCoefficients() {
		for (int i = 0; i < 5; i++) {
			std::cout << curveCoefficients[i] << " ";
		}
		std::cout << std::endl;
	}

	std::vector<int> getStartingSet() { return startingSet; }
	//test function 
	
//setters and getters 

	void setMostRecentCoefficient(int newCoefficient) { mostRecentCoefficient = newCoefficient; };

protected:

	void updateUserInputVec() {
		std::fstream polynomialFile;
		userInputVec.clear();//refill full vector
		polynomialFile.open("Polynomial_Outputs.txt", std::ios::in);
		if (polynomialFile.is_open()) {
			std::string line;
			while (std::getline(polynomialFile, line)) {
				if (line[0] <= 'Z' && line[0] >= 'A') {
					userInputVec.push_back(line[0]);
				}
			}
			polynomialFile.close();
		}
	}

	void updateCurveCoefficient() {
		int count = 1;
		int index = 4 - CurveOrder;

		//mostRecentCoefficient *= (CurveOrder % 2 == 0) ? 1 : -1; // set to the correct sign
		if (coefficientSign < 0 && mostRecentCoefficient>0) { mostRecentCoefficient = -mostRecentCoefficient;}
		else if (coefficientSign > 0 && mostRecentCoefficient<0) { mostRecentCoefficient = -mostRecentCoefficient;}

		double updateNum = static_cast<double>(mostRecentCoefficient);
		while (count <= CurveOrder) {
			updateNum = updateNum / count;
			count += 1;
		}
		if (curveCoefficients[index] != 0) { std::cout << "error index not 0!" << std::endl; }
		curveCoefficients[index] = updateNum;
	}

	void findSetConstant() {
		std::vector<double> tempVec = curveGenerator.generateOutputSet();
		int constant = startingSet[0] - tempVec[0];
		curveCoefficients[4] = constant;
	}

	void updateAdjustedCurve() {
		adjustedVector.clear();
		curveGenerator.setCoefficientsRange(curveCoefficients,0,10);
		curveGenerator.setStringPolynomial();
		std::vector<double> tempVec = curveGenerator.generateOutputSet();
		for (int xi = 0; xi < tempVec.size(); xi++) {
			adjustedVector.push_back(startingSet[xi] - tempVec[xi]);// adjust the curve for the known values
		}
		return;
	}

	std::vector<int> differenceBetweenTerms(const std::vector<int>& inputVector) {
		std::vector<int> returnVector{};
		if (inputVector.empty()) { return returnVector; }
		else
		{
			for (int i = 0; i + 1 < inputVector.size(); i++) {
				returnVector.push_back(inputVector[i] - inputVector[i + 1]);
			}
		}
		return returnVector;
	}

	bool uniformVectorCheck(std::vector<int> inputVector) {
		int firstElement = inputVector[0];
		if (firstElement != 50) {
			for (auto xi : inputVector) {
				if (xi != firstElement) {
					return false;
				}
			}
			setMostRecentCoefficient(firstElement);
			return true;
		}
		return false;
	}

	bool startKnown = false;
	bool endOfDifferentiation = false;
	int rangeStartpoint, rangeEndPoint;
	int coefficientSign;
	int mostRecentCoefficient = _MAX_INT_DIG;
	unsigned int CurveOrder = 0;
	std::vector<int> startingSet{};
	std::vector<int> adjustedVector;
	std::vector<char> userInputVec{};
	//double curveCoefficients[5]{ 0 };
	std::vector<double> curveCoefficients{0.0,0.0,0.0,0.0,0.0};
	PolynomialGenerator <double> curveGenerator;
	FileScholar curveReader;
};

