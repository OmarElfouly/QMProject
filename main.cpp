#include "part4.h"


int main() {
	map<string, vector<int>> piToM_test = {
		{"AB",{0}},
		{"AC",{2}},
		{"AF",{0,1,2}},
		{"AE",{3}}
	};
	string vars = "ABCFE";
	vector<int> mins= { 0,1,2,3 };

	part4func(piToM_test, vars, mins);
}