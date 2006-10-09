/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACMetaAttribute

\brief    


\date     $Date: 2006/08/26 14:11:40,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACMetaAttribute"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <snode.hpp>
#include  <sACMetaAttribute.hpp>


/******************************************************************************/
/**
\brief  ACMetaAttribute - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  dbfield_ptr - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACMetaAttribute"

     ACMetaAttribute :: ACMetaAttribute (node *nodeptr, DBFieldDef *dbfield_ptr )
                     : bnode()
{

  nodetype = NT_ACMetaAttribute;
  nodecur  = 0;
  
  Open(nodeptr->GetObjectHandle(),nodeptr,dbfield_ptr,NULL,PI_Read);

  nodenode->AddMetaNode(this);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  mattrnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACMetaAttribute"

     ACMetaAttribute :: ACMetaAttribute (ACMetaAttribute &mattrnode_ref )
                     : bnode (mattrnode_ref)
{

  nodecur = 0;

  nodenode->AddMetaNode(this);


}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical ACMetaAttribute :: CheckModify ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACMetaAttribute :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACMetaAttribute(*this) ) )    SDBERR(95)
                                                     SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateSubNode - 



\return nodeptr - 

\param  nodeptr - 
\param  nodtype - 
\param  sysnode - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  extoff - 
\param  intoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubNode"

node *ACMetaAttribute :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  Get - 



\return instptr - 

\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACMetaAttribute :: Get (int32 indx0, logical chknode )
{
  char     *instptr  = NULL;
  char     *key_val  = NULL;
  smcb     *smcbptr  = NULL;
  int32     id;
  char     *string;
BEGINSEQ
  if ( !this || !nodenode )                          SDBERR(99)
  if ( indx0 != 0 )                                  ERROR

  if ( !(instptr = (char *)GetArea()) )
  {
    AllocateArea();
    instptr = (char *)GetArea();
  }

  switch ( nodefield->get_meta_field() )
  {
    case MAT_LOID    : if ( !(id = nodenode->GetID(AUTO).get_ebsnum()) )
                                                    ERROR
                       gvtxltoa(id,instptr,10);
                       break;
    case MAT_GUID    : if ( !nodenode->IsPositioned() ||
                            !(string = nodenode->GetGUID()) )
                                                    ERROR
                       strcpy(instptr,string);
                       break;
    case MAT_Type    : if ( !(string = nodenode->GetCurrentType()) )
                                                    ERROR
                       strcpy(instptr,string);
                       break;
    case MAT_Property: if ( !(string = nodenode->get_prop_path()) )
                                                    ERROR
                       strcpy(instptr,string);
                       break;
    case MAT_SortKey : if ( !(smcbptr = nodenode->GetSortKeySMCB()) ||
                            !(key_val = nodenode->ExtractSortKey(NULL,NULL,NO)) )
                                                     ERROR
                       smcbptr->ConvertToString(key_val,instptr,nodefield->fmcbsize);
                       break;
    case MAT_Key     : if ( !(smcbptr = nodenode->GetKeySMCB()) ||
                            !(key_val = nodenode->ExtractKey(NULL,NULL,NO)) )
                                                     ERROR
                       smcbptr->ConvertToString(key_val,instptr,nodefield->fmcbsize);
                       break;
    default          :                              ERROR
  }

  GenerateEvent(DBO_Read);

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetCount - 



\return ecnt - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACMetaAttribute :: GetCount (logical chknode )
{

  return(nodenode->IsPositioned() ? 1 : ERIC);

}

/******************************************************************************/
/**
\brief  GetID - 



\return ebsnum - 
-------------------------------------------------------------------------------
\brief  NODEGID - 



\param  indx0 - Position in collection
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACMetaAttribute :: GetID (int32 indx0, logical chknode, logical pif_opt )
{

  return(nodenode->GetID(indx0,chknode,pif_opt));

}

/******************************************************************************/
/**
\brief  NODEGID_ - 



\param  keyptr - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACMetaAttribute :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

  return(nodenode->GetID(keyptr,chknode,pif_opt));

}

/******************************************************************************/
/**
\brief  GetInstModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 ACMetaAttribute :: GetInstModCount ( )
{

  return(nodenode->GetInstModCount());

}

/******************************************************************************/
/**
\brief  GetString - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *ACMetaAttribute :: GetString ( )
{
  char      * string = "";
  if ( Get(0) )
    string = bnode::GetString();

  return(string);
}

/******************************************************************************/
/**
\brief  IsAutoPosition - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoPosition"

logical ACMetaAttribute :: IsAutoPosition ( )
{

  return ( nodenode ? nodenode->IsAutoPosition() : YES );

}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical ACMetaAttribute :: IsPositioned ( )
{

  return(nodenode->IsPositioned());

}

/******************************************************************************/
/**
\brief  IsSelected - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical ACMetaAttribute :: IsSelected ( )
{

  return(nodenode->IsSelected());

}

/******************************************************************************/
/**
\brief  IsWrite - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical ACMetaAttribute :: IsWrite ( )
{

  return ( NO );


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

void *ACMetaAttribute :: Modify (logical chknode )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  Provide - 



\return instptr - 

\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACMetaAttribute :: Provide (int32 lindx0, logical global_add )
{

  return(Get(lindx0));

}

/******************************************************************************/
/**
\brief  Store - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical ACMetaAttribute :: Store ( )
{
  logical   term = NO;
// Store muss nodenode entsprechend typ ändern (SetType, SetKey etc.

  return(term);
}

/******************************************************************************/
/**
\brief  Switch - 



\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Switch"

logical ACMetaAttribute :: Switch (int32 indx0 )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ~ACMetaAttribute - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACMetaAttribute"

     ACMetaAttribute :: ~ACMetaAttribute ( )
{

  ReleaseProcessEvents(YES);    // müssen wir hier schon machen, da sonst inti weg
  
  nodenode->RemoveMetaNode(this);

  nodeinst  = NULL;
  nodefield = NULL;
  
  if ( nodeidnt == NODE_ID )
    Close();

}


