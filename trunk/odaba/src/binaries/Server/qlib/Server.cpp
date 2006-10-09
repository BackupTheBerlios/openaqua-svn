//******************************************************************/
//* Server
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2004/11/05
//******************************************************************/

#define    OBJ_ID  "Server"

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
  int               port = 6123;
  char            *spath = strdup(argv[0]);
  char            *inifile;
  logical          term = NO;
BEGINSEQ

  if ( argc > 1 )
    if ( !(port = atol(argv[1])) )
    {
      puts("invalid port");
      return -1;
    }

  inifile = strdup(argc > 2 ? argv[2] : "server.ini");
  
  if ( Server(inifile,spath,port) )                  ERROR

  printf("\n  terminated successfully.\n");
RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  free(spath);
  free(inifile);
  return(term);
}
