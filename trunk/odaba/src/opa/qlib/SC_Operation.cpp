/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    SC_Operation

\brief    Server operation
          This  class  runs  an  operation  on  the  server side and returns the
          result.

\date     $Date: 2006/04/05 23:11:48,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Operation"

#include  <popa7.h>
#include  <sCSInstanceList.hpp>
#include  <sParmList.hpp>
#include  <sSC_DBObject.hpp>
#include  <sSC_Property.hpp>
#include  <sbnode.hpp>
#include  <snode.hpp>
#include  <sSC_Operation.hpp>


/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical SC_Operation :: Close ( )
{
  logical                 term = NO;
  if ( this )
  {
    UnregisterHandle();
    PropertyHandle::Close();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - Execute operation


\return term - Termination code

\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical SC_Operation :: Execute (ParmList *parmlist )
{
  logical                 term = NO;
BEGINSEQ
  Close();
  
  if ( !Operation::IsDefined() )                     SDBERR(522)

  if ( Operation::Execute(parmlist) )                ERROR
    
  RegisterHandle();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillResult - Fill execute result



\param  result - 
\param  term - Termination code
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillResult"

void SC_Operation :: FillResult (CSInstanceList *result, logical term )
{
  char          string[ID_SIZE+1];
  DBFieldDef   *fielddef;
  CS_Handle    *cshandle = NULL;
  char         *prop_path;
  smcb         *sksmcb;
  logical       is_coll;
  logical       conversion = result->get_conversion();
BEGINSEQ
  if ( !this || term )                               ERROR

  fielddef  = GetDescription();
  prop_path = GetPropertyPath();
  
  if ( get_nodeptr() && get_nodeptr()->IsLocalNode() == YES )
    cshandle = getBnodeptr;
  
  if ( (is_coll = IsCollection(NO)) && cshandle && !cshandle->GetServerPointer() )
    cshandle->SetServerPointer(calling_property->Get_SC_DBObject()->ProvideProperty(0,prop_path,PI_Read));
  
  result->Reset();
  
  result->get_inst_area().Fill((logical)NO,conversion,YES);
                                                     // 0 - term
  result->get_inst_area().Fill((int32)(get_nodeptr() && fielddef ? get_nodeptr()->get_nodetype() : NT_undefined),conversion,YES);
                                                     // 1 - data_nodetype
  result->get_inst_area().Fill((CS_Handle *)((get_nodeptr() && get_nodeptr()->IsLocalNode() == YES) ? getBnodeptr : NULL),conversion,YES);   
                                                     // 2 - property handle
  if ( fielddef )
  {
    result->get_inst_area().Fill(is_coll = IsCollection(NO),conversion,YES);   
                                                     // 3 - is result a collection
    result->get_inst_area().Fill(prop_path,conversion,YES);   
                                                     // 4 - property path or extent
    result->get_inst_area().Fill(gvtxbts(string,fielddef->fmcbtype,ID_SIZE),conversion,YES);   
                                                     // 5 - structure name

// was, wenn das ergebnis eine eingestellte instanz in einer coll. ist?    
    
    if ( is_coll ) 
    {
      result->get_inst_area().Fill(GetParentProperty()->GetCurrentType(),conversion,YES);  
                                                     // 6 - context structure, kann NULL sein
      result->get_inst_area().Fill((sksmcb = GetSortKeySMCB()) ? gvtxbts(string,sksmcb->smcbname,ID_SIZE) : NULL,conversion,YES);   
                                                     // 7 - sort key names
      result->get_inst_area().Fill(fielddef->get_log_reference(),conversion,YES);
                                                     // 8 - temporary Extent
      result->get_inst_area().Fill(fielddef->get_weak_typed(),conversion,YES);
                                                     // 9 - is weak typed temporary extent
      result->get_inst_area().Fill(fielddef->get_owning(),conversion,YES);
                                                     // 10 - is temporary extent owner of the instances
    }
    else
    {
      result->get_inst_area().Fill((int32)fielddef->fmcbsize,conversion,YES);  
                                                     // 6 - size
      result->get_inst_area().Fill(fielddef->fmcbprec,conversion,YES);  
                                                     // 7 - precision
      result->get_inst_area().Fill(fielddef->fmcbdim,conversion,YES);  
                                                     // 8 - dimension
      result->get_inst_area().Fill(ProvideArea(),fielddef,conversion,YES);  
                                                     // 9 - instance 
    }
  }
  
  result->Terminate();

RECOVER
  result->Fill((logical)YES);

ENDSEQ

}

/******************************************************************************/
/**
\brief  ForceClose - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void SC_Operation :: ForceClose ( )
{

  MSG_Closed();

}

/******************************************************************************/
/**
\brief  GetName - 


\return resource_name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *SC_Operation :: GetName ( )
{

  return ( expression );

}

/******************************************************************************/
/**
\brief  GetTypeName - 


\return resource_type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *SC_Operation :: GetTypeName ( )
{

  return ( "OperationHandle" );

}

/******************************************************************************/
/**
\brief  ProvideExpression - 


\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExpression"

logical SC_Operation :: ProvideExpression (char *expression )
{
  logical    term = NO;
BEGINSEQ
  Operation::Remove();    // remove operation definition
  
// werder dictionary noch object ist zuwenig - muss von COperation kommen  
  if ( Operation::ProvExpression(NULL,NULL,NULL,expression) )
                                                     ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReopenProperty - Reopen operation handle


\return term - Termination code

\param  expression - Expression
\param  own_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReopenProperty"

logical SC_Operation :: ReopenProperty (char *expression, logical own_opt )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  
  Close();
  
  if ( expression )
    if ( ProvideExpression(expression) )             ERROR
  Execute(NULL);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SC_Operation - Konstruktor



\param  sc_property - 
\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Operation"

                        SC_Operation :: SC_Operation (SC_Property *sc_property, int64 client_handle )
                     : SC_Handle (sc_property->get_csconnection(),
           sc_property,client_handle),
Operation (),
  calling_property(sc_property)
{

  if ( sc_property )
    Open(*sc_property);

}

/******************************************************************************/
/**
\brief  ~SC_Operation - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Operation"

                        SC_Operation :: ~SC_Operation ( )
{

  ForceClose();
  
  calling_property->RemoveOperation(this); 
  
  Operation::Remove();    // remove operation definition
  Close();

}


