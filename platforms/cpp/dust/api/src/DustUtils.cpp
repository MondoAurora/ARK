
#include "DustUtils.h"

#include <iostream>
#include <string>


class dev0_buffer : public std::streambuf
{
    //called usually for n-characters
    std::streamsize xsputn (const char* s, std::streamsize n)
    {
        return n;
    }

    //may not required due it's not called anymore
    int overflow (int c)
    {
        return c;
    }
} nirwana;

class dev0_stream : public std::ostream
{
public:
    dev0_stream(): std::ostream(&nirwana) {}
} dev0;

DustEventType levelLimit;

std::ostream &DustUtils::log(DustEventType level)
{
    return std::cout;
}
