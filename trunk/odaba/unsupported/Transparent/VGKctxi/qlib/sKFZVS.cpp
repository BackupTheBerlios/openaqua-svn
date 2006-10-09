/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sKFZVS

\brief    


\date     $Date: 2006/06/19 19:31:52,09 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sKFZVS"

#include  <pvgkctxi.h>
#include  <ssKFZVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sKFZVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sKFZVS();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreate - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical sKFZVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("KFZ") );

}

/******************************************************************************/
/**
\brief  sKFZVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sKFZVS"

     sKFZVS :: sKFZVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sKFZVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sKFZVS"

     sKFZVS :: ~sKFZVS ( )
{



}


