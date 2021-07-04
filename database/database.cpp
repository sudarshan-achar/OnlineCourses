/*
 * DataBase.cpp
 *
 *  Created on: 03-Jul-2020
 *      Author: sudarshan
 */

#include "database.h"

#define __METHOD_NAME__ std::string(std::string("DataBase::") + __func__ + "(): ")
#define LOG_PRINT(...) logInfo(__METHOD_NAME__,__VA_ARGS__)

using namespace olc;

namespace olc{

DataBase::DataBase() :m_dbPtr(nullptr),m_error(0){
	LOG_PRINT("");
	m_error = sqlite3_open("/tmp/olc_database.db", &m_dbPtr);
	if(m_error) {
		LOG_PRINT("Can't open database:");
	} else {
		LOG_PRINT("Opened database successfully");
	}
}

DataBase::~DataBase() {
	sqlite3_close(m_dbPtr);
	m_dbPtr = nullptr;
	LOG_PRINT("Closed database successfully");
}

int DataBase::CreateTables() {
	LOG_PRINT("");
	if(m_dbPtr){
		std::string query = "CREATE TABLE IF NOT EXISTS CoursesList("
				"CourseID INT    PRIMARY KEY    NOT NULL, "
				"CourseName TEXT    NOT NULL, "
				"AuthorName TEXT    NOT NULL, "
				"InstructorName  TEXT    NOT NULL, "
				"Duration  INT    NOT NULL, "
				"Price  INT    NOT NULL, "
				"CourseRating INT    NOT NULL);";

		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		if (m_error != SQLITE_OK) {
			LOG_PRINT("Error in Creating Table CoursesList ");
			sqlite3_free(NULL);
		}else{
			LOG_PRINT("CoursesList Table created Successfully");
		}
		query.clear();

		query = "CREATE TABLE IF NOT EXISTS UsersList("
				"UserId INT    PRIMARY KEY    NOT NULL, "
				"UserName TEXT    NOT NULL, "
				"FullName TEXT    NOT NULL, "
				"DateOfBirth INT    NOT NULL, "
				"Domain TEXT    NOT NULL);";

		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		if (m_error != SQLITE_OK) {
			LOG_PRINT("Error while Creating UsersList Table");
			sqlite3_free(NULL);
		}else{
			LOG_PRINT("UsersList Table created Successfully");
		}
		query.clear();

		query = "CREATE TABLE IF NOT EXISTS VendorsList("
				"VendorId INT    PRIMARY KEY    NOT NULL, "
				"VendorName TEXT    NOT NULL, "
				"FullName TEXT    NOT NULL, "
				"DateOfBirth INT    NOT NULL, "
				"Domain TEXT    NOT NULL);";

		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		if (m_error != SQLITE_OK) {
			LOG_PRINT("Error while Creating VendorsList Table");
			sqlite3_free(NULL);
		}else{
			LOG_PRINT("VendorsList Table created Successfully");
		}
		query.clear();

		query = "CREATE TABLE IF NOT EXISTS LinkedIDsList("
				"UniqueLinkID INT    PRIMARY KEY    NOT NULL, "
				"LinkerID INT    NOT NULL, "
				"LinkedID INT    NOT NULL);";

		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		if (m_error != SQLITE_OK) {
			LOG_PRINT("LinkedIDsList Error Create Table");
			sqlite3_free(NULL);
		}else{
			LOG_PRINT("LinkedIDsList Table created Successfully");
		}
	}else{
		LOG_PRINT("Unable to create tables as dbptr is null");
	}
	return m_error;
}

int DataBase::AddCourseData(IOlc<course_details_t> *course) {
	LOG_PRINT("");
	if(NULL != course && (nullptr != m_dbPtr)){
		LOG_PRINT("course : ",course->GetId());
		course_details_t details = course->GetData();

		std::string query = "INSERT INTO CoursesList VALUES ";
		query.append("('");
		query += std::to_string(details.courseId);
		query.append("','");
		query.append(details.courseName);
		query.append("','");
		query.append(details.authorName);
		query.append("','");
		query.append(details.instructorName);
		query.append("','");
		query += std::to_string(details.duration);
		query.append("','");
		query += std::to_string(details.price);
		query.append("','");
		query += std::to_string(details.courseRating);
		query.append("');");
		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		query.clear();
		generic_list_t* usersList = course->GetList();
		if(nullptr != usersList){
			for(auto element : *usersList){
				query = "INSERT INTO LinkedIDsList VALUES ";
				query.append("('");
				query += std::to_string(IDGenerator::GetID());
				query.append("','");
				query += std::to_string(details.courseId);
				query.append("','");
				query += std::to_string(element);
				query.append("');");
				m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);
				query.clear();
			}
		}else{
			fprintf(stdout, "usersidList is null \n");
		}
	}
	return 0;
}

