//******************************************************************/
//* DBPerformance
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2005/10/03
//******************************************************************/

#define    OBJ_ID  "DBPerformance"

#include  <puti.h>
 
 
#include  <igvts.h>
 
#include  <sCClient.hpp>
#include  <sHandleInfo.hpp>





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
  Statistic        stats;
  ODABAClient      uti_client;
  CClient         *client;
  long             blocksize = 0;
  char            *string;
  HandleInfo       hi;
  char             attribute[512];
  char             order[512];
  char            *extent = NULL;
  char             parmstring[1024];
  logical          term = NO;
BEGINSEQ

  printf("\nDBPerformance statistics");
  stats.Start();
  uti_client.Initialize(argc > 1 ? argv[1] : NULL,"DBPerformance",argv[0],APT_Console);  
  stats.Stop();
  client = uti_client.GetClientPtr();
  client->GetHandleInfo(client,hi);
  printf("\nConnecting to server:      %s(%i msec)",stats.GetTotalTime(),hi.all_calls_time);
  
  CSUtilityHandle  uti_handle(uti_client,"DBPerformance",argc > 1 ? argv[1] : NULL,argv[0],APT_Console);
  
  if ( CheckRuntimeParms(argc,argv,1,6) )            ERROR

  if ( uti_handle.sdbures->SetupVariables("ComeIn") ) ERROR

  GetParmString(parmstring,argc,argv);
  
  *attribute = 0;
  *order = 0;
  if ( string = GetKeyParm(parmstring,"Order",NO,YES) )
    strcpy(order,string);
  if ( string = GetKeyParm(parmstring,"Blocksize",NO,YES) )
    blocksize = atol(string);
  if ( string = GetKeyParm(parmstring,"Attribute",NO,YES) )
    strcpy(attribute,string);
  if ( (string = GetKeyParm(parmstring,"Extent",NO,YES)) || (string = GetSysVariable("Extent")) )
    extent = string;
  
  if ( DBPerformance(uti_handle,extent,blocksize,*attribute ? attribute : NULL,
                     *order ? order : NULL) )        ERROR

  printf("\n  terminated successfully.\n");

RECOVER

  printf("\n  terminated with error.\n");
  term = YES;

ENDSEQ

  uti_client.ShutDown();
  return(term);
}
