/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    VGK_Import

\brief    


\date     $Date: 2006/07/24 12:45:42,29 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "VGK_Import"

#include  <pVGKbase.h>
#include  <ifil.h>
#include  <ivgkbi.h>
#include  <sVGK_Import.hpp>


/******************************************************************************/
/**
\brief  Deinitialize - 




\param  all_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void VGK_Import :: Deinitialize (logical all_opt )
{

  target_ph.Close();
  source_ph.Close();

  if ( all_opt )
  {
    target_dbh.Close();
    source_dbh.Close();
    source_dsh.Close();
  }

}

/******************************************************************************/
/**
\brief  ImportImportProtokoll - 



\return term - Abbruchbedingung

\param  dbhandle - 
\param  source_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportImportProtokoll"

logical VGK_Import :: ImportImportProtokoll (DatabaseHandle &dbhandle, char *source_path )
{
  DEFLOCALERR
  logical          open_dbh  = source_dbh.IsValid() ? NO : YES;
  int32            indx0     = 0;
BEGINSEQ
  StartImport(source_path);
  
  if ( open_dbh )
    if ( LOCALERROR = Initialize(dbhandle) )        ERROR

  SetSysVariable("CSV_IMPORT_PROTOKOLL",source_path);
  source_ph.Open(source_dbh,"CSV_ImportProtokoll",PI_Read);
                                                    LOCAL_SDBCERR
  target_ph.Open(target_dbh,"ImportProtokoll",PI_Write);
                                                    LOCAL_SDBCERR
  PropertyHandle  *status = target_ph.GPH("status");
  
  if ( !source_ph.Get(indx0++) )                    LOCALERR(30)
  while ( source_ph.Get(indx0++) )
  {
    target_ph.Copy(source_ph,REPL_none);
    *status = "IMPORT_initialisiert";
    target_ph.Save();
  }
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(open_dbh);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  ImportStammdaten - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten"

logical VGK_Import :: ImportStammdaten (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
BEGINSEQ
  StartImport("Alle Stammdaten");
  if ( LOCALERROR = Initialize(dbhandle) )        ERROR

  SetupStammdaten_Zahlungsweise(dbhandle);  

  ImportStammdaten_ActionStatus(dbhandle);
  ImportStammdaten_ActorTitel(dbhandle);
  ImportStammdaten_DokumentTypeVG(dbhandle);

  ImportStammdaten_Land(dbhandle);
//  ImportStammdaten_PLZ(dbhandle);
  ImportStammdaten_BLZ(dbhandle);

  ImportStammdaten_Partner(dbhandle);
  ImportStammdaten_Portal(dbhandle);
  ImportStammdaten_Tarif(dbhandle);
  ImportStammdaten_Versicherer(dbhandle);

  ImportStammdaten_Beruf(dbhandle);
  ImportStammdaten_Berufsgruppe(dbhandle);
  ImportStammdaten_Branche(dbhandle);
  ImportStammdaten_KFZ_Zulassungsbezirk(dbhandle);
  ImportStammdaten_KFZ_Typ(dbhandle);
  ImportStammdaten_KFZ_Hersteller(dbhandle);
  
  ImportStammdaten_Hunderasse(dbhandle);
  ImportStammdaten_Pferderasse(dbhandle);
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(YES);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  ImportStammdaten_ActionStatus - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_ActionStatus"

logical VGK_Import :: ImportStammdaten_ActionStatus (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "ActionStatus",
                                     "CSV_ActionState",
                                     "ID") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_ActorTitel - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_ActorTitel"

logical VGK_Import :: ImportStammdaten_ActorTitel (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "ActorTitel",
                                     "CSV_ActorTitel",
                                     "ID") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_BLZ - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_BLZ"

logical VGK_Import :: ImportStammdaten_BLZ (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
  logical          open_dbh  = source_dbh.IsValid() ? NO : YES;
  char             idkey[128];
  Key              newkey(idkey);
  int32            indx0     = 0;
BEGINSEQ
  StartImport("s_Bank");

  if ( open_dbh )
    if ( LOCALERROR = Initialize(dbhandle) )        ERROR
  if ( LOCALERROR = Initialize("s_Bank","CSV_BLZ")) ERROR
  
  PropertyHandle  *blz        = source_ph.GPH("blz");
  PropertyHandle  *name       = source_ph.GPH("name");
  PropertyHandle  *plz        = source_ph.GPH("plz");
  PropertyHandle  *ort        = source_ph.GPH("ort");
  PropertyHandle  *adressen   = target_ph.GPH("adressen");
  PropertyHandle  *adr_stadt  = adressen->GPH("stadt");

  while ( source_ph.Get(indx0++) )
  {
    target_ph.Provide(*blz);                        LOCAL_SDBCERR
    target_ph.ExtractKey(newkey);
    target_ph.Copy(source_ph,newkey,REPL_direct);   LOCAL_SDBCERR
    adressen->Provide(*plz);                        LOCAL_SDBCERR
    *adr_stadt = *ort;
    target_ph.Save();
  }
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(open_dbh);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  ImportStammdaten_Beruf - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Beruf"

logical VGK_Import :: ImportStammdaten_Beruf (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Beruf",
                                     "CSV_Beruf",
                                     "calcval") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Berufsgruppe - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Berufsgruppe"

logical VGK_Import :: ImportStammdaten_Berufsgruppe (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Berufsgruppe",
                                     "CSV_Berufsgruppe",
                                     "calcval") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Branche - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Branche"

logical VGK_Import :: ImportStammdaten_Branche (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Branche",
                                     "CSV_Branche",
                                     "calcval") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_DokumentTypeVG - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_DokumentTypeVG"

logical VGK_Import :: ImportStammdaten_DokumentTypeVG (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "DokumentTypeVG",
                                     "CSV_DokumentTypeVG",
                                     "ID") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Hunderasse - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Hunderasse"

logical VGK_Import :: ImportStammdaten_Hunderasse (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Hunderasse",
                                     "CSV_Hunderasse",
                                     "calcval") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_KFZ_Hersteller - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_KFZ_Hersteller"

logical VGK_Import :: ImportStammdaten_KFZ_Hersteller (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_KFZ_Hersteller",
                                     "CSV_KFZ_Hersteller",
                                     "ID") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_KFZ_Typ - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_KFZ_Typ"

logical VGK_Import :: ImportStammdaten_KFZ_Typ (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_KFZ_Typ",
                                     "CSV_KFZ_Typ",
                                     "ID") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_KFZ_Zulassungsbezirk - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_KFZ_Zulassungsbezirk"

logical VGK_Import :: ImportStammdaten_KFZ_Zulassungsbezirk (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_KFZ_Zulassungsbezirk",
                                     "CSV_KFZ_Zulassungsbezirk",
                                     "ID") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Land - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Land"

logical VGK_Import :: ImportStammdaten_Land (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Staat",
                                     "CSV_Land",
                                     "calcval") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_PLZ - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_PLZ"

logical VGK_Import :: ImportStammdaten_PLZ (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
  logical          open_dbh  = source_dbh.IsValid() ? NO : YES;
  int32            extern_id = 0;
  int32            indx0     = 0;
BEGINSEQ
  StartImport("s_Ort");

  if ( open_dbh )
    if ( LOCALERROR = Initialize(dbhandle) )        ERROR
  if ( LOCALERROR = Initialize("s_Ort","CSV_PLZ") ) ERROR
  
  PropertyHandle  *ID         = source_ph.GPH("ID");
  PropertyHandle  *plz        = source_ph.GPH("plz");
  PropertyHandle  *target_plz = target_ph.GPH("plz");
  Key              newkey(extern_id);

  while ( source_ph.Get(indx0++) )
    if ( extern_id = ID->GetInt() )
    {
      if ( strlen(plz->GetString()) >= 5 )
      {
        if ( !target_ph.Get(newkey) )
          target_ph.Provide(newkey);
        else
          if ( *target_plz != *plz )
          {
//            context->DisplayMessage(19,"PLZ",ID->GetString(),plz->GetString(),target_plz->GetString());
            target_ph.ToTop();
          }
        if ( target_ph.IsPositioned() )
        {
          target_ph.Copy(source_ph,newkey,REPL_direct); LOCAL_SDBCERR
          target_ph.Save();
        }
      }
    }
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(open_dbh);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  ImportStammdaten_Partner - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Partner"

logical VGK_Import :: ImportStammdaten_Partner (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Werbepartner",
                                     "CSV_Partner",
                                     "uid") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Pferderasse - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Pferderasse"

logical VGK_Import :: ImportStammdaten_Pferderasse (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Pferderasse",
                                     "CSV_Pferderasse",
                                     "calcval") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Portal - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Portal"

logical VGK_Import :: ImportStammdaten_Portal (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
  logical          open_dbh  = source_dbh.IsValid() ? NO : YES;
  int32            extern_id = 0;
  int32            indx0     = 0;
BEGINSEQ
  StartImport("s_Portal");

  if ( open_dbh )
    if ( LOCALERROR = Initialize(dbhandle) )        ERROR
  if ( LOCALERROR = Initialize("s_Portal","CSV_Portal") )
                                                    ERROR
  PropertyHandle  *ID              = source_ph.GPH("uid");
  PropertyHandle  *partner_ID      = source_ph.GPH("default_partner_id");
  PropertyHandle  *default_partner = target_ph.GPH("default_partner");
  Key              newkey(extern_id);

  while ( source_ph.Get(indx0++) )
    if ( extern_id = ID->GetInt() )
    {
      target_ph.Provide(newkey);                    LOCAL_SDBCERR
      target_ph.Copy(source_ph,newkey,REPL_direct); LOCAL_SDBCERR

      if ( extern_id = partner_ID->GetInt() )
        default_partner->Provide(newkey);           LOCAL_SDBCERR

      target_ph.Save();
    }
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(open_dbh);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  ImportStammdaten_Tarif - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Tarif"

logical VGK_Import :: ImportStammdaten_Tarif (DatabaseHandle &dbhandle )
{

  return ( ImportStammdaten_standard(dbhandle,
                                     "s_Tarif",
                                     "CSV_Tarif",
                                     "uid") );

}

/******************************************************************************/
/**
\brief  ImportStammdaten_Versicherer - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_Versicherer"

logical VGK_Import :: ImportStammdaten_Versicherer (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
  logical          open_dbh  = source_dbh.IsValid() ? NO : YES;
  int32            extern_id = 0;
  int32            indx0     = 0;
BEGINSEQ
  StartImport("s_Gesellschaft");

  if ( open_dbh )
    if ( LOCALERROR = Initialize(dbhandle) )        ERROR
  if ( LOCALERROR = Initialize("s_Gesellschaft","CSV_Versicherer") )
                                                    ERROR

  PropertyHandle  *ID                = source_ph.GPH("ID");
  PropertyHandle  *weburl            = source_ph.GPH("weburl");
  PropertyHandle  *versichertKFZ     = source_ph.GPH("versichertKFZ");
  PropertyHandle  *versichertHaeuser = source_ph.GPH("versichertHaeuser");
  PropertyHandle  *versichertHR      = source_ph.GPH("versichertHR");
  PropertyHandle  *versichertPHV     = source_ph.GPH("versichertPHV");
  PropertyHandle  *versichertRS      = source_ph.GPH("versichertRS");
  PropertyHandle  *versichertUN      = source_ph.GPH("versichertUN");

  PropertyHandle  *kontakt_weburl          = target_ph.GPH("kontakt.weburl");
  PropertyHandle  *antrags_uebermittlungen = target_ph.GPH("antrags_uebermittlungen");
  PropertyHandle  *versichert              = antrags_uebermittlungen->GPH("versichert");
  PropertyHandle   ph_KFZ("KFZ");
  PropertyHandle   ph_WGV("WGV");
  PropertyHandle   ph_HR("HR");
  PropertyHandle   ph_PHV("PHV");
  PropertyHandle   ph_RS("RS");
  PropertyHandle   ph_UN("UN");
  Key              newkey(extern_id);

  while ( source_ph.Get(indx0++) )
    if ( extern_id = ID->GetInt() )
    {
      target_ph.Provide(newkey);                    LOCAL_SDBCERR
      target_ph.Copy(source_ph,newkey,REPL_direct); LOCAL_SDBCERR
      
      if ( !weburl->IsEmpty() )
        *kontakt_weburl = *weburl;
      if ( versichertKFZ && antrags_uebermittlungen->Provide(ph_KFZ) )
        *versichert = *versichertKFZ;
      if ( versichertHaeuser && antrags_uebermittlungen->Provide(ph_WGV) )
        *versichert = *versichertHaeuser;
      if ( versichertHR && antrags_uebermittlungen->Provide(ph_HR) )
        *versichert = *versichertHR;
      if ( versichertPHV && antrags_uebermittlungen->Provide(ph_PHV) )
        *versichert = *versichertPHV;
      if ( versichertRS && antrags_uebermittlungen->Provide(ph_RS) )
        *versichert = *versichertRS;
      if ( versichertUN && antrags_uebermittlungen->Provide(ph_UN) )
        *versichert = *versichertUN;

      target_ph.Save();
    }
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(open_dbh);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  ImportStammdaten_standard - 



\return term - Abbruchbedingung

\param  dbhandle - 
\param  targ_names - 
\param  srce_names - 
\param  srce_id_proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten_standard"

logical VGK_Import :: ImportStammdaten_standard (DatabaseHandle &dbhandle, char *targ_names, char *srce_names, char *srce_id_proppath )
{
  DEFLOCALERR
  logical          open_dbh  = source_dbh.IsValid() ? NO : YES;
  int32            extern_id = 0;
  int32            indx0     = 0;

BEGINSEQ
  StartImport(targ_names);
  
  if ( open_dbh )
    if ( LOCALERROR = Initialize(dbhandle) )        ERROR
  if ( LOCALERROR = Initialize(targ_names,srce_names) )
                                                    ERROR
  PropertyHandle  *ID = source_ph.GPH(srce_id_proppath);
  Key              newkey(extern_id);

  while ( source_ph.Get(indx0++) )
    if ( extern_id = ID->GetInt() )
    {
      target_ph.Provide(newkey);                    LOCAL_SDBCERR
      target_ph.Copy(source_ph,newkey,REPL_direct); LOCAL_SDBCERR
      target_ph.Save();
    }
RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  Deinitialize(open_dbh);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return errnum - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  dbhandle - 
\param  targ_names - 
\param  srce_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

int32 VGK_Import :: Initialize (DatabaseHandle &dbhandle, char *targ_names, char *srce_names )
{
  DEFLOCALERR
BEGINSEQ
  if ( LOCALERROR = Initialize(dbhandle) )          ERROR
  if ( LOCALERROR = Initialize(targ_names,srce_names) )
                                                    ERROR
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

int32 VGK_Import :: Initialize (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
BEGINSEQ
  target_dbh = dbhandle;
  source_dbh.Open(dbhandle.GetDictionary(),PI_Read); LOCAL_SDBCERR
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dbhandle - 
\param  source_ds - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

int32 VGK_Import :: Initialize (DatabaseHandle &dbhandle, char *source_ds )
{
  DEFLOCALERR
BEGINSEQ
  target_dbh = dbhandle;
  source_dsh.Open(ODABAClient(),source_ds); LOCAL_SDBCERR
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  targ_names - 
\param  srce_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

int32 VGK_Import :: Initialize (char *targ_names, char *srce_names )
{
  DEFLOCALERR
  NString   nstring;

BEGINSEQ
  ::GetImportFolder(nstring,target_dbh,"Stammdaten");
  if ( nstring.IsEmpty() )                           LOCALERR(10)
  SetSysVariable("CSV_STAMMDATEN",nstring);

  source_ph.Open(source_dbh,srce_names,PI_Read);     LOCAL_SDBCERR
  target_ph.Open(target_dbh,targ_names,PI_Write);    LOCAL_SDBCERR


RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  SetupStammdaten_Zahlungsweise - 



\return term - Abbruchbedingung

\param  dbhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupStammdaten_Zahlungsweise"

logical VGK_Import :: SetupStammdaten_Zahlungsweise (DatabaseHandle &dbhandle )
{
  DEFLOCALERR
BEGINSEQ
  StartImport("s_Zahlungsweise");
  
  PropertyHandle   target(dbhandle,"s_Zahlungsweise",PI_Write);
                                                    LOCAL_SDBCERR
  if ( target.ExecutePropertyAction("SetupCollectionByTyp",NULL) )
                                                    ERROR

RECOVER

ENDSEQ
  StopImport(LOCALERROR);
  return(LOCALERROR ? YES : NO);
}

/******************************************************************************/
/**
\brief  StartImport - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartImport"

void VGK_Import :: StartImport (char *string )
{



}

/******************************************************************************/
/**
\brief  StopImport - 




\param  errnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopImport"

void VGK_Import :: StopImport (int32 errnum )
{



}

/******************************************************************************/
/**
\brief  VGK_Import - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VGK_Import"

     VGK_Import :: VGK_Import ( )
                     :   source_dsh(),
  source_dbh(),
  target_dbh(),
  source_ph(),
  target_ph()
{



}

/******************************************************************************/
/**
\brief  ~VGK_Import - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~VGK_Import"

     VGK_Import :: ~VGK_Import ( )
{

  Deinitialize(YES);

}


