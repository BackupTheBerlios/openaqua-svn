/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cValueListEdit

\brief    


\date     $Date: 2006/06/01 17:11:46,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cValueListEdit"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <scValueListEdit.hpp>


/******************************************************************************/
/**
\brief  CheckSave - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckSave"

logical cValueListEdit :: CheckSave ( )
{
  CTX_Project        *proj_ctx        = GetProjectContext();
  PropertyHandle     *prophdl         = GetPropertyHandle();    
  DBObjectHandle      dbo;
  logical             term            = NO;
BEGINSEQ
/*
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
  if ( GetDATDB().GetDictionary().CheckExpression(GetDATDB(),
                                   prophdl->GetString("sys_ident") ,
                                   funct_ph->GetString("sys_ident"),
                                   impl_ph->GetString("sys_ident")) )
    SetupOutput("... Errors found in expression\n",NO);
  else
    SetupOutput("... no errors found\n",NO);
*/
ENDSEQ
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

int32 cValueListEdit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cValueListEdit();
  return(NO);


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

logical cValueListEdit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("CheckSave",ALINK(this,cValueListEdit,CheckSave)),
                           cfte("GenerateInclude",ALINK(this,cValueListEdit,GenerateInclude)),
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
\brief  GenerateInclude - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateInclude"

logical cValueListEdit :: GenerateInclude ( )
{
  PropertyHandle     *prophdl         = GetPropertyHandle();
  int32               curidx          = UNDEF;
  logical             reserve_project = NO;
  logical             term            = NO;
  SetSysVariable("PROJECT_NAME",ODEContext(this)->ProjectName());
  
  ODEOutput(this,"...Creating Enum-include file",YES);
  if ( !prophdl->ExecuteExpression(GetRESDB(),"EnumIncludeO()").IsValid() )
    ODEOutput(this,"...  terminated with errors\n",NO);
  else
    ODEOutput(this,"...  done.\n",NO);

  return(term);
}

/******************************************************************************/
/**
\brief  cValueListEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cValueListEdit"

     cValueListEdit :: cValueListEdit ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cValueListEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cValueListEdit"

     cValueListEdit :: ~cValueListEdit ( )
{



}


