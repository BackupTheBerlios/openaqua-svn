/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_PrivathaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/07/20 17:18:27,09 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_PrivathaftpflichtVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <ivgkxi.h>
#include  <spc0_PrivathaftpflichtVSAusgangsdaten.hpp>


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

logical pc0_PrivathaftpflichtVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("selbstbeteiligung")                = source_ph->GPH("Selbstbeteiligung")->GetInt();
  *GPH("familientarif")                    = source_ph->GPH("Familienversicherung")->GetInt();
  *GPH("schluesselschaeden")               = source_ph->GPH("Schluesselschaeden_ID")->GetInt();
  *GPH("deckungssumme_sachschaeden")       = CalculateEnumValue(source_ph->GPH("Deckungssumme_sachschaeden_ID"),-10000);
  *GPH("deckungssumme_vermoegensschaeden") = CalculateEnumValue(source_ph->GPH("Deckungssumme_vermoegensschaeden_ID"),-100);

  leistungenO.Import("Ausfalldeckung"       ,source_ph->GPH("Ausfalldeckung"),imp_globals);
  leistungenO.Import("DeliktunfaehigeKinder",source_ph->GPH("DeliktunfaehigeKinder"),imp_globals);
  leistungenO.Import("VolljaehrigeKinder"   ,source_ph->GPH("VolljaehrigeKinder"),imp_globals);

  leistungenI.Import("Hunde"                ,source_ph->GPH("Hunde"),imp_globals);

  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_PrivathaftpflichtVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_PrivathaftpflichtVSAusgangsdaten"

     pc0_PrivathaftpflichtVSAusgangsdaten :: pc0_PrivathaftpflichtVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


