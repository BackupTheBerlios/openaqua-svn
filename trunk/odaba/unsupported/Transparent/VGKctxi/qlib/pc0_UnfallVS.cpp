/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_UnfallVS

\brief    


\date     $Date: 2006/07/21 11:53:21,73 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_UnfallVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_UnfallVSAusgangsdaten.hpp>
#include  <spc0_UnfallVersicherter.hpp>
#include  <spc_UnfallVS.hpp>
#include  <spc0_UnfallVS.hpp>


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

logical pc0_UnfallVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
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

logical pc0_UnfallVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_UnfallVSAusgangsdaten   ausgangs_daten(GPH("ausgangs_daten"));
  logical                     term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportDaten(source_ph,imp_globals) ) 
                                                    ERROR
  ausgangs_daten.Import(source_ph,imp_globals);

//  ImportKinderVN(source_ph->GPH("Kinder"),imp_globals);
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

logical pc0_UnfallVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_UnfallVersicherter uv_versicherungsnehmer(GPH("uv_versicherungsnehmer"));
  pc0_UnfallVersicherter uv_partner(GPH("uv_partner"));
  pc0_UnfallVersicherter uv_kinder(GPH("uv_kinder"));
  pc0_Leistung           leistungenO(GPH("leistungenO"));
  pc0_Leistung           leistungenI(GPH("leistungenI"));
  pc0_Leistung           leistungenD(GPH("leistungenD"));
  pc0_Leistung           gliedertaxe(GPH("gliedertaxe"));
  logical                term = NO;

BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR

  uv_versicherungsnehmer.ImportDaten(source_ph,NO,NO,imp_globals);
  uv_partner.ImportDaten(source_ph,YES,NO,imp_globals);
  uv_kinder.ImportDaten(source_ph,NO,YES,imp_globals);

  gliedertaxe.ImportGliedertaxen(source_ph,imp_globals);

  leistungenO.Import("GeringfuegigeUnfallfolgen"        ,source_ph->GPH("Geringfuegige_unfallfolgen"),imp_globals);
  leistungenO.Import("Impfschaeden"                     ,source_ph->GPH("Impfschaeden"),imp_globals);
  leistungenO.Import("Infektionskrankheiten"            ,source_ph->GPH("Infektionskrankheiten"),imp_globals);
  leistungenO.Import("Insektenstiche"                   ,source_ph->GPH("Insenktenstiche"),imp_globals);
  leistungenO.Import("MitversicherungNeugeborene"       ,source_ph->GPH("Mitversicherung_neugeborene"),imp_globals);
  leistungenO.Import("Versehensklausel"                 ,source_ph->GPH("Versehensklausel"),imp_globals);
  leistungenO.Import("Vorschusszahlung"                 ,source_ph->GPH("Vorschusszahlung"),imp_globals);
  leistungenO.Import("Arbeitslosigkeit"                 ,source_ph->GPH("Arbeitslosigkeit"),imp_globals);
  leistungenO.Import("Beitragsfreistellung"             ,source_ph->GPH("Beitragsfreistellung"),imp_globals);
  leistungenO.Import("MeldefristTod"                    ,source_ph->GPH("Meldefrist_tod"),imp_globals);
  leistungenO.Import("Knochenbrueche"                   ,source_ph->GPH("Knochenbrueche"),imp_globals);
  leistungenO.Import("Zahnersatz"                       ,source_ph->GPH("Zahnersatz"),imp_globals);
  leistungenO.Import("Notfalleinweisung"                ,source_ph->GPH("Notfalleinweisung"),imp_globals);
  leistungenO.Import("Rettungsmassnahmen"               ,source_ph->GPH("Rettungsmassnahmen"),imp_globals);
  leistungenO.Import("Vergiftung"                       ,source_ph->GPH("Vergiftung"),imp_globals);
  leistungenO.Import("Tauchschaeden"                    ,source_ph->GPH("Tauchschaeden"),imp_globals);
  leistungenO.Import("Infektion_vor_Vertragsbeginn"     ,source_ph->GPH("Infektion_vor_vertragsbeginn"),imp_globals);
  leistungenO.Import("KeineMindestinvaliditaetInfektion",source_ph->GPH("Keine_mindestinvaliditaet_infektion"),imp_globals);
  leistungenO.Import("PassivesKrebsrisiko"              ,source_ph->GPH("Passives_krebsrisiko"),imp_globals);
  leistungenO.Import("Strahlenschaeden"                 ,source_ph->GPH("Strahlenschaeden"),imp_globals);
  leistungenO.Import("Nahrungsmittelvergiftung"         ,source_ph->GPH("Nahrungsmittelvergiftung"),imp_globals);
  leistungenO.Import("VergiftungKinder"                 ,source_ph->GPH("Vergiftung_kinder"),imp_globals);
  leistungenO.Import("UnerlaubtesFahrenPKW"             ,source_ph->GPH("Unerlaubtes_fahren_pkw"),imp_globals);

  leistungenI.Import("KrankentageMaximal"               ,source_ph->GPH("Ktg_max_anzahl_tage"),imp_globals);
  leistungenI.Import("Transportkosten"                  ,source_ph->GPH("Transportkosten"),imp_globals);
  leistungenI.Import("Kurkostenbeihilfe"                ,source_ph->GPH("Kurkostenbeihilfe"),imp_globals);
  leistungenI.Import("BehinderungMehraufwendung"        ,source_ph->GPH("Behinderung_mehraufwendung"),imp_globals);
  leistungenI.Import("RoomingIn"                        ,source_ph->GPH("Rooming_in"),imp_globals);
  leistungenI.Import("VollwaisenRente"                  ,source_ph->GPH("Vollwaisen_rente"),imp_globals);
  leistungenI.Import("KinderVersichert"                 ,source_ph->GPH("AnzahlKinderversichert"),imp_globals);
  
  leistungenD.Import("Genesungsgeld"                    ,source_ph->GPH("Genesungsgeld"),imp_globals);
  leistungenD.Import("Krankheiten_und_Gebrechen"        ,source_ph->GPH("Krankheiten_und_gebrechen"),imp_globals);
  leistungenD.Import("AlkoholKFZ"                       ,source_ph->GPH("Alkohol_kfz"),imp_globals);

  pc_UnfallVS(this).CalculateVersicherungssumme();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_UnfallVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_UnfallVS"

     pc0_UnfallVS :: pc0_UnfallVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_UnfallVS"

     pc0_UnfallVS :: pc0_UnfallVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"UnfallVS",accopt)
{



}


