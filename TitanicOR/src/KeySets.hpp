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
	//map<int, CandidateSetTree * > keysets;
	CandidateSetTree * old;
	int size;
	int minsup;
	int maxsup;
	int numAtt;
	int numObj;
	int numberCandidates; // Tracing the number of generated candidates (even those pruned)
	bool show;
public:
	KeySets();
	virtual ~KeySets();
	bool generate_candidates(int length);
	bool generate_candidates_one(Database * db);
	bool generate_candidates_two();
	friend ostream& operator<< (ostream& out, KeySets& ks);
	bool should_be_pruned(Generator * gen, CandidateSetTree * cst, int length);
	void set_min_support(int minsup) { this->minsup = minsup; }
	void set_max_support(int maxsup) { this->maxsup = maxsup; }
	void set_show(bool show) {this->show = show;}
};

#endif /* KEYSETS_H_ */
