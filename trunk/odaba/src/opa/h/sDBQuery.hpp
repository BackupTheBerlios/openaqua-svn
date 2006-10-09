/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBQuery

\brief    


\date     $Date: 2006/03/12 19:13:00,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBQuery_HPP
#define   DBQuery_HPP

class     DBQuery;

#include  <cPIACC.h>
#include  <sNString.hpp>
class  DBQuery
{

public     :
public     : virtual                             int32 ConnectDataSource (char *data_source_name, PIACC access_mode=PI_Read, char *ini_file=NULL, char *user_name_w=NULL, char *password=NULL );
public     : virtual                             int32 ConnectDataSource (int32 data_source_id );
public     : virtual                             int32 ConnectServer (char *server_name, int32 port_number );
public     : virtual                             int32 ConnectServer (int32 connect_id );
public     :                                                             DBQuery ( );
public     : virtual                             int32 Define (char *view_definition );
public     : virtual                             logical DisconnectDataSource (int32 data_source_id );
public     : virtual                             logical DisconnectServer (int32 connect_id );
public     : virtual                             char *Execute (int32 query_id, char *parm_string );
public     : virtual                             char *Execute (char *view_definition );
public     : virtual                             logical ShowAttributes (char *structure_name );
public     : virtual                             logical ShowExtents (char *view_definition );
public     : virtual                             logical ShowHelp (char *view_definition );
public     : virtual                             logical ShowReferences (char *structure_name );
public     : virtual                             logical Undefine (int32 query_id );
public     : virtual                                                     ~DBQuery ( );
};

#endif
