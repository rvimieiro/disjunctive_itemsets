/*
 * Titanic.h
 *
 *  Created on: 21/08/2009
 *      Author: rv695
 */

#ifndef TITANIC_H_
#define TITANIC_H_

#include "KeySets.hpp"
#include "Database.hpp"

class Titanic {
private:
	Database * db;
	KeySets ks;
public:
	Titanic(string filename);
	virtual ~Titanic();
	KeySets& titanic(int minsup, int maxitem);
};


#endif /* TITANIC_H_ */
