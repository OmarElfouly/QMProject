#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;


//this function will take an input map where key is the PI and the data is a vector of bool values such that 
//a True in position x means this PI covers minterm x

void SimplifyPIS(map<string, vector<int>> PIToMinterm, string vars, vector<int> minterms) {
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

	

}