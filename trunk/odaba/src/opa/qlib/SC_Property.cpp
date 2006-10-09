/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    SC_Property

\brief    Server property handles


\date     $Date: 2006/07/31 16:28:08,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_Property"

#include  <popa7.h>
#ifndef   DLL_SC_Operation_HPP
#define   DLL_SC_Operation_HPP
#include  <sSC_Operation.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_SC_Property_HPP
#define   DLL_SC_Property_HPP
#include  <sSC_Property.hpp>
#include  <sDLL.h>
#endif
#include  <sCSInstanceList.hpp>
#include  <sSC_DBObject.hpp>
#include  <sSC_Handle.hpp>
#include  <sSC_Operation.hpp>
#include  <sSC_Property.hpp>
#include  <sbnode.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <sSC_Property.hpp>


/******************************************************************************/
/**
\brief  CheckInstance - 



\return term - Termination code

\param  synch_cur - 
\param  synch_loid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckInstance"

logical SC_Property :: CheckInstance (int32 synch_cur, int32 synch_loid )
{
  logical                 term = NO;
BEGINSEQ
  if ( !high_property )                              LEAVESEQ

  ValidateNode(YES);
  GetNode()->SynchInstance(synch_cur,synch_loid);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckSKey - 



\return keysmcb - 

\param  keynames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckSKey"

smcb *SC_Property :: CheckSKey (char *keynames )
{
  char         string[ID_SIZE+1];
  smcb        *keysmcb = NULL;
  if ( !(keysmcb = GetSortKeySMCB()) &&
       !(keysmcb = GetKeySMCB())        )            SDBSET(71)
       
  if ( strcmp(gvtxbts(string,keysmcb->smcbname,ID_SIZE),keynames) )
                                                     SDBSET(513)

  return(keysmcb);
}

/******************************************************************************/
/**
\brief  FillInstBuffer - 



\return term - Termination code

\param  result - 
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillInstBuffer"

logical SC_Property :: FillInstBuffer (CSInstanceList *result, int32 count )
{
  int                     curi = 0;
  logical                 conversion = result->get_conversion();
  CSInstanceList          inst_list(64,conversion,8096);
  logical                 term = NO;
  result->Reset();
  
  result->get_inst_area().Fill(count,conversion,YES);  
  
  while ( GetBufferInstance(curi++) )
  {
    FillInstResult(&inst_list,NO);
    result->get_inst_area().Fill(inst_list.get_inst_area().GetData(),
                                 inst_list.get_inst_area().GetCurSize(),
                                 conversion,YES); 
  }

  result->Terminate();
  return(term);
}

/******************************************************************************/
/**
\brief  FillInstResult - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  result - 
\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillInstResult"

logical SC_Property :: FillInstResult (CSInstanceList *result, logical error_case )
{
  DBStructDef  *strdef;
BEGINSEQ
  if ( error_case )                                  ERROR
  if ( !(strdef = GetCurrentTypeDef()) )             SDBERR(99)
    
  result->Fill(error_case,                               // term
               (void *)GetArea(),strdef,                 // instance
                                                         // strnames
               GetCurrentSize(),                         // instance length
               GetID(),                                  // objid
//             GetCurrentIndex(),                        // curidx
               GetNode()->get_nodecur(),                 // curidx
               GetRelativeIndex(NO),                     // relative_index
               NoWrite(),                                // no_write
               GetSortKeySMCB(),                         // sortkey name
               IsNewInstance(),                          // new instance
               InstanceInserted(),                       // inserted instance
               HasParentChanged(),                       // parent changed
               GetVersion(),                             // version_nr
               IsInitInstance()              );          // is initialized instance

// retrieved by CNode::Inst_setup()
RECOVER
  result->Fill(error_case);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  result - 
\param  inst_data - 
\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillInstResult"

logical SC_Property :: FillInstResult (CSInstanceList *result, char *inst_data, logical error_case )
{
  DBStructDef  *strdef;
BEGINSEQ
  if ( error_case )                                  ERROR
  if ( !(strdef = GetCurrentTypeDef()) )             SDBERR(99)
    
  result->Fill(error_case,                            // term
               (void *)inst_data,strdef,              // instance
                                                      // strnames
               GetCurrentSize() );                    // instance length
               

// retrieved by PropertyHandle::Inst_setup()
RECOVER
  result->Fill(error_case);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  FillKeyResult - 



\return term - Termination code

\param  result - 
\param  keyptr - 
\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillKeyResult"

logical SC_Property :: FillKeyResult (CSInstanceList *result, char *keyptr, logical error_case )
{
  smcb        *keysmcb;
BEGINSEQ
  if ( error_case )                                  ERROR
    
  if ( !(keysmcb = GetSortKeySMCB()) &&
       !(keysmcb = GetKeySMCB())         )           SDBERR(71)
    
  result->Fill(error_case,                                // term
               keyptr,keysmcb,                            // key
                                                          // keynames
               GetID(),                                   // objid
               GetCurrentIndex() );                       // curidx

// retrieved by PropertyHandle::InstKey_setup()
RECOVER
  result->Fill(error_case);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  FillOpenResult - 



\return term - Termination code

\param  result - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillOpenResult"

logical SC_Property :: FillOpenResult (CSInstanceList *result )
{

BEGINSEQ
  if ( !this )                                       ERROR

  result->Fill((logical)NO,                          // term
               GetFieldDef(),
               GetSortKeySMCB());                    // skey_names

RECOVER
  result->Fill((logical)YES);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  FillOpenViewResult - 



\return term - Termination code

\param  result - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillOpenViewResult"

logical SC_Property :: FillOpenViewResult (CSInstanceList *result )
{

BEGINSEQ
  if ( !this )                                       ERROR

  result->Fill(GetCurrentType());                    // strname

RECOVER
  result->Fill((logical)YES);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ForceClose - Force property close




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ForceClose"

void SC_Property :: ForceClose ( )
{
  SC_Property    *sc_dbprop;
  SC_Operation   *sc_oper;
  while ( sc_dbprop = properties->GetTail() )
  {
    sc_dbprop->ForceClose();
    ReleaseProperty(sc_dbprop);
  }

  while ( sc_oper = operations->GetTail() )
  {
    sc_oper->ForceClose();
    ReleaseOperation(sc_oper);
  }
  MSG_Closed();


}

/******************************************************************************/
/**
\brief  GetBaseProperty - Provide property handle for base pi



\return sc_property - 

\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseProperty"

SC_Property *SC_Property :: GetBaseProperty (int64 client_handle )
{
  SC_Property *sc_prop = NULL;
  DBField      temp_field;
BEGINSEQ
  if ( !this )                                       ERROR
  
  sc_prop = new SC_Property(this,client_handle);
  sc_prop->base_collection = YES;
  
  if ( sc_prop->OpenProperty(NULL) )                 ERROR
  
  properties->AddTail(sc_prop);
RECOVER
  delete sc_prop;
  sc_prop = NULL;
ENDSEQ
  return(sc_prop);
}

/******************************************************************************/
/**
\brief  GetName - 



\return resource_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *SC_Property :: GetName ( )
{
  DBFieldDef       *field_def;
  char              resource_name[ID_SIZE+1];
  char             *result = NULL;
  if ( field_def = GetDescription() )
  {
    gvtxbts(resource_name,field_def->fmcbname,ID_SIZE);
    get_nodeptr()->set_result_string(resource_name,UNDEF);
    result = get_nodeptr()->get_nstring();
  }

  return(result);
}

/******************************************************************************/
/**
\brief  GetTypeName - 



\return resource_type - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeName"

char *SC_Property :: GetTypeName ( )
{

  return ( "PropertyHandle" ); 


}

/******************************************************************************/
/**
\brief  Get_SC_DBObject - 



\return sc_dbo - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_SC_DBObject"

SC_DBObject *SC_Property :: Get_SC_DBObject ( )
{
  SC_Property   *sc_prop = this;
  SC_DBObject   *sc_dbo  = NULL;
  while ( sc_prop->get_high_property() )
    sc_prop = sc_prop->get_high_property();

  sc_dbo = (SC_DBObject *)sc_prop->get_parent();

  return(sc_dbo);
}

/******************************************************************************/
/**
\brief  Get_idkeyarea - 



\return datarea - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_idkeyarea"

char *SC_Property :: Get_idkeyarea ( )
{

  return ( (char *)idkeyarea.Resize(GetKeyLength()) );


}

/******************************************************************************/
/**
\brief  Get_instarea - 



\return datarea - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_instarea"

CSInstance &SC_Property :: Get_instarea ( )
{

  return ( instarea ); // Resize erfolgt durch den Benutzer
                       // z.B. beim Konvertieren CSInstance::GetInstance


}

/******************************************************************************/
/**
\brief  Get_skeyarea - 



\return datarea - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_skeyarea"

char *SC_Property :: Get_skeyarea ( )
{

  return ( (char *)skeyarea.Resize(GetSortKeyLength()) );


}

/******************************************************************************/
/**
\brief  HasParentChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasParentChanged"

logical SC_Property :: HasParentChanged ( )
{
  node            *nodptr;
  return (   (nodptr = GetNode()->get_nodenode()) &&
             nodptr->stscsav()                    && 
             (nodptr->get_nodeinst() && nodptr->get_nodeinst()->stscsav())
           ? YES : NO );

// weil: nach first Add zu nicht updatef. Ref muss uebergeordnete 
// Instanze gesichert werden

}

/******************************************************************************/
/**
\brief  OpenProperty - 



\return term - Termination code

\param  propnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenProperty"

logical SC_Property :: OpenProperty (char *propnames )
{
  logical      term = NO;
BEGINSEQ
  if ( base_collection )
  {
    if ( Open(((PropertyHandle *)high_property)->GetBaseProperty()) )
                                                     ERROR
  }
  else
    if ( propnames ? OpenAccessPath(*high_property,propnames,NULL,NO) 
                   : Open(*high_property)                         )
                                                     ERROR
  if ( !nodeptr )                                    ERROR
  origin = nodeptr->GetOrigin();
  transient_collection = !base_collection && IsTransient() && IsCollection();
  
  if ( high_property )
    parent_instance = high_property->GetArea();


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideOperation - Provide server operation



\return operation - 

\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideOperation"

SC_Operation *SC_Property :: ProvideOperation (int64 client_handle )
{
  SC_Operation *sc_oper = NULL;
BEGINSEQ
  SDBRESET
  
  if ( !this )                                       ERROR
  
  sc_oper = new SC_Operation(this,client_handle);
  operations->AddTail(sc_oper);
RECOVER
  delete sc_oper;
  sc_oper = NULL;
ENDSEQ
  return(sc_oper);
}

/******************************************************************************/
/**
\brief  ProvideProperty - 



\return sc_property - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  client_handle - 
\param  propnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProperty"

SC_Property *SC_Property :: ProvideProperty (int64 client_handle, char *propnames )
{
  SC_Property *sc_prop = NULL;
  DBField      temp_field;
BEGINSEQ
  if ( !this )                                       ERROR
  
  sc_prop = new SC_Property(this,client_handle);
  
  if ( sc_prop->OpenProperty(propnames) )            ERROR
    
  properties->AddTail(sc_prop);
/* 
  so werden die CopyNodes nicht als geschlossen registriert, da sie eine Ebene zu hoch hängen. 
  Sollte diese variante gewählt werden, müssen wir das ForceClose ggf. über die SC_Handle hierarchie machen.
  if ( propnames )
    properties->AddTail(sc_prop);
  else
  {
    if ( high_property )
    {
      sc_prop->high_property = high_property;
      high_property->get_properties()->AddTail(sc_prop);
    }
    else
    {
      sc_prop->high_property = NULL;
      ((SC_DBObject *)parent)->get_properties()->AddTail(sc_prop);
    }

  }
*/    

