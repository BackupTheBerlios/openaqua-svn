#undef  VGKbaseImpExp 
#ifndef _DLL
#define VGKbaseImpExp 
#else
#ifdef  _VGKbase_
#define VGKbaseImpExp __declspec(dllexport) 
#define VGKbaseImpExp __declspec(dllexport) 
#else
#define VGKbaseImpExp __declspec(dllimport) 
#define VGKbaseImpExp __declspec(dllimport) 
#endif
#endif
