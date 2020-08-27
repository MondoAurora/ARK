#ifndef DUSTUTILS_H_
#define DUSTUTILS_H_

#include "DustApi.h"

#include <iostream>
#include <string>

class DustUtils
{
public:
    static std::ostream& log(DustEventType level = DUST_EVENT_INFO);
    static DustEntity getSingleTag(DustEntity e, DustEntity tagType, DustEntity defVal);
    static bool tag(DustEntity e, DustAccessType cmd, DustEntity tag);
    inline static bool isReading(DustResultType result)
    {
        return (DUST_RESULT_ACCEPT_READ == result) || (DUST_RESULT_READ == result);
    }
    inline static bool isSuccess(DustResultType result)
    {
        return (DUST_RESULT_ACCEPT_READ == result) || (DUST_RESULT_ACCEPT == result);
    }
};

#endif /* DUSTUTILS_H_ */
