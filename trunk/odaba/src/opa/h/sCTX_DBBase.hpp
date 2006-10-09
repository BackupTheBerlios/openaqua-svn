/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|08:31:01,84}|(REF)
\class    CTX_DBBase

\brief    Base class for data base contexts
          The   base   class   for   database   contexts   provides   some basic
          functionality  for data base context  classes. In particular the class
          provides  most of the default event handlers that can be overloaded in
          specific  context  classes.  Overloaded  handlers need not to call the
          default  handlers  since  nothing  is  done  in  the default handlers.
          Handlers  for  database  events  are  usually  called  within internal
          transactions.  Thus, all  modifications made  by the event handler are
          reset when the transaction fails.
          For  a number of database operations Not-events are generated that are
          called   in   case   of   an   error.   An   error could be a database
          (consistency)  error but  the process  event (before event) could have
          denied the operation as well.

\date     $Date: 2006/03/13 08:31:08,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_DBBase_HPP
#define   CTX_DBBase_HPP

class     CTX_DBBase;

class     CTX_DBBase;
class     CTX_DataBase;
class     CTX_Property;
class     CTX_Structure;
class     DBResource;
class     UCA_Action;
#include  <cDB_Event.h>
#include  <sCTX_Base.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  CTX_DBBase :public CTX_Base
{
protected  :         DBResource                                  *resource ATTR_ALIGN(4);                                    //
protected  :         CTX_DBBase                                  *evt_context;                                               //

public     :
                     DBResource                                  *get_resource() { return(resource); }
                     CTX_DBBase                                  *get_evt_context() { return(evt_context); }
public     :         opa7ImpExp                                          CTX_DBBase ( );
public     :         opa7ImpExp                  logical CheckPermission (UCA_Action *actptr );
public     : virtual opa7ImpExp                  logical DBBeforeRead ( );
public     : virtual opa7ImpExp                  logical DBClose ( );
public     : virtual opa7ImpExp                  logical DBCreate ( );
public     : virtual opa7ImpExp                  logical DBCreated ( );
public     : virtual opa7ImpExp                  logical DBDelete ( );
public     : virtual opa7ImpExp                  logical DBDeleted ( );
public     : virtual opa7ImpExp                  logical DBInitialize ( );
public     : virtual opa7ImpExp                  logical DBInsert ( );
public     : virtual opa7ImpExp                  logical DBInserted ( );
public     : virtual opa7ImpExp                  logical DBModify ( );
public     : virtual opa7ImpExp                  logical DBNotCreated ( );
public     : virtual opa7ImpExp                  logical DBNotDeleted ( );
public     : virtual opa7ImpExp                  logical DBNotInserted ( );
public     : virtual opa7ImpExp                  logical DBNotOpened ( );
public     : virtual opa7ImpExp                  logical DBNotRemoved ( );
public     : virtual opa7ImpExp                  logical DBOpen ( );
public     : virtual opa7ImpExp                  logical DBOpened ( );
public     : virtual opa7ImpExp                  logical DBRead ( );
public     : virtual opa7ImpExp                  logical DBRefresh ( );
public     : virtual opa7ImpExp                  logical DBRemove ( );
public     : virtual opa7ImpExp                  logical DBRemoved ( );
public     : virtual opa7ImpExp                  logical DBReset ( );
public     : virtual opa7ImpExp                  logical DBSelect ( );
public     : virtual opa7ImpExp                  logical DBStore ( );
public     : virtual opa7ImpExp                  logical DBStored ( );
public     :         opa7ImpExp                  logical ExecuteAction (DB_Event intevent );
public     : virtual opa7ImpExp                  PropertyHandle GetDBField (char *fldname_w=NULL );
public     :         opa7ImpExp                  CTX_DataBase *GetDatabaseContext ( );
public     : virtual opa7ImpExp                  CTX_Property *GetPropContext (char *w_fldnames=NULL );
public     : virtual opa7ImpExp                  PropertyHandle *GetPropertyHandle (char *fldname_w=NULL );
public     : virtual opa7ImpExp                  CTX_Structure *GetStructContext (char *w_strnames=NULL );
public     :         opa7ImpExp                  DictionaryHandle &GetSysDict ( );
public     :         opa7ImpExp                  CTX_DBBase *HighDBContext (CTX_Types ctxtype=CTXT_undefined );
public     :         opa7ImpExp                  CTX_DBBase *HighDBContext (char *resname, CTX_Types ctxtype=CTXT_undefined );
public     :                                     void Initialize (DBResource *res_ptr, CTX_Base *highctx );
public     :         opa7ImpExp                  logical IsUserHandle ( );
public     :                                     void Notify (CSA_Events event_id, int32 objid );
public     : virtual opa7ImpExp                  void NotifyClose (int32 objid );
public     : virtual opa7ImpExp                  void NotifyClosed (int32 objid );
public     : virtual opa7ImpExp                  void NotifyCreate (int32 objid );
public     : virtual opa7ImpExp                  void NotifyDelete (int32 objid );
public     : virtual opa7ImpExp                  void NotifyInsert (int32 objid );
public     : virtual opa7ImpExp                  void NotifyOpen (int32 objid );
public     : virtual opa7ImpExp                  void NotifyOpened (int32 objid );
public     : virtual opa7ImpExp                  void NotifyRemove (int32 objid );
public     : virtual opa7ImpExp                  void NotifyUpdate (int32 objid );
public     : virtual opa7ImpExp                  logical SetContextVariables (char *context_string );
public     : virtual opa7ImpExp                  void SetTransactionError ( );
public     :                                     void set_high_ctx (CTX_DBBase *ctxptr );
public     : virtual opa7ImpExp                                          ~CTX_DBBase ( );
public     :                                     void set_evt_context (CTX_DBBase *ctxptr ){

  evt_context = ctxptr;

}

};

#pragma pack()
#endif
