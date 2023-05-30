#include "PolynomialGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

template<typename T>
void PolynomialGenerator<T>::getUsersPolynomial() {
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

template<typename T>
std::vector<double> PolynomialGenerator<T>::generateOutputSet() {
    std::vector<double> returnVector{};
    for (int i = startValue; i <= endValue; i++) {
        returnVector.push_back(generatePolynomialNumber(i));
    }
    return returnVector;
}

template<typename T>
void PolynomialGenerator<T>::AskRunUsersPolynomial() {
    char save;
    char YesOrNo;
    char happyNot;
    while (true) {
        std::cout << "would you like to enter a polynomial? \n please press y/Y for yes or n/N for no" << std::endl;
        std::cin >> YesOrNo;
        if (YesOrNo == 'y' || YesOrNo == 'Y') { break; }
        else if (YesOrNo == 'n' || YesOrNo == 'N') { return; }
        std::cout << " sorry I didn't get that" << std::endl;
    }
    while (true) {
        getUsersPolynomial();
        setStartEndValues();
        updateOutputSet();
        std::cout << "this is the output from your polynomial and range " << std::endl;
        printOutoutSet();
        std::cout << "Are you happy with this polynomial and range? please press y/Y for yes or n/N if you wish to enter a new ploynomial" << std::endl;
        std::cin >> happyNot;
        if (happyNot == 'y' || happyNot == 'Y') { break; }
    }

    std::cout << "Would you like to save this polynomial? Please press y/Y for yes or n/N for no" << std::endl;
    std::cin >> save;
    if (save == 'y' || save == 'Y') {
        savePolynomialToFile();
    }

}

template<typename T>
void PolynomialGenerator<T>::showUserSavedPolynomial() {
    std::cout << "Hi would you like to load and see a saved polinomial? \n please press y/Y for yes" << std::endl;
    char userInput;
    std::cin >> userInput;
    if (userInput == 'y' || userInput == 'Y') {
        while (true) {
            char userLetter;
            std::cout << "please input the letter of the polynomial you would like to see" << std::endl;
            std::cin >> userLetter;
            //code to find letter and display line to user
            std::cout << "Sorry I couldn't find a polynomial with that letter please try again" << std::endl;
        }
    }

}

template<typename T>
void PolynomialGenerator<T>::setStringPolynomial() {
    std::stringstream strPolynomial;
    strPolynomial << "(" << orderFourCoefficient << ")X^4";
    strPolynomial << "+(" << orderThreeCoefficient << ")X^3";
    strPolynomial << "+(" << orderTwoCoefficient << ")X^2";
    strPolynomial << "+(" << orderOneCoefficient << ")X";
    strPolynomial << "+" << "(" << constant << ")";
    StringPolynomial = strPolynomial.str();
    removeZeroTermsString();
}

template<typename T>
void PolynomialGenerator<T>::setCoefficientsRange(std::vector<T> newcoefficients, int start, int end) {
    orderFourCoefficient = newcoefficients[0]; orderThreeCoefficient = newcoefficients[1];
    orderTwoCoefficient = newcoefficients[2]; orderOneCoefficient = newcoefficients[3];
    constant = newcoefficients[4]; startValue = start; endValue = end;
}

//protected

template<typename T>
void PolynomialGenerator<T>::savePolynomialToFile() {
    std::string inputString = StringPolynomial + "  for range[" + std::to_string(startValue) + " - "
        + std::to_string(endValue) + "]\n";
    if (!outputSet.empty()) { inputString.append(std::to_string(outputSet[0])); }
    for (int i = 1; i < outputSet.size(); i++) {
        inputString.append(",");
        inputString.append(std::to_string(outputSet[i]));
    }
    polyFile.saveOutputToFile(inputString);
}

template<typename T>
void PolynomialGenerator<T>::updateOutputSet() {
    outputSet.clear();
    for (int xi = startValue; xi < endValue + 1; xi++) {
        outputSet.push_back(generatePolynomialNumber(xi));
    }
}

template<typename T>
void PolynomialGenerator<T>::printOutoutSet() {
    for (auto ht : outputSet) {
        std::cout << std::to_string(ht) + " ";
    }
    std::cout << "\n";
}

template<typename T>
void PolynomialGenerator<T>::removeZeroTermsString() {
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
    while ((pos = StringPolynomial.find("(0)", pos)) != std::string::npos) {
        StringPolynomial.erase(pos - 1, 4);
    }
}

template<typename T>
T PolynomialGenerator<T>::generatePolynomialNumber(T num) {
    T coefficientPowerFour = orderFourCoefficient * pow(num, 4);
    T coefficientPowerThree = orderThreeCoefficient * pow(num, 3);
    T coefficientPowerTwo = orderTwoCoefficient * pow(num, 2);
    T coefficientPowerOne = orderOneCoefficient * num;
    return coefficientPowerFour + coefficientPowerThree + coefficientPowerTwo + coefficientPowerOne + constant;
}

template<typename T>
void PolynomialGenerator<T>::setStartEndValues() {
    int newStart;
    int newEnd;
    std::cout << "what would you like the range to start from? " << std::endl;
    std::cin >> newStart;
    std::cout << "And what would you like the range to end at? " << std::endl;
    std::cin >> newEnd;
    startValue = newStart;
    endValue = newEnd;
}

template class PolynomialGenerator<double>;