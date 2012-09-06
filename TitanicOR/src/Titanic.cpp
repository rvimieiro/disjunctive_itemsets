/*
 * Titanic.cpp
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#include "Titanic.h"
#include <string>

using namespace std;
int minsup = 0;
int maxsup = 1000000;
Titanic::Titanic(string filename) {
	db = new Database(filename);
}

Titanic::~Titanic() {
	delete db;
}

KeySets& Titanic::titanic(int minsup, int maxitem) {
	db->load();
	ks.set_min_support(minsup);
	ks.set_max_support(maxsup);
	ks.generate_candidates_one(db);
        if(2<=maxitem) ks.generate_candidates_two(db);
	int i = 3;
	while(i<= maxitem && ks.generate_candidates(i++,db));
	return this->ks;
}

int main(int argc, char ** argv){
	//minsup = atoi(argv[2]);
	int max_item = 1000000;
	if(argc>=4){
		minsup = atoi(argv[2]);
		max_item = atoi(argv[3]);
		maxsup = atoi(argv[4]);
	} else{
		cerr << "Usage: " << argv[0] << " <filename> <minsup(int)> <maxitem(int)> <maxsup(int)>" << endl;
		exit(0);
	}
	string s(argv[1]);
	Titanic t(s);
	cout << t.titanic(minsup,max_item);
	return 0;
}

