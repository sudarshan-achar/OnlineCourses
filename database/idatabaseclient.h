/*
 * idatabaseClient.h
 *
 *  Created on: 27-Jun-2021
 *      Author: sudarshan
 */

#ifndef DATABASE_TEST_IDATABASECLIENT_H_
#define DATABASE_TEST_IDATABASECLIENT_H_

#include "../include/olctypes.h"
/*
 *
 */
class IDataBaseClient {
public:
	IDataBaseClient();
	virtual ~IDataBaseClient();
	IDataBaseClient(const IDataBaseClient &other)=delete;
	IDataBaseClient(IDataBaseClient &&other)=delete;
	IDataBaseClient& operator=(const IDataBaseClient &other)=delete;
	IDataBaseClient& operator=(IDataBaseClient &&other)=delete;

	/**
	 * @details Function to Add courses to the map
	 * @param course : course_details_t structure
	 * @return error enumeration
	 */
	virtual err_t AddCourseToMap(course_details_t &&course, bool db_write=true)=0;

	/**
	 * @details Function to Add users to the map
	 * @param user : user_details_t structure
	 * @return error enumeration
	 */
	virtual err_t AddUserToMap(user_details_t &&user, bool db_write=true)=0;

	/**
	 * @details Function Remove course from map
	 * @param id : Course Id
	 * @return error enumeration
	 */
	virtual err_t RemoveCourseFromMap(course_id &&id)=0;

	/**
	 * @details Function Remove user from map
	 * @param id : User Id
	 * @return error enumeration
	 */
	virtual err_t RemoveUserFromMap(usr_id &&id)=0;

	/**
	 * @details Function to Subscribe particular Course
	 * @param cid : Course Id
	 * @param uid : User Id
	 * @return error enumeration
	 */
	virtual err_t SubscribeCourse(course_id cid, usr_id uid, bool db_write=true)=0;

	/**
	 * @details Function to Unsubscribe particular Course
	 * @param cid : Course Id
	 * @param uid : User Id
	 * @return error enumeration
	 */
	virtual err_t UnsubscribeCourse(course_id cid, usr_id uid)=0;
};

#endif /* DATABASE_TEST_IDATABASECLIENT_H_ */
