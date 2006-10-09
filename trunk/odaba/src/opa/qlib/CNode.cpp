/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CNode

\brief    Property Handle
          1.  "Alle"  Funktionen  sind  zu  ¸berarbeiten  f¸r not connection, da
          prophdl  aufgrung der  Dereferenzierung nicht  den Funktionsumfang von
          DBField  abdeckt, d.h. ggf. muﬂ die Funktionalit‰t mit local_ref (wenn
          nicht leer) oder prophdl aufgerufen werden.
          2.  Bei  Einf¸hrung  von  untergeordneten not connection PHs (z.B. f¸r
          Attribute)  f¸r  connection  PHs  muﬂ  in  "allen"  Funktionen gepr¸ft
          werden,  ob  und  wie  diese  mit  leerem  local_ref  und prophdl ohne
          highnod zurechtkommen.
          ******************
          Property  handle  are  used  to  manage  property  instances within an
          object  instance. They can be used also for managing extents, internal
          variables  or any other type of property. Property handle refer to the
          instance data as well as to the metadata (property definition).
          ********************
          Beschreibt  das DBField eine Collection in einer Datenbankinstanz oder
          einen  Extent, stehen neben den DBField-Funktionen alle Funktionen des
          PI-Handle zur Verf¸gung (siehe {.r PI}). 
          DBFields   kˆnnen   PI-basiert   konstruiert   werden,   wenn   die  
          Structure-Instanz,  in  der  sich  die  Property  befindet,  in  einem
          PI-Handle  verwaltet  wird.  In  diesem  Fall  wird mit dem Einstellen
          einer   neuen   Instanz   auch   die   Property-Instanz   im   DBField
          aktualisiert.  ƒnderungen im  DBField werden  in diesem Fall direkt an
          die  Structure-Instanz  des  PI-Handle  weitergeleitet. Damit entf‰llt
          die Modify-Anzeige durch den Entwickler. 
          Extent  oder PI-basierte DBFields sind mit einem Kontext ausgestattet.
          Damit  lˆsen diese DBFields  automatisch system- oder nutzerdefinierte
          Ereignisse  aus,  wenn  sie  ge‰ndert  oder  bereitgestellt  werden. 
          Auﬂerdem  ist  es  f¸r  kontextbezogene  DBFields  mˆglich,  Actions 
          auszulˆsen, die in diesem Kontext definiert sind (->ExecuteAction()).
          DBFields  sind nach auﬂen typneutral Felder,  d.h. der Typ wird intern
          verwaltet. 
          ********************
          Property  handles  support  standard  operations as +, - for different
          property  types, metadata operations and  a number of other functions.
          Property  handle  are  based  on  collection  handles  and provide all
          functionality  for  collection  handles,  especially when referring to
          reference properties.

\date     $Date: 2006/08/30 20:39:09,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CNode"

#include  <popa7.h>
#include  <cutimac.h>
#include  <sofifct.h>
#ifndef   DLL_CNode_HPP
#define   DLL_CNode_HPP
#include  <sCNode.hpp>
#include  <sDLL.h>
#endif
#include  <cDB_Event.h>
#include  <sACAttribute.hpp>
#include  <sACExtend.hpp>
#include  <sACObject.hpp>
#include  <sACTransientReference.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCACObject.hpp>
#include  <sCDictionary.hpp>
#include  <sCNode.hpp>
#include  <sCNodeAttribute.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCS_Handle.hpp>
#include  <sCTX_Base.hpp>
#include  <sClientConnection.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sInstBuffer.hpp>
#include  <sInstanceCache.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSimpleAction.hpp>
#include  <scinti.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <sCNode.hpp>


