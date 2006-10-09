/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Fuehrerschein

\brief    


\date     $Date: 2006/07/07 18:34:57,76 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Fuehrerschein"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Fuehrerschein.hpp>


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

logical pc0_Fuehrerschein :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical   term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("datum") = *source_ph->GPH("Fuehrerschein_seit");
  imp_globals->ImportStaat(GPH("land"),source_ph->GPH("Land_FuehrerscheinpruefungID"));

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Fuehrerschein - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Fuehrerschein"

     pc0_Fuehrerschein :: pc0_Fuehrerschein (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


