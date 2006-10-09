/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACViewProperty

\brief    


\date     $Date: 2006/03/12 19:16:20,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACViewProperty"

#include  <popa7.h>
#include  <sACOperation.hpp>
#include  <sACPath.hpp>
#include  <sBNFData.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDictionary.hpp>
#include  <sExpressionReference.hpp>
#include  <sFieldSource.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbinti.hpp>
#include  <snode.hpp>
#include  <sACViewProperty.hpp>


/******************************************************************************/
/**
\brief  ACViewProperty - 


-------------------------------------------------------------------------------
\brief i0


\param  nodeptr -
\param  dbfield_ptr - Property definition
\param  highctx -
\param  instptr -
\param  accopt - Access mode
\param  operenv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACViewProperty"

                        ACViewProperty :: ACViewProperty (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt, OperEnvironment *operenv )
                     : bnode (),
  target(),
  source(),
  expression(NULL),
  source_type(ADT_undefined),
  oper_env(operenv)
{
  char        string[41];
  nodetype = NT_ACViewProperty;

  object_ref= nodeptr->GetObjectHandle();
  nodenode  = nodeptr;
  nodefield = dbfield_ptr;
  nodeacc   = accopt;
  
  set_prop_path(gvtxbts(string,dbfield_ptr->fmcbname,ID_SIZE));

  if ( nodeptr->IsValid() )
    SetSource();
  SetTarget();

}

/******************************************************************************/
/**
\brief i01


\param  viewattr_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACViewProperty"

                        ACViewProperty :: ACViewProperty (ACViewProperty &viewattr_ref )
                     : bnode (viewattr_ref),
  target(),
  source(viewattr_ref.get_source()),
  expression(viewattr_ref.expression),
  source_type(ADT_undefined),
  oper_env(viewattr_ref.get_oper_env())
{

  SetTarget();

}

/******************************************************************************/
/**
\brief  ChangeMode - Change Mode


\return oldmode -

\param  accopt - Access mode
\param  chkopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC ACViewProperty :: ChangeMode (PIACC accopt, char chkopt )
{
  PIACC                   oldmode = PI_undefined;
BEGINSEQ
  if ( GetMaxMode() < accopt )                       ERROR
    
  if ( source.IsValid() && source.GetMode() != accopt )
    if ( source.ChangeMode(accopt) == PI_undefined ) ERROR
      
  oldmode = bnode::ChangeMode(accopt);
RECOVER
  oldmode = PI_undefined;
ENDSEQ
  return(oldmode);
}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  autoini -
\param  acccheck -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ACViewProperty :: Check (logical autoini, logical acccheck )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( autoini )
  {
    if ( !nodenode || !((ACOperation *)nodenode)->get_co().IsValid() )
                                                     ERROR
    if ( !source.IsValid() && !stscerr() )
    {
      if ( nodefield->IsViewStructure() )
      {
        PropertyHandle source_inst(&((ACOperation *)nodenode)->get_co());
        nodeptr = new ACPath(source_inst.get_nodeptr(),nodefield,source_inst.GetMode());
        if ( SDBERROR )
        {
          delete nodeptr;
          nodeptr = NULL;
          stsserr();
          SDBCERR
        }
        source.RegisterNode(nodeptr);
      }
      else if ( SetSource() )
      {
        stsserr();
        SDBCERR
      }
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACViewProperty :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(nodeptr = new ACViewProperty(*this))) SDBERR(95)
                                                     SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetMaxMode - 


\return oldmode -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMaxMode"

PIACC ACViewProperty :: GetMaxMode ( )
{
  PIACC                 maxmode = PI_undefined;
  switch ( source_type )
  {
    case ADT_BaseCollection :  // das halte ich fuer unnoetig, da schreibend von aussen nicht praktisch nicht zugegriffen werden kann. (nd)
    case ADT_SortKey_String : 
    case ADT_SortKey        : 
    case ADT_PropertyPath   : maxmode = nodenode->GetMode(NO);
                              break;
    case ADT_Expression     : 
    case ADT_Type           : 
    case ADT_GUID           :
    case ADT_LOID           : maxmode = PI_Read;
                              break;
    default                 : maxmode = PI_undefined;
  }
  

  return(maxmode);
}

/******************************************************************************/
/**
\brief  GetNode - 


\return nodeptr -

\param  autoini -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNode"

node *ACViewProperty :: GetNode (logical autoini )
{

  Check(autoini,NO);
  return ( !this ? NULL 
                 : is_collection ? source.get_nodeptr() 
                                   ? source.get_nodeptr()->GetNode()
                                   : NULL
                                 : this                  );

}

/******************************************************************************/
/**
\brief  IsAttribute - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttribute"

logical ACViewProperty :: IsAttribute ( )
{

  return( !is_collection );

}

/******************************************************************************/
/**
\brief  IsCollection - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollection"

logical ACViewProperty :: IsCollection ( )
{

  return( is_collection );

}

/******************************************************************************/
/**
\brief  IsReadOnly - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical ACViewProperty :: IsReadOnly ( )
{
  logical             cond = YES;
BEGINSEQ
  if ( GetMaxMode() <= PI_Read )                     LEAVESEQ

//  cond = GetNode()->IsReadOnly();

  if ( !source.get_nodeptr() )                       LEAVESEQ
  cond = source.get_nodeptr()->IsReadOnly();
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical ACViewProperty :: Read ( )
{
  char            key[513];
  char            string[513];
  logical         term = NO;
BEGINSEQ
  if ( is_collection )                               LEAVESEQ
    
  nodewrit = NO;
  switch ( source_type )
  {
    case ADT_PropertyPath   : source.Refresh();
                              source.AutoLocate(YES);
                              if ( !source.get_nodeptr() )
                                                     ERROR
                              (*(dbf *)(this)) = *source.get_nodeptr();
                              break;
    case ADT_Expression     : if ( operation.Execute(NULL) )
                                                     SDBERR(556)
                              source.CopyHandle(&operation.GetResult());
                              if ( !source.get_nodeptr() )
                                                     ERROR
                              (*(dbf *)(this)) = *source.get_nodeptr();
                              break;
    case ADT_SortKey        : if ( !source.ExtractSortKey(key).GetData() &&
                                   !source.ExtractKey(key).GetData() )
                                                     ERROR
                              (*(dbf *)(this)) = key;
                              break;
    case ADT_SortKey_String : if ( source.ExtractSortKey(key).GetData() ||
                                   source.ExtractKey(key).GetData() )
                                (*(dbf *)(this)) = source.KeyToString(string,key);
                              break;
    case ADT_GUID           : (*(dbf *)(this)) = source.GetGUID();
                              LEAVESEQ
    case ADT_LOID           : (*(dbf *)(this)) = source.GetLOID();
                              LEAVESEQ
    case ADT_Type           : (*(dbf *)(this)) = source.GetCurrentType();
                              LEAVESEQ
    default                 :                        SDBERR(99)
  }
  nodewrit = source.get_nodeptr()->IsWrite();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  switchopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACViewProperty :: Save (logical switchopt )
{
  logical                 term = NO;
BEGINSEQ
  if ( is_collection )
    if ( source.Save(switchopt) )                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetIsCollection - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIsCollection"

void ACViewProperty :: SetIsCollection ( )
{

BEGINSEQ
  if ( is_collection )                               LEAVESEQ
  
  if ( nodefield->fmcbityp != T_MEMO && 
       ( nodefield->fmcbrlev == R_REFR || nodefield->fmcbrlev == R_GENERIC ||
         ( source.IsValid() && source.IsCollection() && source.GetDimension() != 1 ) ) )
    is_collection = YES;
      

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetSource - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSource"

logical ACViewProperty :: SetSource ( )
{
  PropertyHandle          source_inst;
  FieldSource            *srce_def;
  char                   *expr_str;
  BNFData                *expr_bnf;
  logical                 term = NO;
BEGINSEQ
  source_inst.Open(&((ACOperation *)nodenode)->get_co());
  
  if ( !(srce_def = nodefield->GetSource(0)) )         SDBERR(99)
  if ( !(expr_str = srce_def->GetString()) )           SDBERR(99)
  if ( !(expr_bnf = srce_def->GetBNFData(source_inst.get_nodeptr()->GetDictionary())) )
                                                     SDBERR(99)
  nodefield->GetDBStruct(GetDictionary());  // read view definition if necessary
  
  if ( nodefield->IsViewStructure() )
  {
    if ( nodefield->fmcbrlev != R_REFR )
      Check(YES);
    else
      is_collection = YES;
  }
  
  if ( operation.Open(*oper_env->CO()) )           SDBERR(555)
  operation.get_operation()->SetEnvironment(oper_env);
  if ( operation.ProvideExpression(expr_str) )     SDBERR(555)
  source.CopyHandle(operation.get_operation());

  if ( SetupFieldDef() )                             ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTarget - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTarget"

void ACViewProperty :: SetTarget ( )
{

  target.RegisterNode(this);

}

/******************************************************************************/
/**
\brief  SetupAttribute - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAttribute"

logical ACViewProperty :: SetupAttribute ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !is_opened )
  {    
    if ( !(nodeinst = new binti(this,NULL,NULL,
                              nodenode->get_nodeinst()->get_iselarea()+nodefield->fmcbposn,NO)) )
                                                     SDBERR(95)
                                                     SDBCERR
    Open(object_ref,nodenode,nodefield,NULL,nodeacc);
  }
  
  if ( source.IsValid() )
  {
    source.Refresh();
    if ( source.GetMode() < nodeacc )
      nodeacc = source.GetMode();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupFieldDef - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupFieldDef"

logical ACViewProperty :: SetupFieldDef ( )
{
  logical              term = NO;
BEGINSEQ
  if ( !source.IsValid() )                           LEAVESEQ
    
  if ( !*nodefield->fmcbtype && source.GetFieldDef() )
    nodefield->UpdateDescription(*source.GetFieldDef());
  else if ( is_collection && !nodefield->fmcbdim )
    nodefield->fmcbdim = source.GetDimension();
  
  if ( source.GetMode() < nodeacc )
    nodeacc = source.GetMode();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupReference - 


\return term - Termination code

\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReference"

logical ACViewProperty :: SetupReference (void *instptr )
{
  logical                 term = NO;
  nodenode->get_nodeinst()->SetPI(this,instptr);

  if ( !is_opened )
    Open(object_ref,nodenode,nodefield,NULL,nodeacc);

  if ( source.IsValid() )
  {
    source.Refresh();
    if ( source.GetMode() < nodeacc )
      nodeacc = source.GetMode();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Store - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical ACViewProperty :: Store ( )
{
  logical         term = NO;
BEGINSEQ
  if ( nodeacc <= PI_Read )                          SDBERR(28)

  if ( is_collection )
  {
    switch ( source_type )
    {
      case ADT_SortKey        : if ( source.SetKey(Key((char *)GetArea())) )
                                                     ERROR
                                break;
      case ADT_SortKey_String : if ( source.SetKey(Key(StringToKey((char *)GetArea(),NULL))) )
                                                     ERROR
    }
  }
  else
    source = target;                                 SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACViewProperty - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACViewProperty"

                        ACViewProperty :: ~ACViewProperty ( )
{



}


