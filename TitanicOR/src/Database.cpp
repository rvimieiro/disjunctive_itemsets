/*
 * Database.cpp
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#include "Database.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Database::Database(string filename) {
	this->filename = filename;
	numAtt = -1;
	numObj = -1;
}

Database::~Database() {
	items.clear();
}

void Database::load() {
	ifstream ifs(filename.c_str());

	if(ifs.fail()) { cerr << "Error while opening " << filename << endl; exit(-1); }

	ifs >> numAtt;
	ifs >> numObj;
	items.resize(numAtt);
	int i;
	for(i = 0; i < numObj; i++){
		int size = 0;
		int att = -1;
		ifs >> size;
		for(int j = 0; j < size; j++){
			ifs >> att;
			assert(att < numAtt);
			if(items[att].size() == 0) items[att].resize(numObj);
			items[att].set(i,1);
		}
	}
	ifs.close();
}

ostream &operator<< (ostream& out, Database& db){
	out << "[ " << endl;
	for(int i = 0; i < db.numAtt; i++){
		out << "[ " << i << " ] = ";
		print(db.items[i],out);
	}
	out << " ]" << endl;
	return out;
}

void print(const dynamic_bitset<>& items, ostream& out) {
	out << "{ ";
	for(dynamic_bitset<>::size_type i = items.find_first(); i != items.npos; i = items.find_next(i)){
		out << i << " ";
	}
	out << "} -- " << items.count() << endl;
}

//int main(int argc, char ** argv)
//{
//	Database db(argv[1]);
//	db.load();
//	cout << db;
//	return 0;
//}
