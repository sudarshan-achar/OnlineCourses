/*
 * olcdatabasemgr.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olcdatabasemgr.h"

namespace olc {

OLCDataBaseMgr::OLCDataBaseMgr() {}

OLCDataBaseMgr::~OLCDataBaseMgr() {}

err_t OLCDataBaseMgr::CreatDatabaseInstance() {
  mDBClientUniptr = std::make_unique<OLCDatabaseClient>();
  return mDBClientUniptr->CreateLists();
}

err_t OLCDataBaseMgr::AddCourseToList(course_details_t course) {
  return mDBClientUniptr->AddCourseToMap(std::move(course));
}

err_t OLCDataBaseMgr::RemoveCourseFromList(course_id id) {
  return mDBClientUniptr->RemoveCourseFromMap(std::move(id));
}

err_t OLCDataBaseMgr::ClearCourseListDB() {
  return mDBClientUniptr->ClearCourseList();
}

u_int_t OLCDataBaseMgr::GetTotalCoursesCount() {
  return mDBClientUniptr->GetTotalCoursesCount();
}

err_t OLCDataBaseMgr::DisplayAvailableCourses() {
  return mDBClientUniptr->DisplayAllCourses();
}

course_details_t OLCDataBaseMgr::GetCourseById(course_id id) {
  return mDBClientUniptr->GetCourseById(std::move(id));
}

err_t OLCDataBaseMgr::DisplayAllUsers() {
  return mDBClientUniptr->DisplayAllUsers();
}

err_t OLCDataBaseMgr::DisplayAllVendors() {
  return mDBClientUniptr->DisplayAllVendors();
}

user_details_t OLCDataBaseMgr::GetUserById(usr_id id) {
  return mDBClientUniptr->GetUserById(std::move(id));
}

vendor_details_t OLCDataBaseMgr::GetVendorById(vendor_id id) {
  return mDBClientUniptr->GetVendorById(std::move(id));
}

u_int_t OLCDataBaseMgr::GetTotalUserCount() {
  return mDBClientUniptr->GetTotalUsersCount();
}

err_t OLCDataBaseMgr::AddUser(user_details_t &&user) {
  return mDBClientUniptr->AddUserToMap(std::move(user));
}

err_t OLCDataBaseMgr::RemoveUser(usr_id id) {
  return mDBClientUniptr->RemoveUserFromMap(std::move(id));
}

err_t OLCDataBaseMgr::DisplayCoursesByAuthor(str_t &&author) {
  return mDBClientUniptr->DisplayCoursesByAuthor(std::move(author));
}

u_int_t OLCDataBaseMgr::GetTotalVendorsCount() {
  return mDBClientUniptr->GetTotalVendorsCount();
}

err_t OLCDataBaseMgr::SubscribeCourse(course_id cid, usr_id uid) {
  return mDBClientUniptr->SubscribeCourse(cid, uid);
}

err_t OLCDataBaseMgr::UnsubscribeCourse(course_id cid, usr_id uid) {
  return mDBClientUniptr->UnsubscribeCourse(cid, uid);
}

err_t OLCDataBaseMgr::GetCourseByTitle(str_t &&coursename) {
  return mDBClientUniptr->GetCourseByname(std::move(coursename));
}

u_int_t OLCDataBaseMgr::GetAvgCoursesPrice() {
  return mDBClientUniptr->GetAvgCoursePrice();
}

u_int_t OLCDataBaseMgr::GetMinimumCoursePrice(str_t &&author) {
  return mDBClientUniptr->GetMinimumCoursePrice(std::move(author));
}

err_t OLCDataBaseMgr::DiplaySubscribers(course_id &&cid) {
  return mDBClientUniptr->DisplaySubscribers(std::move(cid));
}

err_t OLCDataBaseMgr::DiplaySubscribedCourses(usr_id &&uid) {
  return mDBClientUniptr->DisplayCoursesSubscribed(std::move(uid));
}

} /* namespace olc */
