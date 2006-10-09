/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassRefList

\brief    


\date     $Date: 2006/04/24 13:33:06,24 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassRefList"

#include  <pdesign.h>
#include  <scClassRefList.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassRefList :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassRefList();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoBeforeInsertData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeInsertData"

int8 cClassRefList :: DoBeforeInsertData ( )
{
  CTX_Project       *prj_ctx  = GetProjectContext();
  PropertyHandle    *prophdl  = GetCurrentPropertyHandle();
  PropertyHandle    *init_ph  = GetInitPropertyHandle();
  PropertyHandle    *newtype  = init_ph->GPH("classname");
  char               executed = NO;
BEGINSEQ
  if ( newtype->IsEmpty() )                          ERROR
  
  prj_ctx->SetParm(newtype->GetString());
  if ( prj_ctx->ExecuteFunction("ProvideReferencedType") )
                                                     ERROR
  *init_ph->GPH("source_class") = *prophdl->GetParentProperty()->GPH("sys_ident");
  *init_ph->GPH("code_level")   = "IRL_Member";
  
    

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cClassRefList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassRefList"

                        cClassRefList :: cClassRefList ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cClassRefList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassRefList"

                        cClassRefList :: ~cClassRefList ( )
{



}


