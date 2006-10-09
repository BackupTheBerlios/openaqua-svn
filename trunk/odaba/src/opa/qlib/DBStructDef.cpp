/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBStructDef

\brief    Definition for the internal presentation of data structures and enumerations
          Definitions  for  data  structures  are  usually  read  from an ODABA2
          dictionary.  However they can be provided  and filled directly in main
          storage.  Still  in  this  case  the definition should be provided via
          Dictionary functions to make them available for the ODABA2 kernel.
          From  an ODABA2 dictionary  structures are provided  only, if they are
          marked as checked and as ready for a non test environment.

\date     $Date: 2006/08/30 18:52:35,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBStructDef"

#include  <popa7.h>
#include  <coctp.h>
#ifndef   P_ODC_View_HPP
#define   P_ODC_View_HPP
#include  <sPI.hpp>
class       ODC_View;
PI_dcl     (ODC_View)
#endif
#ifndef   DLL_DBViewPath_HPP
#define   DLL_DBViewPath_HPP
#include  <sDBViewPath.hpp>
#include  <sDLL.h>
#endif
#ifndef   DPA_OPDecl_HPP
#define   DPA_OPDecl_HPP
#include  <sOPDecl.hpp>
#include  <sDPA.h>
#endif
#ifndef   DPA_OPExpressionDecl_HPP
#define   DPA_OPExpressionDecl_HPP
#include  <sOPExpressionDecl.hpp>
#include  <sDPA.h>
#endif
#ifndef   DLL_OPFunctionDecl_HPP
#define   DLL_OPFunctionDecl_HPP
#include  <sOPFunctionDecl.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_kcb_HPP
#define   DLL_kcb_HPP
#include  <skcb.hpp>
#include  <sDLL.h>
#endif
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sACProperty.hpp>
#include  <sACShareBase.hpp>
#include  <sACTopNode.hpp>
#include  <sACTransientReference.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBHandle.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDBViewStructDef.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDictionary.hpp>
#include  <sENUM_Value.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sFieldList.hpp>
#include  <sLACObject.hpp>
#include  <sLDictionary.hpp>
#include  <sODC_View.hpp>
#include  <sOPDecl.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOPFunctionDecl.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sSDB_Attribute.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Index.hpp>
#include  <sSDB_Key.hpp>
#include  <sSDB_KeyComponent.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#include  <sSDB_Structure.hpp>
#include  <sacc.hpp>
#include  <sbinti.hpp>
#include  <scvb.hpp>
#include  <sexd.hpp>
#include  <sfmcb.hpp>
#include  <sinti.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <ssrt.hpp>
#include  <sDBStructDef.hpp>


