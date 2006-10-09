#ifdef __unix__
#define OADI8ImpExp
#define OADIImpExp
#else

#ifndef _DLL
#define OADI8ImpExp
#define OADIImpExp
#else

#ifdef _OADI_
#define OADIImpExp __declspec(dllexport)
#define OADI8ImpExp __declspec(dllexport)
#else
#define OADIImpExp __declspec(dllimport)
#define OADI8ImpExp __declspec(dllimport)
#endif

#endif
#endif
