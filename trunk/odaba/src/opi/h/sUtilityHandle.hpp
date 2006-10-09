/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    UtilityHandle

\brief    


\date     $Date: 2006/03/12 19:10:15,42 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UtilityHandle_HPP
#define   UtilityHandle_HPP

class     UtilityHandle;

#define  DISABLED                                  0
#define  ENABLED                                   2
#define  UCB_EV                                    sizeof(sdbuerv1)
#define  UCB_EVL                                   UCB_EV-1
class     UtilityHandle;
class     svel;
#include  <cApplicationTypes.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sDataSourceHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#pragma pack(8)

class  UtilityHandle
{
public     :         ODABAClient                                  connection;                                                
public     :         char                                         sdbuname[40];                                              //
public     :         char                                         sdbutitle[80];                                             //
protected  :         logical                                      sdbuintern;                                                
public     :         DataSourceHandle                            *sdbusys;                                                   //
public     :         DataSourceHandle                            *sdbures;                                                   //
public     :         DataSourceHandle                            *sdbudat;                                                   //
public     :         FILE                                        *sdbuprn;                                                   //
public     :         char                                         sdbuppth[129];                                             //
public     :         PIREPL                                       sdburepl;                                                  //
public     :         logical                                      sdbuinstonly;                                              //
public     :         logical                                      retain_schemaversion;                                      
public     :         logical                                      retain_sid;                                                
public     :         int16                                        sdbutype;                                                  //
public     :         char                                         sdbuosta;                                                  //
public     :         char                                         sdbuoemp;                                                  //
public     :         char                                         sdbuoall;                                                  //
public     :         char                                         sdbuoenv;                                                  //
public     :         svel                                        *sdbusvel;                                                  //
public     :         DictionaryHandle                             work_dict;                                                 //
protected  :         int16                                        wd_use_count;                                              //
public     :         DictionaryHandle                             res_dict;                                                  //
protected  :         logical                                      close_connection;                                          

public     :
                     logical                                      get_sdbuintern() { return(sdbuintern); }
                     logical                                      get_close_connection() { return(close_connection); }
public     :         OPI7ImpExp                  logical Close ( );
public     :         OPI7ImpExp                  logical CloseDAT ( );
public     :         OPI7ImpExp                  logical CloseDataSource1 ( );
public     :         OPI7ImpExp                  logical CloseDataSource2 ( );
public     :         OPI7ImpExp                  logical CloseRES ( );
public     :         OPI7ImpExp                  logical CloseSYS ( );
public     :         OPI7ImpExp                  void CloseWorkDict ( );
public     :         OPI7ImpExp                  logical DisplayStat ( );
public     :                                     char GetErrorHelpID (char *clsnames, int16 errnum=UNDEF );
public     :         OPI7ImpExp                  logical InitFromIniFile (char *inipath, logical autoini=NO );
public     :         OPI7ImpExp                  logical InitFromParms (int argc, char **argv );
public     :         OPI7ImpExp                  logical InitFromParms (char *cmdline );
public     :         OPI7ImpExp                  logical Initialize (char *utiname, char *utititle, char *inipath, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :                                     void NeverCalled ( );
public     :         OPI7ImpExp                  DataSourceHandle *OpenDAT (PIACC accopt, logical netopt, logical sysappl=NO );
public     :         OPI7ImpExp                  logical OpenDataSource1 (char *dbname );
public     :         OPI7ImpExp                  logical OpenDataSource2 (char *dbname );
public     :         OPI7ImpExp                  DataSourceHandle *OpenRES ( );
public     :         OPI7ImpExp                  DataSourceHandle *OpenSYS ( );
public     :         OPI7ImpExp                  logical OpenSource (UtilityHandle *sdbuold );
public     :         OPI7ImpExp                  logical OpenTarget (UtilityHandle *sdbuold );
public     :         OPI7ImpExp                  logical OpenWorkDict (DatabaseHandle &db_handle );
public     :                                     logical SetParmVariable (int16 short_val, char *sysvar_string );
public     :         OPI7ImpExp                  logical Setup (char *utiname, char *inipath );
public     : static                              logical __cdecl StructFieldError (char *fldnames, char *strnames );
public     :         OPI7ImpExp                                          UtilityHandle (const ODABAClient &client_refc, char *utiname, char *inipath, char *utititle, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                                          UtilityHandle (const ODABAClient &client_refc, char *utiname, char *inipath, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                                          UtilityHandle (const ODABAClient &client_refc, char *utiname, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                                          ~UtilityHandle ( );
};

#pragma pack()
#endif