/******************************************************************************/
/**
\brief  Add - Add instance to collection



\return instptr - 

\param  indx0 - Position in collection
\param  sort_key - Sort key value
\param  ident_key - 
\param  initinst - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *CNode :: Add (int32 indx0, char *sort_key, char *ident_key, void *initinst, logical global_add )
{
  smcb         *skeysmcb;
  smcb         *idkeysmcb;
  DBStructDef  *strdef;
  logical       rerun   = YES;
  logical       term    = YES;
  void         *instptr = NULL;

#ifndef IF_Class  // client version
  
  if ( !Check(YES) && CheckAddSet() == NO )
  {
    LockSendParms();
    if ( nodeinst->stscini() || !Switch(AUTO) )	                             
    {    
      Initialize_intern(initinst);
      if ( !GenerateEvent(DBP_Insert) )
      {
        nodewrit = AUTO;
        if ( !Cnodeinst->before_add() )     // der inhalt der instanz ist hier zufaellig/nicht initialisiert
        {
          skeysmcb   = get_sortkey_smcb();
          idkeysmcb  = get_idkey_smcb();
          strdef     = nodeinst->get_struct_def();
          is_updated = NO; // 22.10.02  
      
          stssnof(); // node is acting
          while ( rerun )
          {
            Get_send_parms().Fill(indx0,                                      
                                  sort_key,skeysmcb ? skeysmcb : idkeysmcb,
                                  ident_key,idkeysmcb,
                                  initinst,strdef,nodeinst->GetSize(),
                                  initinst == nodeinst->get_iselarea() ? YES : NO,  // is_iselarea
                                  global_add );
                          
            if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Add_ci) )
              rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
            else
              term = Get_rec_result()[0].GetUChar();
          }
          stsrnof();
        }
      }
    }
    instptr = Inst_setup(term,YES);  // macht das DB_Inserted
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  void         *newinst;
  
  skeysmcb  = sc_prop->GetSortKeySMCB();
  idkeysmcb = sc_prop->GetKeySMCB();
  strdef    = sc_prop->GetCurrentTypeDef();
  newinst   = (*parms)[5].GetInstance(strdef,
                              sc_prop->Get_instarea(),
                              connection->get_conversion()).GetData();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( (*parms)[7].GetUChar() )                                      // is_iselarea
    {
      sc_prop->GetInitInstance();
      sc_prop->CopyInstance(newinst);
    }

    if ( (*parms)[8].GetUChar()  )        // global_add
    {
      if ( sc_prop->AddGlobal(
           (*parms)[0].GetLong(connection->get_conversion()),           // indx0
           (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,
                              sc_prop->Get_skeyarea(),
                              connection->get_conversion()).GetData(),  // sort_key
                                                                        // sort key name
           (*parms)[3].GetKey(idkeysmcb,
                              sc_prop->Get_idkeyarea(),
                              connection->get_conversion()).GetData(),  // ident_key
                                                                        // ident key name
           newinst)   )
        term = NO;
    }
    else                                 // local_add
    {
      if ( sc_prop->Add(
           (*parms)[0].GetLong(connection->get_conversion()),           // indx0
           (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,
                              sc_prop->Get_skeyarea(),
                              connection->get_conversion()).GetData(),  // sort_key
                                                                        // sort key name
           (*parms)[3].GetKey(idkeysmcb,
                              sc_prop->Get_idkeyarea(),
                              connection->get_conversion()).GetData(),  // ident_key
                                                                        // ident key name
           newinst)   )
        term = NO;
    }
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  AddReference - Add persistent instance



\return term - Termination code

\param  srcenode - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddReference"

logical CNode :: AddReference (node *srcenode, int32 lindx0 )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && !srcenode->Check(YES) )
  {
    LockSendParms();
    if ( srcenode->get_nodetype() != NT_ClientNode )
      SDBSET(99)
    else
    {
      if ( !Switch(AUTO) )
      {
        if ( !GenerateEvent(DBP_Insert) )
        {
          stssnof(); // node is acting
          while ( rerun )
          {
            Get_send_parms().Fill((CS_Handle *)Csrcenode,
                                  lindx0);
            if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_AddReference_ci0) )
              rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
            else
              term = Get_rec_result()[0].GetUChar();
          }
          stsrnof();
        }
      }
    }
    Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->pib::AddReference(
              *(pib *)((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer()),  // source_handle
              (*parms)[1].GetLong(connection->get_conversion()) );                   // lindx0
  sc_prop->FillInstResult(result,term);
  
  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  CNode - Create property handle



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
#define    MOD_ID  "CNode"

     CNode :: CNode (node *nodeptr, NodeTypes nodtype, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 intoff, PIACC accopt )
                     : bnode (),
  conversion(YES),
  data_nodetype(nodtype)
{

  Open(nodeptr,dbfield_ptr,highctx,instptr,accopt);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  obhandle - Database Object handle
\param  dbstructdef - 
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (ACObject *obhandle, DBStructDef *dbstructdef, char *key_name_w )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_ACTempExtent)
{

BEGINSEQ
  nodetype   = NT_ClientNode;
  csconnection = obhandle->GetClientACObject()->get_csconnection();
  
  object_ref    = obhandle;
  is_collection = YES;
  
  if ( InitTempExtent(dbstructdef,key_name_w) )            ERROR
    
  OpenAccessPath(obhandle,YES);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



\param  obhandle - Database Object handle
\param  dbextdef - Extent definition
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (ACObject *obhandle, DBExtend *dbextdef, PIACC accopt )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_ACTopNode)
{
  DBStructDef    *strdef;
  char            string[ID_SIZE+1];
  nodetype   = NT_ClientNode;
  bnode::Open(obhandle,NULL,dbextdef,NULL,accopt);
  csconnection = obhandle->GetClientACObject()->get_csconnection();
  
  if ( !memcmp(dbextdef->fmcbtype,"VOID ",5) )
  {
// wir m¸ssen noch sichern, daﬂ f¸r void-PIs keine sensitiven Attribute modifiziert werden!! das macht z.z. nur die Anwendung
//    nodeacc = PI_Read; f¸r Barto 23.1.02
    stssusr2();
  }
  
  OpenAccessPath(obhandle,NO);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  cnode_ref - 
\param  cnode_top - 
\param  path_opt - 
\param  accmode - 
\param  copy_selection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (CNode &cnode_ref, CNode &cnode_top, logical path_opt, PIACC accmode, logical copy_selection )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{

  nodetype      = NT_ClientNode;
  csconnection    = cnode_ref.get_csconnection();

  nodeacc       = PI_Update;
  object_ref    = cnode_ref.get_object_ref();
  nodeacc       = cnode_ref.GetMode(NO);
  nodenode      = NULL;
  
  OpenPathCopy(cnode_ref,cnode_top,path_opt,accmode,copy_selection);

}

/******************************************************************************/
/**
\brief  i04 - 



\param  cnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (CNode *cnodeptr )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{
// Base node constructor
  char       *extnames  = NULL;
  smcb       *smcbptr   = NULL;
  int32       offset    = 0;
BEGINSEQ
  nodetype      = NT_ClientNode;
  csconnection  = cnodeptr->get_csconnection();
  
  base_reference= cnodeptr;
  nodeacc       = cnodeptr->get_nodeacc();
  object_ref    = cnodeptr->get_object_ref();
  nodeacc       = cnodeptr->GetMode(NO);
  is_collection = YES;
  
  if ( !(extnames = cnodeptr->GetExtentName()) || !*extnames )
                                                     ERROR
  if ( *extnames == '.' )
  {
    set_prop_path(extnames);
    if ( !cnodeptr->get_nodenode() )      SDBERR(99)
      
    if ( !(nodefield = cnodeptr->get_nodenode()->GetCurrentTypeDef()->
                    SearchPathField(GetDictionary(),extnames+(extnames[1] == '.' ? 2 : 1),YES,&offset,NULL,&smcbptr)) )
                                                     SDBERR(99)
    global_instance = nodefield->IsGlobalInstance(GetDictionary(),DBStructDef::GetDBStruct(smcbptr));
  }
  else 
    global_instance = cnodeptr->IsGlobalInstance();

  OpenBaseNode();

  if ( *extnames == '.' )
    set_prop_path(extnames);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i05 - 



\param  nodeptr - 
\param  handle - 
\param  ctx_strnames - 
\param  proppath - 
\param  strnames - Type name
\param  sknames - 
\param  temp_opt - 
\param  weak_opt - 
\param  own_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (node *nodeptr, CS_Handle *handle, char *ctx_strnames, char *proppath, char *strnames, char *sknames, logical temp_opt, logical weak_opt, logical own_opt )
                     : bnode (), 
  conversion(YES),
  data_nodetype(NT_ACTopNode)
{
  ACObject      *obhandle;
  Dictionary    *dictptr;
  DBStructDef   *strdef;
  int32           offset;
BEGINSEQ
  if ( !nodeptr || !(obhandle = Bnodeptr->get_object_ref()) )
                                                     SDBERR(99)
  nodetype      = NT_ClientNode;
  csconnection    = obhandle->GetClientACObject()->get_csconnection();
  set_prop_path(proppath);
  is_collection = YES;
  
  if ( !memcmp(strnames,"VOID",4) )
    stssusr2();
  
  dictptr = obhandle->GetDictionary();
  if ( !ctx_strnames )
  {
    if ( temp_opt )
      if ( dictptr->Dictionary::CreateTempExtent(strnames,prop_path,sknames,NULL,weak_opt,own_opt) )
        nodefield = dictptr->ProvideExtendDef(prop_path);
  }
  else
    if ( strdef = dictptr->ProvideStructDef(ctx_strnames) )
      nodefield = (DBFieldDef *)strdef->SearchField(prop_path,&offset);
  if ( !nodefield )                                  ERROR
  
  if ( bnode::Open(Bnodeptr->get_object_ref(),NULL,nodefield,
                   NULL,Bnodeptr->get_nodeacc()) )    ERROR
  InitHandle();
  SetServerObject(handle->GetServerObject()); 

  if ( strdef = nodefield->GetDBStruct(dictptr) )
  {
    id_key = strdef->smcbidky;
    if ( !nodeinst )                                  
      if ( InitInti(strdef,NULL) )                   ERROR
  }
  if ( sknames )
    sk_index = nodefield->GetIndexDef(sknames);
  
  is_opened = YES;
  GenerateEvent(DBO_Opened);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i06 - 



\param  nodeptr - 
\param  handle - 
\param  proppath - 
\param  fldtypes - Property type
\param  nsid - 
\param  fldreflev - Property reference level
\param  fldsize - Size of property
\param  fldprec - Precision of property
\param  flddim - Dimension of property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (node *nodeptr, CS_Handle *handle, char *proppath, char *fldtypes, int32 nsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim )
                     : bnode(Bnodeptr->get_object_ref(),nodeptr,proppath,fldtypes,nsid,fldreflev,fldsize,fldprec,flddim), 
  conversion(YES),
  data_nodetype(NT_Node)
{
  DBFieldDef   *dbfield_ptr;
BEGINSEQ
  SDBCERR
  if ( !object_ref || !(dbfield_ptr = GetInstFieldDef()) )
                                                     SDBERR(99)
  nodetype   = NT_ClientNode;
  csconnection = object_ref->GetClientACObject()->get_csconnection();
  
  InitHandle();
  SetServerObject(handle->GetServerObject()); 
    
  if ( ! nodefield )
    nodefield = dbfield_ptr;

  if ( dbfield_ptr->GetDBStruct() )
    id_key = dbfield_ptr->GetDBStruct()->smcbidky;
  is_opened = YES;
  GenerateEvent(DBO_Opened);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i09 - 



\param  cnode_ref - 
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (CNode &cnode_ref, char *expression )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)

{

  nodetype = NT_ClientNode;
  InitPathNode(cnode_ref,expression);

}

/******************************************************************************/
/**
\brief  i10 - 



\param  obhandle - Database Object handle
\param  op_type - 
\param  rule - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (ACObject *obhandle, ST_OpCodes op_type, char *rule )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{

  nodetype = NT_ClientNode;
  bnode::Open(obhandle,NULL,NULL,NULL,PI_Update);

  csconnection  = obhandle->GetClientACObject()->get_csconnection();
  
  nodeacc       = PI_Update;
  object_ref    = obhandle;
  is_collection = YES;
    
  OpenOperationNode(obhandle,op_type,rule);

}

/******************************************************************************/
/**
\brief  i11 - 



\param  obhandle - Database Object handle
\param  op_type - 
\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (ACObject *obhandle, ST_OpCodes op_type, BNFData *bnf_data )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{

  nodetype = NT_ClientNode;
  bnode::Open(obhandle,NULL,NULL,NULL,PI_Update);
  csconnection    = obhandle->GetClientACObject()->get_csconnection();
  
  nodeacc       = PI_Update;
  object_ref    = obhandle;
  is_collection = YES;
    
  OpenOperationNode(obhandle,op_type,bnf_data->GetStringValue(NULL,NULL));

}

/******************************************************************************/
/**
\brief  i12 - 



\param  cnode_ref - 
\param  op_type - 
\param  rule - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (CNode &cnode_ref, ST_OpCodes op_type, char *rule )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{

  nodetype      = NT_ClientNode;
  csconnection    = cnode_ref.get_csconnection();
  
  nodeacc       = PI_Update;
  object_ref    = cnode_ref.get_object_ref();
  nodenode      = &cnode_ref;
  is_collection = YES;
    
  OpenOperationNode(cnode_ref,op_type,rule);

}

/******************************************************************************/
/**
\brief  i13 - 



\param  cnode_ref - 
\param  op_type - 
\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (CNode &cnode_ref, ST_OpCodes op_type, BNFData *bnf_data )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{

  nodetype      = NT_ClientNode;
  csconnection    = cnode_ref.get_csconnection();
  
  nodeacc       = PI_Update;
  object_ref    = cnode_ref.get_object_ref();
  nodenode      = &cnode_ref;
  is_collection = YES;
    
  OpenOperationNode(cnode_ref,op_type,bnf_data->GetStringValue(NULL,NULL));

}

/******************************************************************************/
/**
\brief  i14 - 



\param  obhandle - Database Object handle
\param  bnf_data - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (ACObject *obhandle, BNFData *bnf_data, PIACC accopt )
                     : bnode (),
  conversion(YES),
  data_nodetype(NT_undefined)
{

  nodetype      = NT_ClientNode;
  csconnection    = obhandle->GetClientACObject()->get_csconnection();
  
  nodeacc       = accopt;
  object_ref    = obhandle;
  set_prop_path(bnf_data->GetStringValue(NULL,NULL));
  is_collection = YES;
    
  OpenAccessPath(obhandle,NO);

}

/******************************************************************************/
/**
\brief  i15 - 



\param  obhandle - Database Object handle
\param  expression - Expression
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (ACObject *obhandle, char *expression, PIACC accopt )
                     : bnode(),
  conversion(UNDEF),
  data_nodetype(NT_undefined)
{

  nodetype      = NT_ClientNode;
  csconnection  = obhandle->GetClientACObject()->get_csconnection();
  
  nodeacc       = accopt;
  object_ref    = obhandle;
  set_prop_path(expression);
  is_collection = YES;
    
  OpenAccessPath(obhandle,NO);

}

/******************************************************************************/
/**
\brief  i6 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode ( )
                     : bnode (),
  conversion(UNDEF),
  data_nodetype(NT_undefined)
{

  nodetype = NT_ClientNode;



}

/******************************************************************************/
/**
\brief  i7 - 



\param  cnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CNode"

     CNode :: CNode (CNode &cnode_ref )
                     : bnode (cnode_ref),
  conversion(cnode_ref.get_conversion()),
  data_nodetype(cnode_ref.get_data_nodetype())
{

  nodetype   = NT_ClientNode;
  csconnection = cnode_ref.get_csconnection();
  switch ( data_nodetype )
  {
    case  NT_ACAttribute          : 
    case  NT_ACBaseStruct         : nodeinst = cnode_ref.get_nodeinst();
                                    nodecur = cnode_ref.get_nodecur();
                                    if ( !IsActive() )
                                    {
                                      is_opened = YES;
                                      InitHandle();
                                    }
                                    else
                                      OpenCopyNode(cnode_ref);
                                    break;
    case  NT_ACOPView             : InitPathNode(cnode_ref);
                                    break;
    case  NT_ACGenericAttr        : 
    case  NT_ACShareBase          : 
    case  NT_ACReference          :
    case  NT_ACRelationship       : 
    case  NT_ACTransientReference : 
    default                       : OpenCopyNode(cnode_ref);
  }



}

/******************************************************************************/
/**
\brief  CSAClosed - 




\param  parmstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAClosed"

void CNode :: CSAClosed (char *parmstring )
{

  bnode::CSAClosed(parmstring);
  stsserr();
  stsslck();

}

/******************************************************************************/
/**
\brief  CSADirty - 




\param  parmstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSADirty"

void CNode :: CSADirty (char *parmstring )
{

  is_dirty = YES;

}

/******************************************************************************/
/**
\brief  CanUpdateCollection - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanUpdateCollection"

logical CNode :: CanUpdateCollection (logical chknode )
{
  logical                 cond = NO;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( nodenode && nodenode->IsInitInstance() )
      cond = bnode::CanUpdateCollection(NO);
    else
    {
      LockSendParms().Fill();
      if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CanUpdateCollection_ci) )
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(cond);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  sc_prop->CheckInstance();
  cond = sc_prop->IsCollectionUpdate();
   
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Cancel - Cancel selection

        The  function resets modifications made on  the instance and cancels the
        selection.

\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical CNode :: Cancel (logical chknode )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(NO,NO)  )
  {
    if ( chknode && inti_buffer )
      inti_buffer->Cancel();
    
    term = NO;
    if ( is_opened && IsPositioned() )
    {
      term = YES;
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Cancel_ci0) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
    ResetInstance();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->Cancel();
   
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ChangeBuffer - Change collection buffer count



\return buffnum - Number of instance buffers

\param  buffnum - Number of instance buffers
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeBuffer"

int16 CNode :: ChangeBuffer (int16 buffnum )
{
  logical     rerun       = YES;
  int16       new_buffnum = AUTO;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    Switch(AUTO);
    
    while ( rerun )
    {
      LockSendParms().Fill(buffnum);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ChangeBuffer_ci0) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        new_buffnum = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
    }
    if ( new_buffnum > 1 )
    {
      SetSysVariable("MAX_BUFFER_SIZE","");
      if ( bnode::ChangeBuffer(new_buffnum) != new_buffnum )
      {
        SDBSET(99)
        new_buffnum = AUTO;
      }
    }
  }
  return(new_buffnum);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    new_buffnum = sc_prop->ChangeBuffer((*parms)[0].GetShort(connection->get_conversion()));  // buffnum
  
  result->Fill(new_buffnum);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ChangeMode - Change access mode



\return oldmode - 

\param  newmode - 
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC CNode :: ChangeMode (PIACC newmode, char chkopt )
{
  PIACC    oldmode = PI_undefined;
  logical  rerun   = YES;

#ifndef IF_Class  // client version

  if ( !chkopt || !Check(YES,NO) )
  {
    if ( !Switch(AUTO) )
    {
      while ( rerun )
      {
        LockSendParms().Fill((int32)newmode);
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ChangeMode_ci0) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          oldmode = (PIACC)Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
    ChangeMode_intern(oldmode == PI_undefined ? YES : NO,newmode);
  }
  return(oldmode);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    oldmode =  sc_prop->ChangeMode((PIACC)
                            (*parms)[0].GetLong(connection->get_conversion()) ); 
     
  result->Fill((int32)oldmode);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ChangeMode_intern - 




\param  error_case - Error indication
\param  newmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode_intern"

void CNode :: ChangeMode_intern (logical error_case, PIACC newmode )
{

  ResetInstance();
  
  if ( !error_case )
  {
    nodeacc = newmode;
    if ( nodeinst )
      nodeinst->ChangeMode(newmode);
  }


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

logical CNode :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
BEGINSEQ
  if ( stscusr3() )                                  LEAVESEQ  // kommt gerade aus Check
  if ( stscerr() )                                   ERROR
  if ( !csconnection )                               SDBERR(517)
  conversion = csconnection->get_conversion();
  
  if ( autoini  )
  {
    if ( !is_opened )
    {
      if ( !nodenode )                               SDBERR(99)
      if ( GetServerObject() )
        Reopen_intern();
      else
      {
        if ( nodenode->Check(YES,NO) )               ERROR
        if ( OpenSubNode() )                         ERROR
      }
    }
    if ( autoini && !server_object )                 SDBERR(538)
    stssfil();
  }

// this might be to ofton, new on 22.2.2005
  if ( is_dirty )
    Reset();
    
  if ( bnode::Check(autoini,acccheck) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical CNode :: CheckModify ( )
{
  CNode     *high_cnode;
  int        auto_attr_type = AUTO;
  logical    term = NO;
BEGINSEQ
  if ( IsAttribute() )
  {
    if ( IsTransient() )                             LEAVESEQ
    
    if ( !nodenode )                                 LEAVESEQ
    if ( nodenode->CheckModify() )                   ERROR
    if ( nodewrit != 255 )         
      if ( Cnodenode->get_data_nodetype() == NT_ACGenericAttr )
        Cnodenode->SetGenKey(AUTO);                       // SetKey((char *)&auto_attr_type,NULL);  
      
//    if ( nodenode && nodenode->CheckModify() )       ERROR
    LEAVESEQ
  }  
    
  if ( data_nodetype == NT_ACGenericAttr )
    SetGenKey(AUTO);  
  else
    if ( !IsWrite() && !nodeinst->stscini() )        SDBERR(76)
  
  if ( nodewrit != 255 )         
  {  
    if ( high_cnode = Cnodenode )
      if ( high_cnode->get_data_nodetype() == NT_ACGenericAttr ||
           ( (high_cnode = (CNode *)nodenode->get_nodenode() ) && 
           high_cnode->get_data_nodetype() == NT_ACGenericAttr)   )
        if ( !high_cnode->IsPositioned() && high_cnode->get_nodenode()->IsPositioned() )
          high_cnode->get_nodenode()->SetGenAttribute(high_cnode->get_prop_path(),AUTO,NULL);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckReadOnly - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckReadOnly"

logical CNode :: CheckReadOnly ( )
{
  logical                 cond = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms().Fill();
           
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CheckReadOnly_ci) )
      cond = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(cond);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  cond = sc_prop->IsReadOnly();  
  
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  CheckSKey_intern - Check for Sort key



\return keysmcb - 

\param  seterr_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckSKey_intern"

smcb *CNode :: CheckSKey_intern (logical seterr_opt )
{
  smcb        *keysmcb = NULL;
  if ( !(keysmcb = get_sortkey_smcb()) &&
       !(keysmcb = get_idkey_smcb())       ) 
    if ( seterr_opt )                                SDBSET(71)
      
// function returns an error for VOID-Extents

  return(keysmcb);
}

/******************************************************************************/
/**
\brief  CheckWProtect - Is current instance permanent write protected?



\return wpt - Write protect indication for persistant instance

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical CNode :: CheckWProtect ( )
{
  logical    wpt = NO;
#ifndef IF_Class  // client version

  if ( IsPositioned() )
  {
    LockSendParms().Fill();
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CheckWProtect_ci0) )
      wpt = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(wpt);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  sc_prop->CheckInstance();
  wpt = sc_prop->CheckWProtect();
   
  result->Fill(wpt);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Close - Close Property Handle

        The  function will close the property  handle without destroying it. The
        handle can be re-opend later again.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical CNode :: Close ( )
{
  logical   term = NO;
#ifndef IF_Class  // client version

  if ( nodeidnt == NODE_ID )
  {
    if ( csconnection && !Check(NO,NO) && GetServerObject() ) // csconnection-pruefung, damit Check keinen fehler setzt
    {
      Switch(AUTO);
      LockSendParms().Fill();
    
      if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Close_ci0) )
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
    Close_intern();
  }
  return(term);
  
#else             // server version
  
  ((SC_Property *)cso_ptr)->SetClientObject(0);
  term = ((SC_Property *)cso_ptr)->Remove();
  
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Close_intern - Close instance intern




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close_intern"

void CNode :: Close_intern ( )
{

  DLL(CNode)    *topnode_lst;

  if ( !nodenode && object_ref &&
       (topnode_lst = object_ref->GetClientACObject()->get_topnode_list()) )
    if ( topnode_lst->Find(this) )
      topnode_lst->RemoveAt();
  
  if ( origin ) // copy node
  {
    switch ( data_nodetype )
    {
      case  NT_ACAttribute          : 
      case  NT_ACBaseStruct         : nodeinst = NULL;
      default                       : break;
    }
  }
  else // original node
  {
    switch ( data_nodetype )
    {
      case  NT_ACTopNode            : if ( is_codeset )
                                        RemoveField();
      default                       : break;
    }
  }
  bnode::Close();
  UninitHandle();  
  
  


}

/******************************************************************************/
/**
\brief  Contains - 



\return cond - 

\param  reg_string - 
\param  case_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Contains"

logical CNode :: Contains (char *reg_string, logical case_opt )
{
  logical     rerun = YES;
  logical     cond  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(reg_string,                  // regular expression
                            case_opt);                   // case sensitive option
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Contains_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        cond = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(cond);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( !(rerun = sc_prop->CheckInstance()) )
    cond = sc_prop->Contains(
              (*parms)[0].GetString(),         // regular expression
              (*parms)[1].GetUChar() );        // case sensitive option
  
  result->Fill(cond);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  CopyInst - Copy instance



\return instptr - 

\param  srcenode - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  set_pos0_w - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInst"

void *CNode :: CopyInst (node *srcenode, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical chknode )
{
  smcb         *skeysmcb;
  smcb         *idkeysmcb;
  void         *instptr = NULL;
  logical       rerun   = YES;
  logical       term    = YES;

BEGINSEQ
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( csconnection != Csrcenode->get_csconnection() )
      instptr = bnode::CopyInst(srcenode,db_replace,copy_type,w_newkey,set_pos0_w,chknode);
    else
    {
      if ( !Switch(AUTO) )
      {
        skeysmcb  = get_sortkey_smcb();
        idkeysmcb = get_idkey_smcb();
      
        stssnof(); // node is acting
        while ( rerun )
        {
          Get_send_parms().Fill((CS_Handle *)Csrcenode,                                      
                                Key(w_newkey),skeysmcb ? skeysmcb : idkeysmcb,
                                set_pos0_w,
                                (int32)db_replace,
                                (int32)copy_type);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CopyInst_ci) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
        stsrnof();
      }
    }
    if ( !instptr )
      instptr = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  skeysmcb  = sc_prop->GetSortKeySMCB();
  idkeysmcb = sc_prop->GetKeySMCB();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    sc_prop->Copy(
      *(SC_Property *)(*parms)[0].GetHandle()->GetServerPointer(),     // srcenode
      (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,              // w_new_key
                         sc_prop->Get_skeyarea(),
                         connection->get_conversion()).GetData(),     
      (*parms)[3].GetLong(connection->get_conversion()),               // set_pos0
      (PIREPL)(*parms)[4].GetLong(connection->get_conversion()),       // db_replace
      (PIREPL)(*parms)[5].GetLong(connection->get_conversion())        // copy_type
                );
  
    term = SDBERROR ? YES : NO;
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CopySet - Copy collection



\return count - 

\param  srcenode - 
\param  check_inverse - 
\param  db_replace - Replace option
\param  copy_type - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySet"

int32 CNode :: CopySet (node *srcenode, logical check_inverse, PIREPL db_replace, PIREPL copy_type, logical chknode )
{
  int32      count = ERIC;
  logical   rerun = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( srcenode->get_nodetype() != NT_ClientNode || csconnection != Csrcenode->get_csconnection() )
      count = bnode::CopySet(srcenode,check_inverse,db_replace,copy_type,chknode);
    else
    {
      if ( !Switch(AUTO) )
      {
        stssnof(); // node is acting
        while ( rerun )
        {
          LockSendParms().Fill((CS_Handle *)Csrcenode,   
                                check_inverse,                                   
                                (int32)db_replace,
                                (int32)copy_type);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_CopySet_ci) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            count = Get_rec_result()[0].GetLong(conversion);
          UnlockSendParms();
        }
        stsrnof();
      }
      ResetInstance();
    }
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->CopySet(
      *(SC_Property *)(*parms)[0].GetHandle()->GetServerPointer(),     // srcenode
      (PIREPL)(*parms)[2].GetLong(connection->get_conversion()),       // db_replace
      (PIREPL)(*parms)[3].GetLong(connection->get_conversion()),       // copy_type
      (PIREPL)(*parms)[1].GetUChar()                                   // check_inverse
                );
  result->Fill(count);

  return(rerun);

#endif
  return(count);
}

/******************************************************************************/
/**
\brief  CreateAccessPath - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  prop_path - Property path
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *CNode :: CreateAccessPath (char *prop_path, OperEnvironment *operenv )
{
  CNode                   *nodeptr = NULL;
BEGINSEQ
  nodeptr = new CNode(*this,prop_path);            SDBCERR



RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  bnf_data - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *CNode :: CreateAccessPath (BNFData *bnf_data, OperEnvironment *operenv )
{

  return( CreateAccessPath(bnf_data->StringValue(),operenv) );


}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *CNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new CNode(*this) ) )              SDBERR(95)
                                                     SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateInti - 



\return intiptr - 

\param  nodeptr - 
\param  strdef_ptr - Internal data structure definition
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *CNode :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti     *intiptr = NULL;
BEGINSEQ
  if ( !(intiptr = new cinti(nodeptr,strdef_ptr,instptr,init_nodes)) )
                                                      SDBERR(95)
                                                      SDBCERR

RECOVER
  delete intiptr;
  intiptr = NULL;
ENDSEQ
  return(intiptr);
}

/******************************************************************************/
/**
\brief  CreatePathNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  path_prop - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *CNode :: CreatePathNode (char *path_prop, OperEnvironment *operenv )
{

  return( CreateAccessPath(prop_path,operenv) );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  bnf_data - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *CNode :: CreatePathNode (BNFData *bnf_data, OperEnvironment *operenv )
{

  return( CreateAccessPath(bnf_data,operenv) );


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

node *CNode :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{
  node    *subnode = NULL;
BEGINSEQ
  switch ( nodtype )
  {
    case  NT_ACTransientReference : 
              subnode = new ACTransientReference(nodeptr,dbfield_ptr,highctx,accopt);
              break;
    case  NT_ACAttribute          : 
    case  NT_ACBaseStruct         : 
              if ( !dbfield_ptr->IsActive() )
              {
                subnode = new CNodeAttribute(nodeptr,nodtype,dbfield_ptr,highctx,instptr,intoff,accopt);
                break;
              }
    default : subnode = new CNode(nodeptr,nodtype,dbfield_ptr,highctx,instptr,intoff,accopt);
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
\brief  Delete - Delete/remove instance from collection



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  sort_key - Sort key value
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical CNode :: Delete (char *sort_key, logical chknode )
{
  smcb       *keysmcb;
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  int32        obj_id = objid;
  
  if ( !Check(YES) )
  {
    if ( !GenerateEvent(DBP_Remove) )
    {
      if ( keysmcb = CheckSKey_intern() )
      {  
        while ( rerun )
        {
          LockSendParms().Fill(sort_key,keysmcb);  // sort_key + keynames
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Delete_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
          UnlockSendParms();
        }
      }
      if ( !term) 
      {
        ResetInstance();
        if ( origin )
          origin->ResetCopyNodes(this,obj_id);
        else
          ResetCopyNodes(this,obj_id); 
      }
      else
        RecoverSelection(obj_id);  // generates Read-event
      GenerateEvent(term ? DBO_NotRemoved : DBO_Removed);
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(keysmcb = sc_prop->CheckSKey((*parms)[1].GetString())) )
    rerun = NO;
  else   
    if ( !(rerun = sc_prop->CheckInstance()) )
      term = sc_prop->Delete(
          (*parms)[0].GetKey(keysmcb,
                             sc_prop->Get_skeyarea(),
                             connection->get_conversion()).GetData()  // sort_key
                            );                                       
  
  result->Fill(term);

  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  ci1 - 



\param  set_pos0_w - 
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical CNode :: Delete (int32 set_pos0_w, logical chknode, logical del_dep, logical del_inst )
{
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  int32         obj_id = objid;
  
  if ( !Check(YES) )
  {
    if ( !GenerateEvent(DBP_Remove) )
    {
      stssnof(); // node is acting
      while ( rerun )
      {
        LockSendParms().Fill(set_pos0_w,del_dep,del_inst);
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Delete_ci1) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
      stsrnof();
      if ( !term) 
      {
        ResetInstance();
        if ( origin )
          origin->ResetCopyNodes(this,obj_id);
        else
          ResetCopyNodes(this,obj_id); 
      }
      else
        RecoverSelection(obj_id);  // generates Read-event
      GenerateEvent(term ? DBO_NotRemoved : DBO_Removed);
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->Delete(
        (*parms)[0].GetLong(connection->get_conversion()),  // indx0
        (*parms)[1].GetUChar(),                             // del_dep
        (*parms)[1].GetUChar() );                           // del_inst
  
  result->Fill(term);

  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteSet - Delete/remove all instance in a collection



\return term - Termination code

\param  chknode - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSet"

logical CNode :: DeleteSet (logical chknode, logical del_dep )
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    stssnof(); // node is acting
    while ( rerun )
    {
      LockSendParms().Fill(del_dep);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_DeleteSet_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
    stsrnof(); 
    ResetInstance();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->DeleteSet(
        (*parms)[0].GetUChar() );                // del_dep
  
  result->Fill(term);

  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  DisableKeyCheck - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableKeyCheck"

logical CNode :: DisableKeyCheck (logical chknode )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES,NO) )
  {
    term = NO;
    if ( is_opened )
    {
      term = YES;
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_DisableKeyCheck_ci0) )
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->DisableKeyCheck();
   
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Duplicate - 



\return instptr - 

\param  keyptr - 
\param  db_replace - Replace option
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Duplicate"

void *CNode :: Duplicate (char *keyptr, PIREPL db_replace, logical chknode )
{
  Instance     ph_inst = NULL;
  smcb        *keysmcb = NULL;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( Exist() )
  {
    LockSendParms();
    if ( (keysmcb = CheckSKey_intern()) )
    {
      if ( !Save(NO,NO) )
      {
        stssnof(); // node is acting
        while ( rerun )
        {
          Get_send_parms().Fill(keyptr,keysmcb,(int32)db_replace);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Duplicate_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
        stsrnof();
      }
    }
    ph_inst = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(&ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  sc_prop->CheckInstance();
  if ( !(keysmcb = sc_prop->GetSortKeySMCB()) )
    keysmcb = sc_prop->GetKeySMCB();
  
  term = !sc_prop->Duplicate(
              (*parms)[0].GetKey(keysmcb,
                                 sc_prop->Get_skeyarea(),
                                 connection->get_conversion()).GetData(),   // sort_key
              (PIREPL)(*parms)[1].GetLong(connection->get_conversion()) );  // repl_opt
  
  sc_prop->FillInstResult(result,term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  EnableKeyCheck - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableKeyCheck"

logical CNode :: EnableKeyCheck (logical chknode )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES,NO) )
  {
    term = NO;
    if ( is_opened )
    {
      term = YES;
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_EnableKeyCheck_ci0) )
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->EnableKeyCheck();
   
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ExecPropCtxFunc - Execute action on property (collection) level

        The  function calls an action that  is defined in theproperty context of
        the property handle. The function is executed on the server side.

\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecPropCtxFunc"

logical CNode :: ExecPropCtxFunc (char *fnames, char *w_parms )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(fnames,w_parms);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ExecPropCtxFunc_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        if ( !(term = Get_rec_result()[0].GetUChar()) )
        {
          set_result_string(Get_rec_result()[1].GetString(),UNDEF);
          term = bnode::ExecPropCtxFunc(fnames,w_parms);   // Client kann Ergebnis ¸berschreiben
        }
      UnlockSendParms();
    }
  }
  if ( is_dirty )
    Reset();
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  char         *result_str = NULL;
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    if ( !( term = sc_prop->ExecutePropertyAction(
                            (*parms)[0].GetString(),        //  action_name
                            (*parms)[1].GetString()         //  parameter string
            )) )
      result_str = sc_prop->GetActionResult();
   
  result->Fill(term,result_str);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ExecStrCtxFunc - Execute action on instance level

        The  function calls an  action that is  defined in the structure context
        of the current instance. The function is executed on the server side.

\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecStrCtxFunc"

logical CNode :: ExecStrCtxFunc (char *fnames, char *w_parms )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(fnames,w_parms);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ExecStrCtxFunc_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        if ( !(term = Get_rec_result()[0].GetUChar()) )
        {
          set_result_string(Get_rec_result()[1].GetString(),UNDEF);
          term = bnode::ExecStrCtxFunc(fnames,w_parms);  // Client kann Ergebnis ¸berschreiben
        }
      UnlockSendParms();
    }
  }
  if ( is_dirty )
    Reset();
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  char         *result_str = NULL;
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    if ( !( term = sc_prop->ExecuteInstanceAction(
                            (*parms)[0].GetString(),        //  action_name
                            (*parms)[1].GetString()         //  parameter string
            )) )
      result_str = sc_prop->GetActionResult();
   
  result->Fill(term,result_str);
  
  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  FirstKey - 



\return sort_key - Sort key value

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *CNode :: FirstKey (logical chknode )
{
  char       *sort_key;
  char       *keyptr = NULL;
  logical     rerun = YES;

  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    LockSendParms();
    if ( !Switch(AUTO) )
    {
      while ( rerun )
      {
        Get_send_parms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_FirstKey_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
    }
    sort_key = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(sort_key);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = (keyptr = sc_prop->FirstKey()) ? NO : YES;
  sc_prop->FillKeyResult(result,keyptr,term);

  return(term);

#endif
  return(sort_key);
}

/******************************************************************************/
/**
\brief  Get - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *CNode :: Get (int32 lindx0, logical chknode )
{
  void        *instptr = NULL;
  logical      rerun   = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( !(instptr = Get_optimized(lindx0,chknode)) )
    {
      LockSendParms();
      if ( csconnection && !Switch(AUTO) )
      {
        while ( rerun )
        {
          Get_send_parms().Fill(lindx0);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Get_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = NO;
        }
      }
      instptr = Inst_setup(term);
      UnlockSendParms();
    }
    if ( instptr )
      GenerateEvent(DBO_Read);
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->Get((*parms)[0].GetLong(connection->get_conversion())) ? NO : YES;  // indx0
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ci1 - 



\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *CNode :: Get (char *skey, logical chknode )
{
  void        *instptr = NULL;
  smcb        *keysmcb;
  char         wskey[MAX_KEYLEN];
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) && skey )
  {
    if ( stscusr2() )                        // VOID-Extent
      instptr = Get_ByID(skey);
    else
    {
      SaveKey(wskey,skey);
      if ( !(instptr = bnode::Get_optimized(skey)) )
      {
        if ( nodefield->fmcbdim != 1          &&
             (keysmcb = CheckSKey_intern())       )
        {  
          if ( inti_buffer )
          {
            if ( instptr = GetBuffer(skey,0) ) 
              Cnodeinst->SetupInst(nodecur,objid,UNDEF,YES);
          }
          else if ( csconnection && !Switch(AUTO) )
          {
            LockSendParms();
            while ( rerun )
            {
              Get_send_parms().Fill(wskey,keysmcb);           // sort_key + keynames
              if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Get_ci1) )
                rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
              else
                term = NO;
            }
            instptr = Inst_setup(term);
            UnlockSendParms();
          }
        }
        if ( instptr )
          GenerateEvent(DBO_Read);
        if ( instptr && cache_list )
          cache_list->AddEntry(nodeinst);    
      }
    }
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(keysmcb = sc_prop->CheckSKey((*parms)[1].GetString())) )
    rerun = NO;
  else
    if ( !(rerun = sc_prop->CheckInstance()) )
      term = sc_prop->Get(
                (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData())  // sort_key
             ? NO : YES;
   
  sc_prop->FillInstResult(result,term);
  
  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetBaseNode - 



\return nodepptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseNode"

node **CNode :: GetBaseNode ( )
{
  node    *nodeptr;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
    
  if ( !base_node )
  {
    base_node = new CNode(this); // base node constructor
    if ( !((bnode *)base_node)->get_nodefield() )    ERROR
  }
  if ( Exist() )
    ((bnode *)base_node)->ValidatePosition(YES);
  
  if ( sk_index && sk_index->get_key_def() )
    if ( ((bnode *)base_node)->get_nodefield()->GetIndexDef((char *)sk_index->GetKeyName()) )
      base_node->SetOrder((char *)sk_index->GetKeyName(),UNDEF,NULL);
RECOVER
  delete base_node;
  base_node = NULL;
ENDSEQ
  return( (node **) &base_node );
}

/******************************************************************************/
/**
\brief  GetCollectionID - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollectionID"

int32 CNode :: GetCollectionID ( )
{
  logical     rerun = YES;
  int32       coll_id = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( IsAttribute() )
      coll_id = nodefield->fmcbdim;
    else
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetCollectionID_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          coll_id = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
  }
  return(coll_id);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    coll_id = sc_prop->GetCollectionID();
  
  result->Fill(coll_id);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetCount - Get number of instances stored for property



\return count - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 CNode :: GetCount (logical chknode )
{
  logical     rerun = YES;
  int32        count = ERIC;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( IsAttribute() )
      count = nodefield->fmcbdim;
    else
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetCount_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->GetCount();
  
  result->Fill(count);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetExtentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentNode"

node *CNode :: GetExtentNode ( )
{

  if ( !base_node )
    GetBaseNode();
  return(base_node);
}

/******************************************************************************/
/**
\brief  GetGenAttrType - Get generic attribute type



\return attrtype - 

\param  w_propnames - Property path or name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrType"

int CNode :: GetGenAttrType (char *w_propnames )
{
  logical     rerun    = YES;
  int32        attrtype = UNDEF;

#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun)
    {
      LockSendParms().Fill(w_propnames);    
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetGenAttrType_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        attrtype = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(attrtype);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    attrtype = sc_prop->GetGenAttrType(
                          (*parms)[0].GetString() ); // w_propnames
  result->Fill(attrtype);

  return(rerun);

#endif
  return(attrtype);
}

/******************************************************************************/
/**
\brief  GetGenOrderType - Get current type for generic sort order of collection handle



\return attrtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenOrderType"

int CNode :: GetGenOrderType ( )
{
  logical     rerun    = YES;
  int32        attrtype = UNDEF;

#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill();    
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetGenOrderType_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        attrtype = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(attrtype);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    attrtype = sc_prop->GetGenOrderType();
  
  result->Fill(attrtype);

  return(rerun);

#endif
  return(attrtype);
}

/******************************************************************************/
/**
\brief  GetGlobalID - 



\return obident - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

EB_Number CNode :: GetGlobalID ( )
{
  logical      rerun   = YES;
  DBStructDef *strdef;
  int32         obident = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    strdef    = nodeinst->get_struct_def();
      
    while ( rerun )
    {
      LockSendParms().Fill(nodeinst->get_iselarea(),strdef,nodeinst->GetSize());
      
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetGlobalID_ci0) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  strdef       = sc_prop->GetCurrentTypeDef();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( !sc_prop->CopyInstance((*parms)[0].GetInstance(strdef,
                                sc_prop->Get_instarea(),
                                connection->get_conversion()).GetData()  // instance
                     ) )
      obident = sc_prop->GetGlobalID();
  }
    
  result->Fill(obident);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetID - 



\return obident - 
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  lindx0 - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number CNode :: GetID (int32 lindx0, logical chknode, logical pif_opt )
{
  logical     rerun   = YES;
  int32        obident = UNDEF;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( nodecur >= 0 && objid > 0 && (lindx0 == AUTO || lindx0 == nodecur) )
      obident = objid;
    else  
    {
      while ( rerun )
      {
        LockSendParms().Fill(lindx0);   // indx0
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetID_ci0) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    obident = sc_prop->GetID(
                       (*parms)[0].GetLong(connection->get_conversion()));    // indx0
  
  result->Fill(obident);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ci1 - 



\param  keyptr - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number CNode :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  smcb       *keysmcb;
  logical     rerun   = YES;
  int32        obident = UNDEF;

#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( IsPositioned() )
      obident = objid;
    else if ( stscusr2() )               // VOID-Extent
    {
      obident = GetID_ByID(keyptr).get_ebsnum();
    }
    else if ( keysmcb = CheckSKey_intern() )
    {  
      while ( rerun )
      {
        LockSendParms().Fill(keyptr,keysmcb); // sort_key + keynames
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetID_ci1) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
    }
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
   
  if ( !(keysmcb = sc_prop->CheckSKey((*parms)[1].GetString())) )
    rerun = NO;
  else
    if ( !(rerun = sc_prop->CheckInstance()) )
      obident = sc_prop->GetID((*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData()); // sort_key
  
  result->Fill(obident);

  return(rerun);

#endif
  return(obident);
}

/******************************************************************************/
/**
\brief  GetID_ByID - 



\return obident - 

\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID_ByID"

EB_Number CNode :: GetID_ByID (char *keyptr )
{
  smcb       *keysmcb;
  logical     rerun   = YES;
  int32        obident = UNDEF;

#ifndef IF_Class  // client version

  if ( !csconnection )
    SDBSET(517)
  else while ( rerun )
  {
    
    LockSendParms().Fill(keyptr); // sort_key string
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetID_ByID_ci1) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      obident = Get_rec_result()[0].GetLong(csconnection->get_conversion());
    UnlockSendParms();
  }
  return(obident);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
   
  if ( !(rerun = sc_prop->CheckInstance()) )
    obident = sc_prop->GetID((*parms)[0].GetString()); // sort_key string
  
  result->Fill(obident);

  return(rerun);

#endif
  return(obident);
}

/******************************************************************************/
/**
\brief  GetInstModCount - Get update count for selected instance



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 CNode :: GetInstModCount ( )
{
  logical     rerun    = YES;
  int16       modcount = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms().Fill();
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetInstModCount_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else  
      modcount = Get_rec_result()[0].GetShort(csconnection->get_conversion());
    UnlockSendParms();
  }
  return(modcount);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    modcount =  sc_prop->GetInstModCount();
  result->Fill(modcount);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetKey - 



\return sort_key - Sort key value

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *CNode :: GetKey (int32 lindx0, logical chknode )
{
  char       *sort_key;
  char       *keyptr = NULL;
  logical     rerun = YES;
  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(lindx0);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetKey_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = NO;
        
    }
    sort_key = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(sort_key);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = (keyptr = sc_prop->GetKey((*parms)[0].GetLong(connection->get_conversion()))) ? NO : YES;
  sc_prop->FillKeyResult(result,keyptr,term);

  return(term);

#endif
  return(sort_key);
}

/******************************************************************************/
/**
\brief  GetMode - Get access mode for collection handle



\return mode - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMode"

PIACC CNode :: GetMode (logical chknode )
{

  return ( bnode::GetMode(chknode) );

// kommunikation wieder einbauen, wenn zur synchonosation erforderlich!


}

/******************************************************************************/
/**
\brief  GetRefModCount - Get collection update count



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 CNode :: GetRefModCount ( )
{
  logical     rerun    = YES;
  int16       modcount = UNDEF;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRefModCount_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        modcount = Get_rec_result()[0].GetShort(csconnection->get_conversion());
      UnlockSendParms();
  }
  return(modcount);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    modcount =  sc_prop->GetRefModCount();
  result->Fill(modcount);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetRelative - 



\return instptr - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelative"

void *CNode :: GetRelative (int32 lindx0, logical chknode )
{
  void        *instptr = NULL;
  logical      rerun   = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    if ( !(instptr = Get_optimized(lindx0,chknode)) )
    {
      LockSendParms();
      if ( !Switch(AUTO) )
      {
        while ( rerun )
        {
          Get_send_parms().Fill(lindx0);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRelative_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = NO;
        }
      }
      if ( instptr = Inst_setup(term) )
        GenerateEvent(DBO_Read);
      UnlockSendParms();
    }
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->GetRelative((*parms)[0].GetLong(connection->get_conversion())) ? NO : YES;  // indx0
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetRelativeCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeCount"

int32 CNode :: GetRelativeCount ( )
{
  logical     rerun = YES;
  int32        count = ERIC;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( IsAttribute() )
      count = nodefield->fmcbdim;
    else
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRelativeCount_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
        UnlockSendParms();
      }
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->GetRelativeCount();
  
  result->Fill(count);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetRelativeIndex - 



\return lindx0 - 

\param  last_opt - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeIndex"

int32 CNode :: GetRelativeIndex (logical last_opt, logical chknode )
{
  logical                 rerun = YES;
  int32                   lindx0 = AUTO;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(last_opt);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetRelativeIndex_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        lindx0 = Get_rec_result()[0].GetLong(csconnection->get_conversion());
      UnlockSendParms();
    }
  }
  return(lindx0);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    lindx0 = sc_prop->GetRelativeIndex((*parms)[0].GetUChar());
  
  result->Fill(lindx0);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  GetSelectedKey - 



\return sort_key - Sort key value

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedKey"

char *CNode :: GetSelectedKey (logical chknode )
{
  char       *sort_key;
  char       *keyptr = NULL;
  logical     rerun = YES;

  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_GetSelectedKey_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = NO;
    }
    sort_key = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(sort_key);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = (keyptr = sc_prop->GetSelectedKey()) ? NO : YES;
  sc_prop->FillKeyResult(result,keyptr,term);

  return(term);

#endif
  return(sort_key);
}

/******************************************************************************/
/**
\brief  Get_ByID - 



\return instptr - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_ByID"

void *CNode :: Get_ByID (char *skey )
{
  void        *instptr = NULL;
  smcb        *keysmcb;
  char         wskey[MAX_KEYLEN];
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Switch(AUTO) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(skey);           // sort_key string
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Get_ByID_ci1) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = NO;
    }
    if ( instptr = Inst_setup(term) )
      GenerateEvent(DBO_Read);
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->Get(
              (*parms)[0].GetString())  // sort_key string
           ? NO : YES;
   
  sc_prop->FillInstResult(result,term);
  
  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Get_optimized - 



\return instptr - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_optimized"

void *CNode :: Get_optimized (int32 lindx0, logical chknode )
{
  void        *instptr = NULL;
BEGINSEQ
  if ( IsAttribute() )
  {
    instptr = (char *)Get_attribute(lindx0,chknode); LEAVESEQ
  }

  if ( data_nodetype == NT_ACShareBase )
  {
    if ( lindx0 > 0 || !nodenode->IsSelected() )     ERROR
    instptr = nodeinst->get_iselarea();              
    LEAVESEQ
  }
    
  if ( (lindx0 == AUTO || (lindx0 == nodecur && (nodewrit || nodeacc == PI_Read))) && 
       objid && (nodeinst->IsPositioned() || (nodecur == AUTO && nodeinst->stscini())) ) 
  {
    instptr = nodeinst->get_iselarea();              LEAVESEQ
  }
  
  if ( inti_buffer )
  {
    if ( instptr = GetBuffer(lindx0,0) ) 
      Cnodeinst->SetupInst(nodecur,objid,UNDEF,YES);           
    LEAVESEQ
  }

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Group - 



\return term - Termination code

\param  nodeptr - 
\param  distinct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Group"

logical CNode :: Group (node *nodeptr, logical distinct )
{
  logical     rerun   = YES;
  logical     term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    Switch(AUTO);
    
    while ( rerun )
    {
      LockSendParms().Fill((CS_Handle *)Cnodeptr,
                                distinct);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Group_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
/*  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->pib::group(
              *(pib *)((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer()),  // source_handle
              NULL,                                                                  // grouping rule defined in target
              (*parms)[1].GetUChar() );                                              // distinct
*/  
  result->Fill(term);

  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  InSave - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InSave"

