/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_Notiz

\brief    


\date     $Date: 2006/07/17 18:28:42,00 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_Notiz"

#include  <pVGKbase.h>
#include  <spc_DokumentReferenz.hpp>
#include  <spc_Notiz.hpp>


/******************************************************************************/
/**
\brief  CreateDeckungsnote - 



\return term - Abbruchbedingung

\param  betreff_text - 
\param  mail_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDeckungsnote"

logical pc_Notiz :: CreateDeckungsnote (char *betreff_text, char *mail_text, char *von_an )
{
  logical     term = NO;
BEGINSEQ
  if ( !betreff_text )
    betreff_text = "Neuer Vertrag - bitte policieren";

  if ( CreateNotiz("Deckungsnote",betreff_text,mail_text,von_an) )
                                                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateEmailEingangNotiz - 



\return term - Abbruchbedingung

\param  betreff_text - 
\param  sender_email - 
\param  mail_text - 
\param  offen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEmailEingangNotiz"

logical pc_Notiz :: CreateEmailEingangNotiz (char *betreff_text, char *sender_email, char *mail_text, logical offen )
{
  logical       term = NO;
  dbdt          morgen;
BEGINSEQ
  if ( CreateNotiz("Email-Eingang",betreff_text,mail_text,sender_email) )
                                                    ERROR
  if ( !offen )
  {
    morgen.SetDate();
    morgen = morgen+1;
    *GPH("wiedervorlage") = morgen;
  }

  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateNotiz - 



\return term - Abbruchbedingung

\param  typ_string - 
\param  betreff_text - 
\param  mail_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNotiz"

logical pc_Notiz :: CreateNotiz (char *typ_string, char *betreff_text, char *mail_text, char *von_an )
{
  PropertyHandle  *typ  = GPH("typ");
  dbdt             curdate;
  logical          term = NO;
BEGINSEQ
  Add(GetInitInstance());                           SDBCERR
  
  if ( typ_string && *typ_string )
    *typ = typ_string;
  if ( *typ == "Wiedervorlage" )
  {
    curdate.SetDate();
    *GPH("wiedervorlage") = curdate + 3;
  }
  
  if ( betreff_text )
    *GPH("betreff") = betreff_text;

  if ( mail_text)
    *GPH("text") = mail_text;

  if ( von_an )
    *GPH("email") = von_an;
  
  Save();                                           SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateOffeneNotiz - 



\return term - Abbruchbedingung

\param  typ_string - 
\param  betreff_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOffeneNotiz"

logical pc_Notiz :: CreateOffeneNotiz (char *typ_string, char *betreff_text, char *von_an )
{
  logical          term = NO;
BEGINSEQ
  if ( CreateNotiz(typ_string,betreff_text,NULL,von_an) ) 
                                                    ERROR
  if ( ProvideInSpecialExtent("NotizOffen") )       ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreatePolice - 



\return term - Abbruchbedingung

\param  betreff_text - 
\param  anhang - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePolice"

logical pc_Notiz :: CreatePolice (char *betreff_text, char *anhang )
{
  logical     term = NO;
BEGINSEQ
  if ( !betreff_text )
    betreff_text = "Vertrag policiert";

  if ( CreateNotiz("Vertrag-Police",betreff_text,NULL,NULL) )
                                                    ERROR
  pc_DokumentReferenz(GPH("dokumente")).CreateReferenz(anhang);
  Save();                                           SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateWiedervorlageNotiz - 



\return term - Abbruchbedingung
-------------------------------------------------------------------------------
\brief  i00 - 



\param  typ_string - 
\param  betreff_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateWiedervorlageNotiz"

logical pc_Notiz :: CreateWiedervorlageNotiz (char *typ_string, char *betreff_text, char *von_an )
{
  dbdt             curdate;
  logical          term = NO;
BEGINSEQ
  if ( CreateNotiz(typ_string,betreff_text,NULL,von_an) ) 
                                                    ERROR
  curdate.SetDate();
  *GPH("wiedervorlage") = curdate;
  Save();                                           SDBCERR
  
  if ( ProvideInSpecialExtent("NotizWiedervorlage") )
                                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  betreff_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateWiedervorlageNotiz"

logical pc_Notiz :: CreateWiedervorlageNotiz (char *betreff_text, char *von_an )
{

  return ( CreateWiedervorlageNotiz("Wiedervorlage",
                                     betreff_text,von_an) );

}

/******************************************************************************/
/**
\brief  IsWiedervorlageExtent - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWiedervorlageExtent"

logical pc_Notiz :: IsWiedervorlageExtent ( )
{

  return ( IsValid() && !strcmp(GetPropertyPath(),"NotizWiedervorlage") ? YES : NO );
  


}

/******************************************************************************/
/**
\brief  LocateDeckungsnote - 



\return errnum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateDeckungsnote"

int32 pc_Notiz :: LocateDeckungsnote ( )
{
  DEFLOCALERR
  int32            indx0 = 0;
  int32            index = AUTO;
  logical          term  = NO;
BEGINSEQ
  if ( IsPositioned() && *GPH("typ") == "Deckungsnote" )
                                                    LEAVESEQ
  PropertyHandle   copy_ph(*this);
  PropertyHandle  *copy_typ = copy_ph.GPH("typ");

  while ( copy_ph.Get(indx0++) )
    if ( *copy_typ == "Deckungsnote" )
    {
      if ( index != AUTO )                          LOCALERR(26)
      index = indx0-1;
    }
    
  if ( index == AUTO )                              LOCALERR(25)
  Get(index);
  if ( !IsPositioned() || *GPH("typ") != "Deckungsnote" )
                                                    LOCALERR(99)
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  ResetWV - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWV"

logical pc_Notiz :: ResetWV ( )
{
  PropertyHandle  *typ  = GPH("typ");
  logical          term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  if ( *typ == "Wiedervorlage" )
    *typ = "Notiz";               // ist inhaltlich fraglich!!!

  *GPH("wiedervorlage") = dbdt();
  Save();  

  if ( IsWiedervorlageExtent() )
    Delete();
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetMailSend - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMailSend"

logical pc_Notiz :: SetMailSend ( )
{
  dttm        datetime;
  logical     term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  *GPH("typ")   = "Email-Ausgang";
  *GPH("datum") = datetime.SetCurrent();

  Save();                                           SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetWV - 



\return term - Abbruchbedingung

\param  days - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWV"

logical pc_Notiz :: SetWV (int32 days )
{
  PropertyHandle  *wiedervorlage = GPH("wiedervorlage");
  dbdt             newdate;
  dbdt             wv_date;
  logical          term          = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  newdate.SetDate();
  newdate += days;
  wv_date = wiedervorlage->GetDate();

  if ( wv_date.IsEmpty() || newdate < wv_date )
    *wiedervorlage = newdate;
  
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_Notiz - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_Notiz"

     pc_Notiz :: pc_Notiz (PropertyHandle *prophdl )
                     : pcBase(prophdl)
{



}


