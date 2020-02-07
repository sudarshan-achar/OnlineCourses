/*
 * olcdatabaseclient.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 *  OLCDatabaseClient: This class is a client to main database implementation
 *                     template class.
 */

#ifndef DATABASE_OLCDATABASECLIENT_H_
#define DATABASE_OLCDATABASECLIENT_H_

#include "olcdatabaseimpl.h"

namespace olc {

class OLCDatabaseClient {
 public:
  OLCDatabaseClient();
  virtual ~OLCDatabaseClient();
  OLCDatabaseClient(const OLCDatabaseClient &other) = default;
  OLCDatabaseClient(OLCDatabaseClient &&other) = default;
  OLCDatabaseClient &operator=(const OLCDatabaseClient &other) = default;
  OLCDatabaseClient &operator=(OLCDatabaseClient &&other) = default;

 public:
  /**
   * @details Function to create database for each details such as course
   * list,user list
   * and vendor list.
   * @return error enumeration
   */
  err_t CreateLists();

  /**
   * @details Function to Add courses to the map
   * @param course : course_details_t structure
   * @return error enumeration
   */
  err_t AddCourseToList(course_details_t &&course);

  /**
   * @details Function to Add users to the map
   * @param user : user_details_t structure
   * @return error enumeration
   */
  err_t AddUserToList(user_details_t &&user);

  /**
   * @details Function Remove course from map
   * @param id : Course Id
   * @return error enumeration
   */
  err_t RemoveCourseFromList(course_id &&id);

  /**
   * @details Function Remove user from map
   * @param id : User Id
   * @return error enumeration
   */
  err_t RemoveUserFromList(usr_id &&id);

  /**
   * @details Function to Clear course list map
   * @return error enumeration
   */
  err_t ClearCourseList();

  /**
   * @details Function to Display all courses present in the map
   * @return error enumeration
   */
  err_t DisplayAllCourses();

  /**
   * @details Function to Display all users present in the map
   * @return error enumeration
   */
  err_t DisplayAllUsers();

  /**
   * @details Function to Display all vendors present in the map
   * @return error enumeration
   */
  err_t DisplayAllVendors();

  /**
   * @details Function to Display Courses By Author name present in the map
   * @param author : author name
   * @return error enumeration
   */
  err_t DisplayCoursesByAuthor(str_t &&author);

  /**
   * @details Function to Subscribe particular Course
   * @param cid : Course Id
   * @param uid : User Id
   * @return error enumeration
   */
  err_t SubscribeCourse(course_id cid, usr_id uid);

  /**
   * @details Function to Unsubscribe particular Course
   * @param cid : Course Id
   * @param uid : User Id
   * @return error enumeration
   */
  err_t UnsubscribeCourse(course_id cid, usr_id uid);

  /**
   * @details Function to get total courses count
   * @return count
   */
  u_int_t GetTotalUsersCount();

  /**
   * @details Function to get total users count
   * @return count
   */
  u_int_t GetTotalVendorsCount();

  /**
   * @details Function to get total vendors count
   * @return count
   */
  u_int_t GetTotalCoursesCount();

  /**
   * @details Function to get minimum course price
   * @return price
   */
  u_int_t GetMinimumCoursePrice(str_t &&author);

  /**
   * @details Function to get Average course price
   * @return price
   */
  u_int_t GetAvgCoursePrice();

  /**
   * @details Function to get Course by sending id
   * @param id : Course Id
   * @return course_details_t structure
   */
  course_details_t GetCourseById(course_id &&id);

  /**
   * @details Function to get User by sending id
   * @param id : User Id
   * @return user_details_t structure
   */
  user_details_t GetUserById(usr_id &&id);

  /**
   * @details Function to get Vendor by sending id
   * @param id : Vendor Id
   * @return vendor_details_t structure
   */
  vendor_details_t GetVendorById(vendor_id &&id);

  /**
   * @details Function to get Course details by title
   * @param title
   * @return error enumeration
   */
  err_t GetCourseByname(str_t &&title);

  /**
   * @details Function to Display subscribers
   * @param cid
   * @return error enumeration
   */
  err_t DisplaySubscribers(course_id &&cid);

  /**
   * @details Function to Display courses subscribed by user
   * @param uid
   * @return error enumeration
   */
  err_t DisplayCoursesSubscribed(usr_id &&uid);

 private:
  /*!
   * Unique_ptr to implementation of Course list database
   */
  std::unique_ptr<OLCDataBaseImpl<OlcCourse<course_details_t>>> mPimplCourse;

  /*!
   * Unique_ptr to implementation of User list database
   */
  std::unique_ptr<OLCDataBaseImpl<OlcUser<user_details_t>>> mPimplUser;

  /*!
   * Unique_ptr to implementation of Vendor list database
   */
  std::unique_ptr<OLCDataBaseImpl<OlcVendor<vendor_details_t>>> mPimplVendor;
};

} /* namespace olc */

#endif /* DATABASE_OLCDATABASECLIENT_H_ */
