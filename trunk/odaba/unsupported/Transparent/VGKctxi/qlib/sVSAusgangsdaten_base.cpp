/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sVSAusgangsdaten_base

\brief    


\date     $Date: 2006/07/05 23:29:02,01 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sVSAusgangsdaten_base"

#include  <pvgkctxi.h>
#include  <ssVSAusgangsdaten_base.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sVSAusgangsdaten_base :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sVSAusgangsdaten_base();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreated - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sVSAusgangsdaten_base :: DBCreated ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ

  SetupCollectionsByTyp();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetupCollectionsByTyp - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCollectionsByTyp"

logical sVSAusgangsdaten_base :: SetupCollectionsByTyp ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
  logical          term = NO;
  ph->GPH("leistungenD")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  ph->GPH("leistungenO")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  ph->GPH("leistungenI")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  return(term);
}

/******************************************************************************/
/**
\brief  sVSAusgangsdaten_base - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sVSAusgangsdaten_base"

     sVSAusgangsdaten_base :: sVSAusgangsdaten_base ( )
                     : CTX_Structure()
{



}


