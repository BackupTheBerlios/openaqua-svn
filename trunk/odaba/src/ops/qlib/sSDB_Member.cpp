/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    sSDB_Member

\brief    


\date     $Date: 2006/06/13 22:49:42,32 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Member"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <sSDB_Member.hpp>
#include  <scfte.hpp>
#include  <ssSDB_Member.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_Member :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_Member();
  return(NO);

}

/******************************************************************************/
/**
\brief  DBRead - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sSDB_Member :: DBRead ( )
{

  return(SetupStructReference(NO));

}

/******************************************************************************/
/**
\brief  DBStore - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStore"

logical sSDB_Member :: DBStore ( )
{

  return(SetupStructReference(YES));

}

/******************************************************************************/
/**
\brief  DataTypeCString - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

logical sSDB_Member :: DataTypeCString ( )
{
  PropertyHandle   *ph            = GetPropertyHandle();
  char             *result_string = "";
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsPositioned() )                         CTXERR(99)
    
  if ( !(result_string = ((SDB_Member *)ph->Get().GetData())->DataTypeCString(UNDEF)) )
    result_string = "";

RECOVER
  term = YES;
ENDSEQ
  ph->SetActionResult(result_string);
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return term - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical sSDB_Member :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DataTypeCString",ALINK(this,sSDB_Member,DataTypeCString)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = CTX_Structure::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupStructReference - 


\return term - 

\param  auto_correct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupStructReference"

logical sSDB_Member :: SetupStructReference (logical auto_correct )
{
  PropertyHandle    *ph            = GetPropertyHandle();
  PropertyHandle    *ddetype       = NULL;
  PropertyHandle    *type          = NULL;
  PropertyHandle    *base_ph       = NULL;
  PropertyHandle    *base_typetype = NULL;
  logical            term          = NO;
BEGINSEQ
  if ( !auto_correct )                               LEAVESEQ
  if ( !ph->IsServer() || ph->IsPathExpression() )   LEAVESEQ
  if ( !ph->IsPositioned() || !ph->IsWrite() )       LEAVESEQ

  type    = ph->GPH("type");
  if ( type->GetLOID() )                             LEAVESEQ

  ddetype = ph->GPH("ddetype");
  if ( !ddetype->GetCollectionProperty()->Inherits("SDB_Member") )
                                                     LEAVESEQ
    
// SDB_ViewExtent
  if ( type->GetParentProperty() != type->GetCollectionProperty() )
                                                     LEAVESEQ
  
  if ( !(base_ph = type->GetBaseProperty()) )        ERROR
  base_typetype = base_ph->GPH("typetype");
  
  if ( base_ph->Get(*ddetype) && *base_typetype != 1 )
  {
    type->Provide(*ddetype);
    type->ToTop();
  }
  base_ph->ToTop();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sSDB_Member - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Member"

     sSDB_Member :: sSDB_Member ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~sSDB_Member - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Member"

     sSDB_Member :: ~sSDB_Member ( )
{



}


