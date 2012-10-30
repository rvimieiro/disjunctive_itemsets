/*
 * CandidateSetTree.h
 *
 *  Created on: 24/08/2009
 *      Author: rv695
 */

#ifndef CANDIDATESETTREE_H_
#define CANDIDATESETTREE_H_

#include "Generator.hpp"
//#include "boost/unordered_map.hpp"
#include <map>

class CandidateSetTree;

class CandidateNode {
	friend class CandidateSetTree;
	friend class KeySets;
private:
	Generator * gen;
	int level;
	map<int, CandidateNode > children;
public:
	friend ostream& operator<< (ostream& out, CandidateNode& cn);
	CandidateNode(){ level = -1; gen = 0x00000000; }
	~CandidateNode(){delete gen; gen = 0x0000000;}
	void insert(Generator *, set<int>::iterator, int level);
};

class CandidateSetTree {
	friend class KeySets;
	CandidateNode root;
	bool __empty;
public:
	friend ostream& operator<< (ostream& out, CandidateSetTree& cst);
	CandidateSetTree(){__empty = true;}
	virtual ~CandidateSetTree(){}
	void insert(Generator * gen);
	Generator * find(int * key, int length);
	inline bool empty(){return __empty;}
};

#endif /* CANDIDATESETTREE_H_ */
