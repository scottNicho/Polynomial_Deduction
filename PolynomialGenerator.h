#pragma once
#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>
#include<cmath>
#include"FileScholar.h"

template<typename T>
class PolynomialGenerator {
public:
    PolynomialGenerator() : orderFourCoefficient(0), orderThreeCoefficient(0), orderTwoCoefficient(0), orderOneCoefficient(0), constant(0), startValue(0), endValue(0) {}

    void updateOutputSet() {
        outputSet.clear();
        for (int xi = startValue; xi < endValue + 1; xi++) {
            outputSet.push_back(generatePolynomialNumber(xi));
        }
    }

    std::vector<T> generateOutputSet(const std::vector<T> &inputVector) {
        std::vector<T> returnVector{};
        for (auto xi : inputVector) {
            returnVector.push_back(generatePolynomialNumber(xi));
        }
        return returnVector;
    }

    void getUsersPolynomial() {
        polyFile.setOrderfourPolynomial();
         std::vector<int> tempVector = polyFile.getUsersPolynomialCoefficients();
         orderFourCoefficient = tempVector[0];
         orderThreeCoefficient = tempVector[1];
         orderTwoCoefficient = tempVector[2];
         orderOneCoefficient = tempVector[3];
         constant = tempVector[4];
        //coef intialisation function goes here
        setStringPolynomial();
    }

    // Getters and Setters

    void setStringPolynomial() {
        std::stringstream strPolynomial;
        strPolynomial << "(" << orderFourCoefficient << ")X^4";
        strPolynomial << "+(" << orderThreeCoefficient << ")X^3";
        strPolynomial << "+(" << orderTwoCoefficient << ")X^2";
        strPolynomial << "+(" << orderOneCoefficient << ")X";
        strPolynomial << "+" << constant;
        StringPolynomial = strPolynomial.str();
        removeZeroTermsString();
    }

    void savePolynomialToFile() {
        std::string inputString = StringPolynomial + "  for range[" + std::to_string(startValue) + " - "
        +std::to_string(endValue) + "]\n";
        if (!outputSet.empty()) { inputString.append(std::to_string(outputSet[0])); }
        for (int i = 1; i < outputSet.size(); i++) {
            inputString.append(",");
            inputString.append(std::to_string(outputSet[i]));
        }
        polyFile.saveOutputToFile(inputString);
    }
    
    
    void setCoefficientsRange(int c4,int c3,int c2, int c1,int c, int start,int end) {
        orderFourCoefficient = c4; orderThreeCoefficient = c3;
        orderTwoCoefficient = c2; orderOneCoefficient = c1;
        constant = c; startValue = start; endValue = end;
    }
    

    int getStartValue() const { return startValue; }
    int getEndValue() const { return endValue; }
    void setOutputSet(const std::vector<T>& newOutputSet) { outputSet = newOutputSet; }
    const std::vector<T>& getOutputSet() const { return outputSet; }
    const std::string& getStringPolynomial() { return StringPolynomial; }

protected:
    
    void removeZeroTermsString() {
        size_t pos = 0;
        while ((pos = StringPolynomial.find("(0)X^4", pos)) != std::string::npos) {
            StringPolynomial.erase(pos, 6);
        }
        pos = 0;
        while ((pos = StringPolynomial.find("(0)X^3", pos)) != std::string::npos) {
            StringPolynomial.erase(pos - 1, 7);
        }
        pos = 0;
        while ((pos = StringPolynomial.find("(0)X^2", pos)) != std::string::npos) {
            StringPolynomial.erase(pos - 1, 7);
        }
        pos = 0;
        while ((pos = StringPolynomial.find("(0)X", pos)) != std::string::npos) {
            StringPolynomial.erase(pos - 1, 5);
        }
        pos = 0;
        while ((pos = StringPolynomial.find("0", pos)) != std::string::npos) {
            StringPolynomial.erase(pos - 1, 2);
        }
    }

    T generatePolynomialNumber(T num) {
        T coefficientPowerFour = orderFourCoefficient * pow(num, 4);
        T coefficientPowerThree = orderThreeCoefficient * pow(num, 3);
        T coefficientPowerTwo = orderTwoCoefficient * pow(num, 2);
        T coefficientPowerOne = orderOneCoefficient * num;
        return coefficientPowerFour + coefficientPowerThree + coefficientPowerTwo + coefficientPowerOne + constant;
    }

    void setStartEndValues(int newStart, int newEnd) {
        startValue = newStart;
        endValue = newEnd;
    }

    T orderFourCoefficient;
    T orderThreeCoefficient;
    T orderTwoCoefficient;
    T orderOneCoefficient;
    T constant;
    std::string StringPolynomial = "";
    int startValue;
    int endValue;
    std::vector<T> outputSet;
    FileScholar polyFile;
};
