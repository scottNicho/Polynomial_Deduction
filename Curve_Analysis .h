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

	void curveDeduction();

	void curveDeducerNoUserInput();

	void curveAnalyser();

	

	void DeducePolynomial();

	void readAndSaveBatch();

	//Curve no start point
	

	//Curve no start point
	
	//test function
	void printCurveCoefficients();

	//test function 
	
//setters and getters 

	std::vector<int> getStartingSet() { return startingSet; }

	void setMostRecentCoefficient(int newCoefficient) { mostRecentCoefficient = newCoefficient; };

protected:

	bool checkExpressionConditions();

	void updateUserInputVec();

	void updateCurveCoefficient();

	void findSetConstant();

	void updateAdjustedCurve();

	std::vector<int> differenceBetweenTerms(const std::vector<int>& inputVector);

	bool uniformVectorCheck(std::vector<int> inputVector);

	bool startKnown = false;
	bool endOfDifferentiation = false;
	int rangeStartpoint, rangeEndPoint;
	int coefficientSign;
	int mostRecentCoefficient = _MAX_INT_DIG;
	int turningPointIndex;
	unsigned int CurveOrder = 0;
	std::vector<int> startingSet{};
	std::vector<int> adjustedVector;
	std::vector<char> userInputVec{};
	//double curveCoefficients[5]{ 0 };
	std::vector<double> curveCoefficients{0.0,0.0,0.0,0.0,0.0};
	PolynomialGenerator <double> curveGenerator;
	FileScholar curveReader;
};

