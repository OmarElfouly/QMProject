#pragma once
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

template <typename T>
bool IsSubset(vector<T> maybeSub, vector<T> maybeSuper)
{
	/*if (maybeSubset.size() == 0) {
		return false;
	}*/
	sort(maybeSuper.begin(), maybeSuper.end());
	sort(maybeSub.begin(), maybeSub.end());
	return includes(maybeSuper.begin(), maybeSuper.end(), maybeSub.begin(), maybeSub.end());
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

void part4And5(map<string, vector<int>> PIToMinterm) {
	if (PIToMinterm.size() == 0) {
		cout << "\nNo PI terms, so no EPIs and no remaining minterms.\n";
		cout << "Final answer:\nFunction = 0\n";
		return;
	}
	if (PIToMinterm.size() == 1 && PIToMinterm.find("1") != PIToMinterm.end()) {
		cout << "\nFunction = 1 therefore:\nEssential prime implicant are:\n-\t1\n\nNo remaining minterms.\nFinal answer:\nFunction = 1\n";
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
	set<string> EPIS;
	bool flag = false;
	set<int> mintermsToErase;

	for (auto minterm : mintermToPI) {
		if (minterm.second.size() == 1) {// if there is only a single PI covering this minterm
			string pi = minterm.second.front();
			EPIS.insert(pi);
			mintermsToErase.insert(minterm.first);
			flag = true;
		}
	}


	//outputing epis
	if (flag) {
		cout << "\n\nThe essential prime implicants are:\n";
		for (auto epi : EPIS) {
			cout << "-\t" << epi << endl;
		}
	}
	else {
		cout << "\n\nThere are no essential prime implicants.\n";
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


	cout << "\n\nRemaining minterms are:\n";
	for (auto min : mintermToPI) {
		cout << "-\tm" << min.first << endl;
	}
	//Part 5 now requires us to repeat this process until there are no remaining minterms
	set<string> finalAnswer = EPIS;


	while (mintermToPI.size() > 0) {// while there still exist uncovered minterms...
		//remove dominating columns, i.e super set
		
		auto a = mintermToPI.begin();
		while (a!= mintermToPI.end()) {
			auto b = mintermToPI.begin();
			while (b!= mintermToPI.end()) {
				if (a->first != b->first&& IsSubset<string>( a->second, b->second)) {
					int bName = b->first;
					b = mintermToPI.begin();
					mintermToPI.erase(bName);
					deleteMinterm(PIToMinterm, bName);
				}
				else {
					b++;
				}
			}
			a++;
		}

		//remove dominated rows
		auto x = PIToMinterm.begin();
		while ( x!=PIToMinterm.end()) {
			auto y = PIToMinterm.begin();
			while(y!=PIToMinterm.end()) {
				if (x->first != y->first && IsSubset<int>(y->second, x->second)) {
					string yName = y->first;
					
					PIToMinterm.erase(yName);
					deletePI(mintermToPI,yName);
					y = PIToMinterm.begin();
					
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
				finalAnswer.insert(pi);// add the pi to list of epis
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


	cout << "\n\nFinal answer is:\nFunction = ";
	cout << *finalAnswer.begin();
	finalAnswer.erase(finalAnswer.begin());
	for (auto term : finalAnswer) {
		cout << " + "<<term;
	}
	return;
}