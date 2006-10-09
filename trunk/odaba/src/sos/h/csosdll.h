#ifndef __CSOSDLL_H__
#define __CSOSDLL_H__


#ifndef _DLL
#define SOSImpExp 
#define SOS7ImpExp 
#else

#ifdef  _SOS7_
#define SOSImpExp __declspec(dllexport) 
#define SOS7ImpExp __declspec(dllexport) 
#else
#define SOSImpExp __declspec(dllimport) 
#define SOS7ImpExp __declspec(dllimport) 
#endif

#endif

#endif //__CSOSDLL_H__
