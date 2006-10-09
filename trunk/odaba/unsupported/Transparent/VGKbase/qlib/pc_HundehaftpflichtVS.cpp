/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_HundehaftpflichtVS

\brief    


\date     $Date: 2006/07/21 16:36:07,65 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_HundehaftpflichtVS"

#include  <pVGKbase.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ActionStatus.hpp>
#include  <spc_Leistung.hpp>
#include  <spc_HundehaftpflichtVS.hpp>


/******************************************************************************/
/**
\brief  SetupAnzahlHunde - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAnzahlHunde"

logical pc_HundehaftpflichtVS :: SetupAnzahlHunde ( )
{
  pc_ActionStatus   status(GPH("status"));
  pc_Leistung       leistungenI(GPH("leistungenI"));
  pc_Leistung       ausgangs_leistungenI(GPH("ausgangs_daten(0).leistungenI"));
  logical           term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  if ( status.CheckStatus(1) )                      LEAVESEQ
  
  *leistungenI.GPHWert("Kampfhunde",YES)   = *ausgangs_leistungenI.GPHWert("Kampfhunde",NO);
  *leistungenI.GPHWert("Hunde_normal",YES) = *ausgangs_leistungenI.GPHWert("Hunde_normal",NO);
  
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_HundehaftpflichtVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_HundehaftpflichtVS"

     pc_HundehaftpflichtVS :: pc_HundehaftpflichtVS (PropertyHandle *prophdl )
                     : pc_Action(prophdl)
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
#define    MOD_ID  "pc_HundehaftpflichtVS"

     pc_HundehaftpflichtVS :: pc_HundehaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc_Action(dbhandle,"HundehaftpflichtVS",accopt)
{



}


