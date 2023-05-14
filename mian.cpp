
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
	std::vector<int> testVector{2,4,6,8,10,12,14,16};
	
//	doggy.setCoefficientsRange(0, -2, 6, 1, -3, 0, 10);
//doggy.updateOutputSet();
//std::vector<int>temp = doggy.getOutputSet();
//for (auto xi : temp) {
//	std::cout << xi << std::endl;
//}

	bush.curveAnalyser();

	return 0;
}

