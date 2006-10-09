#ifdef WIN32
#pragma pack(push,windows_inc,4)
#endif

#ifdef __unix__
#include <sys/time.h>
#include <dlfcn.h>
#else
#include <windows.h>
#include <winbase.h>
#endif

#ifdef WIN32
#pragma pack(pop,windows_inc)
#endif
