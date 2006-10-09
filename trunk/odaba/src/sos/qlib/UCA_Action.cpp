/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_Action

\brief    


\date     $Date: 2006/03/12 19:22:02,21 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCA_Action"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sSimpleAction.hpp>
#include  <sUCA_Action.hpp>
#include  <sUCA_CAction.hpp>
#include  <sUCA_Function.hpp>
#include  <sUCA_Action.hpp>


/******************************************************************************/
/**
\brief  CheckPermission - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPermission"

logical UCA_Action :: CheckPermission ( )
{

  return(context ? context->CheckPermission(this) : NO);

}

/******************************************************************************/
/**
\brief  Create - 


\return actptr - Action pointer

\param  actype - Action type
\param  acname -
\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

UCA_Action *__cdecl UCA_Action :: Create (ActionType actype, char *acname, CTX_Base *ctxptr )
{
  UCA_Action *actptr = NULL;

BEGINSEQ
  switch ( actype )
  {
    case ACT_Function  : actptr = new UCA_Function(acname,ctxptr);
                         break;
    case ACT_undefined :                             LEAVESEQ
    default            :                             SOSERR(101)
  }

  if ( !actptr )                                     SOSERR(95)
                                                     SOSCERR

RECOVER
  delete actptr;
  actptr = NULL;
ENDSEQ
  return(actptr);

}

/******************************************************************************/
/**
\brief  Execute - 


\return term - Success
-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical UCA_Action :: Execute ( )
{

  return ( YES );

}

/******************************************************************************/
/**
\brief i1


\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical UCA_Action :: Execute (CTX_Base *ctxptr )
{

  context = ctxptr;
  return ( Execute() );

}

/******************************************************************************/
/**
\brief  UCA_Action


\param  acname -
\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UCA_Action"

                        UCA_Action :: UCA_Action (char *acname, CTX_Base *ctxptr )
                     :   context(ctxptr)
{

  gvtxstb(name,acname,ID_SIZE);

}

/******************************************************************************/
/**
\brief  set_context


\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_context"

void UCA_Action :: set_context (CTX_Base *ctxptr )
{

  context = ctxptr;

}

/******************************************************************************/
/**
\brief  ~UCA_Action


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~UCA_Action"

                        UCA_Action :: ~UCA_Action ( )
{



}


