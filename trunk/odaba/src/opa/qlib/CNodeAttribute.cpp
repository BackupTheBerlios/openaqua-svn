/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CNodeAttribute

\brief    


\date     $Date: 2006/08/30 19:44:48,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CNodeAttribute"

#include  <popa7.h>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <snode.hpp>
#include  <sCNodeAttribute.hpp>


/******************************************************************************/
/**
\brief  CNodeAttribute - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  nodeptr - 
\param  nodtype - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  intoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNodeAttribute"

     CNodeAttribute :: CNodeAttribute (node *nodeptr, NodeTypes nodtype, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 intoff, PIACC accopt )
                     : CNode()
{

  data_nodetype = nodtype;
  CNode::Open(nodeptr,dbfield_ptr,highctx,instptr,accopt);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  cnattr_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNodeAttribute"

     CNodeAttribute :: CNodeAttribute (CNodeAttribute &cnattr_ref )
                     : CNode(cnattr_ref)
{



}

/******************************************************************************/
/**
\brief  ChangeMode - 



\return oldmode - 

\param  newmode - 
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC CNodeAttribute :: ChangeMode (PIACC newmode, char chkopt )
{

  return(bnode::ChangeMode(newmode,chkopt));

}

/******************************************************************************/
/**
\brief  Check - 



\return term - 

\param  autoini - 
\param  acccheck - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical CNodeAttribute :: Check (logical autoini, logical acccheck )
{

  return( bnode::Check(autoini,acccheck) );


}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical CNodeAttribute :: CheckModify ( )
{
  logical      term = YES;
BEGINSEQ
  if ( IsTransient() )                               LEAVESEQ
  if ( nodeacc <= PI_Read )                          SDBERR(28)
  
  if ( CheckGenAttribute() )                         ERROR  
  if ( nodenode && nodenode->CheckModify() )         ERROR


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

node *CNodeAttribute :: CreateCopyNode ( )
{
  node *   nodeptr = NO;
BEGINSEQ
  if ( !(nodeptr = new CNodeAttribute(*this) ) )     SDBERR(95)
                                                     SDBCERR
RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Get - 



\return instptr - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *CNodeAttribute :: Get (int32 lindx0, logical chknode )
{
  void *   instptr = NULL;
  if ( instptr = (char *)Get_attribute(lindx0,chknode) )
    GenerateEvent(DBO_Read);

  return(instptr);
}

/******************************************************************************/
/**
\brief  GetCount - 



\return count - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 CNodeAttribute :: GetCount (logical chknode )
{

  return(nodefield->fmcbdim);

}

/******************************************************************************/
/**
\brief  GetID - 



\return obident - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  lindx0 - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number CNodeAttribute :: GetID (int32 lindx0, logical chknode, logical pif_opt )
{
  EB_Number             entnr;
  return( lindx0 >= nodefield->fmcbdim ? entnr 
                                      : nodenode->GetID(AUTO,chknode,pif_opt));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  keyptr - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number CNodeAttribute :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  EB_Number             entnr;
  return(entnr);

}

/******************************************************************************/
/**
\brief  GetInstModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 CNodeAttribute :: GetInstModCount ( )
{

  return(nodenode->GetInstModCount());

}

/******************************************************************************/
/**
\brief  GetKey - 



\return sort_key - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *CNodeAttribute :: GetKey (int32 lindx0, logical chknode )
{
  char *   sort_key;

  return(sort_key);
}

/******************************************************************************/
/**
\brief  GetRefModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 CNodeAttribute :: GetRefModCount ( )
{

  return(1);

}

/******************************************************************************/
/**
\brief  IsAutoPosition - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoPosition"

logical CNodeAttribute :: IsAutoPosition ( )
{

  return ( nodenode ? nodenode->IsAutoPosition() : YES );

}

/******************************************************************************/
/**
\brief  IsWrite - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical CNodeAttribute :: IsWrite ( )
{

  return ( nodenode ? nodenode->IsWrite()
                    : bnode::IsWrite()    );


}

/******************************************************************************/
/**
\brief  Modify - 



\return instptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *CNodeAttribute :: Modify (logical chknode )
{

  return(ModifyAttribute(chknode));

}

/******************************************************************************/
/**
\brief  Provide - 



\return instance - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *CNodeAttribute :: Provide (int32 lindx0, logical global_add )
{

  return(Get(lindx0));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  skey - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *CNodeAttribute :: Provide (char *skey, logical global_add )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  datarea - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *CNodeAttribute :: Provide (void *datarea, logical global_add )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  Switch - 



\return term - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Switch"

logical CNodeAttribute :: Switch (int32 indx0 )
{

  return(node::Switch(indx0));

}

/******************************************************************************/
/**
\brief  ~CNodeAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CNodeAttribute"

     CNodeAttribute :: ~CNodeAttribute ( )
{



}


