/*
 * Generator.h
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <set>
#include <boost/dynamic_bitset.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class Generator {
	friend class KeySets;
private:
	int index_to_insert;
	set<int> items;
	dynamic_bitset<> transactions;
	int weight;
	int parent_weight;
	static const int size_transactions = 5;
	static const int size_items = 5;
	static bool show_trans;
public:
	Generator(int, int, int);
	Generator(int, int);
	Generator();
	virtual ~Generator();
	inline int get_weight() { return weight; }
	inline int get_parent_weight() { return parent_weight; }
	inline void set_weight(int w) { weight = w; }
	inline void set_parent_weight(int pw) { parent_weight = pw; }
	friend ostream& operator<< (ostream& out, Generator& gen);
	inline int length() { return index_to_insert; }
//	inline int item(const int index) { return items[index]; }
	inline void insert(int elem) { items.insert(elem); }
	inline set<int>::iterator begin() { return items.begin(); }
	inline set<int>::iterator end() { return items.end(); }
	inline void set_transactions(dynamic_bitset<>& trans) { this->transactions = trans; }
	void union_trans(dynamic_bitset<> a, dynamic_bitset<> b);
	static void set_show_trans(bool st) {Generator::show_trans = st;}
};

#endif /* GENERATOR_H_ */
