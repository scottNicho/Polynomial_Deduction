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
		while (!endOfDifferentiation) {
			curveAnalyser();
			updateAdjustedCurve();
		}
		findSetConstant();
		curveGenerator.generateOutputSet();
		printCurveCoefficients();
	}

	void curveAnalyser() {
		CurveOrder = 0;
		std::vector<int> runningVector = adjustedVector;
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

	void updateCurveCoefficient() {
		int count = 1;
	    int index = 4 - CurveOrder;
		mostRecentCoefficient *= (CurveOrder % 2 == 0) ? 1 : -1;; // set to the correct sign
		double updateNum = static_cast<double>(mostRecentCoefficient);
		while (count <= CurveOrder) {
			updateNum = updateNum / count;
			count += 1;
		}
		curveCoefficients[index] = updateNum;
	}

	

	//test function
	void printCurveCoefficients() {
		for (int i = 0; i < 5; i++) {
			std::cout << curveCoefficients[i] << " ";
		}
		std::cout << std::endl;
	}
	//test function 
	
//setters and getters 

	void setMostRecentCoefficient(int newCoefficient) { mostRecentCoefficient = newCoefficient; };

protected:

	void findSetConstant() {
		std::vector<double> tempVec = curveGenerator.generateOutputSet();
		int constant = startingSet[0] - tempVec[0];
		curveCoefficients[4] = constant;
	}

	void updateAdjustedCurve() {
		adjustedVector.clear();
		curveGenerator.setCoefficientsRange(curveCoefficients,0,10);
		std::vector<double> tempVec = curveGenerator.generateOutputSet();
		for (int xi = 0; xi < startingSet.size(); xi++) {
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
		if (firstElement != 0) {
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

	bool endOfDifferentiation = false;
	int mostRecentCoefficient = _MAX_INT_DIG;
	unsigned int CurveOrder = 0;
	std::vector<int> startingSet{ -3, 2,7,0,-31,-98,-213,-388,-635,-966,-1393};
	std::vector<int> adjustedVector;
	//double curveCoefficients[5]{ 0 };
	std::vector<double> curveCoefficients{0.0,0.0,0.0,0.0,0.0};
	PolynomialGenerator <double> curveGenerator;
	FileScholar curveReader;
};