/******************************************************************************/
/**
\brief  AddExpression - 



\return term - Termination code

\param  expr_decl - 
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExpression"

logical DBStructDef :: AddExpression (OPDecl *expr_decl, ParmList *parmlist )
{
  logical         term = NO;
BEGINSEQ
  if ( GetExprDecl(expr_decl->get_opname(),NULL,NULL,parmlist,NO,NO) )
                                                     SDBERR(64)
  expression_list->Add(expr_decl);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddUndefinedMember - 



\return term - Termination code

\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddUndefinedMember"

logical DBStructDef :: AddUndefinedMember (char *prop_names )
{
  char                    string[ID_SIZE+1];
  logical                 term = NO;
BEGINSEQ
  if ( !prop_names )                                 ERROR
  if ( !undef_members )
    undef_members = new srt(20,ID_SIZE+1,ID_SIZE,1,'V',YES);
  
  undef_members->srtkad(gvtxbts(string,prop_names,ID_SIZE));


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Check - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  strsid - Internal structure number
\param  basecount - Number of base structures
\param  attrcount - Number of attributes
\param  refrcount - Number of references
\param  rshpcount - Number of relationships
\param  idkeynames - Name of the identifying key
\param  w_vf_opt - Consider virtual function pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical DBStructDef :: Check (int16 strsid, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames, logical w_vf_opt )
{
  int16    count = basecount + attrcount + refrcount + rshpcount;
  logical  term  = NO;
BEGINSEQ
  if ( Check(strsid) )                               ERROR
  
  if ( base_info.get_count() != basecount ||
       attr_info.get_count() != attrcount ||
       refr_info.get_count() != refrcount ||
       rshp_info.get_count() != rshpcount      )     SDBERR(302)
       
  if ( vf_opt != w_vf_opt )                          SDBERR(303)
       
  if ( idkeynames && *idkeynames )
  {
    if ( smcbidky )
      gvtxstb(smcbidky->scbsmcb->smcbname,idkeynames,ID_SIZE);
    else
      if ( !(smcbidky = new kcb(idkeynames,this)) )  SDBERR(95)
  }
      

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  strsid - Internal structure number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical DBStructDef :: Check (int16 strsid )
{
  logical    term = NO;
BEGINSEQ
  if ( !smcbityp )
    smcbityp = strsid;          // das sollte nur fuer CodeSets laufen
  
  if ( smcbityp != strsid )                          
  {
    SDBEV1(smcbname,ID_SIZE)
    SDBERR(301)
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  dictptr - Dictionary handle
\param  baselist - 
\param  attrlist - 
\param  refrlist - 
\param  rshplist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical DBStructDef :: Check (Dictionary *dictptr, SDB_BaseStruct **baselist, SDB_Attribute **attrlist, SDB_Reference **refrlist, SDB_Relationship **rshplist )
{
  int16        count = base_info.get_count() + attr_info.get_count() + refr_info.get_count() + rshp_info.get_count();
  int16        indx0;
  int16        i      = 1;
  int32         intpos = 0;
  int32         netpos = 0;
  int32         extpos = 0;
  logical      term   = NO;
  for (indx0 = 0; indx0 < base_info.get_count(); indx0++)
    if ( GetEntry(i++)->SetupBaseStruct(baselist[indx0],dictptr,intpos,extpos,netpos,defined_align,plattform_align) )
      term = YES;

  for (indx0 = 0; indx0 < attr_info.get_count(); indx0++)
    if ( GetEntry(i++)->SetupAttribute(attrlist[indx0],dictptr,intpos,extpos,netpos,defined_align,plattform_align) )
      term = YES;

  for (indx0 = 0; indx0 < refr_info.get_count(); indx0++)
    if ( GetEntry(i++)->SetupReference(refrlist[indx0],dictptr,intpos,extpos,netpos,defined_align,plattform_align) )
      term = YES;

  for (indx0 = 0; indx0 < rshp_info.get_count(); indx0++)
    if ( GetEntry(i++)->SetupRelation(rshplist[indx0],dictptr,intpos,extpos,netpos,smcbsts.stscold(),defined_align,plattform_align) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckKeyDefs - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckKeyDefs"

logical DBStructDef :: CheckKeyDefs ( )
{
  kcb       *kcbptr;
  logical    term = NO;
  smcbskey->GoTop();
  while ( kcbptr = smcbskey->GetNext() )
    if ( !kcbptr->scbsmcb->smcbfmcl ||
         !kcbptr->scbsmcb->smcbfmcl->GetCount() )  
    {
      UtilityHandle::StructFieldError(kcbptr->scbsmcb->smcbname,smcbname);
      SDBSET(75)
      SDBRESET
    }

  return(term);
}

/******************************************************************************/
/**
\brief  CheckKeyMod - 



\return cond - 

\param  instarea - 
\param  oldinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckKeyMod"

logical DBStructDef :: CheckKeyMod (void *instarea, void *oldinst )
{
  kcb       *kcbptr;
  logical    cond = YES;
BEGINSEQ
  if ( !oldinst )                                    LEAVESEQ
    
  smcbskey->GoTop();
  while ( kcbptr = smcbskey->GetNext() )
  {
    if ( kcbptr->scbsmcb->smcbsts.stscsav() )        LEAVESEQ
    
    if ( !kcbptr->scbsmcb->smcbsts.stscnof() )
      if ( kcbptr->CompareKeys((char *)instarea,(char *)oldinst,CMP_II) )
                                                     LEAVESEQ
  }

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ConvInstVersion - 



\return term - Termination code

\param  lobhandle - 
\param  instarea - 
\param  schemaversion - Scheme version
\param  p_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvInstVersion"

logical DBStructDef :: ConvInstVersion (LACObject *lobhandle, void *instarea, uint8 schemaversion, logical *p_update )
{
  logical                 term = NO;
BEGINSEQ
  if ( schemaversion < prev_struct_def->get_schema_ver() )
  {
    if ( prev_struct_def->ConvInstVersion(lobhandle,instarea,schemaversion,p_update) )
                                                     ERROR
  }
  else
    memcpy(prev_struct_def->get_ext_area(),instarea,prev_struct_def->get_ext_length());
  
  if ( CopyExtInst(lobhandle,prev_struct_def,p_update) ) ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDirect - 



\return term - Termination code

\param  targinst - 
\param  srcedef - 
\param  srceinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDirect"

logical DBStructDef :: CopyDirect (void *targinst, DBStructDef *srcedef, void *srceinst )
{
  DBFieldDef     *targflddef;
  fmcb           *srcefmcb;
  char            fldnames[ID_SIZE+1];
  int16           i;
  int16           last;
  int32            offset;
  logical         term = NO;
BEGINSEQ
  if ( !smcbfmcl || !srcedef->smcbfmcl )             ERROR
  smcbfmcl->stsrerr();

  for (i=1; i<=base_info.get_count(); i++)
    if ( (targflddef = GetEntry(i)) &&
          targflddef->get_privilege() != PI_Share )
      if ( targflddef->GetDBStruct()->CopyDirect(((char *)targinst)+targflddef->fmcbposn,srcedef,srceinst) )
                                                     ERROR
  
  for (last = i; i<last+attr_info.get_count(); i++)
  {
    targflddef = GetEntry(i);
    offset = 0;
    if ( srcefmcb = srcedef->SearchField(gvtxbts(fldnames,targflddef->fmcbname,ID_SIZE),&offset) )
      if ( targflddef->fmcbicvt(srcefmcb,((char *)targinst)+targflddef->fmcbposn,
                                       ((char *)srceinst)+srcefmcb->fmcbposn+offset,AUTO,REPL_all) )
        term = YES;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtInst - 



\return term - Termination code

\param  lobhandle - 
\param  srce_struct - 
\param  p_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtInst"

logical DBStructDef :: CopyExtInst (LACObject *lobhandle, DBStructDef *srce_struct, logical *p_update )
{
  DBFieldDef          *srcefield;
  DBFieldDef          *targfield;
  DBStructDef         *targ_struct;
  register int         indx = 0;
  logical              pif = lobhandle->IsPIF();
  logical              term = NO;

BEGINSEQ
  if ( this == srce_struct )                         LEAVESEQ
  if ( !smcbfmcl || !srce_struct->smcbfmcl )         ERROR
  smcbfmcl->stsrerr();

  InitExtInst(ext_area);

  while ( targfield = GetEntry(++indx) )
    if ( srcefield = srce_struct->GetEntry(targfield->fmcbname) )
    {
      if ( targfield->CopyExtInst(lobhandle,ext_area+targfield->get_offset_ext(),srcefield,
                                  srce_struct->get_ext_area()+srcefield->get_offset_ext(),
                                  p_update,pif) )
        term = YES;
    }
    else if ( targfield->fmcbbstr && targfield->get_privilege() != PI_Share )  // new base structure
    {
      targ_struct = targfield->GetDBStruct();
      memcpy(targ_struct->get_ext_area(),ext_area+targfield->get_offset_ext(),targ_struct->get_ext_length());
      targ_struct->CopyExtInst(lobhandle,srce_struct,p_update);
      memcpy(ext_area+targfield->get_offset_ext(),targ_struct->get_ext_area(),targ_struct->get_ext_length());
    }
    else
      if ( targfield->fmcbrlev && targfield->get_update() && lobhandle->get_access_mode() > PI_Read )
      {
        *(EB_Number *)(ext_area+targfield->get_offset_ext()) = 
                      lobhandle->CreateEntry(targfield->get_mb_number(),0,0);
        *p_update = YES;
      }

RECOVER
  term = YES;
ENDSEQ
  if ( term && smcbfmcl && SOSERROR )
    smcbfmcl->stsserr();
  return(term);

}

/******************************************************************************/
/**
\brief  CreateAttrNodes - 



\return term - Termination code

\param  nodeptr - 
\param  bintiptr - 
\param  high_context - 
\param  instptr - 
\param  extoff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAttrNodes"

logical DBStructDef :: CreateAttrNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff )
{
  DBStructDef    *dbstruct;
  DBFieldDef     *dbfield;
  DBFieldDef     *field_def;
  node           *attrnode;
  node           *genattrnode;
  int16           index = base_info.get_count();
  int16           count = index + attr_info.get_count();
  logical         term = NO;
BEGINSEQ
  while ( index < count )
  {
    dbfield  = GetEntry(++index);
    dbstruct = dbfield->GetDBStruct();
    
    if ( dbfield->fmcbrlev == R_GENERIC )
    {
      if ( !(genattrnode = nodeptr->CreateSubNode(nodeptr,NT_ACGenericAttr,NULL,dbfield,high_context,
                                                  ((char *)instptr)+dbfield->fmcbposn,extoff,
                                                  (((char *)instptr)+dbfield->fmcbposn)-bintiptr->get_iselarea(),
                                                  nodeptr->GetMode())) )
                                                     ERROR
      bintiptr->get_node_genattr().AddTail(genattrnode);
    }
    else if ( (!dbfield->fmcbbase() && dbstruct && dbstruct->smcbstyp != ST_CODE) ||
               dbfield->get_resource()->ContextRequired()                         ||
               ( (field_def = ((CTX_Property *)((CTX_DBBase *)high_context)->HighDBContext(CTXT_Property))->GetDefinition()) &&
                field_def->fmcbrlev == R_GENERIC ) )
    {
      if ( !(attrnode = nodeptr->CreateSubNode(nodeptr,NT_ACAttribute,NULL,dbfield,high_context,
                                               ((char *)instptr)+dbfield->fmcbposn,UNDEF,UNDEF,nodeptr->GetMode())) )
                                                     ERROR
      bintiptr->get_node_attr().AddTail(attrnode);
    }
    
    if ( dbstruct && dbfield->fmcbrlev != R_GENERIC )
      switch ( dbstruct->smcbstyp )
      {
        case ST_USER :
        case ST_SYS  :
        case ST_KEY  : if ( dbstruct->CreateSubNodes(nodeptr,bintiptr,
                            attrnode->get_nodeinst()->GetContext(), 
                            ((char *)instptr)+dbfield->fmcbposn,
                            dbfield->get_offset_ext()+extoff) )
                                                       ERROR
                       break;
        default      : ;
      }
    
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateBaseNodes - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  nodeptr - 
\param  bintiptr - 
\param  high_context - 
\param  instptr - 
\param  extoff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseNodes"

logical DBStructDef :: CreateBaseNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff )
{
  LACObject      *lobhandle = nodeptr->GetObjectHandle()->GetLocalACObject();
  DBFieldDef     *dbfield;
  node           *basenode = NULL;
  node           *attrnode;
  ACExtend       *sysnode  = NULL;
  int16           count    = base_info.get_count();
  int16           index    = 0;
  PIACC           accopt;
  logical         term     = NO;
BEGINSEQ
//  if ( !lobhandle )                                  SDBERR(99)
    
  while ( index < count )
  {
    dbfield = GetEntry(++index);
    if ( dbfield->get_privilege() == PI_Share )
    {
      if ( lobhandle )
      {
        accopt = nodeptr->GetMode();
        if ( !(sysnode = lobhandle->ProvideACExtend(dbfield->GetExtendName(),
                                      accopt,accopt > PI_Read)) )
                                                      ERROR
      }
      if ( !(basenode = nodeptr->CreateSubNode(nodeptr,NT_ACShareBase,sysnode,dbfield,high_context,
                                               ((char *)instptr)+dbfield->fmcbposn,extoff,UNDEF,nodeptr->GetMode(NO))) )
                                                     ERROR
      bintiptr->get_node_base().AddTail(basenode);    
    }
    else
    {
      if ( !(attrnode = nodeptr->CreateSubNode(nodeptr,NT_ACBaseStruct,NULL,dbfield,high_context,
                                               ((char *)instptr)+dbfield->fmcbposn,UNDEF,UNDEF,nodeptr->GetMode(NO))) )
                                                     ERROR
      bintiptr->get_node_attr().AddTail(attrnode);
      
      if ( dbfield->GetDBStruct()->CreateSubNodes(nodeptr,bintiptr,
//    if ( dbfield->GetDBStruct()->CreateSubNodes(nodeptr,attrnode->get_nodeinst(),
                                attrnode->get_nodeinst()->GetContext(),
                                ((char *)instptr)+dbfield->fmcbposn,
                                dbfield->get_offset_ext()+extoff) )
                                                      ERROR
    }
  }
RECOVER
  delete basenode;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  bintiptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseNodes"

logical DBStructDef :: CreateBaseNodes (binti *bintiptr, void *instptr )
{
  DBFieldDef     *dbfield;
  node           *basenode = NULL;
  int16           count    = base_info.get_count();
  int16           index    = 0;
  logical         term     = NO;
BEGINSEQ
//  if ( !lobhandle )                                SDBERR(99)
    
  while ( index < count )
  {
    dbfield = GetEntry(++index);
    if ( dbfield->get_privilege() == PI_Share )
    {
      if ( !(basenode = new ACShareBase(dbfield,((char *)instptr)+dbfield->fmcbposn)) )
                                                     SDBERR(95)
      bintiptr->get_node_base().AddTail(basenode);    
    }
    else
      if ( dbfield->GetDBStruct()->CreateBaseNodes(bintiptr,((char *)instptr)+dbfield->fmcbposn) )
                                                      ERROR
  }
RECOVER
  delete basenode;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExprDecl - 



\return expr_decl - 

\param  dictptr - Dictionary handle
\param  expr_pi - 
\param  retval - 
\param  obhandle - Database Object handle
\param  co - 
\param  parmlist - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExprDecl"

OPDecl *DBStructDef :: CreateExprDecl (Dictionary *dictptr, PropertyHandle *expr_pi, PropertyHandle *retval, ACObject *obhandle, PropertyHandle *co, ParmList *parmlist, OperEnvironment *operenv_w )
{
  PropertyHandle   *impl_pi       = expr_pi->GPH("implementations");
  OPExpressionDecl *new_expr_decl;
  OPDecl           *ret_expr_decl = NULL;
  int32             indx0         = 0;

BEGINSEQ
//  if ( GetExprDecl(fctnames,NULL,NULL,NULL,NO) )     ERROR
  
  if ( !expr_pi->Exist() )                           ERROR
  
  impl_pi->Cancel();
  while ( impl_pi->Get(indx0++) )
  {
    SDBRESET
    new_expr_decl = new OPExpressionDecl(expr_pi->GetString("sys_ident"));
    expression_list->Add(new_expr_decl);
                                                     
    if ( new_expr_decl->Open(dictptr,obhandle,co,impl_pi,operenv_w) )
    {
      expression_list->RemoveLast(1);
      delete new_expr_decl;
    }
    else
      if ( !ret_expr_decl && !new_expr_decl->Check(retval,co,parmlist,NO) )
        ret_expr_decl = new_expr_decl;
  }
   
  if ( ret_expr_decl )                               LEAVESEQ
  ret_expr_decl = GetExprDecl(expr_pi->ExtractKey(),retval,co,parmlist,YES);

RECOVER

ENDSEQ
  return(ret_expr_decl);
}

/******************************************************************************/
/**
\brief  CreateFctDecl - 



\return fctdecl - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dictptr - Dictionary handle
\param  fct_pi - 
\param  obhandle - Database Object handle
\param  co - 
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFctDecl"

OPFunctionDecl *DBStructDef :: CreateFctDecl (Dictionary *dictptr, PropertyHandle *fct_pi, ACObject *obhandle, PropertyHandle *co, ParmList *parmlist )
{
  OPFunctionDecl *ret_fct_decl = NULL;
  OPFunctionDecl *fct_decl     = NULL; 
  PropertyHandle *impl_pi      = fct_pi->GPH("implementations");
  char            fctname[ID_SIZE];
  int32           indx0 = 0;
  int32           indx  = 0;

BEGINSEQ
  if ( !fct_pi->Exist() )                            ERROR
    
  impl_pi->ToTop();
  while ( impl_pi->Get(indx0++) )
  {
    SDBRESET
    fct_decl = new OPFunctionDecl(dictptr,smcbname,NULL,co,impl_pi,YES);
    
    if ( fct_decl->FunctLink::Check(NULL,NULL,NULL,NO) )
      delete fct_decl;
    else
      function_list->AddTail(fct_decl);
  }
   
  ret_fct_decl = GetFctDecl(fct_pi->ExtractKey(),NULL,co,parmlist,YES);

RECOVER

ENDSEQ
  return(ret_fct_decl);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFctDecl"

OPFunctionDecl *DBStructDef :: CreateFctDecl (char *opname )
{
  OPFunctionDecl *ret_fct_decl = NULL;
  OPFunctionDecl *fct_decl     = NULL; 
  int32           indx         = 0;
BEGINSEQ
  fct_decl = new OPFunctionDecl(NULL,smcbname,NULL,NULL,opname,YES);
    
  if ( !fct_decl->FunctLink::Check(NULL,NULL,NULL,NO) && !SDBERROR && !OQLERROR )
    function_list->AddTail(fct_decl);
  else
    delete fct_decl;
   
  ret_fct_decl = GetFctDecl(opname,NULL,NULL,NULL,YES);
RECOVER

ENDSEQ
  return(ret_fct_decl);
}

/******************************************************************************/
/**
\brief  CreateKeyDefs - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i03 - 



\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyDefs"

logical DBStructDef :: CreateKeyDefs (PropertyHandle &ph )
{
  kcb                    *kcbptr;
  int32                   indx0 = 0;
  int16                   last_key_number = 0;
  int32                   i;
  logical                 term = NO;
BEGINSEQ
  indx0 = 0;
  PH(&ph,smcepsmc)
  PH(&smcepsmc,components)
  while ( smcepsmc(indx0++) )
  {  
    if ( !(kcbptr = ProvideKCB(smcepsmc,last_key_number)) )
                                                     ERROR
    if ( last_key_number < kcbptr->get_key_num() )
      last_key_number = kcbptr->get_key_num();
    
    if ( kcbptr->CreateFieldList(MAX((int16)components.GetCount(),1)) )
                                                     SDBERR(95)
    if ( !memcmp(smcepsmc.GetArea("sys_ident"),"__IDENTITY ",11) )
    {
      fmcb keyfmcb("__IDENTITY","INT",0,R_DIRECT,20,0,1,0,8,T_INT,NO,NO,NO,NO);
      kcbptr->scbsmcb->smcbfmcl->AddEntry(1,&keyfmcb);
    }
    else
    {      
      i = 0;
      while ( components(i++) )
        kcbptr->kcbfad(components.GetString("member_path"),(int16)i,
                       components.IsTrue("ignore_case"),components.IsTrue("descending")); 
    }
  }
  
  if ( CheckKeyDefs() )                              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbklistptr - 
\param  keycount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyDefs"

logical DBStructDef :: CreateKeyDefs (SDB_Key *dbklistptr, int16 keycount )
{
  kcb       *kcbptr;
  fmcb      *fmcbptr;
  char     **dbclist;
  char       name[ID_SIZE+1];
  int16      compcount = 0;
  int16      last_key_number = 0;
  int16      i;
  logical    term = NO;
BEGINSEQ
  name[ID_SIZE] = 0;
  while ( keycount-- )
  {  
    if ( !(kcbptr = ProvideKCB(dbklistptr,last_key_number)) )
                                                     ERROR
    if ( last_key_number < kcbptr->get_key_num() )
      last_key_number = kcbptr->get_key_num();
    
    dbclist  = (char **)dbklistptr->get_components().get_nodeptr();
    
    compcount = 0;
    while ( *dbclist[compcount] )
      compcount++; 
    
    if ( kcbptr->scbsmcb->smcbfmcl )
    {
      for ( i = 0; i < compcount; i++ )
        if ( !(fmcbptr = kcbptr->scbsmcb->smcbfmcl->GetEntry(i+1)) ||
             memcmp(fmcbptr->fmcbname,gvtxstb(name,dbclist[i],ID_SIZE),ID_SIZE) ) 
        {
          int32    offset = 0;
          fmcb   *field = SearchField(dbclist[i],&offset);
          if ( !field || memcmp(fmcbptr->fmcbname,field->fmcbname,ID_SIZE) )
          {
            UtilityHandle::StructFieldError(kcbptr->scbsmcb->smcbname,smcbname);
            SDBSET(400)
            SDBRESET                                     ERROR
          }
        }
    }
    else
    {
      if ( kcbptr->CreateFieldList(MAX(compcount,1)) ) 
                                                     SDBERR(95)
      
      if ( !memcmp(kcbptr->scbsmcb->smcbname,"__IDENTITY ",11) )
      {
        fmcb keyfmcb("__IDENTITY","INT",0,R_DIRECT,20,0,1,0,8,T_INT,NO,NO,NO,NO);
        kcbptr->scbsmcb->smcbfmcl->AddEntry(1,&keyfmcb);
      }
      else
      {
        for ( i = 0; i < compcount; i++ )
          kcbptr->kcbfad(gvtxstb(name,dbclist[i],ID_SIZE),i); 
      }
    }  
    dbklistptr++;
  }
  
  if ( CheckKeyDefs() )                              ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyDefs"

logical DBStructDef :: CreateKeyDefs (kcb *kcbptr )
{
  DBFieldDef *dbflddef;
  DBIndex    *dbindex;
  kcb        *fldkcb;
  fmcb       *keyfmcb;
  char        keyfield[65];
  int16       indx = 0;
  int16       i;
  logical     term = NO;
BEGINSEQ
  if ( kcbptr->CreateFieldList(smcbfmcl->GetCount(),YES) )
                                                     ERROR
  while ( dbflddef = GetEntry(++indx) )
    if ( (dbindex = dbflddef->get_index_list()->GetHead()) )  
    {
      if ( !(fldkcb = dbindex->get_key_def()) )
        if ( dbindex->get_unique() && dbflddef->fmcbsmcb )
          fldkcb = dbflddef->fmcbsmcb->smcbidky;
      if ( fldkcb )
      {
        if ( fldkcb->scbsmcb->smcbsts.stscnof() )          // identity
        {
          kcbptr->scbsmcb->smcbsts.stsslck();
          fmcb keyfmcb("__IDENTITY","INT",0,R_DIRECT,20,0,1,0,8,T_INT,NO,NO,NO,NO);
          keyfmcb.fmcbvirt = YES;
          kcbptr->scbsmcb->smcbfmcl->AddEntry(1,&keyfmcb);
        }
        else
        {
          i      = 0;
          while ( keyfmcb = fldkcb->scbsmcb->smcbfmcl->GetEntry(++i) )
          {
            strcat(gvtxbts(keyfield,dbflddef->fmcbname,ID_SIZE),".");
            if ( fldkcb->get_kcbgfmcb() )
            {
              gvtxbcs(keyfield,fldkcb->get_kcbgfmcb()->fmcbname,ID_SIZE,sizeof(keyfield));
              strcat(keyfield,".");
            }
            gvtxbcs(keyfield,keyfmcb->fmcbname,ID_SIZE,sizeof(keyfield));
            kcbptr->kcbfad(keyfield,i,keyfmcb->fmcbic,keyfmcb->fmcbdesc); 
          }
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
\brief  CreateNodes - 



\return term - Termination code

\param  nodeptr - 
\param  sintiptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNodes"

logical DBStructDef :: CreateNodes (node *nodeptr, inti *sintiptr, void *instptr )
{
  DBStructDef    *dbstruct;
  DBFieldDef     *dbfield;
  DBFieldDef     *field_def;
  node           *attrnode;
  int32            index = 0;
  logical         term  = NO;
BEGINSEQ
/*
  while ( dbfield  = GetEntry(++index) )
  {
    dbstruct = dbfield->GetDBStruct();
    if ( dbfield->fmcbrlev == R_DIRECT || dbfield->fmcbrlev == R_INTERN || dbfield->fmcbrlev == R_GENERIC )
    {
      if ( !(attrnode = nodeptr->CreateSubNode(nodeptr,NT_Node,NULL,dbfield,NULL,
                                               ((char *)instptr)+dbfield->fmcbposn,UNDEF,UNDEF,PI_Read)) )
                                                   ERROR
      sintiptr->get_node_attr().AddTail(attrnode);
    
      if ( dbstruct )
        switch ( dbstruct->smcbstyp )
        {
          case ST_USER :
          case ST_SYS  :
          case ST_KEY  : if ( dbstruct->CreateNodes(nodeptr,sintiptr,
                              ((char *)instptr)+dbfield->fmcbposn) ) ERROR
                         break;
          default      : ;
        }
    }    
  }
*/

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRefrNodes - 



