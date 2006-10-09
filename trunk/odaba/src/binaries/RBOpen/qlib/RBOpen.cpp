//******************************************************************/
//* RBOpen
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/01/07
//******************************************************************/

#define    OBJ_ID  "RBOpen"

#include  <puti.h>
 
 
#include  <cEBbase.h>
 





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
  ODABAClient      uti_client(NULL,"SYSTEM",argv[0],APT_Console);
  logical          outopt = YES;
  logical          term   = NO;

BEGINSEQ

  printf("\nOpening ODABA2 root database %s",argv[1]);

  if ( CheckRuntimeParms(argc,argv,2,3) )            ERROR
  
  if ( argc > 2 )
    outopt = *argv[2] == 'Y' || *argv[2] == 'y' ? YES : NO;
  
  eb_RootBase     dbase(NO,NO);
  if ( dbase.Open(argv[1],outopt,NO,YES) )           ERROR
  
  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
