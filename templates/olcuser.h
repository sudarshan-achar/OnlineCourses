/*
 * olcuser.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_OLCUSER_H_
#define TEMPLATES_OLCUSER_H_
#include "iolc.h"

namespace olc{

template <class T>
class OlcUser:public IOlc<T> {
public:
	OlcUser();
	~OlcUser();
	OlcUser(const OlcUser& user);
	OlcUser(OlcUser&& user)noexcept;
	OlcUser& operator=(const OlcUser& user);
	OlcUser& operator=(OlcUser&& user)noexcept;
public:
	IOlc<T>* GetInstance()override;
	err_t DisplayDetails()override;
	err_t SetData(T &&details)override;
	err_t AddToList(course_id id)override;
	err_t RemoveFromList(u_int_t id)override;
	T GetData()override;
	u_int_t GetId()override;
private:
	UserDetails_t mUserData;
	CourseIdList mList;
};

template<class T>
inline OlcUser<T>::OlcUser() {
}

template<class T>
inline OlcUser<T>::~OlcUser() {
}

template<class T>
inline OlcUser<T>::OlcUser(const OlcUser &user) {
	mUserData=user.mUserData;
}

template<class T>
inline OlcUser<T>::OlcUser(OlcUser &&user)noexcept {
	mUserData=user.mUserData;
	user.mUserData={};
}

template<class T>
inline OlcUser<T>& OlcUser<T>::operator =(const OlcUser &user) {
	mUserData=user.mUserData;
	return *this;
}

template<class T>
inline OlcUser<T>& OlcUser<T>::operator =(OlcUser &&user)noexcept {
	mUserData=user.mUserData;
	user.mUserData={};
	return *this;
}

template<class T>
inline IOlc<T>* OlcUser<T>::GetInstance() {
	return this;
}

template<class T>
err_t OlcUser<T>::DisplayDetails() {
	std::cout<<"\n";
	std::cout<<"User full name :  "<<mUserData.fullName<<"\n";
	std::cout<<"User Id        :  "<<mUserData.userId<<"\n";
	std::cout<<"User DOB       :  "<<mUserData.dateOfBirth<<"\n";
	std::cout<<"User Domain    :  "<<mUserData.domain<<"\n";
	std::cout<<"\n";
	return NO_ERROR;
}

template<class T>
inline err_t OlcUser<T>::SetData(T &&details) {
	mUserData=details;
	return NO_ERROR;
}

template<class T>
inline T OlcUser<T>::GetData() {
	return mUserData;
}

template<class T>
inline err_t OlcUser<T>::AddToList(course_id id) {
	mList.emplace_back(std::move(id));
	return NO_ERROR;
}

template<class T>
inline err_t OlcUser<T>::RemoveFromList(u_int_t id) {
	for(auto &ele : mList){
		if(ele==id){
			mList.remove(id);
		}
	}
	return NO_ERROR;
}

template<class T>
inline u_int_t OlcUser<T>::GetId() {
	return mUserData.userId;
}

} //olc namespace

#endif /* TEMPLATES_OLCUSER_H_ */
