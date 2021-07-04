/*
 * FileStorage.h
 *
 *  Created on: 27-Jun-2021
 *      Author: sudarshan
 */

#ifndef DATABASE_FILESTORAGE_H_
#define DATABASE_FILESTORAGE_H_

#include <stdio.h>
#include <string.h>
#include "../include/olctypes.h"
#include "../templates/iolc.h"

#define FILE_NAME "/tmp/OLC_Details.txt"

using namespace olc;

namespace olc{

/*
 *
 */
class FileStorage {
public:
	FileStorage();
	virtual ~FileStorage();
	FileStorage(const FileStorage &other)=delete;
	FileStorage(FileStorage &&other)=delete;
	FileStorage& operator=(const FileStorage &other)=delete;
	FileStorage& operator=(FileStorage &&other)=delete;

	void AddCourseToFile(course_details_t Details);

private:
	FILE* mFileStoragePtr;
};

}

#endif /* DATABASE_FILESTORAGE_H_ */
