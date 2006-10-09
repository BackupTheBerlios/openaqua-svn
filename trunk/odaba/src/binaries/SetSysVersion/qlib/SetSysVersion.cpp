//******************************************************************/
//* SetSysVersion
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/01/07
//******************************************************************/

#define    OBJ_ID  "SetSysVersion"

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
  ODABAClient      uti_client(NULL,"SYSTEM",argv[0],APT_Console);
  uint16           sys_ver;
  uint16           version;
  logical           term = NO;

BEGINSEQ

  RegisterProcess();
  printf("Set ODABA2 System Version for Dictionary");
  
  if ( CheckRuntimeParms(argc,argv,2,3) )            ERROR

  DictionaryHandle   sysdict(uti_client,argv[1],PI_Write,YES,CUR_VERSION);  
	                                             SDBCERR
  sys_ver = sysdict.GetSystemVersion();
  if ( argc > 2 )
    sys_ver = atoi(argv[2]);
  
  while ( (version = sysdict.GetVersion()) < sys_ver )
  {
    sysdict.NewVersion();                            SDBCERR
    TWAIT(2);
    sysdict.SetVersion(version+1);
  }

  printf("\n  terminated successfully.\n");
    


RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
