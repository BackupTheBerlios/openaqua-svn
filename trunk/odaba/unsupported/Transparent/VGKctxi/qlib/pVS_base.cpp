/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pVS_base

\brief    


\date     $Date: 2006/07/06 14:31:50,34 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pVS_base"

#include  <pvgkctxi.h>
#include  <spVS_base.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pVS_base :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pVS_base();
  return(NO);


}

/******************************************************************************/
/**
\brief  pVS_base - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pVS_base"

     pVS_base :: pVS_base ( )
                     : CTX_Property()
{



}

/******************************************************************************/
/**
\brief  ~pVS_base - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pVS_base"

     pVS_base :: ~pVS_base ( )
{



}


