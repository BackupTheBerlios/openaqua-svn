/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_HundehaftpflichtVSAusgangsdaten

\brief    


\date     $Date: 2006/07/21 16:42:46,07 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_HundehaftpflichtVSAusgangsdaten"

#include  <pVGKbase.h>
#include  <spc_Hund.hpp>
#include  <spc_HundehaftpflichtVS.hpp>
#include  <spc_Leistung.hpp>
#include  <spc_HundehaftpflichtVSAusgangsdaten.hpp>


/******************************************************************************/
/**
\brief  CalculateAnzahlHunde - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateAnzahlHunde"

logical pc_HundehaftpflichtVSAusgangsdaten :: CalculateAnzahlHunde ( )
{
  pc_Leistung   leistungenI(GPH("leistungenI"));
  pc_Hund       hunde(GPH("hunde"));
  int32         kampfhund_count = 0;
  logical       term            = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  if ( !hunde.GetCount() )                          LEAVESEQ
  
  kampfhund_count = hunde.GetKampfhundCount();

  *leistungenI.GPHWert("Kampfhunde",YES)   = kampfhund_count;
  *leistungenI.GPHWert("Hunde_normal",YES) = hunde.GetCount() - kampfhund_count;
  
  Save();
  
  pc_HundehaftpflichtVS(GetParentProperty()).SetupAnzahlHunde();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_HundehaftpflichtVSAusgangsdaten - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_HundehaftpflichtVSAusgangsdaten"

     pc_HundehaftpflichtVSAusgangsdaten :: pc_HundehaftpflichtVSAusgangsdaten (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


