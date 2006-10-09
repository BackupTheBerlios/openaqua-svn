/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_RechtsschutzVS

\brief    


\date     $Date: 2006/07/20 17:01:27,50 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_RechtsschutzVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_RechtsschutzVSAusgangsdaten.hpp>
#include  <spc0_RechtsschutzVS.hpp>


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

logical pc0_RechtsschutzVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
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

logical pc0_RechtsschutzVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_RechtsschutzVSAusgangsdaten  ausgangs_daten(GPH("ausgangs_daten"));
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

logical pc0_RechtsschutzVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  logical         term                 = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR
  *GPH("versicherungssumme") = *source_ph->GPH("Deckungssumme");
  *GPH("versicherungs_typ")  = source_ph->GPH("VersicherungsTyp_ID")->GetInt();
  *GPH("familientarif")      = source_ph->GPH("Familientarif")->GetInt();

  leistungenO.Import("Mietrechtsschutz"                ,source_ph->GPH("Mietrechtsschutz"),imp_globals);
  leistungenO.Import("Vermietrechtschutz"              ,source_ph->GPH("Vermietrechtschutz"),imp_globals);
  leistungenO.Import("MitversicherungGewerbe"          ,source_ph->GPH("Mitversicherung_gewerbe"),imp_globals);

  leistungenI.Import("Vermietobjekte"                  ,source_ph->GPH("AnzahlVermietobjekte"),imp_globals);
  leistungenI.Import("PKW"                             ,source_ph->GPH("PKW"),imp_globals);
  leistungenI.Import("NutzfahrzeugeBis4t"              ,source_ph->GPH("NutzfahrzeugeBis4t"),imp_globals);
  leistungenI.Import("NutzfahrzeugeUeber4t"            ,source_ph->GPH("NutzfahrzeugeUeber4t"),imp_globals);
  leistungenI.Import("Arbeitsmaschinen"                ,source_ph->GPH("Arbeitsmaschinen"),imp_globals);
  leistungenI.Import("Omnibusse"                       ,source_ph->GPH("Omnibusse"),imp_globals);
  leistungenI.Import("AnhaengerWohnwagen"              ,source_ph->GPH("AnhaengerWohnwagen"),imp_globals);
  leistungenI.Import("KraftradVersicherungskennzeichen",source_ph->GPH("KraftradVersicherungskennzeichen"),imp_globals);
  leistungenI.Import("KraftradAmtlichesKennzeichen"    ,source_ph->GPH("KraftradAmtlichesKennzeichen"),imp_globals);
  leistungenI.Import("GeltungWelt"                     ,source_ph->GPH("Geltung_welt_monate"),imp_globals);
  leistungenI.Import("Wartezeiten"                     ,source_ph->GPH("Wartezeiten"),imp_globals);

  leistungenD.Import("Selbstbehalt"                    ,source_ph->GPH("Selbstbehalt"),imp_globals);
  leistungenD.Import("BruttoJahresmiete"               ,source_ph->GPH("BruttoJahresmiete"),imp_globals);
  leistungenD.Import("Strafkautionsdarlehen"           ,source_ph->GPH("Strafkautionsdarlehen"),imp_globals);
  leistungenD.Import("Versicherungssumme_weltweit"     ,source_ph->GPH("Versicherungssumme_weltweit"),imp_globals);

  ImportOD(source_ph->GPH("OD"),imp_globals,NO);
  ImportSebststaendig(source_ph->GPH("Selbststaendig"),imp_globals,NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_RechtsschutzVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_RechtsschutzVS"

     pc0_RechtsschutzVS :: pc0_RechtsschutzVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_RechtsschutzVS"

     pc0_RechtsschutzVS :: pc0_RechtsschutzVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"RechtsschutzVS",accopt)
{



}


