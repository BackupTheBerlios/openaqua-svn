/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Person

\brief    


\date     $Date: 2006/07/04 14:13:36,14 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Person"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Adresse.hpp>
#include  <spc0_Arbeit.hpp>
#include  <spc0_Person.hpp>


/******************************************************************************/
/**
\brief  CreatePerson - 


\return term - Abbruchbedingung

\param  kenner - 
\param  id - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePerson"

logical pc0_Person :: CreatePerson (char kenner, int32 id, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( IsWeakTyped() )
    SetType("Person");

  Add(GetInitInstance());
  if ( SDBERROR )
  {
    imp_globals->Message("Neue Person konnte nicht angelegt werden.");
    ERROR
  }
RECOVER
  imp_globals->SetError(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Import - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
\param  vn_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0_Person :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals, logical vn_opt )
{
  logical      term = NO;
BEGINSEQ
  if ( !source_ph->Get(FIRST_INSTANCE) || source_ph->IsEmpty() )
  {
    if ( !vn_opt )                                  LEAVESEQ
    imp_globals->Message("Versicherungsnehmer fehlt");
    ERROR
  }
  else
  {
//*** hier fehlt noch was - wiederfinden??? ***//
    if ( CreatePerson('P',0,imp_globals) )          ERROR
    
    *GPH("name")          = *source_ph->GPH("Nachname");
    *GPH("vorname")       = *source_ph->GPH("Vorname");
    *GPH("geschlecht")    = *source_ph->GPH("Geschlecht");
    *GPH("geburtsdatum")  = *source_ph->GPH("Geburtsdatum");
    *GPH("geburtsort")    = *source_ph->GPH("Geburtsort");
    *GPH("familienstand") = *source_ph->GPH("FamilienstandID");
    *GPH("titel")         = *source_ph->GPH("Titel");

    imp_globals->ImportStaat(GPH("staatsbuergerschaft"),source_ph->GPH("StaatsbuergerVonID"));  

    pc0_Arbeit(GPH("job")).Import(source_ph,imp_globals);
    pc0_Adresse(GPH("adresse")).Import(source_ph->GPH("Adresse"),imp_globals);
    ImportKontakt(source_ph->GPH("Adresse"),imp_globals);
    
    if ( SavePerson(imp_globals) )                  ERROR
  }


RECOVER
  imp_globals->SetError(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportKind - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKind"

logical pc0_Person :: ImportKind (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical      term = NO;
BEGINSEQ
//*** hier fehlt noch was - wiederfinden??? ***//
  if ( CreatePerson('P',0,imp_globals) )           ERROR
    
  *GPH("name")          = *source_ph->GPH("Nachname");
  *GPH("vorname")       = *source_ph->GPH("Vorname");
  *GPH("geburtsdatum")  = *source_ph->GPH("Geburtsdatum");
    
  if ( SavePerson(imp_globals) )                  ERROR


RECOVER
  imp_globals->SetError(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportKinder - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKinder"

logical pc0_Person :: ImportKinder (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  int32       indx0 = 0;
  logical     term  = NO;
  while ( source_ph->Get(indx0++ ) )
    ImportKind(source_ph,imp_globals);
  return(term);
}

/******************************************************************************/
/**
\brief  ImportKontakt - 


\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKontakt"

logical pc0_Person :: ImportKontakt (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
  *GPH("email")                  = *source_ph->GPH("Email");
  *GPH("telefon_tags.vorwahl")   = *source_ph->GPH("TelefonTagsVorwahl");
  *GPH("telefon_tags.nummer")    = *source_ph->GPH("TelefonTagsNummer");
  *GPH("telefon_abends.vorwahl") = *source_ph->GPH("TelefonAbendsVorwahl");
  *GPH("telefon_abends.nummer")  = *source_ph->GPH("TelefonAbendsNummer");
  *GPH("handy.vorwahl")          = *source_ph->GPH("HandyVorwahl");
  *GPH("handy.nummer")           = *source_ph->GPH("HandyNummer");
  *GPH("fax.vorwahl")            = *source_ph->GPH("FaxVorwahl");
  *GPH("fax.nummer")             = *source_ph->GPH("FaxNummer");
  return(term);
}

/******************************************************************************/
/**
\brief  SavePerson - 


\return term - Abbruchbedingung

\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SavePerson"

logical pc0_Person :: SavePerson (TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( !IsPositioned() )                            ERROR

  Save();
  if ( SDBERROR )
  {
    imp_globals->Message("Person konnte nicht gespeichert werden.");
    imp_globals->SetError(YES);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_Person - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Person"

     pc0_Person :: pc0_Person (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


