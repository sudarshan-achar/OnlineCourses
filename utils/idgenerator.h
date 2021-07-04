/*
 * idgenerator.h
 *
 *  Created on: 27-Jun-2021
 *      Author: sudarshan
 */

#ifndef DATABASE_IDGENERATOR_H_
#define DATABASE_IDGENERATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 *
 */
class IDGenerator {
public:
	virtual ~IDGenerator();
	IDGenerator(const IDGenerator &other) = delete;
	IDGenerator(IDGenerator &&other) = delete;
	IDGenerator& operator=(const IDGenerator &other) = delete;
	IDGenerator& operator=(IDGenerator &&other) = delete;

	static unsigned int GetID();
private :
	IDGenerator();

public:
	static unsigned int id_increment;;
};

#endif /* DATABASE_IDGENERATOR_H_ */
