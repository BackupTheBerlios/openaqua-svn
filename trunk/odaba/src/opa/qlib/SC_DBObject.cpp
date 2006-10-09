/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_DBObject

\brief    


\date     $Date: 2006/03/12 19:18:06,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_DBObject"

#include  <popa7.h>
#ifndef   DLL_SC_DBObject_HPP
#define   DLL_SC_DBObject_HPP
#include  <sSC_DBObject.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_SC_Property_HPP
#define   DLL_SC_Property_HPP
#include  <sSC_Property.hpp>
#include  <sDLL.h>
#endif
#include  <sCS_Connection.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sSC_DBObject.hpp>
#include  <sSC_Database.hpp>
#include  <sSC_Handle.hpp>
#include  <sSC_Property.hpp>
#include  <sSC_DBObject.hpp>


/******************************************************************************/
/**
\brief  ForceClose - Force database object close



\param  cache_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void SC_DBObject :: ForceClose (logical cache_opt )
{
  SC_Property   *sc_dbprop;
  ReleaseSubObjects(cache_opt);
  
  RollBack(AUTO); // alle nicht beendeten Transaktionen werden zurückgenommen
  
  while ( sc_dbprop = properties->GetTail() )
  {
    sc_dbprop->ForceClose();
    ReleaseProperty(sc_dbprop);
  }
  MSG_Closed();
  if ( cache_opt )
    SetClientObject(0);


}

/******************************************************************************/
/**
\brief  GetName - 


\return resource_name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *SC_DBObject :: GetName ( )
{

  return ( "Unknown" );

}

/******************************************************************************/
/**
\brief  GetTypeName - 


\return resource_type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *SC_DBObject :: GetTypeName ( )
{

  return( "DBObjectHandle" );

}

/******************************************************************************/
/**
\brief  ProvideDBObject - 


\return sc_dbobject -
-------------------------------------------------------------------------------
\brief i00


\param  client_handle -
\param  objid - Instance or index identity
\param  accopt - Access mode
\param  version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDBObject"

SC_DBObject *SC_DBObject :: ProvideDBObject (int64 client_handle, int32 objid, PIACC accopt, uint16 version )
{
  SC_DBObject *sc_dbo = new SC_DBObject(this,client_handle);
BEGINSEQ
  if ( sc_dbo->Open(*this,objid,accopt,version) )    ERROR
  
  sub_objects->AddTail(sc_dbo);
RECOVER
  delete sc_dbo;
  sc_dbo = NULL;
ENDSEQ
  return(sc_dbo);
}

/******************************************************************************/
/**
\brief i01


\param  client_handle -
\param  objname -
\param  accopt - Access mode
\param  version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDBObject"

SC_DBObject *SC_DBObject :: ProvideDBObject (int64 client_handle, char *objname, PIACC accopt, uint16 version )
{
  SC_DBObject *sc_dbo = new SC_DBObject(this,client_handle);
BEGINSEQ
  if ( sc_dbo->Open(*this,objname,accopt,version) )  ERROR
  
  sub_objects->AddTail(sc_dbo);
RECOVER
  delete sc_dbo;
  sc_dbo = NULL;
ENDSEQ
  return(sc_dbo);
}

/******************************************************************************/
/**
\brief  ProvideProperty - 


\return sc_property -
-------------------------------------------------------------------------------
\brief i00


\param  client_handle -
\param  typenames - Type name
\param  accopt - Access mode
\param  temp_opt_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProperty"

SC_Property *SC_DBObject :: ProvideProperty (int64 client_handle, char *typenames, PIACC accopt, logical temp_opt_w )
{
  SC_Property *sc_prop = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  sc_prop = new SC_Property(this,client_handle);
  if ( temp_opt_w )
  {
    if ( sc_prop->Open(*this,typenames,(char *)NULL) ) ERROR
  }
  else
    if ( sc_prop->Open(*this,typenames,accopt) )     ERROR
      
//  sc_prop->RegisterHandle();
  properties->AddTail(sc_prop);
RECOVER
  delete sc_prop;
  sc_prop = NULL;
ENDSEQ
  return(sc_prop);
}

/******************************************************************************/
/**
\brief i02


\param  client_handle -
\param  operation_rule -
\param  op_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProperty"

SC_Property *SC_DBObject :: ProvideProperty (int64 client_handle, char *operation_rule, ST_OpCodes op_type )
{
  SC_Property            *sc_prop = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  sc_prop = new SC_Property(this,client_handle);
  
  if ( sc_prop->Open(*this,op_type,operation_rule) ) ERROR
  properties->AddTail(sc_prop);

RECOVER
  sc_prop = NULL;
ENDSEQ
  return(sc_prop);
}

/******************************************************************************/
/**
\brief  ReleaseDBObject - 


\return term - Termination code

\param  sc_dbobject -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDBObject"

logical SC_DBObject :: ReleaseDBObject (SC_DBObject *sc_dbobject )
{
  SC_DBObject            *sc_dbo;
  logical                 term = NO;
BEGINSEQ
  if ( !sc_dbobject )                                ERROR
    
  if ( sub_objects->Find(sc_dbobject) )
    sub_objects->RemoveAt();

  sc_dbobject->ReleaseSubObjects(NO);
  term = sc_dbobject->Close();
  
  delete sc_dbobject;
  sc_dbobject = NULL;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseProperty - 


\return term - Termination code

\param  sc_property -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProperty"

logical SC_DBObject :: ReleaseProperty (SC_Property *sc_property )
{
  logical                 term = NO;
BEGINSEQ
  if ( !properties )                                 LEAVESEQ
  if ( !sc_property )                                ERROR
    
  if ( properties->Find(sc_property) )
    properties->RemoveAt();

  sc_property->UnregisterHandle();
  sc_property->Close();
  
  delete sc_property;
  sc_property = NULL;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseSubObjects

\return term - Termination code

\param  cache_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseSubObjects"

logical SC_DBObject :: ReleaseSubObjects (logical cache_opt )
{
  SC_DBObject            *sc_dbo;
  logical                 term = NO;
  if ( sub_objects )
  {  
    sub_objects->GoBottom();
    while ( sc_dbo = sub_objects->GetPrev() )
      sc_dbo->ForceClose(cache_opt);
  
    if ( !cache_opt )
      while ( sc_dbo = sub_objects->GetTail() )
        ReleaseDBObject(sc_dbo);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical SC_DBObject :: Remove ( )
{
  logical    term = NO;
  if ( this )
  {
    if ( GetHighObject().IsEmpty() )
      term = ((SC_Database *)parent)->ReleaseDBObject(this);
    else
      term = ((SC_DBObject *)parent)->ReleaseDBObject(this);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SC_DBObject - 


-------------------------------------------------------------------------------
\brief i0


\param  parent_handle -
\param  client_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_DBObject"

                        SC_DBObject :: SC_DBObject (SC_Handle *parent_handle, int64 client_handle )
                     : SC_Handle ((CS_Connection *) parent_handle->get_csconnection(), parent_handle,client_handle),
DBObjectHandle (),
  sub_objects(new DLL(SC_DBObject)),
  properties(new DLL(SC_Property))
{

  SetServerPointer(this);

}

/******************************************************************************/
/**
\brief i01


\param  cs_connection -
\param  parent_handle -
\param  client_handle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_DBObject"

                        SC_DBObject :: SC_DBObject (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle )
                     : SC_Handle (cs_connection,parent_handle,client_handle),
DBObjectHandle (),
  sub_objects(new DLL(SC_DBObject)),
  properties(new DLL(SC_Property))
{



}

/******************************************************************************/
/**
\brief  SetDBOHdl - 



\param  dbo_hdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDBOHdl"

void SC_DBObject :: SetDBOHdl (DBObjectHandle *dbo_hdl )
{

  if ( dbo_hdl )
    *(DBObjectHandle *)this = *dbo_hdl;
  else
    DBObjectHandle::Close();

}

/******************************************************************************/
/**
\brief  ~SC_DBObject - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_DBObject"

                        SC_DBObject :: ~SC_DBObject ( )
{

  ForceClose(NO);
  
  delete sub_objects;
  sub_objects = NULL;

  delete properties;
  properties = NULL;

}


