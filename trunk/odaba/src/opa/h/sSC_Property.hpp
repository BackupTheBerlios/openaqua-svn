/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Property

\brief    Server property handles


\date     $Date: 2006/03/12 19:13:50,78 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Property_HPP
#define   SC_Property_HPP

class     SC_Property;

#include  <sDLL.h>
class     SC_Operation;
#include  <sDLL.h>
class     SC_Property;
class     CSInstanceList;
class     SC_DBObject;
class     SC_Operation;
class     smcb;
#include  <cPIACC.h>
#include  <sCSInstance.hpp>
#include  <sInstance.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSC_Handle.hpp>
#include  <sSC_Property.hpp>
#pragma pack(8)

class  SC_Property :public SC_Handle,
public PropertyHandle
{
protected  :         DLL(SC_Property)                            *properties;                                                //
protected  :         SC_Property                                 *high_property;                                             //
protected  :         CSInstance                                   skeyarea;                                                  //
protected  :         CSInstance                                   idkeyarea;                                                 //
protected  :         CSInstance                                   instarea;                                                  //
protected  :         DLL(SC_Operation)                           *operations;                                                //
protected  :         void                                        *parent_instance;                                           //
protected  :         void                                        *origin;                                                    //
protected  :         logical                                      base_collection;                                           //
protected  :         logical                                      transient_collection;                                      //

public     :
                     DLL(SC_Property)                            *get_properties() { return(properties); }
                     SC_Property                                 *get_high_property() { return(high_property); }
                     CSInstance                                  &get_skeyarea() { return(skeyarea); }
                     CSInstance                                  &get_idkeyarea() { return(idkeyarea); }
                     CSInstance                                  &get_instarea() { return(instarea); }
                     DLL(SC_Operation)                           *get_operations() { return(operations); }
                     void                                        *get_parent_instance() { return(parent_instance); }
                     void                                        *get_origin() { return(origin); }
                     logical                                      get_base_collection() { return(base_collection); }
                     logical                                      get_transient_collection() { return(transient_collection); }
public     :                                     logical CheckInstance (int32 synch_cur=ERIC, int32 synch_loid=UNDEF );
public     :         opa7ImpExp                  smcb *CheckSKey (char *keynames=NULL );
public     :                                     logical FillInstBuffer (CSInstanceList *result, int32 count );
public     :         opa7ImpExp                  logical FillInstResult (CSInstanceList *result, logical error_case );
public     :         opa7ImpExp                  logical FillInstResult (CSInstanceList *result, char *inst_data, logical error_case );
public     :         opa7ImpExp                  logical FillKeyResult (CSInstanceList *result, char *keyptr, logical error_case );
public     :                                     logical FillOpenResult (CSInstanceList *result );
public     :                                     logical FillOpenViewResult (CSInstanceList *result );
public     :                                     void ForceClose ( );
public     :                                     SC_Property *GetBaseProperty (int64 client_handle );
public     : virtual                             char *GetName ( );
public     : virtual                             char *GetTypeName ( );
public     :                                     SC_DBObject *Get_SC_DBObject ( );
public     :         opa7ImpExp                  char *Get_idkeyarea ( );
public     :         opa7ImpExp                  CSInstance &Get_instarea ( );
public     :         opa7ImpExp                  char *Get_skeyarea ( );
public     :                                     logical HasParentChanged ( );
public     :                                     logical OpenProperty (char *propnames );
public     :         opa7ImpExp                  SC_Operation *ProvideOperation (int64 client_handle );
public     :         opa7ImpExp                  SC_Property *ProvideProperty (int64 client_handle, char *propnames );
public     :         opa7ImpExp                  SC_Property *ProvideProperty (int64 client_handle, char *operation_rule, ST_OpCodes op_type );
public     :         opa7ImpExp                  SC_Property *ProvideProperty (int64 client_handle, SC_Property &top_scprop, logical path_opt, PIACC accmode=PI_undefined, logical copy_selection=YES );
public     :                                     logical RegisterHandle ( );
public     :         opa7ImpExp                  logical ReleaseOperation (SC_Operation *sc_operation );
public     :         opa7ImpExp                  logical ReleaseProperty (SC_Property *sc_property );
public     :         opa7ImpExp                  logical Remove ( );
public     :                                     void RemoveOperation (SC_Operation *sc_operation );
public     : virtual                             logical ReopenProperty (char *propnames );
public     :         opa7ImpExp                                          SC_Property (SC_Property *sc_property, int64 client_handle );
public     :         opa7ImpExp                                          SC_Property (SC_DBObject *sc_dbobject, int64 client_handle );
public     :                                     logical SetBaseNode (SC_Property *sc_property );
public     :                                     logical UnregisterHandle ( );
public     : virtual opa7ImpExp                                          ~SC_Property ( );
};

#pragma pack()
#endif
