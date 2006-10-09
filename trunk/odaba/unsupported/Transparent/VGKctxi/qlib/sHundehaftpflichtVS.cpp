/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sHundehaftpflichtVS

\brief    


\date     $Date: 2006/06/27 12:54:21,93 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sHundehaftpflichtVS"

#include  <pvgkctxi.h>
#include  <ssHundehaftpflichtVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sHundehaftpflichtVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sHundehaftpflichtVS();
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

logical sHundehaftpflichtVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("HHV") );

}

/******************************************************************************/
/**
\brief  sHundehaftpflichtVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sHundehaftpflichtVS"

     sHundehaftpflichtVS :: sHundehaftpflichtVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sHundehaftpflichtVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sHundehaftpflichtVS"

     sHundehaftpflichtVS :: ~sHundehaftpflichtVS ( )
{



}


