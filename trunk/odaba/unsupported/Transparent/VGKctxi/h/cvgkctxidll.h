#undef  VGKctxiImpExp 
#ifndef _DLL
#define VGKctxiImpExp 
#else
#ifdef  _VGKctxi_
#define VGKctxiImpExp __declspec(dllexport) 
#define VGKctxiImpExp __declspec(dllexport) 
#else
#define VGKctxiImpExp __declspec(dllimport) 
#define VGKctxiImpExp __declspec(dllimport) 
#endif
#endif
