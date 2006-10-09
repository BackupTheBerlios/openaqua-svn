/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    LDBQuery

\brief    Database Query
          DBQuery  allows defining  database queries  by means  of an ODABA view
          definition.  A  database  query  usually  re-trieves  data  from  the 
          database.  It  is,  however,  also  pos-sible  to  update  data in the
          database. 
          A  database  query  may  refer  in  different  places  to  OD-ABA  OQL
          expressions.  ODABA-OQL  is  an  object  query  language with specific
          ODABA extensions. 
          You  may run a query against the complete database (global context) or
          in  a reduced context (instance con-text). The context for running the
          query  can be  defined in  the query.  The result  of the query can be
          printed to the console or directed to an output data source.

\date     $Date: 2006/03/12 19:13:35,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LDBQuery_HPP
#define   LDBQuery_HPP

class     LDBQuery;

#include  <sGSRT.h>
class     DBViewDefEntry;
#include  <cPIACC.h>
#include  <sDBQuery.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  LDBQuery :public DBQuery,
public DataSourceHandle
{
protected  :         int32                                        server_connection;                                         
protected  :         int32                                        datasource_connection;                                     
protected  :         NString                                      result_area;                                               
protected  :         char                                        *current_view;                                              
protected  :         GSRT(DBViewDefEntry)                        *view_definitions;                                          
protected  :         char                                         ini_file[257];                                             
protected  :         char                                         user[41];                                                  
protected  :         char                                         pwd[17];                                                   
protected  :         int32                                        last_qid;                                                  

public     :
public     :         opa7ImpExp                  int32 ConnectDataSource (char *data_source_name, PIACC access_mode=PI_Read, char *ini_file=NULL, char *user_name_w=NULL, char *password=NULL );
public     :         opa7ImpExp                  int32 ConnectDataSource (int32 data_source_id );
public     :         opa7ImpExp                  int32 ConnectServer (char *server_name, int32 port_number );
public     :         opa7ImpExp                  int32 ConnectServer (int32 connect_id );
public     :         opa7ImpExp                  int32 Define (char *view_definition );
public     :         opa7ImpExp                  logical DisconnectDataSource (int32 data_source_id );
public     :         opa7ImpExp                  logical DisconnectServer (int32 connect_id );
public     :         opa7ImpExp                  char *Execute (int32 query_id, char *parm_string );
public     :         opa7ImpExp                  char *Execute (char *view_definition );
public     :         opa7ImpExp                                          LDBQuery ( );
public     :                                     logical ShowAttributes (char *structure_name );
public     :                                     logical ShowExtents (char *view_definition );
public     :                                     logical ShowHelp (char *view_definition );
public     :                                     logical ShowReferences (char *structure_name );
public     :         opa7ImpExp                  logical Undefine (int32 query_id );
public     :         opa7ImpExp                                          ~LDBQuery ( );
};

#pragma pack()
#endif
