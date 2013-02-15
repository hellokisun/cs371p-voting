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
		string get_candidate(int);
		vector<int> get_ballot(int);
		int get_ballot_count();
		~Case();
};

void print_vector (vector<int>& v);

void print_double_vector (vector<vector<int> >& v);

bool voting_read(istream& r, Case c);

void voting_print(ostream& w, vector<string> winner);

vector<string> voting_eval(ostream& w, Case c);

void voting_solve (istream& r, ostream& w);

#endif
