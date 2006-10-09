/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sRechtsschutzVS

\brief    


\date     $Date: 2006/06/19 19:32:57,37 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sRechtsschutzVS"

#include  <pvgkctxi.h>
#include  <sCTX_Structure.hpp>
#include  <ssRechtsschutzVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sRechtsschutzVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sRechtsschutzVS();
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

logical sRechtsschutzVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("RS") );

}

/******************************************************************************/
/**
\brief  sRechtsschutzVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sRechtsschutzVS"

     sRechtsschutzVS :: sRechtsschutzVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sRechtsschutzVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sRechtsschutzVS"

     sRechtsschutzVS :: ~sRechtsschutzVS ( )
{



}


