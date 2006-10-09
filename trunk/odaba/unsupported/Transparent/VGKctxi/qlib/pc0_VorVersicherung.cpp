/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_VorVersicherung

\brief    


\date     $Date: 2006/07/04 14:08:05,53 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_VorVersicherung"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_VorVersicherung.hpp>


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

logical pc0_VorVersicherung :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("existiert")            = *source_ph->GPH("hatVorversicherung");
  *GPH("gekuendigt_durch")     = *source_ph->GPH("hatVSgekuendigt");
  *GPH("versicherer_name")     = *source_ph->GPH("VorversicherName");
  *GPH("versicherungs_nummer") = *source_ph->GPH("VVNummer");
  imp_globals->ImportVersicherer(GPH("versicherer"),source_ph->GPH("Vorversicherung_ID"));

  if ( source_ph->IsA("RS_Bestand") )
  {
    *GPH("kuendigung")   = *source_ph->GPH("VVKuendigung");
    *GPH("ablauf_datum") = *source_ph->GPH("VVAblaufDatum");
  }

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportKFZ - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKFZ"

logical pc0_VorVersicherung :: ImportKFZ (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("versicherungs_nummer")     = *source_ph->GPH("VVNummer");
  *GPH("versicherungs_nummer_efz") = *source_ph->GPH("VVNummer_EFZ");
  imp_globals->ImportVersicherer(GPH("versicherer_efz"),source_ph->GPH("Vorversicherer_EFZ_ID"));

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_VorVersicherung - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_VorVersicherung"

     pc0_VorVersicherung :: pc0_VorVersicherung (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


