#ifndef DUSTMAIN_H_INCLUDED
#define DUSTMAIN_H_INCLUDED

#include <DustModule.h>

#define MODNAME_KERNEL "ModKernel"
#define MODNAME_TEXT "ModText"

extern "C" class DustMonolith
{
public:
    static void init(DustModule *pModKernel, DustModule *pModText = NULL);
    static void addModule(DustEntity token, DustModule *pMod);
    static DustResultType launch();
};

extern "C" class DustModular
{
public:
    static void init(const char *nameKernel, const char *nameText);
    static void addModule(const char *name);
    static DustResultType launch();
};

#endif // DUSTMAIN_H_INCLUDED
