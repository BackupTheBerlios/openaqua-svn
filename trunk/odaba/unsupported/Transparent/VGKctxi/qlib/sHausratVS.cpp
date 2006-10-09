/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sHausratVS

\brief    


\date     $Date: 2006/06/26 15:55:50,62 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sHausratVS"

#include  <pvgkctxi.h>
#include  <sCTX_Structure.hpp>
#include  <ssHausratVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sHausratVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sHausratVS();
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

logical sHausratVS :: DBCreate ( )
{


  return ( sVS_base::DBCreate_intern("HR") );

}

/******************************************************************************/
/**
\brief  sHausratVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sHausratVS"

     sHausratVS :: sHausratVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sHausratVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sHausratVS"

     sHausratVS :: ~sHausratVS ( )
{



}


