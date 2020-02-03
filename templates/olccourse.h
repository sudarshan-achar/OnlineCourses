/*
 * olccourse.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_OLCCOURSE_H_
#define TEMPLATES_OLCCOURSE_H_
#include "iolc.h"

namespace olc{

template <class T>
class OlcCourse:public IOlc<T>{
public:
	OlcCourse();
	~OlcCourse();
	OlcCourse(const OlcCourse& course);
	OlcCourse(OlcCourse&& course)noexcept;
	OlcCourse& operator=(const OlcCourse& course);
	OlcCourse& operator=(OlcCourse&& course)noexcept;
public:
	IOlc<T>* GetInstance()override;
	err_t DisplayDetails()override;
	err_t SetData(T&& details)override;
	err_t AddToList(course_id id)override;
	err_t RemoveFromList(u_int_t id)override;
	T GetData()override;
	u_int_t GetId()override;
private:
	CourseDetails_t mCourseData;
	UserIdList mList;
};

template<class T>
inline OlcCourse<T>::OlcCourse() {
}

template<class T>
inline OlcCourse<T>::~OlcCourse() {
}

template<class T>
inline OlcCourse<T>::OlcCourse(const OlcCourse &course) {
	mCourseData=course.mCourseData;
}

template<class T>
inline OlcCourse<T>::OlcCourse(OlcCourse &&course)noexcept {
	mCourseData=course.mCourseData;
	course.mCourseData={};
}

template<class T>
inline OlcCourse<T>& OlcCourse<T>::operator =(const OlcCourse &course) {
	mCourseData=course.mCourseData;
	return *this;
}

template<class T>
inline OlcCourse<T>& OlcCourse<T>::operator =(OlcCourse &&course)noexcept {
	mCourseData=course.mCourseData;
	course.mCourseData={};
	return *this;
}

template<class T>
inline IOlc<T>* OlcCourse<T>::GetInstance() {
	return this;
}

template<class T>
inline err_t OlcCourse<T>::DisplayDetails() {
	std::cout<<"\n";
	std::cout<<"The Course Details Are \n";
	std::cout<<"Course Name     --> "<<mCourseData.courseName<<"\n";
	std::cout<<"Course Id       --> "<<mCourseData.courseId<<"\n";
	std::cout<<"Author name     --> "<<mCourseData.authorName<<"\n";
	std::cout<<"Course price    --> "<<mCourseData.price<<" Rs.\n";
	std::cout<<"Course duration --> "<<mCourseData.duration<<" Weeks.\n";
	std::cout<<"Course rating   --> "<<mCourseData.courseRating<<"% \n";
	std::cout<<"\n";
	return NO_ERROR;
}

template<class T>
inline err_t OlcCourse<T>::SetData(T&& details) {
	mCourseData=details;
	return NO_ERROR;
}

template<class T>
inline T OlcCourse<T>::GetData() {
	return mCourseData;
}

template<class T>
inline err_t OlcCourse<T>::AddToList(course_id id) {
	mList.emplace_back(std::move(id));
	return NO_ERROR;
}

template<class T>
inline err_t OlcCourse<T>::RemoveFromList(u_int_t id) {
	for(auto &ele : mList){
		if(ele==id){
			mList.remove(id);
		}
	}
	return NO_ERROR;
}

template<class T>
inline u_int_t OlcCourse<T>::GetId() {
	return mCourseData.courseId;
}

} //namespace olc

#endif /* TEMPLATES_OLCCOURSE_H_ */
