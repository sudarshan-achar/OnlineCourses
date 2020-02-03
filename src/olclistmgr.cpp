/*
 * olclistmgr.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olclistmgr.h"

namespace olc {

OLCListMgr::OLCListMgr() {
	// TODO Auto-generated constructor stub
	mDbMgr=std::make_shared<OLCDataBaseMgr>();
}

OLCListMgr::~OLCListMgr() {
	// TODO Auto-generated destructor stub
}

OLCListMgr::OLCListMgr(const OLCListMgr &other) {
	// TODO Auto-generated constructor stub
}

OLCListMgr::OLCListMgr(OLCListMgr &&other) {
	// TODO Auto-generated constructor stub
}

OLCListMgr& OLCListMgr::operator=(const OLCListMgr &other) {
	// TODO Auto-generated method stub
	return *this;
}

OLCListMgr& OLCListMgr::operator=(OLCListMgr &&other) {
	// TODO Auto-generated method stub
	return *this;
}

OLCListMgr* OLCListMgr::GetInstance() {
	return this;
}

err_t OLCListMgr::CreateDataBase() {
	if(mDbMgr)return mDbMgr->CreatDatabaseInstance();
	return NULL_PTR;
}

err_t OLCListMgr::DisplayAvailabeCourses() {
	if(mDbMgr)return mDbMgr->DisplayAvailableCourses();
	return NULL_PTR;
}

err_t OLCListMgr::AddCourseToList(CourseDetails_t course) {
	if(mDbMgr)return mDbMgr->AddCourseToList(course);
	return NULL_PTR;
}

err_t OLCListMgr::RemoveCourseFromList(course_id id) {
	if(mDbMgr)return mDbMgr->RemoveCourseFromList(id);
	return NULL_PTR;
}

err_t OLCListMgr::DiplsyCourseDetailsById(course_id id) {
	if(mDbMgr==nullptr)return NULL_PTR;
	auto course = mDbMgr->GetCourseById(id);
	if((course.courseId!=0)){
		auto lcourse = std::make_unique<OlcCourse<CourseDetails_t>>();
		lcourse->SetData(std::move(course));
		return lcourse->DisplayDetails();
	}else if((course.courseId==0)&&(mDbMgr->GetTotalCoursesCount()!=0)){
		return NOT_FOUND;
	}else
		return NO_ELEMENTS;
}

err_t OLCListMgr::ClearAllCourses() {
	if(mDbMgr)return mDbMgr->ClearCourseListDB();
	return NULL_PTR;
}

std::shared_ptr<OLCDataBaseMgr>OLCListMgr::GetPointer() {
	return mDbMgr;
}

} /* namespace olc */
