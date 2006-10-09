/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cMainFunctionEdit

\brief    


\date     $Date: 2006/06/13 22:59:55,76 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cMainFunctionEdit"

#include  <pdesign.h>
#include  <scMainFunctionEdit.hpp>


/******************************************************************************/
/**
\brief  Compile - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compile"

logical cMainFunctionEdit :: Compile ( )
{
  CTX_Project        *proj_ctx        = GetProjectContext();
  PropertyHandle     *prophdl         = GetPropertyHandle();    
  NBuffer             comp_out;
  int32               curidx          = UNDEF;
  int32               rc              = ERIC;
  logical             reserve_project = YES;
  logical             term            = NO;
BEGINSEQ
//  if ( (curidx = StartClassAction(YES,reserve_project)) == ERIC) 
//                                                     ERROR
  SetupOutput("...Creating source code file ...",NO);
  if ( prophdl->ExecuteExpression(GetRESDB(),"SourceCode()").IsValid() )
    SetupOutput("...  done.\n",NO);
  else
  {
    SetupOutput("...  terminated with errors, compile not started\n",NO);
    ERROR
  }
  
  if ( prophdl->ExecuteInstanceAction("GetCompileCommand",NULL) )
    SetupOutput("Error: providing compile command\n",NO);
  else
  {
    rc = ExecuteCommand(prophdl->GetActionResult(),comp_out,YES,NO);
    SetupOutput(comp_out,NO);
    if ( !rc && strstr(comp_out,"ERROR") )
      rc = ERIC;
      
    if ( rc )
    {
      *prophdl->GPH("req_compile") = (char*)(rc ? "CPS_failed" : "CPS_ready");
      term = YES;
    }
    prophdl->ExecuteInstanceAction("SetupModLevel",NULL);
  }


RECOVER
  term = YES;
ENDSEQ
//  StopClassAction(reserve_project,curidx);
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cMainFunctionEdit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cMainFunctionEdit();
  return(NO);


}

/******************************************************************************/
/**
\brief  ErrorLookup - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ErrorLookup"

logical cMainFunctionEdit :: ErrorLookup ( )
{
  CTX_Project        *proj_ctx        = GetProjectContext();
  PropertyHandle     *prophdl         = GetPropertyHandle();    
  NString             command;
  NBuffer             buffer;
  logical             term            = NO;
BEGINSEQ
  if ( !prophdl->GetInstanceContext() )             ERROR
  if ( prophdl->ExecuteInstanceAction("GetProjectPath","ERC_Batch") )
    SetupOutput("Error providing command path\n",NO);
  else
  {
    command = prophdl->GetActionResult();
    command += "ShowErrors.bat";
    command += ' ';
    command += prophdl->GetString("sys_ident");
    ExecuteCommand(command,buffer,YES,NO);
    SetupOutput(buffer,YES);
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cMainFunctionEdit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Compile",ALINK(this,cMainFunctionEdit,Compile)),
                           cfte("ErrorLookup",ALINK(this,cMainFunctionEdit,ErrorLookup)),
                           cfte("Link",ALINK(this,cMainFunctionEdit,Link)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_Control::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Link - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Link"

logical cMainFunctionEdit :: Link ( )
{
  CTX_Project        *proj_ctx        = GetProjectContext();
  PropertyHandle     *prophdl         = GetPropertyHandle();    
  NBuffer             comp_out;
  int32               curidx          = UNDEF;
  int32               rc              = ERIC;
  logical             reserve_project = YES;
  logical             term            = NO;
BEGINSEQ
//  if ( (curidx = StartClassAction(YES,reserve_project)) == ERIC) 
//                                                     ERROR
  SetupOutput("",YES);
  if ( Compile() )                                   ERROR
  SetupOutput("...Link executable ...\n",NO);
  
  if ( prophdl->ExecuteInstanceAction("GetLinkCommand",NULL) )
    SetupOutput("Error: providing link command\n",NO);
  else
  {
    rc = ExecuteCommand(prophdl->GetActionResult(),comp_out,YES,NO);
    SetupOutput(comp_out,NO);
  }


RECOVER
  term = YES;
ENDSEQ
//  StopClassAction(reserve_project,curidx);
  return(term);
}

/******************************************************************************/
/**
\brief  SetupOutput - 


\return term - 

\param  string - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupOutput"

logical cMainFunctionEdit :: SetupOutput (char *string, logical clear_opt )
{

  return ( ODEOutput(this,string,clear_opt) );

}

/******************************************************************************/
/**
\brief  cMainFunctionEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cMainFunctionEdit"

     cMainFunctionEdit :: cMainFunctionEdit ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cMainFunctionEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cMainFunctionEdit"

     cMainFunctionEdit :: ~cMainFunctionEdit ( )
{



}


