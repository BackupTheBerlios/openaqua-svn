//******************************************************************/
//* ODL
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2006/02/08
//******************************************************************/

#define    OBJ_ID  "ODL"

#include  <puti.h>
 
 
 
#include  <sOSchema.hpp>





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
  ODABAClient      uti_client(NULL,"ODABA Schema Loader",argv[0],APT_Console);
  char            *string;
  char            *ini_file    = NULL;
  char            *dictionary  = NULL;
  char             parmstring[1024];
  int              rc = 0;
BEGINSEQ

  if ( CheckRuntimeParms(argc,argv,2,4) )            ERROR 

  GetParmString(parmstring,argc,argv);
  
  if ( string = GetKeyParm(parmstring,"-I",NO,YES) )
    ini_file = strdup(string);
  if ( string = GetKeyParm(parmstring,"-D",NO,YES) )
    dictionary = strdup(string);

  printf("ODABA Schema Loader: Load %s [to %s]\n",argv[1],dictionary ? dictionary : "script file dictionary");
  // wir wollen das Script-Objekt gleich wieder destruieren
  {
    OSchema schema(argv[1],ini_file,dictionary);       SDBCERR
    if ( schema.LoadSchema() )                         ERROR
  }
  if ( dictionary )
    free(dictionary);
  if ( ini_file )
    free(ini_file);
RECOVER

  return(1);

ENDSEQ

  uti_client.ShutDown();
  return(0);
}
