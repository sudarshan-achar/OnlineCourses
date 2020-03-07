/*
 * loggerfile.h
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */

#ifndef LOGGERFILE_H_
#define LOGGERFILE_H_

#include "ilogger.h"
#include <map>
#include <string>
#include <string.h>
#include <fstream>

class FileHeader
{
public:
    FileHeader(const char *ctx = "LOG")
        : mCtx(ctx) {}
    friend std ::ostream &operator <<(std::ostream &out, const FileHeader &h);

    const char *mCtx;
};

class LogContextFile : public ILogContext
{
public:
    LogContextFile(const char *id, const LogLevel_e level, const LogStatus_e status, std::ofstream &filestream);
    virtual ~LogContextFile() {}

    /* ILogContext */
    bool checkLogLevel(const LogLevel_e logLevel) override;

private:
    /* ILogContext */
    bool configure(const LogLevel_e loglevel) override;
    void send() override;
    void append(const int8_t value) override;
    void append(const uint8_t value) override;
    void append(const int16_t value) override;
    void append(const uint16_t value) override;
    void append(const int32_t value) override;
    void append(const uint32_t value) override;
    void append(const uint64_t value) override;
    void append(const int64_t value) override;
    void append(const bool value) override;
    void append(const std::vector<uint8_t> &data) override;
    void append(const char *value) override;

    template<class T>
    void appendFile(T value);

private:
    FileHeader    mHeader;
    LogLevel_e  mLogLevel;
    LogStatus_e mLogStatus;
    std::ofstream &mFilestream;
};

class LoggerFile : public ILogger
{
public:
    LoggerFile(const LogStatus_e status, const bool onlyError = false, const std::string &filename = "");
    ~LoggerFile();

    /* ILogger */
    void registerApp(const char *appid, const char *description) override;
    void unregisterApp() override;
    ILogContext &registerContext(const char *contextid, const char *description) override;
    ILogContext &registerContext(const char *contextid, const char *description,
        const LogLevel_e level, const LogStatus_e status) override;
    ILogContext &importContext(const char *contextid = NULL) override;
    void unregisterContext(const char *contextid) override;

private:
    void print(std::string str);

private:
    FileHeader          mHeader;
    const LogStatus_e mLogStatus;
    const LogLevel_e  mStandardLogLevel;
    std::ofstream        mFilestream;
    std::map<const char *, LogContextFile *> mCtxTable;
};

#endif /* LOGGERFILE_H_ */
