#undef  ODCP8ImpExp 
#ifndef _DLL
#define ODCPImpExp 
#define ODCP8ImpExp 
#define DesignerImpExp 
#else
#ifdef  _ODCP8_
#define ODCP8ImpExp __declspec(dllexport) 
#define ODCPImpExp __declspec(dllexport) 
#else
#define ODCP8ImpExp __declspec(dllimport) 
#define ODCPImpExp __declspec(dllimport) 
#endif
#ifdef  _Designer_
#define DesignerImpExp __declspec(dllexport) 
#else
#define DesignerImpExp __declspec(dllimport) 
#endif
#endif
