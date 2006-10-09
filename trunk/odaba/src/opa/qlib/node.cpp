/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    node

\brief    Access node


\date     $Date: 2006/08/29 20:56:17,70 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "node"

#include  <popa7.h>
#include  <cevtp.h>
#include  <gcvb.h>
#include  <nodetst.h>
#ifndef   DLL_PropertyHandle_HPP
#define   DLL_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLO_PropertyHandle_HPP
#define   DLO_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDLO.h>
#endif
#ifndef   DLL_node_HPP
#define   DLL_node_HPP
#include  <snode.hpp>
#include  <sDLL.h>
#endif
#include  <sACElmView.hpp>
#include  <sACExtend.hpp>
#include  <sACGenericAttr.hpp>
#include  <sACMetaAttribute.hpp>
#include  <sACOPGroupBy.hpp>
#include  <sACOPOutput.hpp>
#include  <sACOPProduct.hpp>
#include  <sACOPSelect.hpp>
#include  <sACOPWhere.hpp>
#include  <sACObject.hpp>
#include  <sACPath.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCNode.hpp>
#include  <sCSA_Handle.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sEventLink.hpp>
#include  <sLACObject.hpp>
#include  <sOPBase.hpp>
#include  <sOperEnvironment.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <sSimpleAction.hpp>
#include  <sbnode.hpp>
#include  <sfmcb.hpp>
#include  <sguid.hpp>
#include  <sinti.hpp>
#include  <skcb.hpp>
#include  <snodelist.hpp>
#include  <sref.hpp>
#include  <ssmcb.hpp>
#include  <snode.hpp>

int32 node_count = 0;
int32 node_max = 0;
int32 node_total = 0;

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

void *node :: Add (int32 lindx0, logical global_add )
{

  return(NULL);


}

