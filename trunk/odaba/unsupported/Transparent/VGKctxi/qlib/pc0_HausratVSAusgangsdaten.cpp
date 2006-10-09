/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_HausratVSAusgangsdaten

\brief    


\date     $Date: 2006/07/06 13:00:05,64 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_HausratVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Arbeit.hpp>
#include  <spc0_Leistung.hpp>
#include  <ivgkxi.h>
#include  <spc0_HausratVSAusgangsdaten.hpp>


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

logical pc0_HausratVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  pc0_Arbeit      job(GPH("job"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("wohnobject_plz")        = *source_ph->GPH("Plz");
  *GPH("wohnobject_strasse")    = *source_ph->GPH("WohnungStrasse");
  *GPH("wohnobject_hausnummer") = *source_ph->GPH("WohnungStrasseHnr");

  *GPH("selbstbehalt")          = source_ph->GPH("Selbstbehalt_ID")->GetInt();
  *GPH("wohnobject_typ")        = source_ph->GPH("Wohnobjecttype_ID")->GetInt();
  *GPH("fahrraeder")            = CalculateEnumValue(source_ph->GPH("Fahrraeder_ID"),100);
  *GPH("ueberspannung")         = CalculateEnumValue(source_ph->GPH("Ueberspannung_ID"),100);

  leistungenO.Import("Unterversicherungsverzicht",source_ph->GPH("Unterversicherungsverzicht"),imp_globals);
  leistungenO.Import("ElementarSchaeden"         ,source_ph->GPH("ElementarSchaeden"),imp_globals);
  leistungenO.Import("Glaskeramik"               ,source_ph->GPH("Glaskeramik"),imp_globals);
  leistungenO.Import("Ueberspannung"             ,source_ph->GPH("UeberspannungInclude"),imp_globals);
  leistungenO.Import("Fahrraeder"                ,source_ph->GPH("FahrraederInclude"),imp_globals);
  leistungenO.Import("Glasflaeche"               ,source_ph->GPH("GlasflaecheInclude"),imp_globals);
  leistungenO.Import("Spezialrisiken"            ,source_ph->GPH("Spezialrisiken"),imp_globals);

  leistungenI.Import("Wohnflaeche"               ,source_ph->GPH("QmWohnflaeche"),imp_globals);
  leistungenI.Import("Glasflaeche"               ,source_ph->GPH("QmGlasflaeche"),imp_globals);

  leistungenD.Import("Deckungssumme"             ,source_ph->GPH("Deckungssumme"),imp_globals);

  job.ImportOD(source_ph->GPH("OD"),imp_globals);

  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_HausratVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_HausratVSAusgangsdaten"

     pc0_HausratVSAusgangsdaten :: pc0_HausratVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


