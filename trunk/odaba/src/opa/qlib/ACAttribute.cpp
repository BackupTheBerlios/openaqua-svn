/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACAttribute

\brief    


\date     $Date: 2006/08/30 20:13:29,07 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACAttribute"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sACProperty.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sbinti.hpp>
#include  <snode.hpp>
#include  <sACAttribute.hpp>


/******************************************************************************/
/**
\brief  ACAttribute - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACAttribute"

     ACAttribute :: ACAttribute (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt )
                     : bnode()
{

BEGINSEQ
  bnode::Open(nodeptr->GetObjectHandle(),nodeptr,dbfield_ptr,highctx,accopt);
  nodetype = NT_ACAttribute;
  nodecur  = 0;
  
  if ( dbfield_ptr && dbfield_ptr->fmcbsmcb )
  {
    if ( dbfield_ptr->fmcbsmcb->smcbstyp == ST_CODE )
      is_codeset = YES;
    else if ( dbfield_ptr->fmcbdim > 1 )
    {
      moveable_instance = YES;
      type_inti = new DPA(inti)(dbfield_ptr->fmcbdim);
    }
  }
    
  if ( Bnodenode->get_moveable_instance() )
    moveable_instance = YES;
    
  if ( InitInti(NULL,instptr,NO) )                   ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  attrnod_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACAttribute"

     ACAttribute :: ACAttribute (ACAttribute &attrnod_ref )
                     : bnode (attrnod_ref)
{

BEGINSEQ
  if ( nodefield->fmcbdim > 1 &&
       nodefield->fmcbsmcb && nodefield->fmcbsmcb->smcbstyp != ST_CODE )
    type_inti = new DPA(inti)(nodefield->fmcbdim);
  
  nodecur = 0;
  
  if ( InitInti(NULL,attrnod_ref.get_nodeinst()->get_iselarea(),NO) )
                                                     ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical ACAttribute :: CheckModify ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsTransient() )                               LEAVESEQ
  if ( nodeacc <= PI_Read )                          SDBERR(28)
  
    
//  if ( GenerateEvent(DBP_Modify) )                   ERROR
//  modif. ist noch nicht in instanz!  
  
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

node *ACAttribute :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACAttribute(*this) ) )        SDBERR(95)
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

node *ACAttribute :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{
  node         *subnode = NULL;
BEGINSEQ
  switch ( nodtype )
  {
    case  NT_ACAttribute    : subnode = new ACAttribute(nodeptr,dbfield_ptr,highctx,
                                                        instptr,accopt);
                              break;
    default                 : subnode = bnode::CreateSubNode(nodeptr,nodtype,sysnode,dbfield_ptr,highctx,instptr,extoff,intoff,accopt);
  }
  if ( !subnode )                                    SDBERR(95)
  SDBCERR
RECOVER
  delete subnode;
  subnode = NULL;
ENDSEQ
  return(subnode);
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

void *ACAttribute :: Get (int32 indx0, logical chknode )
{
  inti     *old_inti = nodeinst;
  char     *instptr  = NULL;
  char     *key_val  = NULL;
  smcb     *smcbptr  = NULL;
  if ( instptr = (char *)Get_attribute(indx0,chknode) )
  {
    if ( old_inti != nodeinst )
      Bnodeinst->ReadEvent();
    GenerateEvent(DBO_Read);
  }  

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

int32 ACAttribute :: GetCount (logical chknode )
{

  return(nodefield->fmcbdim);

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

EB_Number ACAttribute :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number             entnr;
  return( indx0 >= nodefield->fmcbdim ? entnr 
                                      : nodenode->GetID(AUTO,chknode,pif_opt));

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

EB_Number ACAttribute :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  EB_Number           entnr;
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

int16 ACAttribute :: GetInstModCount ( )
{

  return(nodenode->GetInstModCount());

}

/******************************************************************************/
/**
\brief  IsAutoPosition - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoPosition"

logical ACAttribute :: IsAutoPosition ( )
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

logical ACAttribute :: IsPositioned ( )
{

  return(node::IsPositioned());

}

/******************************************************************************/
/**
\brief  IsSelected - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical ACAttribute :: IsSelected ( )
{

  return(node::IsSelected());

}

/******************************************************************************/
/**
\brief  IsWrite - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical ACAttribute :: IsWrite ( )
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

void *ACAttribute :: Modify (logical chknode )
{

  return(ModifyAttribute(chknode));

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

void *ACAttribute :: Provide (int32 lindx0, logical global_add )
{

  return(Get(lindx0));

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

logical ACAttribute :: Switch (int32 indx0 )
{

  return(node::Switch(indx0));

}

/******************************************************************************/
/**
\brief  ~ACAttribute - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACAttribute"

     ACAttribute :: ~ACAttribute ( )
{

  ReleaseProcessEvents(YES);    // müssen wir hier schon machen, da sonst inti weg
  
  delete nodeinst;  
  nodeinst = NULL;

  if ( nodeidnt == NODE_ID )
    Close();

}


