/*
 * olcdatabaseimpl.h
 *
 *  Created on: 28-Jan-2020
 *      Author: sudarshan
 *  OLCDataBaseImpl: This template class is to implement the database operations
 *                   such as insert and delete, etc.
 */

#ifndef DATABASE_OLCDATABASEIMPL_H_
#define DATABASE_OLCDATABASEIMPL_H_

#include "olccourse.h"
#include "olcuser.h"
#include "olcvendor.h"
#include "olctypes.h"

namespace olc {

template <class T>
class OLCDataBaseImpl {
 public:
  OLCDataBaseImpl();
  virtual ~OLCDataBaseImpl();
  OLCDataBaseImpl(const OLCDataBaseImpl &other) = default;
  OLCDataBaseImpl(OLCDataBaseImpl &&other) noexcept = default;
  OLCDataBaseImpl &operator=(const OLCDataBaseImpl &other) = default;
  OLCDataBaseImpl &operator=(OLCDataBaseImpl &&other) noexcept = default;

 public:
  /**
   * @details Function to insert element to map
   * @param item : individual object
   * @return error enumeration
   */
  err_t InsertToMap(T &&item);

  /**
   * @details Function to insert element to map
   * @param item : individual object
   * @return error enumeration
   */
  err_t RemoveFromMap(T &&item) noexcept;

  /**
   * @details Function to display all the element details in the map.
   * @return error enumeration
   */
  err_t DisplayAll();

  /**
   * @details Function to clear particular map
   * @return error enumeration
   */
  err_t ClearAll();

  /**
   * @details Function to add id to subscription list
   * @param insertId : id to be added
   * @param objId    : id of object in which the insertId is to be added in the
   * list
   * @return error enumeration
   */
  err_t AddIdToList(u_int_t &&insertId, u_int_t &&objId);

  /**
   * @details Function to remove id to subscription list
   * @param removeId : id to be removed
   * @param objId    : id of object in which the removeId is to be removed from
   * the list
   * @return error enumeration
   */
  err_t RemoveIdFromList(u_int_t &&removeId, u_int_t &&objId);

  /**
   * @details Function to return element according to the id passed in.
   * @param id
   * @return structure
   */
  T GetById(u_int_t &&id);

  /**
   * @details Function to get Map size
   * @return Map size
   */
  u_int_t GetListSize();

  /**
   * @details Function to return pointer to  current map to the client
   * @return
   */
  std::unordered_map<u_int_t, T> *GetMap();

 private:
  /*!
   * Member which is an unordered_map to hold data list
   */
  std::unordered_map<u_int_t, T> mMap;
};

template <class T>
inline OLCDataBaseImpl<T>::OLCDataBaseImpl() {}

template <class T>
inline OLCDataBaseImpl<T>::~OLCDataBaseImpl() {}

template <class T>
inline err_t OLCDataBaseImpl<T>::InsertToMap(T &&item) {
  auto id = item.GetId();
  mMap.emplace(std::make_pair(id, item));
  return NO_ERROR;
}

template <class T>
err_t OLCDataBaseImpl<T>::RemoveFromMap(T &&item) noexcept {
  if (mMap.size() != 0) {
    for (auto &element : mMap) {
      if (element.first == item.GetId()) {
        mMap.erase(element.first);
        return NO_ERROR;
      }
    }
    return NOT_FOUND;
  }
  return NO_ELEMENTS;
}

template <class T>
err_t OLCDataBaseImpl<T>::DisplayAll() {
  if (mMap.size() != 0) {
    for (auto &element : mMap) {
      element.second.DisplayDetails();
    }
    return NO_ERROR;
  }
  return NO_ELEMENTS;
}

template <class T>
inline err_t OLCDataBaseImpl<T>::ClearAll() {
  if (mMap.size() != 0) {
    mMap.clear();
    return NO_ERROR;
  }
  return NO_ELEMENTS;
}

template <class T>
T OLCDataBaseImpl<T>::GetById(u_int_t &&id) {
  if (mMap.size() != 0) {
    for (auto &element : mMap) {
      if (element.first == id) {
        return element.second;
      }
    }
  }
  T nullRet;
  nullRet.SetData({});
  return nullRet;
}

template <class T>
err_t OLCDataBaseImpl<T>::AddIdToList(u_int_t &&insertId, u_int_t &&objId) {
  if (mMap.size() != 0) {
    for (auto &element : mMap) {
      if (element.first == objId) {
        (element.second).AddToList(insertId);
        return NO_ERROR;
      }
    }
    return NOT_FOUND;
  }
  return NO_ELEMENTS;
}

template <class T>
err_t OLCDataBaseImpl<T>::RemoveIdFromList(u_int_t &&removeId,
                                           u_int_t &&objId) {
  if (mMap.size() != 0) {
    std::cout << "\nEntered Remove\n";
    for (auto &element : mMap) {
      if (element.first == objId) {
        (element.second).RemoveFromList(removeId);
        return NO_ERROR;
      }
    }
    return NOT_FOUND;
  }
  return NO_ELEMENTS;
}

template <class T>
inline u_int_t OLCDataBaseImpl<T>::GetListSize() {
  return mMap.size();
}

template <class T>
inline std::unordered_map<u_int_t, T> *OLCDataBaseImpl<T>::GetMap() {
  return &mMap;
}

}  // olc

#endif /* DATABASE_OLCDATABASEIMPL_H_ */
