/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cResourceRef

\brief    


\date     $Date: 2006/06/01 17:09:58,53 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cResourceRef"

#include  <pdesign.h>
#include  <spc1_ODC_ImpClass.hpp>
#include  <scResourceRef.hpp>


/******************************************************************************/
/**
\brief  AssociateEntry - Destruktor


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AssociateEntry"

logical cResourceRef :: AssociateEntry ( )
{
  PropertyHandle *prophdl       = GetPropertyHandle();
  PropertyHandle *parent        = prophdl->GetParentProperty();
  PropertyHandle *context_class = prophdl->GPH("context_class");
  logical         edit          = NO;
  logical         term          = NO;
BEGINSEQ
  if ( !parent->Exist() )                            ERROR

  if ( prophdl->Get(FIRST_INSTANCE) )
    if ( GetDecisionOk(4) )
      prophdl->Delete();
  
  if ( !prophdl->Get(FIRST_INSTANCE) )
    prophdl->Add(Key::NewAutoident());
  else
    if ( context_class->Get(FIRST_INSTANCE) )        LEAVESEQ

  pc1_ODC_ImpClass  impl(GetDATDB(),PI_Update);      P_SDBCERR
  if ( !impl.ProvideContextClass(parent,this,&edit) )
  {
    context_class->Add(*impl.GPH("sys_ident"));
    if ( edit )
      ExecuteWindow(context_class,"ODC_ImpClass","Edit",NO);
  }
RECOVER
  term = YES;
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

int32 cResourceRef :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cResourceRef();
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

logical cResourceRef :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("AssociateEntry",ALINK(this,cResourceRef,AssociateEntry)),
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
\brief  cResourceRef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cResourceRef"

     cResourceRef :: cResourceRef ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cResourceRef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cResourceRef"

     cResourceRef :: ~cResourceRef ( )
{



}


