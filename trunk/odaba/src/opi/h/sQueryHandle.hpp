/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    QueryHandle

\brief    Database Query Handle
          DBQuery  allows defining  database queries  by means  of an ODABA view
          definition.  A  database  query  usually  re-trieves  data  from  the 
          database.  It  is,  however,  also  possible  to  update  data  in the
          database. 
          A  database  query  may  refer  in  different  places  to  ODABA  OQL 
          expressions.  ODABA-OQL  is  an  object  query  language with specific
          ODABA extensions. 
          You  may run a query against the complete database (global context) or
          in  a reduced context (instance context).  The context for running the
          query  can be  defined in  the query.  The result  of the query can be
          printed to the console or directed to an output data source.

\date     $Date: 2006/03/12 19:10:15,10 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   QueryHandle_HPP
#define   QueryHandle_HPP

class     QueryHandle;

class     DBQuery;
#include  <cPIACC.h>
#include  <sODABAClient.hpp>
#pragma pack(8)

class  QueryHandle
{
protected  :         DBQuery                                     *query;                                                     

public     :
                     DBQuery                                     *get_query() { return(query); }
public     :                                     logical Close ( );
public     :         OPI7ImpExp                  int32 ConnectDataSource (char *data_source_name, PIACC access_mode=PI_Read, char *ini_file_w=NULL, char *user_name=NULL, char *password_w=NULL );
public     :         OPI7ImpExp                  int32 ConnectDataSource (int32 data_source_id );
public     :         OPI7ImpExp                  int32 ConnectServer (char *server_name, int32 port_number );
public     :         OPI7ImpExp                  int32 ConnectServer (int32 connect_id );
public     :         OPI7ImpExp                  int32 Define (char *view_definition );
public     :         OPI7ImpExp                  logical DisconnectDataSource (int32 data_source_id );
public     :         OPI7ImpExp                  logical DisconnectServer (int32 connect_id );
public     :         OPI7ImpExp                  char *Execute (int32 query_id, char *parm_string );
public     :         OPI7ImpExp                  char *Execute (char *view_definition );
public     :         OPI7ImpExp                                          QueryHandle (logical query_client );
public     :         OPI7ImpExp                  logical Undefine (int32 query_id );
public     :         OPI7ImpExp                                          ~QueryHandle ( );
};

#pragma pack()
#endif
