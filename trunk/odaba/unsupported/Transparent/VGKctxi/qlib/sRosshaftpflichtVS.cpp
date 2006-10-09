/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sRosshaftpflichtVS

\brief    


\date     $Date: 2006/06/27 12:56:06,28 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sRosshaftpflichtVS"

#include  <pvgkctxi.h>
#include  <ssRosshaftpflichtVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sRosshaftpflichtVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sRosshaftpflichtVS();
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

logical sRosshaftpflichtVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("RHV") );

}

/******************************************************************************/
/**
\brief  sRosshaftpflichtVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sRosshaftpflichtVS"

     sRosshaftpflichtVS :: sRosshaftpflichtVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sRosshaftpflichtVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sRosshaftpflichtVS"

     sRosshaftpflichtVS :: ~sRosshaftpflichtVS ( )
{



}


