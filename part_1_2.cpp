#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>

/*
A: Part 1 and 2, Ahmed Ali

- Implementation theory: Use a stack to find every matching pair of brackets. For each pair, determine whether it contains purely a product, or if it contains a sum.
Once each pair is determined, loop through the input, and whenever we reach a "warning" input (a multiplication followed by something unknown) then we check that
there is no violation (sum * product, multi-var NOT). If we find a "+", we are fine, if not, we must check. I will use a vector of a pair of a pair of integers
and a character, and the pair of inetegrs is the indices of the opening and closing bracket, and the character tells me if it's a sum, 's' or a product, 'p'.
I will also need to have a checker before checking whether a bracket contains a sum or a product, which checks that if the character after a bracket is a NOT, "'", then
I need to make sure that the bracket does not contain more than one variable, for example, (abc)' is invalid, but (a''')' is.
*/

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