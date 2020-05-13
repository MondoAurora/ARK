#ifndef DUSTGENUNITMINDTEXT_HPP_INCLUDED
#define DUSTGENUNITMINDTEXT_HPP_INCLUDED

#include <DustApi.h>

class DustUnitMindText {
public:
    const DustEntity DustUnitText;
    const DustEntity DustTypePlainText;

    DustUnitMindText() :
        DustUnitText(DustMeta::getUnit("MindText")),
        DustTypePlainText(DustMeta::getIdeaEntity(DustUnitText, "PlainText", DUST_IDEA_TYPE, DUST_BOOT_TYPE_PLAINTEXT))
    {
    }
};

#endif // DUSTGENUNITMINDTEXT_HPP_INCLUDED
