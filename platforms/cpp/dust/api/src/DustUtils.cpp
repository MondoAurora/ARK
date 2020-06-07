
#include "DustUtils.h"
#include "DustRuntime.h"

#include <iostream>
#include <string>

DustEntity DustUtils::getSingleTag(DustEntity e, DustEntity parent, DustEntity defVal)
{
    for ( int i = DustData::getMemberCount(e, DUST_BOOT_REF_TAGS); i-->0; )
    {
        DustEntity t = DustData::getRef(e, DUST_BOOT_REF_TAGS, DUST_ENTITY_INVALID, i);
        if ( t ) {
            if ( parent == DustData::getRef(t, DUST_BOOT_REF_OWNER) ) {
                return t;
            }
        }
    }

    return defVal;
}

bool DustUtils::tag(DustEntity e, DustAccessType cmd, DustEntity tag) {
    switch ( cmd ) {
    case DUST_ACCESS_SET:
        return DustData::setRef(e, DUST_BOOT_REF_TAGS, tag);
    default:
        break;
    }

    return false;
}


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
