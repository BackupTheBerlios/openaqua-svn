//******************************************************************/
//* coe80
//*
//*               ODABA II - Main Function Code
//*                          from  l:\odcp8\odcp8.dev
//*  PD Version 2.0                                     07.02.2006
//******************************************************************/

#define    OBJ_ID  "coe80"

#include  <coe80.h>

#include  <podcp8.h>
 
 





//******************************************************************/
//* main                - 
//*
//* RETURN
//*   term              - 
//*
//* PARAMETERS
//*   argc              - 
//*   argv              - 
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "main"

int main (int argc, char **argv )

{
  typedef           int (*__cdecl CreateAppl)(int,char**);
  CreateAppl        pfunct;

  std::vector<void*>     dlhandles;
  bool              term = false;
  int               retcode = 0;
  oe_helper         oe;
BEGINSEQ
 
  if(oe.help(argc,argv))                             LEAVESEQ
  term |= term || oe.loadLib(dlhandles,"odaba_sos");  //0
  term |= term || oe.loadLib(dlhandles,"odaba_opa");  //1
  term |= term || oe.loadLib(dlhandles,"odaba_ogui");  //2
  term |= term || oe.loadLib(dlhandles,"odaba_oadi");  //3
  
  if(term)                                           ERROR
  // get the function that starts up the application
  // can exit(1) on error
  pfunct = (CreateAppl) oe.bindLibFunc(dlhandles[3],"CreateConsoleAppl");
  retcode = pfunct(argc,argv);


RECOVER

  oe.closeLibs(dlhandles);
  exit(1); 
   // end the progam with a error > 0 
   // (for  $ coe && echo success)

ENDSEQ

  oe.closeLibs(dlhandles);
  return retcode;
}
