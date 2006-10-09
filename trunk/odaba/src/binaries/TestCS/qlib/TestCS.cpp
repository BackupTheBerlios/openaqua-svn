//******************************************************************/
//* TestCS
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/02/14
//******************************************************************/

#define    OBJ_ID  "TestCS"

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
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"DBPerformance",argv[0],APT_Console);
  char            *extent_name;
  long             distance    = 10;
  long             max_count   = 1000;
  long             max_objects = 100;
  logical          term = NO;
BEGINSEQ

  if ( CheckRuntimeParms(argc,argv,1,6) )            ERROR

  CSUtilityHandle  uti_handle(uti_client,"TestCS",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  if ( uti_handle.sdbures->SetupVariables("TestCS") ) ERROR

  if ( argc > 2 )
    extent_name = argv[2];
    
  if ( argc > 3 )
    distance = atoi(argv[3]);
  
  if ( argc > 4 )
    max_count = atoi(argv[4]);
  
  if ( argc > 5 )
    max_objects = atoi(argv[5]);
  
  if ( CheckCS(uti_handle,extent_name,distance,max_count,max_objects) )  
                                                     ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
