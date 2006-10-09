//******************************************************************/
//* ResetSysVersion
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2006/02/25
//******************************************************************/

#define    OBJ_ID  "ResetSysVersion"

#include  <puti.h>
 
 
 





//******************************************************************/
//* main                - 
//*
//* RETURN
//*   rc                - 
//*
//* PARAMETERS
//*   argc              - 
//*   argv              - 
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "main"

int main (int argc, char **argv )

{
  ODABAClient      uti_client(NULL,"SYSTEM",argv[0],APT_Console);
  uint16           sys_ver = CUR_VERSION;
  uint16           version;
  logical           term = NO;
BEGINSEQ

  RegisterProcess();
  printf("Reset database version for Dictionary");
  
  if ( CheckRuntimeParms(argc,argv,2,3) )            ERROR

  DictionaryHandle   sysdict(uti_client,argv[1],PI_Write,YES,CUR_VERSION);  
	                                             SDBCERR
  if ( argc > 2 )
    sys_ver = atoi(argv[2]);
  
  if ( sysdict.ResetLastVersion(sys_ver) )           ERROR

  printf("\n  terminated successfully.\n");
    


RECOVER

  printf("\n ... terminated with errors.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
