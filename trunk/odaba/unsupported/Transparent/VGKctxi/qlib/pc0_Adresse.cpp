/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Adresse

\brief    


\date     $Date: 2006/06/29 13:39:20,92 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Adresse"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Adresse.hpp>


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

logical pc0_Adresse :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
  *GPH("strasse_postfach") = *source_ph->GPH("Strasse");
  *GPH("hausnummer")       = *source_ph->GPH("Hausnummer");
  *GPH("plz")              = *source_ph->GPH("Plz");
  *GPH("stadt")            = *source_ph->GPH("Stadt");
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Adresse - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Adresse"

     pc0_Adresse :: pc0_Adresse (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


