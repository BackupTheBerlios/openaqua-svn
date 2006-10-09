/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sPrivathaftpflichtVS

\brief    


\date     $Date: 2006/06/19 19:32:28,06 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sPrivathaftpflichtVS"

#include  <pvgkctxi.h>
#include  <ssPrivathaftpflichtVS.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sPrivathaftpflichtVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sPrivathaftpflichtVS();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreate - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical sPrivathaftpflichtVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("PHV") );

}

/******************************************************************************/
/**
\brief  sPrivathaftpflichtVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sPrivathaftpflichtVS"

     sPrivathaftpflichtVS :: sPrivathaftpflichtVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sPrivathaftpflichtVS - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sPrivathaftpflichtVS"

     sPrivathaftpflichtVS :: ~sPrivathaftpflichtVS ( )
{



}


