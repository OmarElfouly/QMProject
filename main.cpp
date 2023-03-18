#include "part1_2.h"
#include "part4.h"
#include "part3.h"
#include <chrono>

int main() {
	/*map<string, vector<int>> piToM_test = {
		{"AB",{0,4}},
		{"AC",{2,4}},
		{"AF",{0,1,2}},
		{"AE",{3}}
	};
	//string vars = "ABCFE";
	//vector<int> mins= { 0,1,2,3 };

	part4And5(piToM_test);
	vector<int> minterms = { 0, 4,8,5,6,9,10,7,13,15 };
	vector<char> var = { 'a' , 'b' ,'c','d' };
	cout << "\n\n\n";
	part4And5(primeimplicants(minterms, var));
	*/
	auto start = chrono::high_resolution_clock::now();
	string input;
	getline(cin, input);
	vector<string> terms; map<char, int> index;
	vector<int> minterms;
	if (validation(input, terms, index)) {
		minterms = truthTable(input, terms, index);
		vector<char> var = varList(input);
		part4And5(primeimplicants(minterms, var));
	}
	else {
		cout << "Invalid input." << endl;
		//return;
	}
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	std::cout << "Time taken by function: "
		<< duration.count() << " microseconds" << "\n";
}