/*
 * olcDatabaseClient.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#ifndef DATABASE_OLCDATABASECLIENT_H_
#define DATABASE_OLCDATABASECLIENT_H_

#include "olcdatabaseimpl.h"

namespace olc {

class OLCDatabaseClient {
public:
	OLCDatabaseClient();
	virtual ~OLCDatabaseClient();
	OLCDatabaseClient(const OLCDatabaseClient &other)=default;
	OLCDatabaseClient(OLCDatabaseClient &&other)=default;
	OLCDatabaseClient& operator=(const OLCDatabaseClient &other)=default;
	OLCDatabaseClient& operator=(OLCDatabaseClient &&other)=default;

	err_t CreateLists();
	err_t AddCourseToList(CourseDetails_t course);
	err_t AddUserToList(UserDetails_t &&user);
	err_t RemoveCourseFromList(course_id id);
	err_t RemoveUserFromList(usr_id id);
	err_t ClearCourseList();

	err_t DisplayAllCourses();
	err_t DisplayAllUsers();
	err_t DisplayAllVendors();
	err_t DisplayCoursesByAuthor(str_t  author);

	err_t SubscribeCourse(course_id cid, usr_id uid);
	err_t UnsubscribeCourse(course_id cid,usr_id uid);

	u_int_t GetTotalUsersCount();
	u_int_t GetTotalVendorsCount();
	u_int_t GetTotalCoursesCount();

	u_int_t GetMinimumCoursePrice();
	u_int_t GetAvgCoursePrice();

	CourseDetails_t GetCourseById(course_id id);
	UserDetails_t GetUserById(usr_id id);
	VendorDetails_t GetVendorById(vendor_id id);

	err_t GetCourseByname(str_t title);

public:
    std::unique_ptr<OLCDataBaseImpl<OlcCourse<CourseDetails_t>>> mPimplCourse;
    std::unique_ptr<OLCDataBaseImpl<OlcUser<UserDetails_t>>> mPimplUser;
    std::unique_ptr<OLCDataBaseImpl<OlcVendor<VendorDetails_t>>> mPimplVendor;
};

} /* namespace olc */

#endif /* DATABASE_OLCDATABASECLIENT_H_ */
