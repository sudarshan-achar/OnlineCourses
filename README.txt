Project Name   :  Online Courses 
olc            :  Namespace used in project, this refers to online courses (package)

main.cpp       :  Client Source file 

All Classes and their responsibilitis:

IOlc<T>        :  Basic Template interface used to give functionalities for individual course, user or vendor.
OlcCourse      :  This template class will contain the data of single course at a time, and functions to perform some operations on single course.
OlcUser        :  This template class will contain the data of single user at a time, and functions to perform operations on it.
OlcVendor      :  This template class will contain the data of single vendor at a time, and functions to perform operations on it.
  
OLCListMgr        :  This class will manage the operations and mappings on Course list. Specifically operations like add, remove courses to/from list.
OLCSubscriptionMgr:  This class will manage user related needs like subscribe, unsubscribe specific courses in future sign in related...etc... 
OLCInteractionMgr :  This class will manage to answer user/vendors queiries ,interactions to database.
OLCDatabaseMgr    :  This class will manage to perform different database entries and needs related to database.

OLCDatabaseImpl<T>:  This is template class wich performs all the database entry and deletion operations.
OLCDatabaseClient :  This class is the direct client to Database implementation. This class holds the different unique pointers to OLCDatabaseImpl<T> template class. 
 
To build and run the code:

Follow easy cmake method. The project source folder is having a main.cpp and a CMakeLists.txt.
Create folder with name "build" inside project source folder open terminal inside "build".

Run --> commonds as follows

	cmake ../
	make
	./olcproject
		
