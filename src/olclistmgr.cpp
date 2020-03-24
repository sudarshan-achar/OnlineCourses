/*
 * olclistmgr.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olclistmgr.h"

namespace olc {

OLCListMgr::OLCListMgr() { mDbMgr = std::make_shared<OLCDataBaseMgr>(); }

OLCListMgr::~OLCListMgr() {}

OLCListMgr::OLCListMgr(const OLCListMgr &other) {}

OLCListMgr::OLCListMgr(OLCListMgr &&other) {}

auto OLCListMgr::operator=(const OLCListMgr &other)->OLCListMgr& { return *this; }

auto OLCListMgr::operator=(OLCListMgr &&other)->OLCListMgr& { return *this; }

auto OLCListMgr::GetInstance()->OLCListMgr* { return this; }

auto OLCListMgr::CreateDataBase()->err_t {
  if (mDbMgr) return mDbMgr->CreatDatabaseInstance();
  return NULL_PTR;
}

auto OLCListMgr::DisplayAvailabeCourses()->err_t {
  if (mDbMgr) return mDbMgr->DisplayAvailableCourses();
  return NULL_PTR;
}

auto OLCListMgr::AddCourseToList(course_details_t &&course)->err_t {
  if (mDbMgr) return mDbMgr->AddCourseToList(course);
  return NULL_PTR;
}

auto OLCListMgr::RemoveCourseFromList(course_id &&id)->err_t {
  if (mDbMgr) return mDbMgr->RemoveCourseFromList(id);
  return NULL_PTR;
}

auto OLCListMgr::DiplsyCourseDetailsById(course_id &&id)->err_t {
  if (mDbMgr == nullptr) return NULL_PTR;
  auto course = mDbMgr->GetCourseById(id);
  if ((course.courseId != 0)) {
    auto lcourse = std::make_unique<OlcCourse<course_details_t>>();
    lcourse->SetData(std::move(course));
    return lcourse->DisplayDetails();
  } else if ((course.courseId == 0) && (mDbMgr->GetTotalCoursesCount() != 0)) {
    return NOT_FOUND;
  } else
    return NO_ELEMENTS;
}

auto OLCListMgr::ClearAllCourses()->err_t {
  if (mDbMgr) return mDbMgr->ClearCourseListDB();
  return NULL_PTR;
}

auto OLCListMgr::GetPointer()->std::shared_ptr<OLCDataBaseMgr> { return mDbMgr; }

} /* namespace olc */
