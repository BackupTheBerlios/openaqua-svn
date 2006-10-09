/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_ImportProtokoll

\brief    


\date     $Date: 2006/07/24 22:38:37,55 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_ImportProtokoll"

#include  <pvgkctxi.h>
#include  <cDataFormSpec.h>
#include  <sTP_ImportGlobals.hpp>
#include  <sdfs.hpp>
#include  <ifil.h>
#include  <igvtx.h>
#include  <spc0_HausratVS.hpp>
#include  <spc0_HundehaftpflichtVS.hpp>
#include  <spc0_KFZVS.hpp>
#include  <spc0_PrivathaftpflichtVS.hpp>
#include  <spc0_RechtsschutzVS.hpp>
#include  <spc0_RosshaftpflichtVS.hpp>
#include  <spc0_UnfallVS.hpp>
#include  <spc0_WohngebaeudeVS.hpp>
#include  <ivgkbi.h>
#include  <spc0_ImportProtokoll.hpp>


/******************************************************************************/
/**
\brief  CheckStatus - 



\return cond - Abbruchbedingung

\param  import_status - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckStatus"

logical pc0_ImportProtokoll :: CheckStatus (ImportStatus import_status )
{
  PropertyHandle   *status = GPH("status");

  return ( status->GetInt() == import_status ? YES : NO );


}

/******************************************************************************/
/**
\brief  GetImportFolder - 



\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImportFolder"

char *pc0_ImportProtokoll :: GetImportFolder (NString &nstring )
{

  return ( ::GetImportFolder(nstring,GetDBHandle(),"XMLActions/") );


}

/******************************************************************************/
/**
\brief  ImportOpenXMLActions - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportOpenXMLActions"

logical pc0_ImportProtokoll :: ImportOpenXMLActions ( )
{
  TP_ImportGlobals     imp_globals(GetDBHandle());
  int32                indx0 = 0;
  logical              term  = NO;
  while ( Get(indx0++) )
    if ( *GPH("status") == "IMPORT_initialisiert" )
      if ( ImportXMLActions(&imp_globals) )
        term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  ImportXMLActions - 



\return term - Abbruchbedingung
-------------------------------------------------------------------------------
\brief  i00 - 



\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLActions"

logical pc0_ImportProtokoll :: ImportXMLActions (int32 id )
{
  logical           term = NO;
BEGINSEQ
  if ( !Get(Key((char *)&id)) )                      CTXERR(21)
  term = ImportXMLActions((TP_ImportGlobals *)NULL);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLActions"

logical pc0_ImportProtokoll :: ImportXMLActions (TP_ImportGlobals *imp_globals )
{
  DataSourceHandle  xml_datasource;
  NString           cpath;
  dttm              datetime;
  char             *ori_kennung    = GetSysVariable("EIGENTUEMER_KENNUNG");
  int16             ori_dateformat = dfs::GetDateFormat();
  logical           del_globals    = imp_globals ? NO : YES;
  logical           term           = NO;
  ODABAClient       tmpoclient;
  WriteMessages("Start",NO);
  SetSysVariable("EIGENTUEMER_KENNUNG","P");
  SetStatus(IMPORT_gestartet,YES);
  dfs::ChangeDate(DFS_YYMMDD_point);

  if ( !imp_globals )
    imp_globals = new TP_ImportGlobals(GetDBHandle());
  else
    imp_globals->Clear();
    
  GetImportFolder(cpath);
  cpath += GetString("xml_file_name");
  SetSysVariable("XML_FILE",cpath);
  if ( xml_datasource.Open(tmpoclient,"XMLImport") )
  {
    imp_globals->Message("Import-Datei konnte nicht geöffner werden");
    SetStatus(IMPORT_fehlerhaft_beendet,NO);
  }
  else
  {
    ImportXMLActions(imp_globals->get_vs_hr() ,xml_datasource.dbhandle,"HRAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_rs() ,xml_datasource.dbhandle,"RSAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_un() ,xml_datasource.dbhandle,"UNAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_phv(),xml_datasource.dbhandle,"PHVAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_hhv(),xml_datasource.dbhandle,"HHVAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_rhv(),xml_datasource.dbhandle,"RHVAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_whg(),xml_datasource.dbhandle,"WHGAction",imp_globals);
    ImportXMLActions(imp_globals->get_vs_kfz(),xml_datasource.dbhandle,"KFZAction",imp_globals);
  }
  
  dfs::ChangeDate(ori_dateformat);

  WriteMessages(imp_globals->GetMessages(),NO);
  WriteMessages("Stop",NO);
  datetime.SetCurrent();
  *GPH("terminated") = datetime;
  SetStatus(IMPORT_erfolgreich_beendet,NO);

  if ( del_globals )
    delete imp_globals;
  SetSysVariable("EIGENTUEMER_KENNUNG",ori_kennung ? ori_kennung : "");
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  VS_pc - 
\param  xml_dbhandle - 
\param  xml_extnames - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLActions"

logical pc0_ImportProtokoll :: ImportXMLActions (pc0Base_VS &VS_pc, DatabaseHandle &xml_dbhandle, char *xml_extnames, TP_ImportGlobals *imp_globals )
{
  PropertyHandle  *actions = GPH("actions");
  int32            indx0   = 0;
  logical          term    = NO;
BEGINSEQ
SDBRESET
  PropertyHandle  source(xml_dbhandle,xml_extnames,PI_Read);  
                                                    SDBCERR
  while ( source.Get(indx0++) )
    if ( VS_pc.ImportVS(&source,imp_globals) )
      term = YES;
    else
      actions->AddReference(VS_pc);
RECOVER
  term = YES;
ENDSEQ
  if ( term )
    SetStatus(IMPORT_fehlerhaft_beendet,YES);
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLActions"

logical pc0_ImportProtokoll :: ImportXMLActions ( )
{
  logical   term = NO;
BEGINSEQ
  if ( !IsPositioned() )                            ERROR
  if ( CheckStatus(IMPORT_erfolgreich_beendet) )    ERROR
  
  term = ImportXMLActions((TP_ImportGlobals *)NULL);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeImportXMLActions - 



\return term - Abbruchbedingung

\param  xml_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeImportXMLActions"

logical pc0_ImportProtokoll :: InitializeImportXMLActions (char *xml_string )
{
  dttm        datetime;
  logical     term     = NO;
BEGINSEQ
  Add(Key::NewAutoident());                         SDBCERR

  datetime.SetCurrent();
  *GPH("created") = datetime;
  SetStatus(IMPORT_angelegt,YES);

  if ( WriteXMLActionsFile(xml_string) )            ERROR
  
  *GPH("hat_hr")  = strstr(xml_string,"HRAction")  ? YES : NO;
  *GPH("hat_rs")  = strstr(xml_string,"RSAction")  ? YES : NO;
  *GPH("hat_un")  = strstr(xml_string,"UNAction")  ? YES : NO;
  *GPH("hat_phv") = strstr(xml_string,"PHVAction") ? YES : NO;
  *GPH("hat_hhv") = strstr(xml_string,"HHVAction") ? YES : NO;
  *GPH("hat_rhv") = strstr(xml_string,"RHVAction") ? YES : NO;
  *GPH("hat_whg") = strstr(xml_string,"WHGAction") ? YES : NO;
  *GPH("hat_kfz") = strstr(xml_string,"KFZAction") ? YES : NO;

  SetStatus(IMPORT_initialisiert,YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetStatus - 



\return term - Abbruchbedingung

\param  import_status - 
\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatus"

logical pc0_ImportProtokoll :: SetStatus (ImportStatus import_status, logical reset_opt )
{
  PropertyHandle   *status = GPH("status");
  logical           term   = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  if ( !reset_opt )
    if ( status->GetInt() > import_status )         LEAVESEQ
    
  *status = import_status;
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WriteMessages - 



\return term - Abbruchbedingung
-------------------------------------------------------------------------------
\brief  i00 - 



\param  nstring - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteMessages"

logical pc0_ImportProtokoll :: WriteMessages (NString &nstring, logical clear_opt )
{
  PropertyHandle  *errors = GPH("errors");
  if ( clear_opt )
    *errors = "";

  if ( !nstring.IsEmpty() )
    *errors += (char *)nstring;

  return(NO);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteMessages"

logical pc0_ImportProtokoll :: WriteMessages (char *string, logical clear_opt )
{
  PropertyHandle  *errors = GPH("errors");
  dbdt             curdate;
  dbtm             curtime;
  NString          nstring;
  if ( clear_opt )
    *errors = "";

  curdate.SetDate();
  curtime.SetTime();
  
  nstring += string;
  nstring += " Import ";
  nstring += curdate;
  nstring += " / ";
  nstring += curtime;
  nstring += "\n";
  *errors += (char *)nstring;

  return(NO);
}

/******************************************************************************/
/**
\brief  WriteXMLActionsFile - 



\return term - Abbruchbedingung

\param  xml_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteXMLActionsFile"

logical pc0_ImportProtokoll :: WriteXMLActionsFile (char *xml_string )
{
  NString     cpath;
  char        filename[65];
  char       *fname = filename;
  logical     term   = NO;
BEGINSEQ
  GetImportFolder(cpath);
  CTXSETEV1(cpath,0)
//  if ( MakePathDirectories(cpath) )                 CTXERR(20)
  
  strcpy(filename,"XMLActions_99999999.xml");
  gvtxltp(filename,GPH("__AUTOIDENT")->GetInt(),strlen(filename));

  cpath += filename;
  CTXSETEV1(cpath,0)
  if ( WriteTextFile(cpath,xml_string) )              CTXERR(20)

  *GPH("xml_file_name") = filename;
      

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc0_ImportProtokoll - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_ImportProtokoll"

     pc0_ImportProtokoll :: pc0_ImportProtokoll (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_ImportProtokoll"

     pc0_ImportProtokoll :: pc0_ImportProtokoll (DatabaseHandle &dbhandle, PIACC accopt )
                     : PropertyHandle(dbhandle,"ImportProtokoll",accopt)
{



}


