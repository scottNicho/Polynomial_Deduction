#include "Curve_Analysis .h"


void CurveAnalysis::curveDeduction() {
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
	if (checkExpressionConditions()) {
		char userYN;
		std::string derivedPolyString = curveGenerator.getStringPolynomial();
		std::cout << "This is the polynomial that generated the chosen set" << std::endl;
		std::cout << derivedPolyString << std::endl;
		std::cout << "would you like to save this result? \n please press y/Y for yes" << std::endl;
		std::cin >> userYN;
		if (userYN == 'y' || userYN == 'Y') {
			curveReader.savePolynomialToFile(derivedPolyString);
		}
	}
}

void CurveAnalysis::curveDeducerNoUserInput() {
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
	if (checkExpressionConditions()) {
		curveReader.savePolynomialToFile(derivedPolyString);
	}
	startingSet.clear();
	adjustedVector.clear();
	startKnown = false;
	rangeStartpoint = 0;
	rangeEndPoint = 0;
}

void CurveAnalysis::curveAnalyser() {
	CurveOrder = 0;
	std::vector<int> runningVector = adjustedVector;
	coefficientSign = (adjustedVector[adjustedVector.size() - 1] >= adjustedVector[adjustedVector.size() - 2]) ? 1 : -1;
	while (!uniformVectorCheck(runningVector)) {
		runningVector = differenceBetweenTerms(runningVector);
		CurveOrder += 1;
	}
	if (CurveOrder > 4) { std::cout << "curve order too high probable input error"; }
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



void CurveAnalysis::DeducePolynomial() {
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
		if (curveReader.getStartEndRange().empty()) { 
			std::cout << "Cannot determin this curve without more information" << std::endl;
			startKnown = false; 
		}
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


void CurveAnalysis::readAndSaveBatch() {
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
		else
		{
			std::fstream polynomialBFile;
			polynomialBFile.open("Polynomial_expression.txt", std::ios::app);
			if (polynomialBFile.is_open()) {
				polynomialBFile << "Unknown";
				polynomialBFile.close();
			}
		}
		curveReader.clearStartEndRange();
	}
	
}

void CurveAnalysis::printCurveCoefficients() {
	for (int i = 0; i < 5; i++) {
		std::cout << curveCoefficients[i] << " ";
	}
	std::cout << std::endl;
}

//protected

bool CurveAnalysis::checkExpressionConditions() {
	if (curveCoefficients[4] > 1000 || curveCoefficients[4] < -1000) { return false; }
	for (int i = 0; i < 4; i++) {
		if (curveCoefficients[i] > 9 || curveCoefficients[i] < -9) { return false; }
	}
	return true;
}

void CurveAnalysis::updateUserInputVec() {
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

void CurveAnalysis::updateCurveCoefficient() {
	int count = 1;
	int index = 4 - CurveOrder;

	//mostRecentCoefficient *= (CurveOrder % 2 == 0) ? 1 : -1; // set to the correct sign
	if (coefficientSign < 0 && mostRecentCoefficient>0) { mostRecentCoefficient = -mostRecentCoefficient; }
	else if (coefficientSign > 0 && mostRecentCoefficient < 0) { mostRecentCoefficient = -mostRecentCoefficient; }

	double updateNum = static_cast<double>(mostRecentCoefficient);
	while (count <= CurveOrder) {
		updateNum = updateNum / count;
		count += 1;
	}
	if (curveCoefficients[index] != 0) { std::cout << "error index not 0!" << std::endl; }
	curveCoefficients[index] = updateNum;
}

void CurveAnalysis::findSetConstant() {
	std::vector<double> tempVec = curveGenerator.generateOutputSet();
	int constant = startingSet[0] - tempVec[0];
	curveCoefficients[4] = constant;
}

void CurveAnalysis::updateAdjustedCurve() {
	adjustedVector.clear();
	curveGenerator.setCoefficientsRange(curveCoefficients, 0, 10);
	curveGenerator.setStringPolynomial();
	std::vector<double> tempVec = curveGenerator.generateOutputSet();
	for (int xi = 0; xi < tempVec.size(); xi++) {
		adjustedVector.push_back(startingSet[xi] - tempVec[xi]);// adjust the curve for the known values
	}
	return;
}

std::vector<int> CurveAnalysis::differenceBetweenTerms(const std::vector<int>& inputVector) {
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

bool CurveAnalysis::uniformVectorCheck(std::vector<int> inputVector) {
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