/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pRetvalInODC_Function



\date     $Date: 2006/04/21 14:08:36,55 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pRetvalInODC_Function"

#include  <pfmodel.h>
#include  <spc_ODC_PFunction.hpp>
#include  <spRetvalInODC_Function.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  CTX_Property_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pRetvalInODC_Function :: Create (CTX_Property **CTX_Property_ptrp )
{

  *CTX_Property_ptrp = new pRetvalInODC_Function();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBInserted

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInserted"

logical pRetvalInODC_Function :: DBInserted ( )
{
  PropertyHandle   *prophdl     = GetPropertyHandle();
  logical           term        = NO;
BEGINSEQ
  if ( *prophdl->GetParentProperty()->GPH("retval_name") ==
       *prophdl->GPH("sys_ident")   )               LEAVESEQ
  
  if ( !prophdl->IsServer() )
    ; // re-read parent properties
  else
  {
    pc_ODC_PFunction  pfunct_pc(prophdl->GetCollectionProperty());
    if ( pfunct_pc.InitRetval() )                   ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pRetvalInODC_Function


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pRetvalInODC_Function"

                        pRetvalInODC_Function :: pRetvalInODC_Function ( )
                     : CTX_Property()
{



}

/******************************************************************************/
/**
\brief  ~pRetvalInODC_Function


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pRetvalInODC_Function"

                        pRetvalInODC_Function :: ~pRetvalInODC_Function ( )
{



}


