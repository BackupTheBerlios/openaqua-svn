//******************************************************************/
//* DBSystemInfo
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/01/18
//******************************************************************/

#define    OBJ_ID  "DBSystemInfo"

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
  ODABAClient      uti_client(argc > 3 ? argv[3] : NULL,"SYSTEM",argv[0],APT_Console);
  char            *temp_path = "DBSystemInfo.txt";
  logical          term      = NO;
BEGINSEQ

  printf("Display ODABA2 System Database Information");

  if ( CheckRuntimeParms(argc,argv,2,3) )            ERROR
  
  if ( argc > 2 )
    temp_path = argv[2];
  
  if ( DBSystemInfo(uti_client,argv[1],temp_path) )             ERROR

  printf("\n  terminated successfully.\n");
RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
