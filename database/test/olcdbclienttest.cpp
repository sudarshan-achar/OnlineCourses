/*
 * olcdbclienttest.cpp
 *
 *  Created on: 18-Mar-2020
 *      Author: sudarshan
 */

#include <limits.h>
#include "gtest/gtest.h"
#include "../olcdatabaseclient.h"

using namespace olc;

class OLCDataBaseClientTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		logInfo("OLCDataBaseClientTest : SetUp()");
	}

	virtual void TearDown() {
		logInfo("OLCDataBaseClientTest : TearDown()");
		// Code here will be called immediately after each test
		// (right before the destructor).
	}
};

TEST_F(OLCDataBaseClientTest,Creat_Maps_tets){
	OLCDatabaseClient databaseclient;
	EXPECT_EQ(NO_ERROR,databaseclient.CreateLists());
}

TEST_F(OLCDataBaseClientTest,Map_operations_course){
	OLCDatabaseClient databaseclient;
	databaseclient.CreateLists();

	course_details_t course;
	course.authorName="Suarshan";
	course.courseId=1234;
	course.courseName="C++";

	EXPECT_EQ(NO_ERROR,databaseclient.AddCourseToMap(std::move(course)));
	EXPECT_EQ(NOT_FOUND,databaseclient.RemoveCourseFromMap(std::move(34)));
	EXPECT_EQ(NO_ERROR,databaseclient.RemoveCourseFromMap(std::move(course.courseId)));
	EXPECT_EQ(NO_ELEMENTS,databaseclient.RemoveCourseFromMap(std::move(course.courseId)));
}

TEST_F(OLCDataBaseClientTest,Map_operations_user){
	OLCDatabaseClient databaseclient;
	databaseclient.CreateLists();

	user_details_t user;
	user.userName="Author";
	user.userId=1234;

	EXPECT_EQ(NO_ERROR,databaseclient.AddUserToMap(std::move(user)));
	EXPECT_EQ(NOT_FOUND,databaseclient.RemoveUserFromMap(std::move(34)));
	EXPECT_EQ(NO_ERROR,databaseclient.RemoveUserFromMap(std::move(user.userId)));
	EXPECT_EQ(NO_ELEMENTS,databaseclient.RemoveCourseFromMap(std::move(user.userId)));
}

