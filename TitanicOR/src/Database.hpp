/*
 * Database.h
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "boost/dynamic_bitset.hpp"
#include <string>
//#include "KeySets.hpp"

using namespace std;
using namespace boost;

class Database {
	friend class KeySets;
private:
	vector< dynamic_bitset<> > items;
	int numAtt;
	int numObj;
	string filename;
public:
	friend ostream &operator << (ostream &out, Database& db);
	Database(string filename);
	virtual ~Database();
	void load();
};

void print(const dynamic_bitset<>& items, ostream& out);

#endif /* DATABASE_H_ */
