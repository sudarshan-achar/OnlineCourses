/*
 * olcinteractionmgr.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 *  OLCInteractionMgr: This class is to manage the user or vendor
 *                     interactions(as clients) seeking some details.
 */

#ifndef INCLUDE_OLCINTERACTIONMGR_H_
#define INCLUDE_OLCINTERACTIONMGR_H_
#include "olcdatabasemgr.h"

namespace olc {

class OLCInteractionMgr {
 public:
  OLCInteractionMgr();
  virtual ~OLCInteractionMgr();
  OLCInteractionMgr(const OLCInteractionMgr &other);
  OLCInteractionMgr(OLCInteractionMgr &&other);
  OLCInteractionMgr &operator=(const OLCInteractionMgr &other);
  OLCInteractionMgr &operator=(OLCInteractionMgr &&other);

 public:
  /**
   * @details Function to initialize interactionmgr with databasemgr shared
   * object
   * @param inst : instance of databasemgr shared pointer
   * @return
   */
  err_t Initialize(std::shared_ptr<OLCDataBaseMgr> &&inst);

  /**
   * @details Function to  Find a course by specific title and get details
   * @param str : Course title
   * @return error enumeration
   */
  err_t DisplayCourseByTitle(str_t coursetitle);

  /**
   * @details Function to Find all courses by a specific author
   * @param str : Course author
   * @return error enumeration
   */
  err_t DisplayCourseByAuthor(str_t author);

  /**
   * @details Function to Find the average price of all courses
   * @return average price of all courses
   */
  err_t DisplayAvgCoursePrice();

  /**
   * @details Function to Find the minimum price among all courses by a specific
   * author
   * @param author :
   * @return
   */
  err_t DisplayMinimumCoursePrice(str_t &&author);

 private:
  /*!
   * Member which is a shared_ptr of OLCDataBaseMgr object to access
   * OLCDataBaseMgr functionalities
   */
  std::shared_ptr<OLCDataBaseMgr> mDBmgr;
};

} /* namespace olc */

#endif /* INCLUDE_OLCINTERACTIONMGR_H_ */
