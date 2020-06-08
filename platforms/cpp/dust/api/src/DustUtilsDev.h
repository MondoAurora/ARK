#ifndef DUSTUTILSDEV_H_
#define DUSTUTILSDEV_H_

#include "DustUtils.h"

#include <sys/time.h>

class DustUtilsDev
{
public:
    static void timeBegin(struct timeval &b);
    static long timeElapse(struct timeval &b);
};

#endif /* DUSTUTILSDEV_H_ */
