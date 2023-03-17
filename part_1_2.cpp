#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>
#include <map>
#include <bitset>
#include <set>

using namespace std;

vector<string> split(string input, string delim)		//string splitting function, splits function between each sum (delimiter), each product is an element.
{

	vector<string> terms;
	string delimiter = delim;
	size_t pos = 0;
	string token;
	while ((pos = input.find(delimiter)) != string::npos) {
		token = input.substr(0, pos);
		terms.push_back(token);
		input.erase(0, pos + delimiter.length());
	}
	terms.push_back(input);

	return terms;
}

vector<pair<int, int>> bracketPairs(const string input, vector<int>& allBracks)
{
	vector<pair<int, int>> pairs;
	stack<int> stack;

	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '(') {
			stack.push(i);
		}
		else if (input[i] == ')') {
			if (!stack.empty()) {
				int openBracket = stack.top();
				stack.pop();
				pairs.push_back(make_pair(openBracket, i));
				allBracks.erase(remove(allBracks.begin(), allBracks.end(), openBracket), allBracks.end());
				allBracks.erase(remove(allBracks.begin(), allBracks.end(), i), allBracks.end());			//erase brackets from vector with all brackets
			}
		}
	}

	return pairs;
}

vector<char> varList(const string input)
{
	vector<char> vars;
	for (auto& i : input) {
		if (isalpha(i) && find(vars.begin(), vars.end(), i) == vars.end())	//if it's a letter and does not exist in the vector, add it.
			vars.push_back(i);
	}
	sort(vars.begin(), vars.end());

	return vars;
}

bool validation(string input, vector<string>& terms, map<char, int>& index)
{
	bool defaultBool = true;
	vector<int> allBrackIndices;

	input.erase(remove(input.begin(), input.end(), ' '), input.end());		//remove any spaces in the input, easier to handle.
	transform(input.begin(), input.end(), input.begin(), ::tolower);		//all characters are lowercase for convencience and consistency.
	if (((input[0] < 97 || input[0] > 122) && input[0] != 40) || ((input.back() < 97 || input.back() > 122) && input.back() != 41 && input.back() != 39))
		return false;														//making sure we do not start or end with anything other than letters, or (correct) brackets, or NOTs at the end.
	if (input.size() == 0)
		return false;

	vector<char> variableList = varList(input);
	if (variableList.size() > 10)
		return false;

	int arr[2] = { 0, 0 };
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '(') {
			arr[0]++;
			allBrackIndices.push_back(i);
			if (i < (input.size() - 1) && (input[i + 1] == ')' || input[i + 1] == '+' || input[i + 1] == 39))	//opening bracket cannot have a closing bracket, a '+', or a NOT right after it.
				return false;
		}
		else if (input[i] == ')') {
			arr[1]++;
			allBrackIndices.push_back(i);
			if (i > 0 && (input[i - 1] == '(' || input[i - 1] == '+'))	//closing bracket cannot have an opening bracket or a '+' immediately after it.
				return false;
		}
		else if (input[i] == '+' && i < (input.size() - 1) && (input[i + 1] == 39))	//no NOT directly after a '+'.
			return false;
		else if (!isalpha(input[i]) && input[i] != '+' && input[i] != 39)		//can use the isalpha() function for above if statements
			return false;
	}

	if (arr[0] != arr[1])		//if the number of opening and closing brackets are unequal, then the input is invalid.
		return false;
	else if (arr[0] == 0 && arr[1] == 0)
		return true;				//if there are no brackets, then it is in SoP form.

	vector<pair<int, int>> brackets = bracketPairs(input, allBrackIndices);
	vector<pair<pair<int, int>, char>> bracketTerms;

	if (!allBrackIndices.empty())	//this would mean there are "loose" brackets, which is not a valid input. Most cases covered in above, but instances like (a))(b+c, where ( == ), would not be.
		return false;

	for (auto& i : brackets) {
		if (i.second + 1 < input.size() && input[i.second + 1] == 39) {
			string temp = input.substr(i.first + 1, i.second - i.first - 1);
			temp.erase(remove(temp.begin(), temp.end(), 39), temp.end());
			if (temp.size() > 1)		//checking for multi-var NOT, before identifying brackets.
				return false;
		}
	}

	bool sum = false;
	for (auto& i : brackets) {
		sum = false;
		for (int j = i.first + 1; j < i.second; j++) {
			if (input[j] == '+') {
				sum = true;
				break;
			}
		}
		if (sum)
			bracketTerms.push_back(make_pair(i, 's'));	//if a '+' is found at any point between the brackets, the bracket is identified as a sum bracket
		else
			bracketTerms.push_back(make_pair(i, 'p'));	//otherwise, it is identified as a product bracket.
	}

	for (auto& i : bracketTerms) {
		if (i.second == 's') {			//checks if there is a sum within brackets, as that is where violations occur.
			if (i.first.first > 0) {
				char checker = input[i.first.first - 1];
				if (checker != '+' && checker != '(')
					return false;
			}
			if (i.first.second < input.size() - 1) {
				char checker = input[i.first.second + 1];
				if (checker != '+' && checker != ')' && checker != 39)	//checker == 39 should not occur, already accounted for previously.
					return false;
			}
		}
	}

	return defaultBool;
}

