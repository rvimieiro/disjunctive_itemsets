/*
 * KeySets.cpp
 *
 *  Created on: 25/08/2009
 *      Author: rv695
 */

#include "KeySets.hpp"
#include <algorithm>
#include <iostream>
//extern "C++" int minsup;

using namespace std;

KeySets::KeySets() {
	size = 0;
	this->minsup = 0;
	this->numberCandidates = 0;
}

KeySets::~KeySets() {
	// TODO Auto-generated destructor stub
}

bool KeySets::generate_candidates_one(Database* db){
	CandidateSetTree * cst = new CandidateSetTree();

	register int i;
	const register int size = db->numAtt;
	for(i = 0; i < size; i++){
		int sup = db->items[i].count();
		this->numberCandidates++;
		if(sup >= minsup && sup <= maxsup){
			Generator * gen = new Generator(i,db->numAtt,db->numObj);
			gen->set_weight(sup);
			gen->set_transactions(db->items[i]);
			cst->insert(gen);
			this->size++;
		}
	}
//	cin >> i;
	keysets[1] = cst;
//	cout << *(keysets[1]) << "Hi " << endl <<  *cst;
	return !cst->empty();
}

bool KeySets::generate_candidates_two(Database* db){
	CandidateSetTree * cst = keysets[1];
	CandidateSetTree * newcst = new CandidateSetTree();
	keysets[2] = newcst;
	map<int, CandidateNode>::iterator it = cst->root.children.begin();
	map<int, CandidateNode>::iterator end = cst->root.children.end();
	for(; it != end; it++ ){
		map<int, CandidateNode>::iterator tmp = end;
		for(--tmp; tmp != it; tmp--){
			Generator * gen = new Generator(it->first,db->numAtt,db->numObj);
			gen->insert(tmp->first);
			gen->union_trans(it->second.gen->transactions,tmp->second.gen->transactions);
			this->numberCandidates++;
			int pw1 = it->second.gen->weight;
			int pw2 = tmp->second.gen->weight;
			gen->set_parent_weight((pw1>pw2?pw1:pw2));
			if(gen->get_weight() <= maxsup && gen->get_weight() != gen->get_parent_weight()) {
				newcst->insert(gen);
				this->size++;
			}
		}
	}
	return !newcst->empty();
}

bool KeySets::generate_candidates(int length,Database * db){
	if(length < 3) return true;
//	vector < Generator * > * candys = new vector < Generator * >();
	CandidateSetTree * cst = keysets[length-1];
	CandidateSetTree * newcst = new CandidateSetTree();
	keysets[length] = newcst;
	vector < CandidateNode * > stack;
	stack.push_back(&(cst->root));
	while(!stack.empty()){
		CandidateNode * node = stack.back();
		stack.pop_back();
		if(node){
			map<int, CandidateNode>::iterator it = node->children.begin();
			map<int, CandidateNode>::iterator end = node->children.end();
			if(node->level < length - 2){//We should join the children of the root in the level k-2 to construct the k+1 candidates
				for(; it != end; it++){
					stack.push_back(&(it->second));
				}
			} else{
				for(; it != end; it++ ){
					map<int, CandidateNode>::iterator tmp = end;
					for(--tmp; tmp != it; tmp--){

//						cerr << *(it->second.gen);
//						cerr << *(tmp->second.gen);

						Generator * gen = new Generator(db->numAtt,db->numObj);
						this->numberCandidates++;
						vector<int> begin(length);
						set_union(it->second.gen->begin(),it->second.gen->end(),
								tmp->second.gen->begin(),tmp->second.gen->end(),begin.begin());
						gen->items.insert(begin.begin(),begin.end());
						gen->union_trans(it->second.gen->transactions,tmp->second.gen->transactions);
//						int pw1 = it->second.gen->weight;
//						int pw2 = tmp->second.gen->weight;
//						gen->set_parent_weight((pw1>pw2?pw1:pw2));
						if(!should_be_pruned(gen,cst,length)) {
//							candys->push_back(gen);
							newcst->insert(gen);
							this->size++;
//							cerr << "Included ==>> " << *gen;
						}
//						else cerr << "Pruned ==>> " << *gen;
					}
				}
			}
		}
	}
	return !newcst->empty();
}


bool KeySets:: should_be_pruned(Generator * gen, CandidateSetTree * cst, int length){
	int * key = new int[length -1];
	for(set<int>::const_iterator it = gen->items.begin(); it != gen->items.end(); it++){
		remove_copy(gen->begin(),gen->end(),key,*it);

//		cerr << "Key [ ";
//		for(int i = 0; i < length-1; i++) cerr << key[i] << " ";
//		cerr << "]" << endl;

		Generator * tmp = cst->find(key,length-1);
		if(tmp != NULL){
			gen->set_parent_weight(max(gen->parent_weight,tmp->weight));
		} else{
			delete[] key;
//			cerr << " Didn't find!" << endl;
			return true;
		}
	}
	delete[] key;
	return ((gen->weight > maxsup) || (gen->parent_weight==gen->weight));
}

ostream& operator<< (ostream& out, KeySets& ks){
	for(map<int, CandidateSetTree * >::iterator it = ks.keysets.begin(); it != ks.keysets.end(); it++)
		out << *(it->second);
	out << "# of OR-CLAUSES = " << ks.size << endl;
	out << "# of candidates = " << ks.numberCandidates << endl;
	return out;
}

//int main(int argc, char ** argv){
//	string s(argv[1]);
//	Database db(s);
//	db.load();
//	KeySets ks;
//	ks.generate_candidates_one(&db);
////	cout << ks;
//	ks.generate_candidates_two(&db);
//	int i = 3;
//	while(ks.generate_candidates(i++,&db));
////		cerr << "OLLLLLLLLLLAAAAAAAAAAAAAAA >>>>>>>>>>>> " << i++ << endl;
//
//	cout << ks;
//}
