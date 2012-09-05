/*
 * Generator.cpp
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#include "Generator.hpp"

Generator::Generator(int item, int sI, int sT) {
	index_to_insert = 0;
	transactions.resize(sT);
	items.insert(item);
	parent_weight = -1;
	weight = -1;
}

Generator::Generator(int sI, int sT) {
	index_to_insert = 0;
	transactions.resize(sT);
	parent_weight = -1;
	weight = -1;
}

Generator::Generator() {
	index_to_insert = 0;
//	items.resize(size_items);
	transactions.resize(size_transactions);
	parent_weight = -1;
	weight = -1;
}

Generator::~Generator() {
	// TODO Auto-generated destructor stub
}

ostream& operator<< (ostream& out, Generator& gen){
	out << "{ ";
	for (set<int>::iterator it=gen.items.begin() ; it != gen.items.end(); it++ ) out << *it << " ";
	out << "} " << gen.weight << " (" << gen.parent_weight << ")"<< endl;

	return out;
}

void Generator :: union_trans(dynamic_bitset<> a, dynamic_bitset<> b){
	dynamic_bitset<>::size_type t = max(a.size(),b.size());
	this->transactions.resize(t);
	a.resize(t);
	b.resize(t);
	this->transactions |= a;
	this->transactions |= b;
	this->weight = this->transactions.count();
}
//int main(){
//	Generator gen;
//	gen.insert(5);
//	gen.insert(4);
//	gen.insert(3);
//	cout << gen;
//
//	return 0;
//}
