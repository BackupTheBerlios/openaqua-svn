/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    ss_Zahlungsweise

\brief    


\date     $Date: 2006/06/20 15:10:54,78 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ss_Zahlungsweise"

#include  <pvgkctxi.h>
#include  <sss_Zahlungsweise.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 ss_Zahlungsweise :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new ss_Zahlungsweise();
  return(NO);


}

/******************************************************************************/
/**
\brief  ss_Zahlungsweise - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ss_Zahlungsweise"

     ss_Zahlungsweise :: ss_Zahlungsweise ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~ss_Zahlungsweise - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ss_Zahlungsweise"

     ss_Zahlungsweise :: ~ss_Zahlungsweise ( )
{



}


