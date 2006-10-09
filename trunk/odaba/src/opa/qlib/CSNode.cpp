/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CSNode

\brief    


\date     $Date: 2006/08/26 18:30:40,87 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSNode"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBExtend.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sENUM_Value.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sLACObject.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <srefTable.hpp>
#include  <sCSNode.hpp>


/******************************************************************************/
/**
\brief  CSNode - 



-------------------------------------------------------------------------------
\brief  i01 - 



\param  obhandle - Database Object handle
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSNode"

     CSNode :: CSNode (ACObject *obhandle, char *scoped_name )
                     : bnode (obhandle,NULL,NULL,NULL,PI_Read),
  value_list(NULL),
  local_order(UNDEF)
{
  DBIndex       *index;
  int16          elen = 0;
  DBStructDef   *strdef = NULL;
BEGINSEQ
  TypeKey         tkey(obhandle->GetDictionary(),scoped_name);
  if ( !(strdef = obhandle->GetDictionary()->ProvideStructDef(tkey)) )
                                                    ERROR
  SDBEV1(scoped_name,UNDEF)
  if ( strdef->smcbstyp != ST_CODE )                SDBERR(20)
  
  if ( !(value_list = (ENUM_ValueList *)strdef->smcbacc) )
                                                    SDBERR(99)
  if ( Open(obhandle,NULL,obhandle->GetDictionary()->GetExtendDef(tkey),
            NULL,PI_Read)  )                        ERROR

  SetOrderKey();
  nodetype = NT_CSNode;
  obhandle->GetLocalACObject()->AddCSNode(this);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 



\param  csnode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSNode"

     CSNode :: CSNode (CSNode &csnode )
                     : bnode(*(bnode *)&csnode),
  value_list(csnode.get_value_list()),
  local_order(UNDEF)
{

  nodetype = NT_CSNode;
  if ( object_ref )
    object_ref->GetLocalACObject()->AddCSNode(this);

}

/******************************************************************************/
/**
\brief  i04 - 



\param  parent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSNode"

     CSNode :: CSNode (node *parent )
                     : bnode(NULL,NULL,NULL,NULL,PI_Read),
  value_list(NULL),
  local_order(UNDEF)
{
  Dictionary         *dictptr;
  PropertyHandle     *void_ph;
  PropertyHandle     *list_ph;
  ENUM_Value         *eval;

BEGINSEQ
  if ( !parent->IsPositioned() )                    ERROR
  
  dictptr = parent->GetDictionary();
  eval = (ENUM_Value *)parent->GetArea(); 
  void_ph = dictptr->GetVoidPI();
  if ( !void_ph->Get(eval->id) )                    ERROR
  
  if ( !(list_ph = void_ph->GPH("values")) )        SDBERR(99)
    
  value_list = new ENUM_ValueList(list_ph);         SDBCERR
  
  if ( Open(NULL,parent,parent->GetFieldDef(),NULL,PI_Read)  )
                                                    ERROR
  nodetype = NT_CSNode;
RECOVER
  delete value_list;
  value_list = NULL;
ENDSEQ

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

logical CSNode :: Check (logical autoini, logical acccheck )
{
  logical   term = NO;
BEGINSEQ
  if ( !this || !value_list )                        ERROR
  if ( nodenode && acccheck )
    if ( nodenode->IsPositioned() )                  ERROR

  if ( autoini == YES && !nodeinst )
    if ( node::InitInti(nodefield->GetDBStruct(),NULL,NO) )
                                                     ERROR
  if ( local_order == UNDEF )
    SetOrderKey();
  else if ( local_order != value_list->get_order() )
    value_list->ChangeOrder(local_order);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical CSNode :: Close ( )
{
  logical    orig = origin ? YES : NO;
  Switch(AUTO);
  
  delete nodeinst;
  nodeinst = NULL;

  if ( object_ref )
    object_ref->GetLocalACObject()->RemoveCSNode(this);

  bnode::Close();


  return(NO);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *CSNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new CSNode(*this) ) )            SDBERR(95)
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

inti *CSNode :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti *   intiptr = NO;
  return(bnode::CreateInti(nodeptr,strdef_ptr,instptr,init_nodes));
  return(intiptr);
}

/******************************************************************************/
/**
\brief  ExtractKey - 



\return keyptr - 
-------------------------------------------------------------------------------
\brief  NODEKE - 



\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *CSNode :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{
  ENUM_Value    *eval = NULL;
  char          *keyarea = NULL;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR

  if ( !instptr && !IsPositioned() )                ERROR

  if ( instptr )
    eval = (ENUM_Value *)instptr;
  else
    eval = (ENUM_Value *)nodeinst->get_iselarea(); 
  
  keyarea = value_list->GetName(eval); 
  
  if ( keyptr )
    keyarea = strcpy(keyptr,keyarea);

RECOVER
  keyarea = NULL;
ENDSEQ
  return(keyarea);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  keyptr - 
\param  kcbptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *CSNode :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{

BEGINSEQ
  SDBERR(99)
RECOVER

ENDSEQ
  return(NULL);
}

/******************************************************************************/
/**
\brief  ExtractSortKey - 



\return keyptr - 

\param  keyptr - 
\param  instptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractSortKey"

char *CSNode :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{
  ENUM_Value    *eval = NULL;
  char          *keyarea = NULL;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR

  if ( !instptr && !IsPositioned() )                ERROR

  if ( instptr )
    eval = (ENUM_Value *)instptr;
  else
    eval = (ENUM_Value *)nodeinst->get_iselarea(); 
  
  keyarea = value_list->GetSortKey(eval,UNDEF); 
  
  if ( keyptr )
    keyarea = strcpy(keyptr,keyarea);

RECOVER
  keyarea = NULL;
ENDSEQ
  return(keyarea);
}

/******************************************************************************/
/**
\brief  FirstKey - 



\return keyptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *CSNode :: FirstKey (logical chknode )
{
  char *   keyptr = NULL;
  if ( Get(0) )
    keyptr = ExtractSortKey(NULL,NULL);
  return(keyptr);
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

void *CSNode :: Get (int32 indx0, logical chknode )
{
  ENUM_Value    *eval = NULL;
  void          *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR

  if ( indx0 == AUTO )
    indx0 = nodecur;
    
  Switch(AUTO);
  if ( GenerateEvent(DBP_Read) )                     ERROR
  
  if ( !(eval = value_list->GetEntry(indx0)) )      ERROR
    nodeinst->set_iselarea(eval);
  
  nodecur = indx0;
  instptr = nodeinst->get_iselarea();
  if ( GenerateEvent(DBP_Select) )                   ERROR

RECOVER
  instptr = NULL;
  ResetInstance();
ENDSEQ
  if ( instptr )
    GenerateEvent(DBO_Read);
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

void *CSNode :: Get (char *skey, logical chknode )
{
  ENUM_Value    *eval = NULL;
  void          *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR

  Switch(AUTO);
  if ( GenerateEvent(DBP_Read) )                     ERROR
  
  if ( !(eval = value_list->GetEntry(skey)) )        ERROR
    nodeinst->set_iselarea(eval);
  
  nodecur = value_list->GetCurrentIndex(skey);
  instptr = nodeinst->get_iselarea();
  if ( GenerateEvent(DBP_Select) )                   ERROR

RECOVER
  instptr = NULL;
ENDSEQ
  if ( instptr )
    GenerateEvent(DBO_Read);
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

int32 CSNode :: GetCount (logical chknode )
{
  int32   ecnt;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR

  if ( nodenode && !nodenode->IsPositioned() )      ERROR
  ecnt = value_list->GetCount();
RECOVER
  ecnt = 0;
ENDSEQ
  return(ecnt);
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

EB_Number CSNode :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  ENUM_Value    *eval = NULL;
  EB_Number      ebsnum;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR
  if ( indx0 != AUTO )
    Get(indx0);
  if ( !IsPositioned() && nodecur >= 0 )
    Get(nodecur);
  if ( !IsPositioned() )                            ERROR
  
  eval = (ENUM_Value *)nodeinst->get_iselarea(); 
  
  ebsnum = (1 << 31) + eval->code;
RECOVER
  ebsnum = 0;
ENDSEQ
  return(ebsnum);
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

EB_Number CSNode :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  ENUM_Value    *eval = NULL;
  EB_Number      ebsnum;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR
  if ( keyptr )
    Get(keyptr);
  if ( !IsPositioned() && nodecur >= 0 )
    Get(nodecur);
  if ( !IsPositioned() )                            ERROR
  
  eval = (ENUM_Value *)nodeinst->get_iselarea(); 
  
  ebsnum = (1 << 31) + eval->code;
RECOVER
  ebsnum = 0;
ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  GetKey - 



\return key_val - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *CSNode :: GetKey (int32 lindx0, logical chknode )
{
  char *   key_val = NO;
  return( ExtractSortKey(NULL,NULL,chknode) );

}

/******************************************************************************/
/**
\brief  GetKeyLength - 



\return klen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 CSNode :: GetKeyLength ( )
{
  int16   klen = 0;
BEGINSEQ
  if ( Check(NO,NO) )                                     ERROR
  
  klen = value_list->GetKeyLength();
RECOVER
  klen = 0;
ENDSEQ
  return(klen);
}

/******************************************************************************/
/**
\brief  GetKeySMCB - 



\return smcbptr - 

\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeySMCB"

smcb *CSNode :: GetKeySMCB (char *key_name_w )
{
  smcb *   smcbptr = NULL;
BEGINSEQ
  if ( Check(NO,NO) )                                 ERROR

  if ( this )
    smcbptr = nodefield->fmcbsmcb->GetIdentKeySMCB();

RECOVER
  smcbptr = NULL;
ENDSEQ
  return(smcbptr);
}

/******************************************************************************/
/**
\brief  GetNodePtr - 



\return result_field - 

\param  prop_path - Property path
\param  is_transient - 
\param  supress_struct_error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **CSNode :: GetNodePtr (char *prop_path, logical *is_transient, logical supress_struct_error )
{
  node          **pnodeptr = NULL;

BEGINSEQ
  pnodeptr = node::GetNodePtr(prop_path,is_transient,supress_struct_error);
//SDBERR(99)
RECOVER
  pnodeptr = NULL;
ENDSEQ
  return(NULL);
}

/******************************************************************************/
/**
\brief  GetSortKeyLength - 



\return klen - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeyLength"

int16 CSNode :: GetSortKeyLength (logical chknode )
{
  int16   klen = NULL;
BEGINSEQ
  if ( Check(NO,NO) )                                 ERROR
  
  klen = value_list->GetSortKeyLength();
RECOVER
  klen = 0;
ENDSEQ
  return(klen);
}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 



\return smcbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *CSNode :: GetSortKeySMCB ( )
{
  smcb *   smcbptr = NULL;
BEGINSEQ
  if ( Check(NO,NO) )                                 ERROR

  if ( this && id_key )
    smcbptr = id_key->scbsmcb;
RECOVER
  smcbptr = NULL;
ENDSEQ
  return(smcbptr);
}

/******************************************************************************/
/**
\brief  GetString - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *CSNode :: GetString ( )
{
  char *   string = NULL;
BEGINSEQ
  if ( Check(YES,YES) )                             ERROR
  
  string = local_order != CS_VAL 
           ? ExtractSortKey(NULL,NULL)
           : ExtractKey(NULL,NULL); 
           
  set_result_string(string,UNDEF);

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical CSNode :: IsPositioned ( )
{

  return ( this && nodecur != AUTO && nodeinst && nodeinst->get_iselarea() );

}

/******************************************************************************/
/**
\brief  IsSelected - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical CSNode :: IsSelected ( )
{

  return( this && nodecur >= 0 );

}

/******************************************************************************/
/**
\brief  KeyToString - 



\return key_string - 

\param  key_string - 
\param  key_val - 
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyToString"

char *CSNode :: KeyToString (char *key_string, char *key_val, char *key_name_w )
{

  if ( key_string )
    strcpy(key_string,key_val);
  else
    key_string = key_val;
  return(key_string);
}

/******************************************************************************/
/**
\brief  Locate - 



\return term - 

\param  entnr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical CSNode :: Locate (EB_Number entnr, logical read_opt )
{
  int32     indx0 = 0;
  EB_Number ebsnum;
  logical   term = NO;
BEGINSEQ
  Switch(AUTO);
  
  while ( !(ebsnum = GetID(indx0++,NO)).IsEmpty() )
    if ( ebsnum == entnr )                          LEAVESEQ

  Switch(AUTO);                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey - 



\return term - 

\param  skey - 
\param  exact - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical CSNode :: LocateKey (char *skey, logical exact, logical chknode )
{
  logical             term = NO;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                  ERROR

  Switch(AUTO);
  if ( (nodecur = value_list->LocateKey(skey,exact)) == AUTO )
                                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NextKey - 



\return keyptr - 

\param  skey - 
\param  switch_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

char *CSNode :: NextKey (char *skey, int16 switch_level )
{
  char *   keyptr;
BEGINSEQ
  if ( skey )
  {
    if ( !LocateKey(skey,YES,NO) )
    { 
      if ( LocateKey(skey,NO,NO) )                  ERROR
      nodecur--;
    }
  }
  if ( !Get(nodecur+1) )                            ERROR

  keyptr = ExtractSortKey(NULL,NULL);
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  ResetInstance - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

void CSNode :: ResetInstance ( )
{

  nodeinst->set_iselarea(NULL);
  nodecur = AUTO;

}

/******************************************************************************/
/**
\brief  Save - 



\return term - 

\param  switchopt - 
\param  overwrite - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical CSNode :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical   term = NO;
BEGINSEQ
  if ( Check(NO,NO) )                                 ERROR

  if ( switchopt )
    ResetInstance();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetOrder - 



\return term - Termination code

\param  strnames - Type name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical CSNode :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  char                    sk_name[ID_SIZE+1];
  int                     srt_type = UNDEF;
  logical                 term = NO;
BEGINSEQ
  if ( Check(YES,NO) )	                             ERROR
  Switch(AUTO);

  SDBEV1(nodefield->fmcbsmcb->smcbname,ID_SIZE)
  SDBEV2(strnames,ID_SIZE)

  if ( strnames && *strnames )
  {
    gvtxbts(sk_name,strnames,ID_SIZE);
    if ( !stricmp(sk_name,"name") || !stricmp(sk_name,"ik_name"))
      srt_type = CS_STR;
    else if ( !stricmp(sk_name,"code") || !stricmp(sk_name,"ik_code") )
      srt_type = CS_VAL;
    else if ( !stricmp(sk_name,"type") || !stricmp(sk_name,"ik_type") )
      srt_type = CS_TYP;
    else if ( !stricmp(sk_name,"label") || !stricmp(sk_name,"ik_display_name") )
      srt_type = CS_DSP;
    else
if ( !stricmp(sk_name,"ik_string") || !stricmp(sk_name,"sk_value") )
SDBERR(799)
    else                                       SDBERR(79)
  } 
  else
    srt_type = CS_STR;
    
  value_list->ChangeOrder(srt_type);
  SetOrderKey();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetOrderKey - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrderKey"

void CSNode :: SetOrderKey ( )
{
  smcb          *smcbptr = this ? nodefield->fmcbsmcb : NULL;
  id_key = NULL;
  if ( smcbptr && value_list )                                   
    switch ( local_order = value_list->get_order() )
    {
      case CS_STR : id_key = smcbptr->GetKCB("ik_name");
                    break;
      case CS_VAL : id_key = smcbptr->GetKCB("ik_code");
                    break;
      case CS_TYP : id_key = smcbptr->GetKCB("ik_type");
                    break;
      case CS_DSP : id_key = smcbptr->GetKCB("ik_display_name");
                    break;
      default : ;
    }

}

/******************************************************************************/
/**
\brief  StringToKey - 



\return key_val - 

\param  key_string - 
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringToKey"

char *CSNode :: StringToKey (char *key_string, char *key_name_w )
{

  return(key_string);

}

/******************************************************************************/
/**
\brief  ~CSNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSNode"

     CSNode :: ~CSNode ( )
{

  if ( nodeidnt == NODE_ID )
    Close(); 

  if ( nodenode )
    delete value_list;
  value_list = NULL;
  


}


