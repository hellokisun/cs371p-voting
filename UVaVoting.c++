#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Case {
	int numCandidates;
	vector<std::string > candidates;	// vector of candidate names
	vector<std::vector<int> > ballots;		// vector of all the ballots

	public:
		Case();
		int get_count();
		void set_count(int);
		void add_candidate(std::string);
		void add_ballot(std::vector<int>);
		string get_candidate(int);
		vector<int> get_ballot(int);
		int get_ballot_count();
		~Case();
};
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
	
	//read candidate names
	int i;
	string name;
	getline(r,name);	//skip blank line
	
	
	for(i = 0; i < (*c).get_count(); i++) {
		getline(r,name);
		(*c).add_candidate(name);
	}
	//read ballots
	while(getline(r,name)) {
		//if line is empty, reading for the case is done. return.
		if(name.empty()) {
			break;
		}

		istringstream stream(name);
		vector<int> ballot;

		//read one ballot
		int value;
		for(i = 0; i < count; ++i) {
		    stream >> value;
		    ballot.push_back(value);		
		}
		//while(!stream.eof() && stream >> value) {
		//	if(value == '\n') {
		//		break;
		//	}
		//	ballot.push_back(value);
		//}
		//cout << "BALLOT READ. BALLOT SIZE: " << ballot.size() << "; RESULTS: ";
		//print_vector(ballot);
		(*c).add_ballot(ballot);
	}
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
	unsigned int i, j;
	
	for(i = 0; i <= (*c).get_count(); i++) {
	    vector<int> empty;
		first_picks.push_back(empty);
	}


	//go through all the ballots and check the first choices
	for(i = 0; i < (*c).get_ballot_count(); i++) {
		vector<int> ballot = (*c).get_ballot(i);
		++counter[ballot[0]];
		//add ballot to the sorted vector
		first_picks[ballot[0]].push_back(i); //ballot number goes from 0 to n-1
	}

	while(true) {
	    //check for winner
		for(i = 1; i < (int)first_picks.size(); i++) {
			if((*c).get_ballot_count() < 2*(int)first_picks[i].size()) {
				//winner
				winner.push_back((*c).get_candidate(i-1));
				return winner;
			}
		}
		
		//check for ties
		unsigned int size = first_picks[1].size();
		bool tie = true;
		for(i = 1; i < first_picks.size(); i++) {
			if(first_picks[i].size() != size && first_picks[i].size() != 0)
				tie = false;
		}

		if (tie == true) {
			for(i = 1; i < first_picks.size(); i++) {
				winner.push_back((*c).get_candidate(i-1));
			}
			return winner;
		}
		

		//deal with loser ballots; add the candidate# tied for last place to the vector
		//PROBLEMS HERE!!
//		int lowest = first_picks[1].size();
        int lowest = 21;
		int tmps;
		for(i = 1; i <= (*c).get_count(); i++) {
//		    tmps = first_picks[i].size();
			if(counter[i] <= lowest && counter[i] != -1) {
				if(counter[i] < lowest) {
					lowest = counter[i];
					losers.clear();
				}
				losers.push_back(i);
			}
		}
		
		for(i = 0; i < losers.size(); ++i) {
			counter[losers[i]] = -1;
		}
		
		//reassign ballots
		for(i = 0; i < losers.size(); ++i) { //for all the losing candidates
			int loser = losers[i];
			int losersize = first_picks[loser].size();
			
			for(j = 0; j < losersize; ++j) {	//all the ballots for loser
			    vector<int> tballot;
			    int b_num = first_picks[loser][0];
				tballot = (*c).get_ballot(b_num);	//ballot that has losing candidate listed as #1
				tballot.erase(tballot.begin());

				int x, z;
				int bsize = tballot.size();
				bool f = true;
				
			    for(x = 0; x < bsize; ++x) {
			        if(first_picks[tballot[0]].size() == 0) {
			            tballot.erase(tballot.begin());
			        }
			        else if(tballot[0] == loser || find(losers.begin(), losers.end(), tballot[0]) != losers.end()) {
			            tballot.erase(tballot.begin());
			        }
			        else {
			            break;
			        }
				    //while(first_picks[tballot[0]].size() == 0) {
					//    tballot.erase(tballot.begin());
				    //}
				}
				//at this point, the first vote is for a potential winning candidate
				//remove ballot # from the loser's first_picks pool and add to the appropriate one
				++counter[tballot[0]];
				first_picks[tballot[0]].push_back(b_num);
			    first_picks[loser].erase(first_picks[loser].begin());     //segfaults here... why?
			}
		}
        losers.clear();
	}



	return winner;
}

void voting_solve (istream& r, ostream& w) {
	int totalCases, i;
	r >> totalCases;		//number of cases
//	cout << totalCases << endl;
	
	for(i = 0; i < totalCases; ++i) {
		Case *vote_case = new Case();
		vector<string> winner;
//		cout << "haven't done anything yet" << endl;
		voting_read(r, vote_case);
//		cout << "starting to evaluate" << endl;
		winner = voting_eval(w, vote_case);
//		cout << "got the winners" << endl;
		voting_print(w, winner);
		delete vote_case;
	}
}



int main () {
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    voting_solve(cin, cout);
    return 0;
}
