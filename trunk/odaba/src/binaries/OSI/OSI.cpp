//******************************************************************/
//* OSI
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2006/02/05
//******************************************************************/

#define    OBJ_ID  "OSI"

#include  <puti.h>
 
 
 
#include  <sNParm.hpp>
#include  <sNString.hpp>
#include  <sOScript.hpp>





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
  ODABAClient      uti_client(NULL,"ODABA Script Interpreter",argv[0],APT_Console);
  char            *string;
  char            *parameters  = NULL;
  char            *ini_file    = NULL;
  char            *entry_point = NULL;
  char            *dictionary  = NULL;
  char             parmstring[1024];
  ParmList         parmlist;
  NString          nstring;
  char            *parm;
  int32            indx0 = 0;
  PropertyHandle   ph;
  int              rc = 0;
BEGINSEQ

  if ( CheckRuntimeParms(argc,argv,1,5) )            ERROR

  GetParmString(parmstring,argc,argv);
  
  if ( string = GetKeyParm(parmstring,"-DB",NO,YES) )
    SetSysVariable("OSI_DEBUG","YES");
  if ( string = GetKeyParm(parmstring,"-I",NO,YES) )
    ini_file = strdup(string);
  if ( string = GetKeyParm(parmstring,"-D",NO,YES) )
    dictionary = strdup(string);
  if ( string = GetKeyParm(parmstring,"-P",NO,YES) )
    parameters = strdup(string);
  if ( string = GetKeyParm(parmstring,"-E",NO,YES) )
    entry_point = strdup(string);
  else
    entry_point = strdup("main");

  printf("ODABA Script Interpreter: %s:%s(%s)\n",argv[1],entry_point,parameters ? parameters : "");
  
  if ( parameters) 
  {
    NParm     parms(parameters,',',NO);
    while ( parm = parms(indx0++) )
    {
      nstring = '\'';
      nstring += parm;
      nstring += '\'';
      parmlist.AddParm(ph,nstring);
    }
  }
  // wir wollen das Script-Objekt gleich wieder destruieren
  {
    OScript script(argv[1],ini_file,dictionary);       SDBCERR
    script.Execute(entry_point,&parmlist);
  }  
  if ( entry_point )
    free(entry_point);
  if ( dictionary )
    free(dictionary);
  if ( parameters )
    free(parameters);
  if ( ini_file )
    free(ini_file);

statistics1.Print("Create",YES);
statistics0.Print("Initialize",NO);
statistics2.Print("Execute 1",NO);
statistics3.Print("Execute 2",NO);

RECOVER

  return(1);

ENDSEQ

  uti_client.ShutDown();
  return(0);
}
