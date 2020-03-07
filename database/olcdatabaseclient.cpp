/*
 * olcdatabaseclient.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olcdatabaseclient.h"
#include <stdio.h>

#define __METHOD_NAME__ std::string(std::string("OLCDatabaseClient::") + __func__ + "(): ")
#define LOG_PRINT(...) logInfo(__METHOD_NAME__,__VA_ARGS__)

using namespace olc;

namespace olc {

OLCDatabaseClient::OLCDatabaseClient() {
	LOG_PRINT("Constructed-------------------->");
}

OLCDatabaseClient::~OLCDatabaseClient() {
	LOG_PRINT("<---------------------Distructed");
}

err_t OLCDatabaseClient::CreateLists() {
	LOG_PRINT("Creating 3 Data lists(Maps)");
	mPimplCourse =
			std::make_unique<OLCDataBaseImpl<OlcCourse<course_details_t>>>();
	mPimplUser = std::make_unique<OLCDataBaseImpl<OlcUser<user_details_t>>>();
	mPimplVendor =
			std::make_unique<OLCDataBaseImpl<OlcVendor<vendor_details_t>>>();
	return NO_ERROR;
}

err_t OLCDatabaseClient::AddCourseToList(course_details_t&& course) {
	LOG_PRINT("Course : ",course.courseName);
	auto lcourse = new OlcCourse<course_details_t>();
	lcourse->SetData(std::move(course));
	mPimplCourse->InsertToMap(std::move(*lcourse));
	delete lcourse;
	lcourse = nullptr;
	return NO_ERROR;
}

err_t OLCDatabaseClient::AddUserToList(user_details_t&& user) {
	LOG_PRINT("User : ",user.userName);
	auto luser = new OlcUser<user_details_t>();
	luser->SetData(std::move(user));
	mPimplUser->InsertToMap(std::move(*luser));
	delete luser;
	luser = nullptr;
	return NO_ERROR;
}

err_t OLCDatabaseClient::RemoveUserFromList(usr_id&& id) {
	LOG_PRINT("User Id :",id);
	auto user = mPimplUser->GetById(std::move(id));
	return mPimplUser->RemoveFromMap(std::move(user));
}

err_t OLCDatabaseClient::RemoveCourseFromList(course_id&& id) {
	LOG_PRINT("Course Id :",id);
	auto course = mPimplCourse->GetById(std::move(id));
	return mPimplCourse->RemoveFromMap(std::move(course));
}

err_t OLCDatabaseClient::DisplayAllVendors() {
	LOG_PRINT("");
	return mPimplVendor->DisplayAll();
}

err_t OLCDatabaseClient::DisplayAllUsers() {
	LOG_PRINT("");
	return mPimplUser->DisplayAll(); }

err_t OLCDatabaseClient::DisplayAllCourses() {
	LOG_PRINT("");
	return mPimplCourse->DisplayAll();
}

err_t OLCDatabaseClient::ClearCourseList() {
	LOG_PRINT("");
	return mPimplCourse->ClearAll(); }

u_int_t OLCDatabaseClient::GetTotalVendorsCount() {
	LOG_PRINT("");
	return mPimplVendor->GetListSize();
}

err_t OLCDatabaseClient::SubscribeCourse(course_id cid, usr_id uid) {
	LOG_PRINT("Course Id : ",cid," User Id : ",uid);
	auto resCourse = mPimplCourse->AddIdToList(std::move(uid), std::move(cid));
	auto resUser = mPimplUser->AddIdToList(std::move(cid), std::move(uid));
	return (err_t)(resCourse | resUser);
}

err_t OLCDatabaseClient::UnsubscribeCourse(course_id cid, usr_id uid) {
	LOG_PRINT("Course Id : ",cid," User Id : ",uid);
	auto resCourse =
			mPimplCourse->RemoveIdFromList(std::move(uid), std::move(cid));
	auto resUser = mPimplUser->RemoveIdFromList(std::move(cid), std::move(uid));
	return (err_t)(resCourse | resUser);
}

u_int_t OLCDatabaseClient::GetTotalCoursesCount() {
	LOG_PRINT("");
	return mPimplCourse->GetListSize();
}

u_int_t OLCDatabaseClient::GetTotalUsersCount() {
	LOG_PRINT("");
	return mPimplUser->GetListSize();
}

user_details_t OLCDatabaseClient::GetUserById(usr_id&& id) {
	LOG_PRINT("User Id : ",id);
	auto luser = mPimplUser->GetById(std::move(id));
	return luser.GetData();
}

vendor_details_t OLCDatabaseClient::GetVendorById(vendor_id&& id) {
	LOG_PRINT("Vendor Id : ",id);
	auto lvendor = mPimplVendor->GetById(std::move(id));
	return lvendor.GetData();
}

course_details_t OLCDatabaseClient::GetCourseById(course_id&& id) {
	LOG_PRINT("Course Id : ",id);
	auto lcourse = mPimplCourse->GetById(std::move(id));
	return lcourse.GetData();
}

err_t OLCDatabaseClient::GetCourseByname(str_t&& title) {
	LOG_PRINT("Title : ",title);
	auto lcourselist = mPimplCourse->GetMap();
	if (lcourselist) {
		auto flag = false;
		for_each((*lcourselist).begin(), (*lcourselist).end(),
				[title, &flag](auto& element) -> err_t {
			auto course = (element.second).GetData();
			if (course.courseName == title) {
				(element.second).DisplayDetails();
				flag = true;
			}
		});
		if (flag) return NO_ERROR;
		return NOT_FOUND;
	}
	return NULL_PTR;
}

err_t OLCDatabaseClient::DisplayCoursesByAuthor(str_t&& author) {
	LOG_PRINT("Author : ",author);
	auto lcourselist = mPimplCourse->GetMap();
	if (lcourselist) {
		auto retFlag = false;
		for_each((*lcourselist).begin(), (*lcourselist).end(),
				[author, &retFlag](auto& element) -> err_t {
			auto course = (element.second).GetData();
			if (course.authorName == author) {
				retFlag = true;
				(element.second).DisplayDetails();
			}
		});
		if (retFlag) return NO_ERROR;
		return NOT_FOUND;
	}
	return NULL_PTR;
}

u_int_t OLCDatabaseClient::GetMinimumCoursePrice(str_t&& author) {
	LOG_PRINT("Author : ",author);
	auto lcourselist = mPimplCourse->GetMap();
	if (lcourselist) {
		std::list<u_int_t> list;
		for_each((*lcourselist).begin(), (*lcourselist).end(),
				[author, &list](auto& element) {
			auto course = (element.second).GetData();
			if (course.authorName == author) {
				list.emplace_back(course.price);
			}
		});
		auto minItr = std::min_element(list.begin(), list.end());
		return *minItr;
	}
	return 0;
}

u_int_t OLCDatabaseClient::GetAvgCoursePrice() {
	LOG_PRINT("");
	auto lcourselist = mPimplCourse->GetMap();
	auto avgprice = 0;
	auto size = mPimplCourse->GetListSize();
	if (lcourselist) {
		for_each((*lcourselist).begin(), (*lcourselist).end(),
				[&avgprice](auto& element) {
			auto course = (element.second).GetData();
			avgprice = avgprice + course.price;
		});
	}
	return (avgprice / size);
}

err_t OLCDatabaseClient::DisplaySubscribers(course_id&& cid) {
	LOG_PRINT("Course Id :",cid);
	auto lmap = mPimplCourse->GetMap();
	for_each((*lmap).begin(), (*lmap).end(), [this, cid](auto& element) {
		if ((element.first) == cid) {
			auto list = (element.second).GetList();
			for_each((*list).begin(), (*list).end(), [this](auto& ele) {
				auto user = this->mPimplUser->GetById(std::move(ele));
				if (user.GetId() != 0) user.DisplayDetails();
			});
		}
	});
	return NO_ERROR;
}

err_t OLCDatabaseClient::DisplayCoursesSubscribed(usr_id&& uid) {
	LOG_PRINT("User Id:",uid);
	auto lmap = mPimplUser->GetMap();
	for_each((*lmap).begin(), (*lmap).end(), [this, uid](auto& element) {
		if ((element.first) == uid) {
			auto list = (element.second).GetList();
			for_each((*list).begin(), (*list).end(), [this](auto& ele) {
				auto course = this->mPimplCourse->GetById(std::move(ele));
				if (course.GetId() != 0) course.DisplayDetails();
			});
		}
	});
	return NO_ERROR;
}

} /* namespace olc */
