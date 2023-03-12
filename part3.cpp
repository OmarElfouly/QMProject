#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <bitset>

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

// This function takes two implicants represented as strings of '0's, '1's, and '-',
// and combines them into a new implicant that has '-'s in the positions where the
// two implicants differ.
string combine(string imp1, string imp2) {
	string result;
	int n = imp1.size(); // Get the size of the implicants
	for (int i = 0; i < n; i++) { // Iterate over each character of the implicants
		if (imp1[i] == imp2[i]) { // If the characters are the same
			result.push_back(imp1[i]); // Append the character to the new implicant
		}
		else { // If the characters are different
			result.push_back('-'); // Append a '-' to the new implicant
		}
	}
	return result; // Return the new implicant
}

// This function takes two implicants represented as strings of '0's, '1's, and '-',
// and returns true if the two implicants differ in only one position, indicating
// that they can be combined to form a new implicant.
bool match(string imp1, string imp2) {
	int n = imp1.size(); // Get the size of the implicants
	int diff_count = 0; // Initialize a difference count to 0
	for (int i = 0; i < n; i++) { // Iterate over each character of the implicants
		if (imp1[i] != imp2[i]) { // If the characters differ
			diff_count++; // Increment the difference count
		}
	}
	return (diff_count == 1); // Return true if the difference count is 1, false otherwise
}


string binary_diff(int a, int b) {
	string binary_a = bitset<32>(a).to_string();
	string binary_b = bitset<32>(b).to_string();

	// Find the index of the different bit
	int diff_index = -1;
	for (int i = 0; i < binary_a.length(); i++) {
		if (binary_a[i] != binary_b[i]) {
			diff_index = i;
			break;
		}
	}

	if (diff_index == -1) {
		// The two binary numbers are the same
		return "";
	}

	// Replace the different bit with "-"
	string result = binary_a;
	result[diff_index] = '-';
	return result;
}



map<string, vector<int>> primeimplicants(vector<bool> table, vector<string> var)
{
	vector<int> minterms;

	for (int i = 0; i <= table.size(); i++)
	{
		if (table[i])
			minterms.push_back(i);
	}

	vector<vector<int>> groups(var.size());  // Initialize the groups
	for (auto m : minterms) {
		int count = count_ones(m);
		groups[count].push_back(m);
	}

	vector<string> primes;
	for (int i = 0; i < 31; i++)
	{
		if (groups[i].empty() || groups[i + 1].empty())
			continue;  // Skip empty groups

		for (auto num1 : groups[i])
		{
			for (auto num2 : groups[i + 1])
			{
				if (differ_by_one(num1, num2)) {
					// Combine the two numbers into a new number
					string new_num = binary_diff(num1, num2);
						// Check if the new number is already in the list of primes
						if (find(primes.begin(), primes.end(), new_num) == primes.end())
							primes.push_back(new_num);
				}
			}
		}
	}
}
	





