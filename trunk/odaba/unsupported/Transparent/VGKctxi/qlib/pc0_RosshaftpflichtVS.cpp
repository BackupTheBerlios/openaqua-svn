/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_RosshaftpflichtVS

\brief    


\date     $Date: 2006/07/20 16:34:02,15 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_RosshaftpflichtVS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Leistung.hpp>
#include  <spc0_RosshaftpflichtVSAusgangsdaten.hpp>
#include  <spc0_RosshaftpflichtVS.hpp>


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

logical pc0_RosshaftpflichtVS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( ImportBestandVV(source_ph,imp_globals) )     ERROR
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

logical pc0_RosshaftpflichtVS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_RosshaftpflichtVSAusgangsdaten  ausgangs_daten(GPH("ausgangs_daten"));
  logical                             term = NO;
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

logical pc0_RosshaftpflichtVS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Leistung    leistungenO(GPH("leistungenO"));
  pc0_Leistung    leistungenI(GPH("leistungenI"));
  logical         term  = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportResult(source_ph,imp_globals) ) 
                                                    ERROR
  *GPH("versicherungssumme") = *source_ph->GPH("Versicherungssumme");

  leistungenO.Import("Teilnahme_Tourniere"            ,source_ph->GPH("Teilnahme_Tourniere"),imp_globals);
  leistungenO.Import("Teilnahme_Pferderennen"         ,source_ph->GPH("Teilnahme_Pferderennen"),imp_globals);
  leistungenO.Import("Flurschaeden"                   ,source_ph->GPH("Flurschaeden"),imp_globals);
  leistungenO.Import("Fohlen_mitversichert"           ,source_ph->GPH("Fohlen_mitversichert"),imp_globals);
  leistungenO.Import("Private_Kutschfahrten"          ,source_ph->GPH("Private_Kutschfahrten"),imp_globals);
  leistungenO.Import("Fremdreiterrisiko"              ,source_ph->GPH("Fremdreiterrisiko"),imp_globals);
  leistungenO.Import("Ungewollter_Deckakt"            ,source_ph->GPH("Ungewollter_Deckakt"),imp_globals);
  leistungenO.Import("Krankenversicherung"            ,source_ph->GPH("Krankenversicherung"),imp_globals);
  leistungenO.Import("Rechtsschutzversicherung"       ,source_ph->GPH("Rechtsschutzversicherung"),imp_globals);
  leistungenO.Import("Unfallversicherung"             ,source_ph->GPH("Unfallversicherung"),imp_globals);
  leistungenO.Import("Auslandsaufenthalt"             ,source_ph->GPH("Auslandsaufenthalt_Pferde"),imp_globals);

  leistungenI.Import("DeckungssummeVermoegensschaeden",source_ph->GPH("Vermoegensschaden_Pferde"),imp_globals);
  leistungenI.Import("Selbstbeteiligung"              ,source_ph->GPH("Selbstbehalt"),imp_globals);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_RosshaftpflichtVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_RosshaftpflichtVS"

     pc0_RosshaftpflichtVS :: pc0_RosshaftpflichtVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_RosshaftpflichtVS"

     pc0_RosshaftpflichtVS :: pc0_RosshaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0Base_VS(dbhandle,"RosshaftpflichtVS",accopt)
{



}


