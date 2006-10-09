//******************************************************************/
//* PackDB
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/06/30
//******************************************************************/

#define    OBJ_ID  "PackDB"

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
  char            *temp_path = NULL;
  ODABAClient      uti_client(NULL,"SYSTEM",argv[0],APT_Console);
  logical          term = NO;
BEGINSEQ

  printf("\nPacking ODABA2 database %s",argv[1]);

  if ( CheckRuntimeParms(argc,argv,2,3) )            ERROR
  
  if ( argc > 2 )
  {
    printf("(temporary file %s)",argv[2]);
    temp_path = argv[2];
  }
  printf("\n");
  
  if ( PackDB(uti_client,argv[1],temp_path) )             ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
