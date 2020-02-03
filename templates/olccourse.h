/*
 * olccourse.h
 *
 *  Created on: 26-Jan-2020
 *      Author: sudarshan
 */

#ifndef TEMPLATES_OLCCOURSE_H_
#define TEMPLATES_OLCCOURSE_H_
#include "iolc.h"

namespace olc {

template <class T>
class OlcCourse : public IOlc<T> {
 public:
  OlcCourse();
  ~OlcCourse();
  OlcCourse(const OlcCourse& course);
  OlcCourse(OlcCourse&& course) noexcept;
  OlcCourse& operator=(const OlcCourse& course);
  OlcCourse& operator=(OlcCourse&& course) noexcept;

 public:
  /**
   * @details Function to get pointer to instance of OlcCourse class
   * @return pointer to instance of OlcCourse class
   */
  IOlc<T>* GetInstance() override;

  /**
   * @details Function to Display details of this particular course
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
   * @details Function to add user id to the list to track subscription
   * @param id :
   * @return
   */
  err_t AddToList(course_id id) override;

  /**
   * @details Function to remove user id from the list to track subscription
   * @param id
   * @return
   */
  err_t RemoveFromList(u_int_t id) override;

  /**
   * @details Function to return course data structure to the client
   * @return error enumeration
   */
  T GetData() override;

  /**
   * @details Function to return course id to the client
   * @return Course id
   */
  u_int_t GetId() override;

 private:
  CourseDetails_t mCourseData;
  UserIdList mList;
};

//** Implementation **//

template <class T>
inline OlcCourse<T>::OlcCourse() {}

template <class T>
inline OlcCourse<T>::~OlcCourse() {}

template <class T>
inline OlcCourse<T>::OlcCourse(const OlcCourse& course) {
  mCourseData = course.mCourseData;
}

template <class T>
inline OlcCourse<T>::OlcCourse(OlcCourse&& course) noexcept {
  mCourseData = course.mCourseData;
  course.mCourseData = {};
}

template <class T>
inline OlcCourse<T>& OlcCourse<T>::operator=(const OlcCourse& course) {
  mCourseData = course.mCourseData;
  return *this;
}

template <class T>
inline OlcCourse<T>& OlcCourse<T>::operator=(OlcCourse&& course) noexcept {
  mCourseData = course.mCourseData;
  course.mCourseData = {};
  return *this;
}

template <class T>
inline IOlc<T>* OlcCourse<T>::GetInstance() {
  return this;
}

template <class T>
inline err_t OlcCourse<T>::DisplayDetails() {
  std::cout << "\n";
  std::cout << "The Course Details Are \n";
  std::cout << "Course Name     --> " << mCourseData.courseName << "\n";
  std::cout << "Course Id       --> " << mCourseData.courseId << "\n";
  std::cout << "Author name     --> " << mCourseData.authorName << "\n";
  std::cout << "Course price    --> " << mCourseData.price << " Rs.\n";
  std::cout << "Course duration --> " << mCourseData.duration << " Weeks.\n";
  std::cout << "Course rating   --> " << mCourseData.courseRating << "% \n";
  std::cout << "\n";
  return NO_ERROR;
}

template <class T>
inline err_t OlcCourse<T>::SetData(T&& details) {
  mCourseData = details;
  return NO_ERROR;
}

template <class T>
inline T OlcCourse<T>::GetData() {
  return mCourseData;
}

template <class T>
inline err_t OlcCourse<T>::AddToList(course_id id) {
  mList.emplace_back(std::move(id));
  return NO_ERROR;
}

template <class T>
err_t OlcCourse<T>::RemoveFromList(u_int_t id) {
  for (auto& ele : mList) {
    if (ele == id) {
      mList.remove(id);
    }
  }
  return NO_ERROR;
}

template <class T>
inline u_int_t OlcCourse<T>::GetId() {
  return mCourseData.courseId;
}

}  // namespace olc

#endif /* TEMPLATES_OLCCOURSE_H_ */
