/*
 * olcdatabaseclient.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olcdatabaseclient.h"

using namespace olc;

namespace olc {

OLCDatabaseClient::OLCDatabaseClient(){

}

OLCDatabaseClient::~OLCDatabaseClient(){

}

err_t OLCDatabaseClient::CreateLists() {
	mPimplCourse=std::make_unique<OLCDataBaseImpl<OlcCourse<CourseDetails_t>>>();
	mPimplUser=std::make_unique<OLCDataBaseImpl<OlcUser<UserDetails_t>>>();
	mPimplVendor=std::make_unique<OLCDataBaseImpl<OlcVendor<VendorDetails_t>>>();
	return NO_ERROR;
}

err_t OLCDatabaseClient::AddCourseToList(CourseDetails_t course) {
	auto lcourse=new OlcCourse<CourseDetails_t>();
	lcourse->SetData(std::move(course));
	mPimplCourse->InsertToMap(std::move(*lcourse));
	delete lcourse;
	lcourse=nullptr;
	return NO_ERROR;
}

err_t OLCDatabaseClient::AddUserToList(UserDetails_t &&user) {
	auto luser=new OlcUser<UserDetails_t>();
	luser->SetData(std::move(user));
	mPimplUser->InsertToMap(std::move(*luser));
	delete luser;
	luser=nullptr;
	return NO_ERROR;
}

err_t OLCDatabaseClient::RemoveUserFromList(usr_id id) {
	auto user = mPimplUser->GetById(id);
	return mPimplUser->RemoveFromMap(std::move(user));
}

err_t OLCDatabaseClient::RemoveCourseFromList(course_id id) {
	auto course = mPimplCourse->GetById(id);
	return mPimplCourse->RemoveFromMap(std::move(course));
}

err_t OLCDatabaseClient::DisplayAllVendors() {
	return mPimplVendor->DisplayAll();
}

err_t OLCDatabaseClient::DisplayAllUsers() {
	return mPimplUser->DisplayAll();
}

err_t OLCDatabaseClient::DisplayAllCourses() {
	return mPimplCourse->DisplayAll();
}

err_t OLCDatabaseClient::ClearCourseList() {
	return mPimplCourse->ClearAll();
}

u_int_t OLCDatabaseClient::GetTotalVendorsCount() {
	return mPimplVendor->GetListSize();
}

err_t OLCDatabaseClient::SubscribeCourse(course_id cid, usr_id uid) {
	return mPimplUser->AddIdToList(std::move(cid),std::move(uid));
}

err_t OLCDatabaseClient::UnsubscribeCourse(course_id cid, usr_id uid) {
	return mPimplUser->RemoveIdFromList(std::move(cid),std::move(uid));
}

u_int_t OLCDatabaseClient::GetTotalCoursesCount() {
	return mPimplCourse->GetListSize();
}

u_int_t OLCDatabaseClient::GetTotalUsersCount() {
	return mPimplUser->GetListSize();
}

UserDetails_t OLCDatabaseClient::GetUserById(usr_id id) {
	auto luser = mPimplUser->GetById(id);
	return luser.GetData();
}

VendorDetails_t OLCDatabaseClient::GetVendorById(vendor_id id) {
	auto lvendor = mPimplVendor->GetById(id);
	return lvendor.GetData();
}

CourseDetails_t OLCDatabaseClient::GetCourseById(vendor_id id) {
	auto lcourse = mPimplCourse->GetById(id);
	return lcourse.GetData();
}

err_t OLCDatabaseClient::GetCourseByname(str_t title) {
	auto lcourselist = mPimplCourse->GetMap();
	if(lcourselist){
		for ( auto& element: *lcourselist ){
			auto lcourse=element.second;
			auto course = lcourse.GetData();
			if(course.courseName==title){
				lcourse.DisplayDetails();
				return NO_ERROR;
			}
		}
		return NOT_FOUND;
	}
	return NULL_PTR;
}

err_t OLCDatabaseClient::DisplayCoursesByAuthor(str_t author) {
	auto lcourselist = mPimplCourse->GetMap();
	if(lcourselist){
		bool ret=false;
		for ( auto& element: *lcourselist ){
			auto lcourse=element.second;
			auto course = lcourse.GetData();
			if(course.authorName==author){
				ret=true;
				lcourse.DisplayDetails();
			}
		}
		if(ret)return NO_ERROR;
		return NOT_FOUND;
	}
	return NULL_PTR;
}

u_int_t OLCDatabaseClient::GetMinimumCoursePrice() {
	auto lcourselist = mPimplCourse->GetMap();
	auto course=((*lcourselist)[0]).GetData();
	auto minPrice = course.price;
	if(lcourselist){
		for ( auto& element: *lcourselist ){
			auto lcourse=element.second;
			auto course = lcourse.GetData();
			if(course.price < minPrice){
				minPrice=course.price;
			}
		}
	}
	return minPrice;
}

u_int_t OLCDatabaseClient::GetAvgCoursePrice() {
	auto lcourselist = mPimplCourse->GetMap();
	auto avgprice = 0;
	auto size = mPimplCourse->GetListSize();
	if(lcourselist){
		for ( auto& element: (*lcourselist) ){
			auto lcourse=element.second;
			auto course = lcourse.GetData();
			avgprice=avgprice+course.price;
		}
	}
	return (avgprice/size);
}

} /* namespace olc */

