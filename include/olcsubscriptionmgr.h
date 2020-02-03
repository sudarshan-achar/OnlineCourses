/*
 * olcsubscriptionmgr.h
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#ifndef INCLUDE_OLCSUBSCRIPTIONMGR_H_
#define INCLUDE_OLCSUBSCRIPTIONMGR_H_

#include "olcdatabasemgr.h"

namespace olc {

class OLCSubscriptionMgr {
public:
	OLCSubscriptionMgr();
	virtual ~OLCSubscriptionMgr();
	OLCSubscriptionMgr(const OLCSubscriptionMgr &other);
	OLCSubscriptionMgr(OLCSubscriptionMgr &&other);
	OLCSubscriptionMgr& operator=(const OLCSubscriptionMgr &other);
	OLCSubscriptionMgr& operator=(OLCSubscriptionMgr &&other);

public:
	/**
	 * @details : Function to initialize subscriptionmgr with databasemgr shared object
	 * @param inst : instance of databasemgr shared pointer
	 * @return
	 */
	err_t Initialize(std::shared_ptr<OLCDataBaseMgr>& inst);

	/**
	 * @details Function to Subscribe or Enroll to course
	 * @param cid : Course Id , To subscribe particular Course
	 * @param uid : User Id
	 * @return error enumeration
	 */
	err_t SubscribeCourse(course_id cid,usr_id uid);

	/**
	 * @details Function to Unsubscribe to course
	 * @param cid : Course Id , To unsubscribe particular Course
	 * @param uid : User Id
	 * @return error enumeration
	 */
	err_t UnSubscribeCourse(course_id cid,usr_id uid);

private:
	std::shared_ptr<OLCDataBaseMgr> mDBmgr;
};

} /* namespace olc */

#endif /* INCLUDE_OLCSUBSCRIPTIONMGR_H_ */
