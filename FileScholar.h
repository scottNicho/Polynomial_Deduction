#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<cmath>
#include <sstream>
#include<limits>

class FileScholar {
public:


    void setOrderfourPolynomial() {
        bool isHappy = false;
        bool conditionsSatisfied = false;
        int Orderfour, OrderThree, OrderTwo, OrderOne, constant;
        while (!isHappy || !conditionsSatisfied) {
            std::cout << "Enter the coefficients for the polynomial expression\n coefficients must be an integer from -9 to 9 \n the constant term must be an integer from -1000 to 1000: ";
            std::cout << "(A)x^4 + (B)x^3 + (C)x^2 + (D)x + (E)" << std::endl;

            
            auto validateInput = [](int& value) {
                while (!(std::cin >> value)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter an integer: ";
                }
            };

            std::cout << "A: ";
            validateInput(Orderfour);

            std::cout << "B: ";
            validateInput(OrderThree);

            std::cout << "C: ";
            validateInput(OrderTwo);

            std::cout << "D: ";
            validateInput(OrderOne);

            std::cout << "E: ";
            validateInput(constant);

            std::cout << "Please press 'y' if you are happy with this expression: ";
            std::cout << "(" << Orderfour << ")x^4 + (" << OrderThree << ")x^3 + (" << OrderTwo << ")x^2 + (" << OrderOne << ")x + (" << constant << ")" << std::endl;

            char choice;
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                isHappy = true;
            }
            if (conditionsKept(Orderfour, OrderThree, OrderTwo, OrderOne, constant)) {
                conditionsSatisfied = true;
            }
        }
        usersPolynomialCoefficients.push_back(Orderfour); usersPolynomialCoefficients.push_back(OrderThree);
        usersPolynomialCoefficients.push_back(OrderTwo); usersPolynomialCoefficients.push_back(OrderOne);
        usersPolynomialCoefficients.push_back(constant);
    }

    void saveOutputToFile(const std::string& output) {
        std::fstream polynomialFile;
        polynomialFile.open("Polynomial_results.txt", std::ios::app);
        if (polynomialFile.is_open()) {
            polynomialFile.seekg(0, std::ios::end);
            bool isEmpty = polynomialFile.tellg() == 0;
            if (!isEmpty) {
                polynomialFile << "\n\n";
            }
            polynomialFile << output;
            polynomialFile.close();
        }
    }


    //setters and getters

    /*void setUsersPolynomialCoefficient(int index, int value) {
        if (index >= 0 && index < 5) {
            UsersPolynomialCoefficients[index] = value;
        }
    }*/

    const std::vector<int> &getUsersPolynomialCoefficients() {
        return usersPolynomialCoefficients;
    }

protected:

    bool conditionsKept(int powFour, int powThree, int powTwo, int powOne, int constant) {
        if ((powFour >= -9 && powFour <= 9) && (powThree >= -9 && powThree <= 9) && (powTwo >= -9 && powTwo <= 9) && (powOne >= -9 && powOne <= 9)) {
            if (constant >= -1000 && constant <= 1000) {
                return true;
            }
        }
        return false;
    }

    std::vector<int> usersPolynomialCoefficients{};
    //int UsersPolynomialCoefficients[5]{ 0 };
};