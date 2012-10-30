/*
 * Titanic.cpp
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#include "Titanic.h"
#include <string>
#include <cstdio>
#include "Debug.h"
#include <string.h>

using namespace std;
int minsup = 0;
int maxsup = 1000000;



void show_usage(void);

double get_memory_usage() {
	FILE* pf = fopen("/proc/self/statm", "r");
	if (pf) {
		unsigned size;
		fscanf(pf, "%u", &size);
		fclose(pf);
		return size;
	}
	return 0;
}

Titanic::Titanic(string filename) {
	db = new Database(filename);
}

Titanic::~Titanic() {
	delete db;
}

KeySets& Titanic::titanic(int minsup, int maxitem, bool show) {
	db->load();
	ks.set_min_support(minsup);
	ks.set_max_support(maxsup);
	ks.set_show(show);
	ks.generate_candidates_one(db);

	delete db;
	db = NULL;
    if(2<=maxitem) ks.generate_candidates_two();
	int i = 3;
	while(i<= maxitem && ks.generate_candidates(i++));

	return this->ks;
}

void show_usage(){
	cerr << "Usage: Titanic <filename> <minsup(int)> <maxitem(int)> <maxsup(int)> [-n(do not print minimal generators)] [-o(show generators' objects; incompatible with -n)]" << endl;
}

int main(int argc, char ** argv){
	bool show = true;
//	Generator::set_show_trans(false);
	if (argc < 5){
		show_usage();
		exit(0);
	}
	string s(argv[1]);
	Titanic t(s);
	int max_item = 1000000;

#if DEBUG_MODE
	cout << "Memory usage after loading data and generating first candidates (KB): " << get_memory_usage() << endl;
#endif

	minsup = atoi(argv[2]);
	max_item = atoi(argv[3]);
	maxsup = atoi(argv[4]);

	if(argc == 6){
		if(strstr(argv[5],"-n")) show=false;
		else if(strstr(argv[5],"-o")) Generator::set_show_trans(true);
	}

	if(argc == 7){
		if(strstr(argv[5],"-n") || strstr(argv[6], "-n")) show=false;
		if(strstr(argv[5],"-o") || strstr(argv[6], "-o")) Generator::set_show_trans(true);
	}

	cout << t.titanic(minsup,max_item,show) << endl;
	return 0;
}

