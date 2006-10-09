/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    TP_ImportGlobals

\brief    


\date     $Date: 2006/07/24 22:36:00,55 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TP_ImportGlobals"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_Stammdaten.hpp>
#include  <sTP_ImportGlobals.hpp>


/******************************************************************************/
/**
\brief  Clear - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void TP_ImportGlobals :: Clear ( )
{

  err_num       = 0;
  messages      = "";
  message_start = "";


}

/******************************************************************************/
/**
\brief  GetError - 



\return errnum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetError"

int32 TP_ImportGlobals :: GetError ( )
{

  return(err_num);

}

/******************************************************************************/
/**
\brief  GetMessages - 



\return nstring - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMessages"

NString &TP_ImportGlobals :: GetMessages ( )
{

  return(messages);

}

/******************************************************************************/
/**
\brief  ImportBank - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBank"

logical TP_ImportGlobals :: ImportBank (PropertyHandle *target_ph, PropertyHandle *source_ph )
{
  char           *blz_string = source_ph->GetString();
  PropertyHandle  idkey(blz_string);
  NString         nstring;
  logical         add  = NO;
  logical         term = NO;
BEGINSEQ
  if ( !*blz_string )                            LEAVESEQ
  
  if ( add = !banken.CheckValidExistance(blz_string) )
  {
    nstring  = "Bank BLZ=";
    nstring += blz_string;
    nstring += " durch Import angelegt";
    Message(nstring);
  }

  target_ph->Add(idkey);
  if ( SDBERROR )
  {
    nstring  = "bank BLZ=";
    nstring += blz_string;
    nstring += " konnte nicht zugeordnet werden.";
    Message(nstring);
    ERROR
  }

  if ( add )
    *target_ph->GPH("name") = *source_ph->GetParentProperty()->GPH("Bankname");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportBeruf - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBeruf"

logical TP_ImportGlobals :: ImportBeruf (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&berufe,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportBerufsgruppe - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBerufsgruppe"

logical TP_ImportGlobals :: ImportBerufsgruppe (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&berufsgruppen,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportBranche - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBranche"

logical TP_ImportGlobals :: ImportBranche (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&branchen,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportHunderasse - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportHunderasse"

logical TP_ImportGlobals :: ImportHunderasse (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&hunderassen,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportKFZ_Zulassungsbezirk - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKFZ_Zulassungsbezirk"

logical TP_ImportGlobals :: ImportKFZ_Zulassungsbezirk (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&kfz_zulassungsbezirke,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportPferderasse - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportPferderasse"

logical TP_ImportGlobals :: ImportPferderasse (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&pferderassen,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportPortal - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportPortal"

logical TP_ImportGlobals :: ImportPortal (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&portale,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportStaat - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStaat"

logical TP_ImportGlobals :: ImportStaat (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&laender,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportStammdatum - 



\return term - Abbruchbedingung

\param  stammdaten_pc - 
\param  target_ph - 
\param  source_ph - 
\param  source_prop - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdatum"

logical TP_ImportGlobals :: ImportStammdatum (pc0_Stammdaten *stammdaten_pc, PropertyHandle *target_ph, PropertyHandle *source_ph, char *source_prop )
{
  int32       extern_id = source_ph->GetInt();
  Key         idkey((char *)&extern_id);
  NString     nstring;
  char       *str  = NULL;
  logical     add  = NO;
  logical     term = NO;
BEGINSEQ
  if ( !extern_id )                                 LEAVESEQ
  
  if ( add = !stammdaten_pc->CheckValidExistance(extern_id) )
  {
    nstring  = stammdaten_pc->GetCurrentType();
    nstring += " ID=";
    nstring += extern_id;
    nstring += " durch Import angelegt";
    Message(nstring);
  }

  target_ph->Add(idkey);
  if ( SDBERROR )
  {
    nstring  = (str = target_ph->GetPropertyPath()) ? str : stammdaten_pc->GetCurrentType();
    nstring += " ID=";
    nstring += extern_id;
    nstring += " konnte nicht zugeordnet werden.";
    Message(nstring);
    ERROR
  }
  
  if ( add && source_prop )
    *target_ph->GPH("name") = *source_ph->GetParentProperty()->GPH(source_prop);


RECOVER
  SetError(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportTarif - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportTarif"

logical TP_ImportGlobals :: ImportTarif (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&tarife,target_ph,source_ph,"NAME") );

}

/******************************************************************************/
/**
\brief  ImportVersicherer - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportVersicherer"

logical TP_ImportGlobals :: ImportVersicherer (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&versicherer,target_ph,source_ph,"NAME") );

}

/******************************************************************************/
/**
\brief  ImportWerbePartner - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportWerbePartner"

logical TP_ImportGlobals :: ImportWerbePartner (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&partner,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  ImportZahlungsweise - 



\return term - Abbruchbedingung

\param  target_ph - 
\param  source_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportZahlungsweise"

logical TP_ImportGlobals :: ImportZahlungsweise (PropertyHandle *target_ph, PropertyHandle *source_ph )
{

  return ( ImportStammdatum(&zahlungsweisen,target_ph,source_ph,NULL) );

}

/******************************************************************************/
/**
\brief  Message - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Message"

void TP_ImportGlobals :: Message (char *string )
{

  if ( string )
  {
    messages += message_start;
    messages += " ";
    messages += string;
    messages += "\n";
  }

}

/******************************************************************************/
/**
\brief  SetError - 




\param  errnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetError"

void TP_ImportGlobals :: SetError (int32 errnum )
{

  err_num = errnum;

}

/******************************************************************************/
/**
\brief  SetMessageStart - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMessageStart"

void TP_ImportGlobals :: SetMessageStart (char *string )
{

  message_start = (char*)(string ? string : "");

}

/******************************************************************************/
/**
\brief  TP_ImportGlobals - 




\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TP_ImportGlobals"

     TP_ImportGlobals :: TP_ImportGlobals (DatabaseHandle &dbhandle )
                     :   versicherer(dbhandle,PI_Read),
  portale(dbhandle,PI_Read),
  partner(dbhandle,PI_Read),
  tarife(dbhandle,PI_Read),
  banken(dbhandle,PI_Read),
  laender(dbhandle,PI_Read),
  berufe(dbhandle,PI_Read),
  berufsgruppen(dbhandle,PI_Read),
  branchen(dbhandle,PI_Read),
  kfz_zulassungsbezirke(dbhandle,PI_Read),
  hunderassen(dbhandle,PI_Read),
  pferderassen(dbhandle,PI_Read),
  zahlungsweisen(dbhandle,PI_Read),
  err_num(0),
  message_start(),
  messages(),
  vs_hr(dbhandle,PI_Write),
  vs_rs(dbhandle,PI_Write),
  vs_un(dbhandle,PI_Write),
  vs_phv(dbhandle,PI_Write),
  vs_hhv(dbhandle,PI_Write),
  vs_rhv(dbhandle,PI_Write),
  vs_whg(dbhandle,PI_Write),
  vs_kfz(dbhandle,PI_Write)
{



}