\return term - Termination code

\param  nodeptr - 
\param  bintiptr - 
\param  high_context - 
\param  instptr - 
\param  extoff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRefrNodes"

logical DBStructDef :: CreateRefrNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff )
{
  DBFieldDef     *dbfield;
  node           *refrnode = NULL;
  int16           index = base_info.get_count() + 
                          attr_info.get_count();
  int16           count = index + refr_info.get_count();
  logical         term = NO;
BEGINSEQ
  while ( index < count )
  {
    dbfield = GetEntry(++index);
    if ( !dbfield->get_transient() )
    {
      if ( !(refrnode = nodeptr->CreateSubNode(nodeptr,NT_ACReference,NULL,dbfield,high_context,
                                               UNDEF,extoff,UNDEF,nodeptr->GetMode())) )
                                                     ERROR
      bintiptr->get_node_refr().AddTail(refrnode);
      if ( dbfield->get_cluster_opt() && !nodeptr->GetFieldDef()->get_cluster_opt() )
        bintiptr->set_cluster_crt();
      bintiptr->SetPI(refrnode,instptr);
    }
    else
    {
      if ( !(refrnode = nodeptr->CreateSubNode(nodeptr,NT_ACTransientReference,NULL,dbfield,high_context,
                                               UNDEF,extoff,UNDEF,nodeptr->GetMode())) )
                                                     ERROR
      bintiptr->get_node_tref().AddTail(refrnode);
      if ( dbfield->get_cluster_opt() && !nodeptr->GetFieldDef()->get_cluster_opt() )
        bintiptr->set_cluster_crt();
      bintiptr->SetPI(refrnode,instptr);
    }
  }
RECOVER
  delete   refrnode;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRshpNodes - 



\return term - Termination code

\param  nodeptr - 
\param  bintiptr - 
\param  high_context - 
\param  instptr - 
\param  extoff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRshpNodes"

logical DBStructDef :: CreateRshpNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff )
{
  DBFieldDef     *dbfield;
  node           *rshpnode = NULL;
  int16           index = base_info.get_count() + 
                          attr_info.get_count() + 
                          refr_info.get_count();
  int16           count = index + rshp_info.get_count(); 
  logical         term  = NO;
BEGINSEQ
  while ( index < count )
  {
    dbfield = GetEntry(++index);
      if ( !(rshpnode = nodeptr->CreateSubNode(nodeptr,NT_ACRelationship,NULL,dbfield,high_context,
                                               UNDEF,extoff,UNDEF,nodeptr->GetMode())) )
                                                     ERROR
    bintiptr->get_node_rshp().AddTail(rshpnode);
    bintiptr->SetPI(rshpnode,instptr);
  }
RECOVER
  delete rshpnode;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSubNodes - 



\return term - Termination code

\param  nodeptr - 
\param  bintiptr - 
\param  high_context - 
\param  instptr - 
\param  extoff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubNodes"

logical DBStructDef :: CreateSubNodes (node *nodeptr, binti *bintiptr, CTX_Base *high_context, void *instptr, int32 extoff )
{
  logical  term = NO;
BEGINSEQ
  if ( CreateBaseNodes(nodeptr,bintiptr,high_context,instptr,extoff) ) ERROR
  if ( CreateAttrNodes(nodeptr,bintiptr,high_context,instptr,extoff) ) ERROR
  if ( CreateRefrNodes(nodeptr,bintiptr,high_context,instptr,extoff) ) ERROR    
  if ( CreateRshpNodes(nodeptr,bintiptr,high_context,instptr,extoff) ) ERROR    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBStructDef - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
\param  strsid - Internal structure number
\param  intlen - Internal length
\param  extlen - External length
\param  metatype - Meta type for a type definition
\param  strtype - Structure meta type
\param  basecount - Number of base structures
\param  attrcount - Number of attributes
\param  refrcount - Number of references
\param  rshpcount - Number of relationships
\param  idkeynames - Name of the identifying key
\param  w_vf_opt - Consider virtual function pointer
\param  w_schema_version - Scheme version
\param  w_versioning - Consider online versioning for data
\param  glob_identity - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStructDef"

     DBStructDef :: DBStructDef (TypeKey &tkey, int16 strsid, int32 intlen, int32 extlen, TYP_TYPES metatype, SDB_ST strtype, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames, logical w_vf_opt, int16 w_schema_version, logical w_versioning, logical glob_identity )
                     : StructDef(tkey.Name(),tkey.GetID(),strsid,intlen,metatype,strtype),
  base_info(basecount),
  attr_info(attrcount), 
  refr_info(refrcount),
  rshp_info(rshpcount), 
  ext_length(extlen),
  prev_struct_def(NULL),
  schema_version(w_schema_version),
  sb_number(0),
  cluster_option(NO),
  vf_opt(w_vf_opt),
  function_list(NULL), 
  expression_list(new DPA(OPDecl)),
  resource(NULL),
  versioning(w_versioning),
  ext_area(NULL),
  net_length(0),
  global_identity(glob_identity),
  based_on_object(NO),
  check_del_empty(NO),
  view_struct(NULL),
  guid_pos(ERIC),
  guid_pos_ext(ERIC),
  v5_strdef(NULL),
  undef_members(NULL)
{

BEGINSEQ
  if ( metatype == TYP_Base )
    smcbatyp = AT_ODABA;
    
  if ( idkeynames && *idkeynames )
    if ( !(smcbidky = new kcb(idkeynames,this)) )    SDBERR(95)

  smcbsts.stssnof();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStructDef"

     DBStructDef :: DBStructDef ( )
                     : StructDef("",UNDEF,
          UNDEF,UNDEF,TYP_Structure,ST_USER),
  base_info(UNDEF),
  attr_info(UNDEF), 
  refr_info(UNDEF),
  rshp_info(UNDEF), 
  ext_length(UNDEF),
  prev_struct_def(NULL),
  schema_version(0),
  sb_number(0),
  cluster_option(NO),
  vf_opt(NO),
  function_list(NULL), 
  expression_list(new DPA(OPDecl)),
  resource(new DBResource(NULL)),
  versioning(NO),
  ext_area(NULL),
  net_length(UNDEF),
  global_identity(NO),
  based_on_object(NO),
  check_del_empty(NO),
  view_struct(NULL),
  guid_pos(ERIC),
  guid_pos_ext(ERIC),
  v5_strdef(NULL),
  undef_members(NULL)
{

  smcbsts.stssnof();

}

/******************************************************************************/
/**
\brief  DirToRef - 



\return term - Termination code

\param  targfmcb - 
\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replnum - 
\param  copynum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DirToRef"

logical DBStructDef :: DirToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, int16 replnum, int16 copynum )
{
  uint16           slen   = srcefmcb->fmcbbyte/srcefmcb->fmcbdim;
  PropertyHandle  *targpi = (PropertyHandle *)targfld;
  DBFieldDef      *fielddef = targfmcb->GetDescription();
  uint16           i;
  char            *srceinstfld;
  logical          term   = NO;
BEGINSEQ
  if ( fielddef && fielddef->get_sec_reference() ) LEAVESEQ

  if ( targfmcb->fmcbityp == T_MEMO || targfmcb->fmcbityp == T_BLOB )
  {
    if ( !targpi->Provide(FIRST_INSTANCE) )          ERROR
    if ( cvb(srcefmcb,targfmcb,(char *)srcefld,(char *)targpi->Get().GetData()).cvbconv(replnum,NO,copynum) )
                                                     ERROR
    targpi->Modify();                                SDBCERR 
  }
  else
  {
    if ( copynum != REPL_relationships )            // 11.5.00
      if ( targpi->DeleteSet() )                     ERROR
    for ( i = 0, srceinstfld = (char *)srcefld;
          i < srcefmcb->fmcbdim; 
          i++, srceinstfld += slen )
      if ( !targpi->CopyInst(srceinstfld,srcefmcb->fmcbsmcb,(PIREPL)replnum,(PIREPL)copynum) )
                                                     ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  DisplayAlignInfo - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayAlignInfo"

logical DBStructDef :: DisplayAlignInfo ( )
{
  fmcb         *fmcbptr;
  char          pline[1000];
  int16         size_info;
  int16         offset_info;
  int16         indx0 = 0;
  logical       term  = NO;
  printf(
"\nStruct/Member-Name............. Posi/Offs Byte/S-Of b/B   da pa tlen blen ilen");

  strcpy(pline,
"\n................................          ZZZ9 ZZZ9       Z9 Z9 ZZZ9 ZZZ9 ZZZ9");
  
  SDB_Type::GetAlignInfo(smcbname,NULL,size_info,offset_info);
  memcpy (pline+  1,smcbname,ID_SIZE);
  gvtxitp(pline+ 43,GetInstLength(NO),4);
  gvtxitp(pline+ 48,size_info,4);
  gvtxitp(pline+ 59,defined_align,2);
  gvtxitp(pline+ 62,plattform_align,2);
  gvtxitp(pline+ 65,GetLength(),4);
  gvtxitp(pline+ 70,GetInstLength(YES),4);
  gvtxitp(pline+ 75,GetInstLength(NO),4);
  printf(pline);
  
  while ( fmcbptr = GetEntry(++indx0) )
  {
    strcpy(pline,
"\n ...............................ZZZ9 ZZZ9 ZZZ9 ZZZ9       ZZ ZZ ZZZZ ZZZZ ZZZZ");
    
    SDB_Type::GetAlignInfo(smcbname,fmcbptr->fmcbname,size_info,offset_info);
    memcpy (pline+  2,fmcbptr->fmcbname,31);
    gvtxitp(pline+ 33,fmcbptr->fmcbposn,4);
    gvtxitp(pline+ 38,offset_info,4);
    gvtxitp(pline+ 43,fmcbptr->fmcbbyte,4);
    gvtxitp(pline+ 48,size_info,4);
    memcpy (pline+ 53,fmcbptr->fmcbbstr ? "X" : " ",1);
    gvtxitp(pline+ 59,fmcbptr->fmcbsmcb ? fmcbptr->fmcbsmcb->defined_align : 0,2);
    gvtxitp(pline+ 62,fmcbptr->fmcbsmcb ? fmcbptr->fmcbsmcb->plattform_align : 0,2);
    gvtxitp(pline+ 65,fmcbptr->fmcbsmcb ? fmcbptr->fmcbsmcb->GetLength() : 0,4);
    gvtxitp(pline+ 70,fmcbptr->fmcbsmcb ? fmcbptr->fmcbsmcb->GetInstLength(YES) : 0,4);
    gvtxitp(pline+ 75,fmcbptr->fmcbsmcb ? fmcbptr->fmcbsmcb->GetInstLength(NO) : 0,4);
    printf(pline);
  }
  printf(
"\n");

  return(term);
}

/******************************************************************************/
/**
\brief  ExtToInt - 



\return term - Termination code

\param  intinst - 
\param  extinst - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtToInt"

logical DBStructDef :: ExtToInt (void *intinst, char *extinst, logical pif )
{
  DBFieldDef    *fielddef;
  register int   i;
           int   last;

  for (i=1; i<=base_info.get_count(); i++)
    if ( (fielddef = GetEntry(i))->get_privilege() == PI_Exclusive )
      fielddef->GetDBStruct()->ExtToInt(((char *)intinst)+fielddef->fmcbposn,
                                        extinst+fielddef->get_offset_ext(),pif);

  for (last = i+attr_info.get_count()-1; i<=last; i++)
    if ( fielddef = GetEntry(i) )
      fielddef->ExtToIntDim(((char *)intinst)+fielddef->fmcbposn,
                         extinst+fielddef->get_offset_ext(),pif);


  return(NO);
}

/******************************************************************************/
/**
\brief  FillStructure - 



\return term - Termination code

\param  dictptr - Dictionary handle
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillStructure"

logical DBStructDef :: FillStructure (Dictionary *dictptr, PropertyHandle &ph )
{
  char                   *smceiksm;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(smcbname,ID_SIZE)
  
  if ( Initialize(dictptr,ph))                    SDBERR(20)
  
  smceiksm = ph.GetArea("smceiksm");
  if ( *smceiksm != ' ' )
    smcbidky = GetKCB(smceiksm);

  if ( !Setup(dictptr) )                           SDBERR(20)

RECOVER
  smcbsts.stsserr();
  smcbatyp = AT_NONE;
  smcbityp = 0;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillV5StructDef - 



\return term - Termination code

\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillV5StructDef"

logical DBStructDef :: FillV5StructDef (DBStructDef *strdef )
{
  DBFieldDef      *fielddef;
  int16            last;
  int16            i;
  int32            intpos = 0;
  int32            extpos = 0;
  int32            netpos = 0;
  *this = *strdef;
  
  v5_strdef        = NULL;
  smcbacc          = NULL;
  smcbskey         = NULL;
  smcbidky         = NULL;
  expression_list  = NULL;
  function_list    = NULL;
  view_struct      = NULL;
  prev_struct_def  = NULL;
  resource         = NULL;
  ext_area         = NULL;
  
  smcbfmcl = new DBFieldList(strdef->GetEntryCount());
  
  for (i=1; i<=base_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    *fielddef = *strdef->GetEntry(i);
    fielddef->Remove();
    fielddef->fmcbsmcb = ((DBStructDef *)fielddef->fmcbsmcb)->ProvideV5StructDef();
    GetEntry(i)->SetupBaseStruct(intpos,extpos,netpos,defined_align,plattform_align,YES);
  }
  base_info.SetPosition(intpos,extpos);
  
  for (last = i; i<last+attr_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    *fielddef = *strdef->GetEntry(i);
    fielddef->Remove();
    if ( fielddef->fmcbsmcb )
      fielddef->fmcbsmcb = ((DBStructDef *)fielddef->fmcbsmcb)->ProvideV5StructDef();
    fielddef->SetupAttribute(intpos,extpos,netpos,defined_align,plattform_align,YES);
  }
  attr_info.SetPosition(intpos,extpos);

  for (last = i; i<last+refr_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    *fielddef = *strdef->GetEntry(i);
    fielddef->Remove();
    GetEntry(i)->SetupReference(intpos,extpos,netpos,defined_align,plattform_align,YES);
  }
  refr_info.SetPosition(intpos,extpos);

  for (last = i; i<last+rshp_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    *fielddef = *strdef->GetEntry(i);
    fielddef->Remove();
    GetEntry(i)->SetupRelation(intpos,extpos,netpos,smcbsts.stscold(),defined_align,plattform_align,YES);
  }
  rshp_info.SetPosition(intpos,extpos);
  SetLength(intpos,extpos,netpos);



  return(NO);
}

/******************************************************************************/
/**
\brief  FillView - 



\return term - Termination code

\param  dictptr - Dictionary handle
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillView"

logical DBStructDef :: FillView (Dictionary *dictptr, PropertyHandle &ph )
{
  logical                 term = NO;
BEGINSEQ
  smcbsts.stssmod();  
  
  if ( !(view_struct = new DBViewStructDef(this,ph)) )
                                                     SDBERR(95)
  if ( FillStructure(dictptr,ph) )                   ERROR
    
  smcbstyp = ST_VIEW;
  smcbityp = TEMPSID;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetAccess - 



\return accptr - 

\param  atyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccess"

acc *DBStructDef :: GetAccess (int16 atyp )
{

 return( atyp == AT_ODABA || !atyp ? this : NULL);

}

/******************************************************************************/
/**
\brief  GetAttrPath - 



\return cur_indx0 - Position in collection

\param  indx0 - Position in collection
\param  full_path - 
\param  fld_path - Property path
\param  maxlen - Size of the output buffer
\param  with_generics - 
\param  search_in_sharebase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttrPath"

int32 DBStructDef :: GetAttrPath (int32 indx0, logical full_path, char *fld_path, int32 maxlen, logical with_generics, logical search_in_sharebase )
{
  char       local_path[256];
  char       attrnames[ID_SIZE+1];
  fmcb      *fmcbptr;
  int32      curri = AUTO;
  int32      sub_indx0;
  int16      i;
  int16      last;
BEGINSEQ
  *fld_path = 0;
  
  for (i=1; i<=base_info.get_count(); i++)
    if ( search_in_sharebase || GetEntry(i)->get_privilege() != PI_Share )
    {
      ++curri;
      switch ( sub_indx0 = GetEntry(i)->GetDBStruct()->GetAttrPath(indx0-curri,full_path,local_path,sizeof(local_path)-1,with_generics,search_in_sharebase) )
      {
        case ERIC :                                  ERROR
        case AUTO : --curri;                         break;
        default   : if ( (curri += sub_indx0) == indx0 )
                    {
                      if ( full_path )
                      {
                        if ( !gvtscat(fld_path,maxlen,gvtxbts(attrnames,GetEntry(i)->fmcbname,ID_SIZE),".",local_path) )
                                                     ERROR
                      }
                      else
                        if ( !gvtscat(fld_path,maxlen,local_path,NULL,NULL) )
                                                     ERROR
                      LEAVESEQ
                    }
      }
    }
 
  for (last = i; i<last+attr_info.get_count(); i++)
    if ( GetEntry(i)->fmcbbase() || GetEntry(i)->fmcbrlev > 0 || GetEntry(i)->fmcbsmcb->smcbstyp == ST_CODE )
    {
      if ( ++curri == indx0 )
      {
        if ( !gvtscat(fld_path,maxlen,gvtxbts(attrnames,GetEntry(i)->fmcbname,ID_SIZE),NULL,NULL) )
                                                     ERROR
        LEAVESEQ
      }
    }
    else
      if ( with_generics || GetEntry(i)->fmcbrlev != R_GENERIC )
      {
        ++curri;
        switch ( sub_indx0 = GetEntry(i)->GetDBStruct()->GetAttrPath(indx0-curri,full_path,local_path,sizeof(local_path)-1,with_generics) )
        {
          case ERIC :                                ERROR
          case AUTO : --curri;                       break;
          default   : if ( (curri += sub_indx0) == indx0 )
                      {
                        if ( !gvtscat(fld_path,maxlen,gvtxbts(attrnames,GetEntry(i)->fmcbname,ID_SIZE),".",local_path) )
                                                     ERROR
                        LEAVESEQ
                      }
        }
      }
       
  for (last = i; i<last+refr_info.get_count(); i++)
    if ( (fmcbptr = GetEntry(i)) &&
         (fmcbptr->fmcbityp == T_MEMO || fmcbptr->fmcbityp == T_BLOB) )
    {
      if ( ++curri == indx0 )
      {
        if ( !gvtscat(fld_path,maxlen,gvtxbts(attrnames,fmcbptr->fmcbname,ID_SIZE),NULL,NULL) )
                                                     ERROR
        LEAVESEQ
      }
    }

RECOVER
  curri = ERIC;
ENDSEQ
  return(curri);
}

/******************************************************************************/
/**
\brief  GetBaseStructure - 



\return strdef - Structure definition

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseStructure"

DBStructDef *DBStructDef :: GetBaseStructure (int32 indx0 )
{
  DBFieldDef            *fielddef = NULL;
  DBStructDef           *dbstructdef = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( indx0 < 0 || indx0 >= base_info.get_count() ) ERROR

  if ( fielddef = GetEntry(indx0+1) )
    dbstructdef = fielddef->GetDBStruct();

RECOVER
  dbstructdef = NULL;
ENDSEQ
  return(dbstructdef);
}

/******************************************************************************/
/**
\brief  GetDBStruct - 



\return strdef - Structure definition

\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBStruct"

DBStructDef *__cdecl DBStructDef :: GetDBStruct (smcb *smcbptr )
{

  return (   smcbptr && smcbptr->smcbsts.stscnof() 
           ? (DBStructDef *)smcbptr
           : NULL );


}

/******************************************************************************/
/**
\brief  GetDictionary - 



\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionary"

Dictionary *DBStructDef :: GetDictionary ( )
{

  return ( this && resource ? resource->get_dictionary() : NULL);

}

/******************************************************************************/
/**
\brief  GetEntry - 



\return dbfield_ptr - Property definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

DBFieldDef *DBStructDef :: GetEntry (char *fldnames )
{

  return((DBFieldDef *)smcb::GetEntry(fldnames));

}

/******************************************************************************/
/**
\brief  i1 - 



\param  sindex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

DBFieldDef *DBStructDef :: GetEntry (int16 sindex )
{

  return((DBFieldDef *)smcbfmcl->GetEntry(sindex));

}

/******************************************************************************/
/**
\brief  GetEntryCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryCount"

int16 DBStructDef :: GetEntryCount ( )
{

  return (   this 
           ? base_info.get_count() + attr_info.get_count() + 
             refr_info.get_count() + rshp_info.get_count()
           : ERIC );

}

/******************************************************************************/
/**
\brief  GetExprDecl - 



\return expr_decl - 

\param  fctnames - 
\param  retval - 
\param  co - 
\param  parameters - 
\param  convopt - 
\param  recurse_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExprDecl"

OPDecl *DBStructDef :: GetExprDecl (char *fctnames, PropertyHandle *retval, PropertyHandle *co, ParmList *parameters, logical convopt, logical recurse_opt )
{
  OPDecl                 *expr_decl = NULL;
  DBStructDef            *strdef;
  int16                   indx = 0;
BEGINSEQ
  if ( !expression_list )                            ERROR
  
  for ( indx = expression_list->GetSize(); indx; )
    if ( (expr_decl = (*expression_list)[--indx]) &&
         !strcmp(fctnames,expr_decl->get_opname()) )
    {
      if ( !parameters )                             LEAVESEQ
      if ( !expr_decl->Check(retval,co,parameters,convopt) )
                                                     LEAVESEQ
                                                     SDBCERR
    }

  if ( recurse_opt )
    for ( indx = 1; indx <= base_info.get_count(); indx++ )
      if ( strdef = GetEntry(indx)->GetDBStruct() )
        if ( expr_decl = strdef->GetExprDecl(fctnames,retval,co,parameters,convopt,recurse_opt) )
                                                     LEAVESEQ
  ERROR


RECOVER
  expr_decl = NULL;
ENDSEQ
  return(expr_decl);
}

/******************************************************************************/
/**
\brief  GetExtGUIDPosition - 



\return pos - 

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtGUIDPosition"

int32 DBStructDef :: GetExtGUIDPosition (Dictionary *dictptr )
{
  DBFieldDef         *fmcbptr;
  DBFieldDef         *dbfield;
  int16               count = base_info.get_count();
  int16               index = 0;

BEGINSEQ
  if ( guid_pos_ext != ERIC )                        LEAVESEQ
  guid_pos_ext = AUTO;
  
  // 72 is __OBJECT
  if ( !based_on_object && smcbityp != 72 )          ERROR

  if ( fmcbptr = (DBFieldDef *)GetEntry("__GUID") )
    guid_pos_ext = fmcbptr->get_offset_ext();
  else
    while ( index < count )
    {
      dbfield = GetEntry(++index);
      if ( (guid_pos_ext = dbfield->GetDBStruct(dictptr)->GetExtGUIDPosition(dictptr)) >= 0 )
      {
        guid_pos_ext += dbfield->get_offset_ext();     LEAVESEQ
      }
    }    

RECOVER
  guid_pos_ext = AUTO;
ENDSEQ
  return(guid_pos_ext);
}

/******************************************************************************/
/**
\brief  GetFctDecl - 



\return fct_decl - 

\param  fctnames - 
\param  retval - 
\param  co - 
\param  parameters - 
\param  convopt - 
\param  recurse_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFctDecl"

OPFunctionDecl *DBStructDef :: GetFctDecl (char *fctnames, PropertyHandle *retval, PropertyHandle *co, ParmList *parameters, logical convopt, logical recurse_opt )
{
  OPFunctionDecl         *fct_decl = NULL;
  DBStructDef            *strdef;
  int16                   indx = 0;
BEGINSEQ
  if ( !function_list )                              ERROR
    
  function_list->GoTop();
  while ( fct_decl = function_list->GetNext() )
    if ( !strcmp(fctnames,fct_decl->get_opname()) )
    {
      if ( !fct_decl->Check(retval,co,parameters,convopt) ) 
                                                     LEAVESEQ
                                                     SDBCERR
    }

  if ( recurse_opt )
    for ( indx = 1; indx <= base_info.get_count(); indx++ )
      if ( strdef = GetEntry(indx)->GetDBStruct() )
        if ( fct_decl = strdef->GetFctDecl(fctnames,retval,co,parameters,convopt,recurse_opt) )
                                                     LEAVESEQ
  ERROR

RECOVER
  fct_decl = NULL;
ENDSEQ
  return(fct_decl);
}

/******************************************************************************/
/**
\brief  GetGUIDPosition - 



\return pos - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGUIDPosition"

int32 DBStructDef :: GetGUIDPosition ( )
{
  fmcb              *fmcbptr;
  int32               offset = 0;
BEGINSEQ
  if ( guid_pos != ERIC )                            LEAVESEQ
  guid_pos = AUTO;
  
  if ( !based_on_object )                            ERROR

  if ( !(fmcbptr = SearchField("__GUID",&offset)) )  SDBERR(99)

  guid_pos = offset + fmcbptr->fmcbposn;
RECOVER

ENDSEQ
  return(guid_pos);
}

/******************************************************************************/
/**
\brief  GetKeySMCB - 



\return smcbptr - Pointer to general structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeySMCB"

smcb *DBStructDef :: GetKeySMCB ( )
{
  kcb        *kcbptr;
  smcb       *smcbptr = NULL;

  if ( kcbptr  = smcbidky )
    smcbptr = kcbptr->scbsmcb;


  return(smcbptr);

}

/******************************************************************************/
/**
\brief  GetMetaAttribute - 



\return dbfield_def - 

\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMetaAttribute"

DBFieldDef *__cdecl DBStructDef :: GetMetaAttribute (char *prop_names )
{
  DBFieldDef             *dbfield_def = NULL;
BEGINSEQ
  if ( *prop_names != '_' )                          ERROR

  dbfield_def = DBFieldDef::GetStaticFieldDef(prop_names);

RECOVER
  dbfield_def = NULL;
ENDSEQ
  return(dbfield_def);
}

/******************************************************************************/
/**
\brief  GetNetLength - 



\return len - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNetLength"

uint32 DBStructDef :: GetNetLength ( )
{

  return(net_length);

}

/******************************************************************************/
/**
\brief  GetPHFctDecl - 



\return fct_decl - 

\param  fctnames - 
\param  retval - 
\param  co - 
\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPHFctDecl"

OPFunctionDecl *__cdecl DBStructDef :: GetPHFctDecl (char *fctnames, PropertyHandle *retval, PropertyHandle *co, ParmList *parameters )
{
  OPFunctionDecl           *fct_decl = NULL;
BEGINSEQ
  fct_decl = new OPFunctionDecl(NULL,"PropertyHandle",NULL,co,fctnames);
  if ( fct_decl->Check(retval,co,parameters,YES) )       ERROR

RECOVER
  delete fct_decl;
  fct_decl = NULL;
ENDSEQ
  return(fct_decl);
}

/******************************************************************************/
/**
\brief  GetRefPath - 



\return cur_indx0 - Position in collection

\param  indx0 - Position in collection
\param  full_path - 
\param  fld_path - Property path
\param  maxlen - Size of the output buffer
\param  with_generics - 
\param  search_in_sharebase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefPath"

int32 DBStructDef :: GetRefPath (int32 indx0, logical full_path, char *fld_path, int32 maxlen, logical with_generics, logical search_in_sharebase )
{
  char       local_path[256];
  char       refnames[ID_SIZE+1];
  fmcb      *fmcbptr;
  int32      curri = AUTO;
  int32      sub_indx0;
  int16      i;
  int16      last;
BEGINSEQ
  *fld_path = 0;
  
  for (i=1; i<=base_info.get_count(); i++)
    if ( search_in_sharebase || GetEntry(i)->get_privilege() != PI_Share )
    {
      ++curri;
      switch ( sub_indx0 = GetEntry(i)->GetDBStruct()->GetRefPath(indx0-curri,full_path,local_path,sizeof(local_path)-1,with_generics,search_in_sharebase) )
      {
        case ERIC :                                  ERROR
        case AUTO : --curri;                         break;
        default   : if ( (curri += sub_indx0) == indx0 )
                    {
                      if ( full_path )
                      {
                        if ( !gvtscat(fld_path,maxlen,gvtxbts(refnames,GetEntry(i)->fmcbname,ID_SIZE),".",local_path) )
                                                     ERROR
                      }
                      else
                        if ( !gvtscat(fld_path,maxlen,local_path,NULL,NULL) )
                                                     ERROR
                      LEAVESEQ
                    }
      }
    }
 
  for (last = i; i<last+attr_info.get_count(); i++)
    if ( with_generics && GetEntry(i)->fmcbrlev == R_GENERIC )
    {
      if ( ++curri == indx0 )
      {
        if ( !gvtscat(fld_path,maxlen,gvtxbts(refnames,GetEntry(i)->fmcbname,ID_SIZE),NULL,NULL) )
                                                     ERROR
        LEAVESEQ
      }
    }
    else
      if ( !GetEntry(i)->fmcbbase() && GetEntry(i)->fmcbrlev <= 0 && GetEntry(i)->fmcbsmcb->smcbstyp != ST_CODE ) 
      {
        ++curri;
        switch ( sub_indx0 = GetEntry(i)->GetDBStruct()->GetRefPath(indx0-curri,full_path,local_path,sizeof(local_path)-1,with_generics) )
        {
          case ERIC :                                    ERROR
          case AUTO : --curri;                           break;
          default   : if ( (curri += sub_indx0) == indx0 )
                      {
                        if ( !gvtscat(fld_path,maxlen,gvtxbts(refnames,GetEntry(i)->fmcbname,ID_SIZE),".",local_path) )
                                                         ERROR
                        LEAVESEQ
                      }
        }
      }
    
  for (last = i; i<last+refr_info.get_count(); i++)
    if ( (fmcbptr = GetEntry(i)) &&
         fmcbptr->fmcbityp != T_MEMO && fmcbptr->fmcbityp != T_BLOB )
      if ( ++curri == indx0 )
      {
        if ( !gvtscat(fld_path,maxlen,gvtxbts(refnames,fmcbptr->fmcbname,ID_SIZE),NULL,NULL) )
                                                     ERROR
        LEAVESEQ
      }
    
  for (last = i; i<last+rshp_info.get_count(); i++)
    if ( ++curri == indx0 )
    {
      if ( !gvtscat(fld_path,maxlen,gvtxbts(refnames,GetEntry(i)->fmcbname,ID_SIZE),NULL,NULL) )
                                                     ERROR
      LEAVESEQ
    }

RECOVER
  curri = ERIC;
ENDSEQ
  return(curri);
}

/******************************************************************************/
/**
\brief  GetShareBasePath - 



\return cur_indx0 - Position in collection

\param  indx0 - Position in collection
\param  full_path - 
\param  fld_path - Property path
\param  maxlen - Size of the output buffer
\param  search_in_sharebase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetShareBasePath"

int32 DBStructDef :: GetShareBasePath (int32 indx0, logical full_path, char *fld_path, int32 maxlen, logical search_in_sharebase )
{
  char       local_path[256];
  char       basenames[ID_SIZE+1];
  int32       curri = AUTO;
  int32       sub_indx0;
  int16      i;
BEGINSEQ
  *fld_path = 0;
  
  for (i=1; i<=base_info.get_count(); i++)
  {
    if ( GetEntry(i)->get_privilege() == PI_Share )
    {
      if ( ++curri == indx0 )
      {
        if ( !gvtscat(fld_path,maxlen,gvtxbts(basenames,GetEntry(i)->fmcbname,ID_SIZE),NULL,NULL) )
                                                     ERROR
        LEAVESEQ
      }
    }
    if ( search_in_sharebase || GetEntry(i)->get_privilege() != PI_Share )
    {
      ++curri;
      switch ( sub_indx0 = GetEntry(i)->GetDBStruct()->GetShareBasePath(indx0-curri,full_path,local_path,sizeof(local_path)-1) )
      {
        case ERIC :                                  ERROR
        case AUTO : --curri;                         break;
        default   : if ( (curri += sub_indx0) == indx0 )
                    {
                      if ( full_path )
                      {
                        if ( !gvtscat(fld_path,maxlen,gvtxbts(basenames,GetEntry(i)->fmcbname,ID_SIZE),".",local_path) )
                                                     ERROR
                      }
                      else
                        if ( !gvtscat(fld_path,maxlen,local_path,NULL,NULL) )
                                                     ERROR
                      LEAVESEQ
                    }
      }
    }
  }
RECOVER
  curri = ERIC;
ENDSEQ
  return(curri);
}

/******************************************************************************/
/**
\brief  GetSortKeySMCB - 



\return smcbptr - Pointer to general structure definition

\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeySMCB"

smcb *DBStructDef :: GetSortKeySMCB (char *fldnames )
{
  DBFieldDef *dbfield;
  DBIndex    *dbindex;
  kcb        *kcbptr;
  smcb       *smcbptr = NULL;

BEGINSEQ
  if ( !(dbfield = GetEntry(fldnames)) )             ERROR

  if ( !dbfield->get_index_list() )                  ERROR
    
  if ( (dbindex = dbfield->get_index_list()->GetHead()) &&
       (kcbptr  = dbindex->get_key_def()) )
    smcbptr = kcbptr->scbsmcb;


RECOVER

ENDSEQ
  return(smcbptr);

}

/******************************************************************************/
/**
\brief  GetStrDefVersion - 



\return strdef_ptr - Internal data structure definition

\param  dictptr - Dictionary handle
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStrDefVersion"

DBStructDef *DBStructDef :: GetStrDefVersion (Dictionary *dictptr, uint8 schemaversion )
{
  DBStructDef      *strdef_ptr = this;
BEGINSEQ
  if ( schemaversion >= schema_version )             LEAVESEQ
  if ( !prev_struct_def )
    if ( !(prev_struct_def = dictptr->GetStrDefVersion(GetTypeKey(),schema_version-1)) )
                                                     ERROR
  if ( !(strdef_ptr = prev_struct_def->GetStrDefVersion(dictptr,schemaversion)) )
                                                     ERROR
RECOVER
  strdef_ptr = NULL;
ENDSEQ
  return(strdef_ptr);
}

/******************************************************************************/
/**
\brief  GetSysFctDecl - 



\return fct_decl - 

\param  fctnames - 
\param  retval - 
\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSysFctDecl"

OPFunctionDecl *__cdecl DBStructDef :: GetSysFctDecl (char *fctnames, PropertyHandle *retval, ParmList *parameters )
{
  OPFunctionDecl  *fct_decl = NULL;
BEGINSEQ
  fct_decl = new OPFunctionDecl(NULL,"SystemClass",NULL,NULL,fctnames);
  
  if ( fct_decl->Check(retval,NULL,parameters,YES) ) ERROR
  
  

RECOVER
  delete fct_decl;
  fct_decl = NULL;
ENDSEQ
  return(fct_decl);
}

/******************************************************************************/
/**
\brief  GetTypeKey - 



\return tkey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeKey"

TypeKey &DBStructDef :: GetTypeKey ( )
{

  return( *(TypeKey *)smcbname );

}

/******************************************************************************/
/**
\brief  GetViewStructDef - 



\return vstrdef - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetViewStructDef"

DBViewStructDef *DBStructDef :: GetViewStructDef ( )
{

  return ( this ? view_struct : NULL );

}

/******************************************************************************/
/**
\brief  IncreaseAttrCount - 




\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IncreaseAttrCount"

void DBStructDef :: IncreaseAttrCount (int32 count )
{

  attr_info.set_count(attr_info.get_count()+count);

}

/******************************************************************************/
/**
\brief  IncreaseBaseCount - 




\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IncreaseBaseCount"

void DBStructDef :: IncreaseBaseCount (int32 count )
{

  base_info.set_count(base_info.get_count()+count);

}

/******************************************************************************/
/**
\brief  IncreaseRefrCount - 




\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IncreaseRefrCount"

void DBStructDef :: IncreaseRefrCount (int32 count )
{

  refr_info.set_count(refr_info.get_count()+count);

}

/******************************************************************************/
/**
\brief  IncreaseRshpCount - 




\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IncreaseRshpCount"

void DBStructDef :: IncreaseRshpCount (int32 count )
{

  rshp_info.set_count(rshp_info.get_count()+count);

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

logical DBStructDef :: Inherits (char *strnames )
{
  char            strname[ID_SIZE];
  logical         cond = YES;
BEGINSEQ
  gvtxstb(strname,strnames,ID_SIZE);
  
  if ( !memcmp(strname,smcbname,ID_SIZE) )           LEAVESEQ
  
  cond = IsBasedOn(strnames);

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  InitAttributes - 




\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitAttributes"

void DBStructDef :: InitAttributes (void *instptr )
{
  DBFieldDef    *fielddef;
  char           string[ID_SIZE+1];
  register int   i;
           int   last;
BEGINSEQ
  if ( !this )                                       ERROR
  
  for (i=1; i<=base_info.get_count(); i++)
    if ( fielddef = GetEntry(i) )
      fielddef->GetDBStruct()->InitAttributes(((char *)instptr)+fielddef->fmcbposn);

  for (last = i+attr_info.get_count()-1; i<=last; i++)
    if ( fielddef = GetEntry(i) )
      fielddef->InitAttribute(((char *)instptr)+fielddef->fmcbposn);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  InitExtInst - 



\return term - Termination code

\param  targinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExtInst"

logical DBStructDef :: InitExtInst (void *targinst )
{
  DBFieldDef             *field_def;
  int16                   i;
  int16                   last;
  logical                 term = NO;
BEGINSEQ
  if ( !smcbfmcl )                                   LEAVESEQ

  if ( smcbstyp == ST_CODE )
  {
    memset(targinst,0,2);
    LEAVESEQ
  }
  memset(targinst,0,ext_length);
  
  for (i=1; i<=base_info.get_count(); i++)
    if ( (field_def = GetEntry(i))->get_privilege() == PI_Exclusive )
      field_def->GetDBStruct()->InitExtInst(((char *)targinst)+field_def->get_offset_ext());

  for (last = i+attr_info.get_count()-1; i<=last; i++)
    if ( field_def = GetEntry(i) )
      field_def->InitExtInst(((char *)targinst)+field_def->get_offset_ext());
ENDSEQ
  return(term);
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

logical DBStructDef :: InitInstance (void *instptr )
{

  smcb::Initialize((char *)instptr);

  InitAttributes(instptr);

  return(NO);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code

\param  dictptr - Dictionary handle
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DBStructDef :: Initialize (Dictionary *dictptr, PropertyHandle &ph )
{
  DBFieldList            *fmcdptr;
  SDB_Attribute          *attrptr;
  SDB_BaseStruct         *baseptr;
  SDB_Reference          *refrptr;
  SDB_Relationship       *rshpptr;
  int16                   count;
  int32                   indx0;
  int16                   curindx = 0;
  logical                 term = NO;
BEGINSEQ
  memcpy(smcbname,ph.GetArea("sys_ident"),ID_SIZE);

if ( dictptr->get_sys_version() > 17 )
  smcbnsid          = ph.GetInt("namespace_id");
else smcbnsid = 0;
  smcbatyp          = ph.GetInt("access_type");
  defined_align     = ph.GetInt("allignment");
  schema_version    = ph.GetInt("version");
  vf_opt            = *ph.GetArea("vf_opt") == YES;
  versioning        = *ph.GetArea("versioning") == YES;
  global_identity   = ph.IsTrue("global_identity");
  if ( !(smcbstyp = ph.GetInt("smcestyp")) )
    smcbstyp = dictptr->GetSType(ph.GetInt("typetype"));
  
  if ( !defined_align )
    defined_align = DEFAULT_ALLIGNMENT;
  
  if ( !resource )
    if ( !(resource = new DBResource(dictptr)) )     SDBERR(95)
  if ( resource->Initialize(ph) )                    ERROR

/* smceodaba gibts nicht mehr. Die Angaben müssen aus der Structure geholt werden  
  PH(&ph,smceodaba);
  if ( smceodaba(0L) ) 
  {
    sb_number      = smceodaba.GetInt("sb_number");
    cluster_option = smceodaba.IsTrue("clustered");
  }
*/
  PH(&ph,smcebase);
  PH(&ph,smcepdde);
  PH(&ph,smcepref);
  PH(&ph,smcershp);
  count  = base_info.set_count((int16)smcebase.GetCount());
  count += attr_info.set_count((int16)smcepdde.GetCount() + vf_opt);
  count += refr_info.set_count((int16)smcepref.GetCount());
  count += rshp_info.set_count((int16)smcershp.GetCount());

  if ( !(fmcdptr = new DBFieldList(count)) )         SDBERR(95)
                                                     SDBCERR
  smcbfmcl = fmcdptr;

  indx0 = 0;
  while ( smcebase(indx0++) )
    GetEntry(++curindx)->FillBaseStruct(smcebase,dictptr,smcbnsid,YES);

  if ( vf_opt )
  {
    SDB_Member   sdbmem("__vfptr","VOID",RL_1,0,0,1,"",NO,NO,UNDEF);
    SDB_Property vf_attr(sdbmem,YES,NO);
    GetEntry(++curindx)->Fill((SDB_Attribute *)&vf_attr,dictptr);
  }
  indx0 = 0;
  while ( smcepdde(indx0++) )
    GetEntry(++curindx)->FillAttribute(smcepdde,dictptr,smcbnsid);

  indx0 = 0;
  while ( smcepref(indx0++) )
    GetEntry(++curindx)->FillReference(smcepref,dictptr,smcbnsid,YES);

  indx0 = 0;
  while ( smcershp(indx0++) )
    GetEntry(++curindx)->FillRelationship(smcershp,dictptr,smcbnsid,YES);
  
  if ( CreateKeyDefs(ph) )                           ERROR
  if ( !(smcbityp = ph.GetInt("itype")) )
  {
    smcbityp = TEMPSID;
    if ( smcbatyp == AT_ODABA || smcbstyp == ST_CODE )
{
  char           string[129];
  LDictionary   *ldict = dictptr->GetLocalDictionary();
  strcpy(string,ldict ? ldict->get_db_path() : "");
  strcat(string,": ODABA2-Type without Internal ID: ");
  gvtxbts(&string[strlen(string)],smcbname,ID_SIZE);
  SDBError().TraceMessage(string);
}
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IntToExt - 



\return term - Termination code

\param  extinst - 
\param  intinst - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntToExt"

logical DBStructDef :: IntToExt (char *extinst, void *intinst, logical pif )
{
  DBFieldDef      *fielddef;
  register int     i;
           int     last;
           logical term = NO;


  for (i=1; i<=base_info.get_count(); i++)
    if ( (fielddef = GetEntry(i))->get_privilege() == PI_Exclusive )
      if ( fielddef->GetDBStruct()->IntToExt(extinst+fielddef->get_offset_ext(),
                                        ((char *)intinst)+fielddef->fmcbposn,pif) )
        term = YES;

  for (last = i+attr_info.get_count()-1; i<=last; i++)
    if ( fielddef = GetEntry(i) )
      if ( fielddef->IntToExtDim(extinst+fielddef->get_offset_ext(),
                         ((char *)intinst)+fielddef->fmcbposn,pif) )
        term = YES;


  return(term);
}

/******************************************************************************/
/**
\brief  IntToNet - 



\return term - Termination code

\param  netinst - 
\param  intinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntToNet"

logical DBStructDef :: IntToNet (char *netinst, void *intinst )
{
  DBFieldDef    *fielddef;
  register int   i;
           int   last;


  for (i=1; i<=base_info.get_count(); i++)
    if ( fielddef = GetEntry(i) )
      fielddef->GetDBStruct()->IntToNet(netinst+fielddef->get_net_pos(),
                                        ((char *)intinst)+fielddef->fmcbposn);

  for (last = i+attr_info.get_count()-1; i<=last; i++)
    if ( fielddef = GetEntry(i) )
      fielddef->IntToNet(netinst+fielddef->get_net_pos(),
                         ((char *)intinst)+fielddef->fmcbposn);


  return(NO);
}

/******************************************************************************/
/**
\brief  IsBaseCollection - 



\return cond - 

\param  dictptr - Dictionary handle
\param  tkey - 
\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBaseCollection"

logical DBStructDef :: IsBaseCollection (Dictionary *dictptr, TypeKey &tkey, char *fldnames )
{
  DBFieldDef     *dbfield;
  DBStructDef    *strdef;
  int16           index = base_info.get_count() + 
                          attr_info.get_count() + 
                          refr_info.get_count();
  int16           count = index + rshp_info.get_count(); 
  logical         cond  = YES;
  char            string[ID_SIZE+1];
  const char     *extnames;
BEGINSEQ
  gvtxbts(string,fldnames,ID_SIZE);
  
  while ( index < count )
  {
    dbfield = GetEntry(++index);
    if ( dbfield->IsInverseBased(dictptr,tkey,fldnames) )
                                                     LEAVESEQ
  }
  
  if ( !(strdef = dictptr->GetStructDef(tkey)) )     ERROR
  if ( strdef->IsBased(dictptr,tkey,fldnames) )      LEAVESEQ
    
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsBased - 



\return cond - 

\param  dictptr - Dictionary handle
\param  tkey - 
\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBased"

logical DBStructDef :: IsBased (Dictionary *dictptr, TypeKey &tkey, char *fldnames )
{
  DBFieldDef     *dbfield;
  int16           index = base_info.get_count() + 
                          attr_info.get_count() + 
                          refr_info.get_count();
  int16           count = index + rshp_info.get_count(); 
  logical         cond  = YES;
  char            string[ID_SIZE+1];
  const char     *extnames;
BEGINSEQ
  gvtxbts(string,fldnames,ID_SIZE);
  while ( index < count )
  {
    dbfield = GetEntry(++index);
    if ( dbfield->IsBased(dictptr,tkey,fldnames) )   LEAVESEQ
  }
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
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

logical DBStructDef :: IsBasedOn (char *strnames )
{
  DBFieldDef     *dbfield;
  int16           count = base_info.get_count();
  int16           index = 0;
  char            strname[ID_SIZE];
  logical         cond = YES;
BEGINSEQ
  gvtxstb(strname,strnames,ID_SIZE);
  while ( index < count )
  {
    dbfield = GetEntry(++index);
    if ( !memcmp(strname,dbfield->fmcbtype,ID_SIZE) ||
          dbfield->GetDBStruct()->IsBasedOn(strnames) ) LEAVESEQ
  }
  
  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsPathNode - 



\return cond - 

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPathNode"

logical __cdecl DBStructDef :: IsPathNode (char *prop_path )
{

  return ( STRSearchChar(prop_path,'(',NO) ||
           STRSearchChar(prop_path,'[',NO) ||
           STRSearchChar(prop_path,'{',NO)    );


}

/******************************************************************************/
/**
\brief  IsPropertyPath - 



\return cond - 

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPropertyPath"

logical __cdecl DBStructDef :: IsPropertyPath (char *prop_path )
{
  char       *pos;
  return ( !IsPathNode(prop_path)         &&
           !(pos = strchr(prop_path,','))   );


}

/******************************************************************************/
/**
\brief  IsUndefinedMember - 



\return cond - 

\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUndefinedMember"

logical DBStructDef :: IsUndefinedMember (char *prop_names )
{
  char                    string[ID_SIZE+1];
  logical                 cond = NO;
BEGINSEQ
  if ( !undef_members || !prop_names )               LEAVESEQ
  
  if ( !undef_members->srtssr(gvtxbts(string,prop_names,ID_SIZE)) )
                                                     LEAVESEQ
  cond = YES;

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsViewPath - 



\return cond - 

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsViewPath"

logical __cdecl DBStructDef :: IsViewPath (char *prop_path )
{
  char       *pos;
  return ( !IsPathNode(prop_path)              &&
           ((pos = strchr(prop_path,'.')) || 
            (pos = strchr(prop_path,','))    ) &&
           pos-prop_path <= ID_SIZE                );


}

/******************************************************************************/
/**
\brief  NetToInt - 



\return term - Termination code

\param  intinst - 
\param  netinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NetToInt"

logical DBStructDef :: NetToInt (void *intinst, char *netinst )
{
  DBFieldDef    *fielddef;
  register int   i;
           int   last;

  for (i=1; i<=base_info.get_count(); i++)
    if ( fielddef = GetEntry(i) )
      fielddef->GetDBStruct()->NetToInt(((char *)intinst)+fielddef->fmcbposn,
                                        netinst+fielddef->get_net_pos());

  for (last = i+attr_info.get_count()-1; i<=last; i++)
    if ( fielddef = GetEntry(i) )
      fielddef->NetToInt(((char *)intinst)+fielddef->fmcbposn,
                         netinst+fielddef->get_net_pos());

  return(NO);
}

/******************************************************************************/
/**
\brief  ProvideKCB - 



\return kcbptr - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  sdbkey - 
\param  last_key_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideKCB"

kcb *DBStructDef :: ProvideKCB (SDB_Key *sdbkey, int32 last_key_number )
{
  kcb                    *kcbptr = NULL;
  int16                   key_number;
BEGINSEQ
  if ( !(kcbptr = GetKCB(sdbkey->get_sys_ident())) )
  {
    if ( !(kcbptr = new kcb(sdbkey->get_sys_ident(),this)) )
                                                     SDBERR(95)
  }
  if ( !kcbptr->get_key_num() )
  {
    if ( !(key_number = sdbkey->get___AUTOIDENT()) )
      key_number = last_key_number+1;
    kcbptr->SetKeyNumber(key_number);
  }  

RECOVER
  kcbptr = NULL;
ENDSEQ
  return(kcbptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  keyname - 
\param  keynum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideKCB"

kcb *DBStructDef :: ProvideKCB (char *keyname, int32 keynum )
{
  kcb                    *kcbptr = NULL;
BEGINSEQ
  if ( !(kcbptr = GetKCB(keyname)) )
  {
    if ( !(kcbptr = new kcb(keyname,this)) )         SDBERR(95)
    kcbptr->SetKeyNumber(keynum);
  }

RECOVER
  kcbptr = NULL;
ENDSEQ
  return(kcbptr);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  ph - 
\param  last_key_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideKCB"

kcb *DBStructDef :: ProvideKCB (PropertyHandle &ph, int32 last_key_number )
{
  kcb                    *kcbptr = NULL;
  int16                   key_number;
BEGINSEQ
  if ( !(kcbptr = GetKCB(ph.GetArea("sys_ident"))) )
  {
    if ( !(kcbptr = new kcb(ph.GetArea("sys_ident"),this)) )
                                                     SDBERR(95)
  }
  if ( !kcbptr->get_key_num() )
  {
    if ( !(key_number = ph.GetInt("__AUTOIDENT")) )
      key_number = last_key_number+1;
    kcbptr->SetKeyNumber(key_number);
  }  

RECOVER
  kcbptr = NULL;
ENDSEQ
  return(kcbptr);
}

/******************************************************************************/
/**
\brief  ProvideV5StructDef - 



\return strdef - Structure definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideV5StructDef"

DBStructDef *DBStructDef :: ProvideV5StructDef ( )
{
  DBStructDef      *strdef = v5_strdef;
BEGINSEQ
  if ( strdef )                                      LEAVESEQ
    
  strdef = this;
  if ( smcbstyp == ST_CODE )                         LEAVESEQ

  strdef = v5_strdef = new DBStructDef();
  v5_strdef->FillV5StructDef(this);
  

ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  RefToDir - 



\return term - Termination code

\param  targfmcb - 
\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replnum - 
\param  copynum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefToDir"

logical DBStructDef :: RefToDir (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, int16 replnum, int16 copynum )
{
  uint16           tlen   = targfmcb->fmcbbyte/targfmcb->fmcbdim;
  PropertyHandle  &srcepi = *(PropertyHandle *)srcefld;
  char            *srceinst;
  uint16           i;
  char            *instptr;
  char            *targinstfld;
  logical          term   = NO;
BEGINSEQ
  if ( srcefmcb->fmcbityp == T_MEMO || srcefmcb->fmcbityp == T_BLOB )
  {
    if ( srceinst = (char *)srcepi(0L).GetData() )
      if ( cvb(srcefmcb,targfmcb,srceinst,(char *)targfld).cvbconv(replnum,NO,copynum) )
                                                       ERROR
  }
  else
    for ( i = 0, targinstfld = (char *)targfld;
        i < targfmcb->fmcbdim && (instptr = (char *)srcepi(i).GetData()); 
        i++, targinstfld += tlen )
      if ( cvb(srcefmcb,targfmcb,instptr,targinstfld).cvbconv(replnum,NO,copynum) )
                                                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  RefToRef - 



\return term - Termination code

\param  targfmcb - 
\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replnum - 
\param  copynum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefToRef"

logical DBStructDef :: RefToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targfld, void *srcefld, int16 replnum, int16 copynum )
{
  logical   term   = NO;
  PropertyHandle  *targpi = (PropertyHandle *)targfld;
  PropertyHandle  &srcepi = *(PropertyHandle *)srcefld;
  DBFieldDef      *fielddef = targfmcb->GetDescription();
BEGINSEQ
  if ( fielddef && fielddef->get_sec_reference() ) LEAVESEQ

  if ( targfmcb->fmcbityp == T_MEMO || targfmcb->fmcbityp == T_BLOB )
  {
    if ( srcepi(0L) )
    {
      if ( targpi->Provide(FIRST_INSTANCE) )
        if ( targfmcb->fmcbidtd(srcefmcb,(char *)targpi->Get().GetData(),(char *)srcepi.Get().GetData(),replnum,copynum) )
                                                      ERROR
      targpi->Modify();                               SDBCERR 
    }
    else  
      if ( targpi->DeleteSet() )                      ERROR
  }
  else
  {
//    if ( replnum != REPL_relationships )
    if ( copynum != REPL_relationships )              // 11.5.00
      if ( targpi->DeleteSet() )                      ERROR
    if ( targpi->CopySet(srcepi,(PIREPL)replnum,(PIREPL)copynum,YES) < 0) 
                                                      ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  RemExpr - 




\param  expr_decl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemExpr"

void DBStructDef :: RemExpr (OPDecl *expr_decl )
{
  int16                   indx = 0;
  if ( expression_list )                             
  {
    for ( indx = expression_list->GetSize(); indx; )
      if ( expr_decl == (*expression_list)[--indx] )
      {
        (*expression_list)[indx] = NULL;
        break;
      }
  }

}

/******************************************************************************/
/**
\brief  SearchPathField - 



\return fielddef - Internal field defintion

\param  dictionary - 
\param  fldpath - 
\param  refr_opt - 
\param  offsetpt - 
\param  w_kcbptr - 
\param  w_typsmcb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchPathField"

DBFieldDef *DBStructDef :: SearchPathField (Dictionary *dictionary, char *fldpath, logical refr_opt, int32 *offsetpt, kcb *w_kcbptr, smcb **w_typsmcb )
{
  char           *pkt;
  char           *end;
  char           *par;
  char            fldname[ID_SIZE];
  char            fldnames[ID_SIZE+1];
  DBFieldDef     *fielddef = NULL;
  DBFieldDef     *tfielddef;
  short           indx    = 0;
  char            path[2001];
  int             len = strlen(fldpath);
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  if ( len > 2000 )                                  SDBERR(99)
  
  if ( w_typsmcb )
    *w_typsmcb = NULL;
  
  strcpy(path,fldpath);
  if ( pkt = NextProperty(path,&par) )
    *pkt = 0;
  if ( par )
    *par = 0;
  gvtxstb(fldname,path,ID_SIZE);
  
  if ( !(fielddef = GetEntry(fldname)) ) 
  {
    gvtxbts(fldnames,fldname,ID_SIZE);
    while ( (tfielddef = GetEntry(++indx)) && tfielddef->fmcbbstr && tfielddef->fmcbsmcb  )
      if ( fielddef = tfielddef->GetDBStruct()->SearchPathField(dictionary,fldnames,refr_opt,offsetpt,w_kcbptr,w_typsmcb) )
      {
        *offsetpt += tfielddef->fmcbposn;
        break;
      }
  }
  if ( !fielddef )           // jetzt schaun wir noch mal mit Klammern, sowas gibts in OMA
  {
    gvtxstb(fldname,fldpath,ID_SIZE);
    if ( !(fielddef = GetEntry(fldname)) )           ERROR
  }
  
  if ( w_kcbptr && fielddef->fmcbrlev == R_GENERIC )
    if ( w_kcbptr->SetGenField(fielddef,*offsetpt) )   ERROR

  if ( pkt )
  {
    if ( !fielddef->GetDBStruct(dictionary) )        ERROR
    if ( fielddef->fmcbrlev == R_REFR || fielddef->fmcbrlev > 0 ) 
    {
      if ( !refr_opt )                               ERROR
      *offsetpt = UNDEF;
    }
    else
      *offsetpt += fielddef->fmcbposn;
    
    if ( !(fielddef = fielddef->GetDBStruct()->SearchPathField(dictionary,pkt+1,refr_opt,offsetpt,w_kcbptr,w_typsmcb)) )
                                                     ERROR
    *pkt = '.';
  }

  if ( w_typsmcb && !*w_typsmcb )
    *w_typsmcb = this;

RECOVER
  fielddef = NULL;
ENDSEQ
  return(fielddef);

}

/******************************************************************************/
/**
\brief  SetAccess - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAccess"

void DBStructDef :: SetAccess ( )
{

  switch ( smcbatyp )
  {
    case AT_ODABA   : smcbacc = this;                 
    case AT_CODE    : break;
    case AT_BIN     : 
    case AT_NONE    : 
    default         : if ( (acc *)this != smcbacc  )
                        delete smcbacc;
                      smcbacc = new acc(NO);                                                                                 
  }


}

/******************************************************************************/
/**
\brief  SetEnumFieldList - 



\return term - Termination code

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEnumFieldList"

logical DBStructDef :: SetEnumFieldList (Dictionary *dictptr )
{
  DBStructDef          *value_str = dictptr->ProvideStructDef("ENUM_Value");
  logical               term = NO;
BEGINSEQ
  smcbfmcl = value_str->smcbfmcl;
  attr_info.set_count(smcbfmcl->srtcnt());

  smcbskey = value_str->smcbskey;
  smcbidky = value_str->smcbidky;

//  smcbityp = value_str->smcbityp;
  smcbityp = TEMPSID;
  
  if ( !Setup(dictptr) )                              ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetFctTable - 



\return term - Termination code

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFctTable"

logical DBStructDef :: SetFctTable (Dictionary *dictptr )
{
  void      *dummy_for_unix = NULL;
BEGINSEQ
  if ( function_list )                               LEAVESEQ

  function_list = new DLL(OPFunctionDecl);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetLength - 



\return term - Termination code

\param  intpos - 
\param  extpos - 
\param  netpos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLength"

logical DBStructDef :: SetLength (int32 &intpos, int32 &extpos, int32 &netpos )
{
  logical                 term = NO;
BEGINSEQ
  smcb::SetLength(intpos);
  ext_length = extpos;
  net_length = netpos;
  
  delete ext_area;
  ext_area = NULL;
  
  if ( ext_length > 0 )
    if ( !(ext_area = new char[ext_length]) )        SDBERR(95)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetMemberInfo - 




\param  basecount - Number of base structures
\param  attrcount - Number of attributes
\param  refrcount - Number of references
\param  rshpcount - Number of relationships
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMemberInfo"

void DBStructDef :: SetMemberInfo (int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount )
{

  if ( this )
  {
    base_info.set_count(basecount);
    attr_info.set_count(attrcount);
    refr_info.set_count(refrcount);
    rshp_info.set_count(rshpcount);
  }


}

/******************************************************************************/
/**
\brief  Setup - 



\return dbstr_ptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  mpool - 
\param  fieldlist - 
\param  idkeynames - Name of the identifying key
\param  keyfieldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

DBStructDef *DBStructDef :: Setup (void *mpool, DBFieldDef *fieldlist, char *idkeynames, char *keyfieldname )
{
  DBFieldDef   *fielddef;
  char          fname[ID_SIZE];
  int16         last;
  int16         i;
  int32         intpos = 0;
  int32         extpos = 0;
  int32         netpos = 0;
BEGINSEQ
  smcbatyp = smcbstyp == ST_CODE ? AT_CODE : AT_ODABA;
  
  if ( fieldlist )
  {
    smcbfmcl = new fmcl((fmcb*)fieldlist,sizeof(DBFieldDef),base_info.get_count()+attr_info.get_count()+refr_info.get_count()+rshp_info.get_count());

    for (i=1; i<=base_info.get_count(); i++)
      GetEntry(i)->SetupBaseStruct(intpos,extpos,netpos,defined_align,plattform_align);
    base_info.SetPosition(intpos,extpos);
 
    for (last = i; i<last+attr_info.get_count(); i++)
    {
      fielddef = GetEntry(i);
      fielddef->SetupAttribute(intpos,extpos,netpos,defined_align,plattform_align);
      fielddef->fmcbvar = NO;
    }
    attr_info.SetPosition(intpos,extpos);

    for (last = i; i<last+refr_info.get_count(); i++)
      GetEntry(i)->SetupReference(intpos,extpos,netpos,defined_align,plattform_align);
    refr_info.SetPosition(intpos,extpos);

    for (last = i; i<last+rshp_info.get_count(); i++)
      GetEntry(i)->SetupRelation(intpos,extpos,netpos,smcbsts.stscold(),defined_align,plattform_align);
    rshp_info.SetPosition(intpos,extpos);
  }
  
  if ( SetLength(intpos,extpos,netpos) )                    ERROR

  if ( idkeynames && *idkeynames )
  {
    if ( !smcbidky )
      if ( !(smcbidky = new kcb(idkeynames,this)) )  SDBERR(95)
    smcbidky->kcbini(this,idkeynames,gvtxstb(fname,keyfieldname,ID_SIZE),
                     keyfieldname ? 1 : 0, defined_align);
  }

  SetAccess();
RECOVER

ENDSEQ
  return(this);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

DBStructDef *DBStructDef :: Setup (Dictionary *dictptr )
{
  DBStructDef *ret_strdef = this;
  DBFieldDef  *fielddef;
  int16        last;
  int16        i;
  int32         intpos = 0;
  int32         netpos = 0;
  int32         extpos = 0;
BEGINSEQ
  if ( !resource && dictptr )
    if ( !(resource = new DBResource(dictptr)) )     SDBERR(95)
  
  if ( !smcbatyp )
    smcbatyp = smcbstyp == ST_CODE ? AT_CODE : AT_ODABA;
  
  for (i=1; i<=base_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    if ( !fielddef->GetDBStruct(dictptr,schema_version) )  
//    if ( !fielddef->GetDBStruct(dictptr,fielddef->get_version()) )  
                                                     ERROR
    fielddef->SetupBaseStruct(dictptr,intpos,extpos,netpos,defined_align,plattform_align);
    if ( fielddef->GetDBStruct()->get_check_del_empty() )
      check_del_empty = YES;
    if ( fielddef->HasGUID() )
    {
      based_on_object = YES;
      if ( fielddef->get_global_identity() )
        global_identity = YES;
    }
  }
  base_info.SetPosition(intpos,extpos);
 
  for (last = i; i<last+attr_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    if ( fielddef->fmcbrlev <= 0 )
    {
      fielddef->GetDBStruct(dictptr,schema_version);
//      fielddef->GetDBStruct(dictptr,fielddef->get_version());
      fielddef->fmcbvar = NO;
    }
    fielddef->SetupAttribute(dictptr,intpos,extpos,netpos,defined_align,plattform_align);
    if ( !fielddef->fmcbityp )                      ERROR
    if ( fielddef->get_del_empty() )
      check_del_empty = YES;
  }
  attr_info.SetPosition(intpos,extpos);

  for (last = i; i<last+refr_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    fielddef->SetupReference(dictptr,intpos,extpos,netpos,defined_align,plattform_align);
    if ( fielddef->get_del_empty() )
      check_del_empty = YES;
  }
  refr_info.SetPosition(intpos,extpos);

  for (last = i; i<last+rshp_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    fielddef->SetupRelation(dictptr,intpos,extpos,netpos,smcbsts.stscold(),defined_align,plattform_align);
    if ( fielddef->get_del_empty() )
      check_del_empty = YES;
  }
  rshp_info.SetPosition(intpos,extpos);
  
  if ( SetLength(intpos,extpos,netpos) )             ERROR
  if ( SetupKeyDefs(dictptr ? dictptr->GetSystemVersion() : CUR_SYSVERSION ) )
                                                     ERROR
  
  if ( !smcbityp )
    smcbityp = ERIC;
  SetAccess();
  SetFctTable(dictptr);

RECOVER
  ret_strdef = NULL;
ENDSEQ
  return(ret_strdef);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  dictptr - Dictionary handle
\param  baselist - 
\param  attrlist - 
\param  refrlist - 
\param  rshplist - 
\param  dbklistptr - 
\param  keycount - 
\param  w_alignment - 
\param  w_resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

DBStructDef *DBStructDef :: Setup (Dictionary *dictptr, SDB_BaseStruct **baselist, SDB_Attribute **attrlist, SDB_Reference **refrlist, SDB_Relationship **rshplist, SDB_Key *dbklistptr, int16 keycount, int8 w_alignment, int32 w_resid )
{
  char         fname[ID_SIZE];
  int16        count = GetEntryCount();
  DBFieldDef  *fielddef;
  fmcb        *prev_fmcb;
  int16        indx0;
  int16        i      = 1;
  int32         intpos = 0;
  int32         netpos = 0;
  int32         extpos = 0;
  int32         offset = 0;

BEGINSEQ
//SDBEV1(smcbname,ID_SIZE)
  
  smcbatyp        = smcbstyp == ST_CODE ? AT_CODE : AT_ODABA;
  defined_align   = w_alignment       ? w_alignment 
                    : smcbityp == 151 ? 2 // SDB_IndexRef
                    : DEFAULT_ALLIGNMENT;
  
  SetFctTable(dictptr);
  if ( !count )
  { 
    plattform_align = 1;
    LEAVESEQ
  }
    
  if ( smcbfmcl )
  {
    if ( Check(dictptr,baselist,attrlist,refrlist,rshplist) )
                                                     ERROR
  }
  else
  {
    if ( !(smcbfmcl = new DBFieldList(count)) )      SDBERR(95)                                                     
//                                                   SDBCERR
  
    if ( !resource )
      if ( !(resource = new DBResource(dictptr)) )   SDBERR(95)
    resource->Initialize(NULL,w_resid);         // hier fehlt dem Initilize die Causality - zu lesen aus dem Dictionary
  
    for (indx0 = 0; indx0 < base_info.get_count(); indx0++)
    {
      fielddef = GetEntry(i++);
      fielddef->SetupBaseStruct(baselist[indx0],dictptr,intpos,extpos,netpos,defined_align,plattform_align);
      if ( fielddef->HasGUID() )
      {
        based_on_object = YES;
        if ( fielddef->get_global_identity() )
          global_identity = YES;
      }
      if ( prev_struct_def && (prev_fmcb = prev_struct_def->SearchField(fielddef->fmcbname,&offset)) )
        fielddef->set_prev_field((DBFieldDef *)prev_fmcb);
    }
    base_info.SetPosition(intpos,extpos);

    for (indx0 = 0; indx0 < attr_info.get_count(); indx0++)
    {
      fielddef = GetEntry(i++);
      fielddef->SetupAttribute(attrlist[indx0],dictptr,intpos,extpos,netpos,defined_align,plattform_align);
      if ( prev_struct_def && (prev_fmcb = prev_struct_def->SearchField(fielddef->fmcbname,&offset)) )
        fielddef->set_prev_field((DBFieldDef *)prev_fmcb);
      fielddef->fmcbvar = NO;
    }
    attr_info.SetPosition(intpos,extpos);

    for (indx0 = 0; indx0 < refr_info.get_count(); indx0++)
    {
      fielddef = GetEntry(i++);
      fielddef->SetupReference(refrlist[indx0],dictptr,intpos,extpos,netpos,defined_align,plattform_align);
      if ( prev_struct_def && (prev_fmcb = prev_struct_def->SearchField(fielddef->fmcbname,&offset)) )
        fielddef->set_prev_field((DBFieldDef *)prev_fmcb);
    }
    refr_info.SetPosition(intpos,extpos);

    for (indx0 = 0; indx0 < rshp_info.get_count(); indx0++)
    {
      fielddef = GetEntry(i++);
      fielddef->SetupRelation(rshplist[indx0],dictptr,intpos,extpos,netpos,smcbsts.stscold(),defined_align,plattform_align);
      if ( prev_struct_def && (prev_fmcb = prev_struct_def->SearchField(fielddef->fmcbname,&offset)) )
        fielddef->set_prev_field((DBFieldDef *)prev_fmcb);
    }
    rshp_info.SetPosition(intpos,extpos);
  
    SetLength(intpos,extpos,netpos);
  }
  
  if ( CreateKeyDefs(dbklistptr,keycount) )          ERROR
  if ( SetupKeyDefs(dictptr->GetSystemVersion()) )   ERROR
  SetAccess();

RECOVER

ENDSEQ
  return(this);
}

/******************************************************************************/
/**
\brief  i3 - 



\param  dictptr - Dictionary handle
\param  flistptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

DBStructDef *DBStructDef :: Setup (Dictionary *dictptr, FieldList *flistptr )
{
  int16        count = base_info.get_count() + attr_info.get_count() + refr_info.get_count() + rshp_info.get_count();
  fmcb        *fmcbptr;
  int16        indx  = 0;
  int32         posn  = 0;

BEGINSEQ
  if ( !count )
    attr_info.set_count(flistptr->GetCount());
  else
    if ( count != flistptr->GetCount() )             SDBERR(99)
  smcbfmcl = flistptr;
  
  if ( !resource )
    if ( !(resource = new DBResource(dictptr)) )     SDBERR(95)
  
  while ( fmcbptr = flistptr->GetEntry(++indx) )
  {
    fmcbptr->fmcbesu(dictptr->GetStructDef(fmcbptr->fmcbtype,fmcbptr->fmcbnsid),posn,defined_align,plattform_align);
    posn = fmcbptr->fmcbposn + fmcbptr->fmcbbyte;
  }
  smcb::SetLength(posn);
  
  if ( !smcbityp )
    smcbityp = TEMPSID;
  
  SetAccess();
RECOVER

ENDSEQ
  return(this);
}

/******************************************************************************/
/**
\brief  i4 - 



\param  dictptr - Dictionary handle
\param  enum_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

DBStructDef *DBStructDef :: Setup (Dictionary *dictptr, ENUM_ValueList *enum_list )
{
  DBFieldList     *fieldlist = NULL;
  DBExtend        *extdef    = NULL;
  int32            indx0     = 0;
  SetEnumFieldList(dictptr);
  
  smcbacc = enum_list;




  return(this);
}

/******************************************************************************/
/**
\brief  SetupClient - 



\return dbstr_ptr - 

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupClient"

DBStructDef *DBStructDef :: SetupClient (Dictionary *dictptr )
{
  DBStructDef *ret_strdef = this;
  DBFieldDef  *fielddef;
  int16        last;
  int16        i;
  int32         intpos = 0;
  int32         netpos = 0;
  int32         extpos = 0;
BEGINSEQ
  if ( !resource )
    if ( !(resource = new DBResource(dictptr)) )     SDBERR(95)
  
  if ( !smcbatyp )
    smcbatyp = smcbstyp == ST_CODE ? AT_CODE : AT_ODABA;
  
  for (i=1; i<=base_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    if ( !fielddef->GetDBStruct(dictptr,schema_version) )  
                                                     ERROR
    fielddef->SetupBaseStruct(intpos,extpos,netpos,defined_align,plattform_align);
    if ( fielddef->HasGUID() )
    {
      based_on_object = YES;
      if ( fielddef->get_global_identity() )
        global_identity = YES;
    }
  }
  base_info.SetPosition(intpos,extpos);
 
  for (last = i; i<last+attr_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    if ( fielddef->fmcbrlev <= 0 )
    {
      fielddef->GetDBStruct(dictptr,schema_version);
      if ( !fielddef->fmcbityp )                      ERROR
      fielddef->fmcbvar = NO;
    }
    fielddef->SetupAttribute(intpos,extpos,netpos,defined_align,plattform_align);
  }
  attr_info.SetPosition(intpos,extpos);

  for (last = i; i<last+refr_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    fielddef->SetupReference(intpos,extpos,netpos,defined_align,plattform_align);
  }
  refr_info.SetPosition(intpos,extpos);

  for (last = i; i<last+rshp_info.get_count(); i++)
  {
    fielddef = GetEntry(i);
    fielddef->SetupRelation(intpos,extpos,netpos,smcbsts.stscold(),defined_align,plattform_align);
  }
  rshp_info.SetPosition(intpos,extpos);
  
  if ( SetLength(intpos,extpos,netpos) )             ERROR
  if ( SetupKeyDefs(dictptr->GetSystemVersion()) )
                                                     ERROR
  
  if ( !smcbityp )
    smcbityp = TEMPSID;
  SetAccess();
  SetFctTable(dictptr);

RECOVER
  ret_strdef = NULL;
ENDSEQ
  return(ret_strdef);
}

/******************************************************************************/
/**
\brief  SetupCounts - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCounts"

void DBStructDef :: SetupCounts ( )
{
  DBFieldDef               *fielddef;
  int32                     indx = 0;
  int32                     base_count = 0;
  int32                     refr_count = 0;
  int32                     attr_count = 0;

// updates the counts for ACOperation structures (no relationships)

  while ( fielddef = GetEntry(++indx) )
  {
    if ( fielddef->fmcbbstr )
      base_count++;
    else if ( fielddef->fmcbrlev == R_REFR )
      refr_count++;
    else
      attr_count++;
  }

  base_info.set_count(base_count);
  refr_info.set_count(refr_count);
  attr_info.set_count(attr_count);
  rshp_info.set_count(0);


}

/******************************************************************************/
/**
\brief  SetupKeyDefs - 



\return term - Termination code

\param  sys_version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupKeyDefs"

logical DBStructDef :: SetupKeyDefs (uint16 sys_version )
{
  kcb                    *kcbptr = NULL;  
  logical                 term = NO;
  smcbskey->GoTop();
  while ( kcbptr = smcbskey->GetNext() )
    if ( !kcbptr->scbsmcb->GetLength() )
      kcbptr->kcbini(this,kcbptr->scbsmcb->smcbname,NULL,
                     kcbptr->scbsmcb->smcbfmcl ? kcbptr->scbsmcb->smcbfmcl->GetCount() : 0,
                     sys_version < 3 ? 1 : defined_align);

  return(term);
}

/******************************************************************************/
/**
\brief  SetupViewOrder - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupViewOrder"

logical DBStructDef :: SetupViewOrder (binti *bintiptr )
{
  DBFieldDef     *dbflddef;
  node          *nodeptr = NULL;
  int16           count = attr_info.get_count();
  int16           index = 0;
  logical         term = NO;
BEGINSEQ
  bintiptr->get_node_attr().GoTop();
  while ( index < count )
  {
    dbflddef = GetEntry(++index);
    nodeptr  = bintiptr->get_node_attr().GetNext();
    
    if ( nodeptr->IsCollection() )
      dbflddef->ChangeTopIndex(Bnodeptr->get_sk_index());
  }
  
  smcbskey->RemoveTail();  // geht nur, wenn IDKey einziger Schlüssel. besser Funktion in smcb
  delete smcbidky;
  if ( !(smcbidky = new kcb("VIEW_KEY",this)) )      SDBERR(95)
  if ( CreateKeyDefs(smcbidky) )                     ERROR
  if ( SetupKeyDefs(CUR_SYSVERSION) )                ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  get_attr_info - 



\return attrinfo - Information about attributes

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_attr_info"

MemberInfo &DBStructDef :: get_attr_info ( )
{


  return(attr_info);
}

/******************************************************************************/
/**
\brief  get_base_info - 



\return baseinfo - Information about base structures

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_base_info"

MemberInfo &DBStructDef :: get_base_info ( )
{


  return(base_info);
}

/******************************************************************************/
/**
\brief  get_check_del_empty - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_check_del_empty"

logical DBStructDef :: get_check_del_empty ( )
{

  return(this ? check_del_empty : NO);

}

/******************************************************************************/
/**
\brief  get_from - 



\return from_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_from"

DLL(DBViewPath) *DBStructDef :: get_from ( )
{

  return ( view_struct ? &view_struct->get_from() : NULL);

}

/******************************************************************************/
/**
\brief  get_having - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_having"

char *DBStructDef :: get_having ( )
{

  return ( view_struct ? view_struct->get_where() : NULL);

}

/******************************************************************************/
/**
\brief  get_net_length - 



\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_net_length"

uint32 DBStructDef :: get_net_length ( )
{

  return(net_length);

}

/******************************************************************************/
/**
\brief  get_refr_info - 



\return refrinfo - Information about references

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_refr_info"

MemberInfo &DBStructDef :: get_refr_info ( )
{


  return(refr_info);
}

/******************************************************************************/
/**
\brief  get_rshp_info - 



\return rshpinfo - Information about relationships

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_rshp_info"

MemberInfo &DBStructDef :: get_rshp_info ( )
{


  return(rshp_info);
}

/******************************************************************************/
/**
\brief  get_sb_number - 



\return sbnumber - SubBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_sb_number"

int16 DBStructDef :: get_sb_number ( )
{


  return(sb_number);
}

/******************************************************************************/
/**
\brief  get_schema_ver - 



\return schemaversion - Scheme version

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_schema_ver"

int16 DBStructDef :: get_schema_ver ( )
{


  return(schema_version);
}

/******************************************************************************/
/**
\brief  get_where - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_where"

char *DBStructDef :: get_where ( )
{

  return ( view_struct ? view_struct->get_where() : NULL);

}

/******************************************************************************/
/**
\brief  set_global_identity - 




\param  glob_identity - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_global_identity"

void DBStructDef :: set_global_identity (logical glob_identity )
{

  global_identity = glob_identity;

}

/******************************************************************************/
/**
\brief  set_prev_struct - 




\param  dbstrdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_prev_struct"

void DBStructDef :: set_prev_struct (DBStructDef *dbstrdef )
{

  prev_struct_def = dbstrdef;

}

/******************************************************************************/
/**
\brief  set_resource - 




\param  resptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_resource"

void DBStructDef :: set_resource (DBResource *resptr )
{

  if ( resource && resource != resptr )
    delete resource;
  resource = resptr;

}

/******************************************************************************/
/**
\brief  set_schema_vers - 




\param  schema_vers - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_schema_vers"

void DBStructDef :: set_schema_vers (uint16 schema_vers )
{

  schema_version = schema_vers;

}

/******************************************************************************/
/**
\brief  set_view_struct - 




\param  vstruct - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_view_struct"

void DBStructDef :: set_view_struct (DBViewStructDef *vstruct )
{

  if ( view_struct )
    delete view_struct;

  view_struct = vstruct;

}

/******************************************************************************/
/**
\brief  xCreateViewNodes - 



\return term - Termination code

\param  acnodeptr - 
\param  bintiptr - 
\param  instptr - 
\param  high_node - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xCreateViewNodes"

logical DBStructDef :: xCreateViewNodes (ACNode *acnodeptr, binti *bintiptr, void *instptr, node *high_node, logical init_nodes )
{
  LACObject      *lobhandle = acnodeptr->GetObjectHandle()->GetLocalACObject();
  DBFieldDef     *dbflddef;
  node           *nodeptr = NULL;
  node           *nextnode = NULL;
  ACExtend       *sysnode;
  int16           count = attr_info.get_count();
  int16           index = 0;
  logical         term = NO;
BEGINSEQ
  while ( index < count )
  {
    dbflddef = GetEntry(++index);
    if ( dbflddef->get_static() )     // operand in Product set
    {
      if ( nodeptr )
        bintiptr->get_node_refr().AddTail(nodeptr);
      
      if ( high_node )
      {
        if ( !memcmp(dbflddef->fmcbname,"__local_view     ",16) )
          nodeptr = high_node;
        else if ( !(nodeptr = high_node->GetPropNode(dbflddef->fmcbname,(CTX_Property *)NULL)) || 
                  !nodeptr->IsCollection() )         SDBERR(234)
        nodeptr = (ACNode *)nodeptr->CreateCopyNode();
      }
      else
      {
        if ( !(sysnode = lobhandle->ProvideACExtend(dbflddef->fmcbname,
                                         acnodeptr->get_nodeacc(),acnodeptr->get_nodeacc() > PI_Read)) )
                                                      ERROR
        if ( !(nodeptr = new ACTopNode(sysnode,acnodeptr->get_nodeacc(),
                                       !dbflddef->get_weak_typed() ? ((char *)instptr)+dbflddef->fmcbposn : NULL)) )
                                                     SDBERR(95)
                                                     SDBCERR
      }
      if ( dbflddef->get_weak_typed() )
        if ( !(nodeptr = new ACTransientReference(nodeptr)) )
                                                     ERROR
      if ( nodeptr->Init(((char *)instptr)+dbflddef->fmcbposn) )
                                                     ERROR
      bintiptr->get_node_base().AddTail(nodeptr);
    }
    else
    {
      if ( !nodeptr )                                SDBERR(99)
      
      if ( !(nextnode = nodeptr->GetPropNode(dbflddef->fmcbname,(CTX_Property *)NULL)) || 
           !nextnode->IsCollection() )               SDBERR(234)
      if ( nextnode->Init(((char *)instptr)+dbflddef->fmcbposn) )
                                                     ERROR
      nodeptr = nextnode;
    }
    nodeptr->stsstrans();  
    if ( index > 1 )      
      nodeptr->stssold();  
    bintiptr->get_node_attr().AddTail(nodeptr);
  }

  if ( nodeptr )
    bintiptr->get_node_refr().AddTail(nodeptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~DBStructDef - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBStructDef"

     DBStructDef :: ~DBStructDef ( )
{
  OPFunctionDecl *fct_decl = NULL; 
  DBFieldDef     *flddef   = NULL;
  int16           expr_cnt = 0;
  int16           indx     = 0;
  delete undef_members;
  undef_members = NULL;
  
  delete v5_strdef;
  v5_strdef = NULL;
  
  delete view_struct;
  view_struct = NULL;
  
  if ( expression_list )
  {
    expr_cnt = expression_list->GetSize();
    while ( expr_cnt-- )
    {
      (*expression_list)[expr_cnt]->Set_OPName(NULL);
      delete (*expression_list)[expr_cnt];
    }
    delete expression_list;
    expression_list = NULL;
  }
  
  if ( function_list )
  {
    while ( fct_decl = function_list->RemoveTail() )
      delete fct_decl;
    delete function_list;
    function_list = NULL;
  }
        
  delete prev_struct_def;
  prev_struct_def = NULL;
  
  if ( smcbstyp == ST_CODE )
  {
    smcbidky = NULL;
    smcbskey = NULL;
    smcbfmcl = NULL;
  }
  else
  {
    while ( flddef = GetEntry(++indx) )
      flddef->Release();
    delete (DBFieldList *)smcbfmcl;
    smcbfmcl = NULL;
  }
  
  delete resource;
  resource = NULL;
  
  if ( (acc *)this == smcbacc  || smcbstyp == ST_CODE )
    smcbacc = NULL;

  delete ext_area;
  ext_area = NULL;

}


