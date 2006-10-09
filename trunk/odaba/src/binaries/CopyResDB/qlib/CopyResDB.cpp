//******************************************************************/
//* CopyResDB
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/11/03
//******************************************************************/

#define    OBJ_ID  "CopyResDB"

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
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"CopyResDB",argv[0],APT_Console);
  logical          renamed = YES;
  logical          term = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"CopyResDB",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  
  if ( CheckRuntimeParms(argc,argv,3,4) )            ERROR

  if ( uti_handle.sdbures->SetupVariables(argv[2]) ) ERROR
  if ( argc > 3 )
  {
    if ( uti_handle.sdbudat->SetupVariables(argv[3]) ) ERROR
    renamed = NO;
  }

  if ( CopyResDB(uti_handle,renamed) )               ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
