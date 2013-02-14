#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "Voting.h"

using namespace std;

//class Case {
//	int numCandidates;
//	vector<std::string > candidates;	// vector of candidate names
//	vector<std::vector<int> > ballots;		// vector of all the ballots
//
//	public:
//		Case();
//		int get_count();
//		void set_count(int);
//		void add_candidate(std::string);
//		void add_ballot(std::vector<int>);
//		string get_candidate(int);
//		vector<int> get_ballot(int);
//		int get_ballot_count();
//		~Case();
//};
Case::Case() {

}

int Case::get_count() {
	return numCandidates;
}

void Case::set_count(int count) {
	numCandidates = count;
}

void Case::add_candidate(std::string candidate) {
	candidates.push_back(candidate);
}

void Case::add_ballot(std::vector<int> ballot) {
	ballots.push_back(ballot);
}

vector<int> Case::pop_ballot(int position) {
    vector<int> temp = ballots[position];
    ballots.erase(ballots.begin()+position);
    return temp;
}

string Case::get_candidate(int position) {
	return candidates[position];
}

vector<int> Case::get_ballot(int position) {
	return ballots[position];
}

int Case::get_ballot_count() {
	return ballots.size();
}

Case::~Case() {
	candidates.clear();
	ballots.clear();
//	delete &candidates;
//	delete &ballots;
}

bool voting_read(istream& r, Case *c) {
	//read number of candidates;
	int count;
	r >> count;
	
	(*c).set_count(count);
	
	cout << (*c).get_count() << endl;

	//read candidate names
	int i;
	string name;
	getline(r,name);	//skip blank line
	
	
	for(i = 0; i < (*c).get_count(); i++) {
		getline(r,name);
		cout << name << endl;
		(*c).add_candidate(name);
	}

//	cout << "read the names" << endl;

	//read ballots
	while(getline(r,name)) {
		//if line is empty, reading for the case is done. return.
		if(name.empty()) {
			break;
		}

		cout << name << endl;

		istringstream stream(name);
		vector<int> ballot;

		//read one ballot
		int value;
		while(!stream.eof() && stream >> value) {
			if(value == '\n') {
				break;
			}
			ballot.push_back(value);
		}

		(*c).add_ballot(ballot);
	}
	
//	cout << "read the ballots" << endl;
	return false;
}

void voting_print(ostream& w, vector<string> winner) {
	int i = 0;
	for(; i < (int)winner.size(); i++) {
		w << winner[i] << endl;
	}
}

vector<string> voting_eval(ostream& w, Case *c) {
	vector<string> winner;

	//count ballots
	vector<vector<int> > first_picks; //ballots sorted by first picks. index = first pick
	vector<int> losers; //indexes of losing ballots
	int counter[21] = {0}; //counts the ballots
	int i, j;
	
	cout << "ballot count: " << (*c).get_ballot_count() << endl;
	cout << "candidate count: " << (*c).get_count() << endl;
	
	for(i = 0; i <= (*c).get_count(); i++) {
	    vector<int> empty;
		first_picks.push_back(empty);
	}

//	cout << "filled with empty vectors" << endl;

	//go through all the ballots and check the first choices
	for(i = 0; i < (*c).get_ballot_count(); i++) {
		vector<int> ballot = (*c).get_ballot(i);
		++counter[ballot[0]];
		//add ballot to the sorted vector
		first_picks[ballot[0]].push_back(i); //ballot number goes from 0 to n-1
	}

//	cout << "pushed all the ballots" << endl;

	//check for winner
	while(true) {
		for(i = 1; i < (int)first_picks.size(); i++) {
			if((*c).get_ballot_count() < 2*(int)first_picks[i].size()) {
				//winner
				winner.push_back((*c).get_candidate(i-1));
				return winner;
			}
		}
		
		cout << "checking for ties" << endl;
		
		//check for ties
		unsigned int size = first_picks[1].size();
		bool tie = true;
		for(i = 1; i < first_picks.size(); i++) {
		    cout << "ballot count for candidate " << i << ": " << first_picks[i].size() << endl; 
			if(first_picks[i].size() != size)
				tie = false;
		}

		if (tie == true) {
			for(i = 1; i < first_picks.size(); i++) {
				winner.push_back((*c).get_candidate(i));
			}
			return winner;
		}
		
		cout << "dealing with loser ballots" << endl;


		//deal with loser ballots; add the candidate# tied for last place to the vector
		int lowest = counter[1];
		for(i = 2; i <= (*c).get_count(); i++) {
			if(counter[i] <= lowest) {
				if(counter[i] < lowest) {
					lowest = counter[i];
					losers.clear();
				}
				losers.push_back(i);
			}
		}
		
		cout << "reassigning ballots" << endl;

		//reassign ballots
		for(i = 0; i < losers.size(); i++) { //for all the losing candidates
			int loser = losers[i];
			cout << "loser: " << loser << endl;
			
			for(j = 0; j < first_picks[loser].size(); j++) {	//all the ballots for loser
			    vector<int> tballot;
				tballot = (*c).pop_ballot(first_picks[loser][j]);	//ballot that has losing candidate listed as #1
				tballot.erase(tballot.begin());
				
				cout << "the next choice for this ballot: " << tballot[0] << endl;
				
//				cout << "all the numbers in the losers array" << endl;
//				int tmp;
//				for(tmp = 0; tmp < losers.size(); ++tmp) {
//				    cout << losers[tmp] << endl;
//				}
				
				while(std::find(losers.begin(), losers.end(), tballot[0]) != losers.end()) {
					//erase the first element as long as the first element is a vote for a loser
					tballot.erase(tballot.begin());
				}
				
				cout << "the next choice now: " << tballot[0] << endl;
				//at this point, the first vote is for a potential winning candidate
				//remove ballot # from the loser's first_picks pool and add to the appropriate one
				first_picks[tballot[0]].push_back(first_picks[loser][j]);
				first_picks[loser].erase(first_picks[loser].begin()+j);
			}
			losers.erase(losers.begin());
		}
	}



	return winner;
}

void voting_solve (istream& r, ostream& w) {
	int totalCases, i;
	r >> totalCases;		//number of cases
	cout << totalCases << endl;
	
	for(i = 0; i < totalCases; ++i) {
		Case *vote_case = new Case();
		vector<string> winner;
//		cout << "haven't done anything yet" << endl;
		voting_read(r, vote_case);
		
		cout << "starting to evaluate" << endl;
		winner = voting_eval(w, vote_case);
		cout << "got the winners" << endl;
		voting_print(w, winner);
//		delete vote_case;
	}
}
