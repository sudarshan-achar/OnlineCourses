/*
 * olclistmgr.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#ifndef INCLUDE_OLCLISTMGR_H_
#define INCLUDE_OLCLISTMGR_H_

#include "olcdatabasemgr.h"

namespace olc {

class OLCListMgr {
public:
	OLCListMgr();
	virtual ~OLCListMgr();
	OLCListMgr(const OLCListMgr &other);
	OLCListMgr(OLCListMgr &&other);
	OLCListMgr& operator=(const OLCListMgr &other);
	OLCListMgr& operator=(OLCListMgr &&other);

public:
	/**
	 * @details Function to return the pointer to this class instance to client classes
	 * @return OLCListMgr* pointer to OLClistmgr class instance
	 */
	OLCListMgr* GetInstance();

	/**
	 * @details Function to Create database classes
	 * @return error enumeration
	 */
	err_t CreateDataBase();

	/**
	 * @details Function to Display all available courses
	 * @return error enumeration
	 */
	err_t DisplayAvailabeCourses();

	/**
	 * @details Function to Display course details By Id
	 * @param id : Course id to search course in DB
	 * @return error enumeration
	 */
	err_t DiplsyCourseDetailsById(course_id id);

	/**
	 * @details Function to Add course to list
	 * @param course : Course details structure
	 * @return error enumeration
	 */
	err_t AddCourseToList(CourseDetails_t course);

	/**
	 * @details Function to remove course from list
	 * @param id : course Id
	 * @return error enumeration
	 */
	err_t RemoveCourseFromList(course_id id);

	/**
	 * @details Function to Clear all courses from list
	 * @return error enumeration
	 */
	err_t ClearAllCourses();

	/**
	 * @details Function return shared object of databasemgr
	 * @return error enumeration
	 */
	std::shared_ptr<OLCDataBaseMgr> GetPointer();

private:
	std::shared_ptr<OLCDataBaseMgr> mDbMgr;
};

} /* namespace olc */

#endif /* INCLUDE_OLCLISTMGR_H_ */
