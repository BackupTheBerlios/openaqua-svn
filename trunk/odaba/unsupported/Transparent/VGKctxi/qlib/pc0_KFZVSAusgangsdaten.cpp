/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_KFZVSAusgangsdaten

\brief    


\date     $Date: 2006/07/10 10:15:28,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_KFZVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_KFZ_Fahrer.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_KFZVSAusgangsdaten.hpp>


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

logical pc0_KFZVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("plz_zulassungsort")     = *source_ph->GPH("Postleitzahl_Zulassungsort");
  *GPH("kfz_erstzulassung")     = *source_ph->GPH("KFZ_Erstzulassung");
  *GPH("kfz_erstzulassung_vn")  = *source_ph->GPH("KFZ_Erstzulassung_VN");
  *GPH("kennzeichen.alpha")     = *source_ph->GPH("Kennzeichen_Alpha");
  *GPH("kennzeichen.nummer")    = *source_ph->GPH("Kennzeichen_Nummer");
  *GPH("hersteller_nummer")     = *source_ph->GPH("HSN");
  *GPH("typ_nummer")            = *source_ph->GPH("TSN");

  *GPH("deckung_haftpflicht")   = source_ph->GPH("Deckung_Haftpflicht_ID")->GetInt();
  *GPH("sb_teilkasko")          = source_ph->GPH("SB_Teilkasko_ID")->GetInt();
  *GPH("sb_vollkasko")          = source_ph->GPH("SB_Vollkasko_ID")->GetInt();
  *GPH("halter")                = source_ph->GPH("Halter_ID")->GetInt();
  *GPH("nutzung_fahrzeug")      = source_ph->GPH("Nutzung_Fahrzeug_ID")->GetInt();
  *GPH("land_benutzung")        = source_ph->GPH("Land_Benutzung")->GetInt();
  *GPH("abstellplatz")          = source_ph->GPH("Abstellplatz_ID")->GetInt();
  *GPH("kaskotyp")              = source_ph->GPH("KaskoTyp_ID")->GetInt();
  *GPH("nutzung_durch_vn")      = source_ph->GPH("NutzungVN_ID")->GetInt();
  *GPH("nutzung_durch_partner") = source_ph->GPH("NutzungPartner_ID")->GetInt();
  *GPH("finanzierung")          = source_ph->GPH("Finanzierung")->GetInt();
  *GPH("wohngebaeude_typ")      = source_ph->GPH("WohngebaeudeTyp_ID")->GetInt();

  imp_globals->ImportKFZ_Zulassungsbezirk(GPH("zulassungsbezirk"),source_ph->GPH("Zulassunsbezirk_ID"));  
  imp_globals->ImportBeruf(GPH("beruf"),source_ph->GPH("KFZ_Beruf_ID"));  
  imp_globals->ImportBerufsgruppe(GPH("berufsgruppe"),source_ph->GPH("KFZ_Berufsgruppe_ID"));  
  imp_globals->ImportBranche(GPH("branche"),source_ph->GPH("KFZ_Branche_ID"));  
  imp_globals->ImportVersicherer(GPH("wohneigentum_versicherer"),source_ph->GPH("Wohneigentum_versichert_bei_ID"));  

  leistungenO.Import("Wegfahrsperre"               ,source_ph->GPH("Wegfahrsperre"),imp_globals);
  leistungenO.Import("Mitarbeiterkonditionen"      ,source_ph->GPH("Mitarbeiterkonditionen"),imp_globals);
  leistungenO.Import("Airbag"                      ,source_ph->GPH("Airbag"),imp_globals);
  leistungenO.Import("Alarmanlage"                 ,source_ph->GPH("Alarmanlage"),imp_globals);
  leistungenO.Import("Bahncard"                    ,source_ph->GPH("Bahncard"),imp_globals);
  leistungenO.Import("Jahreskarte_oeffentliche_Vkm",source_ph->GPH("Jahreskarte_oeffentliche_VKM"),imp_globals);
  leistungenO.Import("Dienstreisen"                ,source_ph->GPH("Dienstreisen"),imp_globals);
  leistungenO.Import("Fahrten_zur_Arbeit"          ,source_ph->GPH("Fahrten_zur_Arbeit"),imp_globals);
  leistungenO.Import("Schutzbrief"                 ,source_ph->GPH("Schutzbrief"),imp_globals);
  leistungenO.Import("Erstbesitzer"                ,source_ph->GPH("Erstbesitzer"),imp_globals);
  leistungenO.Import("IstMitgliedBUND"             ,source_ph->GPH("IsMitgliedBUND"),imp_globals);
  leistungenO.Import("IstVersicherungswechsler"    ,source_ph->GPH("IsVersicherungswechsler"),imp_globals);
  leistungenO.Import("IstZweitfahrzeug"            ,source_ph->GPH("IsZweitfahrzeug"),imp_globals);
  leistungenO.Import("HatVKZentralregisterEintrag" ,source_ph->GPH("hatVKZREintrag"),imp_globals);

  leistungenI.Import("Zubehoerwert"                ,source_ph->GPH("Zubehoerwert"),imp_globals);
  leistungenI.Import("Neuwert"                     ,source_ph->GPH("Fahrzeugneuwert"),imp_globals);
  leistungenI.Import("Zeitwert"                    ,source_ph->GPH("Fahrzeugzeitwert"),imp_globals);
  leistungenI.Import("KFZ_im_Haushalt"             ,source_ph->GPH("KFZ_im_HH"),imp_globals);
  leistungenI.Import("Fahrleistung"                ,source_ph->GPH("Fahrleistung_in_km"),imp_globals);

  pc0_KFZ_Fahrer(GPH("fahrer")).ImportAlle(source_ph->GPH("AlleFahrer"),imp_globals);
  pc0_KFZ_Fahrer(GPH("kinder")).ImportAlle(source_ph->GPH("Kinder"),imp_globals);

  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_KFZVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_KFZVSAusgangsdaten"

     pc0_KFZVSAusgangsdaten :: pc0_KFZVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


