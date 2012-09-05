/*
 * KeySets.h
 *
 *  Created on: 25/08/2009
 *      Author: rv695
 */

#ifndef KEYSETS_H_
#define KEYSETS_H_

#include <map>
#include "CandidateSetTree.hpp"
#include "Database.hpp"

class KeySets {
protected:
	map<int, CandidateSetTree * > keysets;
	int size;
	int minsup;
	int maxsup;
	int numberCandidates; // Tracing the number of generated candidates (even those pruned)
public:
	KeySets();
	virtual ~KeySets();
	bool generate_candidates(int length, Database * db);
	bool generate_candidates_one(Database * db);
	bool generate_candidates_two(Database * db);
	friend ostream& operator<< (ostream& out, KeySets& ks);
	bool should_be_pruned(Generator * gen, CandidateSetTree * cst, int length);
	void set_min_support(int minsup) { this->minsup = minsup; }
	void set_max_support(int maxsup) { this->maxsup = maxsup; }
};

#endif /* KEYSETS_H_ */
