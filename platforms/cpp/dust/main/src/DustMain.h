#ifndef DUSTMAIN_H_INCLUDED
#define DUSTMAIN_H_INCLUDED

extern "C" void dustBoot(int moduleCount, char **moduleNames);
extern "C" void dustLaunch();
extern "C" void dustShutdown();

#endif // DUSTMAIN_H_INCLUDED
