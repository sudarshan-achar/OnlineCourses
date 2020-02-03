/*
 * olcuser.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 *     OlcUser: This is a template class inherits functionalities from IOlc
 *              interface.This class is to hold the single user data and manage
 *              operations on it at a time.
 */

#ifndef TEMPLATES_OLCUSER_H_
#define TEMPLATES_OLCUSER_H_
#include "iolc.h"

namespace olc {

template <class T>
class OlcUser : public IOlc<T> {
 public:
  OlcUser();
  ~OlcUser();
  OlcUser(const OlcUser& user);
  OlcUser(OlcUser&& user) noexcept;
  OlcUser& operator=(const OlcUser& user);
  OlcUser& operator=(OlcUser&& user) noexcept;

 public:
  /**
   * @details Function to get pointer to instance of OlcUser class
   * @return pointer to instance of OlcUser class
   */
  IOlc<T>* GetInstance() override;

  /**
   * @details Function to Display details of this particular user
   * @return error enumeration
   */
  err_t DisplayDetails() override;

  /**
   * @details Function to set data
   * @param details : user details structure to set data to this object
   * @return
   */
  err_t SetData(T&& details) override;

  /**
   * @details Function to add course id to the list to track subscription
   * @param id : course id
   * @return
   */
  err_t AddToList(course_id id) override;

  /**
   * @details Function to remove course id from the list to track subscription
   * @param id :course id
   * @return
   */
  err_t RemoveFromList(u_int_t id) override;

  /**
   * @details Function to return user data structure to the client
   * @return user details data structure
   */
  T GetData() override;

  /**
   * @details Function to return User id to client
   * @return
   */
  u_int_t GetId() override;

 private:
  /*!
   * Member variable of type UserDetails_t structure to hold the current user
   * data
   */
  UserDetails_t mUserData;

  /*!
   *  Member variable of type CourseIdList is list to hold the course ids.
   */
  CourseIdList mList;
};

//** Implementation **//

template <class T>
inline OlcUser<T>::OlcUser() {}

template <class T>
inline OlcUser<T>::~OlcUser() {}

template <class T>
inline OlcUser<T>::OlcUser(const OlcUser& user) {
  mUserData = user.mUserData;
}

template <class T>
inline OlcUser<T>::OlcUser(OlcUser&& user) noexcept {
  mUserData = user.mUserData;
  user.mUserData = {};
}

template <class T>
inline OlcUser<T>& OlcUser<T>::operator=(const OlcUser& user) {
  mUserData = user.mUserData;
  return *this;
}

template <class T>
inline OlcUser<T>& OlcUser<T>::operator=(OlcUser&& user) noexcept {
  mUserData = user.mUserData;
  user.mUserData = {};
  return *this;
}

template <class T>
inline IOlc<T>* OlcUser<T>::GetInstance() {
  return this;
}

template <class T>
err_t OlcUser<T>::DisplayDetails() {
  std::cout << "\n";
  std::cout << "User full name :  " << mUserData.fullName << "\n";
  std::cout << "User Id        :  " << mUserData.userId << "\n";
  std::cout << "User DOB       :  " << mUserData.dateOfBirth << "\n";
  std::cout << "User Domain    :  " << mUserData.domain << "\n";
  std::cout << "\n";
  return NO_ERROR;
}

template <class T>
inline err_t OlcUser<T>::SetData(T&& details) {
  mUserData = details;
  return NO_ERROR;
}

template <class T>
inline T OlcUser<T>::GetData() {
  return mUserData;
}

template <class T>
inline err_t OlcUser<T>::AddToList(course_id id) {
  mList.emplace_back(std::move(id));
  return NO_ERROR;
}

template <class T>
err_t OlcUser<T>::RemoveFromList(u_int_t id) {
  for (auto& ele : mList) {
    if (ele == id) {
      mList.remove(id);
    }
  }
  return NO_ERROR;
}

template <class T>
inline u_int_t OlcUser<T>::GetId() {
  return mUserData.userId;
}

}  // olc namespace

#endif /* TEMPLATES_OLCUSER_H_ */
