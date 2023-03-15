#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>

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
		if (isalpha(i) && find(vars.begin(), vars.end(), i) != vars.end())	//if it's a letter and does not exist in the vector, add it.
			vars.push_back(i);
	}
	sort(vars.begin(), vars.end());

	return vars;
}

bool validation(string input, vector<string> terms)
{
	bool defaultBool = true;
	vector<int> allBrackIndices;

	input.erase(remove(input.begin(), input.end(), ' '), input.end());		//remove any spaces in the input, easier to handle.
	transform(input.begin(), input.end(), input.begin(), ::tolower);		//all characters are lowercase for convencience and consistency.
	if (((input[0] < 97 || input[0] > 122) && input[0] != 40) || ((input.back() < 97 || input.back() > 122) && input.back() != 41 && input.back() != 39))
		return false;														//making sure we do not start or end with anything other than letters, or (correct) brackets, or NOTs at the end.

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
		if (i.second == 's') {		//checks if there is a sum within brackets, as that is where violations occur.
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