/******************************************************************************/
/**
\brief  i1 - 



\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *node :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  AddCopy - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCopy"

logical node :: AddCopy (node *nodeptr )
{

  if ( !copies )
    copies = new DLL(node);
  copies->AddTail(nodeptr);
  return(NO);
}

/******************************************************************************/
/**
\brief  AddMetaNode - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddMetaNode"

logical node :: AddMetaNode (node *nodeptr )
{
  logical     term = NO;
BEGINSEQ
  if ( !this || !nodeptr )                           ERROR
  
  if ( !node_meta )
    node_meta = new nodelist();
  
  node_meta->AddTail(nodeptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddReference - 



\return term - Termination code

\param  srcenode - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddReference"

logical node :: AddReference (node *srcenode, int32 lindx0 )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  AllocKeyArea - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocKeyArea"

logical node :: AllocKeyArea ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( key_area )                                    LEAVESEQ

  key_area = new char[MAX_KEYLEN];
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AllocateArea - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateArea"

logical node :: AllocateArea ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !(nodeinst && nodeinst->get_iselarea()) && !flddata )
    dbf::AllocateArea();
  if ( nodeinst )
  {
    if ( !nodeinst->get_iselarea() )
      nodeinst->set_iselarea(flddata);
    else if ( !flddata )
      fld::SetArea(nodeinst->get_iselarea());
    else
      if ( flddata != nodeinst->get_iselarea() )     SDBERR(99)
  }

  if ( nodetype == NT_Node )  // transient node
    nodecur = 0;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AppendString - 



\return term - Termination code

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AppendString"

logical node :: AppendString (char *string )
{
  PropertyHandle    mem_pi;
  logical           term = NO;
BEGINSEQ
  if ( !string || !*string || !flddata || !fldfmcb ) ERROR
  
  if ( !IsText() )
  {
    SDBEV1("AppendString",UNDEF)
    SDBEV2(fldfmcb->fmcbname,sizeof(fldfmcb->fmcbname))
    SDBERR(241)
  }
  
  if ( !Modify() )                                   ERROR

  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxbts(flddata,flddata,fldfmcb->fmcbsize-1);  // das geht so einfach nicht
    
  gvtscat(flddata,fldfmcb->fmcbbyte-1,string,NULL,NULL);
  
  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxstb(flddata,flddata,fldfmcb->fmcbsize);

  if ( IsWrite() && !IsTransient() )
    if ( Store() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AutoLocate - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoLocate"

logical node :: AutoLocate (logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  if ( IsSelected() )                                LEAVESEQ
    
  if ( IsMemo() || IsCollection() )
  {
    if ( GetDimension() == 1 )
    {
      if ( !ProvideArea() )                          ERROR
    }
    else if ( Exist() )
      Get(AUTO,NO);
    if ( !IsSelected() )                             ERROR
  }    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AutoPosition - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoPosition"

logical node :: AutoPosition ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsPositioned() )                              LEAVESEQ

  if ( nodetype == NT_ACGenericAttr ) // bei nächster Gelegenheit virtuell machen und in ACGenAttribute überladen
  {
    if ( !ProvideArea() )                            ERROR
    LEAVESEQ
  }

  if ( nodecur < 0 )                                 ERROR

  if ( !Get() )                                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

guid *node :: BuildGUID (guid *_guid )
{

  return( nodeinst->BuildGUID(_guid) );

}

/******************************************************************************/
/**
\brief  CacheSize - 



\return term - Termination code

\param  bufnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CacheSize"

logical node :: CacheSize (int16 bufnum )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  CanUpdateCollection - 



\return cond - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanUpdateCollection"

logical node :: CanUpdateCollection (logical chknode )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Cancel - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical node :: Cancel (logical chknode )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CancelBuffer - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelBuffer"

logical node :: CancelBuffer ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  CancelNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CancelNode"

logical node :: CancelNode ( )
{

  return(Cancel(NO));

}

/******************************************************************************/
/**
\brief  ChangeBuffer - 



\return bufnum - 

\param  bufnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeBuffer"

int16 node :: ChangeBuffer (int16 bufnum )
{


  return(1);
}

/******************************************************************************/
/**
\brief  ChangeMode - 



\return accopt - Access mode

\param  accopt - Access mode
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeMode"

PIACC node :: ChangeMode (PIACC accopt, char chkopt )
{


  return(PI_undefined);


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

logical node :: Check (logical autoini, logical acccheck )
{
  logical     term = NO;
BEGINSEQ
  if ( autoini && !stscfil() )
  {
    if ( !fldfmcb || !fldfmcb->fmcbbyte )            ERROR
    if ( !flddata )
      if ( AllocateArea() )                          ERROR
    if ( !nodeinst && fldfmcb->fmcbsmcb && 
         fldfmcb->fmcbsmcb->smcbstyp != ST_CODE &&
         fldfmcb->fmcbsmcb->smcbsts.stscnof() )
      CreateInti(this,(DBStructDef *)fldfmcb->fmcbsmcb,flddata);
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDescription - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDescription"

logical node :: CheckDescription ( )
{
  ACObject               *obhandle;
  DBFieldDef             *field_def;
  logical                 term = NO;
BEGINSEQ
  if ( !fldfmcb )                                    ERROR
  if ( fldfmcb->fmcbityp )                           LEAVESEQ
    
  if ( (field_def = fldfmcb->GetDescription()) &&
       *field_def->fmcbtype > ' '              &&
       !field_def->GetDBStruct()                   )
  {
    if ( !(obhandle = GetObjectHandle()) )           ERROR
    if ( !field_def->GetDBStruct(obhandle->GetDictionary()) )
                                                     ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckGenAttribute"

logical node :: CheckGenAttribute ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CheckInlineExpression - 



\return fttype - 

\param  smcbptr - Pointer to general structure definition
\param  path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckInlineExpression"

FunctionTypes node :: CheckInlineExpression (smcb *smcbptr, char *path )
{
  char          *pos;
  FunctionTypes  fttype = FT_undefined;
BEGINSEQ
  if ( *path == '{' )
  {
    if ( !(pos = gvtsfbp(path+1,UNDEF)) )            ERROR
    if ( *pos )                                      ERROR
  }
  fttype = FT_InlineExpression;
RECOVER
  fttype = FT_error;
ENDSEQ
  return(fttype);
}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical node :: CheckModify ( )
{

  return ( highnod && nodenode && GetArea() 
           ? highnod->CheckModify() : NO);
    


}

/******************************************************************************/
/**
\brief  CheckUpdate - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckUpdate"

logical node :: CheckUpdate ( )
{
  node                  **high_node = NULL;
  node                   *coll_node = NULL;
  node                   *inst_node = NULL;
  node                   *gena_node = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( IsCollection() || IsMemo() )
  { 
    coll_node = this;
    coll_node->Check(YES,NO);  
  }
  else if ( high_node = GetHighPIPointer() ) 
    coll_node = *high_node;
  
  if ( coll_node && !coll_node->IsPositioned() && !coll_node->get_nodeinst()->stscini() )
  {
    if ( coll_node->Exist() )
      coll_node->Get(AUTO,NO);  // sonst kein lesen für memo, wenn nodecur == AUTO
      
    if ( !coll_node->IsPositioned() )
    {
      if ( coll_node != this )                   ERROR  // wir wollen keine impliziten Instanzenbildung bei einfachen Attributzuweisungen auf nicht eingestellte PropertyHandle
        
      inst_node = coll_node->get_nodenode();
      while ( inst_node && inst_node->get_nodetype() == NT_ACGenericAttr )
      {
        gena_node = inst_node;
        inst_node = inst_node->get_nodenode();          // die generischen Anteile müssen noch nicht positioniert sein
      }
        
      if ( inst_node && !inst_node->get_nodeinst()->stscini() &&
           !inst_node->IsPositioned() )          ERROR
      if ( gena_node && !gena_node->IsPositioned() )
        gena_node->GetInitInstance();
      coll_node->GetInitInstance();
    }
  }

  if ( IsCollection() && GetDimension() != 1 )
    if ( !IsSelected() )                       SDBERR(517)

  if ( CheckModify() )                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckUpdateSet - 



\return term - Termination code

\param  no_error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckUpdateSet"

logical node :: CheckUpdateSet (logical no_error )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CheckWProtect - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical node :: CheckWProtect ( )
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

logical node :: Close ( )
{
  node              *nodeptr;
  PropertyHandle    *pibptr;
BEGINSEQ
  if ( nodeidnt != NODE_ID )                         LEAVESEQ
  nodeidnt = NODE_IDD;
  
  delete auto_selection;
  auto_selection = NULL;
  
  ReleaseInti();
  
  if ( copies )
  {
    while ( nodeptr = copies->RemoveHead() ) 
      delete nodeptr;
    delete copies;
  }
  copies = NULL;
  
  if ( node_meta )
  {
    while ( nodeptr = node_meta->RemoveHead() ) 
      delete nodeptr;
    delete node_meta;
  }
  node_meta = NULL;
  
  if ( origin )
  {
    origin->RemoveCopy(this);
    origin = NULL;
  }

//  nodeidnt = NODE_IDD;

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  Compare - 



\return cmpval - 

\param  srce_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

char node :: Compare (node *srce_node )
{
  char        cmpval = 0;
  int32       count;
  int32       scount;
  PropertyHandle   l_pi;
  PropertyHandle   r_pi;

BEGINSEQ
  if ( this == srce_node )                           LEAVESEQ
    
  if ( !flddata || !srce_node->flddata ||
       !fldfmcb || !srce_node->fldfmcb    )          ERROR
  
  if ( nodecur == AUTO && !IsCollection() && 
       !(nodeinst && nodeinst->stscini()) )
    Get(FIRST_INSTANCE,NO);
  if ( srce_node->get_nodecur() == AUTO && (srce_node->IsMemo() || !IsCollection()) && 
       !(srce_node->get_nodeinst() && srce_node->get_nodeinst()->stscini()) )
    srce_node->Get(FIRST_INSTANCE);
    
  if ( !IsCollection() )
    cmpval = fldcmp(*srce_node);
  else
  {
    if ( !srce_node->IsCollection() )                ERROR
    
    if ( (count = GetCount()) == ERIC )              ERROR
    if ( (scount = srce_node->GetCount()) == ERIC )  ERROR
    
    count -= scount;
    if ( cmpval = !count ? 0 : count < 0 ? -1 : 1 )  LEAVESEQ
    
    while ( scount-- )
      if ( srce_node->GetID(scount) != GetID(scount) ) ERROR // cannot determin relation
  }
RECOVER
  cmpval = ERIC;

ENDSEQ
  return(cmpval);
}

/******************************************************************************/
/**
\brief  CompareKey - 



\return cmpval - 

\param  skey1 - 
\param  skey2 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareKey"

int8 node :: CompareKey (char *skey1, char *skey2, logical chknode )
{


  return(ERIC);


}

/******************************************************************************/
/**
\brief  CompareSortKey - 



\return cmpval - 

\param  skey1 - 
\param  skey2 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareSortKey"

int8 node :: CompareSortKey (char *skey1, char *skey2, logical chknode )
{

  return(ERIC);


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

logical node :: Contains (char *reg_string, logical case_opt )
{
  int32                    indx0 = 0;
  char                   *prop_path;
  node                  **nodeptr;
  logical                 is_transient;
  logical                 cond = NO;
BEGINSEQ
  if ( !IsPositioned() ) 
  {
    if ( IsMemo() )
      Get(FIRST_INSTANCE);
    else if ( IsSelected() )
      Get(AUTO);
    if ( !IsPositioned() )                           ERROR
  }
  
  if ( fldfmcb->fmcbityp < 0 )   // basic type
  {
    if ( !IsText() )                                 ERROR
    cond = ContainsText((char *)GetArea(),reg_string,fldfmcb->fmcbsize,case_opt);
  }
  else
  {
    while ( (prop_path = GetAttribute(indx0++,NO,YES)) && *prop_path )
    {
      if ( (nodeptr = GetNodePtr(prop_path,&is_transient)) && 
           (cond = (*nodeptr)->Contains(reg_string,case_opt)) )
        LEAVESEQ
    }
    indx0 = 0;
    while ( (prop_path = GetReference(indx0++,NO,NO)) && *prop_path )
    {
      if ( (nodeptr = GetNodePtr(prop_path,&is_transient)) && 
           (*nodeptr)->IsMemo()                               &&
           (cond = (*nodeptr)->Contains(reg_string,case_opt)) )
        LEAVESEQ
    }
  }



RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ConversionError - 



\return error - 

\param  srceinst - 
\param  srcesmcb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConversionError"

int16 node :: ConversionError (void *srceinst, smcb *srcesmcb )
{
  char        string[256];
BEGINSEQ
  if ( SOSERROR == 51 ) 
  {
    SDBEV1(SOSError().get_err_var1(),UNDEF);
    SDBEV2(SOSError().get_err_var2(),UNDEF);
    SDBEV3(SOSError().get_err_var3(),UNDEF);
    SDBEV4(SOSError().get_err_var4(),UNDEF);
  }
  else
  {
    SDBEV1("?",UNDEF);
    SDBEV2(srcesmcb->smcbname,ID_SIZE);
    SDBEV3(fldfmcb->fmcbname,ID_SIZE);
    SDBEV4(fldfmcb->fmcbsmcb->smcbname,ID_SIZE);    
  }
  SDBSET(91);
  
  strcpy(string,"Copy-Error instance '"); 
  srcesmcb->ConvertToString((char *)srceinst,string+strlen(string),48);
  strcat(string,"' from: ");
  gvtxbcs(string,srcesmcb->smcbname,ID_SIZE,sizeof(string)-46);
  strcat(string," to: ");
  strcat(string,GetCurrentType());
  SDBError().TraceMessage(string);

RECOVER

ENDSEQ
  return((int16)SDBERROR);
}

/******************************************************************************/
/**
\brief  CopyBReferences - 



\return term - Termination code

\param  srce_inti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyBReferences"

logical node :: CopyBReferences (inti *srce_inti, PIREPL db_replace, PIREPL copy_type )
{

  return(NO);
 

}

/******************************************************************************/
/**
\brief  CopyInst - 



\return targinst - 
-------------------------------------------------------------------------------
\brief  NODEIC - 



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

void *node :: CopyInst (node *srcenode, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical chknode )
{
  void     *targinst = NULL;

BEGINSEQ
  if ( srcenode == this )                            LEAVESEQ
  if ( !this || !srcenode )                          ERROR
  if ( Check(YES) || srcenode->Check(YES) )          ERROR

  *(dbf *)this = *srcenode;
RECOVER

ENDSEQ
  return(targinst);
}

/******************************************************************************/
/**
\brief  NODEIC_ - 



\param  srceinst - 
\param  srcesmcb - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  set_pos0_w - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInst"

void *node :: CopyInst (void *srceinst, smcb *srcesmcb, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical setwpt )
{
  smcb     *targsmcb;
  char     *targinst;
  int16     converr = NO;
BEGINSEQ
  if ( Check(YES) || !srcesmcb )                     ERROR
  if ( !(targsmcb = GetSMCB(NO)) )                   SDBERR(99)
  
  Initialize_intern(NULL);
  targinst = (char *)GetArea();

  targsmcb->CopyInstance(targinst,srcesmcb,(char *)srceinst,REPL_direct,UNDEF);
  
  if ( w_newkey )
    SetKey(w_newkey,targinst);
RECOVER
  targinst = NULL;

ENDSEQ
  if ( converr && !SDBERROR )
    SDBISET(converr)
  return(targinst);

}

/******************************************************************************/
/**
\brief  CopyInstance - 



\return targinst - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
\param  w_newkey - 
\param  set_pos0_w - 
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstance"

char *node :: CopyInstance (inti *srceinti, PIREPL db_replace, PIREPL copy_type, char *w_newkey, int32 set_pos0_w, logical setwpt )
{
  char                   *targinst = NULL;
  targinst = (char *)CopyInst(srceinti->get_iselarea(),
                              fldfmcb->fmcbsmcb,db_replace,copy_type,
                              w_newkey,set_pos0_w,setwpt);
  return(targinst);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  srce_node - 
\param  db_replace - Replace option
\param  setwpt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstance"

char *node :: CopyInstance (node *srce_node, PIREPL db_replace, logical setwpt )
{
  char         *instance = NULL;
  instance = (char *)CopyInst(srce_node->get_nodeinst()->get_iselarea(),
                              fldfmcb->fmcbsmcb,db_replace,REPL_all,NULL,
                              AUTO,NO);
  return(instance);
}

/******************************************************************************/
/**
\brief  CopyReference - 



\return term - Termination code

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyReference"

logical node :: CopyReference (inti *srceinti, PIREPL db_replace, PIREPL copy_type )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  CopySet - 



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

int32 node :: CopySet (node *srcenode, logical check_inverse, PIREPL db_replace, PIREPL copy_type, logical chknode )
{

  return(NO);  // muß ggf. für Bereiche implementiert werden.

}

/******************************************************************************/
/**
\brief  CreateAccessPath - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  parm_bnf - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *node :: CreateAccessPath (BNFData *parm_bnf, OperEnvironment *operenv )
{

BEGINSEQ
// gibts erst ab bnode (wegen ACObject, das für dumme Nodes nicht da ist)
  SDBERR(99)
RECOVER

ENDSEQ
  return(NULL);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAccessPath"

node *node :: CreateAccessPath (char *prop_path, OperEnvironment *operenv )
{

BEGINSEQ
  SDBERR(99)
RECOVER

ENDSEQ
  return(NULL);
}

/******************************************************************************/
/**
\brief  CreateCopy - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopy"

node *node :: CreateCopy ( )
{
  node              *nodeptr  = NULL;
  node              *tnodeptr = NULL;
  if ( !Check(AUTO,NO) )
  {
    nodeptr = CreateCopyNode();
    if ( nodeptr )
    {
      if ( (tnodeptr = GetNode(YES)) && tnodeptr->Exist() )
        if ( nodeptr->stscusr2() )      // VOID-Extend
          nodeptr->Get(tnodeptr->GetID(AUTO).get_ebsnum());
        else
          nodeptr->Get(tnodeptr->GetCurrentIndex());
    }
  }


  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *node :: CreateCopyNode ( )
{
  node    *nodeptr;
BEGINSEQ
  if ( !(nodeptr = new node(*this)) )                SDBERR(95)
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

inti *node :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti      *intiptr = NULL;
BEGINSEQ
  if ( !instptr )
    instptr = flddata;  // data area aus dbf übernehmen
    
  if ( !(intiptr = new inti(nodeptr,strdef_ptr,instptr,init_nodes)) ) 
                                                      SDBERR(95)
                                                      SDBCERR

RECOVER
  delete intiptr;
  nodeinst = NULL;
  intiptr  = NULL;
ENDSEQ
  return(intiptr);
}

/******************************************************************************/
/**
\brief  CreateOperationNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  op_type - 
\param  rule - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperationNode"

node *__cdecl node :: CreateOperationNode (ACObject *obhandle, node *nodeptr, ST_OpCodes op_type, char *rule, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
{

BEGINSEQ
  SDBRESET
  switch ( op_type )
  {
    case ST_set_from     : nodeptr = new ACOPProduct(obhandle,nodeptr,rule,operenv,accopt);
                           break;
    case ST_set_select   : nodeptr = new ACOPSelect(obhandle,nodeptr,rule,operenv,accopt);
                           break;
    case ST_set_group_by : nodeptr = new ACOPGroupBy(obhandle,nodeptr,rule,operenv,accopt);
                           break;
    case ST_set_where    : nodeptr = new ACOPWhere(obhandle,nodeptr,rule,operenv,accopt);
                           break;
    case ST_file_output  : 
    case ST_db_output    : nodeptr = new ACOPOutput(obhandle,nodeptr,rule,operenv,accopt);
                           break;
    default              :                           SDBERR(99)
  }

  if ( !nodeptr )                                    SDBERR(95)
  SDBCERR

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  op_type - 
\param  bnf_data - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperationNode"

node *__cdecl node :: CreateOperationNode (ACObject *obhandle, node *nodeptr, ST_OpCodes op_type, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
{

BEGINSEQ
  SDBRESET
  switch ( op_type )
  {
    case ST_set_from     : nodeptr = new ACOPProduct(obhandle,nodeptr,bnf_data,operenv,accopt);
                           break;
    case ST_set_select   : nodeptr = new ACOPSelect(obhandle,nodeptr,bnf_data,operenv,accopt);
                           break;
    case ST_set_group_by : nodeptr = new ACOPGroupBy(obhandle,nodeptr,bnf_data,operenv,accopt);
                           break;
    case ST_set_where    : nodeptr = new ACOPWhere(obhandle,nodeptr,bnf_data,operenv,accopt);
                           break;
    case ST_file_output  : 
    case ST_db_output    : nodeptr = new ACOPOutput(obhandle,nodeptr,bnf_data,operenv,accopt);
                           break;
    default              :                           SDBERR(99)
  }

  if ( !nodeptr )                                    SDBERR(95)
  SDBCERR

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreatePathNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  parm_bnf - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *node :: CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv )
{


  return(NULL);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *node :: CreatePathNode (char *prop_path, OperEnvironment *operenv )
{


  return(NULL);
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

node *node :: CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
{
  node    *subnode = NULL;
BEGINSEQ
  switch ( nodetype )
  {
    case  NT_ACAttribute :
    case  NT_Node        : subnode = new node(nodeptr,dbfield_ptr,instptr);
                           if ( nodeptr->IsSelected() )
                             subnode->nodecur = 0;
                           break;
    default              : SDBERR(99)
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
\brief  CreateViewNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  expression - Expression
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateViewNode"

node *node :: CreateViewNode (char *expression, OperEnvironment *operenv )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  bnf_data - 
\param  operenv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateViewNode"

node *node :: CreateViewNode (BNFData *bnf_data, OperEnvironment *operenv )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  NODEID - 



\param  indx0 - Position in collection
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical node :: Delete (int32 indx0, logical chknode, logical del_dep, logical del_inst )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  i1 - 



\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical node :: Delete (char *skey, logical chknode )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  DeleteIndex - 



\return term - Termination code

\param  gen_events - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIndex"

logical node :: DeleteIndex (logical gen_events )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  DeleteIndexEntry - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIndexEntry"

logical node :: DeleteIndexEntry ( )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  DeleteSet - 



\return term - Termination code

\param  chknode - 
\param  del_dep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSet"

logical node :: DeleteSet (logical chknode, logical del_dep )
{

  return(YES);

 

}

/******************************************************************************/
/**
\brief  DeleteSetIndexes - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteSetIndexes"

logical node :: DeleteSetIndexes ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  DisableKeyCheck - 



\return term - Termination code

\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableKeyCheck"

logical node :: DisableKeyCheck (char chkopt )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Distinct - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Distinct"

logical node :: Distinct (node *nodeptr )
{
  smcb            *smcbptr = nodeptr->GetCurrentTypeDef();
  kcb             *kcbptr;
  int32            lindx0 = 0;
  void            *instptr;
  char            *key_name;
  char            *key;
  logical          term = NO;
BEGINSEQ
  if ( !smcbptr )
    if ( !(smcbptr = nodeptr->GetSMCB()) )           SDBERR(99)
    
  if ( !GetSortKeySMCB() )                           SDBERR(99)
  key_name = GetSortKeySMCB()->smcbname;
  if ( !(kcbptr = smcbptr->GetKCB(key_name)) )       SDBERR(99)
    
  while ( nodeptr->Position(1) != AUTO )
  {
    key = nodeptr->ExtractKey(NULL,kcbptr,NULL);
    if ( LocateKey(key,YES) )
      AddReference(nodeptr,AUTO);
  }
  
  Switch(AUTO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

void *node :: Duplicate (char *keyptr, PIREPL db_replace, logical chknode )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  EnableKeyCheck - 



\return term - Termination code

\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableKeyCheck"

logical node :: EnableKeyCheck (char chkopt )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ExecPropCtxFunc - 



\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecPropCtxFunc"

logical node :: ExecPropCtxFunc (char *fnames, char *w_parms )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ExecStrCtxFunc - 



\return term - Termination code

\param  fnames - 
\param  w_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecStrCtxFunc"

logical node :: ExecStrCtxFunc (char *fnames, char *w_parms )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Execute - 



\return term - Termination code

\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical node :: Execute (ParmList *parmlist )
{



  return(NO);
}

/******************************************************************************/
/**
\brief  Exist - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical node :: Exist ( )
{

  return (   ( !nodenode || nodenode->IsSelected() ) && 
             ( nodecur >= 0  || IsMemo() )  ? YES : NO );


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

char *node :: ExtractKey (char *keyptr, void *instptr, logical chknode )
{
 


  return(NULL);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  keyptr - 
\param  kcbptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *node :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{
  char     *skey;

BEGINSEQ
  if ( !instptr )
    if ( !(instptr = IsPositioned() 
                     ? nodeinst->get_iselarea()
                     : Get(AUTO,YES)) )              ERROR

  skey = GetKeyArea();  
  
  if ( kcbptr->scbsmcb->smcbsts.stscnof() )  // __IDENTITY
  {
    if ( !nodeinst->IsPositioned() || instptr != nodeinst->get_iselarea() )
    {
      if ( !nodeinst->GetIdentity() )                ERROR
      *(EB_Number *)skey = *nodeinst->GetIdentity();
    }
    else
      if ( nodeinst->GetIdentity() )  
        *(EB_Number *)skey = *nodeinst->GetIdentity();
      else // nur für nicht-ODABA sinnvoll!!, liefert sonst externe nummer 
        *(EB_Number *)skey = nodeinst->GetID();
  }
  else
    skey = kcbptr->kcbkgt((char *)instptr,skey);

  if ( IsGUID() )
    skey = GUIDToString(NULL,(guid *)skey);
    
  if ( !keyptr )
    keyptr = skey;
  else  
    memcpy(keyptr,skey,kcbptr->kcbklng());

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
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

char *node :: ExtractSortKey (char *keyptr, void *instptr, logical chknode )
{


  return(NULL);

}

/******************************************************************************/
/**
\brief  FillAll - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillAll"

logical node :: FillAll (void *instptr )
{
  logical   term = NO;

BEGINSEQ
  if ( !Get(AUTO) )                                     ERROR
  memcpy(instptr,nodeinst->get_iselarea(),(uint16)fldfmcb->fmcbbyte);

RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillData - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

logical node :: FillData (void *instptr )
{
  smcb     *smcbptr;
  void     *instarea;
  logical   term = NO;

BEGINSEQ
  if ( !instptr || !(instarea = Get(AUTO)) )            ERROR

  smcbptr = fldfmcb->fmcbsmcb;
  smcbptr->smcbfmcl->fmclicpy(smcbptr->smcbfmcl,
                              (char *)instptr,(char *)instarea );

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  FindSource - 



\return srce_fmcb - 

\param  srce_inti - 
\param  offset_ptr - 
\param  pp_srce_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindSource"

fmcb *node :: FindSource (inti *srce_inti, int32 *offset_ptr, node **pp_srce_node )
{
  fmcb          *srce_fmcb = NULL;
  node          *srce_node = NULL;
  char           string[512];

BEGINSEQ
  if ( pp_srce_node )
    *pp_srce_node = NULL;
  
 // 21.5.2003 der zweite versuch koennte nun zuviel liefern
 //           moeglich wird kopieren einer Struktur in eine, die diese exclusiv ableitet
  
  if ( (srce_node = srce_inti->GetPropNode(fldfmcb->fmcbname,prop_path))   ||
       (srce_node = srce_inti->GetPropNode(fldfmcb->fmcbname,(char *)NULL))   ) 
  {
    if ( srce_node->Check(YES) )                     ERROR
    srce_fmcb = srce_node->fldfmcb;  
    if ( pp_srce_node )
      *pp_srce_node = srce_node;
  }
  else
  { 
    if ( !(srce_fmcb = srce_inti->get_struct_def()->
                       SearchField(gvtxbts(string,fldfmcb->fmcbname,ID_SIZE),offset_ptr)) )
                                                     ERROR
    if ( srce_fmcb->GetDescription()->IsPIHandle() )  // R_REFR oder fmcbgentype(PI)
    {
      srce_node = *(node **)(srce_inti->get_iselarea() + srce_fmcb->fmcbposn + *offset_ptr);
      if ( pp_srce_node )
        *pp_srce_node = srce_node;
    }
  }

RECOVER

ENDSEQ
  return(srce_fmcb);
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

char *node :: FirstKey (logical chknode )
{

  return(NULL);


}

/******************************************************************************/
/**
\brief  Format - 



\return string - 

\param  fstring - 
\param  plist - 
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Format"

char *node :: Format (char *fstring, char **plist, int32 count )
{
  int             indx   = 0;
  PropertyHandle *prop_hdl = GetPH();
  logical         positioned = IsSelected();
  char           *string = NULL;
  nstring = fstring;
  
  while ( indx < count )
  {
    if ( !positioned || !(string = plist[indx] ? prop_hdl->GetString(plist[indx]) : NULL) )
    {
      if ( string = GetSysVariable(plist[indx]) )
        if ( !*string )
          string = NULL;
    }
    indx++;
    nstring.ReplaceFirstSymbol("%s",string ? string : "(NULL)");
  }
  string = nstring;
  return(string);
}

/******************************************************************************/
/**
\brief  GUIDToString - 



\return guid_string - 

\param  guid_string - 
\param  _guid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GUIDToString"

char *node :: GUIDToString (char *guid_string, guid *_guid )
{

BEGINSEQ
  if ( !_guid )                                      ERROR
  
  if ( !guid_string )
  {
    nstring.Resize(40);
    guid_string = nstring;
  }
  if ( !_guid->GetString(guid_string) )              ERROR

RECOVER
  guid_string = NULL;
ENDSEQ
  return(guid_string);
}

/******************************************************************************/
/**
\brief  GenerateEvent - 



\return term - Termination code

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical node :: GenerateEvent (DB_Event intevent )
{

  return(NO);

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

void *node :: Get (int32 indx0, logical chknode )
{

  return(dbf::Get(indx0));

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

void *node :: Get (char *skey, logical chknode )
{

  return(NULL);


}

/******************************************************************************/
/**
\brief  i2 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *node :: Get ( )
{

  return(NULL);


}

/******************************************************************************/
/**
\brief  GetArea - 



\return datarea - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

void *node :: GetArea (logical chknode )
{
  void     *datarea = NULL;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                         ERROR

  datarea = (IsCollection() || IsMemo()) && nodeinst 
            ? nodeinst->get_iselarea() 
            : nodecur >= 0 ? dbf::GetArea() : NULL;
//datarea = !IsAttribute() && nodeinst 
//          ? nodeinst->get_iselarea() 
//          : dbf::GetArea();
RECOVER

ENDSEQ
  return(datarea);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

void *node :: GetArea (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  if ( fmcbptr = GetFMCB(prop_path,&offset) )
  {
    datarea = (char *)(nodeinst ? nodeinst->get_iselarea() : dbf::GetArea());
    datarea += offset + fmcbptr->fmcbposn;
  }
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                    ERROR
    datarea = (char *)(*pnodeptr)->GetArea();
  }
RECOVER

ENDSEQ
  return(datarea);
}

/******************************************************************************/
/**
\brief  GetAt - 



\return rindx0 - 

\param  lindx0 - 
\param  direction - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

int32 node :: GetAt (int32 lindx0, int16 direction, logical chknode )
{



  return(AUTO);

}

/******************************************************************************/
/**
\brief  GetAttribute - 



\return fld_path - Property path

\param  indx0 - Position in collection
\param  full_path - 
\param  generic - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttribute"

char *node :: GetAttribute (int32 indx0, logical full_path, logical generic )
{
  char          string[512]; 
  inti         *intiptr;
  char         *fld_path = NULL;
BEGINSEQ
  if ( !(intiptr = nodeinst) && GetNode() )
    intiptr = GetNode()->get_nodeinst();
    
  if ( !GetCurrentTypeDef() || !intiptr )            ERROR

  if ( intiptr->get_struct_def()->GetAttrPath(indx0,full_path,string,sizeof(string)-1,generic) != indx0 )
                                                     ERROR
  set_result_string(string,0);

RECOVER
  set_result_string(NULL,0);
ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetBaseNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseNode"

node **node :: GetBaseNode ( )
{
  static node   *stat_node = NULL;
  return ( &stat_node );

}

/******************************************************************************/
/**
\brief  GetBufferInstance - 



\return instptr - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBufferInstance"

void *node :: GetBufferInstance (int32 indx0 )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetCollectionID - 



\return coll_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollectionID"

int32 node :: GetCollectionID ( )
{

  return(0);

}

/******************************************************************************/
/**
\brief  GetConnectionClient - 



\return client - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient &node :: GetConnectionClient ( )
{

  return(GetMainClient());

}

/******************************************************************************/
/**
\brief  GetContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Property *node :: GetContext ( )
{


  return(NULL);
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

int32 node :: GetCount (logical chknode )
{

  return (fldfmcb ? fldfmcb->fmcbdim : ERIC);


}

/******************************************************************************/
/**
\brief  GetCurrentIndex - 



\return lindx0 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentIndex"

int32 node :: GetCurrentIndex ( )
{

//  return( nodecur != AUTO && stscusr2() ? GetID(AUTO,NO).get_ebsnum() : nodecur);
  
  return( stsctrans() ? ((bnode*)this)->get_relative_index() 
                      : nodecur );


}

/******************************************************************************/
/**
\brief  GetCurrentType - 



\return strnames - Type name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentType"

char *node :: GetCurrentType ( )
{
  DBStructDef *strdef_ptr = NULL;
BEGINSEQ
  if ( strdef_ptr = GetCurrentTypeDef() )
    set_result_string(strdef_ptr->smcbname,ID_SIZE);
  else
  {
    SDBCERR
    if ( Check(YES,NO) )                               ERROR
  
    if ( nodeinst )
      set_result_string(nodeinst->get_field_def()->fmcbtype,ID_SIZE);
    else if ( fldfmcb )
      set_result_string(fldfmcb->fmcbtype,ID_SIZE);;
  }

RECOVER
  set_result_string(NULL,0);
ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCurrentTypeDef - 



\return strdef_ptr - Internal data structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentTypeDef"

DBStructDef *node :: GetCurrentTypeDef ( )
{
  DBStructDef *strdef_ptr = NULL;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
  if ( nodeinst )
    strdef_ptr = nodeinst->get_struct_def();
  else
    strdef_ptr = GetStructDef();

RECOVER

ENDSEQ
  return(strdef_ptr);
}

/******************************************************************************/
/**
\brief  GetDBIndex - 



\return order - 

\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBIndex"

DBIndex *node :: GetDBIndex (char *key_name_w )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetDate - 



\return date_val - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt node :: GetDate (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
  dbdt      date_val;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  datarea = (char *)(nodeinst ? nodeinst->get_iselarea() : dbf::GetArea());
  if ( !prop_path || !*prop_path )
    date_val = GetDate(fldfmcb,datarea);
  else if ( fmcbptr = GetFMCB(prop_path,&offset) )
    date_val = GetDate(fmcbptr,datarea + offset + fmcbptr->fmcbposn);
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                     ERROR
    date_val = (*pnodeptr)->dbf::GetDate();
  }

RECOVER

ENDSEQ
  return(date_val);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt node :: GetDate (fmcb *fmcbptr, void *datarea )
{
  dbdt      date_val;
BEGINSEQ
    if ( fmcbptr->fmcbityp == T_DATE )
      date_val = *(dbdt *)datarea;
    else
    {
      fld     convfld(fmcbptr,datarea );
      date_val = convfld.GetDate();
      if ( dbf::ConversionError(convfld,"DATE") )         ERROR
    }

RECOVER

ENDSEQ
  return(date_val);
}

/******************************************************************************/
/**
\brief  GetDateTime - 



\return datetime_val - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateTime"

dttm node :: GetDateTime (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
  dttm      value;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  datarea = (char *)(nodeinst ? nodeinst->get_iselarea() : dbf::GetArea());
  if ( !prop_path || !*prop_path )
    value = GetDateTime(fldfmcb,datarea);
  else if ( fmcbptr = GetFMCB(prop_path,&offset) )
    value = GetDateTime(fmcbptr,datarea + offset + fmcbptr->fmcbposn);
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                     ERROR
    value = (*pnodeptr)->dbf::GetDateTime();
  }
RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateTime"

dttm node :: GetDateTime (fmcb *fmcbptr, void *datarea )
{
  dttm      value;
BEGINSEQ
  if ( fmcbptr->fmcbityp == T_DATETIME )
    value = *(dttm *)datarea;
  else
  {
    fld     convfld(fmcbptr,datarea);
    value = convfld.GetDateTime();
    if ( dbf::ConversionError(convfld,"DATETIME") ) ERROR
  }

RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  GetDictionary - 



\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

Dictionary *node :: GetDictionary ( )
{
  DBStructDef       *strdef;
  Dictionary        *dict = NULL;
  if ( this && fldfmcb && fldfmcb->fmcbsmcb->IsOdabaDescription() )
  {     
    strdef = (DBStructDef *)fldfmcb->fmcbsmcb;
    dict = strdef->GetDictionary();
  }
  return(dict);
}

/******************************************************************************/
/**
\brief  GetDimension - 



\return pecnt - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDimension"

int32 node :: GetDimension (logical chknode )
{
  int32     dim = AUTO;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                     ERROR
  dim = fldfmcb->fmcbdim;


RECOVER

ENDSEQ
  return(dim);
}

/******************************************************************************/
/**
\brief  GetDouble - 



\return double_val - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double node :: GetDouble (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
  double    value     = 0;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  if ( !prop_path || !*prop_path )
    value = GetDouble(fldfmcb,datarea);
  else if ( fmcbptr = GetFMCB(prop_path,&offset) )
    value = GetDouble(fmcbptr,datarea + offset + fmcbptr->fmcbposn);
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                     ERROR
    value = (*pnodeptr)->dbf::GetDouble();
  }
RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double node :: GetDouble (fmcb *fmcbptr, void *datarea )
{
  double    value     = 0;
BEGINSEQ
  if ( fmcbptr->fmcbityp == T_REAL )
  {
    if ( fmcbptr->fmcbbyte > 4 )
      value = *(double *)datarea;
    else 
      value = *(float *)datarea;
  }
  else
  {
    fld     convfld(fmcbptr,datarea);
    value = convfld.GetDouble();
    if ( dbf::ConversionError(convfld,"REAL") )    ERROR
  }

RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  GetExtInst - 



\return instptr - 

\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInst"

void *node :: GetExtInst (char *extinst )
{
  char     *instptr;

BEGINSEQ
  if ( Check(YES) )                                   ERROR

  if ( Switch(AUTO) )                                 ERROR

  if ( nodeinst->Get(extinst) )                       ERROR
  nodecur = 0;
  instptr = nodeinst->get_iselarea();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  GetExtentName - 



\return extname - Extent name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentName"

char *node :: GetExtentName ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetFMCB - 



\return fmcbptr - 

\param  prop_path - Property path
\param  offset_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFMCB"

fmcb *node :: GetFMCB (char *prop_path, int32 *offset_ptr )
{
  node            *parent_instnode = this;
  char            *path            = prop_path;
  fmcb            *fmcbptr         = NULL;
  smcb            *smcbptr         = NULL;
  char            *spos            = NULL;
  logical          term            = NO;

BEGINSEQ
  if ( !fldfmcb )                                    ERROR
  
  if ( GetNode() != this )
  {
    if ( GetNode()->Check(YES,NO) )                  ERROR
    parent_instnode = GetNode();
  }

  if ( !prop_path || !*prop_path )                   ERROR
  
  if ( !(smcbptr = parent_instnode->GetCurrentTypeDef()) && !(smcbptr = parent_instnode->GetSMCB()) )
                                                     ERROR
  if ( (spos = strchr(prop_path,':')) && 
       (!strchr(prop_path,'.') || spos < strchr(prop_path,'.')) )   // scoped name as '...Person::name'
  {
    *spos = 0;
    term = parent_instnode->SetType(path);
    *spos = ':';
    if ( term )                                      ERROR
    path = spos+2;
    smcbptr = parent_instnode->GetCurrentTypeDef();
  }
  
  if ( !smcbptr->smcbityp )
    smcbptr = GetDictionary()->ProvideStructDef(smcbptr->smcbname);
      
  if ( !(fmcbptr = smcbptr->SearchField(path,offset_ptr)) ) 
                                                     ERROR
RECOVER
  fmcbptr = NULL;
ENDSEQ
  return(fmcbptr);
}

/******************************************************************************/
/**
\brief  GetFieldDef - 



\return fdefptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldDef"

DBFieldDef *node :: GetFieldDef (logical chknode )
{
  DBFieldDef               *fdefptr = NULL;
BEGINSEQ
  if ( chknode && Check(NO,NO) )                        ERROR
  fdefptr = fldfmcb->GetDescription();

RECOVER

ENDSEQ
  return(fdefptr);
}

/******************************************************************************/
/**
\brief  GetFuncResult - 



\return result_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFuncResult"

char *node :: GetFuncResult ( )
{


  return(nstring);
}

/******************************************************************************/
/**
\brief  GetGUID - 



\return id_string - Identifier string

\param  any_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGUID"

char *node :: GetGUID (logical any_id )
{
  guid              *_guid;
  char              *guid = NULL;
  int32               objid;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  if ( !IsPositioned() )                             ERROR
    
  nstring.Resize(40);
  if ( _guid = nodeinst->GetGUID(YES) )
    guid = _guid->GetString(nstring);
  if ( !guid && any_id )
  {
    if ( !(objid = GetID(AUTO,YES,YES).get_ebsnum()) ) ERROR
    gvtxltoa(objid,nstring,10);
    guid = nstring;
  }
RECOVER
  guid = NULL;
ENDSEQ
  return(guid ? guid : "");
}

/******************************************************************************/
/**
\brief  GetGenAttrType - 



\return attrtype - 

\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrType"

int node :: GetGenAttrType (char *fldnames )
{

  return ( UNDEF );


}

/******************************************************************************/
/**
\brief  GetGenOrderType - 



\return attrtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenOrderType"

int node :: GetGenOrderType ( )
{

  return(UNDEF);


}

/******************************************************************************/
/**
\brief  GetGlobalID - 



\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

EB_Number node :: GetGlobalID ( )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  GetHighPIPointer - 



\return pnodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighPIPointer"

node **node :: GetHighPIPointer ( )
{
  node       **nodepptr = NULL;
BEGINSEQ
  if ( !this || Check(NO,NO) )                       ERROR
  
  if ( (nodepptr = &nodenode) && *nodepptr )
    while ( (*nodepptr)->get_nodenode() )
    {
      if ( (*nodepptr)->GetFieldDef(NO)->fmcbrlev == R_REFR )
        break;
      nodepptr = (*nodepptr)->get_nodenode_ptr();
    }
  
  if ( !*nodepptr )                                  ERROR
RECOVER
  nodepptr = NULL;
ENDSEQ
  return(nodepptr);
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

EB_Number node :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
 

  return(0);


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

EB_Number node :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

  return(0);


}

/******************************************************************************/
/**
\brief  GetIdentity - 



\return id_string - Identifier string

\param  id_string - Identifier string
\param  first - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentity"

char *node :: GetIdentity (char *id_string, logical first )
{

  return(id_string ? 
         strcpy(id_string,"") : set_result_string(NULL,0));


}

/******************************************************************************/
/**
\brief  GetInitInstance - 



\return instptr - 

\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitInstance"

void *node :: GetInitInstance (logical set_init )
{
  logical     trans = stsctrans();
  char       *instptr = NULL;
BEGINSEQ
// 9.5.2004 to avoid re-initializing in CheckUpdate()
  if ( IsInitInstance() )                            LEAVESEQ

  if ( nodenode && !nodenode->IsSelected() )
  {
    if ( nodenode->nodetype != NT_ACGenericAttr )    ERROR
    if ( !nodenode->GetInitInstance() )              ERROR
  }
  
  stsrtrans();
  if ( ToTop() )                                     ERROR
  
  if ( !CanUpdateCollection() )                      ERROR
    
  Initialize(NULL,set_init);
  instptr = (char *)GetArea();

RECOVER

ENDSEQ
  if ( trans )
    stsstrans();
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetInstContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstContext"

CTX_Structure *node :: GetInstContext ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetInstFieldDef - 



\return fdefptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstFieldDef"

DBFieldDef *node :: GetInstFieldDef ( )
{

  return ( !CheckDescription() && fldfmcb 
           ? fldfmcb->GetDescription() 
           : NULL );


}

/******************************************************************************/
/**
\brief  GetInstModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 node :: GetInstModCount ( )
{

  return(1);

}

/******************************************************************************/
/**
\brief  GetInt - 



\return int_val - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInt"

int32 node :: GetInt (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
  int32     value     = 0;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  datarea = (char *)(nodeinst ? nodeinst->get_iselarea() : dbf::GetArea());
  if ( !prop_path || !*prop_path )
    value = GetInt(fldfmcb,datarea);
  else if ( fmcbptr = GetFMCB(prop_path,&offset) )
    value = GetInt(fmcbptr,datarea + offset + fmcbptr->fmcbposn);
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                     ERROR
    value = (*pnodeptr)->dbf::GetInt();
  }
RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInt"

int32 node :: GetInt (fmcb *fmcbptr, void *datarea )
{
  int64     val64;
  int32     value     = 0;
BEGINSEQ
  if ( fmcbptr->fmcbityp == T_INT || fmcbptr->fmcbityp == T_UINT )
  {
    val64 = fmcbptr->fmcbligt((char *)datarea);
    if ( fmcbptr->fmcbprec > 0 )
      val64 = val64 / expval[fmcbptr->fmcbprec];
    else if ( fmcbptr->fmcbprec < 0 )
      val64 = val64 * expval[-fmcbptr->fmcbprec];
    value = val64;
  }
  else
  {
    fld     convfld(fmcbptr,datarea);
    value = convfld.GetLong();
    if ( dbf::ConversionError(convfld,"INT") )         ERROR
  }

RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  GetKCB - 



\return kcbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKCB"

kcb *node :: GetKCB ( )
{


  return(NULL);
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

char *node :: GetKey (int32 lindx0, logical chknode )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetKeyArea - 



\return skey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyArea"

char *node :: GetKeyArea ( )
{

  if ( !key_area )
    AllocKeyArea();
  return(key_area);
}

/******************************************************************************/
/**
\brief  GetKeyLength - 



\return klen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 node :: GetKeyLength ( )
{


  return(UNDEF);

}

/******************************************************************************/
/**
\brief  GetKeySMCB - 



\return smcbptr - Pointer to general structure definition

\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeySMCB"

smcb *node :: GetKeySMCB (char *key_name_w )
{
  smcb     *smcbptr = GetCurrentTypeDef();
  if ( !smcbptr )
    smcbptr = GetSMCB();
    
  return( smcbptr 
          ? key_name_w 
            ? smcbptr->GetKeySMCB(key_name_w) 
            : smcbptr->GetIdentKeySMCB()      
          : NULL  );

}

/******************************************************************************/
/**
\brief  GetMetaNode - 



\return nodeptr - 

\param  prop_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMetaNode"

node *node :: GetMetaNode (char *prop_name )
{

  return( node_meta ? node_meta->GetNode(prop_name,GetContext(),NO) : NULL );

}

/******************************************************************************/
/**
\brief  GetMetaNodePtr - 



\return result_field - 

\param  prop_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMetaNodePtr"

node **node :: GetMetaNodePtr (char *prop_name )
{

  return( node_meta ? node_meta->GetNodePtr(prop_name,GetContext(),NO) : NULL );

}

/******************************************************************************/
/**
\brief  GetMode - 



\return accopt - Access mode

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMode"

PIACC node :: GetMode (logical chknode )
{
 PIACC     accmode = PI_undefined;
BEGINSEQ
  if ( chknode && Check(NO,NO) )                       ERROR

  accmode = PI_Update;
RECOVER

ENDSEQ
  return(accmode);
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

node *node :: GetNode (logical autoini )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetNodePtr - 



\return result_field - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  is_transient - 
\param  supress_struct_error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **node :: GetNodePtr (char *prop_path, logical *is_transient, logical supress_struct_error )
{
  node           **pnodeptr        = NULL;
  node            *nodeptr         = NULL;
  node            *parent_instnode = this;
  node            *parent_refnode  = this;
  char            *work_path       = NULL;
  char            *pathptr         = NULL;
  char            *path            = NULL;
  char             path1[ID_SIZE+1];
  char             string[ID_SIZE+1];
  DBFieldDef      *field_def       = NULL;
  fmcb            *fmcbptr         = NULL;
  smcb            *smcbptr         = NULL;
  char            *lastpos         = NULL;
  char            *pos             = NULL;
  char            *par             = NULL;
  char            *spos            = NULL;
  char            *ev1             = NULL;
  char            *ev2             = NULL;
  logical          term            = NO;
  int32            offset          = 0;
  logical          is_top          = YES;
  logical          found           = NO;

BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
  if ( !fldfmcb )                                    ERROR
  
  if ( GetNode() != this )
  {
    if ( GetNode()->Check(YES,NO) )                  ERROR
    parent_instnode = GetNode();
    parent_refnode = GetNode();
  }

  ev1 = prop_path;
  ev2 = fldfmcb->fmcbsmcb ? gvtxbts(string,fldfmcb->fmcbsmcb->smcbname,ID_SIZE) : NULL;
  
  if ( !prop_path || !*prop_path )                   SDBERR2(109,ev1,ev2)
  path = work_path = strdup(prop_path);      
  
  while ( !found )
  {
    if ( !(field_def = parent_instnode->GetFieldDef()) )
                                                     SDBERR2(109,ev1,ev2)
    if ( !(smcbptr = parent_instnode->GetCurrentTypeDef()) && !(smcbptr = parent_instnode->GetSMCB()) )
                                                     ERROR
    if ( (spos = strchr(path,':')) && 
         (!strchr(path,'.') || spos < strchr(path,'.')) )   // scoped name as '...Person::name'
    {
      *spos = 0;
      term = parent_instnode->SetType(path);
      *spos = ':';
      if ( term )                                    SDBERR2(109,ev1,ev2)
      path = spos+2;
      smcbptr = parent_instnode->GetCurrentTypeDef();
    }
  
    if ( !smcbptr->smcbityp )
      smcbptr = GetDictionary()->ProvideStructDef(smcbptr->smcbname);
      
    lastpos = PrevProperty(path+strlen(path),&par,strlen(path));
    offset  = 0;
    if ( !(found = ((fmcbptr = smcbptr->SearchField(path,&offset)) ||
                    (fmcbptr = DBStructDef::GetMetaAttribute(path)) ) ? YES : NO) )
    {
      while ( lastpos && !found )
      {
        *lastpos = 0;
        if ( !(found = ((fmcbptr = smcbptr->SearchField(path,&offset)) ||
                        (fmcbptr = DBStructDef::GetMetaAttribute(path))    ) ? YES : NO) )
	{
          pos = PrevProperty(path+strlen(path),&par,strlen(path));
          *lastpos = '.';
          lastpos  = pos;
        }
      }
          
      if ( !found )
      {
        if ( supress_struct_error )                 ERROR
        else                                        SDBERR2(109,ev1,ev2)
      }
      if ( !(pnodeptr = parent_instnode->GetNodePtr(path)) || !*pnodeptr )
                                                     ERROR
      is_top           = NO;
      found            = NO;
      path             = lastpos+1;
      parent_instnode  = (*pnodeptr)->GetNode();
      if ( fmcbptr->fmcbrlev == R_REFR )
      {
        parent_refnode = (*pnodeptr)->GetNode();
        if ( is_transient && (*pnodeptr)->get_nodetype() == NT_ACTransientReference )
          *is_transient = YES;
      }
      if ( !parent_instnode )                        SDBERR2(109,ev1,ev2)
      if ( parent_instnode->Check(YES,NO) )          ERROR
    }
  }
  
  if ( !fmcbptr )                                    SDBERR2(109,ev1,ev2)
  if ( (field_def = fmcbptr->GetDescription()) && field_def->get_meta_field() != MAT_undefined )
  {
    if ( !(nodeptr = GetMetaNode(fmcbptr->fmcbname)) )
      nodeptr = new ACMetaAttribute(this,field_def);
    if ( !(pnodeptr = GetMetaNodePtr(fmcbptr->fmcbname)) )
                                                     ERROR
  }
  else if ( fmcbptr->GetDescription()->IsPIHandle() )  // R_REFR oder fmcbgentype(PI)
  {
    pnodeptr = (node **)(parent_instnode->get_nodeinst()->get_iselarea() + fmcbptr->fmcbposn + offset);
  }
  else
  {
    pathptr = NextProperty(path,&par) ? path : gvtxbts(path1,fmcbptr->fmcbname,ID_SIZE);
    if ( !(pnodeptr = parent_instnode->GetSubNodePtr(pathptr,NULL)) )
      if ( !(pnodeptr = parent_instnode->get_nodeinst()->ProvideAttrNode(parent_refnode,pathptr,fmcbptr->GetDescription(),offset,GetContext())) )
                                                     SDBERR2(109,ev1,ev2)
  }
  
  if ( par )                                         SDBERR2(99,ev1,ev2)

RECOVER
  pnodeptr = NULL;
ENDSEQ
  if ( work_path )
    free(work_path);
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  prop_path - Property path
\param  operenv - 
\param  path_type - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **node :: GetNodePtr (char *prop_path, OperEnvironment *operenv, FunctionTypes &path_type, PIACC accopt )
{
  node     *nodeptr  = this;
  logical   is_transient = NO;
  node **   pnodeptr = &nodeptr;
BEGINSEQ
  if ( path_type != FT_Property && path_type != FT_MetaAttribute )
  {
    nstring = prop_path;
    if ( prop_path = strchr(nstring,'.') )
    {
      *prop_path = 0;
      prop_path++;
    }
           
    if ( !(nodeptr = GetObjectHandle()->GetStartNode(operenv,nstring,path_type,accopt)) )
                                                    ERROR
  }
  if ( prop_path )
    pnodeptr = nodeptr->GetNodePtr(prop_path,&is_transient); 

RECOVER
  pnodeptr = NULL;
ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  GetOPNode - 



\return op_base - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOPNode"

OPBase *node :: GetOPNode ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetObjectHandle - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandle"

ACObject *node :: GetObjectHandle ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetObjectHandlePtr - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectHandlePtr"

ACObject **node :: GetObjectHandlePtr ( )
{
  static   ACObject  *null_object = NULL;
  return(&null_object);

}

/******************************************************************************/
/**
\brief  GetOrigin - 



\return origin - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrigin"

void *node :: GetOrigin ( )
{

  return ( origin ? origin : this );

}

/******************************************************************************/
/**
\brief  GetPH - 



\return phptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPH"

PropertyHandle *node :: GetPH ( )
{

  return ( this ? (PropertyHandle *)&ph : NULL);

}

/******************************************************************************/
/**
\brief  GetPathBNF - 



\return bdata - 

\param  prop_path - Property path
\param  expr_dup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathBNF"

BNFData *node :: GetPathBNF (char *prop_path, char **expr_dup )
{
  Dictionary         *dictptr;
  BNFData            *bdata   = NULL;
  char               *expression = NULL;
  node               *nodeptr = NULL;
BEGINSEQ
  if ( !(dictptr = GetDictionary()) )                ERROR
    
  if ( !(bdata = dictptr->ParseExpression(prop_path,"simple_op",NULL)) )
                                                     ERROR

RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetPathElement - 



\return prophdl - 

\param  path_element - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathElement"

PropertyHandle *node :: GetPathElement (char *path_element )
{

  return(NULL);


}

/******************************************************************************/
/**
\brief  GetPathString - 



\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathString"

char *node :: GetPathString ( )
{
  NString        rstring;
  nstring = GetPathString(rstring);

  return( nstring );
}

/******************************************************************************/
/**
\brief  i01 - 



\param  rstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPathString"

char *node :: GetPathString (NString &rstring )
{
  char *   keyptr = NULL;
  smcb *   smcbptr = NULL;
  char *   string;
BEGINSEQ
  if ( nodenode )
    string = nodenode->GetPathString(rstring);
  if ( nodetype == NT_ACShareBase )                  LEAVESEQ
  if ( nodenode )
    rstring << '.';
  
  rstring << prop_path;
  if ( IsPositioned() )
  {
    rstring << '(';
    if ( smcbptr = GetSortKeySMCB() )
      keyptr = ExtractSortKey(NULL,NULL);
    else if ( smcbptr = GetKeySMCB() )
      keyptr = ExtractKey(NULL,NULL);
    
    if ( keyptr )
      rstring << '\'' << KeyToString(NULL,keyptr,smcbptr->smcbname) << '\'';
    else 
      rstring << nodecur;
    rstring << ')';
  }
  string = rstring;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetPrivilege - 



\return prvmode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrivilege"

PIADEF node :: GetPrivilege ( )
{
  DBFieldDef  *field_def;
  PIADEF       priv = PI_unknown;
BEGINSEQ
  if ( Check(NO,NO) )                               ERROR

  if ( field_def = GetFieldDef() )
    priv = field_def->get_privilege();


RECOVER

ENDSEQ
  return(priv);
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

node *node :: GetPropNode (char *prop_names, CTX_Property *highprop_ctx )
{
  node                   **pnodeptr = NULL;
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

node *node :: GetPropNode (char *prop_names, char *proppath )
{
  node                   **pnodeptr = NULL;
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

node **node :: GetPropNodePtr (char *prop_names, CTX_Property *highprop_ctx )
{
  node                   **pnodeptr = NULL;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( !nodeinst )                                   ERROR
  pnodeptr = get_nodeinst()->GetPropNodePtr(prop_names,highprop_ctx);
RECOVER

ENDSEQ
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

node **node :: GetPropNodePtr (char *prop_names, char *proppath )
{
  node                   **pnodeptr = NULL;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( !nodeinst )                                   ERROR 
  pnodeptr = get_nodeinst()->GetPropNodePtr(prop_names,proppath);
RECOVER
  pnodeptr = NULL;
ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  GetRefModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 node :: GetRefModCount ( )
{

  return(1);

}

/******************************************************************************/
/**
\brief  GetReference - 



\return fld_path - Property path

\param  indx0 - Position in collection
\param  full_path - 
\param  generic - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReference"

char *node :: GetReference (int32 indx0, logical full_path, logical generic )
{
  char          string[512];
  inti         *intiptr;  
  char         *fld_path = NULL;
BEGINSEQ
  if ( !(intiptr = nodeinst) && GetNode() )
    intiptr = GetNode()->get_nodeinst();
    
  if ( !GetCurrentTypeDef() || !intiptr )            ERROR

  if ( intiptr->get_struct_def()->GetRefPath(indx0,full_path,string,sizeof(string)-1,generic) != indx0 )
                                                     ERROR
  set_result_string(string,0);



RECOVER
  set_result_string(NULL,0);
ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetRelative - 



\return instptr - 

\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelative"

void *node :: GetRelative (int32 indx0, logical chknode )
{

  return(Get(indx0,chknode));

}

/******************************************************************************/
/**
\brief  GetRelativeCount - 



\return ecnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRelativeCount"

int32 node :: GetRelativeCount ( )
{

  return (fldfmcb ? fldfmcb->fmcbdim : ERIC);


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

int32 node :: GetRelativeIndex (logical last_opt, logical chknode )
{


  return( AUTO );
}

/******************************************************************************/
/**
\brief  GetSMCB - 



\return smcbptr - Pointer to general structure definition

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSMCB"

smcb *node :: GetSMCB (logical chknode )
{

  return (   (chknode && Check(YES,NO)) || !fldfmcb 
           ? NULL : fldfmcb->fmcbsmcb);


}

/******************************************************************************/
/**
\brief  GetSelectedKey - 



\return keyptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSelectedKey"

char *node :: GetSelectedKey ( )
{
  char          *keyptr = NULL;

  return(keyptr);
}

/******************************************************************************/
/**
\brief  GetSizeOf - 



\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSizeOf"

uint32 node :: GetSizeOf ( )
{

  return ( Check(YES,NO) || !fldfmcb ? UNDEF : fldfmcb->fmcbsize );


}

/******************************************************************************/
/**
\brief  GetSortKey - 



\return keyname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKey"

char *node :: GetSortKey ( )
{
  smcb                   *smcbptr;
  logical                 term = NO;
BEGINSEQ
  nstring = "";
  if ( !(smcbptr = GetSortKeySMCB()) )               ERROR

  nstring.SetString(smcbptr->smcbname,ID_SIZE);
RECOVER

ENDSEQ
  return( nstring.IsEmpty() ? NULL : (char *)nstring);
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

int16 node :: GetSortKeyLength (logical chknode )
{

  return(UNDEF);


}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 



\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *node :: GetSortKeySMCB ( )
{
  smcb     *smcbptr = NULL;


  return(NULL);

}

/******************************************************************************/
/**
\brief  GetString - 



\return string - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *node :: GetString (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
  char     *value     = "";
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  datarea = (char *)(nodeinst ? nodeinst->get_iselarea() : dbf::GetArea());
  if ( !prop_path || !*prop_path )
    value = GetString(fldfmcb,datarea);
  else if ( fmcbptr = GetFMCB(prop_path,&offset) )
    value = GetString(fmcbptr,datarea + offset + fmcbptr->fmcbposn);
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                     ERROR
    value = (*pnodeptr)->GetString();
  }

RECOVER
  value = "";
ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *node :: GetString (fmcb *fmcbptr, void *datarea )
{
  int32     size;
  int32     level = fmcbptr->fmcbrlev > 0 ? fmcbptr->fmcbrlev : 0;
  char     *value     = "";
BEGINSEQ
  if ( fmcbptr->fmcbityp == T_STRING )
  {
    value = (char *)datarea;
    while ( level )
    {
      value = *(char **)value;
      level--;
    }  
  }
  else if ( fmcbptr->fmcbityp == T_MEMO )
    value = fmcbptr->fmcbrlev == R_REFR 
            ? ((PI(mem) *)datarea)->Get(0L)->memo
            : dbf::GetArea();
  else if ( size = fmcbptr->GetStringLength() )
  {
    nstring.Resize(size);
    fld     string_fld(nstring,size);
    fld     convfld(fmcbptr,datarea);
    string_fld = convfld;
    if ( dbf::ConversionError(*this,"STRING") )    ERROR
    value = nstring;
  }      

RECOVER
  value = "";
ENDSEQ
  return(value ? value : "");
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *node :: GetString ( )
{
  int32    size;
BEGINSEQ
  if ( !fldfmcb )                                    ERROR
  
  if ( size = fldfmcb->GetStringLength() )
  {
    nstring.Resize(size);
    set_result_string(dbf::GetString(nstring,size),UNDEF);
  }
RECOVER
  set_result_string("",UNDEF);
ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetStructDef - 



\return strdef - Structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *node :: GetStructDef ( )
{
  smcb        *smcbptr;
  DBStructDef *strdef_ptr = NULL;

  if ( (smcbptr = GetSMCB()) && smcbptr->smcbsts.stscnof() )
    strdef_ptr = (DBStructDef *)smcbptr;

  return(strdef_ptr);
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

node *node :: GetSubNode (char *prop_names, CTX_Property *highprop_ctx )
{
  node    **pnodeptr = NULL;
  pnodeptr = GetSubNodePtr(prop_names,highprop_ctx);
  return(pnodeptr ? *pnodeptr : NULL);
}

/******************************************************************************/
/**
\brief  GetSubNodePtr - 



\return pnodeptr - 

\param  prop_names - Property name
\param  highprop_ctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubNodePtr"

node **node :: GetSubNodePtr (char *prop_names, CTX_Property *highprop_ctx )
{
  node    **pnodeptr = NULL;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( !nodeinst )                                   ERROR

  pnodeptr = nodeinst->GetSubNodePtr(prop_names,highprop_ctx);
RECOVER

ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  GetTime - 



\return time_val - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prop_path - Property path
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm node :: GetTime (char *prop_path, logical chknode )
{
  int       offset    = NULL;
  fmcb     *fmcbptr   = NULL;
  char     *datarea   = NULL;
  node    **pnodeptr;
  logical  *transient = NO;
  dbtm      value;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR

  datarea = (char *)(nodeinst ? nodeinst->get_iselarea() : dbf::GetArea());
  if ( !prop_path || !*prop_path )
    value = GetTime(fldfmcb,datarea);
  else if ( fmcbptr = GetFMCB(prop_path,&offset) )
    value = GetTime(fmcbptr,datarea + offset + fmcbptr->fmcbposn);
  else
  {
    if ( !(pnodeptr = GetNodePtr(prop_path,transient)) || !*pnodeptr )
                                                     ERROR
    value = (*pnodeptr)->dbf::GetTime();
  }
RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm node :: GetTime (fmcb *fmcbptr, void *datarea )
{
  dbtm      value;
BEGINSEQ
  if ( fmcbptr->fmcbityp == T_TIME )
    value = *(dbtm *)datarea;
  else
  {
    fld     convfld(fmcbptr,datarea);
    value = convfld.GetTime();
    if ( dbf::ConversionError(convfld,"TIME") )    ERROR
  }

RECOVER

ENDSEQ
  return(value);
}

/******************************************************************************/
/**
\brief  GetType - 



\return clname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetType"

char *node :: GetType ( )
{
  char     *clname = NULL;

BEGINSEQ
  if ( Check(NO,NO) )                                  ERROR
  
  if ( fldfmcb )
    clname = fldfmcb->fmcbtype;
    
  set_result_string(clname,ID_SIZE);  

RECOVER

ENDSEQ
  return(nstring);

}

/******************************************************************************/
/**
\brief  GetTypeKey - 



\return tkey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeKey"

TypeKey &node :: GetTypeKey ( )
{


BEGINSEQ
  if ( Check(NO,NO) )                                  ERROR
  
  if ( fldfmcb )
    return( *(TypeKey *)&fldfmcb->fmcbtype );
    


RECOVER

ENDSEQ
  return( *(TypeKey *)NULL );

}

/******************************************************************************/
/**
\brief  GetValue - 



\return instptr - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

void *node :: GetValue (int32 lindx0 )
{
  void        *instptr = NULL;
  if ( IsCollection() )
    instptr = lindx0 == AUTO ? dbf::GetArea() : Get(lindx0);
  else if ( IsMemo() )
  {
    if ( highnod->IsPositioned() )
      instptr = Get(FIRST_INSTANCE);
    if ( !instptr )
      instptr = GetInitInstance();
  }
  else
    instptr = dbf::Get(lindx0);

  return(instptr);
}

/******************************************************************************/
/**
\brief  GetVersion - 



\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 node :: GetVersion ( )
{

  return ( Check(NO,NO) || nodecur == AUTO || !nodeinst 
           ? USHORTMAX 
           : nodeinst->GetVersion() );


}

/******************************************************************************/
/**
\brief  Get_data_nodetype - 



\return node_type - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_data_nodetype"

NodeTypes node :: Get_data_nodetype ( )
{

  return (    nodetype == NT_ClientNode
           ? ((CNode *)this)->get_data_nodetype()
           : nodetype                            );


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

logical node :: Group (node *nodeptr, logical distinct )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  HasFilter - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFilter"

logical node :: HasFilter ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  HasGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasGenAttribute"

logical node :: HasGenAttribute ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  HasIndex - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasIndex"

logical node :: HasIndex ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  HasWorkspace - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasWorkspace"

logical node :: HasWorkspace ( )
{
  LACObject     *lac_object;
  return ( GetObjectHandle() && (lac_object = GetObjectHandle()->GetLocalACObject())
           ? lac_object->HasWorkspace() 
           : NO );
       
       


}

/******************************************************************************/
/**
\brief  Inherits - 



\return cond - 

\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Inherits"

logical node :: Inherits (char *strnames )
{
  char                   *type;
  char                    string[ID_SIZE+1];
  logical                 cond = YES;
BEGINSEQ
  if ( !(type = GetCurrentType()) )                ERROR
  gvtxbts(string,strnames,ID_SIZE);
  if ( !strcmp(string,type) )                      LEAVESEQ
  cond = IsBasedOn(strnames);

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Init - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical node :: Init (void *instptr )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  InitInstance - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInstance"

logical node :: InitInstance (void *instptr )
{
  smcb     *smcbptr;
  logical   term = NO;

BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
  
  if ( nodeinst && (smcbptr = fldfmcb->fmcbsmcb) )
  {  
    if ( !instptr )
      if ( !(instptr = nodeinst->get_iselarea()) )   ERROR
    
    if ( fldfmcb->fmcbrlev != R_DIRECT && fldfmcb->fmcbrlev != R_GENERIC )
      memset(instptr,0,fldfmcb->fmcbbyte);
    else
    {
      if ( nodeinst->get_iselarea() != instptr )
        smcbptr->Initialize((char *)instptr);
      else
        smcbptr->smcbfmcl->fmcliini((char *)instptr);
  
      fldfmcb->GetDescription()->GetDBStruct()->InitAttributes(instptr);
    }
  }
  else if ( instptr )
    fldfmcb->fmcbiini((char *)instptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  InitInti - 



\return term - Termination code

\param  strdefptr - 
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitInti"

logical node :: InitInti (DBStructDef *strdefptr, void *instptr, logical init_nodes )
{
  logical      term = NO;
BEGINSEQ
  if ( !nodeinst )    
  {
    if ( !(nodeinst = /* origin ? origin->CreateInti(this,strdefptr,instptr)
                             : */ CreateInti(this,strdefptr,instptr,init_nodes)        ))
                                                     ERROR
  }
  SetCurrentInti(nodeinst);

