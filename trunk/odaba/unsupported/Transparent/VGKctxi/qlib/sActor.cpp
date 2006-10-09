/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sActor

\brief    


\date     $Date: 2006/06/20 11:03:28,26 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sActor"

#include  <pvgkctxi.h>
#include  <ssActor.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sActor :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sActor();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBInitialize - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInitialize"

logical sActor :: DBInitialize ( )
{

  InitKey("__AUTOIDENT","Actor");
  return(NO);
}

/******************************************************************************/
/**
\brief  sActor - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sActor"

     sActor :: sActor ( )
                     : sBase_SharedData()
{



}

/******************************************************************************/
/**
\brief  ~sActor - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sActor"

     sActor :: ~sActor ( )
{



}


