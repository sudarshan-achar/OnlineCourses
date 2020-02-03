/*
 * olcdatabaseimpl.h
 *
 *  Created on: 28-Jan-2020
 *      Author: sudarshan
 */

#ifndef DATABASE_OLCDATABASEIMPL_H_
#define DATABASE_OLCDATABASEIMPL_H_

#include "olctypes.h"
#include "../templates/olccourse.h"
#include "../templates/olcuser.h"
#include "../templates/olcvendor.h"

namespace olc{

template<class T>
class OLCDataBaseImpl{
public:
	OLCDataBaseImpl();
	virtual ~OLCDataBaseImpl();
	OLCDataBaseImpl(const OLCDataBaseImpl &other)=default;
	OLCDataBaseImpl(OLCDataBaseImpl &&other)noexcept=default;
	OLCDataBaseImpl& operator=(const OLCDataBaseImpl &other)=default;
	OLCDataBaseImpl& operator=(OLCDataBaseImpl &&other)noexcept=default;
public:
	err_t InsertToMap(T&& item);
	err_t RemoveFromMap(T&& item)noexcept;
	err_t DisplayAll();
	err_t ClearAll();
	err_t AddIdToList(u_int_t &&insertId, u_int_t &&objId);
	err_t RemoveIdFromList(u_int_t &&removeId, u_int_t &&objId);
	T GetById(u_int_t id);
	u_int_t GetListSize();
	std::unordered_map<u_int_t,T>* GetMap();
private:
	std::unordered_map<u_int_t,T> mMap;
};

template<class T>
inline OLCDataBaseImpl<T>::OLCDataBaseImpl() {
}

template<class T>
inline OLCDataBaseImpl<T>::~OLCDataBaseImpl() {
}

template<class T>
inline err_t OLCDataBaseImpl<T>::InsertToMap(T &&item) {
	auto id = item.GetId();
	mMap.emplace(std::make_pair(id,item));
	return NO_ERROR;
}

template<class T>
err_t OLCDataBaseImpl<T>::RemoveFromMap(T &&item)noexcept {
	if(mMap.size()!=0){
		for(auto &element:mMap){
			if(element.first==item.GetId()){
				mMap.erase(element.first);
			}
		}
		return NO_ERROR;
	}
	return NO_ELEMENTS;
}

template<class T>
err_t OLCDataBaseImpl<T>::DisplayAll() {
	if(mMap.size()!=0){
		for ( auto& element: mMap )
		{
			element.second.DisplayDetails();
		}
		return NO_ERROR;
	}
	return NO_ELEMENTS;
}

template<class T>
inline err_t OLCDataBaseImpl<T>::ClearAll() {
	if(mMap.size()!=0){
		mMap.clear();
		return NO_ERROR;
	}
	return NO_ELEMENTS;
}

template<class T>
T OLCDataBaseImpl<T>::GetById(u_int_t id) {
	if(mMap.size()!=0){
		for ( auto& element: mMap )
		{
			if(element.first==id)
			{
				return element.second;
			}
		}
	}
	T nullRet;
	nullRet.SetData({});
	return nullRet;
}

template<class T>
err_t OLCDataBaseImpl<T>::AddIdToList(u_int_t &&insertId, u_int_t &&objId) {
	if(mMap.size()!=0){
		for(auto& element:mMap){
			if(element.first==objId){
				(element.second).AddToList(insertId);
				return NO_ERROR;
			}
		}
		return NOT_FOUND;
	}
	return NO_ELEMENTS;
}

template<class T>
err_t OLCDataBaseImpl<T>::RemoveIdFromList(u_int_t &&removeId, u_int_t &&objId) {
	if(mMap.size()!=0){
		for(auto& element:mMap){
			if(element.first==objId){
				(element.second).RemoveFromList(removeId);
				return NO_ERROR;
			}
		}
		return NOT_FOUND;
	}
	return NO_ELEMENTS;
}

template<class T>
inline u_int_t OLCDataBaseImpl<T>::GetListSize() {
	return mMap.size();
}

template<class T>
inline std::unordered_map<u_int_t, T>* OLCDataBaseImpl<T>::GetMap() {
	return &mMap;
}

} //olc

#endif /* DATABASE_OLCDATABASEIMPL_H_ */