logical CNode :: InSave ( )
{
  node   *nodeptr = this;
  while ( nodeptr = nodeptr->get_nodenode() )
    if ( nodeptr->stscsav() )
      return(YES);

  return(NO);

}

/******************************************************************************/
/**
\brief  InitHandle - Initialize handle




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandle"

void CNode :: InitHandle ( )
{

BEGINSEQ
  if ( CSHandle::InitHandle(YES) )                    ERROR
  
  SetClientPointer(this);


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  InitPathNode - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  cnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitPathNode"

logical CNode :: InitPathNode (CNode &cnode_ref )
{
  logical                 term = NO;
BEGINSEQ
  nodetype      = NT_ClientNode;
  data_nodetype = NT_ACOPView;
  csconnection  = cnode_ref.get_csconnection();

  if ( nodenode = cnode_ref.get_nodenode() )
  {
    if ( InitPathNode(*Cnodenode,cnode_ref.get_prop_path()) )
                                                    ERROR
  }
  else
  {
    object_ref    = cnode_ref.get_object_ref();
    nodeacc       = cnode_ref.GetMode(NO);
    set_prop_path(cnode_ref.get_prop_path());
    is_collection = YES;
    nodefield     = NULL;
  
    if ( OpenAccessPath(object_ref,nodeacc) )       ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  cnode_ref - 
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitPathNode"

logical CNode :: InitPathNode (CNode &cnode_ref, char *expression )
{
  logical                 term = NO;
BEGINSEQ
  nodetype      = NT_ClientNode;
  data_nodetype = NT_ACOPView;
  csconnection  = cnode_ref.get_csconnection();
  
  object_ref    = cnode_ref.get_object_ref();
  nodenode      = &cnode_ref;
  nodeacc       = cnode_ref.GetMode(NO);
  set_prop_path(expression);
  is_collection = YES;
  nodefield     = NULL;
  
  if ( OpenAccessPath(cnode_ref) )                  ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InstBuffer_setup - 



\return term - Termination code

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstBuffer_setup"

logical CNode :: InstBuffer_setup (int32 count )
{
  void                   *buffer;
  int32                    curi = 0;
  int32                    len;
  logical                 term = NO;
  inti_buffer->Cancel();
  while ( curi < count )
  {
    buffer = Get_rec_result()[curi+1].GetBuffer();
    len = Get_rec_result()[curi+1].GetCurSize();
    CConnection()->PushResult();
    CConnection()->SetResult(buffer,len);
    Inst_setup(NO,(logical)NO,NO);
    inti_buffer->Fill(curi);
    CConnection()->PopResult();
    curi++;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  InstKey_setup - Setup handle after providing a key



\return key_val - 

\param  error_case - Error indication
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstKey_setup"

char *CNode :: InstKey_setup (logical error_case, char *keyptr )
{
  smcb       *keysmcb;
  char        string[ID_SIZE+1];
  Key         key_val;
BEGINSEQ
  ResetInstance();
  if ( error_case || Get_rec_result()[0].GetUChar() )
                                                     ERROR
  
  if ( !(keysmcb = CheckSKey_intern(NO)) ||
       strcmp(gvtxbts(string,keysmcb->smcbname,ID_SIZE),Get_rec_result()[2].GetString()) )
                                                     SDBERR(513)
    
  objid    = Get_rec_result()[3].GetLong(conversion);
  nodecur  = Get_rec_result()[4].GetLong(conversion);
  key_val.SetData(keyptr ? keyptr : return_buffer);
  Get_rec_result()[1].GetKey(keysmcb,key_val,conversion);

RECOVER

ENDSEQ
  return(key_val);
}

/******************************************************************************/
/**
\brief  InstOrder_setup - Setup handle after order setting



\return term - Termination code

\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstOrder_setup"

logical CNode :: InstOrder_setup (logical error_case )
{
  char       *skey_names;
  logical     term = NO;
BEGINSEQ
  ResetInstance();
    
  if ( error_case )                                  ERROR
  
  if ( skey_names = Get_rec_result()[1].GetString() )
    sk_index = nodefield->GetIndexDef(skey_names);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Inst_setup - Setup handle after reading an instane



\return instptr - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  error_case - Error indication
\param  add - 
\param  active - Active property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Inst_setup"

void *CNode :: Inst_setup (logical error_case, logical add, logical active )
{
  char         *instptr = NULL;
  char         *strnames;
  uint16        version_nr;
  int32          old_id = objid;
  logical       term   = NO;
BEGINSEQ
  is_dirty = NO;
  
  CConnection()->PushResult();
  if ( add != YES )  // NO oder AUTO
    ResetInstance();
  else if ( stscmod() )
    term = nodeinst->Save(NO,NO);
  CConnection()->PopResult();
  if ( term )                                      ERROR
  
  if ( error_case || Get_rec_result()[0].GetUChar() )
  {
    ResetInstance();                              ERROR
  }
  
  strnames = Get_rec_result()[2].GetString();
  CConnection()->PushResult();
  term = SetType_intern(strnames);
  CConnection()->PopResult();
  if ( term )                                        ERROR
      
  objid             = Get_rec_result()[3].GetLong(conversion);
  nodecur           = Get_rec_result()[4].GetLong(conversion);
  relative_index    = Get_rec_result()[5].GetLong(conversion);
  nodewrit          = !Get_rec_result()[6].GetUChar();
  sk_index          = nodefield->GetIndexDef(Get_rec_result()[7].GetString());
  new_instance      = Get_rec_result()[8].GetUChar();
  instance_inserted = Get_rec_result()[9].GetUChar();
  version_nr        = Get_rec_result()[11].GetUShort(conversion);
  
  if ( Get_rec_result()[10].GetUChar() && nodenode ) // parent changed
    Cnodenode->SetModified();
  
  nodeinst->stsrini();
  if ( Get_rec_result()[12].GetUChar() )    // init instance
    nodeinst->stssini();
  
  Get_rec_result()[1].GetInstance(nodeinst->get_struct_def(),
                                  (void *)nodeinst->get_iselarea(),
                                  conversion);
  
  CConnection()->PushResult();
  if ( add )  // YES oder AUTO
  {
    // im local mode kommt das Event vor dem Stored event. Das geht aber nicht, da die Instanz noch nicht fertig ist. Ggf. m¸ssen wir die Funktionen etwas auseinandernehmen.
    if ( new_instance )
      Cnodeinst->SetupNewInst(nodecur,objid,new_instance,version_nr);
    else
      Cnodeinst->SetupInst(nodecur,objid,version_nr,YES);
    if ( instance_inserted )
      GenerateEvent(DBO_Inserted);
    
    instptr = nodeinst->get_iselarea();
  }
  else if ( nodecur >= 0 )
  {
    Cnodeinst->SetupInst(nodecur,objid,version_nr,active);
      
    if ( GenerateEvent(DBP_Select) )                   
      Cancel();
    else
      instptr = nodeinst->get_iselarea();
  }
  CConnection()->PopResult();

RECOVER
  if ( add )
    GenerateEvent(DBO_NotInserted);

ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  error_case - Error indication
\param  inst_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Inst_setup"

void *CNode :: Inst_setup (logical error_case, char *inst_data )
{
  char         *instptr;
  char          string[ID_SIZE+1];
BEGINSEQ
  ResetInstance();
  if ( error_case || Get_rec_result()[0].GetUChar() )
                                                     ERROR
  if ( strcmp(gvtxbts(string,nodeinst->get_struct_def()->smcbname,ID_SIZE),Get_rec_result()[2].GetString()) )
                                                     SDBERR(515)
  Get_rec_result()[1].GetInstance(nodeinst->get_struct_def(),
                                  (void *)nodeinst->get_iselarea(),
                                  csconnection->get_conversion());
  nodecur  = 0;
  instptr  = nodeinst->get_iselarea();


RECOVER

ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Intersect - Intersect collections



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i1 - 



\param  pi_liste - 
\param  count - 
\param  sk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

logical CNode :: Intersect (PropertyHandle **pi_liste, int32 count, char sk_opt )
{
  logical    term = YES;
  term = bnode::Intersect(pi_liste,count,sk_opt);
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  nodeptr - 
\param  sk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

logical CNode :: Intersect (node *nodeptr, char sk_opt )
{
  logical    term = YES;
  term = bnode::Intersect(nodeptr,sk_opt);
  ResetInstance();
  return(term);
}

/******************************************************************************/
/**
\brief  IsAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttribute"

logical CNode :: IsAttribute ( )
{

  return(   data_nodetype == NT_ACAttribute  ||
            data_nodetype == NT_ACBaseStruct ||
            data_nodetype == NT_Node            
          ? YES 
          : NO );

}

/******************************************************************************/
/**
\brief  IsGenericAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGenericAttribute"

logical CNode :: IsGenericAttribute ( )
{

  return( data_nodetype == NT_ACGenericAttr );

}

/******************************************************************************/
/**
\brief  IsLocalNode - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalNode"

logical CNode :: IsLocalNode ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsNewInstance - Indicates whether the instance has just been created or not



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical CNode :: IsNewInstance ( )
{
  logical   cond = NO;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( new_instance == AUTO )
    {
      LockSendParms().Fill();
           
      if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_IsNewInstance_ci) )
        new_instance = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(new_instance == YES ? YES : NO );
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  cond =  sc_prop->IsNewInstance();
  
  result->Fill(cond);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical CNode :: IsPositioned ( )
{

  switch ( data_nodetype )
  {
    case NT_Node          :
    case NT_ACAttribute   :
    case NT_ACBaseStruct  : 
    case NT_ACShareBase   :  
    case NT_ACGenericAttr : return (node::IsPositioned() );
    default               : return ( bnode::IsPositioned() );
  }

}

/******************************************************************************/
/**
\brief  IsReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical CNode :: IsReadOnly ( )
{
  logical                 memo_checked = NO;
  logical                 cond = YES;
BEGINSEQ
  if ( bnode::IsReadOnly() )                         LEAVESEQ
  
  if ( highnod && !highnod->IsWrite() )              LEAVESEQ
  
  if ( is_memo && IsPositioned() )
  {
    if ( !IsWrite() )                                LEAVESEQ
    memo_checked = YES;
  }
   
  if ( data_nodetype == NT_ACGenericAttr || is_memo )
  {
    if ( !memo_checked )
      if ( CheckReadOnly() )                         LEAVESEQ
  }
  else 
    if ( nodenode && ((CNode *)nodenode)->get_data_nodetype() == NT_ACGenericAttr )
      if ( ((CNode *)nodenode)->CheckReadOnly() )    LEAVESEQ
  
  cond = NO;
ENDSEQ
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

logical CNode :: IsSelected ( )
{

  switch ( data_nodetype )
  {
    case NT_Node          :
    case NT_ACAttribute   :
    case NT_ACBaseStruct  : 
    case NT_ACShareBase   :  
    case NT_ACGenericAttr : return (node::IsSelected() );
    default               : return ( bnode::IsSelected() );
  }

}

/******************************************************************************/
/**
\brief  Locate - Locate object by identity

        The  function is  searching for  an instance  with the given identity in
        the  collection of the property handle. The function returns an instance
        when  the  instance  could  be  located.  The  function returns an empty
        instance  in case of an error or when  the instance is not member of the
        collection.

\return term - Termination code

\param  entnr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical CNode :: Locate (EB_Number entnr, logical read_opt )
{
  logical   rerun = YES;
  void     *ph_inst;
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && entnr.get_ebsnum() != AUTO )
  {
    if ( read_opt )  // fuer ! siehe docu
      Switch(AUTO);

    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill((int32)entnr.get_ebsnum(),read_opt);
    
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Locate_ci) )
        rerun  = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    ph_inst = Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  !sc_prop->Locate(
                      (*parms)[0].GetLong(connection->get_conversion()),     // objid
                      (*parms)[1].GetUChar()                                 // read_opt
                );
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  LocateKey - 



\return term - Termination code

\param  sort_key - Sort key value
\param  exact - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical CNode :: LocateKey (char *sort_key, logical exact, logical chknode )
{
  smcb       *keysmcb;
  logical     rerun = YES;
  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    if ( (keysmcb = CheckSKey_intern()) )
    {
      Switch(AUTO);
      LockSendParms();
      while ( rerun )
      {
        Get_send_parms().Fill(sort_key,keysmcb,            // sort_key + keynames
                              exact);                      // exact
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_LocateKey_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
      }
      InstKey_setup(term,sort_key);
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    if ( !(rerun = sc_prop->CheckInstance()) )
      term = sc_prop->LocateKey(
              (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData(), // sort_key
              (*parms)[2].GetUChar() );                                                                   // exact
  
  sc_prop->FillKeyResult(result,sc_prop->Get_skeyarea(),term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Lock - Lock instance



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical CNode :: Lock ( )
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( Exist() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Lock_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->Lock();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  LockSet - Lock collection



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockSet"

logical CNode :: LockSet (logical chknode )
{
  logical     rerun = YES;
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( !chknode || !Check(YES) )
  {
    if ( chknode && inti_buffer )
      inti_buffer->Cancel();
    
    if ( !Switch(AUTO) )
    {
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_LockSet_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
    if ( chknode )
      ResetInstance();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->LockSet();
  
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Minus - Substract collections



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  node1 - 
\param  node2 - 
\param  sk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Minus"

logical CNode :: Minus (node *node1, node *node2, char sk_opt )
{
  logical    term = YES;
  term = bnode::Minus(node1,node2,sk_opt);
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  nodeptr - 
\param  sk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Minus"

logical CNode :: Minus (node *nodeptr, char sk_opt )
{
  logical    term = YES;
  term = bnode::Minus(nodeptr,sk_opt);
  ResetInstance();
  return(term);
}

/******************************************************************************/
/**
\brief  Modify - Mark property as modified



\return instptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *CNode :: Modify (logical chknode )
{
  void       *ph_inst = NULL;
  logical     term    = YES;
#ifndef IF_Class  // client term
  
  if ( !chknode || !Check(YES,NO) )  // siehe bnode
  {
    if ( IsTransient() )
      term = NO;
    else if ( IsAttribute() )
      term = ModifyAttribute(chknode) ? NO : YES;
    else
    {
      if ( !(term = CheckModify()) )
        if ( !(term = GenerateEvent(DBP_Modify)) )
          if ( IsWrite() && !nodeinst->stscini() )
            if ( nodeinst->IsPositioned() )  
              term = nodeinst->Modify();
    
      if ( !term )
        SetModified();
    }
    if ( !term )
      ph_inst = nodeinst->get_iselarea();
  }
  return(ph_inst);

/* 
wir probierens erstmal ohne kommunikation
  if ( !chknode || !Check(YES) )
  {
    if ( IsTransient() )
      term = NO;
    else
    {
      if ( IsWrite() || (nodeinst && nodeinst->stscini()) )  
      {
        if ( GetServerPointer() )
        {
          LockSendParms().Fill();
    
          if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Modify_ci) )
            term = Get_rec_result()[0].GetUChar();
          UnlockSendParms();
        }
      }
      if ( !term )
        SetModified();
    }
    if ( !term )
      ph_inst = nodeinst->get_iselarea();
  }
  return(ph_inst);
wir probierens erstmal ohne kommunikation
*/  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term = ((pib *)sc_prop)->Modify();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Move - 



