/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_RosshaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/06/29 21:10:24,39 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_RosshaftpflichtVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_Pferd.hpp>
#include  <spc0_RosshaftpflichtVSAusgangsdaten.hpp>


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

logical pc0_RosshaftpflichtVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("selbstbehalt") = source_ph->GPH("Selbstbehalt_ID")->GetInt();
  *GPH("name_reitverein") = *source_ph->GPH("ReitvereinName");

  leistungenO.Import("IstMitgliedReitverein",source_ph->GPH("istMitgliedReitverein"),imp_globals);
  leistungenI.Import("Versicherungssumme",source_ph->GPH("Versicherungssumme"),imp_globals);

  pc0_Pferd(GPH("pferde")).ImportAlle(source_ph->GPH("Pferde"),imp_globals);

  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_RosshaftpflichtVSAusgangsdaten - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_RosshaftpflichtVSAusgangsdaten"

     pc0_RosshaftpflichtVSAusgangsdaten :: pc0_RosshaftpflichtVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


