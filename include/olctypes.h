/*
 * olctypes.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 *
 *  Details: This is header file contains all types that are useful in project.
 */
#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <unordered_map>

#ifndef INCLUDE_OLCTYPES_H_
#define INCLUDE_OLCTYPES_H_

/*!
 * Ids for different identities
 */
using usr_id = unsigned int;      //! user specific Id type
using vendor_id = unsigned int;   //! vendor specific Id type
using course_id = unsigned int;   //! course specific Id type
using session_id = unsigned int;  //! Session Id

using str_t = std::string;     //! string type defined
using u_int_t = unsigned int;  //! unsigned int type specified

/*!
 * Enumeration holds error details
 */
using err_t = enum Errors {
  NO_ERROR,
  NO_ELEMENTS,
  NOT_FOUND,
  NULL_PTR,
  MINOR_ERROR,
  MAJOR_ERROR
};

/*!
 * Structure holds Course details
 */
using course_details_t = struct CourseDetails {
  course_id courseId;
  str_t courseName;
  str_t authorName;
  str_t instructorName;
  u_int_t duration;
  u_int_t price;
  u_int_t courseRating;
};

/*!
 * Structure type holds User details
 */
using user_details_t = struct UserDetails {
  usr_id userId;
  str_t userName;
  str_t fullName;
  str_t dateOfBirth;
  str_t domain;
};

/*!
 * Structure to hold Vendor details
 */
using vendor_details_t = struct VendorDetails {
  vendor_id vendorId;
  str_t vendorName;
  str_t fullName;
  str_t dateOfBirth;
  str_t domain;
};

/**
 * Types to define different lists
 */
using course_id_list_t = std::list<course_id>;  //! course id list type
using user_id_list_t = std::list<course_id>;    //! user id list type
using vendor_id_list_t = std::list<course_id>;  //! vendor id list type

using generic_list_t =
    std::list<u_int_t>;  //! generic list type to hold different Ids

#endif /* INCLUDE_OLCTYPES_H_ */
