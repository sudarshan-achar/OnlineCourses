/*
 * test.cpp
 *
 *  Created on: 24-Mar-2020
 *      Author: sudarshan
 */

#include <limits.h>
#include "gtest/gtest.h"
#include "logwrapper.h"

# define APPLICATION_ID "APP"
# define APP_DESCRIPTION "AppName"

int main(int argc, char **argv) {

	const std::string filename= "/tmp/olclog.log";

	//to instantiate the log file
	LogWrapper::instantiateOnce(APPLICATION_ID, APP_DESCRIPTION
			, LogStatus_e::LS_ON,LogService_e::LOG_SERVICE_FILE
			, filename);

	logInfo("The logs starts here..............");
	logInfo("File name is ::  ",filename);

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

