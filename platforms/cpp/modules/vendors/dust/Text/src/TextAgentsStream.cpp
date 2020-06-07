#include "Text.h"

#include <string>

using namespace DustUnitMindBinary;
using namespace DustUnitMindText;

using namespace std;

TextLogicStreamWriter::TextLogicStreamWriter()
{

}
TextLogicStreamWriter::~TextLogicStreamWriter()
{
}

DustResultType TextLogicStreamWriter::DustActionExecute()
{
    if (DustData::getInteger(DUST_CTX_DIALOG, DustIntStreamOk, 0))
    {
        char c = (char) DustData::getInteger(DUST_CTX_DIALOG, DustIntCharCode, -1);
        if ( -1 != c )
        {
            cout << c;
            return DUST_RESULT_ACCEPT_PASS;
        }
    }
    else
    {
        string *pStr = (string *) DustData::getNative(DUST_CTX_DIALOG, DustTypePlainText, false);

        if (!pStr)
        {
            pStr = (string *) DustData::getNative(DUST_CTX_SELF, DustTypePlainText, false);
        }

        if (pStr)
        {
            cout << pStr->c_str() << endl;
            return DUST_RESULT_ACCEPT;
        }
    }
        return DUST_RESULT_REJECT;
}




TextLogicStreamReader::TextLogicStreamReader()
{

}
TextLogicStreamReader::~TextLogicStreamReader()
{
}

DustResultType TextLogicStreamReader::DustActionExecute()
{
    DustRef eDlg(DUST_CTX_DIALOG);
    bool ok;

    if (!inStream.is_open())
    {
        DustRef eSelf(DUST_CTX_SELF);
        pos = 0;
        string *psName = (string *) DustData::getNative(DustData::getRef(eSelf, DustRefBinaryUrl));
        inStream.open(psName->c_str());

        if ( !inStream.is_open() )
        {
            return DUST_RESULT_REJECT;
        }
    }
    else
    {
        ok = DustData::getInteger(eDlg, DustIntStreamPos, 0);
        if (!ok)
        {
            inStream.close();
            return (1 < pos) ? DUST_RESULT_ACCEPT : DUST_RESULT_REJECT;
        }
    }

    char chr;
    inStream.get(chr);
    ok = inStream.good();

    DustData::setInteger(eDlg, DustIntStreamOk, ok);
    DustData::setInteger(eDlg, DustIntStreamPos, ++pos);
    DustData::setInteger(eDlg, DustIntCharCode, chr);

    return DUST_RESULT_ACCEPT_PASS;
}
