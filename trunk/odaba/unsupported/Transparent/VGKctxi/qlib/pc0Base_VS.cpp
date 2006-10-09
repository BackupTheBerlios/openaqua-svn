/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0Base_VS

\brief    


\date     $Date: 2006/07/21 12:49:25,98 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0Base_VS"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0_Arbeit.hpp>
#include  <spc0_Ausgangsdaten.hpp>
#include  <spc0_Bankverbindung.hpp>
#include  <spc0_Fuehrerschein.hpp>
#include  <spc0_Person.hpp>
#include  <ivgkxi.h>
#include  <spc0Base_VS.hpp>


/******************************************************************************/
/**
\brief  CheckImportStatus - 



\return cond - Abbruchbedingung

\param  import_status - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckImportStatus"

logical pc0Base_VS :: CheckImportStatus (ImportStatus import_status )
{
  PropertyHandle   *status = GPH("import_status");
  return ( status->GetInt() == import_status ? YES : NO );

}

/******************************************************************************/
/**
\brief  CheckValidExistence - 



\return term - Abbruchbedingung

\param  key - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValidExistence"

logical pc0Base_VS :: CheckValidExistence (Key key, TP_ImportGlobals *imp_globals )
{
  NString     error;
  logical     term  = NO;
BEGINSEQ
  if ( !Get(key) )                                 LEAVESEQ

  if ( !CheckImportStatus(IMPORT_fehlerhaft_beendet) )
  {
    error = "existiert bereits";
    ERROR
  }
  else
  {
    Delete(AUTO);
    if ( !SDBERROR )                                LEAVESEQ
    error = "' existiert bereits mit status = 'Import_gestarted' und konnte nicht gelöscht werden.";
    ERROR
  }
RECOVER
  error += " Import nicht ausgefuehrt!";
  imp_globals->Message(error);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateVS - 



\return term - Abbruchbedingung

\param  kenner - 
\param  id - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVS"

logical pc0Base_VS :: CreateVS (char kenner, int32 id, TP_ImportGlobals *imp_globals )
{
  char        ik_area[20];
  Key         idkey(ik_area);
  NString     nstring;
  logical     term = NO;
BEGINSEQ
  imp_globals->SetError(NO);
  if ( !id )
  {
    imp_globals->SetMessageStart("Action - ");
    imp_globals->Message("ID nicht angegeben oder 0.");
    ERROR
  }

  nstring += "Vorgang '";
  GetIdentString(nstring,kenner,id,NO);
  nstring += "' -- ";
  imp_globals->SetMessageStart(nstring);
   
  nstring += "wird importiert";
  Output(nstring);

  CalculateIdentKey(ik_area,sizeof(ik_area),kenner,id);
  if ( CheckValidExistence(idkey,imp_globals) )     ERROR
  
  Add(idkey);
  if ( SDBERROR )
  {
    imp_globals->Message("konnte nicht angelegt werden. Import nicht ausgefuehrt!");
    ERROR
  }
  SetImportStatus(IMPORT_angelegt,YES);
RECOVER
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
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0Base_VS :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  PropertyHandle   *source_session     = source_ph->GPH("SESSION");
  PropertyHandle   *source_tarif       = source_ph->GPH("Tarif");
  PropertyHandle   *source_versicherer = source_ph->GPH("Versicherer");
  dttm              datetime;
  logical           term = NO;
  SetImportStatus(IMPORT_initialisiert,YES);

  if ( source_session->Get(FIRST_INSTANCE) )
  {
    *GPH("extern_session") = *source_session->GPH("ID");
    imp_globals->ImportPortal(GPH("portal"),source_session->GPH("portal1"));
    imp_globals->ImportPortal(GPH("portal2"),source_session->GPH("portal2"));
  }
  imp_globals->ImportWerbePartner(GPH("werbepartner"),source_ph->GPH("Werbepartner"));

  if ( source_versicherer->Get(FIRST_INSTANCE) )
    imp_globals->ImportVersicherer(GPH("versicherer"),source_versicherer->GPH("ID"));

  if ( source_tarif->Get(FIRST_INSTANCE) )
    imp_globals->ImportTarif(GPH("tarif"),source_tarif->GPH("ID"));

  *GPH("typ")               = *source_ph->GPH("State");
  *GPH("extern_control_id") = *source_ph->GPH("ControlIdent");

  datetime.SetDate(source_ph->GPH("CREATED")->GetDate());
  *GPH("created") = datetime;
  
  ImportBestand(source_ph->GPH("Bestand"),imp_globals);
  ImportDaten(source_ph->GPH("Daten"),imp_globals);
  ImportResult(source_ph->GPH("Result"),imp_globals);

  CalculateAblauf();
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

logical pc0Base_VS :: ImportArbeitgeber (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  PropertyHandle   *ausgangs_daten      = GPH("ausgangs_daten");
  PropertyHandle   *versicherungsnehmer = GPH("versicherungsnehmer");
  logical           term                = NO;
  if ( ausgangs_daten->Get(FIRST_INSTANCE) )
    pc0_Arbeit(ausgangs_daten->GPH("job")).ImportArbeitgeber(source_ph,imp_globals);
  if ( versicherungsnehmer->Get(FIRST_INSTANCE) )
    pc0_Arbeit(versicherungsnehmer->GPH("job")).ImportArbeitgeber(source_ph,imp_globals);

  return(term);
}

/******************************************************************************/
/**
\brief  ImportBestand - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBestand"

logical pc0Base_VS :: ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Bankverbindung   bankverbindung(GPH("bankverbindung"));
  logical              term           = NO;
BEGINSEQ
  if ( !source_ph->Get(FIRST_INSTANCE) )
  {
    imp_globals->Message("Action-Bestand fehlt");
    ERROR
  }
  else
  {
    *GPH("bankeinzug") = *source_ph->GPH("willBankeinzug");
    bankverbindung.Import(source_ph,imp_globals);
  }

RECOVER
  imp_globals->SetError(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportBestandVV - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportBestandVV"

logical pc0Base_VS :: ImportBestandVV (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Ausgangsdaten    ausgangs_daten(GPH("ausgangs_daten"));
  logical              term = NO;
BEGINSEQ
  if ( pc0Base_VS::ImportBestand(source_ph,imp_globals) )
                                                    ERROR
  ausgangs_daten.ImportVV(source_ph,imp_globals);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportDaten - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportDaten"

logical pc0Base_VS :: ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Ausgangsdaten    ausgangs_daten(GPH("ausgangs_daten"));
  pc0_Person           versicherungsnehmer(GPH("versicherungsnehmer"));
  pc0_Person           partner(GPH("partner"));
  logical              term           = NO;
BEGINSEQ
  if ( !source_ph->Get(FIRST_INSTANCE) )
  {
    imp_globals->Message("Action-Daten fehlt");
    ERROR
  }
  else
  {
    *GPH("versicherungs_beginn") = *source_ph->GPH("Versicherungsbeginn");
    ausgangs_daten.Import(source_ph,imp_globals);
    versicherungsnehmer.Import(source_ph->GPH("PersonVN"),imp_globals,YES);
    partner.Import(source_ph->GPH("PersonPartner"),imp_globals,NO);
  }
RECOVER
  imp_globals->SetError(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportFuehrerscheinVN - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportFuehrerscheinVN"

logical pc0Base_VS :: ImportFuehrerscheinVN (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  PropertyHandle   *versicherungsnehmer = GPH("versicherungsnehmer");
  logical           term                = NO;
BEGINSEQ
  if ( !versicherungsnehmer->Get(FIRST_INSTANCE) )
  {
    imp_globals->Message("Versicherungsnehmer konnte nicht eingestellt werden. Kinder nicht importiert.");
    ERROR
  }
  else
    pc0_Fuehrerschein(versicherungsnehmer->GPH("fuehrerschein")).Import(source_ph,imp_globals);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportKinderVN - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportKinderVN"

logical pc0Base_VS :: ImportKinderVN (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  PropertyHandle   *versicherungsnehmer = GPH("versicherungsnehmer");
  logical           term                = NO;
BEGINSEQ
  if ( !versicherungsnehmer->Get(FIRST_INSTANCE) )
  {
    imp_globals->Message("Versicherungsnehmer konnte nicht eingestellt werden. Kinder nicht importiert.");
    ERROR
  }
  else
    pc0_Person(versicherungsnehmer->GPH("kinder")).ImportKinder(source_ph,imp_globals);

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
\param  vn_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportOD"

logical pc0Base_VS :: ImportOD (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals, logical vn_opt )
{
  PropertyHandle   *ausgangs_daten      = GPH("ausgangs_daten");
  PropertyHandle   *versicherungsnehmer = GPH("versicherungsnehmer");
  logical           term                = NO;
  if ( ausgangs_daten->Get(FIRST_INSTANCE) )
    pc0_Arbeit(ausgangs_daten->GPH("job")).ImportOD(source_ph,imp_globals);

  if ( vn_opt )
    if ( versicherungsnehmer->Get(FIRST_INSTANCE) )
      pc0_Arbeit(versicherungsnehmer->GPH("job")).ImportOD(source_ph,imp_globals);

  return(term);
}

/******************************************************************************/
/**
\brief  ImportResult - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportResult"

logical pc0Base_VS :: ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  pc0_Bankverbindung   bankverbindung(GPH("bankverbindung"));
  logical              term           = NO;
BEGINSEQ
  if ( !source_ph->Get(FIRST_INSTANCE) )
  {
    imp_globals->Message("Action-Result fehlt");
    ERROR
  }
  else
  {
    *GPH("fuenfjahresvertrag") = *source_ph->GPH("Fuenfjahresvertrag");
    *GPH("beitrag")            = *source_ph->GPH("Beitrag");
    imp_globals->ImportZahlungsweise(GPH("zahlungsweise"),source_ph->GPH("Zahlungsweise_ID"));
  }
RECOVER
  imp_globals->SetError(YES);
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
\param  vn_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportSebststaendig"

logical pc0Base_VS :: ImportSebststaendig (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals, logical vn_opt )
{
  PropertyHandle   *ausgangs_daten      = GPH("ausgangs_daten");
  PropertyHandle   *versicherungsnehmer = GPH("versicherungsnehmer");
  logical           term                = NO;
  if ( ausgangs_daten->Get(FIRST_INSTANCE) )
    pc0_Arbeit(ausgangs_daten->GPH("job")).ImportSebststaendig(source_ph,imp_globals);

  if ( vn_opt )
    if ( versicherungsnehmer->Get(FIRST_INSTANCE) )
      pc0_Arbeit(versicherungsnehmer->GPH("job")).ImportSebststaendig(source_ph,imp_globals);

  return(term);
}

/******************************************************************************/
/**
\brief  ImportVS - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportVS"

logical pc0Base_VS :: ImportVS (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  logical     term = NO;
BEGINSEQ
  if ( CreateVS('P',source_ph->GPH("ID")->GetInt(),imp_globals) )
                                                    ERROR
  if ( Import(source_ph,imp_globals) )
    term = YES;
  
  if ( SaveVS(imp_globals) )
    term = YES;


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveVS - 



\return term - Abbruchbedingung

\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveVS"

logical pc0Base_VS :: SaveVS (TP_ImportGlobals *imp_globals )
{
  NString      betreff;
  ImportStatus imp_status;
  logical      term = NO;
BEGINSEQ
  if ( !IsPositioned() )                            ERROR

  Save();
  if ( SDBERROR )
  {
    imp_globals->Message("konnte nicht gespeichert werden.");
    imp_globals->SetError(YES);
  }

  GetIdentString(betreff,YES);
  
  if ( term = imp_globals->GetError() ) 
  {
    imp_status = IMPORT_fehlerhaft_beendet;
    betreff   += " - Fehler beim Import";
    imp_globals->Message("Import unvollständig.");
  }
  else
  {
    imp_status = IMPORT_erfolgreich_beendet;
    betreff   += " - zur Policierung bereit";
    imp_globals->Message("erfolgreich importiert.");
  }

  SetImportStatus(imp_status,YES);
  CreateNotiz("Antrag",betreff,"pecumax");
  ProvideInSpecialExtent("ActionNeu");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0Base_VS - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0Base_VS"

     pc0Base_VS :: pc0Base_VS (PropertyHandle *prophdl )
                     : pc_Action(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  extnames - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0Base_VS"

     pc0Base_VS :: pc0Base_VS (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : pc_Action(dbhandle,extnames,accopt)
{



}


