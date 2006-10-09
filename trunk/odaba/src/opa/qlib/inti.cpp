/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    inti

\brief    


\date     $Date: 2006/08/30 17:18:28,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "inti"

#include  <popa7.h>
#include  <sACMetaAttribute.hpp>
#include  <sACObject.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sguid.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sinti.hpp>

int32 inti_count = 0;
int32 inti_max = 0;

/******************************************************************************/
/**
\brief  Add - 



\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical inti :: Add (logical global_add )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  AllocateArea - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateArea"

char *inti :: AllocateArea ( )
{
  int32                   instlen = 0;
  char                   *instptr = NULL;
BEGINSEQ
  if ( instlen = GetInstLength() )
  {
    if ( !(instptr = (char *)msmgs(instlen)) )       SDBERR(95)
    if ( struct_def->smcbstyp != ST_CODE && struct_def->smcbfmcl )
    {
      struct_def->smcbfmcl->fmcliini(instptr);
      struct_def->InitAttributes(instptr);
    }
  }
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  BuildGUID - 



\return _guid - 

\param  _guid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildGUID"

guid *inti :: BuildGUID (guid *_guid )
{

  _guid->Initialize(struct_def->smcbityp,(uint32)this,GetID().get_ebsnum());
  return(_guid);

}

/******************************************************************************/
/**
\brief  Cancel - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical inti :: Cancel ( )
{

  inst_index = 0;
  return(NO);

}

/******************************************************************************/
/**
\brief  ChangeMode - 



\return term - Termination code

\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

logical inti :: ChangeMode (PIACC accopt )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 



\return wpmode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 inti :: CheckWProtect ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical inti :: Close ( )
{

  DeleteSubNodes();
  
  ReleaseArea();
  return(NO);
}

/******************************************************************************/
/**
\brief  Copy - 



\return converr - 

\param  srceinti - 
\param  nodeptr - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

int16 inti :: Copy (inti *srceinti, node *nodeptr, PIREPL db_replace, PIREPL copy_type )
{
  int16     converr = NO;

  struct_def->CopyInstance(iselarea,srceinti->get_struct_def(),srceinti->get_iselarea(),db_replace,UNDEF);

  return(converr);

}

/******************************************************************************/
/**
\brief  CopyBufferInstance - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyBufferInstance"

logical inti :: CopyBufferInstance (inti *intiptr )
{
  logical                 term = NO;
//  struct_def->CopyInstance(iselarea,intiptr->get_struct_def(),intiptr->get_iselarea(),AUTO,UNDEF);
// das oben ist zwar besser, dauert aber zu lange!!
  memcpy(iselarea,intiptr->get_iselarea(),GetInstLength());
  inst_index = intiptr->get_inst_index();
  return(term);
}

/******************************************************************************/
/**
\brief  CreateGUID - 



\return term - Termination code

\param  _guid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGUID"

logical inti :: CreateGUID (guid *_guid )
{

    return(YES);

}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code

\param  extname - Extent name
\param  is_root - 
\param  delopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical inti :: Delete (char *extname, logical is_root, int16 delopt )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  DeleteInstance - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteInstance"

logical inti :: DeleteInstance ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DeleteSubNodes - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSubNodes"

void inti :: DeleteSubNodes ( )
{

  node_attr.DeleteNodes();
  


}

/******************************************************************************/
/**
\brief  Get - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical inti :: Get (EB_Number entnr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical inti :: Get (char *extinst )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  GetContext - 



\return strctx - Structure Context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Structure *inti :: GetContext ( )
{

  return ( NULL );

}

/******************************************************************************/
/**
\brief  GetCount - 



\return ecnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 inti :: GetCount ( )
{


  return(ERIC);
}

/******************************************************************************/
/**
\brief  GetGUID - 



\return _guid - 

\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGUID"

guid *inti :: GetGUID (char chkopt )
{
  int32                  pos;
  guid                 *_guid = NULL;
BEGINSEQ
  if ( (pos = struct_def->GetGUIDPosition()) == AUTO )
                                                     ERROR
  _guid = (guid *)(iselarea+pos);
  if ( chkopt == YES )
  {
    _guid->AutoCorrection();
    if ( !_guid->GetSID() )                          ERROR
  }
RECOVER
  _guid = NULL;
ENDSEQ
  return(_guid);
}

/******************************************************************************/
/**
\brief  GetID - 



\return entnr - 

\param  w_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number inti :: GetID (int32 w_indx0 )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  GetIdentity - 



\return entnr_pt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentity"

EB_Number *inti :: GetIdentity ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetIndex - 



\return lindx - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 inti :: GetIndex (EB_Number entnr )
{

  return(inst_index);

}

/******************************************************************************/
/**
\brief  GetInstLength - 



\return inst_len - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstLength"

uint32 inti :: GetInstLength ( )
{

  return ( !struct_def                           ? UNDEF 
           : struct_def->smcbityp < 0 && field_def->fmcbrlev == R_DIRECT 
                                                 ? field_def->fmcbbyte
           : struct_def->smcbityp == T_VOID      ? UNDEF 
           : struct_def->smcbityp == T_MEMO      ? field_def->fmcbsize+1 
           : struct_def->smcbityp == T_BLOB      ? field_def->fmcbsize
           : struct_def->GetInstLength(field_def ? field_def->fmcbbstr
                                                 : NO) );

}

/******************************************************************************/
/**
\brief  GetModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 inti :: GetModCount ( )
{

  return(0);

}

/******************************************************************************/
/**
\brief  GetOBHandle - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOBHandle"

ACObject *inti :: GetOBHandle ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetPropNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropNode"

node *inti :: GetPropNode (char *prop_names, CTX_Property *highprop_ctx )
{
  node      **pnodeptr = NULL;
  pnodeptr = GetPropNodePtr(prop_names,highprop_ctx);
  return(pnodeptr ? *pnodeptr : NULL);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_names - Property name
\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropNode"

node *inti :: GetPropNode (char *prop_names, char *proppath )
{
  node      **pnodeptr = NULL;
  pnodeptr = GetPropNodePtr(prop_names,proppath);
  return(pnodeptr ? *pnodeptr : NULL);
}

/******************************************************************************/
/**
\brief  GetPropNodePtr - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropNodePtr"

node **inti :: GetPropNodePtr (char *prop_names, CTX_Property *highprop_ctx )
{
  char        propname[ID_SIZE];
  node      **pnodeptr = NULL;
  gvtxstb(propname,prop_names,ID_SIZE);

  pnodeptr = node_attr.GetNodePtr(propname,highprop_ctx,NO);

  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_names - Property name
\param  proppath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropNodePtr"

node **inti :: GetPropNodePtr (char *prop_names, char *proppath )
{
  char        propname[ID_SIZE];
  node      **pnodeptr = NULL;
  gvtxstb(propname,prop_names,ID_SIZE);

  pnodeptr = node_attr.GetNodePtr(propname,proppath,NO);

  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  GetSID - 



\return sid - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSID"

int16 inti :: GetSID (EB_Number entnr )
{

  return ( struct_def ? struct_def->smcbityp : UNDEF );

}

/******************************************************************************/
/**
\brief  GetSize - 



\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

uint32 inti :: GetSize ( )
{
  uint32    size = UNDEF;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( struct_def && struct_def->smcbityp != T_MEMO  && struct_def->smcbityp != T_BLOB )
    size = struct_def->GetLength();
  else
    if ( field_def )
      size = field_def->fmcbsize;
RECOVER

ENDSEQ
  return(size);
}

/******************************************************************************/
/**
\brief  GetSubNode - 



\return nodeptr - 

\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubNode"

node *inti :: GetSubNode (char *prop_names, CTX_Property *highprop_ctx )
{
  node      **pnodeptr = NULL;
  pnodeptr = GetSubNodePtr(prop_names,highprop_ctx);
  return(pnodeptr ? *pnodeptr : NULL);
}

/******************************************************************************/
/**
\brief  GetSubNodePtr - 



\return nodeptr - 

\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubNodePtr"

node **inti :: GetSubNodePtr (char *prop_names, CTX_Property *highprop_ctx )
{
  char                   *proppath = NULL;
  char                    propname[ID_SIZE];
  char                   *pos;
  node                  **pnodeptr   = NULL;

BEGINSEQ
  if ( !(pos = strchr(prop_names,'.')) )
    gvtxstb(propname,prop_names,sizeof(propname));
  else
  {
    proppath = pos+1;
    memset(propname,' ',sizeof(propname));
    memcpy(propname,prop_names,MIN(pos-prop_names,sizeof(propname)));
  }

  if ( (pnodeptr = node_attr.GetNodePtr(propname,highprop_ctx,NO)) )
  {
    if ( !proppath )                                 LEAVESEQ
    
    if ( (*pnodeptr)->GetContext() )
      highprop_ctx = (CTX_Property *)(*pnodeptr)->GetContext();
    
    if ( pnodeptr = GetSubNodePtr(proppath,highprop_ctx) )
                                                     LEAVESEQ
  }

  

ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  GetVersion - 



\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 inti :: GetVersion ( )
{

  return ( CUR_VERSION );

}

/******************************************************************************/
/**
\brief  InitArea - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitArea"

logical inti :: InitArea (void *instptr )
{
  int32                   instlen = 0;
  logical                 term = NO;
BEGINSEQ
  if ( iselarea )                                    LEAVESEQ
    
  if ( instptr )
    iselarea = (char *)instptr;
  else if ( iselarea = AllocateArea() )
    iselifo = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code

\param  initinst - 
\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical inti :: Initialize (void *initinst, logical set_init )
{

BEGINSEQ
// nd 9.2.2004 - es muessen nun auch basistyp-attribute initialisiert werden (sollen GetInitInstance unterstuetzen)
//  if ( !struct_def )                                 ERROR
  if ( !field_def )                                  ERROR
  
  if ( !initinst )
  {
    if ( field_def->fmcbityp == T_MEMO )
      memset(iselarea,0,field_def->fmcbsize+1);
    else if ( field_def->fmcbityp == T_BLOB )
      memset(iselarea,0,field_def->fmcbsize);
    else if ( struct_def && struct_def->smcbstyp != ST_CODE )
      struct_def->smcbfmcl->fmcliini(iselarea);
    else
      field_def->InitAttribute(iselarea);
  }
  else if ( initinst != iselarea )
  {
    if ( struct_def->smcbityp == T_MEMO )
      gvtxbts(iselarea,(char *)initinst,field_def->fmcbsize);
    else if ( struct_def->smcbityp == T_BLOB )
      memcpy(iselarea,initinst,field_def->fmcbsize);
    else if ( struct_def && struct_def->smcbstyp != ST_CODE )
      struct_def->CopyInstance(iselarea,struct_def,(char *)initinst,AUTO,UNDEF);
    else
      field_def->InitAttribute(initinst);
  }
  if ( set_init )
    stssini();
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  IsModified - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

logical inti :: IsModified ( )
{

  return( stscmod() || stscsav() || stscini() );

}

/******************************************************************************/
/**
\brief  IsNewInstance - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical inti :: IsNewInstance ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical inti :: IsPositioned ( )
{

  return( inst_index >= 0 ? YES : NO );



}

/******************************************************************************/
/**
\brief  IsReadOnly - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical inti :: IsReadOnly ( )
{
  CTX_Structure    *ctx;
  logical           cond = NO;
  if ( ctx = GetContext() )
    cond = ctx->IsReadOnly();
  return(cond);
}

/******************************************************************************/
/**
\brief  IsSelected - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical inti :: IsSelected ( )
{

  return( IsPositioned() || stscini() );



}

/******************************************************************************/
/**
\brief  LocateKey - 



\return term - Termination code

\param  skey - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical inti :: LocateKey (char *skey, logical exact )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical inti :: Lock ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Modify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

logical inti :: Modify ( )
{

  stssmod();

  return(NO);
}

/******************************************************************************/
/**
\brief  MoveInstance - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveInstance"

logical inti :: MoveInstance (inti *intiptr )
{
  logical                 term = NO;
  struct_def->CopyInstance(iselarea,intiptr->get_struct_def(),intiptr->get_iselarea(),AUTO,UNDEF);
  inst_index = intiptr->get_inst_index();
  return(term);
}

/******************************************************************************/
/**
\brief  Position - 



\return term - Termination code

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical inti :: Position (int32 count )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  ProvideAttrNode - 



\return pnodeptr - 

\param  parent - 
\param  prop_names - Property name
\param  dbfield_def - 
\param  offset - 
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideAttrNode"

node **inti :: ProvideAttrNode (node *parent, char *prop_names, DBFieldDef *dbfield_def, int32 offset, CTX_Property *highprop_ctx )
{
  node                  **pnodeptr = NULL;
  node                   *attrnode = NULL;
  char                   *proppath = prop_names;
  char                    propname[1024];
  int32                   index = 0;
  char                   *pos;
  node                   *nodeptr = parent;
BEGINSEQ
  if ( !dbfield_def )                                SDBERR(99)
    
  if ( !(pos = STRSearchChar(prop_names,'.',YES)) )
    gvtxstb(propname,prop_names,sizeof(propname));
  else // das geht nicht, wenn wir z.B. a.b im attribute c suchen!!!
  {
    proppath = pos+1;
    memset(propname,0,sizeof(propname));
    memcpy(propname,prop_names,MIN(pos-prop_names,sizeof(propname)-1));
    if ( !(parent = GetSubNode(propname,highprop_ctx)) )
    {
      if ( (nodeptr->Get_data_nodetype() != NT_ACAttribute  &&
            nodeptr->Get_data_nodetype() != NT_ACBaseStruct &&
            nodeptr->Get_data_nodetype() != NT_Node            )  || !nodeptr->get_highnod()  )
                                                     ERROR
      if ( nodeptr->IsAttribute() )
      {
        strcpy(propname,nodeptr->get_prop_path());
        strcat(strcat(propname,"."),prop_names);
        prop_names=propname;
      }
      pnodeptr = nodeptr->get_highnod()->GetNodePtr(prop_names);
      LEAVESEQ
    }
  }
  
  if ( !(attrnode = parent->CreateSubNode(nodeptr,NT_ACAttribute,NULL,dbfield_def,
                                          parent->get_nodeinst()->GetContext(),
                                          nodeptr->get_nodeinst()->get_iselarea()+offset+dbfield_def->fmcbposn,
                                          UNDEF,UNDEF,parent->GetMode())) )
                                                     ERROR
  if ( dbfield_def->fmcbdim > 1 && (pos = strchr(proppath,'(')) &&
       (index = atoi(pos+1)) >= 0 && index < (int32)dbfield_def->fmcbdim    )
  {
    attrnode->Get(index);
    attrnode->set_prop_path(prop_names);
  }
  node_attr.AddTail(attrnode);
  // hier suchen wir nur noch mit dem attribut namen, d.h. der Pfad muss schon aufgelöst sein. 
  if ( !(pnodeptr = node_attr.GetNodePtr(proppath,parent->GetContext())) )
                                                     SDBERR(99)

RECOVER
  pnodeptr = NULL;
ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  Release - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void inti :: Release ( )
{

  inti::Reset();



}

/******************************************************************************/
/**
\brief  ReleaseArea - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseArea"

void inti :: ReleaseArea ( )
{

  if ( iselifo && iselarea )
    msmfs((void **)&iselarea);
  iselarea = NULL;

}

/******************************************************************************/
/**
\brief  RemoveGUID - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveGUID"

logical inti :: RemoveGUID ( )
{

    return(YES);

}

/******************************************************************************/
/**
\brief  Reserve - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical inti :: Reserve ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void inti :: Reset ( )
{

  *(sts *)this = sts();
  
//  inst_index =AUTO;  // wollte N. so

}

/******************************************************************************/
/**
\brief  ResetGUID - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetGUID"

void inti :: ResetGUID ( )
{
  guid         *_guid;
  if ( _guid = GetGUID() )
    _guid->Reset();

}

/******************************************************************************/
/**
\brief  ResetInitialized - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInitialized"

void inti :: ResetInitialized ( )
{

  stsrini();


}

/******************************************************************************/
/**
\brief  ResetInstance - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

logical inti :: ResetInstance ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  ResetNodes - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNodes"

logical inti :: ResetNodes ( )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  ResetWProtect - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical inti :: ResetWProtect ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Save - 



\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical inti :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{

  stsrini();
  return(NO);

}

/******************************************************************************/
/**
\brief  SetInWork - 



\return workopt - 

\param  workopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInWork"

logical inti :: SetInWork (logical workopt )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  SetObjectID - 




\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetObjectID"

void inti :: SetObjectID (int64 obj_id )
{



}

/******************************************************************************/
/**
\brief  SetPI - 




\param  nodeptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPI"

void inti :: SetPI (node *nodeptr, void *instptr )
{

  if ( !instptr )
    instptr = iselarea;
  *(node **)(((char *)instptr) + nodeptr->GetFieldDef()->fmcbposn) = nodeptr;


}

/******************************************************************************/
/**
\brief  SetRefContext - 



\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRefContext"

logical inti :: SetRefContext (inti *intiptr )
{

  return ( NO );

}

/******************************************************************************/
/**
\brief  SetVersion - 




\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void inti :: SetVersion (uint16 version_nr )
{

  if ( IsPositioned() )
    if ( Save(YES,YES) )
      Cancel();

}

/******************************************************************************/
/**
\brief  SetWProtect - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical inti :: SetWProtect ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Setup - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

void inti :: Setup ( )
{



}

/******************************************************************************/
/**
\brief  i1 - 



\param  clnumb - 
\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

void inti :: Setup (EB_Number clnumb, int16 mbnumber )
{



}

/******************************************************************************/
/**
\brief  StructAttrEvents - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructAttrEvents"

logical inti :: StructAttrEvents (DB_Event intevent )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  StructureEvents - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructureEvents"

logical inti :: StructureEvents (DB_Event intevent )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical inti :: Unlock ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  inti - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  node_ptr - 
\param  strdefptr - 
\param  instptr - 
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "inti"

     inti :: inti (node *node_ptr, DBStructDef *strdefptr, void *instptr, logical crt_opt )
                     : sts (),
  iselarea(NULL),
  iselifo(NO),
  field_def(node_ptr ? node_ptr->GetFieldDef(NO) : NULL),
  struct_def(strdefptr),
  node_attr(),
  inst_index(AUTO)
{

BEGINSEQ
  SDBRESET
  
  if ( node_ptr )
    node_ptr->set_nodeinst(this);
    
  if ( InitArea(instptr) )                             ERROR
  
  if ( node_ptr )
  {
    if ( crt_opt && struct_def )
      if ( struct_def->CreateNodes(node_ptr,this,iselarea) )
                                                   ERROR
    node_ptr->fld::SetArea(iselarea);
  }
RECOVER


ENDSEQ
if ( ++inti_count > inti_max )
  inti_max = inti_count;
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "inti"

     inti :: inti ( )
                     : sts (),
  iselarea(NULL),
  iselifo(NO),
  field_def(NULL),
  struct_def(NULL),
  node_attr(),
  inst_index(AUTO)
{


if ( ++inti_count > inti_max )
  inti_max = inti_count;
}

/******************************************************************************/
/**
\brief  set_inst_index - 




\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_inst_index"

void inti :: set_inst_index (int32 lindx0 )
{

  inst_index = lindx0;

}

/******************************************************************************/
/**
\brief  set_iselarea - 




\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_iselarea"

void inti :: set_iselarea (void *instptr )
{

  if ( iselifo && iselarea )
  {
    msmfs((void **)&iselarea);
    iselifo = NO;    
  }
  iselarea = (char *)instptr;

}

/******************************************************************************/
/**
\brief  ~inti - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~inti"

     inti :: ~inti ( )
{

  inti::Close();


--inti_count;

}


