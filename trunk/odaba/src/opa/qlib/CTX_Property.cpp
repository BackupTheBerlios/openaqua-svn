/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CTX_Property

\brief    Property contexts
          Property  contexts  are  created  for extents, references, attributes,
          relationships  and  base  structures.  The  property  context  defines
          refers  to  the  property  instance  as  well  as  to  the  property 
          definition.  Moreover,  it  allows  determining  the  active  context 
          hierarchy  for  the  property,  i.e.  the  parent  structure/Database 
          Object,  the  property  the  parent  structure  is  accessed from, the
          parent  parent structure  etc. Thus,  the property context defines the
          context in which the property instance has been provided. 
          The  parent  context  for  a  property  context is a structure context
          (when  the  property  is  part  of  an  object instance) or a Database
          Object context (when the property is an extent. 
          The  property context allows handling read and update events, validity
          checks and insert and remove events.
          The  default  property  context  can  be  overloaded  by a application
          specific property context classes.

\date     $Date: 2006/07/31 13:27:28,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Property"

#include  <popa7.h>
#include  <coctp.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBFieldDef.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbinti.hpp>
#include  <sbnode.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sCTX_Property.hpp>


/******************************************************************************/
/**
\brief  CTX_Property - Property context constructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Property"

     CTX_Property :: CTX_Property ( )
                     : CTX_DBBase (),
  prop_node(NULL)
{



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

logical CTX_Property :: DBRefresh ( )
{
//  CTX_Structure      *strctx = GetStructContext();
//  return(strctx ? strctx->DBRefresh() : NO );  8.2.02: führt zum rekursiven Anlegen der intis
  return(NO);
}

/******************************************************************************/
/**
\brief  GetConnectionClient - 


\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient &CTX_Property :: GetConnectionClient ( )
{

  return (   this && prop_node 
           ? prop_node->GetConnectionClient()
           : GetMainClient() );

}

/******************************************************************************/
/**
\brief  GetContextType - Get Context type
        The function returns the specific context type as CTX_Property.

\return ctxtype - Context type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Property :: GetContextType ( )
{


  return(CTXT_Property);
}

/******************************************************************************/
/**
\brief  GetDBField - 


\return property_hdl - 

\param  fldname_w - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBField"

PropertyHandle CTX_Property :: GetDBField (char *fldname_w )
{
  PropertyHandle    *property_handle = NULL;

  property_handle = GetPropertyHandle(fldname_w);
    

  return(property_handle ? property_handle->get_nodeptr() 
                         : (node *)NULL);
}

/******************************************************************************/
/**
\brief  GetDefinition - 


\return flddefptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDefinition"

DBFieldDef *CTX_Property :: GetDefinition ( )
{

  return(this && prop_node ? ((bnode *)prop_node)->get_nodefield() : NULL);

}

/******************************************************************************/
/**
\brief  GetInstContext - Get Instance context
        The  function returns the  structure context for  the instance that owns
        the  current property (high  structure). This is  not identical with the
        structure  that owns the  property. The instance  owning the property is
        the  instance that is  stored in the  database. Hence, the function goes
        up  in the context  hirarchy until it  finds the context that referst to
        the instance stored in the database.

\return strctx - Structure Context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstContext"

CTX_Structure *CTX_Property :: GetInstContext ( )
{
  node                   *nodeptr;
  CTX_Structure          *strctx = NULL;
BEGINSEQ
  if ( !prop_node || !(nodeptr = prop_node->get_nodenode()) )
                                                     ERROR
  if ( !nodeptr->get_nodeinst() )
    nodeptr->Check(YES,NO);
  if ( !nodeptr->get_nodeinst() )                    ERROR
    
  strctx = nodeptr->get_nodeinst()->GetContext();

RECOVER
  strctx = NULL;
ENDSEQ
  return(strctx);
}

/******************************************************************************/
/**
\brief  GetPropContext - Get Property context
        The  function returns  the property  context for  the property passed as
        name  or property path.  The property is  searched in the structure that
        owns the current property.

\return propctx - 

\param  w_fldnames - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropContext"

CTX_Property *CTX_Property :: GetPropContext (char *w_fldnames )
{
  CTX_Structure *strctx  = (CTX_Structure *)HighDBContext(CTXT_Structure);

  return ( strctx ? strctx->GetPropContext(w_fldnames) : NULL );


}

/******************************************************************************/
/**
\brief  GetPropertyHandle - Get Property Handle
        The  function returns the  property handle associated  with the data for
        the  context.  The  function  cannot  be called for database or database
        object  contexts, since  the data  associated with those contexts cannot
        be described by means of a property handle.
        When  a  property  name  is  passed  to  the  function  the subordinated
        property  handle for the  context property handle  is returned. The name
        passed  to  the  function  must  be  a  valid  property  name  in  the 
        structure/class defined for the context property.

\return property_handle - 

\param  fldname_w - Property name or path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *CTX_Property :: GetPropertyHandle (char *fldname_w )
{
  PropertyHandle    *property_handle = NULL;
BEGINSEQ
  if ( !prop_node )                                  ERROR
    
  property_handle = (PropertyHandle *)&prop_node;
  if ( !fldname_w )                                  LEAVESEQ
    
  property_handle = property_handle->GetPropertyHandle(fldname_w);
  
  if ( !property_handle->IsValid(NO) )               ERROR
RECOVER
  property_handle = NULL;
ENDSEQ
  return(property_handle);
}

/******************************************************************************/
/**
\brief  GetResourceName - Get resource name
        The  function  returns  the  property  name as context specific resource
        name.

\return resname - Resource name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceName"

char *CTX_Property :: GetResourceName ( )
{

  return(prop_node ? ((bnode *)prop_node)->get_nodefield()->fmcbname : NULL);

}

/******************************************************************************/
/**
\brief  GetStructContext - Get structure context
        The  function returns  the structure  context for the currently selected
        instance  in the property handle.  For weak-typed properties the context
        may  change  with  the  selection  from  instance  to  instance. When no
        instance  is selected in the property handle associated with the context
        the function returns the instance context for the default instance.

\return strctx - Structure Context

\param  w_strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructContext"

CTX_Structure *CTX_Property :: GetStructContext (char *w_strnames )
{
  CTX_Structure          *strctx = NULL;
BEGINSEQ
  if ( !this || !prop_node )                         ERROR
    
  if ( !prop_node->get_nodeinst() )
    prop_node->Check(YES,NO);
  if ( !prop_node->get_nodeinst() )                  ERROR
    
  strctx = prop_node->get_nodeinst()->GetContext();

RECOVER
  strctx = NULL;
ENDSEQ
  return(strctx);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  bnode_ptr - 
\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CTX_Property :: Initialize (bnode *bnode_ptr, CTX_Base *highctx )
{

  if ( bnode_ptr && bnode_ptr->get_nodefield() )
    CTX_DBBase::Initialize(bnode_ptr->get_nodefield()->get_resource(),
                           highctx);  
  prop_node = bnode_ptr;

  if ( highctx && ((CTX_Structure *)highctx)->IsReadOnly() )
    intern_states.display_state = DSP_undefined;

}

/******************************************************************************/
/**
\brief  IsEdit - Can data be updated
        The function checks whether data can be updated in the property handle.

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEdit"

logical CTX_Property :: IsEdit ( )
{

  return(prop_node->IsWrite());


}

/******************************************************************************/
/**
\brief  IsReadOnly - Is read-only enabled
        The  function returns whether the read only  option has been set for the
        property.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical CTX_Property :: IsReadOnly ( )
{

  return( this ? intern_states.display_state != DSP_Visible : NO);

}

/******************************************************************************/
/**
\brief  MarkReadOnly - 



\param  readonly - Read-only state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MarkReadOnly"

void CTX_Property :: MarkReadOnly (logical readonly )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  switch ( readonly )
  {
    case NO  : intern_states.display_state = DSP_Visible;
               break; 
    case YES : intern_states.display_state = DSP_Disabled;
               break; 
    case 'S' : intern_states.display_state = DSP_undefined;
               break; 
    case 'R' : intern_states.display_state = DSP_Visible;
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetReadOnly - Set read only
        The  function  allows  setting  the  instance  selected  in the property
        handle  to read-only. This will prevent  the data in the property handle
        from  being  updated,  i.e.  you  cannot  add  or  delete  instances  to
        collection  properties  or  change  attribute  values  for  an attribute
        property.  SetReadOnly(YES) will  also mark  all sub-ordinated instances
        and  their property handles  as read-only. The  indication is reset when
        calling   SetReadOnly(NO).   Resetting   the   read-only   state   works
        hierarchical  as well  until subordinated  instances or property handles
        are  found, which  are explicitly  set to  read-only by the application,
        i.e.  SetReadOnly(NO) will not reset  read-only states explicitly set by
        the application.

\return term - Termination code

\param  readonly - Read-only state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

logical CTX_Property :: SetReadOnly (logical readonly )
{
  logical         term = NO;
  MarkReadOnly(readonly);
  term = prop_node->GetInstContext()->SetReadOnly(readonly);
  return(term);
}

/******************************************************************************/
/**
\brief  SetResult - Set value for action result
        Usually  it is not  possible to pass  an result from a context function.
        You  can, however,  return a  string list  which can be retrieved by the
        application  using  the  function  GetActionResult(). The result is also
        passed  from the server to  the client when the  action is executed on a
        server.


\param  result_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetResult"

void CTX_Property :: SetResult (char *result_string )
{

 ((PropertyHandle *)&prop_node)->SetActionResult(result_string);

}

/******************************************************************************/
/**
\brief  SetTransactionError - Set Transaction Error
        The  function marks a transaction as  errounus. This leads to a rollback
        of  the transaction when  the transaction is  finished. The function can
        be  called  in  post  handlers  (as  inserted  or  deleted)  to undo the
        performed operation.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransactionError"

void CTX_Property :: SetTransactionError ( )
{

BEGINSEQ
  if ( !prop_node )                                  LEAVESEQ
  
  prop_node->GetObjectHandle()->SetTransactionError();

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~CTX_Property - Destructor
        The  function  destroys  the  property  context.  The  function  must be
        overloaded  in  an  application  specific implementation of the property
        context.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Property"

     CTX_Property :: ~CTX_Property ( )
{
  PropertyHandle   *piptr = (PropertyHandle *)&prop_node;
  prop_node = NULL;

//  if ( prop_node )        nullt sich selbst. 18.9.00
//    prop_node->ResetPIRef(piptr);

}


