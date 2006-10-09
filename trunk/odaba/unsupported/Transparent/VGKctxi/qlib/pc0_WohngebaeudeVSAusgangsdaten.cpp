/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_WohngebaeudeVSAusgangsdaten

\brief    


\date     $Date: 2006/07/07 15:14:12,68 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_WohngebaeudeVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_WohngebaeudeVSAusgangsdaten.hpp>


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

logical pc0_WohngebaeudeVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("risiko_plz")     = *source_ph->GPH("PLZ_Risiko");

  *GPH("selbstbehalt")   = source_ph->GPH("Selbstbehalt")->GetInt();
  *GPH("wohnobject_typ") = source_ph->GPH("WohnobjectTyp_ID")->GetInt();
  *GPH("bauartklasse")   = source_ph->GPH("Bauartklasse_ID")->GetInt();

  leistungenO.Import("ElementarSchaeden",source_ph->GPH("ElementarSchaeden"),imp_globals);
  leistungenO.Import("Glasversicherung" ,source_ph->GPH("Glasversicherung"),imp_globals);
  leistungenO.Import("Fussbodenheizung" ,source_ph->GPH("Fussbodenheizung"),imp_globals);
  leistungenO.Import("Leitungswasser"   ,source_ph->GPH("Leitungswasser"),imp_globals);
  leistungenO.Import("Feuer"            ,source_ph->GPH("Feuer"),imp_globals);
  leistungenO.Import("Sturm"            ,source_ph->GPH("Sturm"),imp_globals);

  leistungenI.Import("Baujahr"          ,source_ph->GPH("Baujahr"),imp_globals);
  leistungenI.Import("Sanierung"        ,source_ph->GPH("Jahr_Sanierung"),imp_globals);
  leistungenI.Import("Neubausumme"      ,source_ph->GPH("Neubausumme"),imp_globals);
  leistungenI.Import("Wert1914"         ,source_ph->GPH("Wert1914"),imp_globals);
  leistungenI.Import("Wohnflaeche"      ,source_ph->GPH("Wohnflaeche"),imp_globals);
  leistungenI.Import("Glasflaeche"      ,source_ph->GPH("QmGlasflaeche"),imp_globals);
  leistungenI.Import("Wohneinheiten"    ,source_ph->GPH("Anzahl_Wohneinheiten"),imp_globals);
  leistungenI.Import("Garagen"          ,source_ph->GPH("Anzahl_Garagen"),imp_globals);

  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

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

logical pc0_WohngebaeudeVSAusgangsdaten :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("risiko_strasse")    = *source_ph->GPH("Risiko_Strasse");
  *GPH("risiko_hausnummer") = *source_ph->GPH("Risiko_Hausnummer");

  leistungenO.Import("AbweichendeRisikoAnschrift",source_ph->GPH("AbweichendeRisikoanschrift"),imp_globals);
  leistungenO.Import("Klimaanlage"               ,source_ph->GPH("Klimaanlage"),imp_globals);
  leistungenO.Import("GewerbebetriebeImGebaeude" ,source_ph->GPH("GewerbebetriebeImGebaeude"),imp_globals);
  leistungenO.Import("FeuerrohbauVersicherung"   ,source_ph->GPH("FeuerrohbauVers"),imp_globals);

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_WohngebaeudeVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_WohngebaeudeVSAusgangsdaten"

     pc0_WohngebaeudeVSAusgangsdaten :: pc0_WohngebaeudeVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


