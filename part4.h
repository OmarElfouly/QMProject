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
	/*if (maybeSubset.size() == 0) {
		return false;
	}*/
	sort(maybeSubset.begin(), maybeSubset.end());
	sort(maybeSuperset.begin(), maybeSuperset.end());
	return includes(maybeSubset.begin(), maybeSubset.end(), maybeSuperset.begin(), maybeSuperset.end());
}


void deleteMinterm(map<string, vector<int>>& oldmap, int minterm) {
	for (auto pi = oldmap.begin(); pi != oldmap.end(); pi++) {
		pi->second.erase(std::remove(pi->second.begin(), pi->second.end(), minterm), pi->second.end());
	}
	
}

void deletePI(map<int, vector<string>>& oldmap, string piTerm) {
	for (auto min = oldmap.begin(); min != oldmap.end();min++) {
		min->second.erase(remove(min->second.begin(), min->second.end(), piTerm), min->second.end());
	}
}

void part4And5(map<string, vector<int>> PIToMinterm, string vars, vector<int> minterms) {
	if (PIToMinterm.size() == 0) {
		cout << "\nNo PI terms were given.\n";
		return;
	}
	//need a condition in case the prime implicant is "1"
	
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
	set<int> mintermsToErase;

	for (auto minterm : mintermToPI) {
		if (minterm.second.size() == 1) {// if there is only a single PI covering this minterm
			string pi = minterm.second.front();
			EPIS.push_back(pi);
			mintermsToErase.insert(minterm.first);
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
			mintermsToErase.insert(mins);
		}
		PIToMinterm.erase(epi);
		deletePI(mintermToPI, epi);
	}

	for (auto min : mintermsToErase) {
		mintermToPI.erase(min);
		deleteMinterm(PIToMinterm, min);
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
				if (x.first != y.first&& IsSubset<string>(x.second, y.second)) {
					mintermToPI.erase(x.first);
					deleteMinterm(PIToMinterm, x.first);
				}
			}
		}

		//remove dominated rows
		auto x = PIToMinterm.begin();
		while ( x!=PIToMinterm.end()) {
			auto y = PIToMinterm.begin();
			while(y!=PIToMinterm.end()) {
				if (x->first != y->first && IsSubset<int>(x->second, y->second)) {
					string yName = y->first;
					auto newy = PIToMinterm.begin();
					PIToMinterm.erase(yName);
					deletePI(mintermToPI,yName);
					y = newy;
				}
				else {
					y++;
				}
			}
			x++;
		}

		//chose the new "artifical" epis
		vector<int> mintermsToErase;
		vector<string> piToErase;

		for (auto minterm : mintermToPI) {
			if (minterm.second.size() == 1) {// if there is only a single PI covering this minterm
				string pi = minterm.second.front();
				finalAnswer.push_back(pi);// add the pi to list of epis
				piToErase.push_back(pi);
				mintermsToErase.push_back(minterm.first);
			}
		}

		for (auto pi : piToErase) {
			for (auto mins : PIToMinterm[pi]) {
				mintermsToErase.push_back(mins);
			}
			PIToMinterm.erase(pi);
		}

		for (auto min : mintermsToErase) {
			mintermToPI.erase(min);
		}

	}


	cout << "Final answer is:\n";
	cout << finalAnswer.front();
	finalAnswer.erase(finalAnswer.begin());
	for (auto term : finalAnswer) {
		cout << " + "<<term;
	}
	return;
}