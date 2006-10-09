/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_HausratVS

\brief    


\date     $Date: 2006/07/20 16:21:20,60 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_HausratVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Arbeit.hpp>
#include  <spc0_HausratVSAusgangsdaten.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_HausratVS.hpp>


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

logical pc0_HausratVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical              term = NO;
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

logical pc0_HausratVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_HausratVSAusgangsdaten   ausgangs_daten(GPH("ausgangs_daten"));
  logical                      term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportDaten(source_ph,imp_globals) ) 
                                                    ERROR
  ausgangs_daten.Import(source_ph,imp_globals);

  *GPH("wohnobject_strasse")    = *source_ph->GPH("WohnungStrasse");
  *GPH("wohnobject_hausnummer") = *source_ph->GPH("WohnungStrasseHnr");
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

logical pc0_HausratVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  PropertyHandle *versicherungsnehmer = GPH("versicherungsnehmer");
  logical         term                = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR
                                                    
  *GPH("versicherungssumme") = *source_ph->GPH("Deckungssumme");
  *GPH("wohnobject_plz")     = *source_ph->GPH("Plz");
  *GPH("wohnobject_typ")     = source_ph->GPH("WohnobjectTyp_ID")->GetInt();

  leistungenO.Import("Unterversicherungsverzicht",source_ph->GPH("Unterversicherungsverzicht"),imp_globals);
  leistungenO.Import("ElementarSchaeden"         ,source_ph->GPH("ElementarSchaeden"),imp_globals);
  leistungenO.Import("Glaskeramik"               ,source_ph->GPH("Glaskeramik"),imp_globals);
  leistungenO.Import("Spezialrisiken"            ,source_ph->GPH("Spezialrisiken"),imp_globals);

  leistungenI.Import("Wohnflaeche"               ,source_ph->GPH("QmWohnflaeche"),imp_globals);
  leistungenI.Import("Glasflaeche"               ,source_ph->GPH("QmGlasflaeche"),imp_globals);
  leistungenI.Import("Wertsachen"                ,source_ph->GPH("Wertsachen"),imp_globals);
  leistungenI.Import("Wasseraustritt"            ,source_ph->GPH("Wasseraustritt"),imp_globals);
  leistungenI.Import("Implosion"                 ,source_ph->GPH("Implosion"),imp_globals);
  leistungenI.Import("Nutzwaermeschaeden"        ,source_ph->GPH("Nutzwaermeschaeden"),imp_globals);
  leistungenI.Import("Lagerkosten"               ,source_ph->GPH("Lagerkosten"),imp_globals);
  leistungenI.Import("GewerblicheSachen"         ,source_ph->GPH("GewerblicheSachen"),imp_globals);
  leistungenI.Import("Gartenmoebel"              ,source_ph->GPH("Gartenmoebel"),imp_globals);
  leistungenI.Import("DiebstahlAUSPkw"           ,source_ph->GPH("DiebstahlAUSPkw"),imp_globals);
  leistungenI.Import("Bankschliessfaecher"       ,source_ph->GPH("Bankschliessfaecher"),imp_globals);
  leistungenI.Import("Aussenversicherung"        ,source_ph->GPH("Aussenversicherung"),imp_globals);

  leistungenD.Import("Selbstbehalt"              ,source_ph->GPH("Selbstbehalt"),imp_globals);
  leistungenD.Import("Fahrraeder"                ,source_ph->GPH("Fahrraeder"),imp_globals);
  leistungenD.Import("Ueberspannung"             ,source_ph->GPH("Ueberspannung"),imp_globals);

  if ( versicherungsnehmer->Get(FIRST_INSTANCE) )
    pc0_Arbeit(versicherungsnehmer->GPH("job")).ImportOD(source_ph->GPH("OD"),imp_globals);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_HausratVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_HausratVS"

     pc0_HausratVS :: pc0_HausratVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_HausratVS"

     pc0_HausratVS :: pc0_HausratVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"HausratVS",accopt)
{



}


