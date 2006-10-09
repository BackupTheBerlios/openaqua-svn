/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    UtilityHandle

\brief    


\date     $Date: 2006/08/29 16:49:37,04 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UtilityHandle"

#include  <pdefault.h>
#include  <ctype.h>
#include  <cutihdl.h>
#include  <streams.h>
#include  <uthglob.h>
#include  <sDataSourceHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sUtilityHandle.hpp>
#include  <ssvel.hpp>
#include  <sUtilityHandle.hpp>


/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical UtilityHandle :: Close ( )
{
  logical                 term = NO;
  delete sdbusvel;

  if ( sdbuprn )
    fclose(sdbuprn);
    
  res_dict.Close();

  if ( work_dict )
  {
    wd_use_count = 1;
    CloseWorkDict();
  }
  
  delete sdbudat;
  sdbudat = NULL;
  delete sdbures;
  sdbures = 0;
  delete sdbusys;
  sdbusys = NULL;
  
  if ( uti_handle == this )
    uti_handle = NULL;

  if ( close_connection )
    connection.Close();
  return(term);
}

/******************************************************************************/
/**
\brief  CloseDAT - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDAT"

logical UtilityHandle :: CloseDAT ( )
{

  return ( this ? sdbudat->Close() : NO);

}

/******************************************************************************/
/**
\brief  CloseDataSource1 - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDataSource1"

logical UtilityHandle :: CloseDataSource1 ( )
{

  return ( sdbures->Close() );

}

/******************************************************************************/
/**
\brief  CloseDataSource2 - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDataSource2"

logical UtilityHandle :: CloseDataSource2 ( )
{

  return ( sdbudat->Close() );

}

/******************************************************************************/
/**
\brief  CloseRES - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseRES"

logical UtilityHandle :: CloseRES ( )
{
  logical     term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  res_dict.Close();
  CloseDAT();
  if ( sdbures->Close() )                             ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CloseSYS - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseSYS"

logical UtilityHandle :: CloseSYS ( )
{
  logical      term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  CloseRES();
  if ( sdbusys->Close() )                             ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CloseWorkDict - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseWorkDict"

void UtilityHandle :: CloseWorkDict ( )
{

BEGINSEQ
  if ( --wd_use_count > 0 )                     LEAVESEQ
    
  work_dict.Close();

ENDSEQ

}

/******************************************************************************/
/**
\brief  DisplayStat - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayStat"

logical UtilityHandle :: DisplayStat ( )
{

  return (connection.StatDisplay(sdbudat->db_path,sdbuppth));


}

/******************************************************************************/
/**
\brief  GetErrorHelpID - 



\return helpid - 

\param  clsnames - 
\param  errnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorHelpID"

char UtilityHandle :: GetErrorHelpID (char *clsnames, int16 errnum )
{
  char                    helpid;

  return(helpid);
}

/******************************************************************************/
/**
\brief  InitFromIniFile - 



\return term - Termination code

\param  inipath - 
\param  autoini - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFromIniFile"

logical UtilityHandle :: InitFromIniFile (char *inipath, logical autoini )
{
  logical  netopt = NO;
  char    *varstr;
  char     initpath[130];
  char     datasource[129];
  char     server_name[129];
  int32    server_port = 0;
  char    *progpath = ""; if(GetSysVariable("PROGPATH")) progpath = GetSysVariable("PROGPATH");
  char    *progname = ""; if(GetSysVariable("PROGNAME")) progname = GetSysVariable("PROGNAME");
  logical  term = NO;

BEGINSEQ
   *server_name = 0;
   *datasource  = 0;
   strcat(strcat(strcpy(initpath,progpath),progname),".INI");
   inipath = inipath ? inipath : initpath;
   if ( !sdbuintern || autoini )
     SetSysVarINIFile(inipath,progname);
   if ( SOSERROR )                                   SDBERR(221)

   if ( autoini )
   {
     sdbuoenv = ENABLED;
     if ( varstr = GetSectionVariable("SYSAPPL",progname) )
       sdbuoall = ENABLED;

//  common properties
     if ( varstr = GetSectionVariable("ODABA_SERVER",progname) )
     {
       gvtxbts(server_name,varstr,128);
       server_port = 6123;
       if ( (varstr = GetSectionVariable("ODABA_SERVER_PORT",progname)) &&
             *varstr )            
         server_port = atol(varstr);
     }
     if ( varstr = GetSectionVariable("NET",progname) )
       switch ( *varstr )
       {
         case 'Y' :
         case 'y' :
         case 'j' :
         case 'J' :
         case 's' :
         case 'S' : netopt = YES;                       break;
         case 'N' :
         case 'n' : netopt = NO;                        break;
         default  : ;
       }

//  SYSTEM base
     if ( varstr = GetSectionVariable("SYSDB",progname) )
     {
       gvtxbts(sdbusys->dict_path,varstr,255);
       gvtxbts(sdbusys->server_name,server_name,128);
       sdbusys->server_port = server_port;
     }
     else 
       sdbusys->SetupVariables("SYSTEM");

//  RESOURCE base
     if ( varstr = GetSectionVariable("RESDB",progname) )
     {
       gvtxbts(sdbures->dict_path,sdbusys->dict_path,255);
       gvtxbts(sdbures->db_path,varstr,255);
       gvtxbts(sdbures->server_name,server_name,128);
       sdbures->server_port = server_port;
       sdbures->netopt = netopt;
     }  
     else if ( varstr = GetSectionVariable("RESOURCES",progname) )
     {
       gvtxbts(datasource,varstr,128);
       sdbures->SetupVariables(datasource);
     }

//  DATA base
     if ( varstr = GetSectionVariable("DATDB",progname) )
     {
       gvtxbts(sdbudat->dict_path,sdbures->db_path,255);
       gvtxbts(sdbudat->db_path,varstr,255);
       if ( varstr = GetSectionVariable("WORKSPACE",progname) )
         gvtxbts(sdbudat->workspace,varstr,255);
       if ( varstr = GetSectionVariable("DB_VERSION",progname) )
         sdbudat->version = atoi(varstr);
       if ( varstr = GetSectionVariable("SYSTEM_VERSION",progname) )
         sdbudat->system_version = atoi(varstr);
       gvtxbts(sdbudat->server_name,server_name,128);
       sdbudat->server_port = server_port;
       sdbudat->netopt = netopt;
     }
     else if ( varstr = GetSectionVariable("DATA",progname) )
     {
       gvtxbts(datasource,varstr,128);
       sdbudat->SetupVariables(datasource);
     }
     if ( varstr = GetSectionVariable("PRINTPATH",progname) )
       gvtxbts(sdbuppth,varstr,128);
     if ( varstr = GetSectionVariable("PROJECT",progname) )
       gvtxstb(sdbuname,varstr,ID_SIZE);
   }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  InitFromParms - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  SDBUPRM - 



\param  argc - 
\param  argv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFromParms"

logical UtilityHandle :: InitFromParms (int argc, char **argv )
{
  char      progname[256];
  char      progdir[129];
  char      drives[3];
  char      dirs[129];
  int16     parmi = 1;
  logical   term  = NO;
  fildirg(argv[0],drives,dirs);
  SetSysVariable("PROGPATH",strcat(strcpy(progdir,drives),dirs));
  SetSysVariable("PROGNAME",GetFileName(argv[0],progname,NULL));

  InitFromIniFile( argc > 1 ? argv[1] : 0, YES);
  
  while ( argc > ++parmi )
    SetParmVariable(parmi-1,argv[parmi]);

  return(term);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  cmdline - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFromParms"

logical UtilityHandle :: InitFromParms (char *cmdline )
{
  char       cline[256];
  char       progname[256];
  char      *prgpath;
  char       progdir[129];
  char       drives[3];
  char       dirs[129];
  char      *parm;
  int16      parmi = 1;
  logical    term  = NO;

BEGINSEQ
  if ( !(prgpath = strtok(cline," ")) )              ERROR
  fildirg(prgpath,drives,dirs);
  SetSysVariable("PROGPATH",strcat(strcpy(progdir,drives),dirs));
  SetSysVariable("PROGNAME",GetFileName(prgpath,progname,NULL));

  InitFromIniFile(strtok(NULL," "), YES);

  while ( parm = strtok(NULL," ") )
    SetParmVariable(parmi++,parm);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code

\param  utiname - 
\param  utititle - 
\param  inipath - 
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical UtilityHandle :: Initialize (char *utiname, char *utititle, char *inipath, char *progpath, ApplicationTypes application_type )
{
  char    *program_path = "";
  if ( progpath ) {
     program_path = progpath ;
  } else {
     if (GetSysVariable("PROGPATH")) {
        progpath = GetSysVariable("PROGPATH");
     }
  }
  char    *progname  = "";
  if (GetSysVariable("PROGNAME")) progname = GetSysVariable("PROGNAME");
  logical  term = NO;

  if ( !connection )
  {
    connection.Open(inipath,utiname,program_path,application_type);
    close_connection = YES;
  } 
  else if ( inipath && *inipath )
    connection.Initialize(inipath,utiname,program_path,application_type);
    
  gvtxstb(sdbuname, utiname  ? utiname  : "ODABA2-Utility",40);
  gvtxbts(sdbutitle,utititle ? utititle : "ODABA2-Utility",80);
  *sdbuppth = 0;
  
  if ( !*progname && utiname )
    progname = utiname;
     
  SOSRESET
  SetSysVariable("PROGPATH",program_path);
  SetSysVariable("PROGNAME",progname);
  
  uti_handle = this;
  SetUtilityHandle(this);
  return(term);
}

/******************************************************************************/
/**
\brief  NeverCalled - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NeverCalled"

void UtilityHandle :: NeverCalled ( )
{



}

/******************************************************************************/
/**
\brief  OpenDAT - 



\return dbdefptr - Data source handle

\param  accopt - Access option
\param  netopt - 
\param  sysappl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDAT"

DataSourceHandle *UtilityHandle :: OpenDAT (PIACC accopt, logical netopt, logical sysappl )
{
  DataSourceHandle   *dbdefptr = NULL;

BEGINSEQ
  sdbudat->accmode = accopt;
  sdbudat->netopt  = netopt;
  
  if ( sysappl || TestSysVariable("SYSAPPL","YES") )
  {
    sdbudat->SetDictionary(sdbusys->dictionary,sdbusys->dict_path);
    if ( !sdbudat->OpenDatabase()   ||
         !sdbudat->OpenDBObject()    )              ERROR
  }
  else
  {
    if ( !strcmp(sdbures->dict_path,sdbudat->dict_path) )
    {
      sdbudat->SetDictionary(sdbures->dictionary,sdbures->dict_path);
      if ( !sdbudat->OpenDatabase()   ||
           !sdbudat->OpenDBObject()    )            ERROR
    }
    else
      if ( sdbudat->Open(connection,PI_Read) )      ERROR
  }
  
  SetSysVariable("DatDB",uti_handle->sdbudat->db_path);
  dbdefptr = sdbudat;

RECOVER
  SDBError().DisplayMessage();
  sdbudat->Close();
  dbdefptr = NULL;
ENDSEQ
  return(dbdefptr);

}

/******************************************************************************/
/**
\brief  OpenDataSource1 - 



\return term - Termination code

\param  dbname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDataSource1"

logical UtilityHandle :: OpenDataSource1 (char *dbname )
{

  return ( sdbures->Open(connection,dbname) );

}

/******************************************************************************/
/**
\brief  OpenDataSource2 - 



\return term - Termination code

\param  dbname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDataSource2"

logical UtilityHandle :: OpenDataSource2 (char *dbname )
{

  return ( sdbudat->Open(connection,dbname) );

}

/******************************************************************************/
/**
\brief  OpenRES - 



\return dbdefptr - Data source handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRES"

DataSourceHandle *UtilityHandle :: OpenRES ( )
{
  DataSourceHandle   *dbdefptr = NULL;

BEGINSEQ
  if ( !sdbures->dict_path && !sdbures->dict_path )
    sdbures->SetDictionary(sdbusys->dictionary,sdbusys->dict_path);
  else
  {
    if ( sdbures->Connect(connection) )              ERROR
    if ( !sdbures->OpenDictionary(PI_Read) )         ERROR
  }
  
  if ( !strcmp(sdbusys->dict_path,sdbures->db_path) )
  {
    sdbures->SetDatabase(sdbusys->dbhandle);
    sdbures->SetDBObject(sdbusys->object_handle);
    sdbures->accmode = sdbusys->accmode;
    sdbures->netopt  = sdbusys->netopt;
  }
  else
  {
    if ( !strcmp(sdbures->db_path,sdbudat->db_path) ||
         TestSysVariable("ODETEST","YES")            )
    {
      sdbures->netopt  = YES;
      sdbures->accmode = PI_Write;
    }
    if ( !sdbures->OpenDatabase() || !sdbures->OpenDBObject() ) ERROR
  }
  
  SetSysVariable("ResDB",sdbures->db_path);
  dbdefptr = sdbures;
  
  if ( TestSysVariable("SYSAPPL","YES") )
  {
    if ( res_dict.Open(connection,sdbures->db_path,PI_Read,sdbures->netopt) ) 
                                                     ERROR
  }
RECOVER
  SDBError().DisplayMessage();
  sdbures->Close();
ENDSEQ
  return(dbdefptr);

}

/******************************************************************************/
/**
\brief  OpenSYS - 



\return dbdefptr - Data source handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenSYS"

DataSourceHandle *UtilityHandle :: OpenSYS ( )
{
  DataSourceHandle   *dbdefptr = sdbusys;
BEGINSEQ
  if ( !*sdbusys->dict_path )                         SDBERR(7)
    
  if ( GetSysVariable("ODETEST") && 
       *GetSysVariable("ODETEST") == 'Y' )
    sdbusys->netopt  = YES;
  
  sdbusys->dictionary = GetSystemDictionary();
  if ( !strcmp(sdbusys->dict_path,sdbudat->db_path) )
    sdbusys->accmode = PI_Write;
  else if ( !strcmp(sdbusys->dict_path,sdbusys->dictionary.GetPath()) )
                                                     LEAVESEQ
  if ( sdbusys->Open(connection,sdbusys->accmode) )  ERROR
  SetSysVariable("SysDB",uti_handle->sdbusys->db_path);
//  errhndl  = sdbusys->dbhandle;


RECOVER
  SDBError().DisplayMessage();
  dbdefptr = NULL;
ENDSEQ
  return(dbdefptr);

}

/******************************************************************************/
/**
\brief  OpenSource - 



\return term - Termination code

\param  sdbuold - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenSource"

logical UtilityHandle :: OpenSource (UtilityHandle *sdbuold )
{
  logical                 term = NO;
BEGINSEQ
  // hier muß noch die Connection geprüft werden!!
  if ( !sdbuold )
    sdbures->CloseDictionary();
  else
  {
    if ( !strcmp(sdbures->dict_path,sdbuold->sdbures->dict_path) )
      sdbures->SetDictionary(sdbuold->sdbures->dictionary,NULL);
    else if ( !strcmp(sdbures->dict_path,sdbuold->sdbudat->dict_path) )
      sdbures->SetDictionary(sdbuold->sdbudat->dictionary,NULL);
    else if ( !strcmp(sdbures->dict_path,sdbudat->dict_path) )
      sdbures->SetDictionary(sdbudat->dictionary,NULL);
    else
      sdbures->CloseDictionary();
  }
  if ( !sdbures->dictionary )
    if ( !sdbures->OpenDictionary(PI_Read) )               ERROR
    
  if ( !strcmp(sdbures->db_path,sdbures->dict_path) )
    sdbures->SetDatabase(sdbures->dictionary,NULL);
  else 
    if ( !sdbuold )
      sdbures->CloseDatabase();
    else
    {
      if ( !strcmp(sdbures->db_path,sdbuold->sdbures->db_path) )
        sdbures->SetDatabase(sdbuold->sdbures->dbhandle,NULL);
      else if ( !strcmp(sdbures->db_path,sdbuold->sdbudat->db_path) )
        sdbures->SetDatabase(sdbuold->sdbudat->dbhandle,NULL);
      else if ( !strcmp(sdbures->db_path,sdbudat->db_path) )
        sdbures->SetDatabase(sdbudat->dbhandle,NULL);
      else
        sdbures->CloseDatabase();
    }
  if ( !sdbures->dbhandle )
    if ( !sdbures->OpenDatabase() )                       ERROR
      
  if ( !sdbures->OpenDBObject() )                       ERROR
RECOVER
  SDBError().DisplayMessage();
  sdbures->Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenTarget - 



\return term - Termination code

\param  sdbuold - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenTarget"

logical UtilityHandle :: OpenTarget (UtilityHandle *sdbuold )
{
  PIACC      accopt = sdbuinstonly ? PI_Read : PI_Write;
  logical    term   = NO;
BEGINSEQ
  // hier muß noch die Connection geprüft werden!!
  if ( !sdbuold )
    sdbudat->CloseDictionary();
  else  
  {
    if ( sdbuold->sdbures->dictionary.GetAccess() >= accopt &&
         !strcmp(sdbudat->dict_path,sdbuold->sdbures->dict_path) )
      sdbudat->SetDictionary(sdbuold->sdbures->dictionary,NULL);
    else if ( sdbuold->sdbudat->dictionary.GetAccess() >= accopt &&
         !strcmp(sdbudat->dict_path,sdbuold->sdbudat->dict_path) )
      sdbudat->SetDictionary(sdbuold->sdbudat->dictionary,NULL);
    else
      sdbudat->CloseDictionary();
  }
  if ( !sdbudat->dictionary )
    if ( !sdbudat->OpenDictionary(accopt) )                 ERROR
    
  if ( !strcmp(sdbudat->db_path,sdbudat->dict_path) )
    sdbudat->SetDatabase(sdbudat->dictionary,NULL);
  else
    if ( !sdbuold )
      sdbudat->CloseDatabase();
    else
    {
      if ( sdbuold->sdbures->dbhandle.GetAccess() == PI_Write &&
           !strcmp(sdbudat->db_path,sdbuold->sdbures->db_path) )
        sdbudat->SetDatabase(sdbuold->sdbures->dbhandle,NULL);
      else if ( sdbuold->sdbudat->dbhandle.GetAccess() == PI_Write &&
           !strcmp(sdbudat->db_path,sdbuold->sdbudat->db_path) )
        sdbudat->SetDatabase(sdbuold->sdbudat->dbhandle,NULL);
      else
        sdbudat->CloseDatabase();
    }
  if ( !sdbudat->dbhandle )
    if ( !sdbudat->OpenDatabase() )                         ERROR
      
  if ( !sdbudat->OpenDBObject() )                           ERROR
RECOVER
  SDBError().DisplayMessage();
  sdbudat->Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenWorkDict - 



\return term - Termination code

\param  db_handle - Pointer to database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWorkDict"

logical UtilityHandle :: OpenWorkDict (DatabaseHandle &db_handle )
{
  ResourceTypes           res_type = RES_local;  
  logical                 term = NO;
BEGINSEQ
  SDBRESET
  
  if ( !work_dict ) 
  {
    if ( db_handle.IsClient() )
      res_type = RES_server;
    if ( work_dict.Open(connection,db_handle.GetPath(),
                        db_handle.GetAccess(),YES,CUR_VERSION,res_type) ) 
                                                     SDBERR(95)
                                                     SDBCERR
//  if ( !(work_dict.Open(db_handle)) )  SDBERR(95)
  }

  wd_use_count++;

RECOVER
  int saveerr = SDBERROR;
  CloseWorkDict();
  SDBISET(saveerr);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetParmVariable - 



\return term - Termination code

\param  short_val - 
\param  sysvar_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParmVariable"

logical UtilityHandle :: SetParmVariable (int16 short_val, char *sysvar_string )
{
  char       names[17];
  char       string[512];
  char       separator[2];
  char      *blank = " ";
  logical                 term = NO;
  separator[0] = 255;
  separator[1] = 0;
  memset(string,0,sizeof(string));
  strncpy(string,sysvar_string,sizeof(string)-1);
  STRExchange(string,separator,blank,strlen(string));
  
  SetSysVariable(gvtxitp(strcpy(names,"PARM99"),short_val,6),string);

  return(term);
}

/******************************************************************************/
/**
\brief  Setup - 



\return term - Termination code

\param  utiname - 
\param  inipath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical UtilityHandle :: Setup (char *utiname, char *inipath )
{
  logical    term = NO;
BEGINSEQ
  if ( Initialize(utiname,NULL,inipath) )            ERROR

  if ( GetSectionVariable("SYSDB",utiname) )
  {
    gvtxbts(sdbusys->dict_path,GetSectionVariable("SYSDB",utiname),128);
    if ( !OpenSYS() )                                ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StructFieldError - 



\return term - Termination code

\param  fldnames - 
\param  strnames - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructFieldError"

logical __cdecl UtilityHandle :: StructFieldError (char *fldnames, char *strnames )
{
  char                    string[255];

  strcpy(string,"Error in ");
  if ( fldnames )
  {
    strcat(string,"Field: ");
    gvtxbts(string+strlen(string),fldnames,16);
    if ( strnames )
      strcat(string," of ");
  }
  
  if ( strnames )
  {
    strcat(string,"Structure: ");
    gvtxbts(string+strlen(string),strnames,16);
  }
  SDBError().TraceMessage(string);


  return(NO);

}

/******************************************************************************/
/**
\brief  UtilityHandle - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  client_refc - 
\param  utiname - 
\param  inipath - 
\param  utititle - 
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UtilityHandle"

     UtilityHandle :: UtilityHandle (const ODABAClient &client_refc, char *utiname, char *inipath, char *utititle, char *progpath, ApplicationTypes application_type )
                     :   connection(client_refc),
  sdbusys(new DataSourceHandle()),
  sdbures(new DataSourceHandle()),
  sdbudat(new DataSourceHandle()),
  sdbuprn(NULL),
  sdburepl(REPL_none),
  sdbuinstonly(NO),
  sdbutype(UNDEF),
  sdbuosta(UNDEF),
  sdbuoemp(UNDEF),
  sdbuoall(UNDEF),
  sdbuoenv(UNDEF),
  sdbusvel(NULL), 
  retain_sid(NO),
  retain_schemaversion(NO),
  close_connection(NO),
  work_dict(NULL),
  wd_use_count(0),
  res_dict(NULL),
  sdbuintern(NO)
{

  Initialize(utiname,utititle,inipath,progpath,application_type);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  client_refc - 
\param  utiname - 
\param  inipath - 
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UtilityHandle"

     UtilityHandle :: UtilityHandle (const ODABAClient &client_refc, char *utiname, char *inipath, char *progpath, ApplicationTypes application_type )
                     :   connection(client_refc),
  sdbusys(new DataSourceHandle()),
  sdbures(new DataSourceHandle()),
  sdbudat(new DataSourceHandle()),
  sdbuprn(NULL),
  sdburepl(REPL_none),
  sdbuinstonly(NO),
  sdbutype(UNDEF),
  sdbuosta(UNDEF),
  sdbuoemp(UNDEF),
  sdbuoall(UNDEF),
  sdbuoenv(UNDEF),
  sdbusvel(NULL),
  retain_sid(NO),
  retain_schemaversion(NO),
  close_connection(NO),
  sdbuintern(NO)
{

  Initialize(utiname,NULL,inipath,progpath,application_type);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  client_refc - 
\param  utiname - 
\param  progpath - Programme path
\param  application_type - Run as console application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UtilityHandle"

     UtilityHandle :: UtilityHandle (const ODABAClient &client_refc, char *utiname, char *progpath, ApplicationTypes application_type )
                     :   connection(client_refc),
  sdbusys(new DataSourceHandle()), 
  sdbures(new DataSourceHandle()),
  sdbudat(new DataSourceHandle()),
   sdbuprn(NULL),
  sdburepl(REPL_none),
  sdbuinstonly(NO),
  sdbutype(UNDEF),
  sdbuosta(UNDEF),
  sdbuoemp(UNDEF),
  sdbuoall(UNDEF),
  sdbuoenv(UNDEF),
  sdbusvel(NULL),
  retain_sid(NO),
  retain_schemaversion(NO),
  close_connection(NO),
  sdbuintern(YES)
{

  Initialize(utiname,NULL,NULL,progpath,application_type);
  sdbuintern = NO;

}

/******************************************************************************/
/**
\brief  ~UtilityHandle - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~UtilityHandle"

     UtilityHandle :: ~UtilityHandle ( )
{

  Close();

}


