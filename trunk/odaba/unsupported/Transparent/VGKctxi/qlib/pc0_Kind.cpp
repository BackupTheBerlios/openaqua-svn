/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Kind

\brief    


\date     $Date: 2006/07/07 12:23:19,12 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Kind"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Kind.hpp>


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

logical pc0_Kind :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical   term = NO;
BEGINSEQ
  if ( Add(Key::NewAutoident(),imp_globals) )       ERROR

  *GPH("name")         = *source_ph->GPH("Nachname");
  *GPH("vorname")      = *source_ph->GPH("Vorname");
  *GPH("geburtsdatum") = *source_ph->GPH("Geburtsdatum");

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Kind - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Kind"

     pc0_Kind :: pc0_Kind (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


