/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDoubleTabSlave

\brief    


\date     $Date: 2006/04/24 13:35:27,38 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cDoubleTabSlave"

#include  <pdesign.h>
#include  <sNString.hpp>
#include  <scDoubleTabSlave.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cDoubleTabSlave :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cDoubleTabSlave();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cDoubleTabSlave :: DoAfterSelect ( )
{

  GetHighContext()->SetParm(NString(GetDisplayLevel()));
  GetHighContext()->ExecuteFunction("DisplayLevelChanged");
  return NO;
}


