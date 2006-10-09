//******************************************************************/
//* BackupDB
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/10/03
//******************************************************************/

#define    OBJ_ID  "BackupDB"

#include  <puti.h>
 
 
#include  <ifil.h>
 





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
  ODABAClient      uti_client;
  char            *target   = NULL;
  char             string[1024];
  logical          term      = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"Check Database",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);

  printf("\nBackup database");
  
  if ( CheckRuntimeParms(argc,argv,1,2) )            ERROR
  if ( uti_handle.sdbures->SetupVariables("BackupDB") ) 
                                                     ERROR
  uti_client.Initialize(argv[1],"Backup Database");
  
  if ( argc > 2 ) 
    target = argv[2];
  else
  {
    strcpy(string,GetSectionVariable("DATABASE","BackupDB"));
    filextr(string,"ozi");
    target = string;
  }
      
  printf("\n         from: %s",GetSectionVariable("DATABASE","BackupDB"));
  printf("\n           to: %s\n",target);
  
  if ( BackupDB(uti_handle,target) )                ERROR
  
  printf("\n ... terminated successfully.\n");
RECOVER

  printf("\n ... terminated with errors.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
