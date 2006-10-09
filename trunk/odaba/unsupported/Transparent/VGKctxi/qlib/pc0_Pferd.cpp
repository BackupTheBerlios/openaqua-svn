/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Pferd

\brief    


\date     $Date: 2006/07/07 17:34:24,76 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Pferd"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Pferd.hpp>


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

logical pc0_Pferd :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical   term = NO;
BEGINSEQ
  if ( Add(Key::NewAutoident(),imp_globals) )       ERROR

  *GPH("name")         = *source_ph->GPH("Name");
  *GPH("reitpferd")    = *source_ph->GPH("istReitpferd");
  *GPH("pony")         = *source_ph->GPH("istPony");
  *GPH("fohlen")       = *source_ph->GPH("istFohlen");
  *GPH("turnierpferd") = *source_ph->GPH("isTurnierpferd");

  imp_globals->ImportPferderasse(GPH("rasse"),source_ph->GPH("Pferderasse_ID"));

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Pferd - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Pferd"

     pc0_Pferd :: pc0_Pferd (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


