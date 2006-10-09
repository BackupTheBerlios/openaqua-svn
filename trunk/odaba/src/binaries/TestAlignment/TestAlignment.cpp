//******************************************************************/
//* TestAlignment
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/11/20
//******************************************************************/

#define    OBJ_ID  "TestAlignment"

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
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"TestAlignment",argv[0],APT_Console);
  char            *strnames;
  logical          term = NO;
BEGINSEQ

  if ( CheckRuntimeParms(argc,argv,1,3) )            ERROR

  CSUtilityHandle  uti_handle(uti_client,"TestAlignment",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  if ( uti_handle.sdbures->SetupVariables("TestAlignment") ) 
                                                     ERROR
  if ( argc > 2 )
    strnames = argv[2];
    
  if ( TestAlignment(uti_handle,strnames) )          ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
