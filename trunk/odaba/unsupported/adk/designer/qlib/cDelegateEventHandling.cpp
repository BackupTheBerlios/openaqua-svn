/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cDelegateEventHandling

\brief    


\date     $Date: 2006/03/12 19:37:12,53 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cDelegateEventHandling"

#include  <pdesign.h>
#include  <scDelegateEventHandling.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc -

\param  ctx_ctl_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cDelegateEventHandling :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cDelegateEventHandling();
  return(NO);

}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return term -

\param  fname -
\param  chk_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cDelegateEventHandling :: ExecuteFunction (char *fname, logical chk_opt )
{

  return (   strcmp(fname,"ForceClose") && strncmp(fname,"Do",2)
           ? GetHighContext()->ExecuteFunction(fname,chk_opt) 
           : AUTO );

}

/******************************************************************************/
/**
\brief  cDelegateEventHandling - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cDelegateEventHandling"

                        cDelegateEventHandling :: cDelegateEventHandling ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cDelegateEventHandling - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cDelegateEventHandling"

                        cDelegateEventHandling :: ~cDelegateEventHandling ( )
{



}


