/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_DBObject

\brief    


\date     $Date: 2006/03/12 19:13:48,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_DBObject_HPP
#define   SC_DBObject_HPP

class     SC_DBObject;

#include  <sDLL.h>
class     SC_DBObject;
#include  <sDLL.h>
class     SC_Property;
class     CS_Connection;
class     SC_DBObject;
class     SC_Property;
#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sSC_Handle.hpp>
#pragma pack(8)

class  SC_DBObject :public SC_Handle,
public DBObjectHandle
{
protected  :         DLL(SC_DBObject)                            *sub_objects ATTR_ALIGN(4);                                 
protected  :         DLL(SC_Property)                            *properties;                                                

public     :
                     DLL(SC_DBObject)                            *get_sub_objects() { return(sub_objects); }
                     DLL(SC_Property)                            *get_properties() { return(properties); }
public     :                                     void ForceClose (logical cache_opt );
public     : virtual                             char *GetName ( );
public     : virtual                             char *GetTypeName ( );
public     :         opa7ImpExp                  SC_DBObject *ProvideDBObject (int64 client_handle, int32 objid, PIACC accopt, uint16 version );
public     :         opa7ImpExp                  SC_DBObject *ProvideDBObject (int64 client_handle, char *objname, PIACC accopt, uint16 version );
public     :         opa7ImpExp                  SC_Property *ProvideProperty (int64 client_handle, char *typenames, PIACC accopt, logical temp_opt_w=NO );
public     :         opa7ImpExp                  SC_Property *ProvideProperty (int64 client_handle, char *operation_rule, ST_OpCodes op_type );
public     :         opa7ImpExp                  logical ReleaseDBObject (SC_DBObject *sc_dbobject );
public     :         opa7ImpExp                  logical ReleaseProperty (SC_Property *sc_property );
public     :                                     logical ReleaseSubObjects (logical cache_opt );
public     :         opa7ImpExp                  logical Remove ( );
public     :         opa7ImpExp                                          SC_DBObject (SC_Handle *parent_handle, int64 client_handle );
public     :         opa7ImpExp                                          SC_DBObject (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle );
public     :                                     void SetDBOHdl (DBObjectHandle *dbo_hdl );
public     : virtual                                                     ~SC_DBObject ( );
};

#pragma pack()
#endif
