#include "part1_2.h"
#include "part4_5.h"
#include "part3.h"

int main() {
	
	
	vector<string> testCases;
	testCases.push_back("aa'+bb'+cc'");
	testCases.push_back("a'+a+b+c");
	testCases.push_back("aaaa + b'b'b'");
	testCases.push_back("a'b'c'd' + a'bc'd'+a'bc'd+a'bcd'+a'bcd + ab'c'd'+ab'c'd+ab'cd'+abc'd + abcd");
	testCases.push_back("a''b ++ c");
	testCases.push_back("((abbbc)(ac+d))");
	testCases.push_back("(((abbbc'''''))+cdd)");
	testCases.push_back("(a+b)'");
	testCases.push_back("ac + Ac");
	testCases.push_back("((((abcd''''ef'''ghij)) + ghi''') ++++ abbbbc)");

	cout << "The following is the output for our test cases:\n";



	for (int i = 0; i < 10; i++) {
		vector<string> termsTest; map<char, int> indexTest;
		vector<int> mintermsTest;
		if (validation(testCases[i], termsTest, indexTest)) {
			mintermsTest = truthTable(testCases[i], termsTest, indexTest);
			vector<char> varTest = varList(testCases[i]);
			map<string, vector<int>> piMapTest;
			piMapTest = primeimplicants(mintermsTest, varTest, "1");
			part4And5(piMapTest);

		}
	}

	cout << "\n\n\nEnd of test cases. Beginning normal algorithim.\n\n\n";

	cout << "Welcome to our QM program!\nThis program accepts any lowercase latin letter starting from 'a' and uses + as an OR, accepts brackets, and uses ' as a not.\n\n";

	
	bool cont = true;
	while (cont) {
		cout << "\n\nPlease input function:\n";
		string input;
		getline(cin, input);
		vector<string> terms; map<char, int> index;
		vector<int> minterms;
		if (validation(input, terms, index)) {
			minterms = truthTable(input, terms, index);
			vector<char> var = varList(input);
			string choice;
			cout << "Would you like to print the QM table?\n1-\tYes\n2-\tNo\n\nInput your choice as a number: ";
			cin >> choice;
			map<string, vector<int>> piMap;
			while (choice != "1" && choice != "2") {
				cout << "\nInvalid choice!\nPlease input either 1 or 2: ";
				cin >> choice;
			}
			
			piMap = primeimplicants(minterms, var,choice);
			
			part4And5(piMap);
		}
		string c;
		cout << "\n\nWould you like to keep running the program?\n1-\tYes\n2-\tNo\n\nInput your choice as a number: ";
		cin >> c;
		map<string, vector<int>> piMap;
		while (c != "1" && c != "2") {
			cout << "\nInvalid choice!\nPlease input either 1 or 2: ";
			cin >> c;
		}
		if (c == "1") {
			cont = true;
			cin.ignore();
		}
		else if (c == "2") {
			cont = false;
		}
	}
	return 0;
}