RECOVER
  delete sc_prop;
  sc_prop = NULL;
ENDSEQ
  return(sc_prop);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  client_handle - 
\param  operation_rule - 
\param  op_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProperty"

SC_Property *SC_Property :: ProvideProperty (int64 client_handle, char *operation_rule, ST_OpCodes op_type )
{
  SC_Property            *sc_prop = NULL;
  DBField                 temp_field;
BEGINSEQ
  if ( !this )                                       ERROR
  
  sc_prop = new SC_Property(this,client_handle);
  
  if ( sc_prop->Open(*this,op_type,operation_rule) ) ERROR
    
  properties->AddTail(sc_prop);

RECOVER
  delete sc_prop;
  sc_prop = NULL;
ENDSEQ
  return(sc_prop);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  client_handle - 
\param  top_scprop - 
\param  path_opt - 
\param  accmode - 
\param  copy_selection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProperty"

SC_Property *SC_Property :: ProvideProperty (int64 client_handle, SC_Property &top_scprop, logical path_opt, PIACC accmode, logical copy_selection )
{
  SC_Property            *sc_prop = NULL;

BEGINSEQ
  if ( !this )                                       ERROR
  
  sc_prop = new SC_Property(this,client_handle);
  
  if ( sc_prop->OpenHierarchy(this,&top_scprop,path_opt,accmode,copy_selection) )        
                                                     ERROR
  properties->AddTail(sc_prop);

RECOVER
  delete sc_prop;
  sc_prop = NULL;
ENDSEQ
  return(sc_prop);
}

/******************************************************************************/
/**
\brief  RegisterHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterHandle"

logical SC_Property :: RegisterHandle ( )
{

  get_nodeptr()->GetNode()->RegisterHandle(this);
  return(NO);
}

/******************************************************************************/
/**
\brief  ReleaseOperation - 



\return term - Termination code

\param  sc_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseOperation"

logical SC_Property :: ReleaseOperation (SC_Operation *sc_operation )
{
  logical                 term = NO;
BEGINSEQ
  if ( !sc_operation )                                ERROR
    
  delete sc_operation;    // entfernt sich selbst aus der Liste
  sc_operation = NULL;
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

logical SC_Property :: ReleaseProperty (SC_Property *sc_property )
{
  logical                 term = NO;
BEGINSEQ
  if ( !sc_property )                                ERROR
    
  if ( properties )
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
\brief  Remove - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical SC_Property :: Remove ( )
{
  logical                 term = NO;
  if ( this )
  {
    if ( high_property )
      term = ((SC_Property *)parent)->ReleaseProperty(this);
    else
      term = ((SC_DBObject *)parent)->ReleaseProperty(this);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveOperation - Remove operation from List




\param  sc_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveOperation"

void SC_Property :: RemoveOperation (SC_Operation *sc_operation )
{

  if ( operations->Find(sc_operation) )
    operations->RemoveAt();


}

/******************************************************************************/
/**
\brief  ReopenProperty - Reopen property handle



\return term - Termination code

\param  propnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReopenProperty"

logical SC_Property :: ReopenProperty (char *propnames )
{
  logical      term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  Close();
  
  if ( OpenProperty(propnames) )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SC_Property - Constructor



-------------------------------------------------------------------------------
\brief  i0 - 



\param  sc_property - 
\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Property"

     SC_Property :: SC_Property (SC_Property *sc_property, int64 client_handle )
                     : SC_Handle (sc_property->get_csconnection(),
           sc_property,client_handle),
PropertyHandle (),
  properties(new DLL(SC_Property)),
  high_property(sc_property),
  operations(new DLL(SC_Operation)),
  parent_instance(sc_property->GetArea()),
  origin(NULL),
  base_collection(NO),
  transient_collection(NO)
{

  SetServerPointer(this);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  sc_dbobject - 
\param  client_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_Property"

     SC_Property :: SC_Property (SC_DBObject *sc_dbobject, int64 client_handle )
                     : SC_Handle (sc_dbobject->get_csconnection(),
           sc_dbobject,client_handle),
PropertyHandle (),
  properties(new DLL(SC_Property)),
  high_property(NULL),
  operations(new DLL(SC_Operation)),
  parent_instance(NULL),
  origin(NULL),
  base_collection(NO),
  transient_collection(NO)
{

  SetServerPointer(this);

}

/******************************************************************************/
/**
\brief  SetBaseNode - 



\return term - Termination code

\param  sc_property - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBaseNode"

logical SC_Property :: SetBaseNode (SC_Property *sc_property )
{
  logical                 term = NO;
BEGINSEQ
  if ( !get_nodeptr() || !sc_property->get_nodeptr() )    ERROR

  term = getBnodeptr->SetBaseNode(*sc_property);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnregisterHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterHandle"

logical SC_Property :: UnregisterHandle ( )
{

  if ( get_nodeptr() )
    get_nodeptr()->GetNode()->UnregisterHandle();
  return(NO);
}

/******************************************************************************/
/**
\brief  ~SC_Property - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_Property"

     SC_Property :: ~SC_Property ( )
{

  ForceClose();
  
  delete operations;
  operations = NULL;
  
  delete properties;
  properties = NULL;

}


