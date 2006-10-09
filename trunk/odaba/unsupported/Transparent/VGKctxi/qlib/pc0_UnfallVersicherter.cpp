/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_UnfallVersicherter

\brief    


\date     $Date: 2006/07/03 12:04:53,50 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_UnfallVersicherter"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_UnfallVersicherter.hpp>


/******************************************************************************/
/**
\brief  ImportDaten - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  partner_opt - 
\param  kinder_opt - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportDaten"

logical pc0_UnfallVersicherter :: ImportDaten (PropertyHandle *source_ph, logical partner_opt, logical kinder_opt, TP_ImportGlobals *imp_globals )
{
  char       *source_prop =   partner_opt ? "Partner" 
                            : kinder_opt  ? "Kinder"
                            :               "VN";
  char        prop_path[65];
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("vers_summe")     = *source_ph->GPH(strcat(strcpy(prop_path,"VersSumme"),source_prop));
  *GPH("kosmetische_op") = *source_ph->GPH(strcat(strcpy(prop_path,"KosmetischeOP"),source_prop));
  *GPH("unfall_tod")     = *source_ph->GPH(strcat(strcpy(prop_path,"Unfalltod"),source_prop));
  *GPH("unfall_rente")   = *source_ph->GPH(strcat(strcpy(prop_path,"UnfallRente"),source_prop));
  *GPH("ktg")            = *source_ph->GPH(strcat(strcpy(prop_path,"KTG"),source_prop));
  *GPH("progression")    = *source_ph->GPH(strcat(strcpy(prop_path,"Progression"),source_prop));

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportResult - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  partner_opt - 
\param  kinder_opt - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportResult"

logical pc0_UnfallVersicherter :: ImportResult (PropertyHandle *source_ph, logical partner_opt, logical kinder_opt, TP_ImportGlobals *imp_globals )
{
  char       *source_prop =   partner_opt ? "Partner" 
                            : kinder_opt  ? "Kinder"
                            :               "VN";
  char        prop_path[65];
  logical     term = NO;
BEGINSEQ
  if ( Provide(0,imp_globals) )                     ERROR

  *GPH("vers_summe")     = *source_ph->GPH(strcat(strcpy(prop_path,"VersSumme"),source_prop));
  *GPH("kosmetische_op") = *source_ph->GPH(strcat(strcpy(prop_path,"KosmetischeOP"),source_prop));
  *GPH("unfall_tod")     = *source_ph->GPH(strcat(strcpy(prop_path,"Unfalltod"),source_prop));
  *GPH("unfall_rente")   = *source_ph->GPH(strcat(strcpy(prop_path,"UnfallRente"),source_prop));
  *GPH("ktg")            = *source_ph->GPH(strcat(strcpy(prop_path,"KTG"),source_prop));
  *GPH("progression")    = *source_ph->GPH(strcat(strcpy(prop_path,"Progression"),source_prop));
  *GPH("end_preis")      = *source_ph->GPH(strcat(strcpy(prop_path,"EndPreis"),source_prop));

  if ( kinder_opt )
    *GPH("versichert")   = *source_ph->GPH("AnzahlKinderversichert");
  else if ( partner_opt )
  {
    *GPH("versichert")   = *source_ph->GPH("Partnerversichert");
    *GPH("od")           = *source_ph->GPH("ODPartner");
    *GPH("berufstyp")    = source_ph->GPH("BerufstypPartner_ID")->GetInt();
  }
  else
  {
    *GPH("versichert")   = *source_ph->GPH("VNversichert");
    *GPH("od")           = *source_ph->GPH("ODVn");
    *GPH("berufstyp")    = source_ph->GPH("BerufstypVN_ID")->GetInt();
  }

  if ( Save(NULL,imp_globals) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_UnfallVersicherter - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_UnfallVersicherter"

     pc0_UnfallVersicherter :: pc0_UnfallVersicherter (PropertyHandle *prophdl )
                     : pc0Base_local(prophdl)
{



}


