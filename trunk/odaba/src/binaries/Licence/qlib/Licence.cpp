//******************************************************************/
//* Licence
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2003/01/18
//******************************************************************/

#define    OBJ_ID  "Licence"

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
  ODABAClient      uti_client;
  char             default_ini[512];
  char            *pos;
  logical          term = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"Licence",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);

  if ( CheckRuntimeParms(argc,argv,2,2) )            ERROR

  strcpy(default_ini,argv[0]);
  pos = default_ini + strlen(default_ini);
  while ( pos > default_ini )
    if ( *pos == '.' || *pos == '/' || *pos == '\\')
      break;
    else pos--;
  if ( *pos != '.' )
    pos = default_ini + strlen(default_ini);
  strcpy(pos,".ini");
  
  uti_client.Initialize(default_ini,"Licence");

  if ( Licence(uti_handle,argv[1]) )               ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
