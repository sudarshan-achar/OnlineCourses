/*
 * iolc.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_IOLC_H_
#define TEMPLATES_IOLC_H_
#include "../include/olctypes.h"

namespace olc {

template <class T>
class IOlc {
 public:
  /**
   * Simple constructor
   */
  IOlc();

  /**
   * virtual Destructor
   */
  virtual ~IOlc();

  /**
   * Copy constructors
   * @param interface
   */
  IOlc(const IOlc& interface);

  /**
   * Move constructors
   * @param interface
   */
  IOlc(IOlc&& interface) noexcept;

  /**
   * Copy assignment operator
   * @param interface
   * @return
   */
  IOlc& operator=(const IOlc& interface);

  /**
   * Move assignment operator
   * @param interface
   * @return
   */
  IOlc& operator=(IOlc&& interface) noexcept;

 public:
  /**
   * Function to return pointer to current instance to client class
   * @return
   */
  virtual IOlc* GetInstance() = 0;

  /**
   * Function to display current class details
   * @return error enumeration
   */
  virtual err_t DisplayDetails() = 0;

  /**
   * Function to set details
   * @param details
   * @return error enumeration
   */
  virtual err_t SetData(T&& details) = 0;

  /**
   * Function to add ids to the list to maintain the subscription details
   * @param id
   * @return error enumeration
   */
  virtual err_t AddToList(u_int_t id) = 0;

  /**
   * Function to Remove id from list to maintain the subscription details
   * @param id
   * @return error enumeration
   */
  virtual err_t RemoveFromList(u_int_t id) = 0;

  /**
   * Function to return current details
   * @return error enumeration
   */
  virtual T GetData() const = 0;

  /**
   * Function to return respective id associated with current object
   * @return id
   */
  virtual u_int_t GetId() const = 0;

  /**
   * Function to return pointer to respective subscribers id list
   * @return list of type std::list<u_int_t>
   */
  virtual generic_list_t* GetList() = 0;
};

template <class T>
inline IOlc<T>::IOlc() {}

template <class T>
inline IOlc<T>::~IOlc() {}

template <class T>
inline IOlc<T>::IOlc(const IOlc& interface) {
  *this = interface;
}

template <class T>
inline IOlc<T>::IOlc(IOlc&& interface) noexcept {
  *this = interface;
}

template <class T>
inline IOlc<T>& IOlc<T>::operator=(const IOlc& interface) {
  *this = interface;
  return *this;
}

template <class T>
inline IOlc<T>& IOlc<T>::operator=(IOlc&& interface) noexcept {
  *this = interface;
  return *this;
}

}  // namespace olc
#endif /* TEMPLATES_IOLC_H_ */
