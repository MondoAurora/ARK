
#include "DustUtilsDev.h"


void DustUtilsDev::timeBegin(struct timeval &b)
{
    gettimeofday(&b, NULL);
}

long DustUtilsDev::timeElapse(struct timeval &b)
{
    struct timeval e;
    gettimeofday(&e, NULL);

    return 1000000 * (e.tv_sec - b.tv_sec) + (e.tv_usec - b.tv_usec);
}


