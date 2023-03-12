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

bool validation(string input, vector<string> terms)
{
	input.erase(remove(input.begin(), input.end(), ' '), input.end());		//remove any spaces in the input, easier to handle.
	transform(input.begin(), input.end(), input.begin(), ::tolower);		//all characters are lowercase for convencience and consistency.
	if (((input[0] < 97 || input[0] > 122) && input[0] != 40) || ((input.back() < 97 || input.back() > 122) && input.back() != 41 && input.back() != 39))
		return false;														//making sure we do not start or end with anything other than letters, or (correct) brackets, or NOTs at the end.

	int arr[2] = { 0, 0 };
	for (auto& i : input) {
		if (i == '(')
			arr[0]++;
		else if (i == ')')
			arr[1]++;
		else if (!isalpha(i) && i != '+' && i != 39)		//can use the isalpha() function for above if statements
			return false;
	}

	if (arr[0] != arr[1])		//if the number of opening and closing brackets are unequal, then the input is invalid.
		return false;
	else if (arr[0] == 0 && arr[1] == 0)
		return true;				//if there are no brackets, then it is in SoP form.


}