#undef  AdkCtxiImpExp 
#ifndef _DLL
#define AdkCtxiImpExp 
#else
#ifdef  _AdkCtxi_
#define AdkCtxiImpExp __declspec(dllexport) 
#define AdkCtxiImpExp __declspec(dllexport) 
#else
#define AdkCtxiImpExp __declspec(dllimport) 
#define AdkCtxiImpExp __declspec(dllimport) 
#endif
#endif
