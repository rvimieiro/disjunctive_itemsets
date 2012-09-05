/*
 * CandidateSetTree.cpp
 *
 *  Created on: 24/08/2009
 *      Author: rv695
 */

#include "CandidateSetTree.hpp"


//CandidateSetTree::CandidateSetTree() {
//	// TODO Auto-generated constructor stub
//
//}
//
//CandidateSetTree::~CandidateSetTree() {
//	// TODO Auto-generated destructor stub
//}

void CandidateSetTree:: insert (Generator * gen){
	root.insert(gen,gen->begin(),0);
	__empty = false;
}

Generator * CandidateSetTree:: find(int * key, int length){
	vector< CandidateNode * > v;
	v.push_back(&root);
	register int i = 0;
	while(!v.empty()){
		CandidateNode * node = v.back();
		v.pop_back();
		if(i == length) return node->gen;
		map<int, CandidateNode>::iterator it = node->children.find(key[i++]);
		if(it != node->children.end())
			v.push_back(&(it->second));
	}
	return NULL;
}

void CandidateNode:: insert (Generator * gen, set<int>::iterator index, int level){
	this->level = level;
	if(index == gen->end()){
		this->level = level;
		this->gen = gen;
		return;
	}
	int aux = *index;
	this->children[aux].insert(gen,++index,level+1);
}

ostream& operator<< (ostream& out, CandidateSetTree& cst){
	out << cst.root;
	return out;
}

ostream& operator<< (ostream& out, CandidateNode& cn){
	if(cn.gen) out << *(cn.gen);
	else
		for(map<int,CandidateNode >::iterator it = cn.children.begin(); it != cn.children.end(); it++)
			out << it->second;

	return out;
}

//int main (){
//	CandidateSetTree cst;
//	Generator gen;
//	gen.insert(5);
//	gen.insert(4);
////	gen.insert(3);
//
//	Generator gen2;
////	gen2.insert(5);
//	gen2.insert(4);
//	gen2.insert(3);
//
//	cst.insert(&gen2);
//	cst.insert(&gen);
//
//	int key[] = {3,4};
//	cout << *cst.find(key,2);
//	return 0;
//}
