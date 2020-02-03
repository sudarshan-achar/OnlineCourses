/*
 * olcvendor.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_OLCVENDOR_H_
#define TEMPLATES_OLCVENDOR_H_
#include "iolc.h"

namespace olc{

template <class T>
class OlcVendor:public IOlc<T>{
public:
	OlcVendor();
	~OlcVendor();
	OlcVendor(const OlcVendor& vendor);
	OlcVendor(OlcVendor&& vendor)noexcept;
	OlcVendor& operator=(const OlcVendor& vendor);
	OlcVendor& operator=(OlcVendor&& vendor)noexcept;
public:
	IOlc<T>* GetInstance()override;
	err_t DisplayDetails()override;
	err_t SetData(T &&details)override;
	err_t AddToList(course_id id)override;
	err_t RemoveFromList(u_int_t id)override;
	T GetData()override;
	u_int_t GetId()override;
private:
	VendorDetails_t mVendorData;
	CourseIdList mList;
};

template<class T>
inline OlcVendor<T>::OlcVendor() {
}

template<class T>
inline OlcVendor<T>::~OlcVendor() {
}

template<class T>
inline OlcVendor<T>::OlcVendor(const OlcVendor &vendor) {
	mVendorData=vendor.mVendorData;
}

template<class T>
inline OlcVendor<T>::OlcVendor(OlcVendor &&vendor)noexcept {
	mVendorData=vendor.mVendorData;
	vendor.mVendorData={};
}

template<class T>
inline OlcVendor<T>& OlcVendor<T>::operator =(const OlcVendor &vendor) {
	mVendorData=vendor.mVendorData;
	return *this;
}

template<class T>
inline OlcVendor<T>& OlcVendor<T>::operator =(OlcVendor &&vendor)noexcept {
	mVendorData=vendor.mVendorData;
	vendor.mVendorData={};
	return *this;
}

template<class T>
inline IOlc<T>* OlcVendor<T>::GetInstance() {
	return this;
}

template<class T>
err_t OlcVendor<T>::DisplayDetails() {
	std::cout<<"\n";
	std::cout<<"Vendor full name :  "<<mVendorData.fullName<<"\n";
	std::cout<<"Vendor Id        :  "<<mVendorData.vendorId<<"\n";
	std::cout<<"Vendor DOB       :  "<<mVendorData.dateOfBirth<<"\n";
	std::cout<<"Vendor Domain    :  "<<mVendorData.domain<<"\n";
	std::cout<<"\n";
	return NO_ERROR;
}

template<class T>
inline  err_t OlcVendor<T>::SetData(T &&details) {
	mVendorData=details;
	return NO_ERROR;
}

template<class T>
inline T OlcVendor<T>::GetData() {
	return mVendorData;
}

template<class T>
inline err_t OlcVendor<T>::AddToList(course_id id) {
	mList.emplace_back(std::move(id));
	return NO_ERROR;
}

template<class T>
inline err_t OlcVendor<T>::RemoveFromList(u_int_t id) {
	for(auto &ele : mList){
		if(ele==id){
			mList.remove(id);
		}
	}
	return NO_ERROR;
}

template<class T>
inline u_int_t OlcVendor<T>::GetId() {
	return mVendorData.vendorId;
}

} //namespace olc

#endif /* TEMPLATES_OLCVENDOR_H_ */
