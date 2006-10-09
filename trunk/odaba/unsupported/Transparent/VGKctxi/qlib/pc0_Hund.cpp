/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Hund

\brief    


\date     $Date: 2006/07/07 17:36:18,51 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Hund"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Hund.hpp>


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

logical pc0_Hund :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical   term = NO;
BEGINSEQ
  if ( Add(Key::NewAutoident(),imp_globals) )       ERROR

  *GPH("name")                 = *source_ph->GPH("Hundename");
  *GPH("geburtsdatum")         = *source_ph->GPH("Geburtsdatum");
  *GPH("rasse_freitext")       = *source_ph->GPH("Hunderasse_Freitext");
  *GPH("misch_rasse_freitext") = *source_ph->GPH("Mischrasse_Freitext");
  *GPH("kampfhund")            = *source_ph->GPH("istKampfhund");

  *GPH("farbe")                = source_ph->GPH("Hundefarbe_ID")->GetInt();
  imp_globals->ImportHunderasse(GPH("rasse"),source_ph->GPH("Hunderasse_ID"));
//  imp_globals->ImportHundeMischrasse(GPH("rasse"),source_ph->GPH("Mischrasse_ID"));

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Hund - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Hund"

     pc0_Hund :: pc0_Hund (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


