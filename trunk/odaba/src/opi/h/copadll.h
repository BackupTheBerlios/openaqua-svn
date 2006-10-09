#ifndef __COPADLL_H__
#define __COPADLL_H__
#ifdef __unix__


#define OPA7ImpExp
#define opa7ImpExp
#define OPI7ImpExp
#define OPS7ImpExp
#define OQL7ImpExp

#define OPAImpExp
#define opaImpExp
#define OPIImpExp
#define OPSImpExp
#define OQLImpExp
#define FunctionalModelImpExp

#else


#ifndef _DLL

#define OPA7ImpExp
#define opa7ImpExp
#define OPI7ImpExp
#define OPS7ImpExp
#define OQL7ImpExp

#define OPAImpExp
#define opaImpExp
#define OPIImpExp
#define OPSImpExp
#define OQLImpExp
#define FunctionalModelImpExp

#else

#ifdef _OPA7_ 
#define OPA7ImpExp __declspec(dllexport) 
#define opa7ImpExp __declspec(dllexport) 
#define OPI7ImpExp __declspec(dllexport) 
#define OPS7ImpExp __declspec(dllexport) 
#define OQL7ImpExp __declspec(dllexport) 

#define OPAImpExp __declspec(dllexport) 
#define opaImpExp __declspec(dllexport) 
#define OPIImpExp __declspec(dllexport) 
#define OPSImpExp __declspec(dllexport) 
#define OQLImpExp __declspec(dllexport) 
#define FunctionalModelImpExp __declspec(dllexport) 
#else
#define OPA7ImpExp __declspec(dllimport) 
#define opa7ImpExp __declspec(dllimport) 
#define OPI7ImpExp __declspec(dllimport) 
#define OPS7ImpExp __declspec(dllimport) 
#define OQL7ImpExp __declspec(dllimport) 

#define OPAImpExp __declspec(dllimport) 
#define opaImpExp __declspec(dllimport) 
#define OPIImpExp __declspec(dllimport) 
#define OPSImpExp __declspec(dllimport) 
#define OQLImpExp __declspec(dllimport) 
#define FunctionalModelImpExp __declspec(dllimport) 
#endif

#endif


#endif
#endif //__COPADLL_H__

