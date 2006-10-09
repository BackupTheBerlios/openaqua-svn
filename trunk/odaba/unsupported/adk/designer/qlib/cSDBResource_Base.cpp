/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDBResource_Base



\date     $Date: 2006/05/23 21:06:49,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSDBResource_Base"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <scSDBResource_Base.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cSDBResource_Base :: Create (CTX_Control **ctx_ctl_ptrp )
{
  *ctx_ctl_ptrp = new cSDBResource_Base();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterEnter

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterEnter"

int8 cSDBResource_Base :: DoAfterEnter ( )
{
  logical         executed = NO;
BEGINSEQ
  if ( SetDocumentPH() )                            ERROR
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  DoAfterSelect

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cSDBResource_Base :: DoAfterSelect ( )
{
  logical             executed = NO;
BEGINSEQ
  if ( HasFocus() )
    if ( SetDocumentPH() )                          ERROR
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  SetDocumentPH

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDocumentPH"

logical cSDBResource_Base :: SetDocumentPH ( )
{
  logical  term = NO;
  ODEContext(this)->SetDocumentPH(GetCurrentPropertyHandle());
  return(term);
}

/******************************************************************************/
/**
\brief  cSDBResource_Base


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSDBResource_Base"

     cSDBResource_Base :: cSDBResource_Base ( )
                     : CTX_Control()
{
}

/******************************************************************************/
/**
\brief  ~cSDBResource_Base


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSDBResource_Base"

     cSDBResource_Base :: ~cSDBResource_Base ( )
{
}


