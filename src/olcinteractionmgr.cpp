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

err_t OLCInteractionMgr::DisplayCourseByTitle(str_t coursetitle) {
  return mDBmgr->GetCourseByTitle(std::move(coursetitle));
}

err_t OLCInteractionMgr::DisplayCourseByAuthor(str_t author) {
  return mDBmgr->DisplayCoursesByAuthor(std::move(author));
}

err_t OLCInteractionMgr::DisplayAvgCoursePrice() {
  std::cout << "\nThe Average course price is : "
            << mDBmgr->GetAvgCoursesPrice() << "\n";
  return NO_ERROR;
}

err_t OLCInteractionMgr::DisplayMinimumCoursePrice() {
  std::cout << "\nThe Minimum course price is : "
            << mDBmgr->GetMinimumCoursePrice() << "\n";
  return NO_ERROR;
}

} /* namespace olc */
