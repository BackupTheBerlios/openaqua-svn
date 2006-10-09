/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_KFZVS

\brief    


\date     $Date: 2006/07/09 11:47:24,03 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_KFZVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Fuehrerschein.hpp>
#include  <spc0_KFZVSAusgangsdaten.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_KFZVS.hpp>


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

logical pc0_KFZVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Ausgangsdaten     ausgangs_daten(GPH("ausgangs_daten"));
  logical               term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportBestand(source_ph,imp_globals) )
                                                    ERROR

  ausgangs_daten.ImportVV_KFZ(source_ph,imp_globals);

  *GPH("km_stand")          = *source_ph->GPH("KmStand");
  *GPH("fahrzeug_ident_nr") = *source_ph->GPH("FahrzeugIdentNr");
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

logical pc0_KFZVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_KFZVSAusgangsdaten   ausgangs_daten(GPH("ausgangs_daten"));
  logical                  term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportDaten(source_ph,imp_globals) ) 
                                                    ERROR
  ausgangs_daten.Import(source_ph,imp_globals);

  ImportFuehrerscheinVN(source_ph,imp_globals);
  
/* --> ausgangs_daten.vor_versicherung
  *GPH("existiert")  = *source_ph->GPH("hatVorversicherung");
  *GPH("gekuendigt") = *source_ph->GPH("Vorvertrag_kuendigung");
  imp_globals->ImportVersicherer(GPH("versicherer"),source_ph->GPH("Vorversicherung_ID"));
*/
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

logical pc0_KFZVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  logical         term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR
  *GPH("plz_zulassungsort")     = *source_ph->GPH("Postleitzahl_Zulassungsort");
  *GPH("hersteller_nummer")     = *source_ph->GPH("HSN");
  *GPH("typ_nummer")            = *source_ph->GPH("TSN");

  *GPH("nutzung_fahrzeug")      = source_ph->GPH("Nutzung_Fahrzeug_ID")->GetInt();
  *GPH("abstellplatz")          = source_ph->GPH("Abstellplatz_ID")->GetInt();
  *GPH("schutz_typ")            = source_ph->GPH("TypSchutz_ID")->GetInt();
  *GPH("deckung_haftpflicht")   = source_ph->GPH("Deckung_Haftpflicht_ID")->GetInt();

  leistungenO.Import("Wegfahrsperre"               ,source_ph->GPH("Wegfahrsperre"),imp_globals);
  leistungenO.Import("Airbag"                      ,source_ph->GPH("Airbag"),imp_globals);
  leistungenO.Import("Alarmanlage"                 ,source_ph->GPH("Alarmanlage"),imp_globals);
  leistungenO.Import("Bahncard"                    ,source_ph->GPH("Bahncard"),imp_globals);
  leistungenO.Import("Jahreskarte_oeffentliche_Vkm",source_ph->GPH("Jahreskarte_oeffentliche_VKM"),imp_globals);
  leistungenO.Import("Dienstreisen"                ,source_ph->GPH("Dienstreisen"),imp_globals);
  leistungenO.Import("Fahrten_zur_Arbeit"          ,source_ph->GPH("Fahrten_zur_Arbeit"),imp_globals);
  leistungenO.Import("Schutzbrief"                 ,source_ph->GPH("Schutzbrief"),imp_globals);
  leistungenO.Import("Marderbiss"                  ,source_ph->GPH("Marderbiss"),imp_globals);
  leistungenO.Import("Rabattretter"                ,source_ph->GPH("Rabattretter"),imp_globals);
  leistungenO.Import("Kurzschluss"                 ,source_ph->GPH("Kurzschluss"),imp_globals);
  leistungenO.Import("Mehrwertgrenze"              ,source_ph->GPH("Mehrwertgrenze"),imp_globals);
  leistungenO.Import("NeuFuerAlt"                  ,source_ph->GPH("NeuFuerAlt"),imp_globals);
  leistungenO.Import("SB_Verzicht_Glas"            ,source_ph->GPH("SB_Verzicht_Glas"),imp_globals);
  leistungenO.Import("Neuwertentschaedigung"       ,source_ph->GPH("Neuwertentschaedigung"),imp_globals);
  leistungenO.Import("Schluesselverlust"           ,source_ph->GPH("Schluesselverlust"),imp_globals);
  leistungenO.Import("Notruf_24h"                  ,source_ph->GPH("Notruf_24h"),imp_globals);

  leistungenI.Import("Zubehoerwert"                ,source_ph->GPH("Zubehoerwert"),imp_globals);
  leistungenI.Import("Neuwert"                     ,source_ph->GPH("Fahrzeugneuwert"),imp_globals);
  leistungenI.Import("Zeitwert"                    ,source_ph->GPH("Fahrzeugzeitwert"),imp_globals);
  leistungenI.Import("KFZ_im_Haushalt"             ,source_ph->GPH("KFZ_im_HH"),imp_globals);
  leistungenI.Import("Fahrleistung"                ,source_ph->GPH("Fahrleistung_in_km"),imp_globals);
  leistungenI.Import("Fahrzeugalter"               ,source_ph->GPH("Fahrzeugalter"),imp_globals);
  leistungenI.Import("Fahrzeugalter_bei_Erwerb"    ,source_ph->GPH("Fahrzeugalter_bei_Erwerb"),imp_globals);
  leistungenI.Import("Juengster_Fahrer_maennlich"  ,source_ph->GPH("Alter_juengster_FahrerM"),imp_globals);
  leistungenI.Import("Juengster_Fahrer_weiblich"   ,source_ph->GPH("Alter_juengster_FahrerW"),imp_globals);
  leistungenI.Import("Juengster_Fahrer"            ,source_ph->GPH("Alter_juengster_Fahrer"),imp_globals);

  leistungenD.Import("SelbstbeteiligungTeilkasko"  ,source_ph->GPH("SB_Teilkasko"),imp_globals);
  leistungenD.Import("SelbstbeteiligungVollkasko"  ,source_ph->GPH("SB_Vollkasko"),imp_globals);
  leistungenD.Import("SFHaftpflicht"               ,source_ph->GPH("SFHaftpflicht"),imp_globals);
  leistungenD.Import("SFVollkasko"                 ,source_ph->GPH("SFVollkasko"),imp_globals);
  leistungenD.Import("PreisHaftpflicht"            ,source_ph->GPH("KHPreis"),imp_globals);
  leistungenD.Import("PreisTeilkasko"              ,source_ph->GPH("TKPreis"),imp_globals);
  leistungenD.Import("PreisVollkasko"              ,source_ph->GPH("VKPreis"),imp_globals);

  pc0_Fuehrerschein(GPH("fuehrerschein")).Import(source_ph,imp_globals);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_KFZVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_KFZVS"

     pc0_KFZVS :: pc0_KFZVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_KFZVS"

     pc0_KFZVS :: pc0_KFZVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"KFZVS",accopt)
{



}


