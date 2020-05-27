#ifndef TEXTAGENTSSTREAM_H
#define TEXTAGENTSSTREAM_H

#include <DustApi.h>

#include <fstream>

class TextLogicStreamWriter : public DustNativeLogic
{
public:
    TextLogicStreamWriter();
    virtual ~TextLogicStreamWriter();

    virtual DustResultType DustActionExecute();
};

class TextLogicStreamReader : public DustNativeLogic
{
    std::ifstream inStream;
    int pos;

public:
    TextLogicStreamReader();
    virtual ~TextLogicStreamReader();

    virtual DustResultType DustActionExecute();
};


#endif // TEXTAGENTSSTREAM_H
