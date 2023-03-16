#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <algorithm>

using namespace std;

struct implicant {
	string mincovered;
	string imp;
	bool is_combined = false;

	implicant(string m, string i, bool c) {
		mincovered = m;
		imp = i;
		is_combined = c;
	}
};

// Count the number of 1's in a binary number
int count_ones(const std::string& int_string) {
	int num = std::stoi(int_string);
	std::string binary_string = std::bitset<32>(num).to_string();
	int count = 0;
	for (char c : binary_string) {
		if (c == '1') {
			count++;
		}
	}
	return count;
}

// Check if two binary numbers differ by exactly one bit
bool differ_by_one(const string& str1, const string& str2) {
	if (str1.length() != str2.length()) {
		return false; // If the strings are of different lengths, they can't differ by one character
	}
	int diff_count = 0;
	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] != str2[i]) {
			if (str1[i] == '-' || str2[i] == '-') {
				return false; // If either of the characters is a '-', they can't differ by one character
			}
			diff_count++;
		}
	}
	return (diff_count == 1); // Return true if there is only one different character
}

// This function takes in two binary strings of equal length and combines them into a new
// binary string where '-' is used to represent differing bits
string combinestring(string a, string b) {
	// Check that the two strings are the same length
	if (a.length() != b.length()) {
		return "";
	}
	// Combine the strings into a new string
	string result = "";
	for (int i = 0; i < a.length(); i++) {
		// If the bits differ, add '-' to the result
		if (a[i] != b[i]) {
			result += "-";
		}
		// Otherwise, add the matching bit to the result
		else {
			result += a[i];
		}
	}
	return result;
}

//converts a decimal number into a binary string, padding with leading zeroes to reach a specified length.
string to_binary_string(int num, int length) {
	string binary_str; 
	while (num > 0) { // convert decimal to binary by repeated division by 2
		binary_str = to_string(num % 2) + binary_str; // add the remainder to the beginning of the string
		num /= 2;
	}
	while (binary_str.length() < length)  // pad the string with leading zeroes until it reaches the desired length
	{
		binary_str = "0" + binary_str;
	}
	return binary_str; 
}


void printVector(const vector<vector<implicant>>& vec) {
	for (const auto& innerVec : vec) {
		for (const auto& imp : innerVec) {

			for (const auto& str : imp.mincovered) {
				cout << str;
			}

			cout << " " << imp.imp << " " << endl;
		}
		cout << endl;
	}
}

vector<char> parseCommaSeparatedString(const string& str) {
	vector<char> chars;
	stringstream ss(str);
	string token;
	while (getline(ss, token, ',')) {
		chars.push_back(token[0]);
	}
	return chars;
}



vector<implicant> generate_column(vector<vector<implicant>>& groups, vector<string> var)
{
	vector<string> primes;
	vector<vector<implicant>> primegrps(var.size());
	bool is_combined;
	vector<implicant> prime_implicants;

	do
	{
		is_combined = false;
		for (int i = 0; i < var.size() - 1; i++)
		{
			if (groups[i].empty() || groups[i + 1].empty())
			continue;  // Skip empty groups

			for (auto& num1 : groups[i])
			{
				for (auto& num2 : groups[i + 1])
				{
					if (differ_by_one(num1.imp, num2.imp))
					{
						// Combine the two numbers into a new number
						string new_num = combinestring(num1.imp, num2.imp);
						// Check if the new number is already in the list of primes
						num1.is_combined = true;
						num2.is_combined = true;
						if (find(primes.begin(), primes.end(), new_num) == primes.end())
						{
							primes.push_back(new_num);


							implicant new_imp(num1.mincovered + "," + num2.mincovered, new_num, false);
							primegrps[i].push_back(new_imp);

							is_combined = true;
						}
					}
				}
				if (!num1.is_combined)
					prime_implicants.push_back(num1);
			}
		}
		printVector(groups);
		cout << "-------------------------------------------------------" << endl;
		groups = std::move(primegrps);
		primegrps.resize(var.size());

	} 
	while (is_combined);

	return prime_implicants;
}


map<string, vector<int>> primeimplicants(vector<string> minterms , vector<string> var)
{
	int numofmin = minterms.size();

	map<string, vector<int>> result;

	if (numofmin == 1 << var.size())
	{
		result["1"];
		return result;

	}
	if (numofmin == 0)
	{
		return result;
	}
		

	vector<vector<implicant>> groups(var.size() + 1); // Initialize the groups
	for (auto m : minterms) {
		int count = count_ones(m);

		string newbin = to_binary_string(stoi(m), var.size());
		implicant newimp(m, newbin, false);

		groups[count].push_back(newimp);
	}

	vector<implicant> prime_implicants;
	prime_implicants = generate_column(groups, var);

	vector<char> mins;
	for (const auto& imp : prime_implicants)
	{
		mins = parseCommaSeparatedString(imp.mincovered);
		vector<int> intVec(mins.size());

		transform(mins.begin(), mins.end(), intVec.begin(),
			[](char c) { return c - '0'; });

		result[imp.imp] = intVec;
	}

	for (const auto& kv : result) {
		cout << kv.first << ": ";
		for (char c : kv.second) {
			cout << c << " ";
		}
		cout << endl;
	}


	
	return result; 
}


	





