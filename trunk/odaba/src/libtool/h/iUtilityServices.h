/********************************* Class Declaration ***************************/
/**
\package  Utilities
\class    UtilityServices



\date     $Date: 2006/05/20 13:03:45,40 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UtilityServices_H
#define   UtilityServices_H

#include  <sCSUtilityHandle.hpp>
#include  <sCheckOptions.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sStatistic.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

                   logical __cdecl BackupDB (CSUtilityHandle &uti_handle, char *target );
                   logical __cdecl CheckCS (CSUtilityHandle &uti_handle, char *extent_name, int32 distance, int32 max_count, int32 max_objects );
                   logical __cdecl CheckDB (CSUtilityHandle &uti_handle, CheckOptions check_opts, char *source );
                   logical __cdecl CheckRuntimeParms (int argc, char *argv[], int16 min_parms, int16 max_parms );
                   logical __cdecl CommandLineServices ( );
                   logical __cdecl CopyDB (CSUtilityHandle &uti_handle );
                   logical __cdecl CopyResDB (CSUtilityHandle &uti_handle, logical renamed );
                   logical __cdecl DBDictStatistics (ODABAClient &uti_client, char *db_path, char *temp_path );
                   logical __cdecl DBPerformance (CSUtilityHandle &uti_handle, char *extent, int32 blocksize, char *attribute, char *sort_order );
                   logical __cdecl DBPerformancePrint (int32 no_items, Statistic &stats, int32 s_time );
                   logical __cdecl DBStatistics (ODABAClient &uti_client, char *db_path, char *temp_path );
                   logical __cdecl DBSystemInfo (ODABAClient &uti_client, char *db_path, char *temp_path );
                   char *__cdecl GetCommandPrototype (char *command );
                   logical __cdecl Licence (CSUtilityHandle &uti_handle, char *ini_path );
                   logical __cdecl PackDB (ODABAClient &uti_client, char *db_path, char *temp_path );
                   logical __cdecl PrintWS (DatabaseHandle &dbhandle, char *ws_root, char *user_name, int16 level, logical recursive );
                   logical __cdecl QueryLater (CSUtilityHandle &uti_handle, char *exp_path, char *src_path, char *res_path, char *cls_name, logical dboutput );
                   logical __cdecl RestoreDB (CSUtilityHandle &uti_handle, char *source );
                   logical __cdecl Server (char *ini_file, char *spath, int32 port_number );
                   logical __cdecl SetupDB (CSUtilityHandle &uti_handle, logical renamed );
                   logical __cdecl TestAlignment (CSUtilityHandle &uti_handle, char *strnames );
                   logical __cdecl TestVarious (CSUtilityHandle &uti_handle );
                   logical __cdecl UWorkspace (CSUtilityHandle &uti_handle, char *oper_string, char *ws_name, char *user_name, char *options );

#if defined (__cplusplus)
             }
#endif
#endif
