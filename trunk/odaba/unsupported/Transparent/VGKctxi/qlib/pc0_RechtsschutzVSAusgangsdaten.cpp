/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_RechtsschutzVSAusgangsdaten

\brief    


\date     $Date: 2006/07/06 12:58:05,35 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_RechtsschutzVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Arbeit.hpp>
#include  <spc0_Leistung.hpp>
#include  <ivgkxi.h>
#include  <spc0_RechtsschutzVSAusgangsdaten.hpp>


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

logical pc0_RechtsschutzVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  pc0_Leistung    leistungenD(GPH("leistungenD"));
  pc0_Arbeit      job(GPH("job"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("selbstbehalt")      = source_ph->GPH("Selbstbehalt_ID")->GetInt();
  *GPH("versicherungs_typ") = source_ph->GPH("VersicherungsTyp_ID")->GetInt();
  *GPH("familientarif")     = source_ph->GPH("Familientarif")->GetInt();
  *GPH("deckungssumme")     = CalculateEnumValue(source_ph->GPH("Deckungssumme_ID"),-1000);

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

  leistungenD.Import("BruttoJahresmiete"         ,source_ph->GPH("BruttoJahresmiete"),imp_globals);

  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_RechtsschutzVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_RechtsschutzVSAusgangsdaten"

     pc0_RechtsschutzVSAusgangsdaten :: pc0_RechtsschutzVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


