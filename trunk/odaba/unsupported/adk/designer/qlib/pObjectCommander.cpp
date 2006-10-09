/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pObjectCommander



\date     $Date: 2006/05/18 19:07:39,98 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pObjectCommander"

#include  <pdesign.h>
#include  <spObjectCommander.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_prj_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pObjectCommander :: Create (CTX_Project **ctx_prj_ptrp )
{

  *ctx_prj_ptrp = new pObjectCommander();
  return(NO);

}

/******************************************************************************/
/**
\brief  pObjectCommander


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pObjectCommander"

     pObjectCommander :: pObjectCommander ( )
                     : pODE()
{



}

/******************************************************************************/
/**
\brief  ~pObjectCommander


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pObjectCommander"

     pObjectCommander :: ~pObjectCommander ( )
{
}