\return instptr - 

\param  srcenode - 
\param  db_replace - Replace option
\param  w_newkey - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

void *CNode :: Move (node *srcenode, PIREPL db_replace, char *w_newkey, logical setwpt )
{
  smcb         *skeysmcb;
  smcb         *idkeysmcb;
  void         *instptr = NULL;
  logical       rerun   = YES;
  logical       term    = YES;

BEGINSEQ
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( csconnection != Csrcenode->get_csconnection() )
    {
      if ( instptr = bnode::CopyInst(srcenode,db_replace,REPL_all,w_newkey,setwpt) )
        srcenode->Delete(AUTO);
    }
    else
    {
      skeysmcb  = get_sortkey_smcb();
      idkeysmcb = get_idkey_smcb();
      
      Switch(AUTO);
      stssnof(); // node is acting
      
      while ( rerun )
      {
        Get_send_parms().Fill((CS_Handle *)Csrcenode,                                      
                              Key(w_newkey),skeysmcb ? skeysmcb : idkeysmcb,
                              (int32)db_replace);
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Move_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
      }
      stsrnof();
    }
    if ( !instptr )
      instptr = Inst_setup(term);
    UnlockSendParms();
  }
  return(instptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  skeysmcb  = sc_prop->GetSortKeySMCB();
  idkeysmcb = sc_prop->GetKeySMCB();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    sc_prop->Move(
      *(SC_Property *)(*parms)[0].GetHandle()->GetServerPointer(),     // srcenode
      (*parms)[1].GetKey(skeysmcb ? skeysmcb : idkeysmcb,              // w_new_key
                         sc_prop->Get_skeyarea(),
                         connection->get_conversion()).GetData(),     
      (PIREPL)(*parms)[3].GetLong(connection->get_conversion())        // db_replace
                );
  
    term = SDBERROR ? YES : NO;
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  MoveDown - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical CNode :: MoveDown ( )
{
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( !Save(NO,NO) )
    {
      stssnof(); // node is acting
      while ( rerun )
      {
        Get_send_parms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_MoveDown_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
      stsrnof(); 
    }
    Inst_setup(term);
    UnlockSendParms();
    term = (nodecur == AUTO ? YES : NO);
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->MoveDown();
      
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  MoveUp - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical CNode :: MoveUp ( )
{
  logical      rerun = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( !Save(NO,NO) )
    {
      stssnof(); // node is acting
      while ( rerun )
      {
        Get_send_parms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_MoveUp_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
      stsrnof(); 
    }
    Inst_setup(term);
    UnlockSendParms();
    term = (nodecur == AUTO ? YES : NO);
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->MoveUp();
      
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  NextKey - Locate next key



\return skey - 

\param  sort_key_w - 
\param  switch_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

char *CNode :: NextKey (char *sort_key_w, int16 switch_level )
{
  smcb       *keysmcb = NULL;
  char       *keyptr  = NULL;
  logical     rerun = YES;
  logical     term   = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( keysmcb = CheckSKey_intern() )
    {        
      Switch(AUTO);
      while ( rerun )
      {
        Get_send_parms().Fill(sort_key_w,keysmcb,       // sort_key + keynames
                              switch_level);            // switch_level
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_NextKey_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = NO;
      }
    }
    keyptr = InstKey_setup(term,keyptr);
    UnlockSendParms();
  }
  return(keyptr);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    if ( !(rerun = sc_prop->CheckInstance()) )
      if ( keyptr = sc_prop->NextKey(
             (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData(), // sort_key
             (*parms)[2].GetShort(connection->get_conversion())) )                                       // switch_level
        term = NO;
  
  sc_prop->FillKeyResult(result,keyptr,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  OInst_setup - 



\return ph_inst - Pointer to Property Handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OInst_setup"

Instance CNode :: OInst_setup ( )
{
  Instance                inst;
  logical                 term = NO;
BEGINSEQ
  // wo wird das aufgerufen?? in OFI meine ich?? sonst kans weg
  // only for direct instances and memo (!is_collection)
/*  
  if ( instance_list && (IsWeakTyped() || !instance) )
    if ( !(instance = instance_list->ProvideInstance(this,
                       !csconnection ? local_ref->GetCurrentType()->smcbname
                                   : Get_rec_result()[2].GetString())) )
                                                     ERROR
  objid      = ULONGMAX;
  curidx     = 0;
  no_write   = AUTO;
  
  if ( !csconnection )
  {
    if ( is_memo )
      instance->SetData(local_ref->Get(FIRST_INSTANCE));
    else
      instance->SetData(prophdl->GetArea());
  }
  else 
  {
    if ( is_memo )
      strncpy((char *)instance->get_instance().GetData(),Get_rec_result()[6].GetString(),prophdl->GetDescription()->fmcbsize);
    else
      Get_rec_result()[6].GetInstance(prophdl->GetDescription()->GetDescription(),instance->get_instance(),connection->get_conversion());
    prophdl->SetArea((char *)instance->get_instance().GetData());
  }

  inst = PropertyHandle::Inst_setup();
  is_valid = YES;
*/

RECOVER

ENDSEQ
  return(inst);
}

/******************************************************************************/
/**
\brief  Open - 




\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

void CNode :: Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt )
{

BEGINSEQ
  nodetype   = NT_ClientNode;
  bnode::Open(Cnodeptr->get_object_ref(),nodeptr,dbfield_ptr,highctx,accopt);
  csconnection = Cnodeptr->get_csconnection();
  
  switch ( data_nodetype )
  {
    case  NT_ACAttribute          : 
    case  NT_ACBaseStruct         : if ( !(nodeinst = new cinti(this,NULL,instptr,NO)) )
                                                     SDBERR(95)
                                                     SDBCERR
                                    if ( nodefield && nodefield->fmcbsmcb && nodefield->fmcbsmcb->smcbstyp == ST_CODE )
                                      is_codeset = YES;
                                    nodecur = 0;
                                    nodeinst->set_inst_index(0);
                                    Bnodeinst->OpenEvent();
                                    if ( !IsActive() )
                                      is_opened = YES;
                                    break;
    case  NT_ACGenericAttr        : 
    case  NT_ACShareBase          : if ( InitInti(nodefield->GetDBStruct(),instptr) )
                                                     ERROR
                                    break;
    case  NT_ACReference          :
    case  NT_ACRelationship       : LEAVESEQ
    case  NT_ACTransientReference : 
    default                       : SDBERR(99)
  }
  
//  OpenSubNode();
//  kommt erst beim Check

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OpenAccessPath - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci1 - 



\param  obhandle - Database Object handle
\param  temp_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical CNode :: OpenAccessPath (ACObject *obhandle, logical temp_opt_w )
{
  logical                 term = YES;

#ifndef IF_Class  // client version
   
  if ( !csconnection )
    SDBSET(517)
  else if ( object_ref->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)object_ref->GetClientACObject(),  // object_handle
                          prop_path,                                     // access path
                          (int32)nodeacc,                                // accopt
                          temp_opt_w);                                   // temp_opt_w
    InitHandle();
      
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenAccessPath_ci1) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        RegisterPathNode();
        Open_setup();  
        obhandle->GetClientACObject()->get_topnode_list()->AddTail(this);
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_DBObject *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),
                    (*parms)[1].GetString(),                                  // access path
                    (PIACC)(*parms)[2].GetLong(connection->get_conversion()), // accopt
                    (*parms)[3].GetUChar()) )                                 // temp_opt_w
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif


}

/******************************************************************************/
/**
\brief  ci2 - 



\param  cnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenAccessPath"

logical CNode :: OpenAccessPath (CNode &cnode_ref )
{
  logical                 term = YES;

#ifndef IF_Class  // client version 
  
  if ( !csconnection )
    SDBSET(517)
  else if ( object_ref->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref,                 // parent
                          prop_path);                              // access path
    InitHandle();
      
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenAccessPath_ci2) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());        RegisterPathNode();
        RegisterPathNode();
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),                     // parent
                    (*parms)[1].GetString()) );                    // access path
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  OpenBaseNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenBaseNode"

logical CNode :: OpenBaseNode ( )
{
  logical    term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( base_reference->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)(CNode *)base_reference);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenBaseNode_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->GetBaseProperty(
                     handle->GetClientObject())  )               // sc_property
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  OpenCopyNode - 



\return term - Termination code

\param  cnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenCopyNode"

logical CNode :: OpenCopyNode (CNode &cnode_ref )
{
  logical     term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( !cnode_ref.Check(YES,NO) )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenCopyNode_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                     handle->GetClientObject(),               // sc_property
                     NULL)  )                                 // prop_names
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  OpenOperationNode - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci1 - 



\param  cnode_ref - 
\param  op_type - 
\param  rule - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenOperationNode"

logical CNode :: OpenOperationNode (CNode &cnode_ref, ST_OpCodes op_type, char *rule )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( !csconnection )
    SDBSET(517)
  else if ( nodenode->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref,                        // parent handle
                          rule,                                          // operation rule
                          (int32)op_type);                               // op_type
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenOperationNode_ci1) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        Open_setup();  
        object_ref->GetClientACObject()->get_topnode_list()->AddTail(this);
      }
    UnlockSendParms();
  }
    
  return(term);
   
#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),                                // sc_property
                    (*parms)[1].GetString(),                                  // operation rule
                    (ST_OpCodes)(*parms)[2].GetLong(connection->get_conversion())) ) // op_type
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ci2 - 



\param  obhandle - Database Object handle
\param  op_type - 
\param  rule - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenOperationNode"

logical CNode :: OpenOperationNode (ACObject *obhandle, ST_OpCodes op_type, char *rule )
{
  logical                 term = YES;
#ifndef IF_Class  // client version

  if ( !csconnection )
    SDBSET(517)
  else if ( object_ref->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)object_ref->GetClientACObject(),  // object_handle
                          rule,                                          // operation rule
                          (int32)op_type );                              // operation type
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenOperationNode_ci2) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject()); 
        Open_setup();  
        object_ref->GetClientACObject()->get_topnode_list()->AddTail(this);
      }
    UnlockSendParms();
  }
    
  return(term);
   
#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_DBObject *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                    handle->GetClientObject(),
                    (*parms)[1].GetString(),                                  // operation rule
                    (ST_OpCodes)(*parms)[2].GetLong(connection->get_conversion())) ) // operation_type
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  OpenPathCopy - 



\return term - Termination code

\param  cnode_ref - 
\param  last_node - 
\param  path_opt - 
\param  accmode - 
\param  copy_selection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenPathCopy"

logical CNode :: OpenPathCopy (CNode &cnode_ref, CNode &last_node, logical path_opt, PIACC accmode, logical copy_selection )
{
  logical     term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( !cnode_ref.Check(YES,NO) )
  {
    LockSendParms().Fill((CS_Handle *)&cnode_ref,(CS_Handle *)&last_node,path_opt,(int32)accmode,copy_selection);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenPathCopy_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                     handle->GetClientObject(),                                       // sc_property
                     *(SC_Property *)(*parms)[1].GetHandle()->GetServerPointer(),     // last node
                     (*parms)[2].GetUChar(),                                          // path_opt
                     (PIACC)(*parms)[3].GetLong(connection->get_conversion()),        // accmode
                     (*parms)[4].GetUChar() )      )                                  // copy selection
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  OpenSubNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenSubNode"

logical CNode :: OpenSubNode ( )
{
  logical    term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( nodenode->IsValid() )
  {
    LockSendParms().Fill((CS_Handle *)Cnodenode,prop_path);
    InitHandle();
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_OpenSubNode_ci) )
      if ( !(term = Get_rec_result()[0].GetUChar()) )
      {
        SetServerObject(Get_rec_result().GetHandle()->GetServerObject());
        Open_setup();  
      }
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop;
  CS_Handle   *handle = parms->GetHandle();
  
  if ( sc_prop = ((SC_Property *)(*parms)[0].GetHandle()->GetServerPointer())->ProvideProperty(
                     handle->GetClientObject(),                 // sc_property
                     (*parms)[1].GetString())    )              // prop_names
  {
    handle->SetServerPointer(sc_prop);
    *result->GetHandle() = *handle;
  }
  sc_prop->FillOpenResult(result);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Open_setup - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open_setup"

logical CNode :: Open_setup ( )
{
  Dictionary   *dictptr  = object_ref->GetDictionary();
  DBStructDef  *strdef;
  int32         rindx0      = 1;   // DBFieldDef
  int32         intpos      = 0;
  int32         extpos      = 0;
  int8          max_aligned = 1;
  char         *skey_names;
  char         *save_prop_path = NULL;
  logical       term        = NO;
BEGINSEQ
  skey_names = Get_rec_result()[2].GetString();
  
  if ( !nodefield )
  {
    nodefield = new DBFieldDef(); 
    dictptr->GetClientDictionary()->SetupDBFieldDef(nodefield,rindx0);
  
    nodefield->GetDBStruct(dictptr);
    nodefield->SetupField(intpos,extpos,UNDEF,max_aligned);
    
    if ( !prop_path && nodefield->get_extend() )
      set_prop_path((char *)nodefield->get_extend());
    
    if ( prop_path )
      save_prop_path = strdup(prop_path);
  }
  
  if ( !prop_path )                                  SDBERR(99)
  
  if ( !context )
  {
    bnode::Open(object_ref,nodenode,nodefield,NULL,nodeacc);
    if ( save_prop_path )
      set_prop_path(save_prop_path);
  }
  
  if ( term || !nodefield )                          ERROR
  if ( is_opened = !is_collection || *nodefield->fmcbtype > ' ' ? YES : NO )
    GenerateEvent(DBO_Opened);  
    
  if ( !(strdef = nodefield->GetDBStruct(dictptr)) ) LEAVESEQ
  if ( !id_key )
    id_key = strdef->smcbidky;
  
  if ( skey_names )
    sk_index = nodefield->GetIndexDef(skey_names);

  if ( !nodeinst )                                  
    if ( InitInti(strdef,NULL) )                     ERROR


RECOVER
  is_opened = NO;
  term = YES;
ENDSEQ
  if ( save_prop_path )
    free(save_prop_path);
  return(term);
}

/******************************************************************************/
/**
\brief  PathCreateCopy - 



\return nodeptr - 

\param  nodeptr - 
\param  path_opt - 
\param  accmode - 
\param  copy_selection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PathCreateCopy"

node *CNode :: PathCreateCopy (node *nodeptr, logical path_opt, PIACC accmode, logical copy_selection )
{
  node                   *node_ptr = NULL;
BEGINSEQ
  node_ptr = new CNode(*this,*Cnodeptr,path_opt,accmode,copy_selection);
                                                     SDBCERR
RECOVER
  delete node_ptr;
  node_ptr = NULL;
ENDSEQ
  return(node_ptr);
}

/******************************************************************************/
/**
\brief  Position - 



\return rindx0 - 

\param  count - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

int32 CNode :: Position (int32 count, logical chknode )
{
  int32        lindx0 = AUTO;
  void        *instptr = NULL;
  logical      rerun  = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES) )
  {
    lindx0 = nodecur;
    if ( count )
    {
      if ( inti_buffer )
      {
        if ( instptr = GetBuffer(nodecur,count) ) 
        {
          Cnodeinst->SetupInst(nodecur,objid,UNDEF,YES);
          lindx0 = nodecur;
        }
      }
      else 
      {
        LockSendParms();
        if ( !Save(NO,NO) )
        {    
          while ( rerun )
          {
            Get_send_parms().Fill(count,relative_index);
            if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Position_ci) )
              rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
            else
              term = NO;
          }
        }
        instptr = Inst_setup(term);
        UnlockSendParms();
        lindx0 = nodecur;
      }
    }
    if ( instptr )
      GenerateEvent(DBO_Read);
  }
  return(lindx0);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance((*parms)[1].GetLong(connection->get_conversion()))) )
    term = sc_prop->Position((*parms)[0].GetLong(connection->get_conversion()));
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ProvGenAttribute - Provide generic attributes for new instance



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvGenAttribute"

logical CNode :: ProvGenAttribute ( )
{
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ProvGenAttribute_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->ProvGenAttribute();
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Provide - Provide instance



\return instance - Instance handle
-------------------------------------------------------------------------------
\brief  ci0 - 



\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *CNode :: Provide (int32 lindx0, logical global_add )
{
  void        *ph_inst;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) ) 
  {
    if ( !(ph_inst = Get_optimized(lindx0,NO)) )
    {
      LockSendParms();
      if ( !Switch(AUTO) )
      {
        while ( rerun )
        {
          Get_send_parms().Fill(lindx0,global_add);
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Provide_ci0) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
      }
//      ph_inst = Inst_setup(term,new_instance);
      ph_inst = Inst_setup(term,AUTO);
      UnlockSendParms();
    }
  }
  return(ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( (*parms)[1].GetUChar()  )        // global_add
    {
      if ( sc_prop->ProvideGlobal(
              (*parms)[0].GetLong(connection->get_conversion())) )  // indx0
        term = NO;
    }
    else                                  // not global_add
    {
      if ( sc_prop->Provide(
              (*parms)[0].GetLong(connection->get_conversion())) )  // indx0
        term = NO;
    }
  }
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  ci1 - 



\param  skey - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *CNode :: Provide (char *skey, logical global_add )
{
  void        *ph_inst;
  smcb        *keysmcb = NULL;
  logical      rerun = YES;
  logical      term = YES;
BEGINSEQ
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    LockSendParms();
    if ( stscusr2() || (keysmcb = CheckSKey_intern()) )
    {  
      stssnof(); // node is acting
      while ( rerun )
      {
        Get_send_parms().Fill(skey,keysmcb,global_add);           // sort_key + keynames
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Provide_ci1) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
      }
      stsrnof();
    }
    ph_inst = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  sc_prop->CheckInstance();
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    if ( !(rerun = sc_prop->CheckInstance()) )
    {
      if ( (*parms)[2].GetUChar()  )        // global_add
      {
        if ( sc_prop->ProvideGlobal(
                  Key((*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData())) )  // ident_key
          term = NO;
      }        
      else                                  // not global_add
      {
        if ( sc_prop->Provide(
                  Key((*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData())) )  // ident_key
          term = NO;
      }        
    }        
  term = (term || SDBERROR) ? YES : NO;
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ci2 - 



\param  datarea - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *CNode :: Provide (void *datarea, logical global_add )
{
  void        *ph_inst;
  logical      rerun = YES;
  logical      term = YES;
BEGINSEQ
#ifndef IF_Class  // client version

  if ( !Check(YES) )
  {
    Save(YES,NO,NO);
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(datarea,nodeinst->get_struct_def(),nodeinst->GetSize(),global_add);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Provide_ci2) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    ph_inst = Inst_setup(term,AUTO);
    UnlockSendParms();
  }
  return(ph_inst);
  
#else             // server version
  
  SC_Property  *sc_prop = ((SC_Property *)cso_ptr);
  DBStructDef  *strdef  = sc_prop->GetCurrentTypeDef();
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    if ( (*parms)[2].GetUChar()  )        // global_add
    {
      if ( sc_prop->ProvideGlobal(
             Instance((*parms)[0].GetInstance(strdef,sc_prop->Get_instarea(),connection->get_conversion()).GetData())) )   // newitp
        term = NO;
    }
    else                                  // not global_add
    {
      if ( sc_prop->Provide(
             Instance((*parms)[0].GetInstance(strdef,sc_prop->Get_instarea(),connection->get_conversion()).GetData())) )   // newitp
        term = NO;
    }
  }
  term = (term || SDBERROR) ? YES : NO;
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ProvideGUID - 



\return guid_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGUID"

char *CNode :: ProvideGUID ( )
{
  char       *guid_string;
  logical     rerun = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && !(guid_string = GetGUID()) )
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ProvideGUID_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        guid_string = Get_rec_result()[0].GetString();
      UnlockSendParms();
    }
 
  return(guid_string);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    guid_string = sc_prop->ProvideGUID();
  result->Fill(guid_string);

  return(NO);

#endif
  return(guid_string);
}

/******************************************************************************/
/**
\brief  ReadBuffer - Fill instance buffer from position



\return instcount - Number of instances read into buffer

\param  set_pos0 - 
\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBuffer"

int32 CNode :: ReadBuffer (int32 set_pos0, int16 direction )
{
  int32         count = AUTO;
  logical      rerun   = YES;
  logical      term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES) && inti_buffer )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(set_pos0,(int32)direction);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ReadBuffer_ci0) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        count = Get_rec_result()[0].GetLong(csconnection->get_conversion());
    }
    InstBuffer_setup(count);
    UnlockSendParms();
  }
  return(count);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    count = sc_prop->ReadBuffer((*parms)[0].GetLong(connection->get_conversion()),   // indx0
                                (*parms)[1].GetLong(connection->get_conversion()));  // direction
  
  sc_prop->FillInstBuffer(result,count);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  RecoverSelection - 



\return term - Termination code

\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecoverSelection"

logical CNode :: RecoverSelection (int64 obj_id )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - Refresh selected instance

        The  function  checks  whether  the  parent  of  the property handle are
        positioned.  If not, the function trys  to position the parent hierarchy
        (PositionTop()). 
        If  the  parent  handle  is  positioned  and  the  property is an active
        property the function generates a server event (Refresh).

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical CNode :: Refresh ( )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )  // Check(YES,YES) geht nicht, da der Pfad nach oben nicht eingestellt sein muﬂ.
  {
    if ( nodenode &&  !nodenode->Exist() )
    {
      nodenode->PositionTop();
      nodenode->Get(FIRST_INSTANCE);
    }      
    
    if ( IsActive() )
    {
      while ( rerun )
      {
        LockSendParms().Fill();
        if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Refresh_ci) )
          rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
        else
          term = Get_rec_result()[0].GetUChar();
        UnlockSendParms();
      }
    }
  }
  if ( !term )
    term = GenerateEvent(DBO_Refresh);
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->Refresh(
            );
   
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  RegisterHandle - 



\return term - Termination code

\param  cs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterHandle"

logical CNode :: RegisterHandle (CSA_Handle *cs_handle )
{
  logical   rerun = YES;
  logical   term  = YES;
#ifndef IF_Class  // client term

  if ( !Check(YES,NO) && GetServerObject() )
  {
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_RegisterHandle_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->RegisterHandle();
    
  result->Fill(term);

  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveFromCollection - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveFromCollection"

logical CNode :: RemoveFromCollection ( )
{
  logical                 term = YES;
#ifndef IF_Class  // client term

  if ( Exist() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_RemoveFromCollection_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->RemoveFromCollection();
  result->Fill(term);

  return(NO);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  Rename - Rename instance



\return term - Termination code

\param  new_key - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rename"

logical CNode :: Rename (char *new_key, logical chknode )
{
  smcb        *keysmcb;
  logical      rerun = YES;
  logical      term = YES;
#ifndef IF_Class  // client version

  if ( Exist() )
  {
    LockSendParms();
    if ( keysmcb = CheckSKey_intern() )
    {  
      if ( !Save(NO,NO) )
      {
        stssnof(); // node is acting
        while ( rerun )
        {
          Get_send_parms().Fill(new_key,keysmcb);       // sort_key + keynames
          if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Rename_ci) )
            rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
          else
            term = Get_rec_result()[0].GetUChar();
        }
        stsrnof();
      }
    }
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( keysmcb = sc_prop->CheckSKey((*parms)[1].GetString()) )
    term = sc_prop->Rename(
              (*parms)[0].GetKey(keysmcb,sc_prop->Get_skeyarea(),connection->get_conversion()).GetData() );  // ident_key
  
  sc_prop->FillInstResult(result,term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  Reopen_intern - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reopen_intern"

logical CNode :: Reopen_intern ( )
{
  logical    term = YES;
#ifndef IF_Class  // client version
  
  Close_intern();
// danach waere alle weg!   
// wozu wird Reopen_intern noch gebraucht?
  
  Get_send_parms().Fill(prop_path);
    
  if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Reopen_intern_ci) )
    term = Get_rec_result()[0].GetUChar();

  if ( !term )
    Open_setup();  
      
  return(term);

#else             // server version
  
  SC_Property *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( sc_prop->ReopenProperty(
                (*parms)[0].GetString()) )                              // prop_names
    sc_prop = NULL;
  
  sc_prop->FillOpenResult(result);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  RepairIndex - 



\return term - Termination code

\param  key_name - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RepairIndex"

logical CNode :: RepairIndex (char *key_name, char *attrstr )
{
  logical   rerun = YES;
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) && is_collection )
  {
    if ( inti_buffer )
      inti_buffer->Cancel();
    
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(key_name,attrstr);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_RepairIndex_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    InstOrder_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property *sc_prop = ((SC_Property *)cso_ptr);
  smcb        *skeysmcb = NULL;
  char         string[ID_SIZE+1];
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    term =  sc_prop->RepairIndex(
                 (*parms)[0].GetString(),                            // key_names
                 (*parms)[1].GetString() );                          // attrstr
  }
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Reset - Reset instance



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical CNode :: Reset ( )
{
  logical     rerun = YES;
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( Exist() )
  {
    LockSendParms().Fill();
    
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Reset_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      term = Get_rec_result()[0].GetUChar();
    
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->Reset();
  
  sc_prop->FillInstResult(result,term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ResetExpression - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetExpression"

logical CNode :: ResetExpression ( )
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( !Check(YES,NO) )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ResetExpression_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->Lock();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  ResetInstance - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

void CNode :: ResetInstance ( )
{

BEGINSEQ
  switch ( data_nodetype )
  {
    case NT_Node          :
    case NT_ACAttribute   : 
    case NT_ACBaseStruct  : LEAVESEQ
    
    default               : bnode::ResetInstance();
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetWProtect - Reset permanent write protection



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical CNode :: ResetWProtect ( )
{
  logical     rerun = YES;
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( !Exist() )
  {
    LockSendParms().Fill();
    
    if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_ResetWProtect_ci) )
      rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
    else
      term = Get_rec_result()[0].GetUChar();
    
    Inst_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->ResetWProtect();
  
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Save - Store instance



\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical CNode :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical     inst_updated;
  logical     term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  if ( !nodeinst )                                   LEAVESEQ
  if ( IsPositioned() || nodeinst->stscini() )
  {
    if ( chknode && Check(YES) )                       ERROR
  
    if ( (is_collection || is_memo) && !InSave() )
      stsssav();
  
    if ( stscmod() || is_updated ) 
      if ( nodeinst->stscini() && data_nodetype != NT_ACGenericAttr )
        if ( !Add(AUTO,NULL,NULL,nodeinst->get_iselarea()) )
                                                     ERROR
  
    if ( stscmod() ) 
      nodeinst->Save(switchopt,overwrite);
  
    if ( is_collection || is_memo )
    {
      stssnof(); // node is acting
      if ( is_updated )
      {
        if ( data_nodetype == NT_ACGenericAttr && !stscsav() )
          Cnodenode->SetModified();
        else
          term = Update_intern(switchopt);    
        is_updated = NO;
        switchopt  = NO;
      }
      else if ( stscsav() && is_opened )     // is_opened ist neu hier (28.12.01), da Save maschiefgeht, wenn keint ClientPointer gesetzt ist
      {
        if ( stscmod() || switchopt )
          term = Save_intern(switchopt);
        switchopt  = NO;
      }
      stsrnof();
    }
  }
  
  if ( switchopt )
  {
    ResetInstance();
    is_updated = NO;
  }
  stsrmod();
  stsrsav();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save_intern - 



\return term - Termination code

\param  switchopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save_intern"

logical CNode :: Save_intern (logical switchopt )
{
  logical    term = YES;
BEGINSEQ
#ifndef IF_Class  // client version
  if ( !csconnection )                                 SDBERR(517)

  LockSendParms().Fill(switchopt);
    
  if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Save_intern_ci) )
    term = Get_rec_result()[0].GetUChar();
  UnlockSendParms();
    
  if ( switchopt )
    ResetInstance();
  else if ( term )
  {
    Error           saveerr  = SDBError();
    Reset();   
    SDBError() = saveerr;
  }
  
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop = ((SC_Property *)cso_ptr);
  
  term = sc_prop->Save(NO,
                       (*parms)[0].GetUChar()       // switchopt
                      );                       
  result->Fill(term);

  return(NO);

#endif
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Select - Create a subset from a collection



\return term - Termination code

\param  nodeptr - 
\param  expression - Expression
\param  min_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

logical CNode :: Select (node *nodeptr, char *expression, int32 min_inst )
{
  logical     term = YES;
  term = bnode::Select(nodeptr,expression,min_inst);
  return(term);
}

/******************************************************************************/
/**
\brief  SetAction - 



\return term - Termination code

\param  simple_action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

logical CNode :: SetAction (SimpleAction *simple_action )
{
  logical    term = YES;
  SDBSET(99)
  return(term);
  // muss ci werden
  // is so erstmal witzlos, da die Action von aussen nicht aufrufbar!



}

/******************************************************************************/
/**
\brief  SetBaseNode - 



\return term - Termination code

\param  cnode_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBaseNode"

logical CNode :: SetBaseNode (CNode *cnode_ptr )
{
  logical                 term = YES;
#ifndef IF_Class  // client version
  
  if ( !csconnection )
    SDBSET(517)
  else if ( !cnode_ptr->Check(YES,NO) )
  {
    LockSendParms().Fill((CS_Handle *)cnode_ptr);
   
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetBaseNode_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  
  return(term);

#else             // server version
  
  SC_Property *sc_prop   = (SC_Property *)cso_ptr;
  SC_Property *bn_prop   = (SC_Property *)(*parms)[0].GetHandle()->GetServerPointer();
  
  term = YES;
  if ( sc_prop && bn_prop )
    term = sc_prop->SetBaseNode(bn_prop);
  
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SetContextVariables - 



\return term - Termination code

\param  context_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContextVariables"

logical CNode :: SetContextVariables (char *context_string )
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(context_string);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetContextVariables_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        if ( !(term = Get_rec_result()[0].GetUChar()) )
          term = bnode::SetContextVariables(context_string);
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->SetContextVariables(
                 (*parms)[0].GetString());   // context string
  
  result->Fill(term);

  return(rerun);

#endif
  return(term);
}

/******************************************************************************/
/**
\brief  SetExpression - 



\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical CNode :: SetExpression (char *expression )
{
  logical     rerun = YES;
  logical     term  = YES;

#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    while ( rerun )
    {
      LockSendParms().Fill(expression);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetExpression_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  rerun = NO;
  if ( !(rerun = sc_prop->CheckInstance()) )
    term = sc_prop->SetSelection(
                 (*parms)[0].GetString());   // expression
  
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  SetGenAttribute - Set type for generic attribute in instance



\return term - Termination code
-------------------------------------------------------------------------------
\brief  ci - 



\param  fldnames - Property name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical CNode :: SetGenAttribute (char *fldnames, int attrtype, char *attrstr )
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) )
  {
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(fldnames,(int32)attrtype,attrstr);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetGenAttribute_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    if ( Inst_setup(term) )
      GenerateEvent(DBO_Read);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    char   *propnames = (*parms)[0].GetString();
    int     attrtype  = (*parms)[1].GetLong(connection->get_conversion());
    char   *attrstr   = (*parms)[2].GetString();
    
    term = propnames && attrstr ? sc_prop->SetGenAttribute(attrstr,propnames)
         : propnames            ? sc_prop->SetGenAttribute(attrtype,propnames)
         : attrstr              ? sc_prop->SetGenAttribute(attrstr)
         :                        sc_prop->SetGenAttribute(attrtype);
  } 
  sc_prop->FillInstResult(result,term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  i01 - 



\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical CNode :: SetGenAttribute (int attrtype, char *attrstr )
{

  return(SetGenAttribute(NULL,attrtype,attrstr));

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical CNode :: SetGenAttribute ( )
{

  return(SetGenAttribute(NULL,AUTO,NULL));

}

/******************************************************************************/
/**
\brief  SetGenKey - 




\param  attrtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenKey"

void CNode :: SetGenKey (int attrtype )
{

  if ( nodeinst )
    fldfmcb->fmcbsmcb->smcbidky->kcbkpt(nodeinst->get_iselarea(),(char *)&attrtype);


}

/******************************************************************************/
/**
\brief  SetInstAction - 



\return term - Termination code

\param  simple_action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstAction"

logical CNode :: SetInstAction (SimpleAction *simple_action )
{
  logical     term = YES;
  SDBSET(99)
  return(term);
  // muss ci werden
  // is so erstmal witzlos, da die Action von aussen nicht aufrufbar!


}

/******************************************************************************/
/**
\brief  SetModified - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetModified"

void CNode :: SetModified ( )
{
  logical   mod_set = stscmod();
BEGINSEQ
  if ( IsTransient() )                               LEAVESEQ
    
  if ( is_collection || is_memo )
    is_updated = YES;
  if ( nodenode && !(is_collection || is_memo) )
    Cnodenode->SetModified();

  if ( is_updated )
  {
    SetMod();
    if ( !mod_set )
      stsrmod();
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetOrder - Set order for collection



\return term - Termination code

\param  key_name - 
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical CNode :: SetOrder (char *key_name, int attrtype, char *attrstr )
{
  logical   rerun = YES;
  logical   term = YES;
#ifndef IF_Class  // client version

  if ( !Check(YES,NO) && is_collection )
  {
    if ( inti_buffer )
      inti_buffer->Cancel();
    
    Switch(AUTO);
    LockSendParms();
    while ( rerun )
    {
      Get_send_parms().Fill(key_name,attrtype,attrstr);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetOrder_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
    }
    InstOrder_setup(term);
    UnlockSendParms();
  }
  return(term);
  
#else             // server version
  
  SC_Property *sc_prop = ((SC_Property *)cso_ptr);
  smcb        *skeysmcb = NULL;
  char         string[ID_SIZE+1];
  
  if ( !(rerun = sc_prop->CheckInstance()) )
  {
    term =  sc_prop->SetOrder(
                 (*parms)[0].GetString(),                            // key_names
                 (*parms)[1].GetLong(connection->get_conversion()),  // attrtype
                 (*parms)[2].GetString() );                          // attrstr
    skeysmcb = sc_prop->GetSortKeySMCB();  
  }
  result->Fill(term,
               skeysmcb ? gvtxbts(string,skeysmcb->smcbname,ID_SIZE) : (char *)NULL);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  SetType - 



\return term - Termination code

\param  strnames - Type name
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical CNode :: SetType (char *strnames, logical chknode )
{
  char      struct_names[ID_SIZE+1];
  logical   rerun = YES;
  logical   term  = YES;
BEGINSEQ
#ifndef IF_Class  // client version

  if ( !chknode || !Check(YES,NO) )
  {
    gvtxbts(struct_names,strnames,ID_SIZE);
    if ( !IsVariableType(NO) )                       SDBERR(158)
    Switch(AUTO);
    ResetInstance();
    
    while ( rerun )
    {
      LockSendParms().Fill(struct_names);
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetType_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
    
    if ( !term )
      term = SetType_intern(struct_names);
  }

  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->SetType(
                 (*parms)[0].GetString()
            );
   
  result->Fill(term);
  
  return(rerun);

#endif
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetVersion - Set instance version to be provided by the collection handle



\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical CNode :: SetVersion (uint16 version_nr )
{
  logical    term = YES;
BEGINSEQ
  SDBERR(999)
RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetWProtect - Set permanent write protection



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical CNode :: SetWProtect ( )
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( IsWrite() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_SetWProtect_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
    
    nodewrit = NO;
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->SetWProtect();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  SetupCNode - 



\return term - Termination code

\param  lindx0 - 
\param  retain_mod - 
\param  active - Active property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCNode"

logical CNode :: SetupCNode (int32 lindx0, logical retain_mod, logical active )
{
  node       *nodeptr;
  logical     is_ini = nodeinst ? nodeinst->stscini() : NO;
  logical     is_mod = nodeinst ? nodeinst->stscmod() : NO;
  logical     is_coll_mod = stscmod();
  logical     term = NO;
BEGINSEQ
  if ( stscerr() )                                   LEAVESEQ
  
  ResetNode(YES);
  nodewrit = Cnodenode->get_nodewrit();
  nodecur  = lindx0;
  if ( nodeinst && nodecur != AUTO )
    Cnodeinst->SetupInst(nodecur,UNDEF,CUR_VERSION,active);

  if ( copies )
  {
    copies->GoTop();
    while ( nodeptr = copies->GetNext() )
      Cnodeptr->SetupCNode(AUTO,NO,active);
  }

  if ( retain_mod && nodecur == AUTO )
  {
    if ( is_ini )
      nodeinst->stssini();
    if ( is_mod )
      nodeinst->stssmod();
    if ( is_coll_mod )
      SetMod();
  }
ENDSEQ
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

logical CNode :: Switch (int32 indx0 )
{
  logical                 term = NO;
BEGINSEQ
  if ( stscmod() || is_updated )
  {    
    if ( bnode::Switch(indx0) )                      ERROR
  }
  else if ( nodecur == AUTO && nodeinst )      // zuruecknehmen von InitInstance ohne expl. Save/Add
    if ( nodeinst->IsPositioned() || nodeinst->stscini() )
      ResetInstance();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UninitHandle - Uninitialize property handle



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UninitHandle"

logical CNode :: UninitHandle ( )
{
  logical                 term = NO;
  CSHandle::UninitHandle();
  return(term);
}

/******************************************************************************/
/**
\brief  Union - Union two collections



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i01 - 



\param  pi_liste - 
\param  count - 
\param  sk_opt - 
\param  distinct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

logical CNode :: Union (PropertyHandle **pi_liste, int32 count, char sk_opt, logical distinct )
{
  logical    term = YES;
  term = bnode::Union(pi_liste,count,sk_opt,distinct);
  ResetInstance();
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  nodeptr - 
\param  sk_opt - 
\param  distinct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

logical CNode :: Union (node *nodeptr, char sk_opt, logical distinct )
{
  logical   term = YES;
  term = bnode::Union(nodeptr,sk_opt,distinct);
  ResetInstance();
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - Unlock instance



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical CNode :: Unlock ( )
{
  logical     term = YES;
#ifndef IF_Class  // client term

  if ( IsPositioned() )
  {
    LockSendParms().Fill();
    
    if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Unlock_ci) )
      term = Get_rec_result()[0].GetUChar();
    UnlockSendParms();
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  term =  sc_prop->Unlock();
  result->Fill(term);

  return(NO);

#endif

}

/******************************************************************************/
/**
\brief  UnlockSet - Unlock collection



\return term - Termination code

\param  extlock - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockSet"

logical CNode :: UnlockSet (logical extlock, logical chknode )
{
  logical     rerun = YES;
  logical     term = YES;

#ifndef IF_Class  // client term

  if ( !chknode || !Check(YES) )
  {
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_UnlockSet_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
//      ResetInstance();
  }
  
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->UnlockSet();
    
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  UnregisterHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterHandle"

logical CNode :: UnregisterHandle ( )
{
  logical     rerun = YES;
  logical     term  = YES;
#ifndef IF_Class  // client term

  if ( !Check(YES,NO) && GetServerObject() )
  {
    while ( rerun )
    {
      LockSendParms().Fill();
      if ( rerun = CConnection()->SendCSMessage(this,S_CNode,SF_CNode_UnregisterHandle_ci) )
        rerun = rerun == 255 && !Reopen_intern() ? YES : NO;
      else
        term = Get_rec_result()[0].GetUChar();
      UnlockSendParms();
    }
  }
  return(term);
  
#else             // server term
  
  SC_Property  *sc_prop   = ((SC_Property *)cso_ptr);
  
  if ( !(rerun = sc_prop->CheckInstance()) )
    term =  sc_prop->UnregisterHandle();
    
  result->Fill(term);

  return(rerun);

#endif

}

/******************************************************************************/
/**
\brief  Update_intern - Update instance



\return term - Termination code

\param  switchopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update_intern"

logical CNode :: Update_intern (logical switchopt )
{
  logical   term = YES;
BEGINSEQ
#ifndef IF_Class  // client version
  if ( !csconnection )                                 SDBERR(517)

  LockSendParms().Fill(nodeinst->get_iselarea(),nodeinst->get_struct_def(),nodeinst->GetSize(), // inst + strname
                        switchopt);
    
  if ( !CConnection()->SendCSMessage(this,S_CNode,SF_CNode_Update_intern_ci) )
    if ( !(term = Get_rec_result()[0].GetUChar()) )
      nodeinst->StructureEvents(DBO_Stored);
  UnlockSendParms();
    
  if ( switchopt )
    ResetInstance();
  else if ( term )
  {
    Error           saveerr  = SDBError();
    Reset();   
    SDBError() = saveerr;
  }
  
  return(term);
  
#else             // server version
  
  SC_Property  *sc_prop = ((SC_Property *)cso_ptr);
  
  term = sc_prop->CopyData(
      (char *)(*parms)[0].GetFieldInst(sc_prop->GetDescription()->GetDescription(),
                                       sc_prop->Get_instarea(),
                                       connection->get_conversion()).GetData(),   // newitp
      (*parms)[2].GetUChar()                                                      // switchopt
  );                       
//  sc_prop->FillInstResult(result,term);
  result->Fill(term);

  return(NO);

#endif
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~CNode - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CNode"

     CNode :: ~CNode ( )
{

  if ( !nodenode || 
       (csconnection && nodenode->GetContext() && 
        nodenode->GetContext()->ProcessState() != PRC_Closed) )
    Close();
  else
    Close_intern();


}