void flipVector(vector<vector<int>>& vec, int i, int j)
{
	if (vec[i][j] == 0)
		vec[i][j] = 1;
	else if (vec[i][j] == 1)
		vec[i][j] = 0;
}

vector<int> truthTable(string input, vector<string>& terms, map<char, int>& index)
{
	vector<int> minterms;
	input.erase(remove(input.begin(), input.end(), '('), input.end());
	input.erase(remove(input.begin(), input.end(), ')'), input.end());	//if SoP, brackets do not affect its meaning.

	vector<char> variableList = varList(input);
	int varCount = variableList.size();

	terms = split(input, "+");
	for (int i = 0; i < varCount; i++) {
		index[variableList[i]] = i;					//giving each character its index (hierarchy). A/0 is the MSB.
	}

	int tempIndex = 0;

	vector<vector<int>> dominance(2, vector<int>(varCount, 0));
	for (int i = 0; i < terms.size(); i++) {					//checking if a term has both a normal variable and the same variable NOT'ed.
		dominance = vector<vector<int>>(2, vector<int>(varCount, 0));
		for (int j = 0; j < terms[i].size(); j++) {
			if (j < terms[i].size() && terms[i][j] != 39 && terms[i][j + 1] != 39) {
				tempIndex = index[terms[i][j]];
				dominance[0][index[terms[i][j]]] = 1;
			}
			else if (j < terms[i].size() && terms[i][j] != 39 && terms[i][j + 1] == 39) {
				tempIndex = index[terms[i][j]];
				dominance[1][tempIndex] = 1;
			}
			else if (j < terms[i].size() && terms[i][j + 1] == 39)
				flipVector(dominance, 1, tempIndex);
		}
		for (int k = 0; k < dominance[0].size(); k++) {
			if (dominance[0][k] == 1 && dominance[1][k] == 1) {
				terms.erase(terms.begin() + i);					//if it does, remove it from the list.
				i--;
				break;
			}
		}
	}

	for (auto& i : variableList) {
		cout << i << "\t";
	}
	cout << "f" << endl;

	if (terms.empty()) {
		for (int i = 0; i < 1 << varCount; i++) {
			bitset<10> bits(i);
			for (int i = varCount - 1; i >= 0; i--) {
				cout << bits[i] << "\t";
			}
			cout << "0" << endl;
		}
		cout << "f = 0" << endl;
		cout << "Canonical SoP: 0" << endl;

		return minterms;
	}

	vector<vector<int>> binTerms(terms.size(), vector<int>(varCount, 2));	//all terms in binary. Initialize all elements with 2, which will be my marker for "don't care" terms.

	tempIndex = 0;

	for (int i = 0; i < terms.size(); i++) {
		for (int j = 0; j < terms[i].size(); j++) {
			if (terms[i][j] == 39) {
				flipVector(binTerms, i, tempIndex);	//tempindex only changes in the last iteration, and only changes when it is a variable, so NOTs (39), will only affect the variable.
			}
			else {
				tempIndex = index[terms[i][j]];
				binTerms[i][tempIndex] = 1;			//set the var found to 1 in the binary table.
			}
		}
	}

	bool isMinterm = true;

	for (int i = 0; i < 1 << varCount; i++) {
		bitset<10> bits(i);
		for (int i = varCount - 1; i >= 0; i--) {
			cout << bits[i] << "\t";
		}
		for (int j = 0; j < binTerms.size(); j++) {
			isMinterm = true;
			for (int k = 0; k < binTerms[j].size(); k++) {
				if (binTerms[j][k] != 2 && binTerms[j][k] != bits[binTerms[j].size() - 1 - k]) {
					isMinterm = false;
					break;
				}
			}
			if (isMinterm) {
				minterms.push_back(i);
				break;
			}
		}
		if (isMinterm) {
			cout << "1" << endl;
		}
		else
			cout << "0" << endl;
	}

	if (minterms.size() == 1 << varCount) {
		cout << "f = 1" << endl;
		cout << "Canonical SoP: 1" << endl;

		return minterms;
	}

	cout << "Canonical SoP: ";

	for (int i = 0; i < minterms.size(); i++) {
		bitset<10> bits(minterms[i]);
		for (int j = 0; j < varCount; j++) {
			cout << variableList[j];
			if (bits[varCount - 1 - j] == 0)
				cout << "'";
		}
		if (i < minterms.size() - 1)
			cout << " + ";
	}

	cout << "\nCanonical PoS: ";

	set<int> mins(minterms.begin(), minterms.end());
	vector<int> maxterms;

	for (int i = 0; i < 1 << varCount; i++) {
		if (mins.find(i) == mins.end())
			maxterms.push_back(i);
	}

	for (int i = 0; i < maxterms.size(); i++) {
		bitset<10> bits(maxterms[i]);
		cout << "(";
		for (int j = 0; j < varCount; j++) {
			cout << variableList[j];
			if (bits[varCount - 1 - j] == 1)
				cout << "'";
			if (j < varCount - 1)
				cout << " + ";
		}
		cout << ")";
	}

	return minterms;
}