/*
 * iolc.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_IOLC_H_
#define TEMPLATES_IOLC_H_
#include "../include/olctypes.h"

namespace olc{

template<class T>
class IOlc{
public:
	IOlc();
	virtual ~IOlc();
	IOlc(const IOlc& interface);
	IOlc(IOlc&& interface)noexcept;
	IOlc& operator=(const IOlc& interface);
	IOlc& operator=(IOlc&& interface)noexcept;
public:
	virtual IOlc* GetInstance()=0;
	virtual err_t DisplayDetails()=0;
	virtual err_t SetData(T &&details)=0;
	virtual err_t AddToList(u_int_t id)=0;
	virtual err_t RemoveFromList(u_int_t id)=0;
	virtual T GetData()=0;
	virtual u_int_t GetId()=0;
};

template<class T>
inline IOlc<T>::IOlc() {
}

template<class T>
inline IOlc<T>::~IOlc() {
}

template<class T>
inline IOlc<T>::IOlc(const IOlc &interface) {
	*this=interface;
}

template<class T>
inline IOlc<T>::IOlc(IOlc &&interface)noexcept {
	*this=interface;
}

template<class T>
inline IOlc<T>& IOlc<T>::operator =(const IOlc &interface) {
	*this=interface;
	return *this;
}

template<class T>
inline IOlc<T>& IOlc<T>::operator =(IOlc &&interface)noexcept {
	*this=interface;
	return *this;
}

}//namespace olc
#endif /* TEMPLATES_IOLC_H_ */
