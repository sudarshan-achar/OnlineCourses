/*
 * IDGenerator.cpp
 *
 *  Created on: 27-Jun-2021
 *      Author: sudarshan
 */

#include "idgenerator.h"



unsigned int IDGenerator::id_increment = 0;

unsigned int IDGenerator::GetID() {
	id_increment++;
	srand(time(0));
	return (unsigned int)(id_increment+10000+rand());
}

IDGenerator::IDGenerator() {}

IDGenerator::~IDGenerator() {}


