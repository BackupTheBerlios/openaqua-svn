/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Arbeit

\brief    


\date     $Date: 2006/07/03 10:42:08,70 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Arbeit"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Arbeit.hpp>


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

logical pc0_Arbeit :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("odienst")        = *source_ph->GPH("ODienst");
  *GPH("selbststaendig") = *source_ph->GPH("Selbststaendig");
  *GPH("unbef_arb_verh") = *source_ph->GPH("UnbefArbVerh");
  *GPH("beruf_freitext") = *source_ph->GPH("BerufFreitext");
  *GPH("nettoeinkommen") = *source_ph->GPH("Nettoeinkommen");
  *GPH("berufstyp")      = *source_ph->GPH("BerufsTypID");

  imp_globals->ImportBerufsgruppe(GPH("berufsgruppe"),source_ph->GPH("BerufsgruppeID"));
  imp_globals->ImportBranche(GPH("branche"),source_ph->GPH("BrancheID"));

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportArbeitgeber - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportArbeitgeber"

logical pc0_Arbeit :: ImportArbeitgeber (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("arbeitgeber_freitext") = *source_ph;

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportOD - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportOD"

logical pc0_Arbeit :: ImportOD (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("odienst") = *source_ph;

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportSebststaendig - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportSebststaendig"

logical pc0_Arbeit :: ImportSebststaendig (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("selbststaendig") = *source_ph;

  if ( Save(NULL,imp_globals) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Arbeit - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Arbeit"

     pc0_Arbeit :: pc0_Arbeit (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


