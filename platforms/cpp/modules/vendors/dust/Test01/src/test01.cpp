#include <iostream>
#include <string>

#include <DustModule.h>

#include <MiND/DustgenUnitMindTools.h>
#include <MiND/DustgenUnitMindCore.h>
#include <vendors/dust/DustgenUnitTest01.h>

using namespace std;
using namespace DustUnitDustTest01;


#include <regex>

void testSol() {
        // Simple regular expression matching
    const std::string fnames[] = {"   1460 y#4#167                    4.7134579                       0"};
    const std::regex rx("\\s*\\d+\\s+(\\S+)\\s+(\\S+)\\s+\\S+\\s*");

    std::smatch pm;

    for (const auto &fname : fnames) {
        if (std::regex_match(fname, pm, rx)) {
            std::cout << fname << '\n';
            for (size_t i = 0; i < pm.size(); ++i) {
                std::ssub_match sm = pm[i];
                std::string piece = sm.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }
        }
    }

}

void test03() {
        // Simple regular expression matching
    const std::string fnames[] = {"foo.txt", "bar.txt", "baz.dat", "zoidberg"};
    const std::regex txt_regex("[a-z]+\\.txt");

    for (const auto &fname : fnames) {
        std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
    }

    // Extraction of a sub-match
    const std::regex base_regex("([a-z]+)\\.txt");
    std::smatch base_match;

    for (const auto &fname : fnames) {
        if (std::regex_match(fname, base_match, base_regex)) {
            // The first sub_match is the whole string; the next
            // sub_match is the first parenthesized expression.
            if (base_match.size() == 2) {
                std::ssub_match base_sub_match = base_match[1];
                std::string base = base_sub_match.str();
                std::cout << fname << " has a base of " << base << '\n';
            }
        }
    }

    // Extraction of several sub-matches
    const std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
    std::smatch pieces_match;

    for (const auto &fname : fnames) {
        if (std::regex_match(fname, pieces_match, pieces_regex)) {
            std::cout << fname << '\n';
            for (size_t i = 0; i < pieces_match.size(); ++i) {
                std::ssub_match sm = pieces_match[i];
                std::string piece = sm.str();
                std::cout << "  submatch " << i << ": " << piece << '\n';
            }
        }
    }
}

void test01()
{
    cout << "T01 sees int value " << DustData::getInteger(0,0,0) << endl;

    DustEntity e = DustData::getRef(DustUnitMindText::DustTypePlainText, DustUnitMindModel::DustRefGlobalId);

    string *pStr = (string*) DustData::getNative(e, DustUnitMindText::DustTypePlainText);

    cout << "T01 read plain text type id " << pStr->c_str() << endl;

    pStr = (string*) DustData::getNative(e, DustUnitMindText::DustTypePlainText);

    cout << "T01 read plain text type id SECOND TIME " << pStr->c_str() << endl;
}

class T01 : public DustNativeLogic
{
    virtual DustResultType DustActionExecute()
    {
        testSol();

        return DUST_RESULT_ACCEPT;
    }
};

DECLARE_FACTORY(T01, DustAgentTest01)

class TestModule : public DustModule
{
public:
    virtual ~TestModule()
    {
    }

    virtual DustResultType DustResourceInit()
    {
        cout << "TestModule::DustResourceInit" << endl;
        registerFactory(&FactT01);
        return DUST_RESULT_ACCEPT;
    }
    virtual DustResultType DustResourceRelease()
    {
        cout << "TestModule::DustResourceRelease" << endl;
        return DUST_RESULT_ACCEPT;
    }
};

TestModule module;

extern "C" DustModule* getModule()
{
    return &module;
}
