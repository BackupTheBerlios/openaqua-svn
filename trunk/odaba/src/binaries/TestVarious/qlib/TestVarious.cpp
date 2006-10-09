//******************************************************************/
//* TestVarious
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/02/16
//******************************************************************/

#define    OBJ_ID  "TestVarious"

#include  <puti.h>
 
 
#include  <igvts.h>
 





//******************************************************************/
//* main                - 
//*
//* RETURN
//*   rc                - 
//*
//* PARAMETERS
//*   argc              - 
//*   argv[]            - 
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "main"

int main (int argc, char *argv[] )

{
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"TestVarious",argv[0],APT_Console);
  logical          term = NO;
BEGINSEQ


  if ( CheckRuntimeParms(argc,argv,1,2) )            ERROR

  CSUtilityHandle  uti_handle(uti_client,"TestVarious",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  if ( uti_handle.sdbures->SetupVariables("TestVarious") ) 
                                                     ERROR
  if ( TestVarious(uti_handle) )                     ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
