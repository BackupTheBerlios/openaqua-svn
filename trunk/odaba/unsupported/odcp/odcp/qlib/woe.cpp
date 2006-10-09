//******************************************************************/
//* woe80
//*
//*               ODABA II - Main Function Code
//*                          from  l:\odcp8\odcp8.dev
//*  PD Version 2.0                                     07.02.2006
//******************************************************************/

#define    OBJ_ID  "woe80"
#include  <woe80.h>
 
#include  <podcp8.h>
//#include <dumapp.h>
 





//******************************************************************/
//* WinMain             - 
//*
//* RETURN
//*   term              - 
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
  bool              term = false;
  typedef           int (*__cdecl CreateAppl)(HINSTANCE,HINSTANCE,LPSTR,int);
  HINSTANCE         lhinst;
  CreateAppl        pfunct;
  std::vector<void*>     dlhandles;
  int                    retcode = 0;
  oe_helper              oe;
BEGINSEQ
  term |= term || oe.loadLib(dlhandles,"SOS90");  //0
  term |= term || oe.loadLib(dlhandles,"OPA90");  //1
  term |= term || oe.loadLib(dlhandles,"OGUI90");  //2
  term |= term || oe.loadLib(dlhandles,"OADI90");  //3
  if(term)                                           ERROR
  // get the function that starts up the application
  // can exit(1) on error
  pfunct = (CreateAppl) oe.bindLibFunc(dlhandles[3],"CreateAppl");
  retcode = pfunct(hInstance,hPrevInst,GetCommandLine(),nCmdShow);




RECOVER

  oe.closeLibs(dlhandles);
    exit(1); // end the progam with a error > 0 
             //(for  $ ope80 && echo success)

ENDSEQ

  oe.closeLibs(dlhandles);
  return retcode;
}
