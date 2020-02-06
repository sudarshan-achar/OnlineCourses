/*
 * olcinteractionmgr.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olcinteractionmgr.h"

using namespace olc;

namespace olc {

OLCInteractionMgr::OLCInteractionMgr() {
  // TODO Auto-generated constructor stub
}

OLCInteractionMgr::~OLCInteractionMgr() {
  // TODO Auto-generated destructor stub
}

OLCInteractionMgr::OLCInteractionMgr(const OLCInteractionMgr &other) {
  // TODO Auto-generated constructor stub
  *this = other;
}

OLCInteractionMgr::OLCInteractionMgr(OLCInteractionMgr &&other) {
  // TODO Auto-generated constructor stub
  *this = other;
}

OLCInteractionMgr &OLCInteractionMgr::operator=(
    const OLCInteractionMgr &other) {
  // TODO Auto-generated method stub
  *this = other;
  return *this;
}

OLCInteractionMgr &OLCInteractionMgr::operator=(OLCInteractionMgr &&other) {
  // TODO Auto-generated method stub
  *this = other;
  return *this;
}

err_t OLCInteractionMgr::Initialize(std::shared_ptr<OLCDataBaseMgr> &&inst) {
  mDBmgr = inst;
  return NO_ERROR;
}

err_t OLCInteractionMgr::DisplayCourseByTitle(str_t &&coursetitle) {
  if (mDBmgr != nullptr)
    return mDBmgr->GetCourseByTitle(std::move(coursetitle));
  return NULL_PTR;
}

err_t OLCInteractionMgr::DisplayCourseByAuthor(str_t &&author) {
  if (mDBmgr != nullptr)
    return mDBmgr->DisplayCoursesByAuthor(std::move(author));
  return NULL_PTR;
}

err_t OLCInteractionMgr::DisplayAvgCoursePrice() {
  if (mDBmgr != nullptr) {
    std::cout << "\nThe Average course price is : "
              << mDBmgr->GetAvgCoursesPrice() << " Rs.\n\n\n";
    return NO_ERROR;
  }
  return NULL_PTR;
}

err_t OLCInteractionMgr::DisplayMinimumCoursePrice(str_t &&author) {
  if (mDBmgr != nullptr) {
    std::cout << "\nThe Minimum course price is : "
              << mDBmgr->GetMinimumCoursePrice(std::move(author))
              << " Rs.\n\n\n";
    return NO_ERROR;
  }
  return NULL_PTR;
}

err_t OLCInteractionMgr::DisplayTotalUserCount() {
  if (mDBmgr != nullptr) {
    std::cout << "\nThe total users are : " << mDBmgr->GetTotalUserCount()
              << "\n\n";
    return NO_ERROR;
  }
  return NULL_PTR;
}

err_t OLCInteractionMgr::DisplaySubscribers(course_id &&id) {
  if (mDBmgr != nullptr) return mDBmgr->DiplaySubscribers(std::move(id));
  return NULL_PTR;
}

err_t OLCInteractionMgr::DisplayCoursesSubscribed(usr_id &&id) {
  if (mDBmgr != nullptr) return mDBmgr->DiplaySubscribedCourses(std::move(id));
  return NULL_PTR;
}

} /* namespace olc */
