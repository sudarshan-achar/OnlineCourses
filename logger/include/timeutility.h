/*
 * timeutility.cpp
 *
 *  Created on: 07-Mar-2020
 *      Author: sudarshan
 */

#ifndef TIMEUTILITY_H_
#define TIMEUTILITY_H_

#include <string>

class TimeUtility
{
public:
    static inline std::string now()
    {
        time_t     t(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        struct tm *timeinfo(localtime(&t));
        char       buffer[80];
        strftime(buffer, 80, "%D %T ", timeinfo);
        return (std::string(buffer));
    }

    virtual ~TimeUtility();
};

#endif /* TIMEUTILITY_H_ */
