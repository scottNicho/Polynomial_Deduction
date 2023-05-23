
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"PolynomialGenerator.h"
#include"FileScholar.h"
#include"Curve_Analysis .h"

int main() {
	FileScholar monkey;
	PolynomialGenerator<int> doggy;
	CurveAnalysis bush;
	std::vector<int> testVector{0,-2,6,1,0};
	std::string testSet = { "12,34,6,778,2,13,11,28,29,72,90,113,207" };

	doggy.AskRunUsersPolynomial();
	bush.DeducePolynomial();
	std::vector<int> output = bush.getStartingSet();
	for (auto ll : output) {
		std::cout << ll << std::endl;
	}
	//doggy.AskRunUsersPolynomial();
	//bush.curveDeduction();
	/*doggy.setCoefficientsRange(testVector, 0, 10);
	std::vector<int>temp = doggy.generateOutputSet();
	for (auto xi : temp) {
	std::cout << xi << std::endl;
	}*/
	return 0;
}

