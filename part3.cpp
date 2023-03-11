#include <iostream>
#include <map>
#include <vector>

using namespace std;
// Count the number of 1's in a binary number
int count_ones(int num) {
	int count = 0;
	while (num) {
		count += num % 2;
		num /= 2;
	}
	return count;
}
// Check if two binary numbers differ by exactly one bit
bool differ_by_one(int num1, int num2) {
	int diff = num1 ^ num2;
	return (count_ones(diff) == 1);
}
// check if two strings differ by one character only
bool isOneCharDiff(string str1, string str2) {
	int diffCount = 0;
	if (str1.length() != str2.length()) {
		return false; 
	}
	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] != str2[i]) {
			diffCount++;
		}
		if (diffCount > 1) {
			return false; 
		}
	}
	return (diffCount == 1); 
}


map<string, vector<int>> primeimplicants(vector<bool> table, vector<string> var)
{
	vector<int> minterms;

	for (int i = 0; i <= table.size(); i++)
	{
		if (table[i])
			minterms.push_back(i);

	}
	vector<vector<int>> groups(32);  // Initialize the groups
	for (auto m : minterms) {
		int count = count_ones(m);
		groups[count].push_back(m);
	}


}

