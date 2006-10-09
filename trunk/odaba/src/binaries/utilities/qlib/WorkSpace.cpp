//******************************************************************/
//* WorkSpace
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/03/22
//******************************************************************/

#define    OBJ_ID  "WorkSpace"

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
  ODABAClient      uti_client(argc > 1 ? argv[1] : NULL,"WorkSpace",argv[0],APT_Console);
  CommandLine      cl(NULL);
  char             tree_opt[3];
  logical          term = NO;
BEGINSEQ

  CSUtilityHandle  uti_handle(uti_client,"WorkSpace",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  
  std::cout << std::endl << "Running Workspace Utility ..." << std::endl;
  std::cout.flush();
  
  if ( CheckRuntimeParms(argc,argv,4,7) )            ERROR
  if ( uti_handle.sdbures->SetupVariables(argv[2]) ) ERROR

  cl.InputFromArguments(argc,argv);
  
  *tree_opt = 0;
  if ( cl.GetOption('T') || cl.GetOption('t') )  
    strcpy(tree_opt,"-T");
    
  if ( UWorkspace(uti_handle,cl.Parm(2),cl.Parm(3),cl.Parm(4),tree_opt) )
                                                     ERROR
  
  std::cout << std::endl << argv[3] << " Workspace terminated successfully." << std::endl;
  std::cout.flush();


RECOVER

  std::cout << std::endl << (argc > 3 ? argv[3] : "")    << " Workspace"
       << (argc > 3 ? "" : " Utility") << " terminated with errors. See error log for details." << std::endl;
  std::cout.flush();
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
