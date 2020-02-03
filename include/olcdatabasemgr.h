/*
 * olcdatabasemgr.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#ifndef INCLUDE_OLCDATABASEMGR_H_
#define INCLUDE_OLCDATABASEMGR_H_

#include "../database/olcdatabaseclient.h"

namespace olc {

class OLCDataBaseMgr {
public:
	OLCDataBaseMgr();
	virtual ~OLCDataBaseMgr();
	OLCDataBaseMgr(const OLCDataBaseMgr &other)=default;
	OLCDataBaseMgr(OLCDataBaseMgr &&other)=default;
	OLCDataBaseMgr& operator=(const OLCDataBaseMgr &other)=default;
	OLCDataBaseMgr& operator=(OLCDataBaseMgr &&other)=default;

public:
	err_t CreatDatabaseInstance();
	err_t AddCourseToList(CourseDetails_t course);
	err_t AddUser(UserDetails_t &&user);
	err_t RemoveUser(usr_id id);
	err_t RemoveCourseFromList(course_id id);
	err_t ClearCourseListDB();

	err_t DisplayAvailableCourses();
	err_t DisplayAllUsers();
	err_t DisplayAllVendors();
	err_t DisplayCoursesByAuthor(str_t author);

	err_t SubscribeCourse(course_id cid ,usr_id uid);
	err_t UnsubscribeCourse(course_id cid ,usr_id uid);

	CourseDetails_t GetCourseById(course_id id);
	UserDetails_t GetUserById(usr_id id);
	VendorDetails_t GetVendorById(vendor_id id);

	u_int_t GetTotalCoursesCount();
	u_int_t GetTotalUserCount();
	u_int_t GetTotalVendorsCount();

	u_int_t GetAvgCoursesPrice();
	u_int_t GetMinimumCoursePrice();
	err_t GetCourseByTitle(str_t coursename);

private :
	std::unique_ptr<OLCDatabaseClient> mDBClientUniptr;
};

} /* namespace olc */

#endif /* INCLUDE_OLCDATABASEMGR_H_ */
