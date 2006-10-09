/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBFieldDef

\brief    Definition for the internal presentation of property data
          The  internal property  definition contains  all information available
          and  necessary accessing data of the property. Among basic information
          such  as type and  size it contains  special ODABA2 access information
          such as index and base collection definitions.
          Alls  these information are used for  reading and writing data just as
          to execute operations on properties.

\date     $Date: 2006/08/30 13:36:13,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBFieldDef"

#include  <gentyps.h>
#include  <popa7.h>
#include  <ctype.h>
#include  <cwinsock.h>
#include  <idbd.h>
#ifndef   DLL_DBIndex_HPP
#define   DLL_DBIndex_HPP
#include  <sDBIndex.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_FieldSource_HPP
#define   DLL_FieldSource_HPP
#include  <sFieldSource.hpp>
#include  <sDLL.h>
#endif
#include  <cADT_Types.h>
#include  <sACObject.hpp>
#include  <sACStructure.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCAU_simpleAction.hpp>
#include  <sDBExtend.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Number.hpp>
#include  <sExpressionReference.hpp>
#include  <sFieldSource.hpp>
#include  <sLACObject.hpp>
#include  <iNetConversion.h>
#include  <sODC_Function.hpp>
#include  <sODC_Variable.hpp>
#include  <sSDB_Attribute.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Index.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Property.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#include  <sSDB_ViewSource.hpp>
#include  <scvb.hpp>
#include  <sexd.hpp>
#include  <smvlp.hpp>
#include  <sref.hpp>
#include  <srefp.hpp>
#include  <ssmcb.hpp>
#include  <sDBFieldDef.hpp>


