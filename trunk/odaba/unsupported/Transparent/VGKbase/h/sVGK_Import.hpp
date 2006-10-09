/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    VGK_Import

\brief    


\date     $Date: 2006/07/21 14:16:26,75 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   VGK_Import_HPP
#define   VGK_Import_HPP

class     VGK_Import;

#include  <sDataSourceHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
class  VGK_Import
{
protected  :         DataSourceHandle                             source_dsh;                                                // 
protected  :         DatabaseHandle                               source_dbh;                                                // 
protected  :         DatabaseHandle                               target_dbh;                                                // 
protected  :         PropertyHandle                               source_ph;                                                 // 
protected  :         PropertyHandle                               target_ph;                                                 // 

public     :
                     DataSourceHandle                            &get_source_dsh() { return(source_dsh); }
                     DatabaseHandle                              &get_source_dbh() { return(source_dbh); }
                     DatabaseHandle                              &get_target_dbh() { return(target_dbh); }
                     PropertyHandle                              &get_source_ph() { return(source_ph); }
                     PropertyHandle                              &get_target_ph() { return(target_ph); }
public     :                                        void Deinitialize (logical all_opt );
public     :                                        logical ImportImportProtokoll (DatabaseHandle &dbhandle, char *source_path );
public     :                                        logical ImportStammdaten (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_ActionStatus (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_ActorTitel (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_BLZ (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Beruf (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Berufsgruppe (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Branche (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_DokumentTypeVG (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Hunderasse (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_KFZ_Hersteller (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_KFZ_Typ (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_KFZ_Zulassungsbezirk (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Land (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_PLZ (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Partner (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Pferderasse (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Portal (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Tarif (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_Versicherer (DatabaseHandle &dbhandle );
public     :                                        logical ImportStammdaten_standard (DatabaseHandle &dbhandle, char *targ_names, char *srce_names, char *srce_id_proppath );
public     :                                        int32 Initialize (DatabaseHandle &dbhandle, char *targ_names, char *srce_names );
public     :                                        int32 Initialize (DatabaseHandle &dbhandle );
public     :                                        int32 Initialize (DatabaseHandle &dbhandle, char *source_ds );
public     :                                        int32 Initialize (char *targ_names, char *srce_names );
public     :                                        logical SetupStammdaten_Zahlungsweise (DatabaseHandle &dbhandle );
public     : virtual                                void StartImport (char *string );
public     : virtual                                void StopImport (int32 errnum );
public     :                                             VGK_Import ( );
public     :                                             ~VGK_Import ( );
};

#endif
