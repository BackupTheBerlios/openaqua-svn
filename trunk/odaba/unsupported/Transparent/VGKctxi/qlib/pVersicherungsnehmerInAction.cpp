/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pVersicherungsnehmerInAction

\brief    


\date     $Date: 2006/07/07 12:33:36,98 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pVersicherungsnehmerInAction"

#include  <pvgkctxi.h>
#include  <spVersicherungsnehmerInAction.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pVersicherungsnehmerInAction :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pVersicherungsnehmerInAction();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBInserted - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInserted"

logical pVersicherungsnehmerInAction :: DBInserted ( )
{
  PropertyHandle    *ph = GetPropertyHandle();

BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ
  
  PropertyHandle   kunden(ph->GetDBHandle(),"Kunde",PI_Write);
  kunden.Provide(ph->ExtractKey());
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  pVersicherungsnehmerInAction - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pVersicherungsnehmerInAction"

     pVersicherungsnehmerInAction :: pVersicherungsnehmerInAction ( )
                     : CTX_Property()
{



}

/******************************************************************************/
/**
\brief  ~pVersicherungsnehmerInAction - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pVersicherungsnehmerInAction"

     pVersicherungsnehmerInAction :: ~pVersicherungsnehmerInAction ( )
{



}


