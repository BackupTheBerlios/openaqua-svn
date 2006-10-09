//******************************************************************/
//* OShell
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2006/02/05
//******************************************************************/

#define    OBJ_ID  "OShell"

#include  <puti.h>
 
 
 





//******************************************************************/
//* main                - 
//*
//* RETURN
//*   rc                - 
//*
//* PARAMETERS
//*   argc              - 
//*   argv              - 
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "main"

int __cdecl main (int argc, char **argv )

{
  extern  CLInterpreter *OShell;
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"OShell",argv[0],APT_Console);

BEGINSEQ

  if ( CheckRuntimeParms(argc,argv,1,3) )            ERROR

  CLInterpreter   cli(uti_client);
  printf("ODABA Commandline Utility - Enter Command or ? for help\n");
  
  CLInterpreterBase::SetOShell(&cli);
  cli.Execute(argc > 2 ? argv[2] : NULL);
  CLInterpreterBase::SetOShell(NULL);
RECOVER

  return(1);

ENDSEQ

  uti_client.ShutDown();
  return(0);
}
