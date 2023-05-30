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


    void setOrderfourPolynomial();

    void saveOutputToFile(const std::string& output);

    void savePolynomialToFile(const std::string& polynomialStr);

    std::vector<int> extractOutputSet(std::string line);


    //setters and getters

    /*void setUsersPolynomialCoefficient(int index, int value) {
        if (index >= 0 && index < 5) {
            UsersPolynomialCoefficients[index] = value;
        }
    }*/

    const std::vector<int> &getUsersPolynomialCoefficients() {
        return usersPolynomialCoefficients;
    }

    const std::vector<int> getStartEndRange() {
        return startEndRange;
    }

    void clearStartEndRange() {
        startEndRange.clear();
    }

    void showUserFile();

    bool findLetter(const std::string line, const char Letter);

    void GetStartEnd(const std::string line);

protected:

    bool conditionsKept(int powFour, int powThree, int powTwo, int powOne, int constant);

    

    std::vector<int> usersPolynomialCoefficients{};
    std::vector<int> startEndRange{};
    //int UsersPolynomialCoefficients[5]{ 0 };
};
