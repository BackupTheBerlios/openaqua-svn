/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF)
\class    cVirtualPFunction



\date     $Date: 2006/03/23 18:29:56,57 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cVirtualPFunction"

#include  <pdesign.h>
#include  <scVirtualPFunction.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc -

\param  ctx_ctl_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cVirtualPFunction :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cVirtualPFunction();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterOpen

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 cVirtualPFunction :: DoAfterOpen ( )
{
  int8           executed = NO;
  source.Open(GetDATDB(),"ODC_PFunction",PI_Update);
  SetPropertyHandle(&source);
  return(executed);
}

/******************************************************************************/
/**
\brief  cVirtualPFunction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cVirtualPFunction"

                        cVirtualPFunction :: cVirtualPFunction ( )
                     :   CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cVirtualPFunction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cVirtualPFunction"

                        cVirtualPFunction :: ~cVirtualPFunction ( )
{



}


