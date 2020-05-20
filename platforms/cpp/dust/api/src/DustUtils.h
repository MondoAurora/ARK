#ifndef DUSTUTILS_H_
#define DUSTUTILS_H_

#include "DustApi.h"

#include <iostream>
#include <string>

class DustUtils
{
public:
    static std::ostream& log(DustEventType level = DUST_EVENT_INFO);
};

#endif /* DUSTUTILS_H_ */
