/*
 * olclistmgr.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 *
 *  OLCListMgr: This class is to manage the typical operations on Course list.
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
  auto operator=(const OLCListMgr &other)->OLCListMgr&;
  auto operator=(OLCListMgr &&other)->OLCListMgr&;

 public:
  /**
   * @details Function to return the pointer to this class instance to client
   * classes
   * @return OLCListMgr* pointer to OLClistmgr class instance
   */
  auto GetInstance()->OLCListMgr *;

  /**
   * @details Function to Create database classes
   * @return error enumeration
   */
  auto CreateDataBase()->err_t;

  /**
   * @details Function to Display all available courses
   * @return error enumeration
   */
  auto DisplayAvailabeCourses()->err_t;

  /**
   * @details Function to Display course details By Id
   * @param id : Course id to search course in DB
   * @return error enumeration
   */
  auto DiplsyCourseDetailsById(course_id &&id)->err_t;

  /**
   * @details Function to Add course to list
   * @param course : Course details structure
   * @return error enumeration
   */
  auto AddCourseToList(course_details_t &&course)->err_t;

  /**
   * @details Function to remove course from list
   * @param id : course Id
   * @return error enumeration
   */
  auto RemoveCourseFromList(course_id &&id)->err_t;

  /**
   * @details Function to Clear all courses from list
   * @return error enumeration
   */
  auto ClearAllCourses()->err_t;

  /**
   * @details Function return shared object of databasemgr
   * @return error enumeration
   */
  auto GetPointer()->std::shared_ptr<OLCDataBaseMgr>;

 private:
  std::shared_ptr<OLCDataBaseMgr> mDbMgr;  //
};

} /* namespace olc */

#endif /* INCLUDE_OLCLISTMGR_H_ */
