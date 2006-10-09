/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Ausgangsdaten

\brief    


\date     $Date: 2006/07/07 13:49:40,51 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Ausgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Kind.hpp>
#include  <spc0_VorSchaden.hpp>
#include  <spc0_VorVersicherung.hpp>
#include  <spc0_Ausgangsdaten.hpp>


/******************************************************************************/
/**
\brief  Import - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0_Ausgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("versicherungs_beginn") = *source_ph->GPH("Versicherungsbeginn");
  *GPH("fuenfjahresvertrag")   = *source_ph->GPH("Fuenfjahresvertrag");
  *GPH("zahlungsweise")        = *source_ph->GPH("Zahlungsweise_ID");

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportKinder - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKinder"

logical pc0_Ausgangsdaten :: ImportKinder (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical              term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  pc0_Kind(GPH("kinder")).ImportAlle(source_ph,imp_globals);

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportSchaeden - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportSchaeden"

logical pc0_Ausgangsdaten :: ImportSchaeden (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical              term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  pc0_VorSchaden(GPH("schaeden")).ImportAlle(source_ph,imp_globals);

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportVV - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportVV"

logical pc0_Ausgangsdaten :: ImportVV (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_VorVersicherung   vor_versicherung(GPH("vor_versicherung"));
  logical               term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  vor_versicherung.Import(source_ph,imp_globals);

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportVV_KFZ - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportVV_KFZ"

logical pc0_Ausgangsdaten :: ImportVV_KFZ (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_VorVersicherung   vor_versicherung(GPH("vor_versicherung"));
  logical               term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  vor_versicherung.ImportKFZ(source_ph,imp_globals);

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Ausgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Ausgangsdaten"

     pc0_Ausgangsdaten :: pc0_Ausgangsdaten (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


