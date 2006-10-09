/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_UnfallVSAusgangsdaten

\brief    


\date     $Date: 2006/07/07 12:24:23,45 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_UnfallVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_UnfallVersicherter.hpp>
#include  <spc0_UnfallVSAusgangsdaten.hpp>


/******************************************************************************/
/**
\brief  Import - 



\return term - 

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0_UnfallVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_UnfallVersicherter uv_versicherungsnehmer(GPH("uv_versicherungsnehmer"));
  pc0_UnfallVersicherter uv_partner(GPH("uv_partner"));
  pc0_UnfallVersicherter uv_kinder(GPH("uv_kinder"));
  logical                term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("versicherte_personen") = source_ph->GPH("Versicherte_Personen")->GetInt();

  uv_versicherungsnehmer.ImportDaten(source_ph,NO,NO,imp_globals);
  uv_partner.ImportDaten(source_ph,YES,NO,imp_globals);
  uv_kinder.ImportDaten(source_ph,NO,YES,imp_globals);

  ImportKinder(source_ph->GPH("Kinder"),imp_globals);
  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_UnfallVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_UnfallVSAusgangsdaten"

     pc0_UnfallVSAusgangsdaten :: pc0_UnfallVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


