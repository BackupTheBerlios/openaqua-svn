/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cPFunctionEdit

\brief    


\date     $Date: 2006/06/13 23:00:29,42 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cPFunctionEdit"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc1_ODC_PFunction.hpp>
#include  <scPFunctionEdit.hpp>


/******************************************************************************/
/**
\brief  Changed - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Changed"

logical cPFunctionEdit :: Changed ( )
{
  CTX_Control  *context = GetImplHeadlineContext();
  PropertyHandle *impls = GetPropertyHandle()->GPH("implementations");
  impls->ExecuteInstanceAction("FillHeadLine",NULL);
  
  return (   context 
           ? context->FillControl() 
           : NO                     );


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

int32 cPFunctionEdit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cPFunctionEdit();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoBeforeFillData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cPFunctionEdit :: DoBeforeFillData ( )
{
  pc1_ODC_PFunction  prop_pc(GetPropertyHandle());
  char               executed = NO;
BEGINSEQ
  if ( !prop_pc.IsSelected() )                       ERROR
  
  if ( UserState1() )
    not_init_objid = prop_pc.GetLOID();
  else 
    if ( not_init_objid != prop_pc.GetLOID() )
    {
      prop_pc.ProvideImplementation();
      not_init_objid = 0;
    }

  
  

RECOVER
  executed = YES;
ENDSEQ
  SetUserState1(NO);
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecSearchReplace - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecSearchReplace"

logical cPFunctionEdit :: ExecSearchReplace ( )
{
  CTX_Control    *context   = GetImplEditContext();
  PropertyHandle *impls     = GetPropertyHandle()->GPH("implementations");
  char           *find_next = "Y";
  int             count     = impls->GetCount();
  int             findx0    = 0;
  logical         term      = NO;

BEGINSEQ
  if ( !context )                                    ERROR
 
  for ( findx0 = 0; *find_next == 'Y' && findx0 < count; findx0++ )
  {
    impls->Get(findx0);
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

logical cPFunctionEdit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Changed",ALINK(this,cPFunctionEdit,Changed)),
                           cfte("ExecSearchReplace",ALINK(this,cPFunctionEdit,ExecSearchReplace)),
                           cfte("SetNotInit",ALINK(this,cPFunctionEdit,SetNotInit)),
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
\brief  GetImplEditContext - 


\return ctx_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplEditContext"

CTX_Control *cPFunctionEdit :: GetImplEditContext ( )
{

  return ( GetFieldContext("implementations.edit") );

}

/******************************************************************************/
/**
\brief  GetImplHeadlineContext - 


\return ctx_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplHeadlineContext"

CTX_Control *cPFunctionEdit :: GetImplHeadlineContext ( )
{

  return ( GetFieldContext("implementations.headline.head_line") );

}

/******************************************************************************/
/**
\brief  SetNotInit - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNotInit"

logical cPFunctionEdit :: SetNotInit ( )
{

  SetUserState1(YES);
  return(NO);

}

/******************************************************************************/
/**
\brief  cPFunctionEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cPFunctionEdit"

     cPFunctionEdit :: cPFunctionEdit ( )
                     : CTX_Control (),
  not_init_objid(0)
{



}

/******************************************************************************/
/**
\brief  ~cPFunctionEdit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cPFunctionEdit"

     cPFunctionEdit :: ~cPFunctionEdit ( )
{



}


