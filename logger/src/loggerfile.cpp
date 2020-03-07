/*
 * loggerfile.cpp
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <mutex>
#include <iomanip>
#include "logwrapper.h"
#include "loggerfile.h"
#include "timeutility.h"

using namespace std;


#define PADDING_WIDTH 4

pthread_mutex_t gFileMtx = PTHREAD_MUTEX_INITIALIZER;

ostream &operator <<(ostream &out, const class FileHeader &h)
{
    out << TimeUtility::now() << "[" << setw(PADDING_WIDTH) << left << string(h.mCtx, 0, PADDING_WIDTH) << "] ";
    return out;
}

LogContextFile::LogContextFile(const char *id, const LogLevel_e level, const LogStatus_e status, ofstream &filestream)
    : mHeader(id)
    , mLogLevel(level)
    , mLogStatus(status)
    , mFilestream(filestream)
{
}

void LogContextFile::append(const int8_t value)
{
    appendFile(value);
}

void LogContextFile::append(const uint8_t value)
{
    appendFile(value);
}

void LogContextFile::append(const int16_t value)
{
    appendFile(value);
}

void LogContextFile::append(const uint16_t value)
{
    appendFile(value);
}

void LogContextFile::append(const int32_t value)
{
    appendFile(value);
}

void LogContextFile::append(const uint32_t value)
{
    appendFile(value);
}

void LogContextFile::append(const uint64_t value)
{
    appendFile(value);
}

void LogContextFile::append(const int64_t value)
{
    appendFile(value);
}

void LogContextFile::append(const bool value)
{
    appendFile(value);
}

void LogContextFile::append(const char *value)
{
    appendFile(value);
}

void LogContextFile::append(const vector<uint8_t> &data)
{
    mFilestream << data.data() << " ";
}

template<class T>
void LogContextFile::appendFile(T value)
{
    mFilestream << value << " ";
}

bool LogContextFile::configure(const LogLevel_e loglevel)
{
    if (LS_OFF || loglevel > mLogLevel)
    {
        return false;
    }

    pthread_mutex_lock(&gFileMtx);
    mFilestream << mHeader;

    return true;
}

bool LogContextFile::checkLogLevel(const LogLevel_e logLevel)
{
    return logLevel <= mLogLevel;
}

void LogContextFile::send()
{
    mFilestream << endl;
    pthread_mutex_unlock(&gFileMtx);
}

LoggerFile::LoggerFile(const LogStatus_e status, const bool onlyError, const string &filename)
    : mLogStatus(status)
    , mStandardLogLevel(onlyError ? LL_ERROR : LL_INFO)
{
    if (mLogStatus == LS_OFF)
    {
        cout << "Running without Logging support" << endl;
        return;
    }

    mFilestream.open(filename.c_str(), ofstream::out | ofstream::trunc);
    if (!mFilestream.is_open())
    {
        throw runtime_error("Cannot open log file: " + filename);
    }
}

LoggerFile::~LoggerFile()
{
    mFilestream.close();
    unregisterApp();
}

void LoggerFile::unregisterApp()
{
    for (auto &&context : mCtxTable)
    {
        unregisterContext(context.first);
    }
}

void LoggerFile::registerApp(const char *appid, const char *description)
{
    if (mLogStatus == LS_ON)
    {
        mFilestream << mHeader << "Register Application " << string(appid, PADDING_WIDTH) << ", " << description << endl;
    }

    registerContext(DEFAULT_CONTEXT, DEFAULT_DESCRIPTION);
}

ILogContext &LoggerFile::registerContext(const char *contextid, const char *description)
{
    return registerContext(contextid, description, mStandardLogLevel, mLogStatus);
}

ILogContext &LoggerFile::registerContext(const char *contextid, const char *description,
    const LogLevel_e level, const LogStatus_e status)
{
    // check, if we already have this context
    for (auto &ctx : mCtxTable)
    {
        if (contextid && strncmp(contextid, ctx.first, PADDING_WIDTH) == 0)
        {
            return *ctx.second;
        }
    }

    // Not in list. Create new
    if (mLogStatus == LS_ON)
    {
        mFilestream << mHeader << "Registering Context " << string(contextid, PADDING_WIDTH) << ", " << description << endl;
    }
    size_t len = (contextid ? strlen(contextid) : 0);
    char *pKey = new char[1 + len];
    strncpy(pKey, contextid, len);
    pKey[len] = '\0';
    auto *pContext = new LogContextFile(contextid, level, status, mFilestream);
    mCtxTable[pKey] = pContext;

    return *pContext;
}

ILogContext &LoggerFile::importContext(const char *contextid)
{
    // check, if we have this context
    contextid = (contextid ? contextid : DEFAULT_CONTEXT);
    for (auto &ctx : mCtxTable)
    {
        if (contextid && strncmp(ctx.first, contextid, PADDING_WIDTH) == 0)
        {
            return *ctx.second;
        }
    }

    // no match. Fall back to default context
    return importContext(DEFAULT_CONTEXT);
}

void LoggerFile::unregisterContext(const char *contextid)
{
    for (auto it = mCtxTable.begin(); it != mCtxTable.end(); ++it)
    {
        if (contextid && strncmp(contextid, it->first, PADDING_WIDTH) == 0)
        {
            delete it->second;
            const char *key = it->first;
            mCtxTable.erase(it);
            delete key;

            if (mLogStatus == LS_ON)
            {
                mFilestream << mHeader << "Context " << string(contextid, PADDING_WIDTH) << "unregistered" << endl;
            }

            return;
        }
    }
}
