/*
 * main.cpp
 *
 *  Created on: 28-Jan-2020
 *      Author: sudarshan
 *
 * Main program of the  project
 */

#include <iostream>
#include "include/olcinteractionmgr.h"
#include "include/olcsubscriptionmgr.h"
#include "include/olclistmgr.h"

using namespace olc;

int main() {

  std::cout << "\n\n\n * ************ ******* Welcome to Online courses portal "
               "******* ************ *\n\n\n\n";
  std::cout << "Enter the choices as follows\n\n";
  std::unique_ptr<OLCListMgr> olclistmgr = std::make_unique<OLCListMgr>();
  std::unique_ptr<OLCInteractionMgr> olcintmgr =
      std::make_unique<OLCInteractionMgr>();
  std::unique_ptr<OLCSubscriptionMgr>olcsubscriptmgr =
  	  std::make_unique<OLCSubscriptionMgr>();
  olclistmgr->CreateDataBase();
  olcintmgr->Initialize((olclistmgr->GetPointer()));
  olcsubscriptmgr->Initialize((olclistmgr->GetPointer()));

  int choice;
  while (true) {
    std::cout
        << "1-->Display available courses:\n"
        << "2-->Add Course:\n"
        << "3-->Remove Course:\n"
        << "4-->Clear All Courses\n"
        << "5-->Display Course details by Id\n"
        << "6-->To Find a course by specific title \n"
        << "7-->To Find all courses by a specific author\n"
        << "8-->To Find the average price of all courses\n"
        << "9-->To Find the minimum price among all courses by specific "
           "author\n"
        << "10-->To Enroll/Subscribe any course as a User\n"
        << "11-->To UnSubscribe any course as a User\n"
        << "12-->To Display enrolled users of a particular course\n"
        << "13-->To Display all courses that are enrolled by a specific user\n"
        << "14-->Exit\n";

    std::cin >> choice;

    switch (choice) {
      case 1: {
        if (olclistmgr->DisplayAvailabeCourses() == NO_ELEMENTS) {
          std::cout << "\n\n\n * ************ The course list is empty "
                       "************ *\n\n\n";
        }
        break;
      }
      case 2: {
        std::cout << "Enter the course details: \n\n";
        CourseDetails_t course;
        std::cout << "Enter the course name: \n";
        std::cin >> course.courseName;
        std::cout << "Enter the course Id: \n";
        std::cin >> course.courseId;
        std::cout << "Enter the Author name: \n";
        std::cin >> course.authorName;
        std::cout << "Enter the course price: \n";
        std::cin >> course.price;
        std::cout << "Enter the course Duration: \n";
        std::cin >> course.duration;
        std::cout << "Enter the course rating: \n";
        std::cin >> course.courseRating;
        olclistmgr->AddCourseToList(std::forward<CourseDetails_t>(course));
        break;
      }
      case 3: {
        std::cout << "Enter the course id to remove course\n";
        course_id cid;
        std::cin >> cid;
        if (olclistmgr->RemoveCourseFromList(std::forward<u_int_t>(cid)) == NO_ELEMENTS) {
          std::cout << "\n\n\n  ************* The course list is empty "
                       "*************\n\n\n";
        }
        break;
      }
      case 4: {
        if (olclistmgr->ClearAllCourses() == NO_ELEMENTS) {
          std::cout << "\n\n\n ************* The course list is already empty "
                       "*************\n\n\n";
        }
        break;
      }
      case 5: {
        std::cout << "Enter the course id to display course details\n";
        course_id cid;
        std::cin >> cid;
        switch (olclistmgr->DiplsyCourseDetailsById(std::forward<u_int_t>(cid))) {
          case NO_ELEMENTS: {
            std::cout << "\n\n\n  ************** The course list is empty "
                         "*************\n\n\n";
            break;
          }
          case NOT_FOUND: {
            std::cout << "\n\n\n  ************* The course is not found in the "
                         "list *************\n\n\n";
            break;
          }
          default:
            break;
        }
        break;
      }
      case 6: {
        std::cout << "\nEnter course title\n\n";
        str_t title;
        std::cin >> title;
        if (olcintmgr->DisplayCourseByTitle(std::forward<str_t>(title)) == NOT_FOUND) {
          std::cout << "\n\n\n  ************* No results found in the list "
                       "*************\n\n\n";
        }
      } break;
      case 7: {
        std::cout << "\nEnter author name\n\n";
        str_t authorname;
        std::cin >> authorname;
        if(olcintmgr->DisplayCourseByAuthor(std::forward<str_t>(authorname))==NOT_FOUND){
          std::cout << "\n\n\n  ************* No results found in the list "
        	           "*************\n\n\n";
        }
      } break;
      case 8: {
        std::cout << "\n";
        if(olcintmgr->DisplayAvgCoursePrice()==0){
        	std::cout<<"\n\n\n  ************* Check Inputs / Something went wrong with data"
        	                       "*************\n\n\n";
        }
      } break;
      case 9: {
        std::cout << "\nEnter author name\n\n";
        str_t authorname;
        std::cin >> authorname;
        if(olcintmgr->DisplayMinimumCoursePrice(std::forward<str_t>(authorname))==0){
        	std::cout<<"\n\n\n  ************* Check Inputs / Something went wrong with data"
                       "*************\n\n\n";
        }
      } break;
      case 10: {
    	  std::cout<<"Are you already an user ?....\nYES---> Y ......NO---> N\n";
    	  str_t ch;
    	  while(1){
    	  std::cin>>ch;
    	  if((ch=="N")||(ch=="n")){
    		  std::cout<<"\nEnter User details \n\n";
    		  UserDetails_t user;
    		  std::cout<<"User name (without space): \t";
    		  std::cin>>user.userName;
    		  std::cout<<"\nUser Id (Unique Id): \t";
    		  std::cin>>user.userId;
    		  std::cout<<"\nUser domain : \t";
    		  std::cin>>user.domain;
    		  std::cout<<"\nEnter Course Id to enroll \n\n";
    		  auto cid =0;
    		  std::cin>>cid;
    		  olcsubscriptmgr->RegisterUser(std::move(user));
    		  olcsubscriptmgr->SubscribeCourse(std::move(cid),std::move(user.userId));
    		  break;
    	  }else if((ch=="Y")||(ch=="y")){
    		  std::cout<<"\nEnter User Id to enroll \n\n";
    		  auto cid=0,uid=0;
    		  std::cin>>uid;
    		  std::cout<<"\nEnter Course Id to enroll \n\n";
    		  std::cin>>cid;
    		  olcsubscriptmgr->SubscribeCourse(std::move(cid),std::move(uid));
    		  break;
    	  }else{
    		  std::cout<<"\n\n....... Invalid choice ....\n\n";
    	  }
    	  }
      } break;
      case 11: {

      } break;
      case 14: {
        std::cout
            << "\n\n......................Thank You.....................!!\n\n";
        return 0;
      }
      default: { break; }
    }
  }
  return 0;
}
