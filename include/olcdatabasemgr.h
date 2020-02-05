/*
 * olcdatabasemgr.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 *  OLCDataBaseMgr: This class is to manage the database operations and divide
 * the functionalities
 */

#ifndef INCLUDE_OLCDATABASEMGR_H_
#define INCLUDE_OLCDATABASEMGR_H_

#include "../database/olcdatabaseclient.h"

namespace olc {

class OLCDataBaseMgr {
 public:
  OLCDataBaseMgr();
  virtual ~OLCDataBaseMgr();
  OLCDataBaseMgr(const OLCDataBaseMgr &other) = default;
  OLCDataBaseMgr(OLCDataBaseMgr &&other) = default;
  OLCDataBaseMgr &operator=(const OLCDataBaseMgr &other) = default;
  OLCDataBaseMgr &operator=(OLCDataBaseMgr &&other) = default;

 public:
  /**
   * @details Function to Create database
   * @return error enumeration value
   */
  err_t CreatDatabaseInstance();

  /**
   * @details Function to Add course to map
   * @param course
   * @return error enumeration value
   */
  err_t AddCourseToList(CourseDetails_t course);

  /**
   * @details Function to Add user to map
   * @param user
   * @return error enumeration value
   */
  err_t AddUser(UserDetails_t &&user);

  /**
   * @details Function to remove user from map
   * @param id
   * @return error enumeration value
   */
  err_t RemoveUser(usr_id id);

  /**
   * @details Function to remove course from map
   * @param id
   * @return error enumeration value
   */
  err_t RemoveCourseFromList(course_id id);

  /**
   * @details Function to clear course list database map
   * @return error enumeration value
   */
  err_t ClearCourseListDB();

  /**
   * @details Function to display all available courses details
   * @return error enumeration value
   */
  err_t DisplayAvailableCourses();

  /**
   * @details Function to display all available users details
   * @return error enumeration value
   */
  err_t DisplayAllUsers();

  /**
   * @details Function to display all available vendors details
   * @return error enumeration value
   */
  err_t DisplayAllVendors();

  /**
   * @details Function to display course details by author name
   * @param author
   * @return error enumeration value
   */
  err_t DisplayCoursesByAuthor(str_t &&author);

  /**
   * @details Function to subscribe particular course
   * @param cid : Course Id
   * @param uid : User Id
   * @return error enumeration value
   */
  err_t SubscribeCourse(course_id cid, usr_id uid);

  /**
   * @details Function to unsubscribe particular course
   * @param cid : Course Id
   * @param uid : User Id
   * @return error enumeration value
   */
  err_t UnsubscribeCourse(course_id cid, usr_id uid);

  /**
   * @details Function to get course details by Id
   * @param id : Course Id
   * @return error enumeration value
   */
  CourseDetails_t GetCourseById(course_id id);

  /**
   * @details Function to get user details by Id
   * @param id
   * @return UserDetails_t structure
   */
  UserDetails_t GetUserById(usr_id id);

  /**
   * @details Function to get vendor by Id
   * @param id
   * @return VendorDetails_t structure
   */
  VendorDetails_t GetVendorById(vendor_id id);

  /**
   * @details Function to get total courses count
   * @return count value
   */
  u_int_t GetTotalCoursesCount();

  /**
   * @details Function to get total users count
   * @return count value
   */
  u_int_t GetTotalUserCount();

  /**
   * @details Function to get total vendors count
   * @return count value
   */
  u_int_t GetTotalVendorsCount();

  /**
   * @details Function to get average courses price
   * @return price value
   */
  u_int_t GetAvgCoursesPrice();

  /**
   * @details Function to Function to get minimum courses price
   * @return price value
   */
  u_int_t GetMinimumCoursePrice(str_t &&author);

  /**
   * @details Function to get course by title
   * @param coursename : title of the course
   * @return
   */
  err_t GetCourseByTitle(str_t &&coursename);

  /**
   *
   * @param cid
   * @return
   */
  err_t DiplaySubscribers(course_id &&cid);

  /**
   *
   * @param uid
   * @return
   */
  err_t DiplaySubscribedCourses(usr_id &&uid);

 private:
  /*!
   * Unique pointer to point the single ownered database client object to access
   * data base
   */
  std::unique_ptr<OLCDatabaseClient> mDBClientUniptr;
};

} /* namespace olc */

#endif /* INCLUDE_OLCDATABASEMGR_H_ */
