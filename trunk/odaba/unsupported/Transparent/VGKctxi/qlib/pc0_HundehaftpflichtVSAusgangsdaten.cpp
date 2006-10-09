/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_HundehaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/07/21 16:37:28,84 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_HundehaftpflichtVSAusgangsdaten"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Hund.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc_HundehaftpflichtVSAusgangsdaten.hpp>
#include  <spc0_HundehaftpflichtVSAusgangsdaten.hpp>


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

logical pc0_HundehaftpflichtVSAusgangsdaten :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  logical         term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("selbstbehalt") = source_ph->GPH("Selbstbehalt_ID")->GetInt();

  leistungenI.Import("Versicherungssumme",source_ph->GPH("Versicherungssumme"),imp_globals);

  pc0_Hund(GPH("hunde")).ImportAlle(source_ph->GPH("Hunde"),imp_globals);

  pc_HundehaftpflichtVSAusgangsdaten(this).CalculateAnzahlHunde();
  ImportSchaeden(source_ph->GPH("Schaeden"),imp_globals);
  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_HundehaftpflichtVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_HundehaftpflichtVSAusgangsdaten"

     pc0_HundehaftpflichtVSAusgangsdaten :: pc0_HundehaftpflichtVSAusgangsdaten (PropertyHandle *prophdl )
                     : pc0_Ausgangsdaten(prophdl)
{



}


