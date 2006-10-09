/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Bankverbindung

\brief    


\date     $Date: 2006/06/29 11:04:59,50 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Bankverbindung"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Bankverbindung.hpp>


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

logical pc0_Bankverbindung :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("kontoinhaber") = *source_ph->GPH("KontoInhaber");
  *GPH("kontonummer")  = *source_ph->GPH("Kontonummer");

  imp_globals->ImportBank(GPH("bank"),source_ph->GPH("Bankleitzahl"));

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Bankverbindung - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Bankverbindung"

     pc0_Bankverbindung :: pc0_Bankverbindung (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


