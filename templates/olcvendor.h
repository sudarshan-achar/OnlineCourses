/*
 * olcvendor.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_OLCVENDOR_H_
#define TEMPLATES_OLCVENDOR_H_
#include "iolc.h"

namespace olc {

template <class T>
class OlcVendor : public IOlc<T> {
 public:
  OlcVendor();
  ~OlcVendor();
  OlcVendor(const OlcVendor& vendor);
  OlcVendor(OlcVendor&& vendor) noexcept;
  OlcVendor& operator=(const OlcVendor& vendor);
  OlcVendor& operator=(OlcVendor&& vendor) noexcept;

 public:
  /**
   * @details Function to return current instance
   * @return Pointer to current instance
   */
  IOlc<T>* GetInstance() override;

  /**
   * @details Function to display details of current instance
   * @return error enumeration
   */
  err_t DisplayDetails() override;

  /**
   * @details Function to Set the details
   * @param details : vendor details to set member
   * @return error enumeration
   */
  err_t SetData(T&& details) override;

  /**
   * @details Function to Add id to list
   * @param id : Particular course Id to add to list
   * @return error enumeration
   */
  err_t AddToList(course_id id) override;

  /**
   * @details Function to Remove id from the list
   * @param id :  Particular course Id to remove from list
   * @return error enumeration
   */
  err_t RemoveFromList(course_id id) override;

  /**
   * @details Function to Get the vendor data
   * @return vendor_details_t structure
   */
  T GetData() const override;

  /**
   * @details Function to Get Id of current vendor
   * @return vendor_id
   */
  u_int_t GetId() const override;

  /**
   * @details Function to return pointer to respective subscribers id list
   * @return pointer to list of user ids
   */
  generic_list_t* GetList() override;

 private:
  vendor_details_t mVendorData;
  course_id_list_t mList;
};

template <class T>
inline OlcVendor<T>::OlcVendor() {}

template <class T>
inline OlcVendor<T>::~OlcVendor() {}

template <class T>
inline OlcVendor<T>::OlcVendor(const OlcVendor& vendor) {
  mVendorData = vendor.mVendorData;
}

template <class T>
inline OlcVendor<T>::OlcVendor(OlcVendor&& vendor) noexcept {
  mVendorData = vendor.mVendorData;
  vendor.mVendorData = {};
}

template <class T>
inline OlcVendor<T>& OlcVendor<T>::operator=(const OlcVendor& vendor) {
  mVendorData = vendor.mVendorData;
  return *this;
}

template <class T>
inline OlcVendor<T>& OlcVendor<T>::operator=(OlcVendor&& vendor) noexcept {
  mVendorData = vendor.mVendorData;
  vendor.mVendorData = {};
  return *this;
}

template <class T>
inline IOlc<T>* OlcVendor<T>::GetInstance() {
  return this;
}

template <class T>
err_t OlcVendor<T>::DisplayDetails() {
  std::cout << "\n";
  if (mVendorData.fullName != "")
    std::cout << "Vendor full name :  " << mVendorData.fullName << "\n";
  std::cout << "Vendor Id        :  " << mVendorData.vendorId << "\n";
  if (mVendorData.dateOfBirth != "")
    std::cout << "Vendor DOB       :  " << mVendorData.dateOfBirth << "\n";
  if (mVendorData.domain != "")
    std::cout << "Vendor Domain    :  " << mVendorData.domain << "\n";
  std::cout << "\n";
  return NO_ERROR;
}

template <class T>
inline err_t OlcVendor<T>::SetData(T&& details) {
  mVendorData = details;
  return NO_ERROR;
}

template <class T>
inline T OlcVendor<T>::GetData() const {
  return mVendorData;
}

template <class T>
inline err_t OlcVendor<T>::AddToList(course_id id) {
  mList.emplace_back(std::move(id));
  return NO_ERROR;
}

template <class T>
inline err_t OlcVendor<T>::RemoveFromList(u_int_t id) {
  mList.remove(std::move(id));
  return NO_ERROR;
}

template <class T>
inline u_int_t OlcVendor<T>::GetId() const {
  return mVendorData.vendorId;
}

template <class T>
inline generic_list_t* OlcVendor<T>::GetList() {
  return &mList;
}

}  // namespace olc

#endif /* TEMPLATES_OLCVENDOR_H_ */