int DataBase::AddUserData(IOlc<user_details_t> *user) {
	LOG_PRINT("");
	if(nullptr != user && (nullptr != m_dbPtr)){
		LOG_PRINT("user : ",user->GetId());

		user_details_t details = user->GetData();

		std::string query = "INSERT INTO UsersList VALUES ";
		query.append("('");
		query += std::to_string(details.userId);
		query.append("','");
		query.append(details.userName);
		query.append("','");
		query.append(details.fullName);
		query.append("','");
		query.append(details.dateOfBirth);
		query.append("','");
		query.append(details.domain);
		query.append("');");
		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		query.clear();
		generic_list_t* coursesList = user->GetList();
		if(nullptr != coursesList){
			for(auto element : *coursesList){
				query = "INSERT INTO LinkedIDsList VALUES ";
				query.append("('");
				query += std::to_string(IDGenerator::GetID());
				query.append("','");
				query += std::to_string(details.userId);
				query.append("','");
				query += std::to_string(element);
				query.append("');");
				m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);
				query.clear();
			}
		}else{
			fprintf(stdout, "coursesidList is null \n");
		}
	}
	return 0;
}

int DataBase::AddVendorData(IOlc<vendor_details_t> *vendor) {
	if(nullptr != vendor && (nullptr != m_dbPtr)){
		LOG_PRINT("vendor : ",vendor->GetId());

		vendor_details_t details = vendor->GetData();

		std::string query = "INSERT INTO UsersList VALUES ";
		query.append("('");
		query += std::to_string(details.vendorId);
		query.append("','");
		query.append(details.vendorName);
		query.append("','");
		query.append(details.fullName);
		query.append("','");
		query.append(details.dateOfBirth);
		query.append("','");
		query.append(details.domain);
		query.append("');");
		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);

		query.clear();
		generic_list_t* coursesList = vendor->GetList();
		if(nullptr != coursesList){
			for(auto element : *coursesList){
				query = "INSERT INTO LinkedIDsList VALUES ";
				query.append("('");
				query += std::to_string(IDGenerator::GetID());
				query.append("','");
				query += std::to_string(details.vendorId);
				query.append("','");
				query += std::to_string(element);
				query.append("');");
				m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);
				query.clear();
			}
		}else{
			fprintf(stdout, "coursesidList is null \n");
		}
	}
	return 0;
}

int DataBase::AddLinkedId(u_int_t linkerId, u_int_t linkedId) {
	LOG_PRINT("linkerId :",linkerId,"linkedId :",linkedId);
	if((0 != linkerId) && (0 != linkedId)){
		std::string  query = "INSERT INTO LinkedIDsList VALUES ";
		query.append("('");
		query += std::to_string(IDGenerator::GetID());
		query.append("','");
		query += std::to_string(linkerId);
		query.append("','");
		query += std::to_string(linkedId);
		query.append("');");
		m_error = sqlite3_exec(m_dbPtr, query.c_str(), NULL, 0, NULL);
		LOG_PRINT("DB write is done");
	}
	return 0;
}

