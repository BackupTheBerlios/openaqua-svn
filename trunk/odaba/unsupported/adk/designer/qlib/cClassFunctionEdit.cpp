/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassFunctionEdit

\brief    


\date     $Date: 2006/08/28 07:57:43,20 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassFunctionEdit"

#include  <pdesign.h>
#include  <stdinc.h>
#include  <sPropertyHandle.hpp>
#include  <sRegExp.hpp>
#include  <scODCFunctionImpl.hpp>
#include  <scPFunctionEdit.hpp>
#include  <igvts.h>
#include  <spODE.hpp>
#include  <spc1_ODC_ImpClass.hpp>
#include  <scClassFunctionEdit.hpp>


/******************************************************************************/
/**
\brief  CheckSave - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckSave"

logical cClassFunctionEdit :: CheckSave ( )
{
  CTX_Project        *proj_ctx        = GetProjectContext();
  PropertyHandle     *prophdl         = GetPropertyHandle();    
  PropertyHandle     *funct_ph        = prophdl->GPH("pfunctions");    
  PropertyHandle     *impl_ph         = funct_ph->GPH("implementations");    
  PropertyHandle     *imp_type        = funct_ph->GPH("imp_type"); 
  DBObjectHandle      dbo;
  logical             term            = NO;
BEGINSEQ
  SetupOutput("... ",NO);
  SetupOutput(prophdl->GetString("sys_ident"),NO);
  SetupOutput(": checking expression ",NO);
  SetupOutput(funct_ph->GetString("sys_ident"),NO);
  SetupOutput("\n",NO);
  
  ExecuteAction("Save",ACT_Function);
  if ( !impl_ph->IsPositioned() )                    LEAVESEQ
  
  if ( *imp_type != "MT_OQLExpression" )
  {
    SetupOutput("Function is not an expression - not checked.\n",NO);
    LEAVESEQ
  }
  if ( GetWorkDictionary().CheckExpression(GetDATDB(),
                                   prophdl->GetString("sys_ident") ,
                                   funct_ph->GetString("sys_ident"),
                                   impl_ph->GetString("sys_ident")) )
    SetupOutput("... Errors found in expression\n",NO);
  else
    SetupOutput("... no errors found\n",NO);
    

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Compile - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compile"

logical cClassFunctionEdit :: Compile ( )
{
  CTX_Project        *proj_ctx        = GetProjectContext();
  PropertyHandle     *prophdl         = GetPropertyHandle();    
  NBuffer             comp_out;
  int32               curidx          = UNDEF;
  int32               rc              = ERIC;
  logical             reserve_project = YES;
  logical             term            = NO;
BEGINSEQ
  proj_ctx->ExecuteFunction("GenerateIncludes");
  
  if ( (curidx = StartClassAction(YES,reserve_project)) == ERIC) 
                                                     ERROR
  SetupOutput("...Creating source code file ...",NO);
  if ( prophdl->ExecuteExpression(GetRESDB(),"ClassSourceCodeO()").IsValid() )
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
  
    *prophdl->GPH("req_compile") = (char*)(rc ? "CPS_failed" : "CPS_ready");
    prophdl->ExecuteInstanceAction("SetupModLevel",NULL);
  }


RECOVER
  term = YES;
ENDSEQ
  StopClassAction(reserve_project,curidx);
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

int32 cClassFunctionEdit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassFunctionEdit();
  return(NO);


}

/******************************************************************************/
/**
\brief  DistributeSearchReplace - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DistributeSearchReplace"

logical cClassFunctionEdit :: DistributeSearchReplace ( )
{

  return ( DistributeSearchReplace(ODEContext(this)->GetCurSearchReplace()) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  ode_search_replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DistributeSearchReplace"

logical cClassFunctionEdit :: DistributeSearchReplace (ODE_SearchReplace *ode_search_replace )
{
  pODE            *ode_ctx = ODEContext(this);
  CTX_Control     *context = NULL;
  logical          term    = NO;
BEGINSEQ
  if ( !ode_search_replace )                         P_ERR(99)
    
  switch ( ode_search_replace->GetLocation() )
  {
    case 1   : // FSR_Implementation
               context = GetImplementationContext();
               break;
    case 2   : // FSR_Function
               context = GetPFunctionContext();
               break;
    case 3   : // FSR_Class
               context = this;
               break;
    case 4   : // FSR_Project
               context = ode_ctx;
               break;
    default  : ERROR
  }
    
  if ( !context )                                    P_ERR(99)
  
  term = context->ExecuteFunction("ExecSearchReplace");
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 cClassFunctionEdit :: DoAfterOpen ( )
{
  pODE            *ode_ctx     = ODEContext(this);
BEGINSEQ
  search_replace.Init(GetRESDictionary());
  
  if ( !ode_ctx )                                    ERROR

  ode_ctx->SetTargetContext(this);
  ode_ctx->SetImpClassContext(this);
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DoBeforeClose - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

int8 cClassFunctionEdit :: DoBeforeClose ( )
{
  pODE            *ode_ctx     = ODEContext(this);
BEGINSEQ
  search_replace.Deinit();
  
  if ( !ode_ctx )                                    ERROR

  ode_ctx->SetTargetContext(NULL);
RECOVER

ENDSEQ
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

logical cClassFunctionEdit :: ErrorLookup ( )
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
\brief  ExecSearchReplace - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecSearchReplace"

logical cClassFunctionEdit :: ExecSearchReplace ( )
{
  CTX_Control       *context   = GetPFunctionContext();
  PropertyHandle    *pfunct    = GetPropertyHandle()->GPH("pfunctions");
  char              *find_next = "Y";
  int                count     = pfunct->GetCount();
  int                findx0    = 0;
  logical            term      = NO;
BEGINSEQ
  if ( !context )                                    ERROR
 
  for ( findx0 = 0; *find_next == 'Y' && findx0 < count; findx0++ )
  {
    pfunct->Get(findx0);
    if ( context->ExecuteFunction("ExecSearchReplace") )
                                                     ERROR
    find_next = context->GetResult();
  }
RECOVER
  find_next = "N";
  term      = YES;
ENDSEQ
  SetResult(find_next);
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

logical cClassFunctionEdit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("CheckSave",ALINK(this,cClassFunctionEdit,CheckSave)),
                           cfte("Compile",ALINK(this,cClassFunctionEdit,Compile)),
                           cfte("DistributeSearchReplace",ALINK(this,cClassFunctionEdit,DistributeSearchReplace)),
                           cfte("ErrorLookup",ALINK(this,cClassFunctionEdit,ErrorLookup)),
                           cfte("ExecSearchReplace",ALINK(this,cClassFunctionEdit,ExecSearchReplace)),
                           cfte("FindEntry",ALINK(this,cClassFunctionEdit,FindEntry)),
                           cfte("GenerateInclude",ALINK(this,cClassFunctionEdit,GenerateInclude)),
                           cfte("Goto",ALINK(this,cClassFunctionEdit,Goto)),
                           cfte("GotoLine",ALINK(this,cClassFunctionEdit,GotoLine)),
                           cfte("InputHelp",ALINK(this,cClassFunctionEdit,InputHelp)),
                           cfte("RenameEntry",ALINK(this,cClassFunctionEdit,RenameEntry)),
                           cfte("SelectPFunction",ALINK(this,cClassFunctionEdit,SelectPFunction)),
                           cfte("SetPFunctionNotInit",ALINK(this,cClassFunctionEdit,SetPFunctionNotInit)),
                           cfte("Update",ALINK(this,cClassFunctionEdit,Update)),
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
\brief  FindEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindEntry"

logical cClassFunctionEdit :: FindEntry ( )
{


  return ( SearchReplace(NO) );


}

/******************************************************************************/
/**
\brief  GenerateInclude - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateInclude"

logical cClassFunctionEdit :: GenerateInclude ( )
{
  PropertyHandle     *prophdl         = GetPropertyHandle();
  int32               curidx          = UNDEF;
  logical             reserve_project = NO;
  logical             term            = NO;
BEGINSEQ
  if ( (curidx = StartClassAction(NO,reserve_project)) == ERIC )   
                                                     ERROR 
  SetupOutput("...Creating include file",YES);
  if ( !prophdl->ExecuteExpression(GetRESDB(),"ClassIncludeO()").IsValid() )
    SetupOutput("...  terminated with errors\n",NO);
  else
    SetupOutput("...  done.\n",NO);
  
  StopClassAction(reserve_project,curidx);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetImplementationContext - 



\return ctx_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplementationContext"

CTX_Control *cClassFunctionEdit :: GetImplementationContext ( )
{

  return ( GetFieldContext("function.implementations.edit.code") );

}

/******************************************************************************/
/**
\brief  GetPFunctionContext - 



\return ctx_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPFunctionContext"

CTX_Control *cClassFunctionEdit :: GetPFunctionContext ( )
{

  return ( GetFieldContext("edit_class_function_tab.function") );

}

/******************************************************************************/
/**
\brief  Goto - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Goto"

logical cClassFunctionEdit :: Goto ( )
{
  char     *string = NULL;

  return (   (string = GetString("","","1"))
           ? GotoLine(string) 
           : NO                  );


}

/******************************************************************************/
/**
\brief  GotoLine - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GotoLine"

logical cClassFunctionEdit :: GotoLine ( )
{

  return ( GotoLine(Parm(1)) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  line_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GotoLine"

logical cClassFunctionEdit :: GotoLine (char *line_string )
{
  pc1_ODC_ImpClass       cur_pc(GetPropertyHandle());
  CTX_Control           *context   = NULL;
  char                  *string    = NULL;
  char                  *area      = NULL;
  std::string            parm_string;
  int32                  line      = 0;
  int32                  findx0    = 0;
  int32                  iindx0    = 0;
  logical                term      = NO;

BEGINSEQ
  if ( !line_string )                                ERROR
  line = strtol(line_string,NULL,10);
  if ( !(area = cur_pc.LocateSource(line,findx0,iindx0)) )
                                                    ERROR
  if ( !(context = GetPFunctionContext()) )         ERROR
  context->GetPropertyHandle()->Get(findx0);
  if ( !(context = context->GetFieldContext("implementations")) )
                                                    ERROR
  context->GetPropertyHandle()->Get(iindx0);
  if ( !(context = context->GetFieldContext("edit")) )
                                                    ERROR
  parm_string.append(PropertyHandle(line).GetString());
  parm_string.append(",");
  parm_string.append(area);
  context->SetParm((char *)parm_string.c_str());
  context->ExecuteFunction("GotoLine");
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InputHelp - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputHelp"

logical cClassFunctionEdit :: InputHelp ( )
{
  CTX_Control   *context = GetFieldContext("function.implementations.edit");
  logical        term    = NO;
BEGINSEQ
  if ( !context )                                    ERROR

  context->SetParm(Parm(1));
  context->ExecuteFunction("InputHelp");
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RenameEntry - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RenameEntry"

logical cClassFunctionEdit :: RenameEntry ( )
{

  return ( SearchReplace(YES) );  


}

/******************************************************************************/
/**
\brief  SearchReplace - 



\return term - 

\param  do_replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchReplace"

logical cClassFunctionEdit :: SearchReplace (logical do_replace )
{
  pODE            *ode_ctx = ODEContext(this);
  logical          term    = NO;
BEGINSEQ
  SetupOutput(do_replace ? "Replace" : "Find",YES);
  
  if ( !ode_ctx )                                    ERROR
    
  if ( search_replace.GetData("FSR_Function",do_replace,this) )
                                                     ERROR  
  ode_ctx->SetCurSearchReplace(&search_replace);
  term = DistributeSearchReplace(&search_replace);
  ode_ctx->SetCurSearchReplace(NULL);

  SetupOutput(" reached starting point of the search\n",NO);


RECOVER
  SetupOutput(" terminated with error\n",NO);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SelectPFunction - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectPFunction"

logical cClassFunctionEdit :: SelectPFunction ( )
{
  char           *parm1     = Parm(1);
  PropertyHandle *pfunc_ph  = GetPFunctionContext()->GetPropertyHandle();
  logical         term      = NO;

BEGINSEQ
  if ( !parm1 || !pfunc_ph )                         ERROR

  pfunc_ph->Get(pfunc_ph->StringToKey(parm1));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPFunctionNotInit - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPFunctionNotInit"

logical cClassFunctionEdit :: SetPFunctionNotInit ( )
{
  CTX_Control     *context = GetPFunctionContext();
  return ( context ? context->ExecuteFunction("SetNotInit") : YES );


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

logical cClassFunctionEdit :: SetupOutput (char *string, logical clear_opt )
{

  return ( ODEOutput(this,string,clear_opt) );

}

/******************************************************************************/
/**
\brief  StartClassAction - 



\return cur_pfunct_indx0 - 

\param  write_opt - 
\param  reserve_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartClassAction"

int32 cClassFunctionEdit :: StartClassAction (logical write_opt, logical reserve_opt )
{
  pODE               *ode_ctx   = ODEContext(this);
  PropertyHandle     *prophdl   = GetPropertyHandle();    
  PropertyHandle     *module    = prophdl->GPH("module");    
  PropertyHandle     *project   = NULL;    
  char               *prj_names = NULL;
  PropertyHandle     *pfunct_ph = GetPFunctionContext()->GetPropertyHandle(); 
  int32               curidx    = pfunct_ph->GetCurrentIndex();
BEGINSEQ
  prophdl->GetObjectHandle().DisableEventHandling(); 
  prophdl->Save();
  
  SetupOutput("  ",NO);
  SetupOutput(prophdl->GPH("sys_ident")->GetString(),NO);
  
  if ( !(prj_names = ode_ctx->ProjectName()) )       P_ERR(8)
       
  if (   write_opt 
       ? prophdl->NoWrite() 
       : !prophdl->IsSelected() )                    P_ERR(9)
    
  if ( !module->Get(FIRST_INSTANCE) )                P_ERR(6)
  if ( strcmp(module->GPH("sys_ident")->GetString(),prj_names) )
                                                     P_ERR(7)

  if ( reserve_opt && ode_ctx->ReserveProject() )    ERROR
  Pointer(POINTER_Wait);
RECOVER
  prophdl->GetObjectHandle().EnableEventHandling(); 
  curidx = ERIC;
ENDSEQ
  return(curidx);
}

/******************************************************************************/
/**
\brief  StopClassAction - 



\return term - 

\param  reserve_opt - 
\param  cur_pfunct_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopClassAction"

logical cClassFunctionEdit :: StopClassAction (logical reserve_opt, int32 cur_pfunct_indx0 )
{
  pODE               *ode_ctx   = ODEContext(this);
  PropertyHandle     *prophdl   = GetPropertyHandle();    
  PropertyHandle     *pfunct_ph = GetPFunctionContext()->GetPropertyHandle(); 
  logical             term      = NO;
  Pointer(POINTER_Arrow);
  prophdl->GetObjectHandle().EnableEventHandling();

  if ( reserve_opt )
    ode_ctx->ReleaseProject();

  if ( cur_pfunct_indx0 != AUTO )
    pfunct_ph->Get(cur_pfunct_indx0);
  return(term);
}

/******************************************************************************/
/**
\brief  Update - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical cClassFunctionEdit :: Update ( )
{
  pc1_ODC_ImpClass    prop_pc(GetPropertyHandle());  
  int32               curidx          = UNDEF;
  char               *result          = NULL;
  logical             reserve_project = NO;
  logical             term            = NO;
BEGINSEQ
  if ( (curidx = StartClassAction(YES,reserve_project)) == ERIC )
                                                       ERROR
  if ( prop_pc.ExecuteInstanceAction("SetupReferences",NULL) )
    term = YES;

  if ( prop_pc.SetupExecuteFunction(this) )
    term = YES;
  
  StopClassAction(reserve_project,curidx);
  
  GetImplementationContext()->FillControl();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cClassFunctionEdit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassFunctionEdit"

     cClassFunctionEdit :: cClassFunctionEdit ( )
                     : CTX_Control (),
  search_replace()
{



}

/******************************************************************************/
/**
\brief  ~cClassFunctionEdit - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassFunctionEdit"

     cClassFunctionEdit :: ~cClassFunctionEdit ( )
{



}


