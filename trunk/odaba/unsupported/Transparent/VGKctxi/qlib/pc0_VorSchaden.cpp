/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_VorSchaden

\brief    


\date     $Date: 2006/06/29 11:05:23,67 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_VorSchaden"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_VorSchaden.hpp>


/******************************************************************************/
/**
\brief  Import - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0_VorSchaden :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Add(Key::NewAutoident(),imp_globals) )       ERROR

  *GPH("jahr")  = *source_ph->GPH("Jahr");
  *GPH("summe") = *source_ph->GPH("Summe");

  if ( source_ph->IsA("KFZ_Schaden") )
  {
    *GPH("is_hp") = *source_ph->GPH("IsHPschaden");
    *GPH("is_tk") = *source_ph->GPH("IsTKschaden");
    *GPH("is_vk") = *source_ph->GPH("IsVKschaden");
  }

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_VorSchaden - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_VorSchaden"

     pc0_VorSchaden :: pc0_VorSchaden (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