int DataBase::RemoveLink(u_int_t linkerId, u_int_t linkedId) {
	return 0;
}

int DataBase::RestoreFromeSqlDb(IDataBaseClient *db_client) {
	if(db_client){
		LOG_PRINT("");
		restoreCourses(db_client);
		restoreUsers(db_client);
		restoreVendors(db_client);
		restoreSubscribers(db_client);
	}else{}//db client is null
	return 0;
}

void DataBase::restoreUsers(IDataBaseClient *db_client) {
	if(m_dbPtr){
		std::string query = "SELECT * from UsersList";
		auto rc = sqlite3_exec(m_dbPtr, query.c_str(), [](void* data, int argc, char** argv, char** azColName){
			user_details_t user;
			user.userId=(unsigned int)atoi(argv[0]);
			user.userName=std::string(argv[1]);
			user.fullName=std::string(argv[2]);
			user.dateOfBirth=std::string(argv[3]);
			user.domain=std::string(argv[4]);

			auto db_client_ptr = (IDataBaseClient *)data;
			db_client_ptr->AddUserToMap(std::move(user),false);
			return 0;

		}, (void *)db_client, NULL);
	}//m_dbPtr is null
}

void DataBase::restoreCourses(IDataBaseClient *db_client) {
	if(m_dbPtr){
		std::string query = "SELECT * from CoursesList";
		auto rc = sqlite3_exec(m_dbPtr, query.c_str(), [](void* data, int argc, char** argv, char** azColName){
			course_details_t course_fromDB;
			course_fromDB.courseId=(unsigned int)atoi(argv[0]);
			course_fromDB.courseName=std::string(argv[1]);
			course_fromDB.authorName=std::string(argv[2]);
			course_fromDB.instructorName=std::string(argv[3]);
			course_fromDB.duration=(unsigned int)atoi(argv[4]);
			course_fromDB.price=(unsigned int)atoi(argv[5]);
			course_fromDB.courseRating=(unsigned int)atoi(argv[6]);

			auto db_client_ptr = (IDataBaseClient *)data;
			db_client_ptr->AddCourseToMap(std::move(course_fromDB),false);
			return 0;

		}, (void *)db_client, NULL);
	}//m_dbPtr is null
}

void DataBase::restoreVendors(IDataBaseClient *db_client) {
	//	if(m_dbPtr){
	//			std::string query = "SELECT * from UsersList";
	//			auto rc = sqlite3_exec(m_dbPtr, query.c_str(), [](void* data, int argc, char** argv, char** azColName){
	//				vendor_details_t vendor;
	//				vendor.vendorId=(unsigned int)atoi(argv[0]);
	//				vendor.vendorName=std::string(argv[1]);
	//				vendor.fullName=std::string(argv[2]);
	//				vendor.dateOfBirth=std::string(argv[3]);
	//				vendor.domain=std::string(argv[4]);
	//
	//				auto db_client_ptr = (IDataBaseClient *)data;
	//				//db_client_ptr->A(std::move(vendor),false);
	//				return 0;
	//
	//			}, (void *)db_client, NULL);
	//		}//m_dbPtr is null
}

void DataBase::restoreSubscribers(IDataBaseClient *db_client) {
	if(m_dbPtr){
		std::string query = "SELECT * from LinkedIDsList";
		auto rc = sqlite3_exec(m_dbPtr, query.c_str(), [](void* data, int argc, char** argv, char** azColName){
			auto linkerId =(unsigned int)atoi(argv[1]);
			auto linkedId =(unsigned int)atoi(argv[2]);
			auto db_client_ptr = (IDataBaseClient *)data;
			db_client_ptr->SubscribeCourse(std::move(linkerId),std::move(linkedId),false);
			return 0;
		}, (void *)db_client, NULL);
	}//m_dbPtr is null
}

}/* namespace olc */
