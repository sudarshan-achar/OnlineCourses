/*
 * logwrapper.h
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */


#ifndef LOGWRAPPER_H_
#define LOGWRAPPER_H_

#include "pthread.h"
#include "ilogger.h"
#include "loggertypes.h"

/**
 * This class is instantiated as a singleton and offers logging to a default context (maincontext).
 * Logging under the default context can simply be done with the logDebug/logInfo/logError/logWarning/logVerbose
 * templates. For logging with a different context, you need to register a context with registerContext,
 * method provided by backends implementing the ILogger interface. registerContext returns a logging context.
 * To import this context into other classes use importContext, method provided by backends implementing the ILogger
 * interface. To access the ILogger interface, simply ask LogWrapper::instance().
 */
class LogWrapper
{
public:
    static ILogger *instantiateOnce(const char *appid, const char *description,
        const LogStatus_e logStatus = LS_ON, const LogService_e logService = DEFAULT_LOG_SERVICE,
        const std::string Filename = "", bool onlyError = false);
    static ILogger *instance(const LogService_e logservice = DEFAULT_LOG_SERVICE);

    inline static LogService_e getLogService()
    {
        return mLogService;
    }

    virtual ~LogWrapper();

private:
    LogWrapper(void);             //!< is private because of singleton pattern
    static ILogger      *mpLogger; //!< pointer to the logger instance
    static std::string     mAppId;
    static std::string     mDescription;
    static LogStatus_e  mLogStatus;
    static LogService_e mLogService;
    static std::string     mFilename;
    static bool            mOnlyError;
};

/**
 * returns the instance of instantiated ILogger
 * @return
 */
inline ILogger *getLogger()
{
    return (LogWrapper::instance(LogWrapper::getLogService()));
}

/**
 * logs given values with debuglevel with the default context
 * @param value
 * @param ...
 */
template<typename T, typename... TArgs>
void logDebug(const T &value, const TArgs & ... args)
{
    getLogger()->logToDefaultContext(LL_DEBUG, value, args...);
}

/**
 * logs given values with infolevel with the default context
 * @param value
 * @param ...
 */
template<typename T, typename... TArgs>
void logInfo(const T &value, const TArgs & ... args)
{
    getLogger()->logToDefaultContext(LL_INFO, value, args...);
}

/**
 * logs given values with errorlevel with the default context
 * @param value
 * @param ...
 */
template<typename T, typename... TArgs>
void logError(const T &value, const TArgs & ... args)
{
    getLogger()->logToDefaultContext(LL_ERROR, value, args...);
}

/**
 * logs given values with warninglevel with the default context
 * @param value
 * @param ...
 */
template<typename T, typename... TArgs>
void logWarning(const T &value, const TArgs & ... args)
{
    getLogger()->logToDefaultContext(LL_WARN, value, args...);
}

/**
 * logs given values with verboselevel with the default context
 * @param value
 * @param ...
 */
template<typename T, typename... TArgs>
void logVerbose(const T &value, const TArgs & ... args)
{
    getLogger()->logToDefaultContext(LL_VERBOSE, value, args...);
}

//}

#endif /* LOGWRAPPER_H_ */
