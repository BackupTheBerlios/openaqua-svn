//******************************************************************/
//* OPE80
//*
//*               ODABA II - Main Function Code
//*                          from  l:\odcp8\odcp8.dev
//*  PD Version 2.0                                     27.10.2005
//******************************************************************/

#define    OBJ_ID  "OPE80"

#include  <ope80.h>
 
#include  <podcp8.h>
 
 





//******************************************************************/
//* WinMain             - 
//*
//* RETURN
//*                     - 
//*
//* PARAMETERS
//*   hInstance         - 
//*   hPrevInst         - 
//*   lpszCmdLine       - 
//*   nCmdShow          - 
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "WinMain"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow )

{
  char              section[65];
  char              opath[129];
  char              dllpath[150];
  char              parm1[256];
  char              cmdline[1024];
  char              *cmdlptr = cmdline;
  bool              hk = false;
  typedef           int (*__cdecl CreateAppl)(HINSTANCE,HINSTANCE,LPSTR,int);
  HINSTANCE         lhinst;
  CreateAppl        pfunct;

  if ( lpszCmdLine )
  {
    while ( *lpszCmdLine )
    {
      if ( *lpszCmdLine == '"' )
        hk = !hk;
      else
      {
        if ( hk && *lpszCmdLine == ' ' )
          *cmdlptr = 255;
        else
          *cmdlptr = *lpszCmdLine;
        cmdlptr++;
      }
      lpszCmdLine++;
    }
    *cmdlptr = 0;

    memset(parm1,0,sizeof(parm1)-1);
    strncpy(parm1,cmdline,sizeof(parm1)-1);
    if (strchr(parm1,' ') )
      *strchr(parm1,' ') = 0;
    while ( strchr(parm1,255) )
      *strchr(parm1,255) = ' ';

    GetPrivateProfileString(NULL,"ODABA_PATH","",section,sizeof(section)-1,parm1);  
    if ( *section )
    {
      GetPrivateProfileString(section,"ODABA_PATH","",opath,sizeof(opath)-1,parm1);  
      if ( *opath && opath[strlen(opath)-1] != '\\' && opath[strlen(opath)-1] != '/' )
        strcat(opath,"/");
      if ( !LoadLibrary(strcat(strcpy(dllpath,opath),"SOS90.DLL")) )
        LoadLibrary("SOS80.DLL");
      if ( !LoadLibrary(strcat(strcpy(dllpath,opath),"OPA90.DLL")) )
        LoadLibrary("OPA80.DLL");
      if ( !LoadLibrary(strcat(strcpy(dllpath,opath),"OGUI90.DLL")) )
        LoadLibrary("OGUI80.DLL");        
      if ( !(lhinst = LoadLibrary(strcat(strcpy(dllpath,opath),"OADI90.DLL"))) )
        lhinst = LoadLibrary("OADI80.DLL");
      
      if ( lhinst && (pfunct = (CreateAppl)GetProcAddress(lhinst,"CreateAppl")) )
//        return(pfunct(hInstance,hPrevInst,cmdline,nCmdShow));
        return(pfunct(hInstance,hPrevInst,GetCommandLine(),nCmdShow));
      }
  }




  return(1);

}
