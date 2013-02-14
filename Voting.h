#ifndef Voting_h
#define Voting_h

#include <string>
#include <vector>


using namespace std;
class Case {
    private:
	    int numCandidates;
	    vector<string > candidates;	// vector of candidate names
	    vector<vector<int> > ballots;		// vector of all the ballots

	public:
		Case();
		int get_count();
		void set_count(int);
		void add_candidate(std::string);
		void add_ballot(std::vector<int>);
		vector<int> pop_ballot(int position);
		string get_candidate(int);
		vector<int> get_ballot(int);
		int get_ballot_count();
		~Case();
};
//Case::Case();
//int Case::get_count();
//void Case::set_count(int count);
//void Case::add_candidate(std::string candidate);
//void Case::add_ballot(std::vector<int> ballot);
//string Case::get_candidate(int position);
//vector<int> Case::get_ballot(int position);
//int Case::get_ballot_count();
//Case::~Case();
bool voting_read(istream& r, Case c);

void voting_print(ostream& w, vector<string> winner);

vector<string> voting_eval(ostream& w, Case c);

void voting_solve (istream& r, ostream& w);

#endif
