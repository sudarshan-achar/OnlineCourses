/*
 * FileStorage.cpp
 *
 *  Created on: 27-Jun-2021
 *      Author: sudarshan
 */

#include "filestorage.h"

#define __METHOD_NAME__ std::string(std::string("DataBase::") + __func__ + "(): ")
#define LOG_PRINT(...) logInfo(__METHOD_NAME__,__VA_ARGS__)

using namespace olc;

namespace olc{

FileStorage::FileStorage() {
	LOG_PRINT("");
	mFileStoragePtr = fopen(FILE_NAME, "w+"); //open the file with filename & assign that file to mFileStoragePtr.
}

FileStorage::~FileStorage() {
	LOG_PRINT("");
	fclose(mFileStoragePtr);
}

void FileStorage::AddCourseToFile(course_details_t data) {
	mFileStoragePtr = fopen(FILE_NAME, "a+");
	if(mFileStoragePtr){
		LOG_PRINT("");
		fprintf(mFileStoragePtr, "%s, [%s], %s, %s, %s, %s .\n",data.courseName.c_str(),std::to_string(data.courseId).c_str(),
				data.authorName.c_str(),std::to_string(data.price).c_str(),std::to_string(data.duration).c_str(),
				std::to_string(data.courseRating).c_str());
	}
	fclose(mFileStoragePtr);
}

}
