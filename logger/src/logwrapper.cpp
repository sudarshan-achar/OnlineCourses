/*
 * logwrapper.cpp
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */

#include <iostream>
#include <unistd.h>
#include "logwrapper.h"
#include "loggerfile.h"


using namespace std;

ILogger      *LogWrapper::mpLogger     = NULL;
string          LogWrapper::mAppId       = "";
string          LogWrapper::mDescription = "";
LogStatus_e  LogWrapper::mLogStatus   = LS_ON;
LogService_e LogWrapper::mLogService  = DEFAULT_LOG_SERVICE;
string          LogWrapper::mFilename    = "";
bool            LogWrapper::mOnlyError   = false;

LogWrapper::LogWrapper(void)
{
}

ILogger *LogWrapper::instantiateOnce(const char *appid, const char *description,
    const LogStatus_e logStatus, const LogService_e logService,
    const string fileName, bool onlyError)
{
    if (mpLogger)
    {
        return mpLogger;
    }

    mAppId       = string(appid);
    mDescription = string(description);
    mLogStatus   = logStatus;
    mLogService  = logService;
    mFilename    = fileName;
    mOnlyError   = onlyError;
    return instance(mLogService);
}

ILogger *LogWrapper::instance(const LogService_e service)
{
    if (mpLogger)
    {
        return mpLogger;
    }

    switch (service)
    {
    case LOG_SERVICE_FILE:
        mpLogger = new LoggerFile(mLogStatus, mOnlyError, mFilename);
        break;
    default:
        break;
    }

    // an application seems not to use our LogWrapper class properly therefore create default context
    if ((mLogStatus == LS_ON) && mAppId.empty() && mDescription.empty())
    {
        mAppId = "AMDL";
        std::ostringstream description;
        description << "PID=" << getpid() << " _=" << getenv("_");
        mDescription = description.str().c_str();
        std::cerr << "Application doesn't call LogWrapper::instantiateOnce!!!" << std::endl;
        std::cerr << "-> LogWrapper::instance registers DLT application [ AMDL | " << description.str() << " ]" << std::endl;
    }

    mpLogger->registerApp(mAppId.c_str(), mDescription.c_str());

    return mpLogger;
}

LogWrapper::~LogWrapper()
{
    if (mpLogger)
    {
        mpLogger->unregisterApp();
        delete mpLogger;
    }
}

//}
