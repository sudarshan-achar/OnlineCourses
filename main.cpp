/*
 * main.cpp
 *
 *  Created on: 28-Jan-2020
 *      Author: sudarshan
 *
 * Main program of the  project
 */

#include<iostream>
#include "include/olcListMgr.h"
#include "include/olcInteractionMgr.h"

using namespace olc;

int main()
{
	std::cout<<"\n\n\n * ************ ******* Welcome to Online courses portal ******* ************ *\n\n\n\n";
	std::cout<<"Enter the choices as follows\n\n";
	OLCListMgr* olclistmgr=new OLCListMgr();
	OLCInteractionMgr* olcintmgr=new OLCInteractionMgr();
	olclistmgr->CreateDataBase();
	//olcintmgr->Initialize(std::forward<>(olclistmgr->GetPointer()));
	int choice;
	while(true)
	{
		std::cout<<"1-->Display available courses:\n"
				<<"2-->Add Course:\n"
				<<"3-->Remove Course:\n"
				<<"4-->Clear All Courses\n"
				<<"5-->Display Course details by Id\n"
				<<"6-->To Find a course by specific title \n"
				<<"7-->To Find all courses by a specific author\n"
				<<"8-->To Find the average price of all courses\n"
				<<"9-->To  Find the minimum price among all courses\n"
				<<"10-->Exit\n";
		std::cin>>choice;
		switch(choice)
		{
		case 1:{
			if(olclistmgr->DisplayAvailabeCourses()==NO_ELEMENTS){
				std::cout<<"\n\n\n * ************ The course list is empty ************ *\n\n\n";
			}
			break;
		}
		case 2:{
			std::cout<<"Enter the course details: \n\n";
			CourseDetails_t course;
			std::cout<<"Enter the course name: \n";
			std::cin>>course.courseName;
			std::cout<<"Enter the course Id: \n";
			std::cin>>course.courseId;
			std::cout<<"Enter the Author name: \n";
			std::cin>>course.authorName;
			std::cout<<"Enter the course price: \n";
			std::cin>>course.price;
			std::cout<<"Enter the course Duration: \n";
			std::cin>>course.duration;
			std::cout<<"Enter the course rating: \n";
			std::cin>>course.courseRating;
			olclistmgr->AddCourseToList(course);
			break;
		}
		case 3:{
			std::cout<<"Enter the course id to remove course\n";
			course_id cid;
			std::cin>>cid;
			if(olclistmgr->RemoveCourseFromList(cid)==NO_ELEMENTS){
				std::cout<<"\n\n\n  ************* The course list is empty *************\n\n\n";
			}
			break;
		}
		case 4:{
			if(olclistmgr->ClearAllCourses()==NO_ELEMENTS){
				std::cout<<"\n\n\n ************* The course list is already empty *************\n\n\n";
			}
			break;
		}
		case 5:{
			std::cout<<"Enter the course id to display course details\n";
			course_id cid;
			std::cin>>cid;
			switch(olclistmgr->DiplsyCourseDetailsById(cid)){
			case NO_ELEMENTS:{
				std::cout<<"\n\n\n  ************** The course list is empty *************\n\n\n";
				break;
			}
			case NOT_FOUND:{
				std::cout<<"\n\n\n  ************* The course is not found in the list *************\n\n\n";
				break;
			}
			default:break;
			}
			break;
		}
		case 6:{
			std::cout<<"Enter course title\n";
			str_t title;
			std::cin>>title;
			olcintmgr->DisplayCourseByTitle(title);
		}
		break;
		case 7:{
			std::cout<<"Enter author name\n";
			str_t authorname;
			std::cin>>authorname;
			olcintmgr->DisplayCourseByAuthor(authorname);
		}
		break;
		case 8:{
			olcintmgr->DisplayAvgCoursePrice();
		}
		break;
		case 9:{
			olcintmgr->DisplayMinimumCoursePrice();
		}
		break;
		case 10:{
			std::cout<<"\n\n...............Thank You.............!!\n\n";
			delete olclistmgr;
			olclistmgr = nullptr;
			return 0;
		}
		default :{
			break;
		}
		}
	}
	return 0;
}