RECOVER
  nodeinst = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitReference - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitReference"

logical node :: InitReference ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code

\param  instptr - 
\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical node :: Initialize (void *instptr, logical set_init )
{
  logical                 term = NO;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
    
  if ( Initialize_intern(instptr,set_init) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize_intern - 



\return term - Termination code

\param  instptr - 
\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize_intern"

logical node :: Initialize_intern (void *instptr, logical set_init )
{
  logical                 term = NO;
  if ( nodeinst )
  {
    term = nodeinst->Initialize(instptr,set_init);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  InsertString - 



\return term - Termination code

\param  string - 
\param  position - Position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertString"

logical node :: InsertString (char *string, int32 position )
{
  PropertyHandle    mem_pi;
  logical           term = NO;
BEGINSEQ
  if ( !string || !*string || !flddata || !fldfmcb ) ERROR
  if ( position >= fldfmcb->fmcbbyte )               ERROR
  
  if ( !IsText() )
  {
    SDBEV1("InsertString",UNDEF)
    SDBEV2(fldfmcb->fmcbname,sizeof(fldfmcb->fmcbname))
    SDBERR(241)
  }
  
  if ( !Modify() )                                   ERROR

  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxbts(flddata,flddata,fldfmcb->fmcbsize-1);  // das geht so einfach nicht
    
  gvtssin(flddata+position,string,fldfmcb->fmcbbyte-1-position);
  
  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxstb(flddata,flddata,fldfmcb->fmcbsize);

  if ( IsWrite() && !IsTransient() )
    if ( Store() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InstanceInserted - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceInserted"

logical node :: InstanceInserted ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  InstanceToString - 



\return string - 

\param  string_sep - 
\param  field_sep - 
\param  block_sep - 
\param  empty_string - 
\param  skip_trans - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceToString"

char *node :: InstanceToString (char *string_sep, char *field_sep, char *block_sep, char *empty_string, logical skip_trans )
{
  char                *string = NULL;
  DBStructDef         *strdef;
  int32                len;
  int32                count;
BEGINSEQ
  if ( !IsPositioned() )                             ERROR

  if ( strdef = GetStructDef() )
  {
    len = strdef->GetCharLength();
    count = strdef->GetRecursiveFieldCount();
    if ( string_sep )
      len += 2*count;
    if ( field_sep )
      len += 2*count;
    if ( block_sep )
      len += 2*count;
    nstring.Resize(len,0);
    string = strdef->ConvertToString((char*)GetArea(),nstring,string_sep,field_sep,block_sep,empty_string,len,skip_trans);
  }

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  Intersect - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  sk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

logical node :: Intersect (node *nodeptr, char sk_opt )
{
  int32             lindx0 = GetCount();
  logical          term = NO;
  if ( IsPositioned() )
    Save(YES,NO,NO);

  while ( Get(--lindx0) )
  {
    switch ( sk_opt )
    {
      case YES  : if ( nodeptr->LocateKey(ExtractSortKey(NULL,NULL,NO)) )
                    if ( Delete(AUTO) )
                      term = YES;
                  break;
      case AUTO :
      default   : if ( nodeptr->Locate(GetID(AUTO,NO),NO) )
                    if ( Delete(AUTO) )
                      term = YES;
    }
  }

  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  pi_liste - 
\param  count - 
\param  sk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Intersect"

logical node :: Intersect (PropertyHandle **pi_liste, int32 count, char sk_opt )
{
  char            *keyptr;
  EB_Number        entnr;
  logical          next = YES;
  logical          found;
  node            *nodeptr;
  int32             lindx0 = 0;
  int32             i;
  logical          term = NO;
  DeleteSet();
  
  while ( next )
  {
    switch ( sk_opt )
    {
      case YES  : next = ( keyptr = pi_liste[0]->get_nodeptr()->NextKey(NULL) ) ? YES : NO;
                  break;
      case AUTO : 
      default   : next = pi_liste[0]->get_nodeptr()->Get(lindx0++) ? YES : NO;
    }
    if ( next )
    {
      entnr = pi_liste[0]->get_nodeptr()->GetID(AUTO,NO);
      for ( i = 1; i < count; i++)
      {
        nodeptr = pi_liste[i]->get_nodeptr();
        switch ( sk_opt )
        {
          case YES  : found = nodeptr->LocateKey(keyptr) ? NO : YES;
                      break;
          case AUTO : 
          default   : found = nodeptr->Locate(entnr) ? NO : YES;
        }
        if ( !found )
          break;
      }
      if ( i == count )
        if ( AddReference(nodeptr,AUTO) )
          term = YES;
    }
  }

  Switch(AUTO);
  return(term);
}

/******************************************************************************/
/**
\brief  IsACShareBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsACShareBase"

logical node :: IsACShareBase ( )
{

  return ( this && nodetype == NT_ACShareBase ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttribute"

logical node :: IsAttribute ( )
{

  return(   nodetype == NT_ACAttribute  || 
            nodetype == NT_ACBaseStruct ||
            nodetype == NT_Node            
          ? YES 
          : NO );

}

/******************************************************************************/
/**
\brief  IsAutoPosition - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoPosition"

logical node :: IsAutoPosition ( )
{

  return( auto_position >= 0 || auto_key || auto_selection );

}

/******************************************************************************/
/**
\brief  IsBasedOn - 



\return cond - 

\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasedOn"

logical node :: IsBasedOn (char *strnames )
{
  DBStructDef *strdef_ptr = NULL;
  logical      cond = NO;
  if ( IsPositioned() )
    strdef_ptr = GetCurrentTypeDef();
  else
    strdef_ptr = GetStructDef();

  if ( strdef_ptr )
    cond = strdef_ptr->IsBasedOn(strnames);

  return(cond);
}

/******************************************************************************/
/**
\brief  IsBasetypeProperty - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasetypeProperty"

logical node :: IsBasetypeProperty ( )
{
  DBFieldDef  *field_def;
  logical      cond = YES;
  int32         offset;
BEGINSEQ
  if ( !prop_path || !*prop_path || !nodenode )      ERROR
    
  field_def = nodenode->GetFieldDef(NO);
  
  if ( field_def->IsTyped() )                        LEAVESEQ

  if ( !field_def->fmcbsmcb->SearchField(prop_path,&offset) )
                                                     ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsClientNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsClientNode"

logical node :: IsClientNode ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  IsCollection - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCollection"

logical node :: IsCollection ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsCopyNode - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCopyNode"

logical node :: IsCopyNode ( )
{

  return ( origin ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsDirectField - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDirectField"

logical node :: IsDirectField ( )
{

  return ( YES );

}

/******************************************************************************/
/**
\brief  IsEnumeration - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

logical node :: IsEnumeration ( )
{

  return( fldfmcb && fldfmcb->fmcbsmcb && 
          fldfmcb->fmcbsmcb->smcbstyp == ST_CODE );

}

/******************************************************************************/
/**
\brief  IsGenericAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGenericAttribute"

logical node :: IsGenericAttribute ( )
{

  return( nodetype == NT_ACGenericAttr );  


}

/******************************************************************************/
/**
\brief  IsGlobalInstance - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGlobalInstance"

logical node :: IsGlobalInstance ( )
{
  DBFieldDef             *field_def = GetFieldDef();
  node                   *nodeptr;
  char                   *extent_name;
BEGINSEQ
  if ( global_instance != AUTO )
    return (global_instance);
    
  global_instance = field_def->IsGlobalInstance(GetDictionary(),nodenode ? nodenode->GetCurrentTypeDef() : NULL);
  
/*
  global_instance = YES;
  if ( !field_def || !(extent_name = field_def->GetExtendName()) ||
       *extent_name <= ' ' )                         ERROR

  if ( *extent_name == '#' )                         ERROR    // temporärer Extent
  if ( *extent_name != '.' )                         LEAVESEQ // global Extent oder *

  if ( nodeptr = *GetBaseNode() )
    if ( nodeptr->IsGlobalInstance() )               LEAVESEQ  // globaler Basisextent

  if ( field_def->fmcbrlev == R_REFR || !nodenode )  ERROR
    
  global_instance = nodenode->IsGlobalInstance();
*/
RECOVER
  global_instance = NO;
ENDSEQ
  return(global_instance);
}

/******************************************************************************/
/**
\brief  IsInitInstance - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInitInstance"

logical node :: IsInitInstance ( )
{

// sollte virtuell arbeiten
  
  return ( (nodeinst && nodeinst->stscini()) ||
           ((nodetype == NT_ACAttribute || nodetype == NT_Node) && 
            (highnod && highnod->IsInitInstance() || 
             nodenode && nodenode->IsInitInstance() ) )         );

}

/******************************************************************************/
/**
\brief  IsLocalNode - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalNode"

logical node :: IsLocalNode ( )
{

  return ( AUTO );

}

/******************************************************************************/
/**
\brief  IsMemo - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMemo"

logical node :: IsMemo ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsMetaAttribute - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsMetaAttribute"

logical node :: IsMetaAttribute ( )
{
  DBFieldDef             *fielddef;
  logical                 cond = YES;
BEGINSEQ
  if ( !this || !(fielddef = fldfmcb->GetDescription()) )
                                                      ERROR
  if ( fielddef->get_meta_field() == MAT_undefined )  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsModified - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

logical node :: IsModified ( )
{

  return ( stscmod() || stscsav() || IsInitInstance() ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsNewInstance - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical node :: IsNewInstance ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsNewReference - 



\return term - Termination code

\param  create_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewReference"

logical node :: IsNewReference (logical create_ref )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  IsPathExpression - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPathExpression"

logical node :: IsPathExpression ( )
{

  return( nodetype == NT_ACOPView || stsctrans() || stscold() );

}

/******************************************************************************/
/**
\brief  IsPositioned - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical node :: IsPositioned ( )
{

  return( (!nodenode || nodenode->IsPositioned()) && flddata );  


}

/******************************************************************************/
/**
\brief  IsReadOnly - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical node :: IsReadOnly ( )
{

  return ( fldfmcb->fmcbsensi && 
           nodenode && nodenode->IsGlobalInstance() );


}

/******************************************************************************/
/**
\brief  IsSelected - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical node :: IsSelected ( )
{

  return( (!nodenode || nodenode->IsSelected()) && flddata );  


}

/******************************************************************************/
/**
\brief  IsSensitive - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSensitive"

logical node :: IsSensitive ( )
{

  return ( fldfmcb->fmcbsensi && 
           nodenode && nodenode->IsGlobalInstance() );


}

/******************************************************************************/
/**
\brief  IsServerNode - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsServerNode"

logical node :: IsServerNode ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  IsText - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsText"

logical node :: IsText ( )
{
  logical     cond = YES;
  fmcb       *field_def;
BEGINSEQ
  if ( !(field_def = fldfmcb) )                 ERROR
    
  switch ( field_def->fmcbityp ) 
  {
    case T_CHAR    :
    case T_MEMO    :
    case T_CCHAR   :
    case T_STRING  : LEAVESEQ 
    
    default      : ERROR
  } 

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsTransient - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTransient"

logical node :: IsTransient ( )
{
  DBFieldDef   *field_def = GetFieldDef();
  return (    field_def && ( IsMemo() || IsCollection() || 
                             (nodenode && !nodenode->IsTransient()) )
           ?  field_def->get_transient() 
           :  YES );

}

/******************************************************************************/
/**
\brief  IsTypeVariable - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTypeVariable"

logical node :: IsTypeVariable ( )
{
  DBFieldDef   *field_def = GetFieldDef();
  smcb         *smcbptr;
  return( field_def->get_weak_typed() || 
          ((smcbptr = GetSMCB()) && smcbptr->smcbityp == T_VOID) );


}

/******************************************************************************/
/**
\brief  IsUndefined - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUndefined"

logical node :: IsUndefined ( )
{

  return ( !fldfmcb );

}

/******************************************************************************/
/**
\brief  IsUserHandle - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUserHandle"

logical node :: IsUserHandle ( )
{

  return ( this && use_count > 0 && references.GetCount() ? YES : NO);

}

/******************************************************************************/
/**
\brief  IsValid - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical node :: IsValid ( )
{
  logical                 cond = YES;
BEGINSEQ
  try 
  {
    if ( !this    || 
         (nodeidnt == NODE_ID && stscerr() && !stsclck()) ||    // err+lck: Client-Node durch event disconnected
         nodeidnt == NODE_IDD                     )  ERROR
    if ( nodeidnt != NODE_ID )                       SDBERR(9)
  }
  catch (...)
  {
    SDBERR(9)
  }
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsVariableType - 



\return cond - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsVariableType"

logical node :: IsVariableType (logical chknode )
{
  DBFieldDef   *field_def = GetFieldDef(chknode);
  smcb         *smcbptr;
  return( field_def->get_weak_typed() || 
          ((smcbptr = GetSMCB(NO)) && smcbptr->smcbityp == T_VOID 
            && !GetCount()) );


}

/******************************************************************************/
/**
\brief  IsWrite - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWrite"

logical node :: IsWrite ( )
{

  return ( YES );


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

char *node :: KeyToString (char *key_string, char *key_val, char *key_name_w )
{
  char            keystr[MAX_KEYLEN*2];
  char           *keyptr = keystr;
  smcb           *smcbptr;
BEGINSEQ
  if ( Check(YES,NO) )                              ERROR
    
  if ( fldfmcb && fldfmcb->fmcbityp == 72 )  // __OBJECT
    keyptr = GetGUID(NO);
  else
  {
    if ( key_name_w ) 
      smcbptr = GetKeySMCB(key_name_w);
    else
      if ( !(smcbptr = GetSortKeySMCB()) )
        smcbptr = GetKeySMCB();

    if ( !smcbptr )                                 ERROR
    
    smcbptr->ConvertToString(key_val,keystr,255);
  }
  if ( key_string )
    strcpy(key_string,keyptr);
  else
  {
    set_result_string(keyptr,UNDEF);
    key_string = nstring;
  }

RECOVER
  key_string = NULL;
ENDSEQ
  return(key_string);
}

/******************************************************************************/
/**
\brief  Locate - 



\return term - Termination code

\param  entnr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical node :: Locate (EB_Number entnr, logical read_opt )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  LocateIndex - 



\return term - Termination code

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateIndex"

logical node :: LocateIndex (int32 lindx0, logical chknode )
{
  logical        term = NO;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR
  
  if ( nodecur == lindx0 )                           LEAVESEQ
  Switch(AUTO);
  
  if ( GetCount() <= lindx0 )                        ERROR
  
  nodecur = lindx0;
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  LocateKey - 



\return term - Termination code

\param  skey - 
\param  exact - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical node :: LocateKey (char *skey, logical exact, logical chknode )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  LocatePIRef - 



\return term - Termination code

\param  pibptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocatePIRef"

logical node :: LocatePIRef (PropertyHandle *pibptr )
{

  return( this ? !references.Find((ObjectReferenceHandle *)pibptr) : YES );

}

/******************************************************************************/
/**
\brief  LocatePath - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocatePath"

logical node :: LocatePath ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsPositioned() )                              LEAVESEQ
  if ( nodenode && nodenode->LocatePath() )          ERROR

  if ( !Get(FIRST_INSTANCE) )                        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical node :: Lock ( )
{
 

  return(YES);
 

}

/******************************************************************************/
/**
\brief  LockSet - 



\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockSet"

logical node :: LockSet (logical chknode )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Minus - 



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

logical node :: Minus (node *node1, node *node2, char sk_opt )
{
  char            *keyptr;
  int32             lindx0 = 0;
  logical          term = NO;
  DeleteSet();
  
  switch ( sk_opt )
  {
    case  YES  : while ( keyptr = node1->NextKey(NULL) )
                   if ( node2->LocateKey(keyptr) )
                     if ( AddReference(node1,AUTO) )
                       term = YES;
                 break;
    case  AUTO : 
    default    : while ( node1->Get(lindx0++) )
                   if ( node2->Locate(node1->GetID(AUTO,NO),NO) )
                     if ( AddReference(node1,AUTO) )
                       term = YES;
  }

  Switch(AUTO);
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

logical node :: Minus (node *nodeptr, char sk_opt )
{
  int32             lindx0 = 0;
  logical          term = NO;
  while ( nodeptr->Get(lindx0++) )
  {
    switch ( sk_opt )
    {
      case YES  : if ( !LocateKey(nodeptr->ExtractSortKey(NULL,NULL,NO)) )
                    if ( Delete(AUTO) )
                      term = YES;
                  break;
      case AUTO :
      default   : if ( !Locate(nodeptr->GetID(AUTO,NO)) )
                    if ( Delete(AUTO) )
                      term = YES;
    }
  }

  return(term);
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

void *node :: Modify (logical chknode )
{

  if ( nodecur == AUTO )
    nodecur = 0;
    
  if ( nodenode && highnod )
    return(highnod->Modify());
    
  return(flddata ? flddata : "");

}

/******************************************************************************/
/**
\brief  Move - 



\return targinst - 

\param  srcenode - 
\param  db_replace - Replace option
\param  w_newkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

void *node :: Move (node *srcenode, PIREPL db_replace, char *w_newkey, logical chknode )
{
  void     *targinst = NULL;


  return(targinst);
}

/******************************************************************************/
/**
\brief  MoveDown - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical node :: MoveDown ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  MoveUp - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical node :: MoveUp ( )
{

  return(YES);

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

char *node :: NextKey (char *skey, int16 switch_level )
{

  return(NULL);


}

/******************************************************************************/
/**
\brief  OBHOutputResult - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBHOutputResult"

void node :: OBHOutputResult (char *string )
{

  GetObjectHandle()->OutputResult(string);

}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00 - 



\param  nodeptr - 
\param  dbfield_ptr - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical node :: Open (node *nodeptr, DBFieldDef *dbfield_ptr )
{
  logical    term = NO;
  nodenode = nodeptr;
  nodeidnt = NODE_ID;

  if ( dbfield_ptr )
  {
    if ( dbfield_ptr->fmcbrlev == R_REFR ) 
    {
      CopyDescription(dbfield_ptr);
      Dereference(NULL);
  
      if ( dbfield_ptr->fmcbityp == T_MEMO )
      {
        fldfmcb->fmcbbyte = (fldfmcb->fmcbsize = dbfield_ptr->fmcbsize)+1;
        fldfmcb->fmcbityp = T_STRING;
        fldfmcb->fmcbsmcb = NULL;
        gvtxstb(fldfmcb->fmcbtype,"STRING",ID_SIZE);
      }
      else if ( dbfield_ptr->fmcbityp == T_BLOB )
      {
        fldfmcb->fmcbbyte = (fldfmcb->fmcbsize = dbfield_ptr->fmcbsize);
        fldfmcb->fmcbityp = T_VOID;
        fldfmcb->fmcbsmcb = NULL;
        gvtxstb(fldfmcb->fmcbtype,"VOID",ID_SIZE);
      }
    }
    else
      SetFMCB(dbfield_ptr);
  }
  Connect(nodeptr);


  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical node :: Open ( )
{
  logical                 term = NO;
  nodeidnt = NODE_ID;
  // ggf. inti aus datarea setzen!!


__Increase();
  return(term);
}

/******************************************************************************/
/**
\brief  OutputResult - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OutputResult"

void node :: OutputResult (char *string )
{

  if ( this )
  {
    if ( IsClientNode() )
      printf(string);
    else
      nstring += string;
  }

}

/******************************************************************************/
/**
\brief  PathCreateCopy - 



\return nodeptr - 

\param  top_node - 
\param  accmode - 
\param  copy_selection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PathCreateCopy"

node *node :: PathCreateCopy (node *top_node, PIACC accmode, logical copy_selection )
{

  return ( CreateCopyNode() );

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

int32 node :: Position (int32 count, logical chknode )
{
  int32            indx0 = AUTO;
BEGINSEQ
  if ( nodecur+count < 0 )                          ERROR

  if ( !Get(nodecur+count) )                        ERROR
  
  indx0 = nodecur;
RECOVER
  indx0 = AUTO;
ENDSEQ
  return(indx0);

}

/******************************************************************************/
/**
\brief  PositionExpression - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  expr_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionExpression"

void *node :: PositionExpression (char *expr_string )
{
  char                   *end;
  char                   *key     = NULL;
  void                   *instptr = NULL;
BEGINSEQ
  if ( !expr_string || !*expr_string )               LEAVESEQ
  if ( nodenode && !nodenode->IsSelected() )         ERROR
  key = strdup(expr_string);

  if ( !(end = gvtsfbp(key,UNDEF)) )                 SDBERR(99)

  *(end-1) = 0;
  
  if ( !(instptr = PositionExpression(key+1,*key)) ) ERROR

RECOVER
  instptr = NULL;
ENDSEQ
  if ( key )
    free(key);
  return(instptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  expr_string - 
\param  expr_char - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionExpression"

void *node :: PositionExpression (char *expr_string, char expr_char )
{
  logical                 number = YES;
  int32                   klen   = 0;
  char                    keyarea[MAX_KEYLEN];
  char                   *end;
  int32                   num_val;
  char                   *keyptr;
  void                   *instptr = NULL;
BEGINSEQ
  if ( isdigit(*expr_string) )
    num_val = atol(expr_string);
  else
  {
    if ( *expr_string == '\'' || *expr_string == '"')
    {
      if ( !(end = gvtsfbp(expr_string,UNDEF)) )   SDBERR(344)
      *(end-1) = 0;
      expr_string++;
    }
    if ( !(keyptr = StringToKey(expr_string,NULL)) ) ERROR
    if ( !(klen = GetSortKeyLength(NO)) )
      if ( !(klen = GetKeyLength()) )                ERROR
    memcpy(keyarea,keyptr,klen);
    number = NO;
  }

  switch ( expr_char )
  {
    case '[': if ( GetMode() > PI_Read && (!nodenode || nodenode->IsWrite()) )
              {
                if ( CheckGenAttribute() )             ERROR
                if ( nodenode && !nodenode->IsPositioned() )
                  if ( nodenode->get_nodeinst()->stscini() )
                    if ( nodenode->Modify() )
                      nodenode->Save(NO,NO,NO);
                if ( nodenode && !nodenode->IsPositioned() )
                                                     ERROR
                if ( !(instptr = number ? Get(num_val,YES) : Get(keyarea,YES)) )
                  if ( !CheckUpdateSet(NO) )
                    instptr = number ? Provide(num_val,YES) : Provide(keyarea,YES);
                break;
              }
    case '(': instptr = number ? Get(num_val,YES) : Get(keyarea,YES);
              break;
    case '{':                                        SDBERR(343)
              break;
    default :                                        SDBERR(99)
  }

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  PositionTop - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop"

logical node :: PositionTop ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( nodenode )
  {
    if ( nodenode->PositionTop() )                   ERROR
    if ( !nodenode->IsPositioned() )
      if ( !nodenode->Get(FIRST_INSTANCE) )          ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PositionTop_intern - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop_intern"

node *node :: PositionTop_intern ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  PrepareGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrepareGenAttribute"

logical node :: PrepareGenAttribute ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ProvGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvGenAttribute"

logical node :: ProvGenAttribute ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Provide - 



\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEKP - 



\param  skey - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *node :: Provide (char *skey, logical global_add )
{

BEGINSEQ
  return(NULL);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *node :: Provide (int32 lindx0, logical global_add )
{
 

  return(NULL);
 

}

/******************************************************************************/
/**
\brief  i2 - 



\param  datarea - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *node :: Provide (void *datarea, logical global_add )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  ProvideArea - 



\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideArea"

void *node :: ProvideArea ( )
{
  void                 *instptr = NULL;
BEGINSEQ
// virtuell machen und in AC_ShareBase und GenAttribute überladen
  if ( nodetype == NT_ACGenericAttr )
  {
    SetGenAttribute();
    if ( !nodeinst )                                 ERROR
    instptr = nodeinst->get_iselarea();              
    LEAVESEQ
  }

  if ( !IsCollection() && nodetype != NT_ACShareBase )
    if ( !IsInitInstance() )
      if ( !Get() && !Get(FIRST_INSTANCE,YES) )
        if ( GetMode() > PI_Read )
          GetInitInstance();
    
  if ( IsSelected() || IsInitInstance() )
    instptr = GetArea();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  ProvideGUID - 



\return guid_string - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideGUID"

char *node :: ProvideGUID (logical chknode )
{
  guid              *_guid;
  char              *guid = NULL;
BEGINSEQ
  if ( chknode )
  {
    if ( Check(YES) )                                ERROR
    if ( !IsPositioned() )                           ERROR
  }
  if ( guid = GetGUID(NO) )                          LEAVESEQ
  
  if ( !(_guid = nodeinst->GetGUID(NO)) )            ERROR
  BuildGUID(_guid);
  if ( nodeinst->CreateGUID(_guid) )                 ERROR
  stssmod();    
  nodeinst->stssmod();
  
  guid = GetGUID();
RECOVER
  guid = NULL;
ENDSEQ
  return(guid);
}

/******************************************************************************/
/**
\brief  ReadBuffer - 



\return count - 

\param  lindx0 - 
\param  direction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBuffer"

int32 node :: ReadBuffer (int32 lindx0, int16 direction )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical node :: Refresh ( )
{
  logical    term = NO;
BEGINSEQ
  if ( highnod && !highnod->IsPositioned() )
  {
    highnod->PositionTop();
    highnod->Get(AUTO);
  }      
    
  if ( GenerateEvent(DBO_Refresh) )                  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical node :: RegisterHandle (CSA_Handle *cs_handle )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ReleaseBuffer - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseBuffer"

logical node :: ReleaseBuffer ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ReleaseInti - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseInti"

void node :: ReleaseInti ( )
{

  if ( nodeinst )
  {
    if ( flddaloc && flddata == nodeinst->get_iselarea() )
      nodeinst->set_iselarea(NULL);
    delete nodeinst;
    nodeinst = NULL;
  }


}

/******************************************************************************/
/**
\brief  RemoveCopy - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveCopy"

logical node :: RemoveCopy (node *nodeptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !copies )                                     SDBERR(99)
  
  if ( copies->Find(nodeptr) )
    copies->RemoveAt();

RECOVER
  term = YES;
ENDSEQ
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

logical node :: RemoveFromCollection ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  RemoveMetaNode - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveMetaNode"

logical node :: RemoveMetaNode (node *nodeptr )
{
  logical     term = NO;
BEGINSEQ
  if ( !this || !nodeptr )                           ERROR
  
  if ( node_meta )
    node_meta->Remove(nodeptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveString - 



\return term - Termination code

\param  string - 
\param  position - Position
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveString"

logical node :: RemoveString (char *string, int32 position, uint16 len )
{
  PropertyHandle    mem_pi;
  logical           term = NO;
BEGINSEQ
  if ( !string || !*string || !flddata || !fldfmcb ) ERROR
  if ( position >= fldfmcb->fmcbbyte )               ERROR
  if ( len <= 0 || position+len >= fldfmcb->fmcbbyte )      
    len = fldfmcb->fmcbbyte - position - 1;
  
  if ( !IsText() )
  {
    SDBEV1("InsertString",UNDEF)
    SDBEV2(fldfmcb->fmcbname,sizeof(fldfmcb->fmcbname))
    SDBERR(241)
  }
  
  if ( !Modify() )                                   ERROR

  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxbts(flddata,flddata,fldfmcb->fmcbsize-1);  // das geht so einfach nicht
    
  strncpy(flddata+position,flddata+position+len,fldfmcb->fmcbbyte-1-position-len);
  
  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxstb(flddata,flddata,fldfmcb->fmcbsize);

  if ( IsWrite() && !IsTransient() )
    if ( Store() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Rename - 



\return term - Termination code

\param  identkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rename"

logical node :: Rename (char *identkey, logical chknode )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  RenameHandle - 



\return term - Termination code

\param  var_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RenameHandle"

logical node :: RenameHandle (char *var_name )
{
  DBFieldDef             *fielddef = NULL;
  char                    vname[ID_SIZE];
  logical                 term = NO;
BEGINSEQ
  if ( !this || !fldfmcb )                           ERROR
    
  gvtxstb(vname,var_name,ID_SIZE);
  if ( !memcmp(fldfmcb->fmcbname,vname,ID_SIZE) )    LEAVESEQ

  if ( !fldfaloc )
  {
    if ( fielddef = GetFieldDef() )
    {
      AllocDescription();
      *GetFieldDef() = *fielddef;
    }
    else
      SetupDescription();
  }
  
  memcpy(fldfmcb->fmcbname,vname,ID_SIZE);

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical node :: RepairIndex (char *key_name, char *attrstr )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  Replace - 



\return term - Termination code

\param  old_str - Old string value
\param  new_str - New string value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

logical node :: Replace (char *old_str, char *new_str )
{
  PropertyHandle    mem_pi;
  logical           term = NO;
BEGINSEQ
  if ( !old_str || !*old_str || !new_str || !flddata || !fldfmcb )
                                                     ERROR
  ReplaceControlSequences(old_str,UNDEF,NO);
  ReplaceControlSequences(new_str,UNDEF,NO);
  
  if ( !IsText() )
  {
    SDBEV1("ReplaceString",UNDEF)
    SDBEV2(fldfmcb->fmcbname,sizeof(fldfmcb->fmcbname))
    SDBERR(241)
  }
  
  if ( !Modify() )                                   ERROR

  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxbts(flddata,flddata,fldfmcb->fmcbsize-1);  // das geht so einfach nicht
    
  gvtsexc(flddata,old_str,new_str,fldfmcb->fmcbbyte-1);
  
  if ( fldfmcb->fmcbityp == T_CHAR || fldfmcb->fmcbityp == T_CCHAR )
    gvtxstb(flddata,flddata,fldfmcb->fmcbsize);

  if ( IsWrite() && !IsTransient() )
    if ( Store() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceSysVar - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSysVar"

logical node :: ReplaceSysVar ( )
{
  PropertyHandle    mem_pi;
  logical           term = NO;
BEGINSEQ
  if ( !flddata || !fldfmcb )                        LEAVESEQ
    
  if ( !IsText() )
  {
    SDBEV1("ReplaceSysVariables",UNDEF)
    SDBEV2(fldfmcb->fmcbname,sizeof(fldfmcb->fmcbname))
    SDBERR(241)
  }
  
  if ( !Modify() )                                   ERROR

  ReplaceSysVariable(flddata,fldfmcb->fmcbsize);

  if ( IsWrite() && !IsTransient() )
    if ( Store() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical node :: Reset ( )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  ResetCopyNodes - 




\param  node_ptr - 
\param  obj_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCopyNodes"

void node :: ResetCopyNodes (node *node_ptr, int64 obj_id )
{
  node        *nodeptr;
  if ( copies )
  {
    copies->GoTop();
    while ( nodeptr = copies->GetNext() ) 
      if ( nodeptr != node_ptr && nodeptr->IsPositioned() && 
           Bnodeptr->get_objid() == obj_id                   )
        nodeptr->Cancel(NO);
  }
  if ( this != node_ptr )
    Cancel(NO);

}

/******************************************************************************/
/**
\brief  ResetExpression - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetExpression"

logical node :: ResetExpression ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ResetGenAttribute - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetGenAttribute"

logical node :: ResetGenAttribute ( )
{

  return(NO);
 ;
}

/******************************************************************************/
/**
\brief  ResetInitInstance - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInitInstance"

void node :: ResetInitInstance ( )
{

  nodeinst->ResetInitialized();

}

/******************************************************************************/
/**
\brief  ResetInstance - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstance"

void node :: ResetInstance ( )
{

BEGINSEQ
  if ( !stscfil() || stscerr() )                     LEAVESEQ
    
  if ( nodeinst && nodeinst->IsSelected() )
  {
    nodeinst->ResetNodes();
    nodeinst->Reset();  
    nodeinst->stsrdel();  // wird in binti::DeleteRelationships() gesetzt
  }
     
  nodecur      = AUTO;
  stsrsav();
  stsrmod();
  stsrwpt();
ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetInstanceEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceEventHandler"

void node :: ResetInstanceEventHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  ResetInstanceProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetInstanceProcessHandler"

void node :: ResetInstanceProcessHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  ResetNode - 



\return reset - 

\param  reset_all - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNode"

logical node :: ResetNode (logical reset_all )
{
  node            *cpy_node;
  logical          reset = YES;
BEGINSEQ
  if ( stscfil() || (nodeinst && nodeinst->stscini()) )  
    ResetInstance();
  
  if ( stscerr() || !stscfil() )                     ERROR
    
  if ( origin && reset_all ) 
    origin->ResetNode(YES);
  else
  {
    if ( nodeinst )
      nodeinst->ResetNodes();
  
    if ( reset_all && copies )
    {
      copies->GoTop();
      while ( cpy_node = (bnode *)copies->GetNext() ) 
        cpy_node->ResetNode(NO);     // copy node do not have copies
    }
  }  

  stsrfil();
RECOVER
  reset = NO;
ENDSEQ
  return(reset);

}

/******************************************************************************/
/**
\brief  ResetOnError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetOnError"

void node :: ResetOnError ( )
{
  PropertyHandle  *pibptr;
  while ( pibptr = (PropertyHandle *)references.RemoveTail() )
    pibptr->Close();
  
  stsserr();

}

/******************************************************************************/
/**
\brief  ResetPIRef - 



\return term - Termination code

\param  pibptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPIRef"

logical node :: ResetPIRef (PropertyHandle *pibptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  ObjectReference::Disconnect((ObjectReferenceHandle *)pibptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetPropertyEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyEventHandler"

void node :: ResetPropertyEventHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  ResetPropertyProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetPropertyProcessHandler"

void node :: ResetPropertyProcessHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  ResetReference - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetReference"

logical node :: ResetReference ( )
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

logical node :: ResetWProtect ( )
{

  return(NO);


}

/******************************************************************************/
/**
\brief  Save - 



\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical node :: Save (logical switchopt, logical overwrite, logical chknode )
{
 

  return(YES);
  

}

/******************************************************************************/
/**
\brief  SaveKey - 



\return term - Termination code

\param  savekey - 
\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveKey"

logical node :: SaveKey (char *savekey, char *skey )
{
  int16     klen;
BEGINSEQ
  if ( stscusr2() )         // VOID-Extend
                                                     SDBERR(777)
  else  
    if ( !(klen = GetSortKeyLength(NO)) )
      klen = GetKeyLength();
    
  if ( klen )  
    memcpy(savekey,skey,klen);

RECOVER

ENDSEQ
  return(NO);

}

/******************************************************************************/
/**
\brief  SaveNode - 



\return term - Termination code

\param  switchopt - 
\param  overwrite - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveNode"

logical node :: SaveNode (logical switchopt, logical overwrite )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Select - 



\return term - Termination code

\param  nodeptr - 
\param  expression - Expression
\param  min_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

logical node :: Select (node *nodeptr, char *expression, int32 min_inst )
{

BEGINSEQ
  return(YES);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Set - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Set"

logical node :: Set (node *nodeptr )
{


  return(YES);
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

logical node :: SetAction (SimpleAction *simple_action )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  SetArea - 



\return instptr - 

\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetArea"

void *node :: SetArea (void *datarea )
{

  if ( nodeinst && nodeinst->get_iselarea() != datarea )
  {
    if ( !flddaloc || !datarea )
    {
      delete nodeinst;
      nodeinst = NULL;
    }
    else
      nodeinst->set_iselarea(datarea);
  }
  if ( datarea && IsAttribute() )
    nodecur = 0;
  return( fld::SetArea((char *)datarea) );

}

/******************************************************************************/
/**
\brief  SetAutoLocate - 




\param  auto_pos - 
\param  keyptr - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoLocate"

void node :: SetAutoLocate (int32 auto_pos, char *keyptr, logical provide )
{
  int32           klen;
BEGINSEQ
  auto_provide = provide;
  auto_position = auto_pos;
  if ( keyptr && *keyptr )
  {
    if ( !(klen = GetSortKeyLength()) )
      if ( !(klen = GetKeyLength()) )                SDBERR(344)
    auto_key = new char[klen];
    if ( !(keyptr = StringToKey(keyptr,NULL)) )      ERROR
    memcpy(auto_key,keyptr,klen);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetAutoLocateExpression - 



\return term - Termination code

\param  expression - Expression
\param  operenv - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoLocateExpression"

logical node :: SetAutoLocateExpression (char *expression, OperEnvironment *operenv, logical provide )
{
  Dictionary     *dictionary  = GetDictionary();
  ACObject       *resobj      = dictionary;
  ACObject       *obhandle    = GetObjectHandle();
  logical         term        = NO;
BEGINSEQ
  auto_provide = provide;
  auto_selection = new Operation(*GetPH(),operenv);

  if ( operenv )
  {
    if ( operenv->DictHandle() )
      resobj = dictionary = operenv->DictHandle();
    if ( operenv->ResOBHandle() )
      resobj = operenv->ResOBHandle();
    if ( operenv->ObjectHandle() )
      obhandle = operenv->ObjectHandle();
  }
  if ( auto_selection->ProvExpression(dictionary,resobj,obhandle,expression) )
                                                    ERROR

RECOVER
  delete auto_selection;
  auto_selection = NULL;
  term = YES;
ENDSEQ
  return(term);
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

logical node :: SetContextVariables (char *context_string )
{
  CTX_DBBase             *context;
  logical                 term = NO;
  if ( context = GetContext() )
    term = context->SetContextVariables(context_string);
  if ( nodeinst && (context = nodeinst->GetContext()) )
    if ( context->SetContextVariables(context_string) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  SetCurrentInti - 




\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentInti"

void node :: SetCurrentInti (inti *intiptr )
{

  if ( nodeinst = intiptr )
    fld::SetArea(nodeinst->get_iselarea());
  else
    SetArea(NULL);


}

/******************************************************************************/
/**
\brief  SetDescription - 




\param  field_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

void node :: SetDescription (DBFieldDef *field_def )
{

  dbf::SetDescription(field_def);

}

/******************************************************************************/
/**
\brief  SetDynLength - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDynLength"

logical node :: SetDynLength ( )
{
  logical                 term = NO;
  CopyDescription(NULL);
  if ( fldfmcb )
    fldfmcb->fmcbvar = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  SetExpression - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical node :: SetExpression (char *expression )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

logical node :: SetExpression (BNFData *bnf_data )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  SetGUID - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGUID"

void node :: SetGUID ( )
{

  stssdel();

}

/******************************************************************************/
/**
\brief  SetGenAttribute - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  fldnames - Property name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical node :: SetGenAttribute (char *fldnames, int attrtype, char *attrstr )
{
  node               *nodeptr = this;
  logical             term = NO;
BEGINSEQ
  if ( !nodenode || (fldnames && *fldnames) )        ERROR
    
  while ( nodeptr )
  {
    if ( nodeptr->get_nodetype() == NT_ACGenericAttr )
    {
      term = ((ACGenericAttr *)nodeptr)->SetGenAttribute(attrtype,attrstr);
      LEAVESEQ
    }
    nodeptr = nodeptr->get_nodenode();
  }  

  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical node :: SetGenAttribute (int attrtype, char *attrstr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical node :: SetGenAttribute ( )
{

  return(YES);

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

logical node :: SetInstAction (SimpleAction *simple_action )
{


  return(YES);

}

/******************************************************************************/
/**
\brief  SetInstance - 



\return instptr - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

void *node :: SetInstance (void *instptr )
{

  return ( dbf::SetInstance(instptr) );

}

/******************************************************************************/
/**
\brief  SetInstanceEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceEventHandler"

void node :: SetInstanceEventHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  SetInstanceProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstanceProcessHandler"

void node :: SetInstanceProcessHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  SetIntiArea - 




\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIntiArea"

void node :: SetIntiArea (void *instptr )
{

  if ( !nodeinst )
    Check(YES,NO);
  
  if ( nodeinst )
  {
    nodeinst->ReleaseArea();
    nodeinst->InitArea(instptr);
  }

}

/******************************************************************************/
/**
\brief  SetKey - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  - 



\param  kcbptr - 
\param  keyptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical node :: SetKey (kcb *kcbptr, char *keyptr, void *instptr )
{
  void     *instance = instptr;
  logical   term = NO;
BEGINSEQ
  if ( !keyptr )                                     ERROR
  if ( kcbptr->scbsmcb->smcbsts.stscnof() )          LEAVESEQ
  
  if ( !instance )
  {
    if ( !IsPositioned() && !nodeinst->stscini() )   SDBERR(76)
    instance = nodeinst->get_iselarea();
  }
  
  kcbptr->kcbkpt((char *)instance,keyptr);
  if ( (!instptr || instptr == nodeinst->get_iselarea()) 
       && (nodecur != AUTO || nodeinst->stscini()) )
    Modify(NO);                                 // neu in opa7
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NODEKX - 



\param  keyptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical node :: SetKey (char *keyptr, void *instptr )
{
  kcb      *kcbptr;
  logical   term = NO;

BEGINSEQ
  if ( Check(YES,NO) )                               ERROR			
  if ( !(kcbptr = GetSMCB(NO)->smcbidky) )           SDBERR(71)

  if ( SetKey(kcbptr,keyptr,instptr) )               ERROR
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetKeyArea - 



\return skey - 

\param  skey - 
\param  klen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyArea"

char *node :: SetKeyArea (char *skey, int16 klen )
{

  if ( !key_area )
    AllocKeyArea();

  if ( !klen )
    klen = MAX_KEYLEN;

  memcpy(key_area,skey,klen);

  return(key_area);
}

/******************************************************************************/
/**
\brief  SetMod - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMod"

void node :: SetMod ( )
{
  node     *nodeptr = this;
BEGINSEQ
  if ( nodeinst && nodeinst->stscusr1() )             LEAVESEQ
  
  stssmod();  
    
  while ( (nodeptr = nodeptr->get_nodenode()) && 
          !nodeptr->stscmod() )
    nodeptr->SetMod();
ENDSEQ

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

logical node :: SetOrder (char *strnames, int attrtype, char *attrstr )
{

  return(YES);


}

/******************************************************************************/
/**
\brief  SetPIRef - 




\param  pibptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPIRef"

void node :: SetPIRef (PropertyHandle *pibptr )
{

  if ( this )
    ObjectReference::Connect((ObjectReferenceHandle *)pibptr);


}

/******************************************************************************/
/**
\brief  SetPathExpression - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  expr_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPathExpression"

logical node :: SetPathExpression (char *expr_string )
{
  char                   *key = NULL;
  char                   *wstr= NULL;
  char                    par;
  char                   *end;
  logical                 term = NO;
BEGINSEQ
  if ( !expr_string || !*expr_string )               LEAVESEQ
  if ( fldfmcb )
  {
    SDBEV1(fldfmcb->fmcbname,ID_SIZE)
    if ( nodenode && nodenode->fldfmcb )
      SDBEV2(nodenode->fldfmcb->fmcbtype,ID_SIZE)
  }
  wstr = key = strdup(expr_string);
  
  if ( !(end = gvtsfbp(key,UNDEF)) )                 SDBERR(99)
  par = *key;
  while ( *(++key) == ' ' ) ;
  if ( *key == '{' )
  {
    if ( !(end = gvtsfbp(key,UNDEF)) )               SDBERR(99)
    par = *key;
    key++;
  }
  if ( end == key+1 )                                LEAVESEQ
  *end = 0;
  *(--end) = 0;
  
  if ( SetPathExpression(key,par) )                  ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( wstr )
    free(wstr);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  expr_string - 
\param  expr_char - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPathExpression"

logical node :: SetPathExpression (char *expr_string, char expr_char )
{
  char                   *keyptr;
  int32                   klen;
  char                   *end;
  logical                 term = NO;
BEGINSEQ
  switch ( expr_char )
  {
    case '[': auto_provide = YES;
    case '(': if ( isdigit(*expr_string) )
                auto_position = atol(expr_string);
              else
              {
                if ( !(klen = GetSortKeyLength()) )
                  if ( !(klen = GetKeyLength()) )    SDBERR(344)
                auto_key = new char[klen];
                if ( *expr_string == '\'' || *expr_string == '"' )
                {
                  if ( !(end = gvtsfbp(expr_string,UNDEF)) )SDBERR(344)
                  *(--end) = 0;
                  expr_string++;
                }
                if ( !(keyptr = StringToKey(expr_string,NULL)) )
                                                     ERROR
                memcpy(auto_key,keyptr,klen);
              }
              break;
    case '{': term = SetExpression(expr_string);
              break;
    default :                                        SDBERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPropertyEventHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyEventHandler"

void node :: SetPropertyEventHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  SetPropertyProcessHandler - 




\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPropertyProcessHandler"

void node :: SetPropertyProcessHandler (EventLink *event_link )
{



}

/******************************************************************************/
/**
\brief  SetSortKey - 



\return term - Termination code

\param  keyptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSortKey"

logical node :: SetSortKey (char *keyptr, void *instptr )
{

  return ( SetKey(keyptr,instptr) );



}

/******************************************************************************/
/**
\brief  SetTransientProperty - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransientProperty"

logical node :: SetTransientProperty (node *nodeptr )
{


  return(YES);
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

logical node :: SetType (char *strnames, logical chknode )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - Termination code

\param  nodeptr - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical node :: SetValue (node *nodeptr, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( this == nodeptr )         LEAVESEQ // 16.2.2004 geht nicht beim übernehmen von CollectionHandles
  
  if ( IsCollection() && nodeptr->IsCollection() )
  {
    DeleteSet();
    CopySet(nodeptr,YES);                            LEAVESEQ
  }
  
  if ( !nodeptr->ProvideArea() )  // no source value
  {
    if ( IsUndefined() )                             LEAVESEQ
    if ( Initialize_intern(NULL,NO) )                ERROR
    LEAVESEQ
  }
  else if ( IsUndefined() )
    CopyDescription(nodeptr->fldfmcb);

  if ( !IsSelected() )
    if ( AutoLocate(NO) )                            SDBERR(235)
    
  if ( nodetype != NT_Node )
    if ( !IsCollection() && !nodeptr->IsCollection() )
      if ( GetArea(NO) == nodeptr->GetArea(NO) || !Compare(nodeptr) )
                                                     LEAVESEQ 
  if ( fld::GetArea() == nodeptr->fld::GetArea() )   LEAVESEQ
  
  if ( chknode && CheckUpdate() )               ERROR
    
  *(dbf *)this = *(dbf *)nodeptr; 
  if ( fld::GetArea() == nodeptr->fld::GetArea() )   LEAVESEQ
  
  if ( chknode )
  {
    if ( !Modify(NO) )                               ERROR
    Store();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetVersion - 



\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical node :: SetVersion (uint16 version_nr )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  SetWPT - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWPT"

void node :: SetWPT ( )
{
  node     *nodeptr = this;
    while ( (nodeptr = nodeptr->get_nodenode()) && 
            !nodeptr->stscwpt() )
      nodeptr->stsswpt(YES);



}

/******************************************************************************/
/**
\brief  SetWProtect - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical node :: SetWProtect ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  SetupNode - 



\return term - Termination code

\param  create_ref - 
\param  retain_mod - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNode"

logical node :: SetupNode (logical create_ref, logical retain_mod )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  SetupSubNode - 



\return term - Termination code

\param  create_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSubNode"

logical node :: SetupSubNode (logical create_ref )
{
  node                   *nodeptr;
  logical                 term = NO;
BEGINSEQ
  if ( !IsNewReference(create_ref) )
  {
    GenerateEvent(DBO_Refresh);
    if ( copies )
    {
      copies->GoTop();
      while ( nodeptr = copies->GetNext() )
        if ( nodeptr->SetupSubNode(create_ref) )
          term = YES;
    }
  }
  else
  {
    if ( create_ref && nodeinst && nodeinst->stscini() )  // create_ref sollte nur für Add (und Duplicate) auf YES stehen
    {
      SetupNode(create_ref,create_ref);
      // beim Add müssen nachgeordnete Instanzen ggf. gesichert werden, 16.6.2006
      if ( Save(NO,NO,NO) )                         ERROR
    }    
    else
    {
      ResetNode(YES);
      if ( SetupNode(create_ref,create_ref) )       ERROR
    }
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StartReadTA - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartReadTA"

ACObject *node :: StartReadTA ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  StopReadTA - 




\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopReadTA"

void node :: StopReadTA (logical error_case )
{



}

/******************************************************************************/
/**
\brief  Store - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical node :: Store ( )
{

  return ( YES );

}

/******************************************************************************/
/**
\brief  StoreData - 



\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreData"

logical node :: StoreData (void *instptr )
{
  smcb     *smcbptr;
  logical   term = NO;
BEGINSEQ
  if ( !Get(AUTO) )                                     ERROR
  if ( Check(YES) )                                     ERROR
  if ( !IsWrite() )                                     ERROR

  smcbptr = fldfmcb->fmcbsmcb;
  smcbptr->smcbfmcl->fmclicpy(smcbptr->smcbfmcl,
                              nodeinst->get_iselarea(),(char *)instptr);
  Modify();


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StringToGUID - 



\return _guid - 

\param  _guid - 
\param  guid_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringToGUID"

guid *node :: StringToGUID (guid *_guid, char *guid_string )
{

BEGINSEQ
  if ( !guid_string )                               ERROR
  
  if ( !_guid )
  {
    nstring.Resize(16);
    _guid = (guid *)nstring.GetArea();
  }
  _guid->Initialize(guid_string);

RECOVER
  _guid = NULL;
ENDSEQ
  return(_guid);
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

char *node :: StringToKey (char *key_string, char *key_name_w )
{
  kcb            *kcbptr;
  char           *keyval;
  smcb           *smcbptr;
  char           *keyptr;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR
  if ( !key_string )                                 SDBERR(99)
  
  keyval = GetKeyArea();
  
  if ( fldfmcb && fldfmcb->fmcbityp == 72 )  // __OBJECT
    StringToGUID((guid *)keyval,key_string);
  else
  {
    if ( key_name_w ) 
      smcbptr = GetKeySMCB(key_name_w);
    else
      if ( !(smcbptr = GetSortKeySMCB()) )
        smcbptr = GetKeySMCB();
    
    if ( !smcbptr ) 
    { // !VOID-Extend || !GUID
      if ( !stscusr2() || key_string[1] != '-' )  ERROR
      keyval = key_string;
      LEAVESEQ
    }
  
    kcbptr = GetSMCB()->GetKCB(smcbptr->smcbname);
    smcbptr->ConvertToStruct(key_string,keyval,UNDEF);
  }
RECOVER
  keyval = NULL;
ENDSEQ
  return(keyval);
}

/******************************************************************************/
/**
\brief  StructFieldError - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructFieldError"

logical node :: StructFieldError ( )
{

  UtilityHandle::StructFieldError(GetFieldDef()->fmcbname,
                          nodenode ? nodenode->GetFieldDef()->fmcbsmcb->smcbname : NULL);

  return(NO);
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

logical node :: Switch (int32 indx0 )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  SynchInstance - 



\return term - Termination code

\param  synch_cur - 
\param  synch_loid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SynchInstance"

logical node :: SynchInstance (int32 synch_cur, int32 synch_loid )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || (synch_cur == ERIC && !synch_loid) ) LEAVESEQ
  
  if ( synch_cur != ERIC )
  {
    if ( synch_cur == AUTO )
      Cancel();
    else
      if ( !GetRelative(synch_cur) )                         ERROR
  }
  if ( synch_loid ) 
  {
    if ( synch_loid != GetID(AUTO,NO,YES).get_ebsnum() )
      if ( Locate(synch_loid) )                      ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ToTop - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

logical node :: ToTop ( )
{
  node                   *topnode;
  logical                 term = NO;
BEGINSEQ
//  return(Save() || Cancel());
// jetzt so:
  if ( !IsPositioned() )  // das müssen wir machen, damit beim ToTop kein ini oder mod stehen bleibt 27.1.03
    if ( !nodeinst && nodetype == NT_ACOPView ) // AccessPath
      Check(YES,YES);                 
  
  Save(YES,NO,NO);

// weil, wenn wir das so machen, werden new instances be Modifikation nicht gespeichert
/*
  if ( !IsPositioned() )  // das müssen wir machen, damit beim ToTop kein ini oder mod stehen bleibt 27.1.03
  { 
    if ( nodeinst )
      nodeinst->ResetNodes();
    else if ( nodetype == NT_ACOPView ) // AccessPath
      Check(YES,YES);                 
    ResetInstance();
    LEAVESEQ
  }
   
  Save(YES,NO,NO);
*/

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Union - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  sk_opt - 
\param  distinct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

logical node :: Union (node *nodeptr, char sk_opt, logical distinct )
{
  int32            lindx0 = 0;
  logical          owning = GetFieldDef(NO)->get_owning();
  void            *instptr;
  logical          term = NO;
  while ( instptr = nodeptr->Get(lindx0++) )
  {
    if ( owning )
      switch ( sk_opt )
      {
        case AUTO :
        case YES  : Provide(instptr);
                    break;
        default   : if ( !distinct || Locate(nodeptr->GetID(AUTO,NO),NO) )
                      Add(AUTO,NULL,NULL,instptr);
      }
    else
      switch ( sk_opt )
      {
        case AUTO :
        case YES  : if ( !Get(ExtractSortKey(NULL,instptr)) )
                      AddReference(nodeptr,AUTO);
                    break;
        default   : if ( !distinct || Locate(nodeptr->GetID(AUTO,NO),NO) )
                      AddReference(nodeptr,AUTO);
      }
  }
  
  Switch(AUTO);

  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  pi_liste - 
\param  count - 
\param  sk_opt - 
\param  distinct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Union"

logical node :: Union (PropertyHandle **pi_liste, int32 count, char sk_opt, logical distinct )
{
  char            *keyptr;
  char             keyarea[MAX_KEYLEN];
  int32             lindx0 = 0;
  int32             i;
  node            *nodeptr;
  logical          term = NO;
  DeleteSet();
  
  for ( i = 0; i < count; i++)
  {
    nodeptr = pi_liste[i]->get_nodeptr();
    lindx0  = 0;
    nodeptr->Switch(AUTO);
    switch ( sk_opt )
    {
      case  YES  : while ( keyptr = nodeptr->NextKey(NULL) )
                     if ( !distinct || LocateKey(keyptr) )
                       if ( AddReference(nodeptr,AUTO) )
                         term = YES;
                   break;
      case  AUTO : keyptr = keyarea;
                   while ( nodeptr->Get(lindx0++) && (keyptr = nodeptr->ExtractKey(keyarea,NULL)) )
                     if ( !distinct || LocateKey(keyptr) )
                       if ( AddReference(nodeptr,AUTO) )
                         term = YES;
                   break;
      default    : while ( nodeptr->Get(lindx0++) )
                     if ( !distinct || Locate(nodeptr->GetID(AUTO,NO)) )
                       if ( AddReference(nodeptr,AUTO) )
                         term = YES;
    }
  }

  Switch(AUTO);
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical node :: Unlock ( )
{
 

  return(NO);
 

}

/******************************************************************************/
/**
\brief  UnlockSet - 



\return term - Termination code

\param  extlock - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockSet"

logical node :: UnlockSet (logical extlock, logical chknode )
{


  return(NO);

}

/******************************************************************************/
/**
\brief  UnregisterHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterHandle"

logical node :: UnregisterHandle ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ValidateNode - 



\return new_node - 

\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateNode"

node *node :: ValidateNode (logical crt_opt )
{
  node         *nodeptr = this;
  if ( fldfmcb && fldfmcb->fmcbrlev == R_REFR )
    if ( flddata && (*(node **)flddata)->IsValid() )
      nodeptr = *(node **)flddata;
      
  return(nodeptr);

}

/******************************************************************************/
/**
\brief  __Decrease - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__Decrease"

void node :: __Decrease ( )
{

  node_count--;

//  __all_nodes.Find(this);
//  __all_nodes.RemoveAt();

}

/******************************************************************************/
/**
\brief  __Increase - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__Increase"

void node :: __Increase ( )
{

  ++node_total;
  if ( ++node_count > node_max )
    node_max = node_count;

//  set_result_string ((char *)&node_count,4);
//  __all_nodes.AddTail(this);

}

/******************************************************************************/
/**
\brief  __TraceList - 



\return count - 

\param  max_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__TraceList"

int32 __cdecl node :: __TraceList (int32 max_count )
{
  node   *nodeptr;
  char   *fldname;
  nodeptr = __all_nodes.GetTail();
  while ( nodeptr && max_count-- )
  {
    fldname = nodeptr->fldfmcb->fmcbname;
    nodeptr = __all_nodes.GetPrev();
  }
  return(node_count);
}

/******************************************************************************/
/**
\brief  get_bnode - 



\return bnodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_bnode"

bnode *node :: get_bnode ( )
{

  return(this && nodetype != NT_Node ? (bnode *)this : NULL);

}

/******************************************************************************/
/**
\brief  get_nodenode_ptr - 



\return pnodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_nodenode_ptr"

node **node :: get_nodenode_ptr ( )
{

  return ( &nodenode );

}

/******************************************************************************/
/**
\brief  node - 



-------------------------------------------------------------------------------
\brief  BigInt - 



\param  int64_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (int64 int64_val )
                     : sts (),
dbf (int64_val),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i02 - 



\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (node *nodeptr, DBFieldDef *dbfield_ptr, void *instptr )
                     : sts (),
dbf (),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(AUTO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

BEGINSEQ
  Open();
  Open(nodeptr,dbfield_ptr);
  if ( !(nodeinst = new inti(this,GetFieldDef()->GetDBStruct(),instptr,YES)) )
                                                     SDBERR(95)



RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 



\param  struct_def - Pointer to generel structure definition
\param  prop_names - Property name
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (DBStructDef *struct_def, char *prop_names, void *instptr )
                     : sts (),
dbf (struct_def,prop_names,instptr),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i04 - 



\param  time_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (dbtm time_val )
                     : sts (),
dbf (time_val),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i05 - 



\param  dictptr - Dictionary handle
\param  field_def - 
\param  init_string - 
\param  init_opt - 
\param  const_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (Dictionary *dictptr, DBFieldDef *field_def, char *init_string, logical init_opt, logical const_opt )
                     : sts (),
dbf (dictptr,field_def,init_string,init_opt,const_opt),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(AUTO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i06 - 



\param  logval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (logical logval )
                     : sts (),
dbf (logval),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i07 - 



\param  dictptr - Dictionary handle
\param  prop_names - Property name
\param  typenames - Type name
\param  nsid - 
\param  ref_level - Level, data is referenced
\param  size - Field size
\param  precision - 
\param  dimension - Dimension of property
\param  init_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (Dictionary *dictptr, char *prop_names, char *typenames, int32 nsid, SDB_RLEV ref_level, uint32 size, int32 precision, uint32 dimension, char *init_string )
                     : sts (),
dbf (dictptr,prop_names,typenames,nsid,ref_level,
     size,precision,dimension,init_string),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(AUTO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i08 - 



\param  field_def - 
\param  initinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (DBFieldDef *field_def, void *initinst )
                     : sts (),
dbf (field_def,initinst),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i09 - 



\param  string - 
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (char *string, int32 string_len )
                     : sts (),
dbf (string,string_len),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node ( )
                     : sts(),
dbf(), 
  nodeidnt(0), 
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(AUTO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i10 - 



\param  datetime_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (dttm datetime_val )
                     : sts (),
// dbf (datetime_val),
dbf (),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i11 - 



\param  dictptr - Dictionary handle
\param  typenames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (Dictionary *dictptr, char *typenames )
                     : sts (),
dbf (dictptr,typenames),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(AUTO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i12 - 



\param  strdef - Structure definition
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (DBStructDef *strdef, void *instptr )
                     : sts (),
dbf (strdef,instptr),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i13 - 



\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (char *string )
                     : sts (),
dbf (string),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i14 - 



\param  dbl_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (double dbl_value )
                     : sts (),
dbf (dbl_value),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i15 - 



\param  int_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (int32 int_val )
                     : sts (),
dbf (int_val),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i16 - 



\param  date_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (dbdt date_val )
                     : sts (),
dbf (date_val),
  nodeidnt(0),
  nodenode(NULL),
  nodeinst(NULL),
  nodetype(NT_Node),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(NO),
  key_area(NULL),
  parent(NULL),
  ph(this),
  auto_key(NULL),
  auto_position(AUTO),
  auto_provide(NO),
  auto_selection(NULL),
  node_meta(NULL)
{

  Open();

}

/******************************************************************************/
/**
\brief  i2 - 



\param  noderef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "node"

     node :: node (node &noderef )
                     : sts (),
dbf (noderef),
  nodeidnt(noderef.get_nodeidnt()),
  nodenode(noderef.get_nodenode()),
  nodeinst(NULL),
  nodetype(noderef.get_nodetype()),
  prop_path(NULL),
  origin(NULL),
  copies(NULL),
  nstring(),
  global_instance(noderef.get_global_instance()),
  key_area(NULL),
  parent(noderef.get_parent()),
  ph(this),
  auto_key(NULL),
  auto_position(noderef.get_auto_position()),
  auto_provide(noderef.get_auto_provide()),
  auto_selection(NULL),
  node_meta(NULL)

{
  int32          klen;
BEGINSEQ
  Open();
  noderef.Check(YES,NO);
  
  if ( noderef.stscusr2() )
    stssusr2();
    
  if ( noderef.get_prop_path() )
    prop_path = strdup(noderef.get_prop_path());

  if ( !(origin = noderef.get_origin()) )
    origin = &noderef;
  if ( !origin )                                     SDBERR(99)
    
  origin->AddCopy(this);

  if ( noderef.get_auto_key() )
  {
    if ( !(klen = noderef.GetSortKeyLength()) )
      klen = noderef.GetKeyLength();
    if ( klen )
    {
      auto_key = new char[klen];
      memcpy(auto_key,noderef.get_auto_key(),klen);
    }
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  set_auto_key - 



\return term - Termination code

\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_auto_key"

logical node :: set_auto_key (char *keyptr )
{
  int32       klen;
  logical     term = NO;
BEGINSEQ
  delete auto_key;
  auto_key = NULL;
  
  if ( !keyptr )                                     LEAVESEQ
    
  if ( !(klen = GetSortKeyLength()) )
    if ( !(klen = GetKeyLength()) )                  SDBERR(344)
      
  auto_key = new char[klen];
  memcpy(auto_key,keyptr,klen);
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  set_auto_position - 




\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_auto_position"

void node :: set_auto_position (int32 lindx0 )
{

  auto_position = lindx0;

}

/******************************************************************************/
/**
\brief  set_auto_provide - 




\param  logval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_auto_provide"

void node :: set_auto_provide (logical logval )
{

  auto_provide = logval;

}

/******************************************************************************/
/**
\brief  set_nodeinst - 




\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_nodeinst"

void node :: set_nodeinst (inti *intiptr )
{

  nodeinst = intiptr;

}

/******************************************************************************/
/**
\brief  set_nodenode - 




\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_nodenode"

void node :: set_nodenode (node *nodeptr )
{

  nodenode = nodeptr;

}

/******************************************************************************/
/**
\brief  set_parent - 




\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_parent"

void node :: set_parent (node *nodeptr )
{

  parent = nodeptr;

}

/******************************************************************************/
/**
\brief  set_prop_path - 




\param  path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_prop_path"

void node :: set_prop_path (char *path )
{

  if ( prop_path )
    free(prop_path);
  prop_path = NULL;

  if ( path )
    prop_path = strdup(path);

}

/******************************************************************************/
/**
\brief  set_result_string - 



\return string - 

\param  char_buffer - 
\param  longlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_result_string"

char *node :: set_result_string (char *char_buffer, int32 longlen )
{

  return( nstring.SetString(char_buffer,longlen) );

}

/******************************************************************************/
/**
\brief  ~node - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~node"

     node :: ~node ( )
{
  CTX_Property        *context;
  node::Close();   // ist eigentlich nur zur Sicherheit
  
  if ( prop_path )
    free(prop_path);
  prop_path = NULL;
  
  delete key_area;
  key_area = NULL;
  
  delete auto_key;
  auto_key = NULL;
  
  if ( highnod && stscold() )   // nichtletzter PathNode
  {
    if ( highnod->get_nodeidnt() == NODE_ID &&
         ( !(context = highnod->GetContext()) || 
           (context->ProcessState() != PRC_Busy && context->ProcessState() != PRC_Closed) ) )
      delete highnod;
    nodenode = NULL;
  }

  __Decrease();

}


