/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cMemberType

\brief    


\date     $Date: 2006/04/24 13:39:02,63 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cMemberType"

#include  <pdesign.h>
#include  <scMemberType.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cMemberType :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cMemberType();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterStoreData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterStoreData"

int8 cMemberType :: DoAfterStoreData ( )
{
  PropertyHandle  *prophdl  = GetPropertyHandle();
  CTX_Project     *prj_ctx  = GetProjectContext();
  logical          executed = NO;
  prj_ctx->SetParm(prophdl->GetString());
  prj_ctx->ExecuteFunction("ProvideType");
  return(executed);
}

/******************************************************************************/
/**
\brief  cMemberType - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cMemberType"

                        cMemberType :: cMemberType ( )
                     : CTX_Control()
{



}

/******************************************************************************/
/**
\brief  ~cMemberType - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cMemberType"

                        cMemberType :: ~cMemberType ( )
{



}


