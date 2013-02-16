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
		int get_count();
		void set_count(int);
		void add_candidate(std::string);
		void add_ballot(std::vector<int>);
		string get_candidate(int);
		vector<int> get_ballot(int);
		int get_ballot_count();
		~Case();
};

// ------------
// print_vector
// ------------
/**
 * prints a vector to cout
 * @param v vector to be printed
 */
void print_vector (vector<int>& v);


// -------------------
// print_double_vector
// -------------------
/**
 * prints a 2D vector to cout
 * @param v 2D vector to be printed
 */
void print_double_vector (vector<vector<int> >& v);


// -----------
// voting_read
// -----------
/**
 * reads the candidate names and ballots and stores them in Case object
 * for one case
 * @param r a std::istream
 * @param c a Case object to store the names and ballots
 * @return boolean value for debug
 */
bool voting_read(istream& r, Case *c);


// ------------
// voting_print
// ------------
/**
 * prints the winners
 * @param w a std::ostream
 * @param winner vector containing the names of the winning candidates
 */
void voting_print(ostream& w, vector<string> winner);


// -----------
// voting_eval
// -----------
/**
 * evaluates the winning candidate for one case
 * @param w a std::ostream (mainly for debug)
 * @param c a Case object to retrieve candidate names and ballots from
 * @return a vector containing the names of the winning candidates
 */
vector<string> voting_eval(ostream& w, Case *c);


// ------------
// voting_solve
// ------------
/**
 * calculates winning candidates for all the cases
 * @param r a std::istream (cin)
 * @param w a std::ostream (cout)
 */
void voting_solve (istream& r, ostream& w);

#endif
