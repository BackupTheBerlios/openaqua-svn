//******************************************************************/
//* CopyDB
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2004/04/25
//******************************************************************/

#define    OBJ_ID  "CopyDB"

#include  <puti.h>
 
 
 





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
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"CopyDB",argv[0],APT_Console);
  logical          term = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"CopyDB",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  
  if ( CheckRuntimeParms(argc,argv,4,4) )            ERROR

  if ( uti_handle.sdbures->SetupVariables(argv[2]) ) ERROR
  if ( uti_handle.sdbudat->SetupVariables(argv[3]) ) ERROR

  if ( CopyDB(uti_handle) )                          ERROR

  printf("\n  terminated successfully.\n");
RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
