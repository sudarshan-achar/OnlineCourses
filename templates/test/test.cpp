/*
 * main.cpp
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */
#include "../iolc.h"
#include "../olccourse.h"
#include "../olcuser.h"
#include "../olcvendor.h"

using namespace olc;

int main()
{
	CourseDetails_t course={123,"c++11","sudarshan","rajesh",12,1200,58};
	auto iolc = std::make_unique<OlcCourse<CourseDetails_t>>();
	iolc->SetData(std::forward<CourseDetails_t>(course));
	iolc->DisplayDetails();

	UserDetails_t user={111,"sudarshan","Sudarshan Acharya","25-05-1997","science"};
	auto userPtr=std::make_unique<OlcUser<UserDetails_t>>();
	userPtr->SetData(std::forward<UserDetails_t>(user));
	userPtr->DisplayDetails();

	VendorDetails_t vendor={112,"unKnown","Unknown Acharya","05-09-1999","science"};
	auto vendorPtr=std::make_unique<OlcVendor<VendorDetails_t>>();
	vendorPtr->SetData(std::forward<VendorDetails_t>(vendor));
	vendorPtr->DisplayDetails();

	auto insta=vendorPtr->GetInstance();
	insta->SetData(std::move(vendor));
	insta->DisplayDetails();

	auto instUser=userPtr->GetInstance();
	instUser->SetData(std::move(user));
	instUser->DisplayDetails();

	auto instCourse=iolc->GetInstance();
	instCourse->SetData(std::move(course));
	instCourse->DisplayDetails();

	OlcCourse<CourseDetails_t> oc;
	oc.SetData(std::move(course));
	oc.DisplayDetails();

	OlcCourse<CourseDetails_t> dc(oc);
	dc.DisplayDetails();

	OlcCourse<CourseDetails_t> fc;
	fc=std::move(dc);
	fc.DisplayDetails();
	dc.DisplayDetails();
	return 0;
}



