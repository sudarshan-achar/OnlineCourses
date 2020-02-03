/*
 * olctypes.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <memory>

#ifndef INCLUDE_OLCTYPES_H_
#define INCLUDE_OLCTYPES_H_

/**
 * Ids for different identities
 */
using usr_id = unsigned int ;
using vendor_id = unsigned int;
using course_id = unsigned int;
using session_id = unsigned int;

using str_t= std::string ;
using u_int_t = unsigned int;

/*
 * Enumeration holds error details
 */
typedef enum{
	NO_ERROR,
	NO_ELEMENTS,
	NOT_FOUND,
	NULL_PTR,
	MAJOR_ERROR,
	MINOR_ERROR
}err_t;

/*
 * Structure holds Course details
 */
typedef struct{
	course_id courseId;
	str_t courseName;
	str_t authorName;
	str_t instructorName;
	u_int_t duration;
	u_int_t price;
	u_int_t courseRating;
}CourseDetails_t;

/*
 * Structure type holds User details
 */
typedef struct{
	usr_id userId;
	str_t userName;
	str_t fullName;
	str_t dateOfBirth;
	str_t domain;
}UserDetails_t;

/*
 * Structure to hold Vendor details
 */
typedef struct{
	vendor_id vendorId;
	str_t vendorName;
	str_t fullName;
	str_t dateOfBirth;
	str_t domain;
}VendorDetails_t;

/**
 * Types to define different lists
 */
using CourseIdList = std::list<course_id>;
using UserIdList = std::list<course_id>;
using VendorIdList = std::list<course_id>;

#endif /* INCLUDE_OLCTYPES_H_ */
