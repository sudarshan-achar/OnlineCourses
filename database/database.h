/*
 * database.h
 *
 *  Created on: 03-Jul-2020
 *      Author: sudarshan
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <string.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include <memory>
#include <iostream>

#include "idatabaseclient.h"
#include "../templates/iolc.h"
#include "../templates/olccourse.h"
#include "../templates/olcuser.h"
#include "../templates/olcvendor.h"
#include "../utils/idgenerator.h"


using namespace olc;

namespace olc{

/*
 *
 */
class DataBase {
public:
	DataBase();
	virtual ~DataBase();
	DataBase(const DataBase &other)=delete;
	DataBase(DataBase &&other)=delete;
	DataBase& operator=(const DataBase &other)=delete;
	DataBase& operator=(DataBase &&other)=delete;

	int CreateTables();
	int AddCourseData(IOlc<course_details_t> *course);
	int AddUserData(IOlc<user_details_t> *user);
	int AddVendorData(IOlc<vendor_details_t> *vendor);
	int AddLinkedId(u_int_t linkerId, u_int_t linkedId);
	int RemoveLink(u_int_t linkerId, u_int_t linkedId);

	int RestoreFromeSqlDb(IDataBaseClient* db_client);

private :
	void restoreUsers(IDataBaseClient* db_client);
	void restoreCourses(IDataBaseClient* db_client);
	void restoreVendors(IDataBaseClient* db_client);
	void restoreSubscribers(IDataBaseClient* db_client);

private:
	sqlite3 *m_dbPtr;
    int m_error;
};

}/* namespace olc */

#endif /* DATABASE_H_ */
