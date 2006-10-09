/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_WohngebaeudeVS

\brief    


\date     $Date: 2006/07/21 12:13:41,31 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_WohngebaeudeVS"

#include  <pVGKbase.h>
#include  <sPropertyHandle.hpp>
#include  <spc_Leistung.hpp>
#include  <ivgkbi.h>
#include  <spc_WohngebaeudeVS.hpp>


/******************************************************************************/
/**
\brief  CalculateVersicherungssumme - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateVersicherungssumme"

logical pc_WohngebaeudeVS :: CalculateVersicherungssumme ( )
{
  PropertyHandle  baupreis_index(BauPreisIndex());
  PropertyHandle *wert1914 = NULL;
  logical         term     = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  if ( !(wert1914 = pc_Leistung(GPH("leistungenI")).GPHWert("Wert1914",NO)) )
                                                    ERROR
  *GPH("versicherungssumme") = *wert1914 * baupreis_index;
  
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_WohngebaeudeVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_WohngebaeudeVS"

     pc_WohngebaeudeVS :: pc_WohngebaeudeVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc_WohngebaeudeVS"

     pc_WohngebaeudeVS :: pc_WohngebaeudeVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc_Action(dbhandle,"WohngebaeudeVS",accopt)
{



}


