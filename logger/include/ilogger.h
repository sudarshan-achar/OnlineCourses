/*
 * ilogger.h
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <pthread.h>
#include <stdint.h>
#include <sstream>
#include <vector>
#include <cassert>
#include "loggertypes.h"
#include "olctypes.h"


#define DEFAULT_CONTEXT     "DEF"
#define DEFAULT_DESCRIPTION "default Context registered by DLT Logger Class"

#define DEFAULT_LOG_SERVICE static_cast<LogService_e>(0)

enum LogService_e
{
	LOG_SERVICE_DLT,
	LOG_SERVICE_STDOUT,
	LOG_SERVICE_FILE,
	LOG_SERVICE_OFF
};

enum LogLevel_e
{
	LL_OFF     = 0x00, /**< Log level off */
	LL_FATAL   = 0x01, /**< fatal system error */
	LL_ERROR   = 0x02, /**< error with impact to correct functionality */
	LL_WARN    = 0x03, /**< warning, correct behavior could not be ensured */
	LL_INFO    = 0x04, /**< informational */
	LL_DEBUG   = 0x05, /**< debug  */
	LL_VERBOSE = 0x06  /**< highest grade of information */
};

enum LogStatus_e
{
	LS_OFF = 0x00,
	LS_ON  = 0x01
};

class ILogContext
{
public:
	virtual ~ILogContext() {}

	/**
	 * logs given loglevel and given values
	 * @param loglevel
	 * @param ...
	 */
	template<typename... TArgs>
	void off(const TArgs & ... args)
	{
		this->log(LL_OFF, args...);
	}

	template<typename... TArgs>
	void fatal(const TArgs & ... args)
	{
		this->log(LL_FATAL, args...);
	}

	template<typename... TArgs>
	void error(const TArgs & ... args)
	{
		this->log(LL_ERROR, args...);
	}

	template<typename... TArgs>
	void warn(const TArgs & ... args)
	{
		this->log(LL_WARN, args...);
	}

	template<typename... TArgs>
	void info(const TArgs & ... args)
	{
		this->log(LL_INFO, args...);
	}

	template<typename... TArgs>
	void debug(const TArgs & ... args)
	{
		this->log(LL_DEBUG, args...);
	}

	template<typename... TArgs>
	void verbose(const TArgs & ... args)
	{
		this->log(LL_VERBOSE, args...);
	}

	template<typename... TArgs>
	void log(const LogLevel_e loglevel, const TArgs & ... args)
	{
		if (!this->configure(loglevel))
		{
			return;
		}

		this->append(args...);
		this->send();
	}

	virtual bool checkLogLevel(const LogLevel_e logLevel) = 0;

	virtual bool configure(const LogLevel_e loglevel) = 0;

private:
	virtual void send() = 0;

	virtual void append(const int8_t value)               = 0;
	virtual void append(const uint8_t value)              = 0;
	virtual void append(const int16_t value)              = 0;
	virtual void append(const uint16_t value)             = 0;
	virtual void append(const int32_t value)              = 0;
	virtual void append(const uint32_t value)             = 0;
	virtual void append(const uint64_t value)             = 0;
	virtual void append(const int64_t value)              = 0;
	virtual void append(const bool value)                 = 0;
	virtual void append(const std::vector<uint8_t> &data) = 0;
	virtual void append(const char *value)                = 0;

	template<typename T = std::string &>
	void append(const std::string &value)
	{
		this->append(value.c_str());
	}

	template<typename T>
	void append_enum(const T &value, const T &tmax, const std::vector<const char *> &text)
	{
		assert(tmax == text.size());
		try
		{
			this->append(text.at(value));
		}
		catch (const std::out_of_range &)
		{
			this->append(__PRETTY_FUNCTION__);
			this->append(static_cast<int32_t>(value));
			this->append("out of range!");
		}
	}



	template<typename T = Availability_e>
	void append(const Availability_e value)
	{
		this->append_enum(value, A_MAX, std::vector<const char *> {
			"A_UNKNOWN",
			"A_AVAILABLE",
			"A_UNAVAILABLE"
		}
		);
	}

	template<typename T = InterruptState_e>
	void append(const InterruptState_e value)
	{
		this->append_enum(value, IS_MAX, std::vector<const char *> {
			"IS_UNKNOWN",
			"IS_OFF",
			"IS_INTERRUPTED"
		}
		);
	}

	template<typename T = err_t>
	void append(const err_t value)
	{
		this->append_enum(value, MINOR_ERROR, std::vector<const char *> {
			"NO_ERROR",
			"NO_ELEMENTS",
			"NOT_FOUND",
			"NULL_PTR",
			"MINOR_ERROR",
			"MAJOR_ERROR"
		}
		);
	}

	// Template to print unknown pointer types with their address
	template<typename T>
	void append(T *value)
	{
		std::ostringstream ss;
		ss << "0x" << std::hex << (uint64_t)value;
		this->append(ss.str().c_str());
	}

	// Template to print unknown types
	template<typename T>
	void append(T value)
	{
		std::ostringstream ss;
		ss << std::dec << value;
		this->append(ss.str().c_str());
	}

	// Template parameter pack to generate recursive code
	void append(void) {}
	template<typename T, typename... TArgs>
	void append(const T &value, const TArgs & ... args)
	{
		this->append(value);
		this->append(args...);
	}

};

class ILogger
{
public:
	virtual ~ILogger() {}
	virtual void registerApp(const char *appid, const char *description) = 0;
	virtual void unregisterApp() = 0;
	virtual ILogContext &registerContext(const char *contextid, const char *description) = 0;
	virtual ILogContext &registerContext(const char *contextid, const char *description,
			const LogLevel_e level, const LogStatus_e status) = 0;
	virtual ILogContext &importContext(const char *contextid = NULL) = 0;
	virtual void unregisterContext(const char *contextid)      = 0;

	template<typename T, typename... TArgs>
	void logToDefaultContext(const LogLevel_e loglevel, const T &value, const TArgs & ... args)
	{
		this->importContext().log(loglevel, value, args...);
	}

};

#endif // LOGGER_H_
