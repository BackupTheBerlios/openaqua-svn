/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACHierNode

\brief    


\date     $Date: 2006/07/24 13:45:44,35 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACHierNode"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sACObject.hpp>
#include  <sPropertyHandle.hpp>
#include  <sinti.hpp>
#include  <sref.hpp>
#include  <sACHierNode.hpp>


/******************************************************************************/
/**
\brief  ACHierNode - 




\param  sysnode - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACHierNode"

     ACHierNode :: ACHierNode (ACExtend *sysnode, PIACC accopt )
                     : ACTopNode (sysnode,accopt,NULL),
  nodelist(NULL),
  pib_count(1)
{
  ACObject  *ob_handle = object_ref;
  int        i = 1;
  nodetype = NT_ACTopNode;
  
  while ( ob_handle = ob_handle->GetHighObject() )
    pib_count++;
    
  nodelist = (PropertyHandle **)new char[pib_count*sizeof(PropertyHandle *)];
  memset(nodelist,0,pib_count*sizeof(PropertyHandle *));  


}

/******************************************************************************/
/**
\brief  Add - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACHierNode :: Add (int32 lindx0, logical global_add )
{
  node           *nodeptr = nodelist[0]->get_nodeptr();
  logical         newi;
  char           *instptr = NULL;
BEGINSEQ
  if ( !nodeptr->Add(AUTO,NULL,NULL,nodeinst->get_iselarea(),global_add) )
                                                     ERROR
  newi = !nodeptr->get_nodeinst()->stscold();
  
  nodeptr->Save(NO,NO,NO);
  if ( AddReference(nodeptr,lindx0) )                ERROR
  instptr = nodeinst->get_iselarea();
  
  if ( newi )
    nodeinst->stsrold();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACHierNode :: Add (int32 lindx0, char *skey, char *idkey, void *initinst )
{
  node           *nodeptr = nodelist[0]->get_nodeptr();
  void           *instptr = NULL;
  char           *ident_key = idkey;
BEGINSEQ
  if ( !idkey )
  {
    if ( skey )
      ident_key = skey;
    else if (initinst )
      ident_key = nodeptr->ExtractKey(NULL,initinst);
  }
  if ( !ident_key )                                  SDBERR(99)
    
  if ( !nodeptr->LocateKey(ident_key,YES,NO) )
  {
    noderefp->SetKeyErrorVariables(ident_key);
    SDBERR(64)
  }

  if ( !LocateKey(ident_key,YES,NO) )  // lokalisieren der Instanz
  {
    if ( !Get(ident_key) )                           ERROR
    if ( !nodeptr->CopyInst(this,REPL_none) )        ERROR
    if ( system_node->Delete(Bnodeinst,NO,NO,YES) )  ERROR
    if ( AddReference(nodeptr,lindx0) )              ERROR
    instptr = nodeinst->get_iselarea();
  }
  else
    instptr = LNode::Add(lindx0,skey,idkey,initinst);
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code

\param  lindx0 - 
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACHierNode :: Delete (int32 lindx0, logical chknode, logical del_dep, logical del_inst )
{
  node           *nodeptr = nodelist[0]->get_nodeptr();
  char            key[513];
  int16           talevel = 0;
  int             count = 0;
  logical         term = NO;
BEGINSEQ
  if ( !Get(lindx0,chknode) )                        ERROR
  if ( nodeptr->LocateKey(ExtractKey(key,NULL),YES,NO) )
                                                     SDBERR(99)
  talevel = StartTA();
  if ( system_node->Delete(Bnodeinst,YES,del_dep,YES,del_inst) )   
                                                     ERROR
  ResetInstance();
  if ( !nodeptr->Get() )                             SDBERR(99)
  if ( nodeptr->Delete(AUTO) )                       ERROR

  while ( ++count < pib_count )
  {
    if ( !nodelist[count]->get_nodeptr()->LocateKey(key,YES,NO) )
    {
      if ( AddReference(nodelist[count]->get_nodeptr(),AUTO) )
                                                     ERROR
      Switch(AUTO);
      break;
    }
  }

RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  nodecur = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG - 



\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACHierNode :: Get (int32 indx0, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( !(instptr = ACTopNode::Get(indx0,chknode)) )  ERROR

  if ( nodewrit )
    SetWrite();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACHierNode :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( !(instptr = ACTopNode::Get(skey,chknode)) )  ERROR
  
  if ( nodewrit )
    SetWrite();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACHierNode :: GetMainBase ( )
{

  return(((LNode *)nodelist[0]->get_nodeptr())->GetMainBase());

}

/******************************************************************************/
/**
\brief  InitReference - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitReference"

logical ACHierNode :: InitReference ( )
{
  ACObject     *ob_handle = object_ref;
  logical       overload  = object_ref->SetOverload(NO);
  PIACC         original_mode;
  char          extnames[41];
  int           i = 0;
  logical       term = NO;
  DBObjectHandle dbohandle;
BEGINSEQ
  if ( !noderefl )
    if ( LNode::InitReference() )                     ERROR
    
  if ( !nodelist[0] && nodefield->get_extend() )
  {
    do {
	  dbohandle = DBObjectHandle(ob_handle);  
      if ( !(nodelist[i] = new PropertyHandle(dbohandle,gvtxbts(extnames,(char *)nodefield->get_extend(),ID_SIZE),
                                   i || nodeacc == PI_Read ? PI_Read : PI_Update)) )  
                                                     SDBERR(95)
                                                     SDBCERR
      i++;
    } while ( ob_handle = ob_handle->GetHighObject() );
    
    if ( !GetCount() )
    {
      original_mode = ChangeMode(PI_Write);
      Union(nodelist,pib_count,YES,YES);
      ChangeMode(original_mode);
    }
  }
RECOVER
  term = YES;
ENDSEQ
  object_ref->SetOverload(overload);
  return(term);
}

/******************************************************************************/
/**
\brief  SetWrite - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWrite"

logical ACHierNode :: SetWrite ( )
{
  node           *nodeptr = nodelist[0]->get_nodeptr();
  logical         term = NO;
  if ( nodeptr->LocateKey(ExtractKey(NULL,NULL),YES,NO) )
    nodewrit = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACHierNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACHierNode"

     ACHierNode :: ~ACHierNode ( )
{

  if ( nodeidnt == NODE_ID )
    Close();
      
  while ( pib_count-- )
    delete nodelist[pib_count];

}


