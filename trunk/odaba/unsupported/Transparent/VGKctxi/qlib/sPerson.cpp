/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sPerson

\brief    


\date     $Date: 2006/06/20 11:04:17,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sPerson"

#include  <pvgkctxi.h>
#include  <ssPerson.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sPerson :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sPerson();
  return(NO);


}

/******************************************************************************/
/**
\brief  sPerson - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sPerson"

     sPerson :: sPerson ( )
                     : sBase_SharedData()
{



}

/******************************************************************************/
/**
\brief  ~sPerson - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sPerson"

     sPerson :: ~sPerson ( )
{



}


