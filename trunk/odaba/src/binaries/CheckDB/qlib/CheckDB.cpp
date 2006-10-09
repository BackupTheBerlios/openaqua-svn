//******************************************************************/
//* CheckDB
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/10/03
//******************************************************************/

#define    OBJ_ID  "CheckDB"

#include  <puti.h>
 
 
 
#include  <sCheckOptions.hpp>





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
  CheckOptions     check_opts;
  char            *string;
  char             parmstring[1024];
  char             source[1025];
  logical          term   = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"Check Database",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);

  printf("\nChecking database consistency");
  
  if ( CheckRuntimeParms(argc,argv,2,6) )            ERROR
  if ( uti_handle.sdbures->SetupVariables("CheckDB") ) 
                                                     ERROR
  GetParmString(parmstring,argc,argv);
  check_opts.Initialize(parmstring);
  
  *source = 0;  
  if ( string = GetKeyParm(parmstring,"-S",NO,YES) )
    strcpy(source,string);
  
  uti_client.Initialize(argv[1],"Check Database");
  
  if ( CheckDB(uti_handle,check_opts,*source ? source : NULL) )
                                                     ERROR
  printf("\nCheck terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
