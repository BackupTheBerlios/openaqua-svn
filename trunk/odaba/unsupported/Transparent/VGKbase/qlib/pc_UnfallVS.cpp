/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_UnfallVS

\brief    


\date     $Date: 2006/07/21 11:52:06,42 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_UnfallVS"

#include  <pVGKbase.h>
#include  <sPropertyHandle.hpp>
#include  <spc_UnfallVS.hpp>


/******************************************************************************/
/**
\brief  CalculateVersicherungssumme - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateVersicherungssumme"

logical pc_UnfallVS :: CalculateVersicherungssumme ( )
{
  PropertyHandle  *uv_versicherungsnehmer = GPH("uv_versicherungsnehmer");
  logical          term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  if ( !uv_versicherungsnehmer->Get(FIRST_INSTANCE) )
                                                    ERROR
  *GPH("versicherungssumme") = *uv_versicherungsnehmer->GPH("vers_summe");
  
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_UnfallVS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_UnfallVS"

     pc_UnfallVS :: pc_UnfallVS (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc_UnfallVS"

     pc_UnfallVS :: pc_UnfallVS (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc_Action(dbhandle,"UnfallVS",accopt)
{



}


