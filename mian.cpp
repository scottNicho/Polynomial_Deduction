
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"PolynomialGenerator.h"
#include"FileScholar.h"
#include"Curve_Analysis .h"

int main() {
	FileScholar monkey;
	PolynomialGenerator<double> doggy;
	CurveAnalysis bush;
	std::vector<double> testVector{0,-2,-7,-5,-1,10,12,10,8,6,4,2,0};
	std::string testSet = { "12,34,6,778,2,13,11,28,29,72,90,113,207" };

	
	doggy.AskRunUsersPolynomial();
	monkey.showUserFile();

	char userInput;
	std::cout <<"Would you like to read and derive all the polinomials in the output file then save them? \n please press y/Y for yes"<< std::endl;
	std::cin >> userInput;
	if (userInput == 'y' || userInput == 'Y') {
		bush.readAndSaveBatch();
	}
	
	


	return 0;
}