/******************************************************************************/
/**
\brief  CanReference - 



\return cond - 

\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanReference"

logical DBFieldDef :: CanReference (DBFieldDef *fielddef )
{
  logical          cond = YES;
BEGINSEQ
  if ( fmcbrlev == fielddef->fmcbrlev )              LEAVESEQ
  
  if ( fmcbrlev != R_DIRECT || fmcbrlev != R_GENERIC 
                            || fmcbrlev != R_REFR  ) ERROR
  if ( fielddef->fmcbrlev != R_DIRECT || fielddef->fmcbrlev != R_GENERIC 
                                      || fielddef->fmcbrlev != R_REFR   ) 
                                                     ERROR
  if ( (fmcbdim != 1 && fielddef->fmcbdim != 1) ||
       (fmcbdim == 1 && fielddef->fmcbdim == 1)   )  LEAVESEQ
  
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ChangeTopIndex - 



\return term - Termination code

\param  dbindex_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeTopIndex"

logical DBFieldDef :: ChangeTopIndex (DBIndex *dbindex_ptr )
{
  DBIndex      *index_def;
  logical       term = NO;
BEGINSEQ
  ILock(YES);
  if ( !dbindex_ptr )                                LEAVESEQ
  
  if ( !index_list )
    index_list = new DBIndexList();  
    
  if ( (index_def = index_list->GetHead()) &&
       index_def->get_key_def() == dbindex_ptr->get_key_def() )
                                                   LEAVESEQ
  
  if ( CreateIndex(dbindex_ptr) )                  ERROR

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDescription - 



\return term - Termination code

\param  dbfield_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDescription"

logical DBFieldDef :: CopyDescription (DBFieldDef &dbfield_ref )
{
  DBIndexList           *idx_list  = index_list;
  DBResource            *dbres     = resource;
  char                  *ext       = extend;
  ExpressionReference   *ival      = initval;
  ExpressionReference   *cnstr     = constraint;
  DLL(FieldSource)      *srce_list = sources;
  DLL(char)             *syn_list  = fmcbsyns;
  logical                term      = NO;
  RemoveSynonyms();
  
  memcpy(this,&dbfield_ref,sizeof(DBFieldDef));

  if ( fmcbsyns )
  {
    fmcbsyns = NULL;
    CopySynonyms(dbfield_ref.fmcbsyns);
  }
  
  if ( ext )
    delete ext;
  if ( extend )
  {
    extend = NULL;
    SetExtent((char *)dbfield_ref.get_extend());
  }
  
  if ( ival )
    delete ival;
  if ( initval )
  {
    initval = NULL;
    set_initval(dbfield_ref.initval);
  }
  
  if ( cnstr )
    delete cnstr;
  if ( constraint )
  {
    constraint = NULL;
    set_constraint(dbfield_ref.get_constraint());
  }
  
  if ( index_list )         // kopierte index liste
    index_list->Reserve();
    
  if ( idx_list )
    idx_list->Release();
  
  sources = srce_list;      // werden nicht uebernommen, solange nicht einer es braucht
  RemoveSourceList();
    
  if ( dbres )
    delete dbres;
  resource = new DBResource(NULL);  // da fehlt noch ein richtiger Copy Konstruktor
  resource_lock = NULL;

  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtField_dtd - 



\return term - Termination code

\param  srce_flddef - 
\param  targfld - 
\param  srcefld - 
\param  tlen - 
\param  slen - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtField_dtd"

logical DBFieldDef :: CopyExtField_dtd (DBFieldDef *srce_flddef, void *targfld, void *srcefld, int32 tlen, int32 slen, logical pif )
{
  logical   pif_conv = NO;
  int64     bval;
  char     *cval = (char *)&bval;
  char     *source;
  char     *target;
  logical   term     = NO;
BEGINSEQ
  source = (char *)srcefld;
  if ( srce_flddef->IsEnumerator() )
  {
    memcpy(cval,srcefld,2); // codeset values are codes externally in two bytes,
    *(int32 *)cval = *(int16 *)cval;
    source = cval;
    pif_conv = pif;
  }
  else if ( srce_flddef->IsInteger() || srce_flddef->fmcbityp == T_REAL )
  {
    memcpy(cval,srcefld,slen);
    source = cval;
    pif_conv = pif && srce_flddef->fmcbityp != T_REAL;
  }
  if ( pif_conv )
    srce_flddef->ConvertIFromNet(cval,cval);
  
  target = (char *)targfld;
  pif_conv = NO;
  if ( IsInteger() || IsEnumerator() || fmcbityp == T_REAL )
  {
    target = cval;
    pif_conv = pif && fmcbityp != T_REAL;
  }
  
  if ( cvb(srce_flddef,this,source,target).cvbconv() )  ERROR
  
  if ( pif_conv )
    ConvertIToNet(cval,cval);
  if ( IsEnumerator() )
  {
    *(int16 *)cval = *(int32 *)cval;
    memcpy(targfld,cval,2); 
  }
  else if ( IsInteger() || fmcbityp == T_REAL)
    memcpy(targfld,cval,tlen);

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
\param  targ_inst - 
\param  srce_flddef - 
\param  srce_inst - 
\param  p_update - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtInst"

logical DBFieldDef :: CopyExtInst (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst, logical *p_update, logical pif )
{
  logical                 term = NO;
BEGINSEQ
  if ( fmcbtrans || srce_flddef->get_transient() )    LEAVESEQ

  switch ( (fmcbrlev == R_REFR || fmcbrlev == R_GENERIC) + 2*(srce_flddef->fmcbrlev == R_REFR  || srce_flddef->fmcbrlev == R_GENERIC) )
  {
    case 0 : term = CopyExtInst_dtd(lobhandle,targ_inst,srce_flddef,srce_inst,p_update,pif);
             break;
    case 1 : term = CopyExtInst_dtr(lobhandle,targ_inst,srce_flddef,srce_inst);
             *p_update = YES;
             break;
    case 2 : term = CopyExtInst_rtd(lobhandle,targ_inst,srce_flddef,srce_inst);
             break;
    case 3 : term = CopyExtInst_rtr(lobhandle,targ_inst,srce_flddef,srce_inst,pif);
             break;
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtInst_dtd - 



\return term - Termination code

\param  lobhandle - 
\param  targ_inst - 
\param  srce_flddef - 
\param  srce_inst - 
\param  p_update - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtInst_dtd"

logical DBFieldDef :: CopyExtInst_dtd (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst, logical *p_update, logical pif )
{
  logical   srcebase;
  logical   targbase;
  short     tdim  = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  short     sdim  = srce_flddef->fmcbrlev == R_GENERIC ? 1 : srce_flddef->fmcbdim;
  short     dim   = MIN(tdim,sdim);
  ushort    tlen  = tdim ? fmcbbyte/tdim : 0;
  ushort    slen  = sdim ? srce_flddef->fmcbbyte/sdim : 0;
  char     *sinst;
  char     *tinst;
  int32     i;
  logical   term     = NO;
BEGINSEQ
  if ( fmcbrlev != srce_flddef->fmcbrlev )              ERROR
  if ( !dim )                                        LEAVESEQ    
  
  if ( !fmcbityp && fmcbsmcb )
    fmcbityp = fmcbsmcb->smcbityp;
  if ( !srce_flddef->fmcbityp && srce_flddef->fmcbsmcb )
    srce_flddef->fmcbityp = srce_flddef->fmcbsmcb->smcbityp;
  
  srcebase = srce_flddef->fmcbbase();
  targbase = fmcbbase();
  
  if ( fmcbrlev > 0                       ||
       (srcebase && targbase && tlen == slen && 
        fmcbprec == srce_flddef->fmcbprec &&
        fmcbityp == srce_flddef->fmcbityp   )   )
    memcpy(targ_inst,srce_inst,MIN(fmcbbyte,srce_flddef->fmcbbyte));
  else for ( i = 0, sinst = srce_inst, tinst = targ_inst; 
             i < dim; 
             i++, sinst += slen, tinst += tlen)
    switch ( srcebase + targbase )
    {
      case 0  : switch ( (privilege == PI_Share) + 2*(srce_flddef->get_privilege() == PI_Share) )
                {
                  case 0 : if ( srce_flddef->fmcbsmcb && srce_flddef->fmcbsmcb->smcbstyp == ST_CODE )
                             memcpy(tinst,sinst,ext_length);
                           else
                           {
                             memcpy(srce_flddef->GetDBStruct()->get_ext_area(),sinst,srce_flddef->GetDBStruct()->get_ext_length());
                             term = GetDBStruct()->CopyExtInst(lobhandle,srce_flddef->GetDBStruct(),p_update);
                             memcpy(tinst,GetDBStruct()->get_ext_area(),GetDBStruct()->get_ext_length());
                           }
                           break;
                  case 1 : term = CopyExtInst_dtr(lobhandle,tinst,srce_flddef,sinst);
                           *p_update = YES;
                           break;
                  case 2 : term = CopyExtInst_rtd(lobhandle,tinst,srce_flddef,sinst);
                           break;
                  case 3 : term = CopyExtInst_rtr(lobhandle,tinst,srce_flddef,sinst,pif);
                           break;
                }
                break;
      case 1  : if ( !DTConversion(srce_flddef,tinst,sinst) )
                  break;
      case 2  : CopyExtField_dtd(srce_flddef,tinst,sinst,tlen,slen,pif);
                break;
      default : ;
    }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtInst_dtr - 



\return term - Termination code

\param  lobhandle - 
\param  targ_inst - 
\param  srce_flddef - 
\param  srce_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtInst_dtr"

logical DBFieldDef :: CopyExtInst_dtr (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst )
{
  ACStructure  *struct_access;
  exd          *exd_area;
  DBIndex      *idxptr;
  logical       term = NO;
BEGINSEQ
  if ( fmcbityp == srce_flddef->fmcbityp )  // gleich Struktur
  {
    if ( !(struct_access = (ACStructure *)lobhandle->GetStructAccess(fmcbityp)) )
                                                     SDBERR(99)
    if ( !(exd_area = struct_access->CreateEXD(srce_inst,srce_flddef->GetDBStruct()->get_ext_length(),
                                                srce_flddef->GetDBStruct()->get_schema_ver())) )
                                                     ERROR
    idxptr = index_list->GetHead();
    exd_area->ReserveInstance(NULL);
    
    if ( fmcbbstr ||                       // base structure
         (fmcbdim == 1 && !update) )       // refx
      *(EB_Number *)targ_inst = exd_area->get_exdebsn();
    else if ( fmcbdim == 1 && !update )    // refp
    {
      refp    loc_ref(lobhandle,(EB_Number *)targ_inst,UNDEF,idxptr,NO);
      loc_ref.AddExt(exd_area->get_exdebsn(),NULL,AUTO);
    }
    else if ( !*idxptr->GetKeyName() )     // mvlp
    {
      mvlp    loc_ref(lobhandle,(EB_Number *)targ_inst,UNDEF,IDB_MVLP,MVLP_OLN,AUTO,idxptr,NO);
      loc_ref.AddExt(exd_area->get_exdebsn(),NULL,AUTO);
    }
    
    exd_area->ReleaseInstance(NULL);
    LEAVESEQ
  }
  
  SDBSET(999)         // 2.4.00; sonst gehts nicht weiter
  SDBRESET
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtInst_rtd - 



\return term - Termination code

\param  lobhandle - 
\param  targ_inst - 
\param  srce_flddef - 
\param  srce_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtInst_rtd"

logical DBFieldDef :: CopyExtInst_rtd (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst )
{
  logical                 term = NO;
  SDBSET(999)         // 2.4.00; sonst gehts nicht weiter
  SDBRESET
  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtInst_rtr - 



\return term - Termination code

\param  lobhandle - 
\param  targ_inst - 
\param  srce_flddef - 
\param  srce_inst - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtInst_rtr"

logical DBFieldDef :: CopyExtInst_rtr (LACObject *lobhandle, char *targ_inst, DBFieldDef *srce_flddef, char *srce_inst, logical pif )
{
  logical                 term = NO;
  if ( srce_flddef->ext_length == 4 && ext_length == 8)  // V5 instance
    *(uint64 *)targ_inst = BigToPIF(PIFToLong(*(int32 *)srce_inst,pif),pif);
  else
    memcpy(targ_inst,srce_inst,sizeof(EB_Number));
  return(term);
}

/******************************************************************************/
/**
\brief  CopyTopIndex - 



\return term - Termination code

\param  flddefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyTopIndex"

logical DBFieldDef :: CopyTopIndex (DBFieldDef *flddefptr )
{
  DBIndex    *dbindex;
  logical     term = NO;
BEGINSEQ
  ILock(YES);
  if ( !index_list )
    index_list = new DBIndexList();  
    
  flddefptr->get_index_list()->GoTop();
  while ( dbindex = flddefptr->get_index_list()->GetNext() )
    if ( !dbindex->get_temporary() )
    {
      if ( CreateIndex(dbindex) )                    ERROR
      break;
    }  
    
  if ( index_list->GetCount() == 0 )
    if ( CreateIndex() )                             ERROR
    
          

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CreateIndex - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dictptr - Dictionary handle
\param  dbiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndex"

logical DBFieldDef :: CreateIndex (Dictionary *dictptr, SDB_Index *dbiptr )
{
  DBIndex    *index_def;
  kcb        *kcbptr = NULL;
  logical     term   = NO;
BEGINSEQ
  if ( *dbiptr->get_skdname() && *dbiptr->get_skdname() != ' ' )
  {
    SDBEV3(dbiptr->get_skdname(),16)
    if ( dictptr )
      kcbptr = GetDBStruct(dictptr)->GetKCB(dbiptr->get_skdname());
    else  
      if ( !(kcbptr = fmcbsmcb->GetKCB(dbiptr->get_skdname())) )
      {
//        if ( fmcbsmcb->smcbityp )                    SDBERR(75)
        if ( !(kcbptr = new kcb(dbiptr->get_skdname(),fmcbsmcb)) )   
                                                     SDBERR(95)
      }
  }  
  
  if ( !(index_def = new DBIndex(kcbptr,this,dbiptr)) )  
                                                     SDBERR(95)
                                                     SDBCERR
  ILock(YES);
  if ( index_list )
    index_list->AddTail(index_def);
  IUnlock();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  key_names - 
\param  uniopt - 
\param  tempopt - 
\param  caseopt - 
\param  empopt - 
\param  settyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndex"

logical DBFieldDef :: CreateIndex (char *key_names, logical uniopt, logical tempopt, logical caseopt, logical empopt, SDB_SET settyp )
{
  DBIndex    *index_def;
  kcb        *kcbptr = NULL;
  logical     idkey_opt = NO;
  logical     term      = NO;
BEGINSEQ
  ILock(YES);
  
  if ( !(index_def = new DBIndex(key_names,uniopt,tempopt,caseopt,empopt,fmcbdim,settyp,idkey_opt)) )
                                                     SDBERR(95)
  index_def->set_field_def(this);
  
  if ( !index_list )
    if ( !(index_list = new DBIndexList()) )         SDBERR(95)
  
  index_list->AddTail(index_def);

  if ( fmcbsmcb )
    index_def->Setup();
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  i04 - 



\param  ph - 
\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndex"

logical DBFieldDef :: CreateIndex (PropertyHandle &ph, Dictionary *dictptr )
{
  DBIndex    *index_def;
  char       *skdname;
  kcb        *kcbptr = NULL;
  logical     term   = NO;
BEGINSEQ
  skdname = ph.GetArea("skdname");
  if ( skdname && *skdname != ' ' )
  {
    SDBEV3(skdname,ID_SIZE)
    if ( dictptr )
      kcbptr = GetDBStruct(dictptr)->GetKCB(skdname);
    else  
      if ( !(kcbptr = fmcbsmcb->GetKCB(skdname)) )
      {
        if ( !(kcbptr = new kcb(skdname,fmcbsmcb)) ) SDBERR(95)
      }
  }  
  
  if ( !(index_def = new DBIndex(kcbptr,this,ph)) )  SDBERR(95)
                                                     SDBCERR
  ILock(YES);
  if ( index_list )
    index_list->AddTail(index_def);
  IUnlock();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndex"

logical DBFieldDef :: CreateIndex ( )
{
  DBIndex    *index_def;
  logical     idkey_opt = NO;
  logical     term      = NO;
BEGINSEQ
  ILock(YES);
  if ( get_extend() && fmcbdim == 1 )
    idkey_opt = YES;
  
  if ( !(index_def = new DBIndex((kcb *)NULL,YES,NO,YES,NO,fmcbdim,SET_SMAL,idkey_opt)) )
                                                     SDBERR(95)
  index_def->set_field_def(this);
  
  if ( !index_list )
    if ( !(index_list = new DBIndexList()) )         SDBERR(95)
  
  if ( index_list )
    index_list->AddTail(index_def);

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  indxdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndex"

logical DBFieldDef :: CreateIndex (DBIndex *indxdef )
{
  DBIndex    *index_def;
  logical     term = NO;
BEGINSEQ
  ILock(YES);
  if ( !(index_def = new DBIndex(*indxdef)) )        SDBERR(95)
  
  index_def->set_field_def(this);
  index_list->AddHead(index_def);

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CreateIndexList - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dictptr - Dictionary handle
\param  dbrptr - ODABA2 reference definition
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndexList"

logical DBFieldDef :: CreateIndexList (Dictionary *dictptr, SDB_Reference *dbrptr, logical crt_opt )
{
  SDB_Index  *sdb_index;
  int32        indx0  = 0;
  logical     term   = NO;
BEGINSEQ
  while ( sdb_index = dbrptr->get_ddeindx()(indx0++) )
    if ( CreateIndex(dictptr,sdb_index) )            ERROR
  
  if ( crt_opt )
  {
    ILock(YES);
    if ( index_list->GetCount() == 0 )
      term = CreateIndex();
    IUnlock();
    if ( term )                                      ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  ph - 
\param  dictptr - Dictionary handle
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndexList"

logical DBFieldDef :: CreateIndexList (PropertyHandle &ph, Dictionary *dictptr, logical crt_opt )
{
  int32        indx0  = 0;
  logical     term   = NO;
BEGINSEQ
  PH(&ph,ddeindx);
  while ( ddeindx(indx0++) )
    if ( CreateIndex(ddeindx,dictptr) )             ERROR
  
  if ( crt_opt )
  {
    ILock(YES);
    if ( index_list->GetCount() == 0 )
      term = CreateIndex();
    IUnlock();
    if ( term )                                      ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbilistptr - 
\param  dbicount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateIndexList"

logical DBFieldDef :: CreateIndexList (SDB_Index *dbilistptr, int16 dbicount )
{
  logical                 term = NO;
BEGINSEQ
  if ( dbicount > 1 )
    multikey = YES;
  
  while ( dbicount-- )
    if ( CreateIndex(NULL,dbilistptr++) )            ERROR
  
  ILock(YES);
  if ( index_list->GetCount() == 0 )
    term = CreateIndex();
  IUnlock();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSourceList - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbmptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSourceList"

logical DBFieldDef :: CreateSourceList (SDB_Member *dbmptr )
{
  SDB_ViewSource    *vsource;
  int32              indx0 = 0;
  logical            term = NO;
BEGINSEQ
  if ( dbmptr->get_source().GetCount() <= 0 )        LEAVESEQ

  if ( !sources )
    sources = new DLL(FieldSource);
    
  while ( vsource = dbmptr->get_source().Get(indx0++) )
    sources->AddTail(new FieldSource(vsource->get_path().GetString(),
                                     vsource->get_order()));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  init_string - 
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSourceList"

logical DBFieldDef :: CreateSourceList (char *init_string, int32 string_len )
{
  FieldSource      *fsource;
  if ( !sources )
    sources = new DLL(FieldSource);
    
  fsource = new FieldSource();
  SetExpressionRef((ExpressionReference **)&fsource,init_string,string_len);
  sources->AddTail(fsource);

  return(NO);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSourceList"

logical DBFieldDef :: CreateSourceList (PropertyHandle &ph )
{
  int32              indx0 = 0;
  logical            term = NO;
BEGINSEQ
  PH(&ph,source);
  if ( source.GetCount() <= 0 )                      LEAVESEQ

  if ( !sources )
    sources = new DLL(FieldSource);
    
  while ( source.Get(indx0++) )
    sources->AddTail(new FieldSource(source.GetString("path"),
                                     source.GetArea("order")));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSynonymList - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbmptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSynonymList"

logical DBFieldDef :: CreateSynonymList (SDB_Member *dbmptr )
{
  int32              indx0 = 0;
  logical            term = NO;
BEGINSEQ
  if ( dbmptr->get_synonyms().GetCount() <= 0 )        LEAVESEQ

  while ( dbmptr->get_synonyms().Get(indx0++) )
    AddSynonym(dbmptr->get_synonyms().GetString("sys_ident"));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSynonymList"

logical DBFieldDef :: CreateSynonymList (PropertyHandle &ph )
{
  int32              indx0 = 0;
  logical            term = NO;
BEGINSEQ
  PH(&ph,synonyms)
  if ( synonyms.GetCount() <= 0 )                    LEAVESEQ

  while ( synonyms.Get(indx0++) )
    AddSynonym(synonyms.GetString("sys_ident"));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateViewSource - 



\return term - Termination code

\param  bnf_data - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateViewSource"

logical DBFieldDef :: CreateViewSource (BNFData *bnf_data )
{
  char              *string;
  logical            term = NO;
BEGINSEQ
  if ( string = bnf_data->StringValue() )            LEAVESEQ

  if ( !sources )
    sources = new DLL(FieldSource);
    
  sources->AddTail(new FieldSource(string,NULL));
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBFieldDef - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  fldnames - Property name
\param  fldtypes - Property type
\param  fldnsid - 
\param  fldreflev - Property reference level
\param  fldsize - Size of property
\param  fldprec - Precision of property
\param  flddim - Dimension of property
\param  smcbptr - Pointer to general structure definition
\param  gentype - Generic type of property
\param  secrefr - Property is secundary referenced
\param  extnames - Extent name
\param  irefname - Name of inverse property
\param  indexptr - Index definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldDef"

     DBFieldDef :: DBFieldDef (char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim, smcb *smcbptr, char *gentype, logical secrefr, char *extnames, char *irefname, DBIndex *indexptr )
                     : FieldDef(fldnames,fldtypes,fldnsid,fldreflev,fldsize,
         fldprec,flddim),
  index_list(new DBIndexList()),
  offset_ext(UNDEF),
  ext_length(UNDEF), 
  inverse_field(NULL),
  cluster_opt(NO),
  mb_number(AUTO),
  meta_field(MAT_undefined),
  privilege(extnames && *extnames > ' ' ?
            PI_Share : PI_Exclusive), 
  static_field(NO),
  virtual_field(NO), 
  dominant(YES),
  sec_reference(secrefr), 
  log_reference(NO),
  version(0),
  create(YES),
  owning(NO),
  week_typed(NO),
  update(NO),
  multikey(NO),
  depend(NO),
  initval(NULL),
  resource(NULL),
  clustered_table(NO),
  extend(NULL),
  is_base_coll(AUTO),
  resource_lock(NULL),
  prev_field(NULL),
  global_identity(NO),
  set_operation(NO),
  by_reference(NO),
  del_empty(NO),
  shared(NO),
  constraint(NULL),
  sources(NULL)

{

BEGINSEQ
  fmcbopt = YES;
  gvtxstb(gen_type,gentype ? gentype : "",sizeof(gen_type));

  if ( !indexptr )
    if ( !(indexptr = new DBIndex((kcb *)NULL,YES,NO,YES,NO,1,SET_SOME,NO)) )
                                                     SDBERR(95)
  SetupIntern(smcbptr,extnames,irefname,indexptr);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04 - 



\param  fmcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldDef"

     DBFieldDef :: DBFieldDef (fmcb *fmcbptr )
                     : FieldDef (fmcbptr),
  index_list(new DBIndexList()),
  offset_ext(UNDEF), 
  ext_length(UNDEF), 
  inverse_field(NULL), 
  cluster_opt(NO), 
  mb_number(AUTO), 
  meta_field(MAT_undefined),
  privilege(PI_Exclusive), 
  static_field(YES), 
  virtual_field(NO), 
  dominant(NO), 
  sec_reference(NO), 
  log_reference(NO), 
  version(0), 
  extend(NULL),
  owning(NO), 
  create(YES),
  week_typed(NO), 
  depend(NO),
  update(NO),
  multikey(NO),
  initval(NULL),
  resource(NULL),
  clustered_table(NO),
  is_base_coll(AUTO),
  resource_lock(NULL),
  net_pos(0),
  net_length(0),
  prev_field(NULL),
  global_identity(NO),
  set_operation(NO),
  by_reference(NO),
  del_empty(NO),
  shared(NO),
  constraint(NULL),
  sources(NULL)
{
  int32                    intpos      = fmcbptr->fmcbposn;
  int32                    extpos      = 0;
  int32                    netpos      = 0;
  int8                     max_aligned = 1;
  fmcbopt = YES;
  memset(inverse_fname,' ',sizeof(inverse_fname));
  memset(gen_type,' ',sizeof(gen_type));
  
  if ( fmcbrlev == R_REFR )
    SetupReference(intpos,extpos,netpos,1,max_aligned);
  else
    SetupAttribute(intpos,extpos,netpos,1,max_aligned);


}

/******************************************************************************/
/**
\brief  i05 - 



\param  dictptr - Dictionary handle
\param  ph - 
\param  smcbptr - Pointer to general structure definition
\param  indexptr - Index definition
\param  domopt - Property is dominant
\param  logrefr - Property is a logical reference
\param  secrefr - Property is secundary referenced
\param  depopt - Property data depends on property
\param  extnames - Extent name
\param  irefname - Name of inverse property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldDef"

     DBFieldDef :: DBFieldDef (Dictionary *dictptr, PropertyHandle &ph, smcb *smcbptr, DBIndex *indexptr, logical domopt, logical logrefr, logical secrefr, logical depopt, char *extnames, char *irefname )
                     : FieldDef(),
  index_list(new DBIndexList()),
  offset_ext(0),
  ext_length(0), 
  inverse_field(NULL), 
  meta_field(MAT_undefined),
  privilege(PI_Exclusive), 
  dominant(domopt), 
  sec_reference(secrefr), 
  log_reference(logrefr),
  update(NO), 
  multikey(NO),
  depend(depopt),
  initval(NULL),
  resource(NULL),
  clustered_table(NO),
  extend(NULL),
  is_base_coll(AUTO),
  resource_lock(NULL),
  prev_field(NULL),
  global_identity(NO),
  set_operation(NO),
  by_reference(NO),
  del_empty(NO),
  shared(NO),
  constraint(NULL),
  sources(NULL)
{

  if ( ph.IsPositioned() )
  {
    update = ph.IsTrue("update"); 
    multikey = ph.IsTrue("multikey");
    FillReference(ph,dictptr,AUTO,NO);
    FMCBRefLevel((SDB_RLEV)ph.GetInt("reference_level"),ph.IsTrue("ddetrans"));
  }
  privilege = extnames && *extnames > ' ' ? PI_Share : PI_Exclusive;
  
  SetupIntern(smcbptr,extnames,irefname,indexptr);


}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldDef"

     DBFieldDef :: DBFieldDef ( )
                     : FieldDef("","",0,RL_direct,UNDEF,UNDEF,UNDEF),
  index_list(new DBIndexList()),
  offset_ext(UNDEF), 
  ext_length(UNDEF), 
  inverse_field(NULL), 
  cluster_opt(NO), 
  mb_number(AUTO), 
  meta_field(MAT_undefined),
  privilege(PI_Exclusive), 
  static_field(NO), 
  virtual_field(NO), 
  dominant(NO), 
  sec_reference(NO), 
  log_reference(NO), 
  version(0), 
  extend(NULL),
  owning(NO), 
  create(YES),
  week_typed(NO), 
  depend(NO),
  update(NO), 
  multikey(NO), 
  initval(NULL),
  resource(NULL), 
  clustered_table(NO), 
  is_base_coll(AUTO),
  resource_lock(NULL),
  net_pos(0),
  net_length(0),
  prev_field(NULL),
  global_identity(NO),
  set_operation(NO),
  by_reference(NO),
  del_empty(NO),
  shared(NO),
  constraint(NULL),
  sources(NULL)
{

  fmcbopt = YES;
  memset(inverse_fname,' ',sizeof(inverse_fname));
  memset(gen_type,' ',sizeof(gen_type));


}

/******************************************************************************/
/**
\brief  i2 - 



\param  dictptr - Dictionary handle
\param  dbrptr - ODABA2 reference definition
\param  smcbptr - Pointer to general structure definition
\param  indexptr - Index definition
\param  domopt - Property is dominant
\param  logrefr - Property is a logical reference
\param  secrefr - Property is secundary referenced
\param  depopt - Property data depends on property
\param  extnames - Extent name
\param  irefname - Name of inverse property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldDef"

     DBFieldDef :: DBFieldDef (Dictionary *dictptr, SDB_Reference *dbrptr, smcb *smcbptr, DBIndex *indexptr, logical domopt, logical logrefr, logical secrefr, logical depopt, char *extnames, char *irefname )
                     : FieldDef(),
  index_list(new DBIndexList()),
  offset_ext(0),
  ext_length(0), 
  inverse_field(NULL), 
  meta_field(MAT_undefined),
  privilege(PI_Exclusive), 
  dominant(domopt), 
  sec_reference(secrefr), 
  log_reference(logrefr),
  update(NO), 
  multikey(NO),
  depend(depopt),
  initval(NULL),
  resource(NULL),
  clustered_table(NO),
  extend(NULL),
  is_base_coll(AUTO),
  resource_lock(NULL),
  prev_field(NULL),
  global_identity(NO),
  set_operation(NO),
  by_reference(NO),
  del_empty(NO),
  shared(NO),
  constraint(NULL),
  sources(NULL)
{

  if ( dbrptr )
  {
    update = dbrptr->get_update(); 
    multikey = dbrptr->get_multikey();
    Fill(dbrptr,dictptr,NO);
    FMCBRefLevel(dbrptr->get_reference_level(),dbrptr->get_ddetrans());
  }
  privilege = extnames && *extnames > ' ' ? PI_Share : PI_Exclusive;
  
  SetupIntern(smcbptr,extnames,irefname,indexptr);


}

/******************************************************************************/
/**
\brief  i3 - 



\param  dbyptr - ODABA2 property definition
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBFieldDef"

     DBFieldDef :: DBFieldDef (SDB_Property *dbyptr, smcb *smcbptr )
                     : FieldDef (),
  index_list(new DBIndexList()),
  offset_ext(0),
  ext_length(0),   
  inverse_field(NULL),
  cluster_opt(NO),
  mb_number(UNDEF), 
  meta_field(MAT_undefined),
  privilege(PI_Exclusive), 
  dominant(NO), 
  sec_reference(NO), 
  log_reference(NO),
  version(0), 
  owning(NO),
  create(YES),
  week_typed(NO),
  update(NO), 
  multikey(NO),
  depend(NO),
  initval(NULL),
  resource(NULL),
  clustered_table(NO),
  extend(NULL),
  is_base_coll(AUTO),
  resource_lock(NULL),
  prev_field(NULL),
  global_identity(NO),
  set_operation(NO),
  by_reference(NO),
  del_empty(NO),
  shared(NO),
  constraint(NULL),
  sources(NULL)
{

  Fill(dbyptr,NULL);
  
  if ( smcbptr )
  {
    if ( !fmcbnsid && smcbptr->smcbnsid > 0 )
      fmcbnsid = smcbptr->smcbnsid;
    
    fmcbityp = smcbptr->smcbityp;
    if ( smcbptr->smcbstyp != ST_BASE )
      fmcbsmcb = smcbptr;
  }

}

/******************************************************************************/
/**
\brief  ExtToInt - 



\return term - Termination code

\param  intfld - 
\param  extfld - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtToInt"

logical DBFieldDef :: ExtToInt (char *intfld, char *extfld, logical pif )
{
  int32    len = fmcbbyte;
  int16    code_val;
BEGINSEQ
  if ( fmcbtrans )
  {
    InitAttribute(intfld);
    LEAVESEQ
  }

  if ( fmcbbase() )
  {
    if ( pif )
      ConvertFromNet(extfld,intfld);
    else
      memcpy(intfld,extfld,fmcbdim > 1 ? fmcbbyte/fmcbdim : fmcbbyte);
  }
  else if ( fmcbsmcb->smcbstyp == ST_CODE )
  {            
    LoadShort(code_val,extfld);
    if ( pif )
      *(int *)intfld = (int)PIFToShort(code_val,YES);
    else
      *(int *)intfld = (int)code_val;
  }
  else 
    GetDBStruct()->ExtToInt(intfld,extfld,pif);



ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ExtToIntDim - 



\return term - Termination code

\param  extfld - 
\param  intfld - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtToIntDim"

logical DBFieldDef :: ExtToIntDim (char *extfld, char *intfld, logical pif )
{
  uint16   i = 0;
  uint32   len;
  uint32   elen;
  logical  term = NO;
  if ( fmcbrlev == R_DIRECT && !fmcbtrans )   
     for (i=0, len=fmcbbyte/fmcbdim, elen=ext_length/fmcbdim; 
          i < fmcbdim;
          i++, intfld+=len, extfld+=elen )
       ExtToInt(extfld,intfld,pif);

  return(term);
}

/******************************************************************************/
/**
\brief  Fill - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbaptr - 
\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (SDB_Attribute *dbaptr, Dictionary *dictptr )
{
  logical    chk        = IsFilled();
  int16      old_revlev;
  logical    term = NO;
BEGINSEQ
  Fill((SDB_Property *)dbaptr,dictptr);
  
  if ( chk )
  {
    old_revlev = fmcbrlev;
    FMCBRefLevel(dbaptr->get_reference_level(),dbaptr->get_ddetrans());
    if ( fmcbrlev != old_revlev )
    {
      fmcbrlev = old_revlev;    
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }
  
  if ( fmcbrlev == R_GENERIC )
  {
    update          = NO;        // war YES bis 11.5, Problem mit Refresh in mvld!, setzt refcuri zurück
    create          = YES;
#ifdef __unix__    
    clustered_table = NO;        // das machen wir, weil die SPARK mit mvld's noch nicht klar kommt, kann später wieder raus
#else
    clustered_table = YES;
#endif
//  clustered_table = NO;        // das machen wir, weil die SPARK mit mvld's noch nicht klar kommt, kann später wieder raus
                                 // ausserdem bekommen wir sonst keine ID für ORACLE
    if ( fmcbdim = 1 )
      fmcbdim         = 0;  // singuläre generische Referenzen könnten Sinn machen, wenn man sprachabhängige Indizees fuer eindimensionale Attribute bilden will
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i06 - 



\param  strdef - Structure definition
\param  bnf_data - 
\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (DBStructDef *strdef, BNFData *bnf_data, Dictionary *dictptr )
{
  logical                 unicode = NO;  // muss dann in den FMCB
  BNFData                *bdata;
  DBFieldDef             *source_field;
  logical                 term = NO;
BEGINSEQ
// parameter             := parm_spec | operand | '*'
// parm_spec             := [simple_type_spec] [ref_symbol(*)] identifier [fixed_array_size(*)] assigned_value
// assigned_value        := assign_op operand
  
  if ( bnf_data->IsValue("*") )                      SDBERR(109)
  if ( bnf_data->IsSymbol("operand") )               // only names allows as operands
  {
    if ( !(bdata = bnf_data->GetSymbol("pname")) )   SDBERR(777)
    gvtxstb(fmcbname,bdata->StringValue(),ID_SIZE);
    CreateSourceList(bdata->StringValue(),UNDEF);
  }
  else // parm_spec
  {
    bdata = bnf_data->GetElement("identifier");
    gvtxstb(fmcbname,bdata->StringValue(),ID_SIZE);
    bdata = bnf_data->GetElement("assigned_value")->GetElement(1);
    CreateSourceList(bdata->StringValue(),UNDEF);
  }
  SDBEV1(GetSource(0)->GetString(),UNDEF)
  SDBEV2(fmcbname,ID_SIZE)
  GetSource(0)->SetStructDef(strdef);
  
  if ( source_field = GetSource(0)->GetResultDescription(dictptr) )
    UpdateDescription(*source_field);

  if ( bdata = bnf_data->GetSymbol("fixed_array_size") )
    fmcbsize = bdata->IntValue();
  if ( bdata = bnf_data->GetElement("simple_type_spec") )
  {
    if ( ((BNFExpData *)bdata)->GetTypeSpec(fmcbtype,gen_type,fmcbsize,fmcbdim,fmcbprec,unicode) )
                                                     ERROR
    fmcbrlev = R_DIRECT;
    if ( !strcmp(gen_type,"SET") || !strcmp(gen_type,"LIST") || !strcmp(gen_type,"BAG") )
      fmcbrlev = R_REFR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbbptr - 
\param  dictptr - Dictionary handle
\param  setup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (SDB_BaseStruct *dbbptr, Dictionary *dictptr, logical setup )
{
  logical    chk  = IsFilled();
  DBIndex   *index;
  logical    term = NO;
BEGINSEQ
  fmcbbstr = YES;
  if ( Fill((SDB_Relationship *)dbbptr,dictptr,setup) && chk )
                                                     ERROR
  if ( index = index_list->GetTail() )
    index->SetBaseStructOrgType();       // refx
  
  FMCBRefLevel(RL_direct,NO);
  fmcbdim     = 1;
  dominant    = dbbptr->get_smcedom();
    
  if ( chk )
  {
    if ( privilege != (get_extend() ? PI_Share : PI_Exclusive) )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }
  
  privilege   = get_extend() ? PI_Share : PI_Exclusive;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  dbrptr - ODABA2 reference definition
\param  dictptr - Dictionary handle
\param  setup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (SDB_Reference *dbrptr, Dictionary *dictptr, logical setup )
{
  logical    chk  = IsFilled();
  logical    term = NO;
BEGINSEQ
  if ( Fill((SDB_Property *)dbrptr,dictptr) && chk )   ERROR

  FMCBRefLevel(RL_reference,NO);  
  cluster_opt       = dbrptr->get_clustered();
  mb_number         = dbrptr->get_mb_number();
  owning            = dbrptr->get_owning();
  create            = dbrptr->get_create();
  week_typed        = dbrptr->get_week_typed();
  global_identity   = dbrptr->get_global_identity();
  
  if ( chk )
  {
    if ( update          != dbrptr->get_update()       ||
         multikey        != dbrptr->get_multikey()     ||
         clustered_table != (dbrptr->get_clustered_table() == YES) )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }
  
  update          = dbrptr->get_update();
  multikey        = dbrptr->get_multikey();
  clustered_table = dbrptr->get_clustered_table() == YES;
  
  if ( setup )   
  {
    if ( SetupType(dictptr,YES) )                    ERROR
    if ( CreateIndexList(NULL,dbrptr,YES) )          ERROR
  }
RECOVER
  term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i3 - 



\param  dbpptr - 
\param  dictptr - Dictionary handle
\param  setup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (SDB_Relationship *dbpptr, Dictionary *dictptr, logical setup )
{
  logical    chk  = IsFilled();
  logical    term = NO;
BEGINSEQ
  if ( Fill((SDB_Reference *)dbpptr,dictptr,setup) && chk )
                                                     ERROR
  SetExtent(dbpptr->get_ddeext());
  if ( get_extend() )
    owning = NO;
    
  depend        = dbpptr->get_depend();
  sec_reference = dbpptr->get_ddesecr();
  
  if ( chk )
  {
    if ( memcmp(inverse_fname,dbpptr->get_ddeinv(),ID_SIZE) ||
         log_reference != dbpptr->get_dderlog()           )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }

  memcpy(inverse_fname,dbpptr->get_ddeinv(),ID_SIZE);
  log_reference = dbpptr->get_dderlog();
  privilege     = PI_Share;
  
  if ( extend )
    owning = NO;
  
  if ( *inverse_fname == ' ' )
  {
    sec_reference = NO;
    if ( !extend )
      owning = YES;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i5 - 



\param  dbyptr - ODABA2 property definition
\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (SDB_Property *dbyptr, Dictionary *dictptr )
{
  logical    chk       = IsFilled();
  char      *expression;
  logical    term = NO;
BEGINSEQ
  if ( Fill(dbyptr,dictptr,dbyptr->get_ddetrans()) && chk )  ERROR
  
  if ( chk )
  {
    if ( memcmp(gen_type,dbyptr->get_ddegent(),8) ||
         version != dbyptr->get_version()            )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }

  memcpy(gen_type,dbyptr->get_ddegent(),8);
  SetExtent(NULL);
  memset(inverse_fname,' ',sizeof(inverse_fname));
  
  privilege       = PI_Exclusive;
  del_empty       = dbyptr->get_delete_empty();
  shared          = dbyptr->get_shared();
  static_field    = dbyptr->get_ddestat();
  virtual_field   = dbyptr->get_ddevirt();
  version         = dbyptr->get_version();
  fmcbtrans       = fmcbrlev > 0 ? YES : dbyptr->get_ddetrans();
  
  if ( !index_list )
    if ( !(index_list = new DBIndexList()) )         SDBERR(95)
  
  expression = dbyptr->get_constraint().GetString();
  if ( expression && *expression )
    set_constraint(expression,UNDEF);

  CreateSourceList(dbyptr);
  CreateSynonymList(dbyptr);
  
  if ( !resource && dictptr )
  {
    if ( !(resource = new DBResource(dictptr)) )     SDBERR(95)
    if ( resource->Initialize(dbyptr,dbyptr->GetResID()) )
                                                     ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i6 - 



\param  dbmptr - 
\param  dictptr - Dictionary handle
\param  transient - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical DBFieldDef :: Fill (SDB_Member *dbmptr, Dictionary *dictptr, logical transient )
{
  int32      nsid = 0;
  logical    term = NO;
BEGINSEQ
  if ( FieldDef::Fill(dbmptr,transient) )             ERROR
  
  Initialize();
  set_initval(dbmptr->get_ddeinit(),127);
  global_identity = NO;

  if ( *dbmptr->get_scope() > ' ' )
    fmcbnsid = dictptr->GetNSID(dbmptr->get_scope());
  
  if ( fmcbnsid )
  {
    TypeKey  tkey(fmcbtype,fmcbnsid);
    if ( (nsid = tkey.LookUp(dictptr)) == AUTO )     ERROR
    fmcbnsid = nsid;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillAttribute - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillAttribute"

logical DBFieldDef :: FillAttribute (PropertyHandle &ph, Dictionary *dictptr, int32 nsid )
{
  logical    chk  = IsFilled();
  int16      old_revlev;
  logical    term = NO;
BEGINSEQ
  if ( FillProperty(ph,dictptr,nsid) && chk )       ERROR

  if ( chk )
  {
    old_revlev = fmcbrlev;
    FMCBRefLevel((SDB_RLEV)ph.GetInt("reference_level"),ph.IsTrue("ddetrans"));
    if ( fmcbrlev != old_revlev )
    {
      fmcbrlev = old_revlev;    
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }
  
  if ( fmcbrlev == R_GENERIC )
  {
    update          = NO;        // war YES bis 11.5, Problem mit Refresh in mvld!, setzt refcuri zurück
    create          = YES;
#ifdef __unix__    
    clustered_table = NO;        // das machen wir, weil die SPARK mit mvld's noch nicht klar kommt, kann später wieder raus
#else
    clustered_table = YES;
#endif
//  clustered_table = NO;        // das machen wir, weil die SPARK mit mvld's noch nicht klar kommt, kann später wieder raus
                                 // ausserdem bekommen wir sonst keine ID für ORACLE
    if ( fmcbdim = 1 )
      fmcbdim         = 0;  // singuläre generische Referenzen könnten Sinn machen, wenn man sprachabhängige Indizees fuer eindimensionale Attribute bilden will
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillBaseStruct - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
\param  setup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillBaseStruct"

logical DBFieldDef :: FillBaseStruct (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical setup )
{
  logical    chk  = IsFilled();
  DBIndex   *index;
  logical    term = NO;
BEGINSEQ
  fmcbbstr = YES;
  if ( FillRelationship(ph,dictptr,nsid,setup) && chk ) 
                                                     ERROR
  if ( index = index_list->GetTail() )
    index->SetBaseStructOrgType();       // refx
  
  FMCBRefLevel(RL_direct,NO);
  fmcbdim     = 1;
  dominant    = ph.IsTrue("smcedom");
    
  if ( chk )
  {
    if ( privilege != (get_extend() ? PI_Share : PI_Exclusive) )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }
  
  privilege   = get_extend() ? PI_Share : PI_Exclusive;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillFunction - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillFunction"

logical DBFieldDef :: FillFunction (PropertyHandle &ph, Dictionary *dictptr, int32 nsid )
{
  smcb     *smcbptr     = NULL;
  int8      max_aligned = 1;
  logical                 term = NO;
  FillMember(ph,dictptr,nsid,YES);
  
  set_operation = ph.GetInt("proc_type") == PRCT_collection ? YES : NO; 
   
  if ( *fmcbtype <= ' ' )
    SetNoField();
  else
  {
    if ( fmcbrlev == R_REFR )
    {
      fmcbrlev     = R_DIRECT;
      by_reference = YES;
    }
  }

  if ( dictptr )
    smcbptr = dictptr->ProvideStructDef(fmcbtype);
  fmcbesu(smcbptr,0,UNDEF,max_aligned);
  return(term);
}

/******************************************************************************/
/**
\brief  FillMember - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
\param  transient - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillMember"

logical DBFieldDef :: FillMember (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical transient )
{
  char                   *scope = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( FieldDef::FillMember(ph,transient) )            ERROR
  
  Initialize();
  set_initval(ph.GetString("ddeinit"),127);
  global_identity = NO;

  fmcbnsid = nsid;
if ( dictptr->get_sys_version() > 17 )
{
  if ( (scope = ph.GetArea("scope")) && *scope > ' ' )
    fmcbnsid = dictptr->GetNSID(scope);
  
  if ( fmcbnsid )
  {
    TypeKey  tkey(fmcbtype,fmcbnsid);
    if ( (nsid = tkey.LookUp(dictptr)) == AUTO )     ERROR
    fmcbnsid = nsid;
  }
}
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillProperty - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillProperty"

logical DBFieldDef :: FillProperty (PropertyHandle &ph, Dictionary *dictptr, int32 nsid )
{
  logical    chk  = IsFilled();
  char      *expression;
  logical    term = NO;
BEGINSEQ
  if ( FillMember(ph,dictptr,nsid,ph.IsTrue("ddetrans")) && chk )
                                                     ERROR
  if ( chk )
  {
    if ( memcmp(gen_type,ph.GetArea("ddegent"),ID_SIZE) ||
         version != ph.GetInt("version")            )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }

  memcpy(gen_type,ph.GetArea("ddegent"),ID_SIZE);
  SetExtent(NULL);
  memset(inverse_fname,' ',sizeof(inverse_fname));
  
  privilege       = PI_Exclusive;
  del_empty       = ph.IsTrue("delete_empty");
  shared          = ph.IsTrue("shared");
  static_field    = ph.IsTrue("ddestat");
  virtual_field   = ph.IsTrue("ddevirt");
  version         = ph.GetInt("version");
  fmcbtrans       = fmcbrlev > 0 ? YES : ph.IsTrue("ddetrans");
  
  if ( !index_list )
    if ( !(index_list = new DBIndexList()) )         SDBERR(95)
  
  expression = ph.GetString("constraint");
  if ( expression && *expression )
    set_constraint(expression,UNDEF);

  CreateSourceList(ph);
  CreateSynonymList(ph);
  
  if ( !resource && dictptr )
  {
    if ( !(resource = new DBResource(dictptr)) )     SDBERR(95)
    if ( resource->Initialize(ph) )                  ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillReference - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
\param  setup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillReference"

logical DBFieldDef :: FillReference (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical setup )
{
  logical    chk  = IsFilled();
  logical    term = NO;
BEGINSEQ
if ( dictptr->get_sys_version() > 17 )
{
  PH(&ph,name_space)
  if ( name_space(0) )
    nsid = name_space.GetInt("itype"); 
}  
  if ( FillProperty(ph,dictptr,nsid) && chk )        ERROR

  FMCBRefLevel(RL_reference,NO);  
  cluster_opt       = ph.IsTrue("clustered");
  mb_number         = ph.GetInt("mb_number");
  owning            = ph.IsTrue("owning");
  create            = ph.IsTrue("create");
  week_typed        = ph.IsTrue("week_typed");
  global_identity   = ph.IsTrue("global_identity");
  
  if ( chk )
  {
    if ( update          != ph.IsTrue("update")         ||
         multikey        != ph.IsTrue("multikey")       ||
         clustered_table != (*ph.GetArea("clustered_table") == 1)   )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }
  
  update          = ph.IsTrue("update");
  multikey        = ph.IsTrue("multikey");
  clustered_table = (*ph.GetArea("clustered_table") == 1);
  
  if ( setup )   
  {
    if ( SetupType(dictptr,YES) )                    ERROR
    if ( CreateIndexList(ph,NULL,YES) )              ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillRelationship - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
\param  setup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillRelationship"

logical DBFieldDef :: FillRelationship (PropertyHandle &ph, Dictionary *dictptr, int32 nsid, logical setup )
{
  logical    chk  = IsFilled();
  logical    term = NO;
BEGINSEQ
  if ( FillReference(ph,dictptr,nsid,setup) && chk ) ERROR
    
  SetExtent(ph.GetString("ddeext"));
  if ( get_extend() )
    owning = NO;
    
  depend        = ph.IsTrue("depend");
  sec_reference = ph.IsTrue("ddesecr");
  
  if ( chk )
  {
    if ( memcmp(inverse_fname,ph.GetArea("ddeinv"),ID_SIZE) ||
         log_reference != ph.IsTrue("dderlog")           )
    {
      TraceGenError();                               ERROR
    }
    LEAVESEQ
  }

  memcpy(inverse_fname,ph.GetArea("ddeinv"),ID_SIZE);
  log_reference = ph.IsTrue("dderlog");
  privilege     = PI_Share;
  
  if ( extend )
    owning = NO;
  
  if ( *inverse_fname == ' ' )
  {
    sec_reference = NO;
    if ( !extend )
      owning = YES;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillVariable - 



\return term - Termination code

\param  ph - 
\param  dictptr - Dictionary handle
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillVariable"

logical DBFieldDef :: FillVariable (PropertyHandle &ph, Dictionary *dictptr, int32 nsid )
{
  smcb     *smcbptr     = NULL;
  int8      max_aligned = 1;
  logical   term = NO;
  FillMember(ph,dictptr,nsid,YES);
     
  fmcbinit = ph.IsTrue("initialize");
  fmcbcnst = ph.IsTrue("const_val");

  if ( fmcbrlev == R_REFR )
  {
    fmcbrlev     = R_DIRECT;
    by_reference = YES;
  }

  if ( dictptr )
    smcbptr = dictptr->ProvideStructDef(fmcbtype);
  fmcbesu(smcbptr,0,UNDEF,max_aligned);
  return(term);
}

/******************************************************************************/
/**
\brief  GetDBField - 



\return dbfield_def - 

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBField"

DBFieldDef *DBFieldDef :: GetDBField (uint16 version_nr )
{
  DBFieldDef        *dbfield_def = this;
  while ( dbfield_def->get_prev_field() && 
          version_nr <= dbfield_def->get_prev_field()->get_version() )
    dbfield_def = dbfield_def->get_prev_field();
  return(dbfield_def);
}

/******************************************************************************/
/**
\brief  GetDBStruct - 



\return dbstruct_ptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBStruct"

DBStructDef *DBFieldDef :: GetDBStruct ( )
{
  DBStructDef  *strdefptr   = NULL;
  int8          max_aligned = 1;
BEGINSEQ
  if ( !this )                                     ERROR
    
  if ( !fmcbityp && fmcbsmcb && (fmcbsmcb->smcbityp > 0 || fmcbsmcb->smcbityp == TEMPSID) )
    fmcbesu(fmcbsmcb,fmcbposn,DEFAULT_ALLIGNMENT,max_aligned);
    
  if ( fmcbityp && fmcbsmcb )
    strdefptr = (DBStructDef *)fmcbsmcb;

RECOVER

ENDSEQ
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  dictptr - Dictionary handle
\param  schema_version_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBStruct"

DBStructDef *DBFieldDef :: GetDBStruct (Dictionary *dictptr, int16 schema_version_w )
{
  DBStructDef  *dbstruct_ptr = NULL;
  int8          max_aligned  = 1;
BEGINSEQ
  if ( !this || *fmcbtype <= ' ' )                   ERROR

  if ( dictptr )
    if ( !(dbstruct_ptr = dictptr->ProvideStructDef(fmcbtype,schema_version_w)) )
                                                     ERROR
  if ( !fmcbityp )
  {
    if ( dbstruct_ptr->GetLength() <= 0 && dictptr )
      dbstruct_ptr->Setup(dictptr);
    fmcbesu(dbstruct_ptr,fmcbposn,DEFAULT_ALLIGNMENT,max_aligned);
  }
RECOVER
  dbstruct_ptr = NULL;
ENDSEQ
  return(dbstruct_ptr);
}

/******************************************************************************/
/**
\brief  GetExtendName - 



\return extname - Extent name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtendName"

char *DBFieldDef :: GetExtendName ( )
{

  return((char *)get_extend());

}

/******************************************************************************/
/**
\brief  GetIndexDef - 



\return indexdef - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  indx_pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexDef"

DBIndex *DBFieldDef :: GetIndexDef (int16 indx_pos )
{
  DBIndex                   *indexdef = NULL;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  ILock(YES);
  
  index_list->GoTop();
  for (; indx_pos >= 0 && (indexdef = index_list->GetNext()); indx_pos-- ) ;
  
  IUnlock();


ENDSEQ
  return(indexdef);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  keyname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexDef"

DBIndex *DBFieldDef :: GetIndexDef (char *keyname )
{
  DBIndex                *indexdef = NULL;
  char                    name[ID_SIZE];
BEGINSEQ
  ILock(YES);
  if ( !index_list )                                 ERROR
  
  if ( !keyname || !*keyname )                       
    indexdef = index_list->GetHead();
  else
  {  
    gvtxstb(name,keyname,ID_SIZE);
    index_list->GoTop();
    while ( indexdef = index_list->GetNext() )
      if ( !memcmp(name,indexdef->GetKeyName(),ID_SIZE) )   
        break;
  }

RECOVER

ENDSEQ
  IUnlock();
  return(indexdef);
}

/******************************************************************************/
/**
\brief  GetIndexName - 



\return index_name - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexName"

char *DBFieldDef :: GetIndexName (int32 indx0 )
{

  return ( this && index_list ? index_list->GetIndexName(indx0) : NULL);

}

/******************************************************************************/
/**
\brief  GetResourceID - 



\return ressource_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceID"

int32 DBFieldDef :: GetResourceID ( )
{

  return ( this && resource ? resource->get_res_id() : UNDEF );

}

/******************************************************************************/
/**
\brief  GetSQLType - Get SQL table definition

        The  function  returns  a  string  for  a attribute definition in an SQL
        CREATE  TABLE statement. The passed string area should have at least 100
        characters.

\return sql_type - String for the SQL definition

\param  sql_type - String for the SQL definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSQLType"

char *DBFieldDef :: GetSQLType (char *sql_type )
{
  char           string[17];
BEGINSEQ
  if ( !sql_type )                                   ERROR
  if ( !fmcbityp )                                   ERROR
  
  *sql_type = 0;
  
  switch ( fmcbityp )
  {
    case T_STRING :
    case T_MEMO   :
    case T_GUID   :
    case T_CHAR   : strcat(sql_type,"VARCHAR");
                    strcat(strcat(strcat(sql_type,"("),gvtxltoa(fmcbsize,string,10)),")");
                    break;
    case T_LO     : strcat(sql_type,"BOOLEAN");
                    break;
    case T_DATE   : strcat(sql_type,"DATE");
                    break;
    case T_TIME   : strcat(sql_type,"TIME");
                    break;
    case T_UINT   :
    case T_INT    : if ( !fmcbprec )
                    {
                      strcat(sql_type,"INTEGER");
                      break;
                    }
    case T_REAL   : strcat(sql_type,"NUMERIC");
                    strcat(strcat(strcat(sql_type,"("),gvtxltoa(fmcbsize,string,10)),",");
                    strcat(strcat(sql_type,gvtxltoa(fmcbprec,string,10)),")");
                    break;
    default       : ERROR
  }
  if ( !fmcbempty )
    strcat(sql_type," NOT NULL");
RECOVER
  sql_type = NULL;
ENDSEQ
  return(sql_type);
}

/******************************************************************************/
/**
\brief  GetSource - 



\return fld_source - 

\param  indx_pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSource"

FieldSource *DBFieldDef :: GetSource (int16 indx_pos )
{
  FieldSource    *source = NULL;
BEGINSEQ
  if ( !sources )                                    LEAVESEQ
  
  ILock(YES);
  
  sources->GoTop();
  for (; indx_pos >= 0 && (source = sources->GetNext()); indx_pos-- ) ;
  
  IUnlock();

ENDSEQ
  return(source);
}

/******************************************************************************/
/**
\brief  GetStaticFieldDef - 



\return dbfield_def - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  ityp - Internal structure number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticFieldDef"

DBFieldDef *__cdecl DBFieldDef :: GetStaticFieldDef (int16 ityp )
{

  static    DBFieldDef  lo_flddef      (fmcb::GetStaticFMCB(T_LO));
  static    DBFieldDef  int_flddef     (fmcb::GetStaticFMCB(T_INT));
  static    DBFieldDef  uint_flddef    (fmcb::GetStaticFMCB(T_UINT));
  static    DBFieldDef  real_flddef    (fmcb::GetStaticFMCB(T_REAL));
  static    DBFieldDef  char_flddef    (fmcb::GetStaticFMCB(T_CHAR));
  static    DBFieldDef  string_flddef  (fmcb::GetStaticFMCB(T_STRING));
  static    DBFieldDef  cchar_flddef   (fmcb::GetStaticFMCB(T_CCHAR));
  static    DBFieldDef  guid_flddef    (fmcb::GetStaticFMCB(T_GUID));
  static    DBFieldDef  date_flddef    (fmcb::GetStaticFMCB(T_DATE));
  static    DBFieldDef  time_flddef    (fmcb::GetStaticFMCB(T_TIME));
  static    DBFieldDef  datetime_flddef(fmcb::GetStaticFMCB(T_DATETIME));

  switch ( ityp )
  {
    case T_LO       : return ( &lo_flddef );
    case T_INT      : return ( &int_flddef );
    case T_UINT     : return ( &uint_flddef );
    case T_REAL     : return ( &real_flddef );
    case T_STRING   : return ( &string_flddef );
    case T_GUID     : return ( &guid_flddef );
    case T_CHAR     : return ( &char_flddef );
    case T_CCHAR    : return ( &cchar_flddef );
    case T_DATE     : return ( &date_flddef );
    case T_TIME     : return ( &time_flddef );
    case T_DATETIME : return ( &datetime_flddef );
  }
  return(NULL);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  strnames - Type name
\param  dbstrdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticFieldDef"

DBFieldDef *__cdecl DBFieldDef :: GetStaticFieldDef (char *strnames, DBStructDef *dbstrdef )
{
  int8          max_align   = 1;
  DBFieldDef   *dbfield_def = NULL;
  static    DBFieldDef  dict_flddef     ("DictionaryHandle","DictionaryHandle",0,RL_direct,0,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);
  static    DBFieldDef  dbhandle_flddef ("DatabaseHandle",  "DatabaseHandle"  ,0,RL_direct,0,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);

  if ( !strcmp(strnames,"DictionaryHandle") )
    dbfield_def = &dict_flddef;
  else if ( !strcmp(strnames,"DatabaseHandle") )
    dbfield_def = &dbhandle_flddef;

  if ( dbfield_def && !dbfield_def->fmcbsmcb && dbstrdef )
    dbfield_def->fmcbesu(dbstrdef,0,DEFAULT_ALLIGNMENT,max_align);

  return(dbfield_def);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticFieldDef"

DBFieldDef *__cdecl DBFieldDef :: GetStaticFieldDef (char *prop_names )
{

  return ( GetStaticFieldDef(GetMetaAttributeType(prop_names)) );

}

/******************************************************************************/
/**
\brief  i03 - 



\param  meta_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticFieldDef"

DBFieldDef *__cdecl DBFieldDef :: GetStaticFieldDef (MAT_Types meta_type )
{
  int8          max_align   = 1;
  DBFieldDef   *dbfield_def = NULL;
BEGINSEQ
  static    DBFieldDef  loid_flddef     ("__LOID",   "STRING",0,RL_direct,20,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);
  static    DBFieldDef  guid_flddef     ("__GUID",   "STRING",0,RL_direct,40,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);
  static    DBFieldDef  type_flddef     ("__TYPE",   "STRING",0,RL_direct,40,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);
  static    DBFieldDef  skey_flddef     ("__S","STRING",0,RL_direct,MAX_KEYLEN,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);
  static    DBFieldDef  idkey_flddef    ("__key",    "STRING",0,RL_direct,MAX_KEYLEN,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);

  switch ( meta_type )
  {
    case MAT_LOID           : dbfield_def = &loid_flddef;
                              break;
    case MAT_GUID           : dbfield_def = &guid_flddef;
                              break;
    case MAT_Type           : dbfield_def = &type_flddef;
                              break;
    case MAT_SortKey        : dbfield_def = &skey_flddef;
                              break;
    case MAT_Key            : dbfield_def = &idkey_flddef;
                              break;
    default                 : ERROR
  }

  if ( dbfield_def && dbfield_def->meta_field == MAT_undefined )
  {
    dbfield_def->meta_field = meta_type;
    dbfield_def->fmcbityp  = T_STRING;
    dbfield_def->fmcbesu(NULL,0,DEFAULT_ALLIGNMENT,max_align);
  }

RECOVER

ENDSEQ
  return(dbfield_def);
}

/******************************************************************************/
/**
\brief  GetStructDef - 



\return dbstruct_ptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *DBFieldDef :: GetStructDef ( )
{

  return(GetDBStruct());

}

/******************************************************************************/
/**
\brief  i1 - 



\param  dict_hdl - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *DBFieldDef :: GetStructDef (DictionaryHandle &dict_hdl )
{

  return(GetDBStruct(dict_hdl.get_dictionary()));

}

/******************************************************************************/
/**
\brief  i2 - 



\param  dict_hdl - Dictionary handle
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *DBFieldDef :: GetStructDef (DictionaryHandle &dict_hdl, uint8 schemaversion )
{

  return(GetDBStruct(dict_hdl.get_dictionary(),schemaversion));

}

/******************************************************************************/
/**
\brief  GetSysPropType - 



\return spt - 

\param  prop_names - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSysPropType"

SystemPropertyTypes __cdecl DBFieldDef :: GetSysPropType (char *prop_names )
{
  SystemPropertyTypes      spt = SPT_undefined;
  if ( !strcmp(prop_names,"__loid") )
    spt = SPT_loid;
  else if ( !strcmp(prop_names,"__guid") )
    spt = SPT_guid;
  else if ( !strcmp(prop_names,"__type") )
    spt = SPT_type;
  else if ( !strcmp(prop_names,"__sortkey") )
    spt = SPT_sort_key;
  else if ( !strcmp(prop_names,"__key") )
    spt = SPT_key;
  else if ( !strcmp(prop_names,"__base_collection") )
    spt = SPT_base_collection;


  return(spt);
}

/******************************************************************************/
/**
\brief  GetTypeKey - 



\return tkey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeKey"

TypeKey &DBFieldDef :: GetTypeKey ( )
{

  return( *(TypeKey *)&fmcbtype );

}

/******************************************************************************/
/**
\brief  HasGUID - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasGUID"

logical DBFieldDef :: HasGUID ( )
{

  return ( !memcmp(fmcbsmcb->smcbname,"__OBJECT ",9) ||  // structure oder
           (!extend && ((DBStructDef *)fmcbsmcb)->get_based_on_object())    );// direkte base-structure ist von __OBJECT abgeleitet


}

/******************************************************************************/
/**
\brief  ILock - 



\return term - Termination code

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical DBFieldDef :: ILock (logical wait )
{
  logical                 term = NO;
  if ( resource_lock )
  {
    resource_lock->ILock(wait);
//  char                    string[ID_SIZE];
//  gvtxbts(string,fmcbname,ID_SIZE);
//  SDBError().TraceMessage("Lock Field: ",string);
  }


  return(term);
}

/******************************************************************************/
/**
\brief  IUnlock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical DBFieldDef :: IUnlock ( )
{
  logical                 term = NO;
  if ( resource_lock )
  {
//  char                    string[ID_SIZE];
//  gvtxbts(string,fmcbname,ID_SIZE);
//  SDBError().TraceMessage("Unlock Field: ",string);
    resource_lock->IUnlock(); 
  }


  return(term);
}

/******************************************************************************/
/**
\brief  InitAttribute - 




\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitAttribute"

void DBFieldDef :: InitAttribute (void *instptr )
{
  char       *string;
  int         dim;
  int         len        = 0;
  int32       intval;
  logical     is_numeric = NO;
  int         i;
  char       *instance = (char *)instptr;
BEGINSEQ
  if ( fmcbrlev != R_DIRECT && fmcbrlev != R_INTERN && fmcbrlev != R_GENERIC )
                                                     LEAVESEQ
  if ( string = (char *)get_initval() )
  {
    len = strlen(string);
    if ( string[0] == '"' && len > 1 && string[len-1] == '"' )
    {
      gvtssdl(string,1);
      len -= 2;
      string[len] = 0;
    }
    else if ( isdigit(*string) )
    {
      intval = atol(string);
      is_numeric = YES;
    }

    if ( !memcmp(fmcbname,"__GUID ",7) )
    {
      memset(instance+fmcbposn,0,fmcbbyte);   LEAVESEQ
    }
  }  
    
  dim = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  for ( i=0; i<dim; i++, instance+=fmcbbyte/dim)
    if ( fmcbbase() || (fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE) )
    {
      if ( len )
      {
        PropertyHandle  field(this,NULL);
        field.SetArea(instance);
        if ( is_numeric )
          field.SetValue(intval,NO);
        else
          field.SetValue(string,NO);
      }
    }
    else
      if ( fmcbsmcb )
        GetDBStruct()->InitAttributes(instptr);
ENDSEQ

}

/******************************************************************************/
/**
\brief  InitExtInst - 




\param  targ_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExtInst"

void DBFieldDef :: InitExtInst (char *targ_inst )
{
  int         tempval;
BEGINSEQ
  memset(targ_inst,0,(int)ext_length);
  
  if ( fmcbrlev != R_DIRECT )                        LEAVESEQ
  
  if ( fmcbbase() )
  {
    fmcbiini(targ_inst);
    if ( fmcbbase() )
      InitAttribute(targ_inst);
    if ( fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE )
    {
      InitAttribute((char *)&tempval);
      memcpy(targ_inst,&tempval,ext_length);
    }
  }
  else
    if ( GetDBStruct() )
      GetDBStruct()->InitExtInst(targ_inst);

ENDSEQ

}

/******************************************************************************/
/**
\brief  InitField - 



\return flddef - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  ityp - Internal structure number
\param  set_opt - 
\param  stat_opt - 
\param  v_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitField"

DBFieldDef *DBFieldDef :: InitField (int16 ityp, int8 set_opt, logical stat_opt, logical v_opt )
{
  DBFieldDef   *tpl_field = NULL;
BEGINSEQ
  if ( fmcbityp )                                    LEAVESEQ
  if ( !(tpl_field = DBFieldDef::GetStaticFieldDef(ityp)) )
                                                     ERROR
  CopyDescription(*tpl_field);
  
  set_operation = set_opt;
  fmcbstat      = stat_opt;
  fmcbvirt      = v_opt;

RECOVER

ENDSEQ
  return(fmcbityp ? this : NULL);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  strnames - Type name
\param  dbstrdef - Structure definition
\param  set_opt - 
\param  stat_opt - 
\param  v_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitField"

DBFieldDef *DBFieldDef :: InitField (char *strnames, DBStructDef *dbstrdef, int8 set_opt, logical stat_opt, logical v_opt )
{
  DBFieldDef   *tpl_field = NULL;
BEGINSEQ
  if ( fmcbsmcb )                                    LEAVESEQ
  if ( !(tpl_field = DBFieldDef::GetStaticFieldDef(strnames,dbstrdef)) )
                                                     ERROR
  CopyDescription(*tpl_field);
  
  set_operation = set_opt;
  fmcbstat      = stat_opt;
  fmcbvirt      = v_opt;

RECOVER

ENDSEQ
  return(fmcbsmcb ? this : NULL);
}

/******************************************************************************/
/**
\brief  Initialize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DBFieldDef :: Initialize ( )
{

  if ( !resource_lock )
    resource_lock = new RessourceLock(YES);
  
  is_base_coll = AUTO;
  fmcbopt      = YES;

}

/******************************************************************************/
/**
\brief  IntToExt - 



\return term - Termination code

\param  extfld - 
\param  intfld - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntToExt"

logical DBFieldDef :: IntToExt (char *extfld, char *intfld, logical pif )
{
  int16    code_val;
  logical  term = NO;
BEGINSEQ
  if ( !fmcbempty && IsEmpty(intfld) )             SDBERR(374)
  
  if ( fmcbbase() )
  {
    if ( pif )
      ConvertToNet(extfld,intfld);
    else
      memcpy(extfld,intfld,fmcbdim > 1 ? fmcbbyte/fmcbdim : fmcbbyte);
  }
  else if ( fmcbsmcb->smcbstyp == ST_CODE )
  {            
    code_val = (int16)(*(int *)intfld);
    if ( pif )
      code_val = ShortToPIF(code_val,YES);
    StoreShort(extfld,code_val);
  }
  else 
    GetDBStruct()->IntToExt(extfld,intfld,pif);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IntToExtDim - 



\return term - Termination code

\param  extfld - 
\param  intfld - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntToExtDim"

logical DBFieldDef :: IntToExtDim (char *extfld, char *intfld, logical pif )
{
  uint16   i = 0;
  uint32   len;
  uint32   elen;
  logical  term = NO;
  if ( fmcbrlev == R_DIRECT && !fmcbtrans )   
     for (i=0, len=fmcbbyte/fmcbdim, elen=ext_length/fmcbdim; 
          i < fmcbdim;
          i++, intfld+=len, extfld+=elen )
       IntToExt(extfld,intfld,pif);

  return(term);
}

/******************************************************************************/
/**
\brief  IntToNet - 



\return term - Termination code

\param  netfld - 
\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntToNet"

logical DBFieldDef :: IntToNet (char *netfld, char *intfld )
{
  uint16    i = 0;
  uint16    dim = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  uint16    len;
  if ( fmcbrlev == R_DIRECT || fmcbrlev == R_INTERN || fmcbrlev == R_GENERIC  )   
  {
    if ( fmcbbase() || (fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE) )
      ConvertDimToNet(netfld,intfld,UNDEF);
    else for (i=0, len=fmcbbyte/dim; i < dim; i++, intfld+=len)
    { 
      GetDBStruct()->IntToNet(netfld,intfld);
      netfld += GetDBStruct()->get_ext_length();
    }
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  IsActive - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsActive"

logical DBFieldDef :: IsActive ( )
{

  return( this && (fmcbityp > 0 || GetResourceID()) ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsBaseCollection - 



\return cond - 

\param  dictptr - Dictionary handle
\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBaseCollection"

logical DBFieldDef :: IsBaseCollection (Dictionary *dictptr, TypeKey &tkey )
{
  logical                 cond = YES;
BEGINSEQ
  if ( is_base_coll == AUTO )
  {
    if ( !GetDBStruct(dictptr) )                     ERROR
    is_base_coll = GetDBStruct()->IsBaseCollection(dictptr,tkey,fmcbname);
  }

RECOVER
  is_base_coll = NO;
ENDSEQ
  return(is_base_coll);
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

logical DBFieldDef :: IsBased (Dictionary *dictptr, TypeKey &tkey, char *fldnames )
{
  DBStructDef *struct_def = dictptr->GetStructDef(tkey);
  DBFieldDef  *path_field;
  fmcb        *fmcbptr;
  int32        offset;
  char         buffer[ID_SIZE];
  logical      cond = YES;
BEGINSEQ
  if ( get_inverse_name() )                        ERROR
  if ( !extend || *extend != '.' )                 ERROR
  
  if ( !(fmcbptr = struct_def->SearchField(extend+2,&offset)) || 
       !(path_field = fmcbptr->GetDescription()) ) ERROR
    
  if ( memcmp(path_field->fmcbname,gvtxstb(buffer,fldnames,ID_SIZE),ID_SIZE) )
                                                   ERROR
  if ( !GetDBStruct()->Inherits(path_field->fmcbtype) )
                                                   ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsEnumeration - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

logical DBFieldDef :: IsEnumeration ( )
{

  return( this && fmcbsmcb && 
          fmcbsmcb->smcbstyp == ST_CODE );

}

/******************************************************************************/
/**
\brief  IsGlobalInstance - 



\return cond - 

\param  dictionary - 
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGlobalInstance"

logical DBFieldDef :: IsGlobalInstance (Dictionary *dictionary, DBStructDef *strdef )
{
  char                   *extnames  = NULL;
  char                   *extpath   = NULL;
  smcb                   *smcbptr   = NULL;
  DBFieldDef             *fielddef  = NULL;
  int32                   offset    = 0;
  logical                 cond      = YES;
BEGINSEQ
  if ( !(extpath = GetExtendName()) || !*extpath || *extpath == '#' )
                                                     ERROR
  if ( *extpath != '.' )                             LEAVESEQ
  if ( !strdef )                                     SDBERR(99)
  
  if ( extpath[1] != '.' )                           SDBERR(99)
  if ( !(fielddef = strdef->SearchPathField(dictionary,extpath+2,YES,&offset,NULL,&smcbptr)->GetDescription()) )
                                                     SDBERR(99)
  cond = fielddef->IsGlobalInstance(dictionary,DBStructDef::GetDBStruct(smcbptr));

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsInverseBased - 



\return cond - 

\param  dictptr - Dictionary handle
\param  tkey - 
\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInverseBased"

logical DBFieldDef :: IsInverseBased (Dictionary *dictptr, TypeKey &tkey, char *fldnames )
{
  DBStructDef            *struct_def = GetDBStruct(dictptr);
  const char             *pos;
  const char             *base_path;
  DBFieldDef             *path_field;
  fmcb                   *fmcbptr;
  int32                   offset;
  char                    prop_name[ID_SIZE+1];
  char                    string[ID_SIZE+1];
  logical                 cond = YES;
BEGINSEQ
  if ( !get_inverse_name() )                         ERROR
  if ( !inverse_field )                              ERROR
  if ( !(base_path = inverse_field->get_extend()) || *base_path != '.' )
                                                     ERROR
  pos = (base_path += 2);
  while ( struct_def && (pos = strchr(base_path,'.')) )
  {
    memcpy(memset(prop_name,' ',ID_SIZE),base_path,pos-base_path);
    base_path = pos+1;
    
    if ( !(fmcbptr = struct_def->SearchField(prop_name,&offset)) || 
         !(path_field = fmcbptr->GetDescription()) ) ERROR
    
    struct_def = path_field->GetDBStruct(dictptr);
  }
  if ( !struct_def )                                 ERROR

  if ( strcmp(base_path,gvtxbts(string,fldnames,ID_SIZE)) )
                                                     ERROR
  if ( struct_def != GetDBStruct() && tkey != struct_def->smcbname )
                                                     ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsPIHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPIHandle"

logical DBFieldDef :: IsPIHandle ( )
{

  return ( this &&
           (fmcbrlev == R_REFR ||
            ((fmcbrlev == R_DIRECT || fmcbrlev == R_INTERN) 
             && fmcbopt && !memcmp(gen_type,"PI      ",8))) );

}

/******************************************************************************/
/**
\brief  IsStructure - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsStructure"

logical DBFieldDef :: IsStructure ( )
{
  DBStructDef   *strdef = NULL;
  return ( fmcbsmcb && 
           fmcbsmcb->smcbstyp != ST_BASE && fmcbsmcb->smcbstyp != ST_CODE
           ? YES
           : NO );


}

/******************************************************************************/
/**
\brief  IsText - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsText"

logical DBFieldDef :: IsText ( )
{
  logical                 cond = NO;
BEGINSEQ
  if ( !this )                                    ERROR
    
  switch ( fmcbityp ) 
  {
    case T_CHAR    :
    case T_MEMO    :
    case T_CCHAR   :
    case T_STRING  : cond = YES;
                     break; 
    default        : ;
  } 

RECOVER

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

logical DBFieldDef :: IsTransient ( )
{

  return ( this ? fmcbtrans : YES );

}

/******************************************************************************/
/**
\brief  IsTyped - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTyped"

logical DBFieldDef :: IsTyped ( )
{
  logical                 cond = YES;
BEGINSEQ
  if ( week_typed )                                  ERROR
  if ( !memcmp(fmcbtype, "VOID ", 5) )               ERROR
  if ( !memcmp(fmcbtype, "LOID ", 5) )               ERROR
  if ( !memcmp(fmcbtype, "GUID ", 5) )               ERROR
  if ( !memcmp(fmcbtype, "     ", 5) )               ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsUniqueKey - 



\return term - Termination code

\param  keynames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUniqueKey"

logical DBFieldDef :: IsUniqueKey (char *keynames )
{
  char                    keyname[ID_SIZE];
  DBIndex                *index;
  logical                 cond = NO;
  ILock(YES);
  gvtxstb(keyname,keynames,ID_SIZE);
  
  index_list->GoTop();
  while ( index = index_list->GetNext() )
    if ( index->get_key_def() && !memcmp(index->get_key_def()->scbsmcb->smcbname,keyname,ID_SIZE) )
    {
      cond = index->get_unique();
      break;
    }

  IUnlock();
  return(cond);
}

/******************************************************************************/
/**
\brief  IsViewStructure - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsViewStructure"

logical DBFieldDef :: IsViewStructure ( )
{

  return ( IsStructure() && fmcbsmcb->smcbsts.stscmod()
           ? YES
           : NO );


}

/******************************************************************************/
/**
\brief  NetToInt - 



\return term - Termination code

\param  intfld - 
\param  netfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NetToInt"

logical DBFieldDef :: NetToInt (char *intfld, char *netfld )
{
  uint16    i = 0;
  uint16    dim = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  uint16    len;
  if ( fmcbrlev == R_DIRECT || fmcbrlev == R_INTERN || fmcbrlev == R_GENERIC  )   
  {
    if ( fmcbbase() || (fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE) )
      ConvertDimFromNet(netfld,intfld,UNDEF);
    else for (i=0, len=fmcbbyte/dim; i < dim; i++, intfld+=len)
    { 
      GetDBStruct()->NetToInt(intfld,netfld);
      netfld += GetDBStruct()->get_ext_length();
    }
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  Release - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

logical DBFieldDef :: Release ( )
{
  logical                 term = NO;
  ILock(YES);
  
  if ( index_list )
    index_list->Release();
  index_list = NULL;
  
  delete resource;
  resource = NULL;

  IUnlock();

  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void DBFieldDef :: Remove ( )
{

  RemoveSourceList();
  
  delete constraint;
  constraint = NULL;
  
  delete initval;
  initval = NULL;
  
  if ( index_list )
    index_list->Release();
  index_list = NULL;
  
  delete extend;
  extend = NULL;

  delete resource_lock;
  resource_lock = NULL;

  delete resource;
  resource = NULL;

}

/******************************************************************************/
/**
\brief  RemoveSourceList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveSourceList"

void DBFieldDef :: RemoveSourceList ( )
{
  FieldSource   *source;
  if ( sources )
  {
    while ( source = sources->RemoveTail() )
      delete source;
    delete sources;
    sources = NULL;
  }

}

/******************************************************************************/
/**
\brief  SetExpressionRef - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  expr_ref - 
\param  init_string - 
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpressionRef"

logical DBFieldDef :: SetExpressionRef (ExpressionReference **expr_ref, char *init_string, int32 string_len )
{
  char     string[2048];
  logical  term = NO;
BEGINSEQ
  if ( !init_string || !expr_ref )                   LEAVESEQ
  if ( !string_len )
    string_len = strlen(init_string);
  if ( string_len > sizeof(string)-1 )               SDBERR(99)
  
  gvtxbts(string,init_string,string_len);    
  if ( !*string )                                    LEAVESEQ
    
  if ( !*expr_ref )
    *expr_ref = new ExpressionReference(NULL,string);
  else
    (*expr_ref)->SetExpression(string);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  expr_ref - 
\param  exprref_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpressionRef"

logical DBFieldDef :: SetExpressionRef (ExpressionReference **expr_ref, ExpressionReference *exprref_ptr )
{

BEGINSEQ
  if ( !expr_ref )                                   LEAVESEQ
  delete *expr_ref;
  *expr_ref = NULL;
  
  if ( exprref_ptr )
    *expr_ref = new ExpressionReference(*exprref_ptr);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetExtent - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExtent"

logical DBFieldDef :: SetExtent (char *extnames )
{
  int                     len;
  logical                 term = NO;
BEGINSEQ
  if ( extend ) 
  {
    free(extend);
    extend = NULL;
  }
  if ( !extnames || *extnames <= ' ' )               LEAVESEQ
  extend = strdup(extnames);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPrevious - 




\param  flddefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPrevious"

void DBFieldDef :: SetPrevious (DBFieldDef *flddefptr )
{

  prev_field = flddefptr;

}

/******************************************************************************/
/**
\brief  SetupAttribute - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAttribute"

logical DBFieldDef :: SetupAttribute (int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5 )
{
  int         dim = MAX(1,fmcbdim);
  SetupField(intpos,extpos,allign,max_aligned);
  
  offset_ext = extpos;
  net_pos    = netpos;
  
  if ( !fmcbtrans )
  {
    if ( fmcbbase() )
      ext_length = fmcbbyte;
    else if ( fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE )
      ext_length = DB_ENUM_SIZE * dim;
    else if ( fmcbrlev == R_GENERIC )
      ext_length = is_v5 ? 4 : sizeof(EB_Number);
    else if ( fmcbsmcb && fmcbityp != T_MEMO )
      ext_length = ((DBStructDef *)fmcbsmcb)->get_ext_length() * dim;
    else
      ext_length = fmcbbyte;
  }
  extpos += ext_length;
  
  switch ( fmcbrlev )    
  {
    case R_GENERIC : if ( fmcbsmcb )
                     {
                       SDB_Index  genidx(fmcbsmcb->GetIdentKeySMCB()->smcbname,
                                         SET_SMAL,YES,NO,NO,NO,UNDEF);
                       CreateIndex(NULL,&genidx);
                       owning = YES;
                     }
    case R_DIRECT  :                  
    case R_INTERN  : if ( fmcbbase() )
                       net_length = fmcbbyte;
                     else if ( fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE )
                       net_length = sizeof(int) * dim;
                     else if ( fmcbsmcb && fmcbityp != T_MEMO )
                       net_length = ((DBStructDef *)fmcbsmcb)->get_net_length() * dim;
                     else
                       net_length = fmcbbyte;
                     netpos += net_length;               
  }  

  return(NO);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAttribute"

logical DBFieldDef :: SetupAttribute (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5 )
{
  logical                 term = NO;
BEGINSEQ
  if ( SetupType(dictptr,fmcbrlev > 0 || *gen_type > ' ' ? YES : NO) )    
                                                     ERROR
  SetupAttribute(intpos,extpos,netpos,allign,max_aligned);

RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbaptr - 
\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupAttribute"

logical DBFieldDef :: SetupAttribute (SDB_Attribute *dbaptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned )
{
  logical    chk  = IsFilled();
  logical    term = NO;
BEGINSEQ
  Fill(dbaptr,dictptr); 
  delete dbaptr;
  
  if ( chk )                                         LEAVESEQ
  
  SetupAttribute(dictptr,intpos,extpos,netpos,allign,max_aligned);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupBaseStruct - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupBaseStruct"

logical DBFieldDef :: SetupBaseStruct (int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5 )
{

  fmcbbstr   = YES;
  SetupField(intpos,extpos,allign,max_aligned);
  
  offset_ext = extpos;
  net_pos    = netpos;
  if ( is_v5 )
    ext_length = privilege == PI_Share ? 4 : ((DBStructDef *)fmcbsmcb)->ProvideV5StructDef()->get_ext_length();
  else
    ext_length = privilege == PI_Share ? sizeof(EB_Number) : ((DBStructDef *)fmcbsmcb)->get_ext_length();
  extpos    += ext_length;
  net_length = ((DBStructDef *)fmcbsmcb)->get_net_length();
  netpos    += net_length;
  if ( !global_identity )
    global_identity = !get_extend() && ((DBStructDef *)fmcbsmcb)->get_global_identity() ? YES : NO;
  
  SetupInverse();
  return(NO);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupBaseStruct"

logical DBFieldDef :: SetupBaseStruct (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5 )
{
  DBIndex   *index;
  logical    term = NO;
BEGINSEQ
  if ( SetupType(dictptr,NO) )                       ERROR
  
  SetupIndexList();
    
  if ( index = index_list->GetTail() )
    index->SetBaseStructOrgType();       // refx
  
  SetupBaseStruct(intpos,extpos,netpos,allign,max_aligned);

RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbbptr - 
\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupBaseStruct"

logical DBFieldDef :: SetupBaseStruct (SDB_BaseStruct *dbbptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned )
{
  DBIndex   *index;
  logical    chk  = IsFilled();
  logical    term = NO;
BEGINSEQ
  Fill(dbbptr,dictptr,NO);
  delete dbbptr; 
  
  if ( chk )                                         LEAVESEQ
  
  if ( SetupType(dictptr,NO) )                       ERROR
  if ( CreateIndex() )                               ERROR
    
  if ( index = index_list->GetTail() )
    index->SetBaseStructOrgType();       // refx
  
  SetupBaseStruct(intpos,extpos,netpos,allign,max_aligned);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupField - 



\return term - Termination code

\param  intpos - 
\param  extpos - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupField"

logical DBFieldDef :: SetupField (int32 &intpos, int32 &extpos, int16 allign, int8 &max_aligned )
{

  SDBEV2(fmcbname,ID_SIZE)
  
  fmcbesu(fmcbsmcb,intpos,allign,max_aligned);
  
  if ( (fmcbrlev == R_DIRECT || fmcbrlev == R_INTERN) && get_gen_type() )
  {
    if      ( !memcmp(gen_type,"INTERVAL",8) )
      fmcbbyte *= 2;
    else if ( !memcmp(gen_type,"PI      ",8) )
      fmcbbyte  = sizeof(PropertyHandle);
    else if ( !memcmp(gen_type,"GSRT    ",8) )
      fmcbbyte  = sizeof(srt);
    else if ( !memcmp(gen_type,"DPA     ",8) )
      fmcbbyte  = sizeof(PtrArray);
    else if ( !memcmp(gen_type,"DLL     ",8) )
      fmcbbyte  = sizeof(QuList);
    else if ( !memcmp(gen_type,"DEQUE   ",8) )
      fmcbbyte  = sizeof(DEQUE(void *));
    else if ( !memcmp(gen_type,"LIST    ",8) )
      fmcbbyte  = sizeof(LIST(void *));
    else if ( !memcmp(gen_type,"QUEUE   ",8) )
      fmcbbyte  = sizeof(QUEUE(void *));
    else if ( !memcmp(gen_type,"PAIR    ",8) )
      fmcbbyte  = sizeof(PAIR(int));
    else if ( !memcmp(gen_type,"VECTOR  ",8) )
      fmcbbyte  = sizeof(VECTOR(int));
    fmcbposn    = GetAllignedPosition(intpos,allign,max_aligned);
    fmcbgentype = YES;
  }

  intpos = fmcbposn + fmcbbyte;
  return(NO);
}

/******************************************************************************/
/**
\brief  SetupIndexList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupIndexList"

logical DBFieldDef :: SetupIndexList ( )
{
  DBIndex                *index_def;
  logical                 term = NO;
  if ( !index_list )
    CreateIndex();

  index_list->GoTop();
  while ( index_def = index_list->GetNext() )
  {
    index_def->set_field_def(this);  // position may have changed
    if ( index_def->Setup() )
      term = YES;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetupIntern - 




\param  smcbptr - Pointer to general structure definition
\param  extnames - Extent name
\param  irefname - Name of inverse property
\param  indexptr - Index definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupIntern"

void DBFieldDef :: SetupIntern (smcb *smcbptr, char *extnames, char *irefname, DBIndex *indexptr )
{
  char      string[ID_SIZE+1];
  if ( smcbptr )
  {
    if ( !fmcbnsid && smcbptr->smcbnsid > 0 )
      fmcbnsid = smcbptr->smcbnsid;
    
    fmcbityp = smcbptr->smcbityp;
    if ( smcbptr->smcbstyp != ST_BASE )
      fmcbsmcb = smcbptr;
  }

  SetExtent(gvtxbts(string,extnames,ID_SIZE));
  
  memset(inverse_fname,' ',ID_SIZE);
  if ( irefname )
    gvtxstb(inverse_fname,irefname,ID_SIZE);

  if ( indexptr )
  {
    index_list->AddTail(indexptr);
    indexptr->set_field_def(this);  
  }


}

/******************************************************************************/
/**
\brief  SetupInverse - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInverse"

logical DBFieldDef :: SetupInverse ( )
{
  DBFieldDef             *invdbf;
  logical                 term = NO;
  if ( *inverse_fname != ' ' )
    if ( invdbf = ((DBStructDef *)fmcbsmcb)->GetEntry(inverse_fname) )
    {
      invdbf->set_inverse(this);
      set_inverse(invdbf);
    }
  return(term);
}

/******************************************************************************/
/**
\brief  SetupReference - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReference"

logical DBFieldDef :: SetupReference (int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5 )
{

  SetupField(intpos,extpos,allign,max_aligned);
  offset_ext = extpos;
  net_pos    = netpos;
  net_length = 0;
  if ( !fmcbtrans )
    ext_length = is_v5 ? 4 : sizeof(EB_Number);
  extpos += ext_length;
  return(NO);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReference"

logical DBFieldDef :: SetupReference (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned, logical is_v5 )
{
  logical    term = NO;
BEGINSEQ
  if ( SetupType(dictptr,YES) )                      ERROR
  
  SetupIndexList();
    
  SetupReference(intpos,extpos,netpos,allign,max_aligned);

RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbrptr - ODABA2 reference definition
\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReference"

logical DBFieldDef :: SetupReference (SDB_Reference *dbrptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, int16 allign, int8 &max_aligned )
{
  SDB_Index *dbilistptr = (SDB_Index *)dbrptr->get_ddeindx().get_nodeptr();
  int16      dbicount   = (int16)dbrptr->get_ddeprec();
  logical    chk        = IsFilled();
  logical    term       = NO;
BEGINSEQ
  Fill(dbrptr,dictptr,NO);
  delete dbrptr;
  
  if ( chk )                                         LEAVESEQ
  
  if ( SetupType(dictptr,YES) )                      ERROR
  if ( CreateIndexList(dbilistptr,dbicount) )        ERROR
  SetupReference(intpos,extpos,netpos,allign,max_aligned);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupRelation - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  old_version - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupRelation"

logical DBFieldDef :: SetupRelation (int32 &intpos, int32 &extpos, int32 &netpos, logical old_version, int16 allign, int8 &max_aligned, logical is_v5 )
{

  fmcbtrans = NO;
  SetupReference(intpos,extpos,netpos,allign,max_aligned,is_v5);
  if ( !old_version ) 
    SetupInverse();

  return(NO);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  old_version - 
\param  allign - 
\param  max_aligned - 
\param  is_v5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupRelation"

logical DBFieldDef :: SetupRelation (Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, logical old_version, int16 allign, int8 &max_aligned, logical is_v5 )
{
  logical    term = NO;
  fmcbtrans = NO; 
  SetupReference(dictptr,intpos,extpos,netpos,allign,max_aligned);
  if ( !old_version ) 
    SetupInverse();

  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbpptr - 
\param  dictptr - Dictionary handle
\param  intpos - 
\param  extpos - 
\param  netpos - 
\param  old_version - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupRelation"

logical DBFieldDef :: SetupRelation (SDB_Relationship *dbpptr, Dictionary *dictptr, int32 &intpos, int32 &extpos, int32 &netpos, logical old_version, int16 allign, int8 &max_aligned )
{
  SDB_Index *dbilistptr = (SDB_Index *)dbpptr->get_ddeindx().get_nodeptr();
  int16      dbicount   = (int16)dbpptr->get_ddeprec();
  logical    chk        = IsFilled();
  logical    term       = NO;
BEGINSEQ
  Fill(dbpptr,dictptr,NO);
  delete dbpptr;
  
  if ( chk )                                         LEAVESEQ
  
  if ( SetupType(dictptr,YES) )                      ERROR
  if ( CreateIndexList(dbilistptr,dbicount) )        ERROR
  SetupRelation(intpos,extpos,netpos,old_version,allign,max_aligned);

RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupType - 



\return term - Termination code

\param  dictptr - Dictionary handle
\param  dclopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupType"

logical DBFieldDef :: SetupType (Dictionary *dictptr, logical dclopt )
{
  smcb      *smcbptr = fmcbsmcb;
  int8       max_aligned = 1;
  logical    term    = NO;
BEGINSEQ
  if ( fmcbityp )                                    LEAVESEQ
    
  if ( !smcbptr && !(smcbptr = dictptr->GetStructDef(fmcbtype,fmcbnsid)) )
  {
    if ( !dclopt )                                 SDBERR(20)
    if ( !(smcbptr = dictptr->ProvideStructDcl(GetTypeKey())) )
                                                     ERROR
  }
  
  fmcbsmcb = smcbptr;
//  fmcbesu(smcbptr,fmcbposn,DEFAULT_ALLIGNMENT,max_aligned);

RECOVER
  SDBRESET
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateDescription - 



\return term - Termination code

\param  dbfield_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateDescription"

logical DBFieldDef :: UpdateDescription (DBFieldDef &dbfield_ref )
{
  DLL(FieldSource)      *srces   = sources;
  ExpressionReference   *cnstrnt = constraint;
  char                   fldname[ID_SIZE];
  logical                term     = NO;
  memcpy(fldname,fmcbname,ID_SIZE);
  sources = NULL;
  constraint = NULL;
    
  CopyDescription(dbfield_ref);
  
  memcpy(fmcbname,fldname,ID_SIZE);
  constraint = cnstrnt;
  sources    = srces;

  return(term);
}

/******************************************************************************/
/**
\brief  get_clst_table - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_clst_table"

logical DBFieldDef :: get_clst_table ( )
{

  return(clustered_table);

}

/******************************************************************************/
/**
\brief  get_cluster_opt - 



\return cluster_opt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_cluster_opt"

logical DBFieldDef :: get_cluster_opt ( )
{


  return(this ? cluster_opt : NO);
}

/******************************************************************************/
/**
\brief  get_create - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_create"

logical DBFieldDef :: get_create ( )
{


  return(create);
}

/******************************************************************************/
/**
\brief  get_del_empty - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_del_empty"

logical DBFieldDef :: get_del_empty ( )
{

  return(del_empty);

}

/******************************************************************************/
/**
\brief  get_depend - 



\return depend - Depending relationship

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_depend"

logical DBFieldDef :: get_depend ( )
{


  return(depend);
}

/******************************************************************************/
/**
\brief  get_dominant - 



\return dominant - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_dominant"

logical DBFieldDef :: get_dominant ( )
{


  return(dominant);
}

/******************************************************************************/
/**
\brief  get_ext_length - 



\return ext_length - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_ext_length"

int32 DBFieldDef :: get_ext_length ( )
{


  return(ext_length);
}

/******************************************************************************/
/**
\brief  get_extend - 



\return extend - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_extend"

const char *DBFieldDef :: get_extend ( )
{

  return (this ? extend : NULL);

}

/******************************************************************************/
/**
\brief  get_gen_type - 



\return gentype - Generic type of property

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_gen_type"

const char *DBFieldDef :: get_gen_type ( )
{

  return( *gen_type > ' ' ? gen_type : NULL);

}

/******************************************************************************/
/**
\brief  get_generic_type - 



\return gentype - Generic type of property

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_generic_type"

const char *DBFieldDef :: get_generic_type ( )
{

  return( this ? gen_type : NULL);

}

/******************************************************************************/
/**
\brief  get_index_list - 



\return index_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_index_list"

DBIndexList *DBFieldDef :: get_index_list ( )
{

  return(index_list);

}

/******************************************************************************/
/**
\brief  get_initval - 



\return initval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_initval"

const char *DBFieldDef :: get_initval ( )
{


  return( initval ? initval->GetString() : NULL);
}

/******************************************************************************/
/**
\brief  get_initval_expr - 



\return expref - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_initval_expr"

ExpressionReference *DBFieldDef :: get_initval_expr ( )
{


  return( initval );
}

/******************************************************************************/
/**
\brief  get_inverse - 



\return dbfield_ptr - Property definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_inverse"

DBFieldDef *DBFieldDef :: get_inverse ( )
{

  return(inverse_field);

}

/******************************************************************************/
/**
\brief  get_inverse_name - 



\return fldname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_inverse_name"

const char *DBFieldDef :: get_inverse_name ( )
{

  return( *inverse_fname > ' ' ? inverse_fname : NULL);

}

/******************************************************************************/
/**
\brief  get_is_base_coll - 



\return is_base_coll - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_is_base_coll"

logical DBFieldDef :: get_is_base_coll ( )
{

  return(is_base_coll);

}

/******************************************************************************/
/**
\brief  get_log_reference - 



\return log_referenc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_log_reference"

logical DBFieldDef :: get_log_reference ( )
{


  return(log_reference);
}

/******************************************************************************/
/**
\brief  get_mb_number - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_mb_number"

int16 DBFieldDef :: get_mb_number ( )
{

  return(mb_number);

}

/******************************************************************************/
/**
\brief  get_multikey - 



\return multikey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_multikey"

logical DBFieldDef :: get_multikey ( )
{


  return(multikey);
}

/******************************************************************************/
/**
\brief  get_net_length - 



\return instlen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_net_length"

uint32 DBFieldDef :: get_net_length ( )
{

  return(net_length);

}

/******************************************************************************/
/**
\brief  get_offset_ext - 



\return offset_ext - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_offset_ext"

int32 DBFieldDef :: get_offset_ext ( )
{


  return(offset_ext);
}

/******************************************************************************/
/**
\brief  get_owning - 



\return owning - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_owning"

logical DBFieldDef :: get_owning ( )
{


  return(owning);
}

/******************************************************************************/
/**
\brief  get_prev_field - 



\return fielddef - Internal field defintion

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_prev_field"

DBFieldDef *DBFieldDef :: get_prev_field ( )
{

  return ( prev_field );

}

/******************************************************************************/
/**
\brief  get_privilege - 



\return privilege - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_privilege"

PIADEF DBFieldDef :: get_privilege ( )
{


  return(privilege);
}

/******************************************************************************/
/**
\brief  get_resource - 



\return resource - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_resource"

DBResource *DBFieldDef :: get_resource ( )
{


  return(resource);
}

/******************************************************************************/
/**
\brief  get_sec_reference - 



\return sec_referenc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_sec_reference"

logical DBFieldDef :: get_sec_reference ( )
{


  return(sec_reference);
}

/******************************************************************************/
/**
\brief  get_shared - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_shared"

logical DBFieldDef :: get_shared ( )
{

  return(shared);

}

/******************************************************************************/
/**
\brief  get_static - 



\return stat_opt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_static"

logical DBFieldDef :: get_static ( )
{


  return(static_field);
}

/******************************************************************************/
/**
\brief  get_transient - 



\return transopt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_transient"

logical DBFieldDef :: get_transient ( )
{

  return(fmcbtrans);

}

/******************************************************************************/
/**
\brief  get_update - 



\return update - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_update"

logical DBFieldDef :: get_update ( )
{


  return(update);
}

/******************************************************************************/
/**
\brief  get_version - 



\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_version"

int16 DBFieldDef :: get_version ( )
{


  return(version);
}

/******************************************************************************/
/**
\brief  get_virtual - 



\return virtopt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_virtual"

logical DBFieldDef :: get_virtual ( )
{


  return(virtual_field);
}

/******************************************************************************/
/**
\brief  get_weak_typed - 



\return weak_typed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_weak_typed"

logical DBFieldDef :: get_weak_typed ( )
{


  return(this ? week_typed : NO);
}

/******************************************************************************/
/**
\brief  operator= - 



\return term - Termination code

\param  dbfield_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

logical DBFieldDef :: operator= (DBFieldDef &dbfield_ref )
{

  CopyDescription(dbfield_ref);
  return(NO);
}

/******************************************************************************/
/**
\brief  set_by_reference - 




\param  log_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_by_reference"

void DBFieldDef :: set_by_reference (logical log_ref )
{

  by_reference = log_ref;

}

/******************************************************************************/
/**
\brief  set_clst_table - 




\param  clustopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_clst_table"

void DBFieldDef :: set_clst_table (logical clustopt )
{

  clustered_table = clustopt;

}

/******************************************************************************/
/**
\brief  set_cluster_opt - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_cluster_opt"

void DBFieldDef :: set_cluster_opt (logical option )
{

  cluster_opt = option;

}

/******************************************************************************/
/**
\brief  set_constraint - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  init_string - 
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_constraint"

logical DBFieldDef :: set_constraint (char *init_string, int32 string_len )
{

  return(SetExpressionRef(&constraint,init_string,string_len));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  exprref_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_constraint"

logical DBFieldDef :: set_constraint (ExpressionReference *exprref_ptr )
{

  return(SetExpressionRef(&constraint,exprref_ptr));

}

/******************************************************************************/
/**
\brief  set_create - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_create"

void DBFieldDef :: set_create (logical option )
{

  create = option;

}

/******************************************************************************/
/**
\brief  set_del_empty - 




\param  del_empty_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_del_empty"

void DBFieldDef :: set_del_empty (logical del_empty_opt )
{

  global_identity = del_empty_opt;

}

/******************************************************************************/
/**
\brief  set_depend - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_depend"

void DBFieldDef :: set_depend (logical option )
{

  depend = option;

}

/******************************************************************************/
/**
\brief  set_dominant - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_dominant"

void DBFieldDef :: set_dominant (logical option )
{

  dominant = option;

}

/******************************************************************************/
/**
\brief  set_ext_length - 




\param  length - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ext_length"

void DBFieldDef :: set_ext_length (int32 length )
{

  ext_length = length;

}

/******************************************************************************/
/**
\brief  set_gen_type - 




\param  gtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_gen_type"

void DBFieldDef :: set_gen_type (char *gtype )
{

  if ( gtype )
    gvtxstb(gen_type,gtype,sizeof(gen_type));
  else
    memset(gen_type,' ',sizeof(gen_type));

}

/******************************************************************************/
/**
\brief  set_global_identity - 




\param  guid_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_global_identity"

void DBFieldDef :: set_global_identity (logical guid_opt )
{

  global_identity = guid_opt;

}

/******************************************************************************/
/**
\brief  set_index_list - 




\param  indxlst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_index_list"

void DBFieldDef :: set_index_list (DBIndexList *indxlst )
{

  ILock(YES);
  
  if ( index_list && index_list != indxlst )
  {
    index_list->Release();
    if ( index_list = indxlst )
      index_list->Reserve();
  }

  IUnlock();


}

/******************************************************************************/
/**
\brief  set_initval - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  init_string - 
\param  string_len - String length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_initval"

logical DBFieldDef :: set_initval (char *init_string, int32 string_len )
{

  return(SetExpressionRef(&initval,init_string,string_len));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  exprref_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_initval"

logical DBFieldDef :: set_initval (ExpressionReference *exprref_ptr )
{

  return(SetExpressionRef(&initval,exprref_ptr));


}

/******************************************************************************/
/**
\brief  set_inverse_name - 




\param  inv_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_inverse_name"

void DBFieldDef :: set_inverse_name (char *inv_name )
{

  if ( inv_name )
    gvtxstb(inverse_fname,inv_name,sizeof(inverse_fname));
  else
    memset(inverse_fname,' ',sizeof(inverse_fname));

}

/******************************************************************************/
/**
\brief  set_is_base_coll - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_is_base_coll"

void DBFieldDef :: set_is_base_coll (logical option )
{

  is_base_coll = option;

}

/******************************************************************************/
/**
\brief  set_log_reference - 




\param  log_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_log_reference"

void DBFieldDef :: set_log_reference (logical log_ref )
{

  log_reference = log_ref;

}

/******************************************************************************/
/**
\brief  set_multikey - 




\param  multi_key - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_multikey"

void DBFieldDef :: set_multikey (logical multi_key )
{

  multikey = multi_key;

}

/******************************************************************************/
/**
\brief  set_net_length - 




\param  netlength - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_net_length"

void DBFieldDef :: set_net_length (uint32 netlength )
{

  net_length = netlength;

}

/******************************************************************************/
/**
\brief  set_net_pos - 




\param  position - Position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_net_pos"

void DBFieldDef :: set_net_pos (int32 position )
{

  net_pos = position;

}

/******************************************************************************/
/**
\brief  set_offset_ext - 




\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_offset_ext"

void DBFieldDef :: set_offset_ext (int32 offset )
{

  offset_ext = offset;

}

/******************************************************************************/
/**
\brief  set_owning - 




\param  own_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_owning"

void DBFieldDef :: set_owning (logical own_opt )
{

  owning = own_opt;

}

/******************************************************************************/
/**
\brief  set_prev_field - 




\param  dbfield_ptr - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_prev_field"

void DBFieldDef :: set_prev_field (DBFieldDef *dbfield_ptr )
{

  prev_field = dbfield_ptr;

}

/******************************************************************************/
/**
\brief  set_privilege - 




\param  accss_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_privilege"

void DBFieldDef :: set_privilege (PIADEF accss_opt )
{

  privilege = accss_opt;

}

/******************************************************************************/
/**
\brief  set_resource - 




\param  resptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_resource"

void DBFieldDef :: set_resource (DBResource *resptr )
{

  if ( resource && resource != resptr )
    delete resource;
  resource = resptr;

}

/******************************************************************************/
/**
\brief  set_sec_reference - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_sec_reference"

void DBFieldDef :: set_sec_reference (logical option )
{

  sec_reference = option;

}

/******************************************************************************/
/**
\brief  set_set_operation - 




\param  int_option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_set_operation"

void DBFieldDef :: set_set_operation (int8 int_option )
{

  set_operation = int_option;

}

/******************************************************************************/
/**
\brief  set_shared - 




\param  shared_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_shared"

void DBFieldDef :: set_shared (logical shared_opt )
{

  shared = shared_opt;

}

/******************************************************************************/
/**
\brief  set_transient - 




\param  transient_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_transient"

void DBFieldDef :: set_transient (logical transient_opt )
{

  fmcbtrans = transient_opt;

}

/******************************************************************************/
/**
\brief  set_update - 




\param  update_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_update"

void DBFieldDef :: set_update (logical update_opt )
{

  update = update_opt;

}

/******************************************************************************/
/**
\brief  set_version - 




\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_version"

void DBFieldDef :: set_version (uint16 version_nr )
{

  version = version_nr;

}

/******************************************************************************/
/**
\brief  set_virtual - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_virtual"

void DBFieldDef :: set_virtual (logical option )
{

  virtual_field = option;

}

/******************************************************************************/
/**
\brief  set_weak_typed - 




\param  option - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_weak_typed"

void DBFieldDef :: set_weak_typed (logical option )
{

  week_typed = option;

}

/******************************************************************************/
/**
\brief  ~DBFieldDef - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBFieldDef"

     DBFieldDef :: ~DBFieldDef ( )
{

  Remove();

}


