#include <iostream>
#include <vector>
#include <string>
#include <stack>

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

bool validation(string input, vector<string> terms)
{
	input.erase(remove(input.begin(), input.end(), ' '), input.end());	//remove any spaces in the input, easier to handle.
	int arr[2] = { 0, 0 };

	for (auto& i : input) {
		if (i == '(')
			arr[0]++;
		else if (i == ')')
			arr[1]++;
	}

	if(!(arr[0] == arr[1]))		//if the number of opening and closing brackets are unequal, then the input is invalid.
		return false;
}