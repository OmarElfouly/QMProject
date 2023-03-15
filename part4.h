#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

template <typename T>
bool IsSubset(vector<T> maybeSuperset, vector<T> maybeSubset)
{
	if (maybesubset.size() == 0) {
		return false;
	}
	sort(maybeSubset.begin(), maybeSubset.end());
	sort(maybeSuperset.begin(), maybeSuperset.end());
	return includes(maybeSubset.begin(), maybeSubset.end(), maybeSuperset.begin(), maybeSuperset.end());
}

void part4And5(map<string, vector<int>> PIToMinterm, string vars, vector<int> minterms) {
	//find epi, then remove dominated rows, then remove dominating cols repeat until no minterms left
	//an epi is an essential prime implicant that is the only cover for a certain minterm
	//so for every minterm we must know who is covering it

	// Since we wish to find the minterms of each PI and the PIs of each minterm we would require
	// a data structre that allows us to read both of these with a reasonable complexity
	// given the choice of sets or maps we have chosen maps for the convience offered by keys

	map<int, vector<string>> mintermToPI;
	for (auto piWithMinterms : PIToMinterm) {
		for (auto minterm : PIToMinterm[piWithMinterms.first]) {
			mintermToPI[minterm].push_back(piWithMinterms.first);
		}
	}

	// first we find all epis
	vector<string> EPIS;
	bool flag = false;
	vector<int> mintermsToErase;

	for (auto minterm : mintermToPI) {
		if (minterm.second.size() == 1) {// if there is only a single PI covering this minterm
			string pi = minterm.second.front();
			EPIS.push_back(pi);
			mintermsToErase.push_back(minterm.first);
			flag = true;
		}
	}


	//outputing epis
	if (flag) {
		cout << "The essential prime implicants are:\n";
		for (auto epi : EPIS) {
			cout << "-\t" << epi << endl;
		}
	}
	else {
		cout << "There are no essential prime implicants.\n";
	}

	//remaing minterm output
	for (auto epi : EPIS) {
		for (auto mins : PIToMinterm[epi]) {
			mintermsToErase.push_back(mins);
		}
		PIToMinterm.erase(epi);
	}

	for (auto min : mintermsToErase) {
		mintermToPI.erase(min);
	}


	cout << "\nRemaining minterms are:\n";
	for (auto min : mintermToPI) {
		cout << "-\tm" << min.first << endl;
	}
	//Part 5 now requires us to repeat this process until there are no remaining minterms
	vector<string> finalAnswer = EPIS;
	while (mintermToPI.size() > 0) {// while there still exist uncovered minterms...
		//remove dominating columns
		for (auto x : mintermToPI) {
			for (auto y : mintermToPI) {
				if (x.first != y.first) {
					if (IsSubset<string>(x.second, y.second)) {
						mintermToPI.erase(x.first);
					}
				}
			}
		}

		//remove dominated rows

	}
	return;
}