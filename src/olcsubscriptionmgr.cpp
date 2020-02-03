/*
 * olcSubscriptionMgr.cpp
 *
 *  Created on: 19-Jan-2020
 *      Author: sudarshan
 */

#include "olcSubscriptionMgr.h"

namespace olc {

OLCSubscriptionMgr::OLCSubscriptionMgr() {
	// TODO Auto-generated constructor stub
}

OLCSubscriptionMgr::~OLCSubscriptionMgr() {
	// TODO Auto-generated destructor stub
}

OLCSubscriptionMgr::OLCSubscriptionMgr(const OLCSubscriptionMgr &other) {
	// TODO Auto-generated constructor stub
}

OLCSubscriptionMgr::OLCSubscriptionMgr(OLCSubscriptionMgr &&other) {
	// TODO Auto-generated constructor stub
}

OLCSubscriptionMgr& OLCSubscriptionMgr::operator=(const OLCSubscriptionMgr &other) {
	// TODO Auto-generated method stub
	*this=other;
	return *this;
}

OLCSubscriptionMgr& OLCSubscriptionMgr::operator=(OLCSubscriptionMgr &&other) {
	// TODO Auto-generated method stub
	*this=other;
	return *this;
}

err_t OLCSubscriptionMgr::Initialize(std::shared_ptr<OLCDataBaseMgr> &inst) {
	mDBmgr=inst;
	return NO_ERROR;
}
err_t OLCSubscriptionMgr::SubscribeCourse(course_id cid ,usr_id uid) {
	if(mDBmgr!=nullptr)return mDBmgr->SubscribeCourse(cid,uid);
	return NULL_PTR;
}

err_t OLCSubscriptionMgr::UnSubscribeCourse(course_id cid, usr_id uid) {
	if(mDBmgr!=nullptr)return mDBmgr->UnsubscribeCourse(cid,uid);
	return NULL_PTR;
}

} /* namespace olc */
