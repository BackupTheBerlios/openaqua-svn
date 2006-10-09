/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassInputHelp

\brief    


\date     $Date: 2006/06/21 16:42:38,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassInputHelp"

#include  <pdesign.h>
#include  <cODE_OBJECTTYPE.h>
#include  <spODE.hpp>
#include  <spc_ClassMemberInputHelp.hpp>
#include  <scClassInputHelp.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return  - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassInputHelp :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassInputHelp();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterDataSet - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDataSet"

int8 cClassInputHelp :: DoAfterDataSet ( )
{
  PropertyHandle  *prophdl     = GetPropertyHandle();
  char            *pixmap      = NULL;
  char             executed    = NO;
BEGINSEQ
  if ( !prophdl->Exist() )                           LEAVESEQ
    
  switch ( (ODE_OBJECTTYPE)prophdl->GPH("type")->GetInt() )
  {
    case OT_Attribute    : pixmap = "SD_Attribute";     break;
    case OT_Reference    : pixmap = "SD_Reference";     break;
    case OT_Relationship : pixmap = "SD_Relationship";  break;
    case OT_Function     : pixmap = "CE_Function";      break;
    case OT_Parameter    : pixmap = "CE_Parameter";     break;
    default              : pixmap = NULL;
  }
    
  if ( pixmap )
    SetLinePixmap(pixmap,0);

  cInputHelpBase::DoAfterDataSet();
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  DoAfterShow - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterShow"

int8 cClassInputHelp :: DoAfterShow ( )
{
  PropertyHandle          *functimp_ph   = NULL;
  pODE                    *ode_ctx       = ODEContext(this);
  pc_ClassMemberInputHelp *memb_input_pc = NULL;
  char                    *access_path   = NULL;
  char                    *datarea       = NULL;
  TypeKey                  type_key;
  int32                    offset        = UNDEF;
BEGINSEQ
  if ( !ode_ctx )                                    ERROR
    
  if ( GetMyClass(type_key) )                        ERROR
  if ( my_class )
    functimp_ph = GetMyFunctImpPH();
      
  datarea = GetContextInfo(offset);    

  if ( memb_input_pc = ode_ctx->GetMemberInputHelpPH(type_key,datarea,offset,NO) )
  {
    memb_input_pc->ResetLocals(memb_input_pc);
    if ( functimp_ph )
    {
      memb_input_pc->SetupList(functimp_ph->GPH("parameters"),OT_Parameter,NO,YES);
      memb_input_pc->SetupVariables(functimp_ph->GetString("start_code"),OT_LocalVariable);
    }
  }    
  if ( SetDatasource(memb_input_pc) )                ERROR    

RECOVER
  if ( access_path )
    free(access_path);
ENDSEQ
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

logical cClassInputHelp :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetAsMyClass",ALINK(this,cClassInputHelp,SetAsMyClass)),
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
    term = cInputHelpBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetAsMyClass - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAsMyClass"

logical cClassInputHelp :: SetAsMyClass ( )
{

  my_class = YES;
  return(NO);
}

/******************************************************************************/
/**
\brief  cClassInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassInputHelp"

     cClassInputHelp :: cClassInputHelp ( )
                     : cInputHelpBase (),
  my_class(NO)
{



}

/******************************************************************************/
/**
\brief  ~cClassInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassInputHelp"

     cClassInputHelp :: ~cClassInputHelp ( )
{



}


