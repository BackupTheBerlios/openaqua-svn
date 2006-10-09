/********************************* Class Source Code ***************************/
/**
\package  OPA
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

\date     $Date: 2006/05/01 16:10:44,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_DBBase"

#include  <popa7.h>
#include  <coctp.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sCTX_DataBase.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBResource.hpp>
#include  <sPropertyHandle.hpp>
#include  <sUCA_Action.hpp>
#include  <sCTX_DBBase.hpp>


/******************************************************************************/
/**
\brief  CTX_DBBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_DBBase"

     CTX_DBBase :: CTX_DBBase ( )
                     : CTX_Base (),
  resource(NULL),
  evt_context(NULL)
{
  intern_states.display_state = DSP_Visible;

}

/******************************************************************************/
/**
\brief  CheckPermission - Check permission
        The  function  checks  whether  the  user/application has permission for
        running  the action  passed to  the function.  The function returns true
        (YES) when the application has permissions for calling the action. 
        Permissions  are defined in the project  or database context and must be
        initialized when permission check is to be supported.

\return term - Termination code

\param  actptr - Action pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPermission"

logical CTX_DBBase :: CheckPermission (UCA_Action *actptr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  DBBeforeRead - Before read event handler
        The  before  read  event  handler  is  called before reading an instance
        (DBP_Read event). 
        At  the  time,  when  the  handler  is  called,  the instance is already
        selected  in  the  property  handle.  Key  data  for  the sort key (when
        defined)  is available and can be copied  to the instance area using the
        SetKey()  structure  context  function  or  can be provided by using the
        GetKey() context function. 
        The  handler  can  be  used  to optimize read access by returning YES or
        marking  an instance as 'hidden' (HideInstance()), when an instance with
        the given key should not be provided.
        The  handler  can  be  overloaded in specialized structure context class
        (CTX_Structure) implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBBeforeRead"

logical CTX_DBBase :: DBBeforeRead ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBClose - Close event
        The  function reacts on the DBO_Close event,  i.e. it is called when the
        context  is  going  to  be  closed.  In  this phase all resources of the
        context are still accessible.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBClose"

logical CTX_DBBase :: DBClose ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBCreate - Before create handler
        The  before create handler is called before creating a new data instance
        (DBP_Create event). 
        The  before  create  handler  can  deny  creating  the  data instance by
        returning YES.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical CTX_DBBase :: DBCreate ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBCreated - After create handler
        The  after  create  handler  is  called  when  a  data instance has been
        cretaed.  (DBO_Created  event).  The  handler  can  be  overloaded  in 
        specialized context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical CTX_DBBase :: DBCreated ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBDelete - Before delete handler
        The  before  delete  handler  is  called before deleting a data instance
        (DBP_Delete event). 
        The  before  delete  handler  can  deny  deleting  the  data instance by
        returning YES.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBDelete"

logical CTX_DBBase :: DBDelete ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBDeleted - After delete handler
        The  after  delete  handler  is  called  when  a  data instance has been
        deleted.  (DBO_Deleted  event).  The  handler  can  be  overloaded  in 
        specialized context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBDeleted"

logical CTX_DBBase :: DBDeleted ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBInitialize - Initialize handler
        The  initialize  handler  is  called  when  a  data  instance  has  been
        initializes  (DBO_Initialized  event).  When  the  handler is called the
        instance  is  not  yet  selected  in  the  property  handle. Hence, only
        attributes  can be  accessed in  the instance  in this phase. References
        and relationships are not accessable.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInitialize"

logical CTX_DBBase :: DBInitialize ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBInsert - Before insert handler
        The  before insert handler is called  before insering a data instance in
        a  collection  (DBP_Insert  event).  When  the  handler  is  called  the
        instance  to be  inserted in  the collection  is not yet selected in the
        property  handle. Hence, only attributes can be accessed in the instance
        in this phase. References and relationships are not accessable.
        The  before  insert  handler  can  deny  creating  the  data instance by
        returning YES.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInsert"

logical CTX_DBBase :: DBInsert ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBInserted - After inserted handler
        The  after  inserted  handler  is  called  when a data instance has been
        inserted  in  a  collection  (DBO_Inserted event). In contrast to create
        insert  means only that  an instance has  been added to a collection but
        it need not to be a newly created instance. 
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInserted"

logical CTX_DBBase :: DBInserted ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBModify - Modify handler
        The  modify handler  is called  when a  modification is signaled for the
        instance  (DBP_Modify event). This may happen before or after performing
        the modification. new data instance. 
        The  before  create  handler  can  deny  creating  the  data instance by
        returning YES.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.  When  handling  the  modify  event no values should be
        assigned  to the instance  of the property  handle since this will cause
        another  modification  event  and  thus,  a  recursive call of the event
        handler.  You can prevent recursion by setting a user state and checking
        it  always when entering  the modify event  handler. The state should be
        reset at least in the stored handler to handle new modify events.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBModify"

logical CTX_DBBase :: DBModify ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBNotCreated - Not created handler
        The  not  created  handler  is  called when a data instance could not be
        cretaed  because of an error (DBO_NotCreated  event). The handler can be
        overloaded in specialized context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBNotCreated"

logical CTX_DBBase :: DBNotCreated ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBNotDeleted - Not deleted handler
        The  not  deleted  handler  is  called when a data instance could not be
        deleted  because of an error (DBO_NotDeleted  event). The handler can be
        overloaded in specialized context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBNotDeleted"

logical CTX_DBBase :: DBNotDeleted ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBNotInserted - Not inserted handler
        The  not inserted  handler is  called when  a data instance could not be
        inserted  because of  an error  (DBO_NotInserted event). The handler can
        be overloaded in specialized context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBNotInserted"

logical CTX_DBBase :: DBNotInserted ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBNotOpened - Not opened handler
        The  not opened  handler is  called when  the context could not be oened
        because  of  an  error  (DBO_NotOpened  event).  The  handler  can  be 
        overloaded in specialized context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBNotOpened"

logical CTX_DBBase :: DBNotOpened ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBNotRemoved - Not removed handler
        The  not  removed  handler  is  called when a data instance could not be
        removed  from a  collection because  of an error (DBO_NotRemoved event).
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBNotRemoved"

logical CTX_DBBase :: DBNotRemoved ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBOpen - Before open handler
        The  before open  handler is  called when  opening the context (DBP_Open
        event). 
        The  before  delete  handler  can  deny opening the context by returning
        YES. In this case the cantext has the process state PRC_NotOpened. 
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpen"

logical CTX_DBBase :: DBOpen ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBOpened - After Open handler
        The  function  is  called  when  the  context  has been opened (DBOpened
        event).  The  handler  can  be  overloaded  in  the  specific context to
        perform  necessary actions after opening the  context. In this phase all
        resources of the context are already accessible.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical CTX_DBBase :: DBOpened ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBRead - After read event
        The  after  delete  handler  is  called  when  a  data instance has been
        deleted.  (DBO_Read event). This handler is typically used to initialize
        transient  attributes  and  references  in  the  instance  or  to select
        propert settings for generic attributes. 
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical CTX_DBBase :: DBRead ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBRefresh - Refresh handler
        The  refresh handler  is signaled  by the  application when submitting a
        refresh  request to a property  handle (DBO_Refresh event). This handler
        is  typically used to initialize transient attributes and references for
        the property handle or to re-calculate derived values.  
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRefresh"

logical CTX_DBBase :: DBRefresh ( )
{

  return(NO);
}

/******************************************************************************/
/**
\brief  DBRemove - Before remove handler
        The  before  remove  handler  is  called before removing a data instance
        from a collection (DBP_Remove event). 
        The  before  insert  handler  can  deny  creating  the  data instance by
        returning YES.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRemove"

logical CTX_DBBase :: DBRemove ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBRemoved - After remove handler
        The  after  remove  handler  is  called  when  a  data instance has been
        removed  from  a  collection  (DBO_Removed event). In contrast to delete
        remove  means only that  an instance has  been removed from a collection
        but  not necessarily deleted as instance. When the handler is called the
        instance  removed  from  the  collection  is not anymore selected in the
        property handle and thus, not accessible.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRemoved"

logical CTX_DBBase :: DBRemoved ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBReset

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBReset"

logical CTX_DBBase :: DBReset ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBSelect

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBSelect"

logical CTX_DBBase :: DBSelect ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBStore - Before stor handler
        The  before  store  handler  is  called  before  storing  data  to  the 
        transaction  or  database  (DBP_Store  event).  The  event  handler  is 
        typically  used  to  perform  application  consistency  checks  for  the
        instance.  Since in this phase all indices have already been updated and
        consistency  checks  have  been  finished  key  components  must  not be
        updated.  When  changing  sub-ordinated  instances  in  this handler the
        modifications  should  be  saved  explicitely.  Otherwise,  they are not
        stored  in  the  same  transaction  and  may  cause  problems  when  the
        transaction fails.
        The  before  store  handler  can  deny  creating  the  data  instance by
        returning YES.
        The   handler   can   be   overloaded   in   specialized   context class
        implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStore"

logical CTX_DBBase :: DBStore ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DBStored - After strore handler
        The  after store handler is called when  a data instance has been stored
        (DBO_Stored  event).  The  handler  can  be  overloaded  in  specialized
        context class implementations.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStored"

logical CTX_DBBase :: DBStored ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ExecuteAction - Execute action
        The  function allows executing  an action with  the action name and type
        passed  to the  function or  an event.  The function returns whether the
        action  could be  exuted faormally.  The action  result can be retrieved
        with the function GetActionResult().

\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

logical CTX_DBBase :: ExecuteAction (DB_Event intevent )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  switch ( intevent )
  {
    case DBO_Opened     : term = DBOpened();         break;
    case DBO_Initialize : term = DBInitialize();     break;
    case DBO_Created    : if ( !(term = DBCreated()) )
                            intern_states.data_state = DAT_Filled; 
			  break;
    case DBO_NotCreated : term = DBNotCreated();     break;
    case DBO_Read       : if ( !(term = DBRead()) )
                            intern_states.data_state = DAT_Filled; 
			  break;
    case DBO_Reset      : term = DBReset();          break;
    case DBO_Stored     : term = DBStored();         break;
    case DBO_Inserted   : if ( !(term = DBInserted()) )
                            intern_states.data_state = DAT_Filled; 
			  break;
    case DBO_NotInserted: term = DBNotInserted();    break;
    case DBO_Removed    : term = DBRemoved();        break;
    case DBO_NotRemoved : term = DBNotRemoved();     break;
    case DBO_Deleted    : term = DBDeleted();        break;
    case DBO_NotDeleted : term = DBNotDeleted();     break;
    case DBO_Refresh    : term = DBRefresh();        break;
    case DBO_NotOpened  : term = DBNotOpened();      break;
    case DBO_Close      : term = DBClose();          break;
    
    case DBP_Read       : term = DBBeforeRead();     break;
    case DBP_Create     : term = DBCreate();         break;
    case DBP_Modify     : term = DBModify();         break;
    case DBP_Store      : term = DBStore();          break;
    case DBP_Insert     : term = DBInsert();         break;
    case DBP_Open       : term = DBOpen();           break;
    case DBP_Remove     : term = DBRemove();         break;
    case DBP_Delete     : term = DBDelete();         break;
    case DBP_Select     : term = DBSelect();         break;
    
    case DB_undefined   :                            LEAVESEQ
    default             : ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDBField - 


\return property_hdl

\param  fldname_w - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBField"

PropertyHandle CTX_DBBase :: GetDBField (char *fldname_w )
{
  return PropertyHandle();
}

/******************************************************************************/
/**
\brief  GetDatabaseContext - 


\return db_context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDatabaseContext"

CTX_DataBase *CTX_DBBase :: GetDatabaseContext ( )
{
  CTX_DBBase  *ctx_ptr = this;

  while ( ctx_ptr = ctx_ptr->HighDBContext() )
    if ( ctx_ptr->GetContextType() == CTXT_Database )
      break;
  return((CTX_DataBase *)ctx_ptr);
}

/******************************************************************************/
/**
\brief  GetPropContext - Get Property context
        The  function returns  the property  context for  the property passed as
        name or property path. When

\return propctx - 

\param  w_fldnames - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropContext"

CTX_Property *CTX_DBBase :: GetPropContext (char *w_fldnames )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetPropertyHandle - Get Property handle
        The  function returns the  property handle associated  with the data for
        the  context.  The  function  cannot  be called for database or database
        object  context, since the data associated  with those context cannot be
        described by means of a property handle.
        When  a  property  name  is  passed  to  the  function  the subordinated
        property  handle for the  context property handle  is returned. The name
        passed  to  the  function  must  be  a  valid  property  name  in  the 
        structure/class defined for the context property.

\return property_handle

\param  fldname_w - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CTX_DBBase :: GetPropertyHandle (char *fldname_w )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetStructContext - 


\return strctx - Structure Context

\param  w_strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructContext"

CTX_Structure *CTX_DBBase :: GetStructContext (char *w_strnames )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetSysDict - Get system dictionary
        The  function returns the system dictionary for the database opened. The
        system dictionary contains the model definitions for the metadata.

\return dict_hdl - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSysDict"

DictionaryHandle &CTX_DBBase :: GetSysDict ( )
{

  return ( GetSystemDictionary() );

}

/******************************************************************************/
/**
\brief  HighDBContext - Get next higher database context
        The  function  returns  the  next  upper  context  with the context type
        and/or resource name passed to the function.

\return ctxdbptr
/******************************************************************************/
/**
\brief  i0


\param  ctxtype - Context type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HighDBContext"

CTX_DBBase *CTX_DBBase :: HighDBContext (CTX_Types ctxtype )
{

  return ( this && high_ctx && (ctxtype == CTXT_undefined || high_ctx->GetContextType() == ctxtype) 
           ? (CTX_DBBase *)high_ctx : NULL);


}

/******************************************************************************/
/**
\brief  i1


\param  resname - Resource name
\param  ctxtype - Context type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HighDBContext"

CTX_DBBase *CTX_DBBase :: HighDBContext (char *resname, CTX_Types ctxtype )
{
  CTX_DBBase  *ctx_ptr = this;
  char         name[ID_SIZE];

  gvtxstb(name,resname,ID_SIZE);
  while ( ctx_ptr = ctx_ptr->HighDBContext() )
    if ( !memcmp(name,ctx_ptr->GetResourceName(),ID_SIZE) )
      if ( ctxtype == CTXT_undefined || ctx_ptr->GetContextType() == ctxtype )
        break;
  return(ctx_ptr);

}

/******************************************************************************/
/**
\brief  Initialize - 



\param  res_ptr - 
\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CTX_DBBase :: Initialize (DBResource *res_ptr, CTX_Base *highctx )
{

  CTX_Base::Initialize(highctx);
  resource = res_ptr;

}

/******************************************************************************/
/**
\brief  IsUserHandle - Is property handle user defined
        Besides  property handles  constructed  or  opened by the application, a
        number  of  property  handles  are  constructed  for  internal purposes.
        Internal  property handles behave as  user-defined ones, i.e. they react
        on  events  and  context  functions  are  called,  when defined. In some
        cases,  this is  disturbing and  might lead  to infinit recursions. This
        function  allows  supressing  context  functions  for  internal property
        handles.

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUserHandle"

logical CTX_DBBase :: IsUserHandle ( )
{
  PropertyHandle      *ph = GetPropertyHandle();
  return(ph ? ph->IsUserHandle() : NO);

}

/******************************************************************************/
/**
\brief  Notify


\param  event_id - Ivend type
\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Notify"

void CTX_DBBase :: Notify (CSA_Events event_id, int32 objid )
{

BEGINSEQ
  switch ( event_id )
  {
    case CSA_undefined : ERROR 
                         break;
    case SE_Open       : 
    case CE_Open       : NotifyOpen(objid);
                         break;
    case SE_Opened     : 
    case CE_Opened     : NotifyOpened(objid);
                         break;
    case SE_Create     : 
    case CE_Create     : NotifyCreate(objid);
                         break;
    case SE_Update     : 
    case CE_Update     : NotifyUpdate(objid);
                         break;
    case SE_Insert     : 
    case CE_Insert     : NotifyInsert(objid);
                         break;
    case SE_Remove     : 
    case CE_Remove     : NotifyRemove(objid);
                         break;
    case SE_Delete     : 
    case CE_Delete     : NotifyDelete(objid);
                         break;
    case SE_Close      : 
    case CE_Close      : NotifyClose(objid);
                         break;
    case SE_Closed     : 
    case CE_Closed     : NotifyClosed(objid);
                         break;
    default            : SDBERR(99);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  NotifyClose


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyClose"

void CTX_DBBase :: NotifyClose (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyClosed


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyClosed"

void CTX_DBBase :: NotifyClosed (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyCreate - 



\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyCreate"

void CTX_DBBase :: NotifyCreate (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyDelete


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyDelete"

void CTX_DBBase :: NotifyDelete (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyInsert


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyInsert"

void CTX_DBBase :: NotifyInsert (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyOpen


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyOpen"

void CTX_DBBase :: NotifyOpen (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyOpened


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyOpened"

void CTX_DBBase :: NotifyOpened (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyRemove - 



\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyRemove"

void CTX_DBBase :: NotifyRemove (int32 objid )
{


}

/******************************************************************************/
/**
\brief  NotifyUpdate


\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotifyUpdate"

void CTX_DBBase :: NotifyUpdate (int32 objid )
{


}

/******************************************************************************/
/**
\brief  SetContextVariables - 


\return term - Termination code

\param  context_string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContextVariables"

logical CTX_DBBase :: SetContextVariables (char *context_string )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  SetTransactionError - Set trasaction error
        The  function marks a transaction as  errounus. This leads to a rollback
        of  the transaction when  the transaction is  finished. The function can
        be  called  in  post  handlers  (as  inserted  or  deleted)  to undo the
        performed operation.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransactionError"

void CTX_DBBase :: SetTransactionError ( )
{
}

/******************************************************************************/
/**
\brief  set_high_ctx - 



\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_high_ctx"

void CTX_DBBase :: set_high_ctx (CTX_DBBase *ctxptr )
{

  high_ctx = ctxptr;

}

/******************************************************************************/
/**
\brief  ~CTX_DBBase - Desctructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_DBBase"

     CTX_DBBase :: ~CTX_DBBase ( )
{

}


