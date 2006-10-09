/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_DataSource



\date     $Date: 2006/03/12 19:36:45,57 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_DataSource_HPP
#define   pc_DataSource_HPP

class     pc_DataSource;

class     DataSourceHandle;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(4)

class  pc_DataSource :public PropertyHandle
{

public     :
public     :                                     logical CheckDataSource (char *datasource, char *new_name=NULL );
public     :                                     logical CheckName (char *datasource, char *new_name=NULL );
public     :                                     logical DeleteDefinition (char *datasource, char *new_name=NULL );
public     :                                     logical InitInstance (char *datasource, DataSourceHandle *db_def );
public     :                                     logical InitInstance (char *datasource );
public     :                                     logical SaveDefinition (char *datasource, char *new_name=NULL );
public     :                                     logical Setup (DataSourceHandle *db_def, char *datasource );
public     :                                     logical SetupForRCrtExt (char *datasource );
public     :                                                             pc_DataSource (DatabaseHandle &dbhandle );
};

#pragma pack()
#endif
