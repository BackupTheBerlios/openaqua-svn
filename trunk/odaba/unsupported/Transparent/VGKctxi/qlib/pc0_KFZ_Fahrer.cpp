/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_KFZ_Fahrer

\brief    


\date     $Date: 2006/07/03 17:36:56,92 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_KFZ_Fahrer"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_KFZ_Fahrer.hpp>


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

logical pc0_KFZ_Fahrer :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Add(Key::NewAutoident(),imp_globals) )       ERROR

  *GPH("geburtsdatum") = *source_ph->GPH("Geburtsdatum");
  *GPH("geschlecht")   = source_ph->GPH("Geschlecht")->GetInt();
  *GPH("kfz_nutzung")  = source_ph->GPH("Nutzung_ID")->GetInt();

  if ( source_ph->IsA("KFZ_Fahrer") )
    *GPH("name")= *source_ph->GPH("Name");
  if ( source_ph->IsA("KFZ_Kind") )
    *GPH("lebt_im_haushalt") = *source_ph->GPH("Lebt_im_Haushalt");

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_KFZ_Fahrer - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_KFZ_Fahrer"

     pc0_KFZ_Fahrer :: pc0_KFZ_Fahrer (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


