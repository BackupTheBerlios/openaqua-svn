//******************************************************************/
//* CheckGUIDs
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/04/02
//******************************************************************/

#define    OBJ_ID  "CheckGUIDs"

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
  char            *parmstring;
  char             source[1025];
  logical          term   = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"Check Database",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);

  printf("Checking database consistency\n");
  
  if ( CheckRuntimeParms(argc,argv,2,6) )            ERROR
  if ( uti_handle.sdbures->SetupVariables("CheckDB") ) 
                                                     ERROR
  parmstring = GetParmString(argc,argv);
  
  if ( string = GetKeyParm(parmstring,"-C",NO,YES) )
  {
    check_opts.guids              = NO;
    check_opts.inverse_references = NO;
    check_opts.ref_indexes        = NO;
    while ( *string )
    {
      switch ( *string )
      {
        case 'g' : 
        case 'G' : check_opts.guids = YES;
                   break;
        case 'i' : 
        case 'I' : check_opts.inverse_references = YES;
                   break;
        case 'x' : 
        case 'X' : check_opts.ref_indexes = YES;
                   break;
        default  : printf("invalid check (-C) option: %c",*string);
      }
      *string++;
    }
  }
  if ( string = GetKeyParm(parmstring,"-T",NO,YES) )
  {
    check_opts.instances   = NO;
    check_opts.collections = NO;
    switch ( *string )
    {
      case 'i' : 
      case 'I' : check_opts.instances = YES;
                 break;
      case 'c' : 
      case 'C' : check_opts.collections = YES;
                 break;
      case 'a' : 
      case 'A' : check_opts.instances = YES;
                 check_opts.collections = YES;
                 break;
      default  : printf("invalid type (-T) option: %c",*string);
    }
  }
  if ( string = GetKeyParm(parmstring,"-S",NO,YES) )
    strcpy(source,string);
  if ( string = GetKeyParm(parmstring,"-R",NO,YES) )
    check_opts.repair_all = YES;
  
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
