/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_WohngebaeudeVS

\brief    


\date     $Date: 2006/07/21 12:11:47,96 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_WohngebaeudeVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_WohngebaeudeVSAusgangsdaten.hpp>
#include  <spc_WohngebaeudeVS.hpp>
#include  <spc0_WohngebaeudeVS.hpp>


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

logical pc0_WohngebaeudeVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_WohngebaeudeVSAusgangsdaten  ausgangs_daten(GPH("ausgangs_daten"));
  logical                          term = NO;
BEGINSEQ
  if ( ImportBestandVV(source_ph,imp_globals) )     ERROR

  ausgangs_daten.ImportBestand(source_ph,imp_globals);

//  *GPH("risiko_plz")        = *source_ph->GPH("Risiko_PLZ");
  *GPH("risiko_strasse")    = *source_ph->GPH("Risiko_Strasse");
  *GPH("risiko_hausnummer") = *source_ph->GPH("Risiko_Hausnummer");
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

logical pc0_WohngebaeudeVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_WohngebaeudeVSAusgangsdaten  ausgangs_daten(GPH("ausgangs_daten"));
  logical                          term = NO;
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

logical pc0_WohngebaeudeVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  logical         term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR
                                                    
  *GPH("wohnobject_typ") = source_ph->GPH("WohnobjectTyp_ID")->GetInt();
  *GPH("bauartklasse")   = source_ph->GPH("Bauartklasse_ID")->GetInt();

  leistungenO.Import("ElementarSchaeden"      ,source_ph->GPH("ElementarSchaeden"),imp_globals);
  leistungenO.Import("Glasversicherung"       ,source_ph->GPH("Glasversicherung"),imp_globals);
  leistungenO.Import("Fussbodenheizung"       ,source_ph->GPH("Fussbodenheizung"),imp_globals);
  leistungenO.Import("Leitungswasser"         ,source_ph->GPH("Leitungswasser"),imp_globals);
  leistungenO.Import("Feuer"                  ,source_ph->GPH("Feuer"),imp_globals);
  leistungenO.Import("Sturm"                  ,source_ph->GPH("Sturm"),imp_globals);

  leistungenI.Import("Baujahr"                ,source_ph->GPH("Baujahr"),imp_globals);
  leistungenI.Import("Sanierung"              ,source_ph->GPH("Jahr_Sanierung"),imp_globals);
  leistungenI.Import("Neubausumme"            ,source_ph->GPH("Neubausumme"),imp_globals);
  leistungenI.Import("Wert1914"               ,source_ph->GPH("Wert1914"),imp_globals);
  leistungenI.Import("Wohnflaeche"            ,source_ph->GPH("Wohnflaeche"),imp_globals);
  leistungenI.Import("Glasflaeche"            ,source_ph->GPH("QmGlasflaeche"),imp_globals);
  leistungenI.Import("Wohneinheiten"          ,source_ph->GPH("Anzahl_Wohneinheiten"),imp_globals);
  leistungenI.Import("Garagen"                ,source_ph->GPH("Anzahl_Garagen"),imp_globals);
  leistungenI.Import("FeuerRohbauversicherung",source_ph->GPH("FeuerRohbauversicherung"),imp_globals);
  leistungenI.Import("Mietverlust"            ,source_ph->GPH("Mietverlust"),imp_globals);

  leistungenD.Import("Selbstbehalt"           ,source_ph->GPH("Selbstbehalt"),imp_globals);
  leistungenD.Import("Ueberspannungsschaeden" ,source_ph->GPH("Ueberspannungsschaeden"),imp_globals);
  leistungenD.Import("Nutzwaermeschaeden"     ,source_ph->GPH("Nutzwaermeschaeden"),imp_globals);
  leistungenD.Import("Aufraeumarbeiten"       ,source_ph->GPH("Aufraeumarbeiten"),imp_globals);
  leistungenD.Import("Wasseraustritt"         ,source_ph->GPH("Wasseraustritt"),imp_globals);
  leistungenD.Import("Einbruchschaeden"       ,source_ph->GPH("Einbruchschaeden"),imp_globals);
  leistungenD.Import("Sachverstaendigerkosten",source_ph->GPH("Sachverstaendigerkosten"),imp_globals);
  leistungenD.Import("Vandalismus"            ,source_ph->GPH("Vandalismus"),imp_globals);
  leistungenD.Import("NeuwertFactor"          ,source_ph->GPH("GNeuwertFactor"),imp_globals);

  pc_WohngebaeudeVS(this).CalculateVersicherungssumme();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_WohngebaeudeVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_WohngebaeudeVS"

     pc0_WohngebaeudeVS :: pc0_WohngebaeudeVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_WohngebaeudeVS"

     pc0_WohngebaeudeVS :: pc0_WohngebaeudeVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"WohngebaeudeVS",accopt)
{



}


