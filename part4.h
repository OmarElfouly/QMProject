#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

void part4func(map<string, vector<int>> PIToMinterm, string vars, vector<int> minterms) {
	//find epi, then remove dominated rows, then remove dominating cols repeat until no minterms left
	//an epi is an essential prime implicant that is the only cover for a certain minterm
	//so for every minterm we must know who is covering it

	// Since we wish to find the minterms of each PI and the PIs of each minterm we would require
	// a data structre that allows us to read both of these with a reasonable complexity
	// given the choice of sets or maps we have chosen maps for
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
			//mintermToPI.erase(minterm.first);
			PIToMinterm.erase(pi);
			flag = true;
		}
	}
	for (auto min : mintermsToErase) {
		mintermToPI.erase(min);
	}

	//output
	if (flag) {
		cout << "The essential prime implicants are:\n";
		for (auto epi : EPIS) {
			cout << "-\t" << epi << endl;
		}
	}
	else {
		cout << "There are no essential prime implicants.\n";
	}
	//remain minterm output
	cout << "\nRemaining minterms are:\n";
	for (auto min : mintermToPI) {
		cout << "-\tm" << min.first << endl;
	}

	return;
}