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

    
    std::vector<double> generateOutputSet();

    void AskRunUsersPolynomial();

    void showUserSavedPolynomial();

    void getUsersPolynomial();

    // Getters and Setters

    void setStringPolynomial();


    void setCoefficientsRange(std::vector<T> newcoefficients, int start, int end);
    
    
    int getStartValue() const { return startValue; }
    int getEndValue() const { return endValue; }
    void setOutputSet(const std::vector<T>& newOutputSet) { outputSet = newOutputSet; }
    const std::vector<T>& getOutputSet() const { return outputSet; }
    const std::string& getStringPolynomial() { return StringPolynomial; }

protected:

    void savePolynomialToFile();

    void updateOutputSet();

    void printOutoutSet();
    
    void removeZeroTermsString();

    T generatePolynomialNumber(T num);

    void setStartEndValues();

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
