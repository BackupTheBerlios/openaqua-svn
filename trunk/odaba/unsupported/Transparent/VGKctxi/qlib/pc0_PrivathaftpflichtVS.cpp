/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_PrivathaftpflichtVS

\brief    


\date     $Date: 2006/07/20 17:19:13,62 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_PrivathaftpflichtVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Arbeit.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_PrivathaftpflichtVSAusgangsdaten.hpp>
#include  <spc0_PrivathaftpflichtVS.hpp>


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

logical pc0_PrivathaftpflichtVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( ImportBestandVV(source_ph,imp_globals) )     ERROR
  ImportArbeitgeber(source_ph->GPH("ArbeitgeberName"),imp_globals);

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

logical pc0_PrivathaftpflichtVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_PrivathaftpflichtVSAusgangsdaten  ausgangs_daten(GPH("ausgangs_daten"));
  logical                               term = NO;
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

logical pc0_PrivathaftpflichtVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  PropertyHandle *versicherungsnehmer = GPH("versicherungsnehmer");
  logical         term                 = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR
  *GPH("versicherungssumme") = *source_ph->GPH("SummeSach");
  *GPH("familientarif")      = source_ph->GPH("Familienversicherung")->GetInt();

  leistungenO.Import("Ausfalldeckung"       ,source_ph->GPH("Ausfalldeckung"),imp_globals);
  leistungenO.Import("DeliktunfaehigeKinder",source_ph->GPH("DeliktunfaehigeKinder"),imp_globals);
  leistungenO.Import("VolljaehrigeKinder"   ,source_ph->GPH("VolljaehrigeKinder"),imp_globals);
  leistungenO.Import("Surfbretter"          ,source_ph->GPH("Surfbretter"),imp_globals);
  leistungenO.Import("Diensthaftpflicht"    ,source_ph->GPH("Diensthaftpflicht"),imp_globals);
  leistungenO.Import("Sondertarif_Alter"    ,source_ph->GPH("Sondertarif_Alter"),imp_globals);

  leistungenI.Import("Hunde"                          ,source_ph->GPH("Hunde"),imp_globals);
  leistungenI.Import("DeckungssummeVermoegensschaeden",source_ph->GPH("SummeVermoegen"),imp_globals);
  leistungenI.Import("Schluesselschaeden"             ,source_ph->GPH("Schluesselschaeden"),imp_globals);
  leistungenI.Import("Selbstbeteiligung"              ,source_ph->GPH("Selbstbeteiligung"),imp_globals);
  leistungenI.Import("Auslandsdeckung_Europa"         ,source_ph->GPH("Auslandsdeckung_Europa"),imp_globals);
  leistungenI.Import("Auslandsdeckung_Welt"           ,source_ph->GPH("Auslandsdeckung_Welt"),imp_globals);
  leistungenI.Import("Bauherrenrisiko_bis"            ,source_ph->GPH("Bauherrenrisiko_bis"),imp_globals);
  leistungenI.Import("Modellfahrzeuge"                ,source_ph->GPH("Modellfahrzeuge"),imp_globals);
  leistungenI.Import("Allmaehlichkeitsschaeden"       ,source_ph->GPH("Allmaehlichkeitsschaeden"),imp_globals);
  leistungenI.Import("Mietsachschaeden"               ,source_ph->GPH("Mietsachschaeden"),imp_globals);
  leistungenI.Import("Unentgeltliche_Hilfeleistung"   ,source_ph->GPH("Unentgeltliche_Hilfeleistung"),imp_globals);
  leistungenI.Import("Oeltanks"                       ,source_ph->GPH("Oeltanks"),imp_globals);

  if ( versicherungsnehmer->Get(FIRST_INSTANCE) )
    pc0_Arbeit(versicherungsnehmer->GPH("job")).ImportOD(source_ph->GPH("OD"),imp_globals);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_PrivathaftpflichtVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_PrivathaftpflichtVS"

     pc0_PrivathaftpflichtVS :: pc0_PrivathaftpflichtVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_PrivathaftpflichtVS"

     pc0_PrivathaftpflichtVS :: pc0_PrivathaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"PrivathaftpflichtVS",accopt)
{



}


