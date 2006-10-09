//******************************************************************/
//* SystemVersion
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/10/15
//******************************************************************/

#define    OBJ_ID  "SystemVersion"

#include  <puti.h>
 
 
#include  <igvts.h>
 





//******************************************************************/
//* main                - 
//*
//* RETURN
//*   term              - 
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
  int           port = 6123;
  char         *server_name;
BEGINSEQ

  if ( CheckRuntimeParms(argc,argv,1,2) )            ERROR

  if ( argc > 2 )
    port = atoi(argv[2]);
  
  if ( argc > 1 )
  {
    server_name = argv[1];
      printf("\nCurrent client version is: %s.\n",ODABA2Version());
  }
  else
    printf("\nCurrent client version is: %s.\n",ODABA2Version());

RECOVER


ENDSEQ


}
