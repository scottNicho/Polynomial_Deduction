#include "FileScholar.h"

void FileScholar::setOrderfourPolynomial() {
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

void FileScholar::showUserFile() {
    int scrollingLetter = 65;
    std::string fullFile = "";
    std::fstream file("Polynomial_results.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            fullFile.append(line);
            fullFile.append("\n");
        }
    }
    std::cout << " here is all the user generated polynomials\n" << fullFile << std::endl;
}

void FileScholar::saveOutputToFile(const std::string& output) {
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

void FileScholar::savePolynomialToFile(const std::string& polynomialStr) {
    std::fstream polynomialFile;
    polynomialFile.open("Polynomial_expression.txt", std::ios::app);
    if (polynomialFile.is_open()) {
        polynomialFile.seekg(0, std::ios::end);
        polynomialFile << polynomialStr + "\n\n";
        polynomialFile.close();
    }
}

std::vector<int> FileScholar::extractOutputSet(std::string line) {
    std::vector<int> returnVector = {};
    int xi = 0;
    bool inNumber = false;
    while (xi < line.length()) {
        if ((static_cast<int>(line[xi]) <= 57 && static_cast<int>(line[xi]) >= 48) || line[xi] == '-') {
            for (int j = xi + 1; j < line.length(); j++) {
                if ((static_cast<int>(line[j]) > 57 || static_cast<int>(line[j]) < 48) || j + 1 == line.length()) {
                    int number = std::stoi(line.substr(xi, j));
                    returnVector.push_back(number);
                    xi = j;
                    break;
                }
            }
        }
        xi++;
    }

    return returnVector;
}

//protected
void FileScholar::GetStartEnd(const std::string line) {
    unsigned int xi = 0;
    while (xi < line.length()) {
        if (static_cast<int>(line[xi]) <= 57 && static_cast<int>(line[xi]) >= 48) {
            for (int j = xi + 1; j < line.length(); j++) {
                if ((static_cast<int>(line[j]) > 57 || static_cast<int>(line[j]) < 48) || j + 1 == line.length()) {
                    int number = std::stoi(line.substr(xi, j));
                    startEndRange.push_back(number);
                    xi = j;
                    break;
                }
            }
        }
        xi++;
    }
}

bool FileScholar::findLetter(const std::string line, const char Letter) {
    if (line[0] == Letter) { return true; }
    return false;
}


bool FileScholar::conditionsKept(int powFour, int powThree, int powTwo, int powOne, int constant) {
    if ((powFour >= -9 && powFour <= 9) && (powThree >= -9 && powThree <= 9) && (powTwo >= -9 && powTwo <= 9) && (powOne >= -9 && powOne <= 9)) {
        if (constant >= -1000 && constant <= 1000) {
            return true;
        }
    }
    return false;
}