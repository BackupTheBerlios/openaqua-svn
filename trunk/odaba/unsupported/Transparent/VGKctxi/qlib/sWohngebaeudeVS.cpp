/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sWohngebaeudeVS

\brief    


\date     $Date: 2006/06/19 19:34:11,54 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sWohngebaeudeVS"

#include  <pvgkctxi.h>
#include  <sCTX_Structure.hpp>
#include  <ssWohngebaeudeVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sWohngebaeudeVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sWohngebaeudeVS();
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

logical sWohngebaeudeVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("WGV") );

}

/******************************************************************************/
/**
\brief  sWohngebaeudeVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sWohngebaeudeVS"

     sWohngebaeudeVS :: sWohngebaeudeVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sWohngebaeudeVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sWohngebaeudeVS"

     sWohngebaeudeVS :: ~sWohngebaeudeVS ( )
{



}


