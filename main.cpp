#include "part4.h"
#include "part3.h"

int main() {
	map<string, vector<int>> piToM_test = {
		{"AB",{0,4}},
		{"AC",{2,4}},
		{"AF",{0,1,2}},
		{"AE",{3}}
	};
	//string vars = "ABCFE";
	//vector<int> mins= { 0,1,2,3 };

	part4And5(piToM_test);
	vector<int> minterms = { 0, 4,8,5,6,9,10,7,13,15 };
	vector<string> var = { "a" , "b" ,"c","d", };
	cout << "\n\n\n";
	part4And5(primeimplicants(minterms, var));

}