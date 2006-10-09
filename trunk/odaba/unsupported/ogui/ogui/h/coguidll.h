#ifdef __unix__

#define OGUI7ImpExp 
#define OGUIImpExp 
#define stricmp(a, b)   strcasecmp(a,b)
#define strnicmp(a, b, c)  strncasecmp(a,b,c)

#else

#ifndef _DLL
#define OGUIImpExp __far
#define OGUI7ImpExp __far
#else

#ifdef _OGUI_
#define OGUIImpExp __declspec(dllexport)
#define OGUI7ImpExp __declspec(dllexport)
#else
#define OGUIImpExp __declspec(dllimport)
#define OGUI7ImpExp __declspec(dllimport)
#endif

#endif
#endif
