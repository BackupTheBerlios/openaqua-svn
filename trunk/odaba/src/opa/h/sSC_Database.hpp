/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Database

\brief    


\date     $Date: 2006/03/12 19:13:49,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Database_HPP
#define   SC_Database_HPP

class     SC_Database;

#include  <sDLL.h>
class     SC_DBObject;
class     CS_Connection;
#include  <cPIACC.h>
#include  <sCheckOptions.hpp>
#include  <sSC_DBObject.hpp>
#include  <sSC_Handle.hpp>
#pragma pack(8)

class  SC_Database :public SC_DBObject,
public DatabaseHandle
{
protected  :         DLL(SC_DBObject)                            *db_objects ATTR_ALIGN(4);                                  //

public     :
public     :                                     logical CheckDB (CheckOptions check_opts, char *source );
public     :                                     void ForceClose (logical cache_opt );
public     : virtual                             char *GetName ( );
public     : virtual                             char *GetTypeName ( );
public     :                                     SC_Handle *IsUsingDB (char *cpath );
public     :         opa7ImpExp                  SC_DBObject *ProvideDBObject (int64 client_handle, PIACC accopt, uint16 version );
public     :         opa7ImpExp                  logical ReleaseDBObject (SC_DBObject *sc_dbobject );
public     :         opa7ImpExp                  logical Remove ( );
public     :         opa7ImpExp                                          SC_Database (SC_Handle *parent_handle, int64 client_handle );
public     :         opa7ImpExp                                          SC_Database (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle );
public     :                                     void SetDBHdl (DatabaseHandle *dbhdl_ptr );
public     : virtual                                                     ~SC_Database ( );
};

#pragma pack()
#endif
