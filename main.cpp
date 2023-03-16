#include "part4.h"


int main() {
	map<string, vector<int>> piToM_test = {
		{"AB",{0,4}},
		{"AC",{2,4}},
		{"AF",{0,1,2}},
		{"AE",{3}}
	};
	string vars = "ABCFE";
	vector<int> mins= { 0,1,2,3 };

	part4And5(piToM_test, vars, mins);

}