//******************************************************************/
//* DBError
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/03/22
//******************************************************************/

#define    OBJ_ID  "DBError"

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
  CommandLine cl(NULL);
  char       *ini_file = NULL;
  logical     term     = NO;
BEGINSEQ

  std::cout << std::endl << "Running Error Lookup Utility ..." << std::endl;
  std::cout.flush();
  
  if ( CheckRuntimeParms(argc,argv,2,7) )            ERROR
  cl.InputFromArguments(argc,argv);
  
  if ( !(ini_file = cl.GetOption('I')) )
    ini_file = cl.GetOption('i');
  
  ODABAClient uti_client(ini_file,"DBError",argv[0],APT_Console);
  CSUtilityHandle  uti_handle(uti_client,"DBError",ini_file,argv[0],APT_Console);
  
  if ( ini_file )
  {
    term = uti_handle.sdbures->SetupVariables("DBError");
  }
  else
  {
    uti_handle.sdbures; // hier fehlt noch alles
  }

  
  std::cout << std::endl << argv[3] << " DBError terminated successfully." << std::endl;
  std::cout.flush();

  uti_client.ShutDown();

RECOVER

  term = YES;

ENDSEQ

  return(term);
}
