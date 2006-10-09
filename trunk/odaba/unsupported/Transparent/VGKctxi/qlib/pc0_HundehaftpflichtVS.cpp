/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_HundehaftpflichtVS

\brief    


\date     $Date: 2006/07/21 16:40:05,26 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_HundehaftpflichtVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_HundehaftpflichtVSAusgangsdaten.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc_HundehaftpflichtVS.hpp>
#include  <spc0_HundehaftpflichtVS.hpp>


/******************************************************************************/
/**
\brief  ImportBestand - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBestand"

logical pc0_HundehaftpflichtVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( ImportBestandVV(source_ph,imp_globals) )     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportDaten - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportDaten"

logical pc0_HundehaftpflichtVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_HundehaftpflichtVSAusgangsdaten  ausgangs_daten(GPH("ausgangs_daten"));
  logical                              term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportDaten(source_ph,imp_globals) ) 
                                                    ERROR
  ausgangs_daten.Import(source_ph,imp_globals);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportResult - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportResult"

logical pc0_HundehaftpflichtVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  logical         term  = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR

  *GPH("versicherungssumme") = *source_ph->GPH("Versicherungssumme");

  leistungenO.Import("Hundeschlittenrennen"    ,source_ph->GPH("Hundeschlittenrennen"),imp_globals);
  leistungenO.Import("Welpen_mitversichert"    ,source_ph->GPH("Welpen_mitversichert"),imp_globals);
  leistungenO.Import("Einsatz_Blindenhund"     ,source_ph->GPH("Einsatz_Blindenhund"),imp_globals);
  leistungenO.Import("Einsatz_Jagdhund"        ,source_ph->GPH("Einsatz_Jagdhund"),imp_globals);
  leistungenO.Import("Hueten_fremde_Personen"  ,source_ph->GPH("Hueten_fremde_Personen"),imp_globals);
  leistungenO.Import("Ungewollter_Deckakt"     ,source_ph->GPH("Ungewollter_Deckakt"),imp_globals);
  leistungenO.Import("Eigenschaeden"           ,source_ph->GPH("Eigenschaeden"),imp_globals);
  leistungenO.Import("Krankenversicherung"     ,source_ph->GPH("Krankenversicherung"),imp_globals);
  leistungenO.Import("Rechtsschutzversicherung",source_ph->GPH("Rechtsschutzversicherung"),imp_globals);
  leistungenO.Import("Unfallversicherung"      ,source_ph->GPH("Unfallversicherung"),imp_globals);

  leistungenI.Import("DeckungssummeVermoegensschaeden",source_ph->GPH("Vermoegensschaden_Hunde"),imp_globals);
  leistungenI.Import("Auslandsaufenthalt"             ,source_ph->GPH("Auslandsaufenthalt_Hunde"),imp_globals);
  leistungenI.Import("Mietsachschaeden"               ,source_ph->GPH("Mietsachschaeden"),imp_globals);
  leistungenI.Import("Selbstbeteiligung"              ,source_ph->GPH("Selbstbehalt"),imp_globals);
  
  pc_HundehaftpflichtVS(this).SetupAnzahlHunde();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_HundehaftpflichtVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_HundehaftpflichtVS"

     pc0_HundehaftpflichtVS :: pc0_HundehaftpflichtVS (PropertyHandle *prophdl )
                     : pc0Base_VS(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_HundehaftpflichtVS"

     pc0_HundehaftpflichtVS :: pc0_HundehaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"HundehaftpflichtVS",accopt)
{



}


