/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    Dictionary

\brief    Dictionary
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/08/30 18:50:21,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Dictionary"

#include  <popa7.h>
#include  <coctp.h>
#include  <cparser.h>
#include  <ifil.h>
#ifndef   DLL_DBHandle_HPP
#define   DLL_DBHandle_HPP
#include  <sDBHandle.hpp>
#include  <sDLL.h>
#endif
#ifndef   GSRT_OBH_ListEntry_HPP
#define   GSRT_OBH_ListEntry_HPP
#include  <sOBH_ListEntry.hpp>
#include  <sGSRT.h>
#endif
#ifndef   DLL_OPDecl_HPP
#define   DLL_OPDecl_HPP
#include  <sOPDecl.hpp>
#include  <sDLL.h>
#endif
#include  <cMethodTypes.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sBNFParser.hpp>
#include  <sBNF_OSI.hpp>
#include  <sCDictionary.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDBViewStructDef.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDictionary.hpp>
#include  <sENUM_Value.hpp>
#include  <sExpressionReference.hpp>
#include  <sLDictionary.hpp>
#include  <sOPAccessPathDecl.hpp>
#include  <sOPDecl.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOPFunctionDecl.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sRessourceLock.hpp>
#include  <sSDB_Attribute.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Key.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#include  <sStructDef.hpp>
#include  <sSystemDict.hpp>
#include  <spc_SDB_Value.hpp>
#include  <spc_SDB_ValueList.hpp>
#include  <stim.hpp>
#include  <sDictionary.hpp>


/******************************************************************************/
/**
\brief  AddExpression - 



\return term - Termination code

\param  strdef - Structure definition
\param  expr_decl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExpression"

logical Dictionary :: AddExpression (DBStructDef *strdef, OPDecl *expr_decl )
{
  logical              term = NO;
BEGINSEQ
  ILock(YES);
  
// do not add local expressions, duplicate name '__inline_expression__'
  if ( !expr_decl->IsExpression() || expr_decl->IsInline() )
                                                    LEAVESEQ
  SDBEV1(expr_decl->get_opname(),UNDEF);
  if ( strdef )
  {
    ParmList     *parmlist = expr_decl->CreatPrototypeParmList();
    strdef->AddExpression(expr_decl,parmlist);  
    delete parmlist;
  }
  else
  {
    if ( GetExpression(NULL,expr_decl->get_opname(),NULL) )
                                                     SDBERR(379)
    if ( !expression_list )
      expression_list = new DLL(OPDecl);
                                                       
    expression_list->AddTail(expr_decl);
  }
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  AddExtendDef - 




\param  db_ext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExtendDef"

void Dictionary :: AddExtendDef (DBExtend *db_ext )
{

  if ( this && db_ext ) 
  {
    ILock(YES);
    extdef_list.Insert(db_ext);
    IUnlock();
  }


}

/******************************************************************************/
/**
\brief  AddHandle - 




\param  dbh_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHandle"

void Dictionary :: AddHandle (DBHandle *dbh_ptr )
{

  ILock(YES);
  
  handle_list->AddTail(dbh_ptr);

  IUnlock();


}

/******************************************************************************/
/**
\brief  BaseType - Is type a base type



\return ityp - Internal structure number

\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BaseType"

int32 Dictionary :: BaseType (char *strnames )
{
  char           string[65];
  DBObjectHandle dbo(this);
  int32          ityp = UNDEF;
BEGINSEQ
  ILock(YES);
  
  PropertyHandle   datatypes(dbo,"DataTypes",PI_Read); SDBCERR
  
  if ( !datatypes.Get(strnames) )                      ERROR
  ityp = datatypes.GetInt("code"); 

RECOVER
  ityp = 0;
ENDSEQ
  IUnlock();
  return(-ityp);
}

/******************************************************************************/
/**
\brief  CheckExpression - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  resobj - 
\param  clsnames - 
\param  exprnames - 
\param  w_implnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical Dictionary :: CheckExpression (ACObject *resobj, char *clsnames, char *exprnames, char *w_implnames )
{
  PropertyHandle  *meth_ph = NULL;
  PropertyHandle  *impl_ph = NULL;
  char             name[ID_SIZE];
  logical          term = NO;
BEGINSEQ
  ILock(YES);
  
  SDBEV1(clsnames,ID_SIZE)
  SDBEV2(exprnames,ID_SIZE)
  
  DBObjectHandle   temp_object(resobj ? resobj : this);
  PropertyHandle   cls_ph(temp_object,"ODC_ImpClass",PI_Read);
                                                     SDBCERR
  TypeKey     tkey(this,clsnames);
  if ( !cls_ph(tkey.GetKey()) )                      SDBERR(188)
  meth_ph = cls_ph.GPH("pfunctions");  
  if ( !meth_ph->Get(gvtxstb(name,exprnames,ID_SIZE)) ) 
                                                     SDBERR(167)
  impl_ph = meth_ph->GPH("implementations");
  
  if ( w_implnames && *w_implnames )
    impl_ph->Get(gvtxstb(name,w_implnames,ID_SIZE));
  else
    impl_ph->Get(0L);
  if ( !impl_ph->Exist() )                           SDBERR(167)
  
  OPExpressionDecl exp_dcl(this,NULL,NULL,impl_ph);  SDBCERR
                                                     OQLCERR
  if ( exp_dcl.Initialize(-1) )                      ERROR

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  expression - Expression
\param  obhandle - Database Object handle
\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExpression"

logical Dictionary :: CheckExpression (char *expression, ACObject *obhandle, char *clsnames )
{
  logical    term = NO;
BEGINSEQ
  SDBEV1(clsnames,ID_SIZE)
  SDBEV2(expression,UNDEF)

  OPExpressionDecl exp_dcl(this,NULL,obhandle,NULL,NULL,expression);
// clsnames in einem zu konstr. co oder fielddef ?
                                                     SDBCERR
  if ( OQLERROR )                                    SDBERR(OQL_ERROR)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckExtendDef - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  extname - Extent name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtendDef"

logical Dictionary :: CheckExtendDef (char *extname, int32 nsid )
{
  TypeKey      tkey(extname,nsid);

  return( CheckExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtendDef"

logical Dictionary :: CheckExtendDef (TypeKey &tkey )
{
  logical         term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  ILock(YES);
  
  if ( extdef_list.Get(tkey,tkey.Exact()) )          LEAVESEQ

  if ( extend_pi->Get(tkey.GetKey()) || 
       refr_pi->Get(tkey.GetKey())   || 
       codeset_pi->Get(tkey.GetKey())  )             LEAVESEQ
                                                    
  ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( this )
    IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtendDef"

logical Dictionary :: CheckExtendDef (char *scoped_name )
{
  TypeKey      tkey(this,scoped_name);
  return( CheckExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  CheckValueSet - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  extname - Extent name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValueSet"

logical Dictionary :: CheckValueSet (char *extname, int32 nsid )
{
  TypeKey      tkey(extname,nsid);

  return( CheckExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValueSet"

logical Dictionary :: CheckValueSet (TypeKey &tkey )
{
  DBStructDef    *strdef = NULL;
  logical         term   = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  ILock(YES);
  
  if ( !(strdef = ProvideStructDef(tkey)) )          ERROR

  if ( strdef->smcbstyp != ST_CODE )                 ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( this )
    IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValueSet"

logical Dictionary :: CheckValueSet (char *scoped_name )
{
  TypeKey      tkey(this,scoped_name);
  return( CheckExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  CloseDictionary - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDictionary"

void Dictionary :: CloseDictionary ( )
{
  DBHandle      *dbhandle;
  StructDef     *structdef;
  DBExtend      *extdef;
  int16          count = 0;
  OBH_ListEntry *obh_entry;
  if ( handle_list )
  {
    while ( dbhandle = handle_list->RemoveTail() )
      delete dbhandle;
    delete handle_list;
  }
  handle_list = NULL;
  
  CloseNamespace();
  ClosePIs();
    
  if ( obh_list && (count = obh_list->GetCount()) )
    while ( count > 0 ) 
    {
      obh_entry = obh_list->GetEntry(count--);
      if ( obh_entry->get_ob_handle() != (ACObject *)this ) // ACObject of this dictionary
        delete obh_entry->get_ob_handle();
    }
  delete obh_list;
  obh_list = NULL;
  
  CloseDBHandle();

  if ( extdef_tree )
  {
    while ( extdef = extdef_list.RemoveTail() )
      delete extdef;
    delete extdef_tree;
  }
  extdef_tree = NULL;
  
  if ( structure_tree )
  {
    while ( structdef = structure_list.RemoveTail() )
      delete structdef;
    delete structure_tree;
  }
  structure_tree = NULL;
    
  dictionary = NULL;


}

/******************************************************************************/
/**
\brief  ClosePIs - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClosePIs"

logical Dictionary :: ClosePIs ( )
{
  logical                 term = NO;
  delete refr_pi;
  refr_pi = NULL;
  delete extend_pi;
  extend_pi = NULL;
  delete struct_pi;
  struct_pi = NULL;
  delete codeset_pi;
  codeset_pi = NULL;
  delete type_pi;
  type_pi = NULL;
  delete view_pi;
  view_pi = NULL;
  delete viewext_pi;
  viewext_pi = NULL;


  return(term);
}

/******************************************************************************/
/**
\brief  CopyCodeset - Copy enumeration



\return term - Termination code

\param  srcedict - Source dictionary
\param  tkey_d - 
\param  nkey_d - 
\param  db_replace - Replace option
\param  retainSID - Retain internal type numbers
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyCodeset"

logical Dictionary :: CopyCodeset (Dictionary *srcedict, TypeKey tkey_d, TypeKey nkey_d, PIREPL db_replace, logical retainSID, logical retain_schemav )
{
  PropertyHandle  *srce_pi = srcedict->get_codeset_pi();
  int16            sid;
  Instance         instance;
  int16            indx0 = 0;
  char             string[512];
  logical          term = NO;
BEGINSEQ
  PropertyHandle targ_pi(*GetDBObjectHandle(),"SDB_ValueList",PI_Write);
                                                     SDBCERR
  SDBEV1(tkey_d.Name(),ID_SIZE)
  SDBEV2(nkey_d.Name(),ID_SIZE)
  
  if ( !srce_pi->Get(tkey_d.GetKey()) )              SDBERR(85)
  if ( struct_pi->Get(nkey_d.GetKey()) )             SDBERR(128)
  
  if ( targ_pi(nkey_d.GetKey()) ) 
  {
    if ( db_replace == REPL_none )                   LEAVESEQ
//    sid = targ_pi->get_itype();
  }
  else
  {
    if ( retainSID )
    {
      srce_pi->Get(tkey_d.GetKey());
      if ( SetupTypeID(sid = srce_pi->GetInt("itype")) ) 
                                                     ERROR
    }
    else
      if ( !(sid = GetNewTypeID()) )                 ERROR
    if ( !targ_pi.Add(nkey_d.GetKey()) )             ERROR

    if ( !targ_pi.Copy(*srce_pi,nkey_d.GetKey(),REPL_local,REPL_all) )   
                                                     ERROR
    pc_SDB_Value  pc_targ_values(targ_pi.GPH("values"));
    pc_targ_values.SetupCopySet(srce_pi->GPH("values"));

//    if ( targ_pi.GetStructDef()->CopyInstance(targ_pi.Get().GetArea(),srce_pi->GetStructDef(),
//                                              srce_pi->Get(tkey_d.GetKey()).GetArea(),REPL_local,UNDEF) )    
//                                                     SDBERR(99)
    *targ_pi.GPH("itype") = sid;
    targ_pi.Modify();                                  
    targ_pi.Save();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyExtentDef - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  srcedict - Source dictionary
\param  tkey - 
\param  nkey - 
\param  targ_struct - Target type
\param  transaction - Transaction option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtentDef"

logical Dictionary :: CopyExtentDef (Dictionary *srcedict, TypeKey &tkey, TypeKey &nkey, char *targ_struct, logical transaction )
{
  PropertyHandle   *srce_pi = srcedict->get_extend_pi();
  TypeKey           tstructkey(targ_struct,tkey.GetID());
  logical           term = NO;
BEGINSEQ
  if ( transaction )
    StartTAIntern(NO,YES,AUTO);
    
  PropertyHandle targ_pi(*GetDBObjectHandle(),"SDB_Extend",PI_Write);
                                                     SDBCERR
  SDBEV1(tkey.Name(),ID_SIZE)
  
  if ( !srce_pi->Get(tkey.GetKey()) )     
  {
    if ( ProvideExtendDef(tkey) )                    LEAVESEQ
    SDBERR(68)
  }
  
  if ( CopyExtentDef(targ_pi,*srce_pi,tkey,tstructkey) )
                                                     ERROR
  

RECOVER
  term = YES;
ENDSEQ
  if ( transaction )
    StopTA(AUTO,term);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  text_ph - 
\param  sext_ph - 
\param  nkey_d - 
\param  tstructkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyExtentDef"

logical Dictionary :: CopyExtentDef (PropertyHandle &text_ph, PropertyHandle &sext_ph, TypeKey nkey_d, TypeKey &tstructkey )
{
  int32             indx0 = 0;
  char             *srce_struct;
  char             *srce_ext;
  logical           term = NO;
BEGINSEQ
  PropertyHandle     ext_ph(*GetDBObjectHandle(),"SDB_Extend",PI_Read);
                                                     SDBCERR
  PropertyHandle     ssys_ident(&sext_ph,"sys_ident");
  PropertyHandle     sddetype(&sext_ph,"ddetype");
  PropertyHandle     ssexbase(&sext_ph,"sexbase");
  PropertyHandle     tsexbase(&text_ph,"sexbase");
  
  PropertyHandle     ddetype(&ext_ph,"ddetype");
    
  SDBEV2(nkey_d.Name(),ID_SIZE)
  
  srce_struct = sddetype.GetArea();
  srce_ext = ssys_ident.GetArea();
  if ( *tstructkey.Name() <= ' ' ) 
    tstructkey.SetName(srce_struct);
  
  if ( !memcmp(srce_ext,srce_struct,ID_SIZE) && nkey_d != tstructkey )
                                                     SDBERR(125)
  memcpy(srce_struct,tstructkey.Name(),ID_SIZE);
  if ( ssys_ident == sddetype ) 
    memcpy(srce_ext,tstructkey.Name(),ID_SIZE);
  
  if ( ext_ph(ssys_ident) )                          LEAVESEQ
    
  if ( !text_ph.Copy(sext_ph,nkey_d.GetKey(),REPL_local) )      
                                                     ERROR
  while ( ssexbase(indx0++) )
    CopyExtentDef(tsexbase,ssexbase,nkey_d,tstructkey);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyMemberType - 



\return term - Termination code

\param  srcedict - Source dictionary
\param  memb_pi - 
\param  nkey_d - 
\param  topname - Name of top-type
\param  db_replace - Replace option
\param  retainSID - Retain internal type numbers
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyMemberType"

logical Dictionary :: CopyMemberType (Dictionary *srcedict, PropertyHandle *memb_pi, TypeKey nkey_d, char *topname, PIREPL db_replace, logical retainSID, logical retain_schemav )
{
  DictionaryHandle *sysdict;
  DBStructDef      *strdefptr;
  char             *extref;
  char             *datatype;
  logical           term = NO;
BEGINSEQ
  PH(memb_pi,ddetype)
  datatype = ddetype.GetArea();
  TypeKey  tkey(this,memb_pi->GetString("scope"),datatype);
  
  if ( sysdict = &GetSystemDictionary() )
  {
    if ( sysdict->BaseType(datatype) )               LEAVESEQ
  }
  else
  {
    if ( (strdefptr = GetStructDef(tkey)) && strdefptr->smcbityp < 0 )
                                                     LEAVESEQ
  }
  if ( tkey == topname )
  {
    ddetype = nkey_d.Name();
    memb_pi->Save();
  }
  else      
    if ( CopyType(srcedict,tkey,nkey_d,topname,db_replace,retainSID,retain_schemav) )
                                                     ERROR
  if ( (memb_pi->IsA("SDB_Relationship") || memb_pi->IsA("SDB_BaseStruct")) &&
       (extref = memb_pi->GetArea("ddeext"))                                &&
       *extref && *extref != ' ' && *extref != '*' && *extref != '.'    )
  {
    TypeKey    text(this,extref);
    TypeKey    next(text != topname ? text.Name() : nkey_d.Name(),text.GetID());
    if ( CopyExtentDef(srcedict,text,next,datatype) )
                                                     SDBCERR
  }
RECOVER
  SDBError().DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyStructure - Copy structure definition



\return term - Termination code

\param  srcedict - Source dictionary
\param  tkey_d - 
\param  nkey_d - 
\param  topname - Name of top-type
\param  db_replace - Replace option
\param  retainSID - Retain internal type numbers
\param  retain_schemav - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyStructure"

logical Dictionary :: CopyStructure (Dictionary *srcedict, TypeKey tkey_d, TypeKey nkey_d, char *topname, PIREPL db_replace, logical retainSID, logical retain_schemav )
{
  PropertyHandle     srce_pi;
  logical            reserved = srcedict->Reserve_struct_pi(srce_pi);
  PropertyHandle    *memb_pi;
  int32              indx0;
  int16              sid;
  logical            term = NO;
BEGINSEQ
  PropertyHandle     targ_pi(*GetDBObjectHandle(),"SDB_Structure",PI_Write);
                                                     SDBCERR
  PropertyHandle     tversion(targ_pi.GPH("version"));
  PropertyHandle     titype(targ_pi.GPH("itype"));
  PropertyHandle     tsys_ident(targ_pi.GPH("sys_ident"));
  PropertyHandle     tsmceodaba(targ_pi.GPH("smceodaba"));
  
  PropertyHandle     sversion(srce_pi.GPH("version"));
  PropertyHandle     sitype(srce_pi.GPH("itype"));
  PropertyHandle     ssmceodaba(srce_pi.GPH("smceodaba"));
  
  TypeKey     tempkey(nkey_d);
  if ( tkey_d.Name() != topname )
    tempkey.SetName(tkey_d.Name());
  SDBEV1(tkey_d.Name(),ID_SIZE)
  SDBEV2(tempkey.Name(),ID_SIZE)
  if ( !srce_pi.Get(tkey_d.GetKey()) )               SDBERR(20)
  if ( codeset_pi->Get(tempkey.GetKey()) )           SDBERR(130)
  
  sid = sitype.GetInt();
  if ( targ_pi(tempkey.GetKey()) )
  {
    if ( db_replace == REPL_none )                   LEAVESEQ
    if ( retainSID )                                 SDBERR(99)
    if ( targ_pi.IsTrue("ready") )                   SDBERR(131)
    if ( targ_pi.GetInt("access_type") != srce_pi.GetInt("access_type") )
                                                     SDBERR(132)
    if ( titype.GetInt() )
    {
       if ( titype != sitype )                       SDBERR(133)
       if ( tversion > sversion )                    SDBERR(134)
    }
    sid = titype.GetInt();
  }
  else
  {
    if ( !retainSID )
      sid = UNDEF;
    else
      if ( SetupTypeID(sid) )                        ERROR
    if ( !targ_pi.Add(tempkey.GetKey()) )            ERROR
  }
  
  if ( !targ_pi.Copy(srce_pi,tempkey.GetKey(),REPL_local,REPL_all) )   
                                                     ERROR
  tsys_ident = tempkey.Name();
  if ( !retainSID )
  {
    if ( !sid && targ_pi.GetInt("smcestyp") )
      if ( !(sid = GetNewTypeID()) )                   ERROR
    titype = sid;
//    targ_inst->Reset(); nacfolgende Zeilen aus SDB_Structure ¸bernommen
    *targ_pi.GPH("checked")  = NO;
    *targ_pi.GPH("ready")    = NO;
    *targ_pi.GPH("modified") = YES;
    if ( targ_pi.GetInt("itype") && targ_pi.GetInt("version") )
    {
      tversion = 0;
      SDBRESET
    }
  }
  else if ( !retain_schemav )
    tversion = 0;   // wenn alles kopiert wird, wird die Version zur¸ckgesetzt 
      
  if ( tversion.GetInt() > last_schemav )
    last_schemav = tversion.GetInt();
    
  targ_pi.Modify();
  targ_pi.Save();                                    SDBCERR
  
  if ( db_replace != REPL_all )
    db_replace = REPL_none;
  
  indx0 = 0;
  memb_pi = targ_pi.GPH("smcebase");
  while ( memb_pi->Get(indx0++) )
    if ( CopyMemberType(srcedict,memb_pi,nkey_d,topname,db_replace,retainSID,retain_schemav) )
                                                     ERROR
  indx0 = 0;
  memb_pi = targ_pi.GPH("smcepdde");
  while ( memb_pi->Get(indx0++) )
    if ( CopyMemberType(srcedict,memb_pi,nkey_d,topname,db_replace,retainSID,retain_schemav) )
                                                     ERROR
  indx0 = 0;
  memb_pi = targ_pi.GPH("smcepref");
  while ( memb_pi->Get(indx0++) )
    if ( CopyMemberType(srcedict,memb_pi,nkey_d,topname,db_replace,retainSID,retain_schemav) )
                                                     ERROR
  indx0 = 0;
  memb_pi = targ_pi.GPH("smcershp");
  while ( memb_pi->Get(indx0++) )
    if ( CopyMemberType(srcedict,memb_pi,nkey_d,topname,db_replace,retainSID,retain_schemav) )
                                                     ERROR
  targ_pi.Save();

// inhaltliches Pr¸fen der Structure
RECOVER
  term = YES;
ENDSEQ
  srcedict->Release_struct_pi(reserved);
  return(term);
}

/******************************************************************************/
/**
\brief  CopyToODABAStr - 



\return term - Termination code

\param  pers_pi - 
\param  ext_pi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyToODABAStr"

logical Dictionary :: CopyToODABAStr (PropertyHandle &pers_pi, PropertyHandle &ext_pi )
{
  int32             indx0 = 0;
  logical           term = NO;
BEGINSEQ
  PropertyHandle psys_ident(pers_pi.GPH("sys_ident"));
  
  PropertyHandle eddetype(ext_pi.GPH("ddetype"));
  PropertyHandle esys_ident(ext_pi.GPH("sys_ident"));
  
  if ( eddetype != psys_ident )
  {
    if ( eddetype != esys_ident )
      eddetype = psys_ident;
  }
  
  pers_pi.GPH("smceextd")->Provide(esys_ident);      SDBCERR
  
  PH(ext_pi,sexbase)
  while ( sexbase(indx0++) )
    if ( CopyToODABAStr(pers_pi,sexbase) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyType - Copy type definition



\return term - Termination code

\param  srcedict - Source dictionary
\param  tkey_d - 
\param  nkey_d - 
\param  topname - Name of top-type
\param  db_replace - Replace option
\param  retainSID - Retain internal type numbers
\param  retain_schemav - 
\param  transaction - Transaction option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyType"

logical Dictionary :: CopyType (Dictionary *srcedict, TypeKey tkey_d, TypeKey nkey_d, char *topname, PIREPL db_replace, logical retainSID, logical retain_schemav, logical transaction )
{
  logical            is_struct;
  PropertyHandle     source_pi;
  logical            reserved;
  logical            term = NO;
BEGINSEQ
  if ( *tkey_d.Name() <= ' ' )                       LEAVESEQ
    
  if ( transaction )
    StartTAIntern(NO,NO,AUTO);
    
  reserved = srcedict->Reserve_struct_pi(source_pi);  
  is_struct = source_pi.Get(tkey_d.Name()) ? YES : NO;
  srcedict->Release_struct_pi(reserved);
  
  if ( is_struct )
  {
    if ( CopyStructure(srcedict,tkey_d,nkey_d,topname,db_replace,retainSID,retain_schemav) )
                                                     ERROR
  }
  else if ( srcedict->get_codeset_pi()->Get(tkey_d.GetKey()) )
  {
    if ( tkey_d != topname )
      nkey_d.SetName(tkey_d.Name());
    if ( CopyCodeset(srcedict,tkey_d,nkey_d,db_replace,retainSID,retain_schemav) )    
                                                     ERROR
  }
  else
  {                   
    SDBEV1(tkey_d.Name(),ID_SIZE)                       SDBERR(20)
  }
RECOVER
  term = YES;
ENDSEQ
  if ( transaction )
    StopTA(AUTO,term);
  return(term);
}

/******************************************************************************/
/**
\brief  CreateDBHandle - 



\return dbhandle - Database handle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBHandle"

DBHandle *Dictionary :: CreateDBHandle (char *cpath, PIACC accopt, logical netopt, uint16 version_nr, char sysenv )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBHandle"

DBHandle *Dictionary :: CreateDBHandle ( )
{

  return(new DBHandle());

}

/******************************************************************************/
/**
\brief  i2 - 



\param  cpath - Complete path
\param  lowEBN - First entry number in database
\param  highEBN - Last entry number in database
\param  dasize - Size of data area in byte
\param  largedb - Indicates a large database
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBHandle"

DBHandle *Dictionary :: CreateDBHandle (char *cpath, int16 lowEBN, int16 highEBN, int32 dasize, logical largedb )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  CreateEnum - Create new enumeration



\return term - Termination code

\param  enum_name - Enumeration name
\param  basetype - Base type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEnum"

logical Dictionary :: CreateEnum (char *enum_name, char *basetype )
{
  TypeKey      tkey(this,enum_name);
  TypeKey      bkey(this,basetype);
  char         scope[256];
  logical      term = NO;
BEGINSEQ

  pc_SDB_ValueList  vl_pc(codeset_pi);
  vl_pc.Provide(tkey.GetKey());                           SDBCERR
  vl_pc.Initialize(bkey.Name(),bkey.Scope(this,scope,sizeof(scope)-1));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExtentDef - 



\return dbextdef - Extent definition

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExtentDef"

DBExtend *Dictionary :: CreateExtentDef (TypeKey &tkey )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  CreateGlobalVariable - 



\return prophdl - 

\param  prophdl_ref - Reference to Property handle
\param  var_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGlobalVariable"

PropertyHandle *Dictionary :: CreateGlobalVariable (PropertyHandle &prophdl_ref, char *var_name )
{
  PropertyHandle           *ph = NULL;
  ParmList                 *global_vars;
  char                      vname[ID_SIZE];
BEGINSEQ
  if ( !(global_vars = (ParmList *)GetOPAProcessVariable(PVN_GlobalVariables)) )
                                                     SDBERR(99)
  if ( !prophdl_ref.IsValid() )                      ERROR
  
  if ( var_name && *var_name )
    gvtxstb(vname,var_name,ID_SIZE);
  else
    memcpy(vname,prophdl_ref.GetFieldDef()->fmcbname,ID_SIZE);
  
  if ( global_vars->Get(vname) )                     SDBERR(376)
  
  if ( var_name && *var_name )
    prophdl_ref.GetNode()->RenameHandle(var_name);

  global_vars->AddParm(&prophdl_ref);
  if ( !(ph = global_vars->Get(vname)) )             SDBERR(99)

RECOVER

ENDSEQ
  return(ph);
}

/******************************************************************************/
/**
\brief  CreateParser - 



\return parser - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateParser"

BNFParser *Dictionary :: CreateParser ( )
{

  return(new BNF_OSI(NULL));


}

/******************************************************************************/
/**
\brief  CreateStructDef - 



\return structdef - 

\param  tkey - 
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStructDef"

DBStructDef *Dictionary :: CreateStructDef (TypeKey &tkey, DBStructDef *strdef )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  CreateTempExtent - Create temporary extent



\return extnames - Extent name
-------------------------------------------------------------------------------
\brief  i0 - 



\param  strnames - Type name
\param  extnames_w - Extent name
\param  key_name_w - 
\param  baseexts_w - 
\param  weak_opt_w - 
\param  own_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *Dictionary :: CreateTempExtent (char *strnames, char *extnames_w, char *key_name_w, char *baseexts_w, logical weak_opt_w, logical own_opt_w )
{
  DBStructDef            *strdef    = NULL;
  DBIndex                *dbindex   = NULL;
  DBExtend               *dbext     = NULL;
  DBExtend               *extdef    = NULL;
  kcb                    *kcbptr    = NULL;
  char                    string[ID_SIZE+1];
  logical                 trans_opt = NO;
  logical                 term      = NO;
BEGINSEQ
  ILock(YES);
  if ( !(trans_opt = DBStructDef::IsViewPath(strnames)) )
  {
    SDBEV1(strnames,ID_SIZE)
    if ( !(strdef  = ProvideStructDef(strnames)) )   SDBERR(20)
  }
  
  *string = 0;
  if ( !extnames_w )
    extnames_w = string;
  extnames_w = GetTempName(extnames_w);
  
  if ( !strdef ) // for simple view pathes like "a.b,c"
  {
    SDBEV1(strnames,UNDEF)
    if ( !(strdef  = CreateTempStruct(NULL,strnames,extnames_w)) )
                                                     SDBERR(20)
  }

  SDBEV2(key_name_w,ID_SIZE)
  if ( !key_name_w )
    kcbptr = strdef->smcbidky;
  else
    kcbptr = strdef->GetKCB(key_name_w);
  if ( !kcbptr )                                     SDBERR(79)
      
  SDBEV1(extnames_w,ID_SIZE)
  SDB_Member sdbmem(extnames_w,strdef->smcbname,RL_reference,0,0,0,"",NO,NO);
  SDB_Reference dbrptr(sdbmem,trans_opt,0,own_opt_w,YES,NO,TEMP_MAIN,weak_opt_w,NULL,1,YES);
                                  
  if ( !(dbext   = new DBExtend(this,&dbrptr,strdef,NO,YES,NO,YES)) )
                                                     SDBERR(95)
  if ( !(dbindex = new DBIndex(kcbptr,YES,!own_opt_w,YES,NO,UNDEF,
                               own_opt_w ? SET_LARG : SET_SMAL,YES)) )
                                                     SDBERR(95)
  dbindex->set_field_def(dbext);
  delete dbext->get_index_list()->RemoveHead();
  dbext->get_index_list()->AddHead(dbindex);
  
  dbext->set_log_ref(YES);
  extdef_list.Insert(dbext);

  if ( baseexts_w )
  {
    SDBEV2(baseexts_w,ID_SIZE)
    if ( !(extdef = ProvideExtendDef(baseexts_w)) )  SDBERR(168)
    dbext->get_base_extend()->AddTail(extdef);
    extdef->get_derived_extends()->AddTail(dbext);
  }

  extnames_w = dbext->fmcbname;
RECOVER
  extnames_w = NULL;
ENDSEQ
  IUnlock();
  return(extnames_w);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  dbfield_ptr - Property definition
\param  extnames_w - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *Dictionary :: CreateTempExtent (DBFieldDef *dbfield_ptr, char *extnames_w )
{
  DBExtend               *dbext = NULL;
  char                    string[ID_SIZE+1];
  

BEGINSEQ
  ILock(YES);

  *string = 0;
  if ( !extnames_w )
    extnames_w = string;
  extnames_w = GetTempName(extnames_w);

  dbfield_ptr->GetDBStruct(this);
    
  if ( !(dbext = new DBExtend(dbfield_ptr,extnames_w)) ) 
                                                     ERROR
                                                     SDBCERR
  extdef_list.Insert(dbext);

  extnames_w = dbext->fmcbname;
RECOVER
  delete dbext;
  extnames_w = NULL;
ENDSEQ
  IUnlock();
  return(extnames_w);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  db_ext - 
\param  extnames_w - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtent"

char *Dictionary :: CreateTempExtent (DBExtend *db_ext, char *extnames_w )
{
  DBExtend               *dbext = NULL;
  char                    string[ID_SIZE+1];
  

BEGINSEQ
  ILock(YES);

  *string = 0;
  if ( !extnames_w )
    extnames_w = string;
  extnames_w = GetTempName(extnames_w);

  db_ext->GetDBStruct(this);

  if ( !(dbext = new DBExtend(*db_ext,extnames_w)) ) ERROR
                                                     SDBCERR
  extdef_list.Insert(dbext);

  extnames_w = dbext->fmcbname;
RECOVER
  delete dbext;
  extnames_w = NULL;
ENDSEQ
  IUnlock();
  return(extnames_w);
}

/******************************************************************************/
/**
\brief  CreateTempStruct - Create temporary structure definition



\return dbstrdef - Structure definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbfieldlist - 
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempStruct"

DBStructDef *Dictionary :: CreateTempStruct (DBFieldList *dbfieldlist, char *strnames_w )
{
   char *p;
   if (strnames_w) p = strnames_w;
   else p =  "VIEW_STRUCT";
   TypeKey       tkey(p, 0);
  
  DBStructDef  *dbstrdef    = NULL;

BEGINSEQ
  ILock(YES);
  if ( !(dbstrdef = new DBStructDef(tkey,
                                    TEMPSID,UNDEF,UNDEF,
                                    TYP_Structure,ST_USER,
                                    UNDEF,UNDEF,UNDEF,UNDEF,
                                    "VIEW_KEY",NO,0,NO))) 
                                                     SDBERR(95)
  
  if ( !dbstrdef->Setup(this,dbfieldlist) )          ERROR
  if ( dbstrdef->CreateKeyDefs(dbstrdef->smcbidky) ) ERROR
  if ( dbstrdef->SetupKeyDefs(GetSystemVersion()) )  ERROR
  
  if ( strnames_w )
    structure_list.Insert(dbstrdef);  // ?????
RECOVER
  delete dbstrdef;
  dbstrdef = NULL;
ENDSEQ
  IUnlock();
  return(dbstrdef);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  field_def - 
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempStruct"

DBStructDef *Dictionary :: CreateTempStruct (DBFieldDef *field_def, char *strnames_w )
{
  DBFieldList  *dbfieldlist = NULL;
  DBStructDef  *dbstrdef = NULL;
BEGINSEQ
  if ( !(dbfieldlist = DBFieldList::Create(this,field_def)) )
                                                     ERROR
  dbstrdef = CreateTempStruct(dbfieldlist,strnames_w);

RECOVER
  delete dbfieldlist;
  dbfieldlist = NULL;
  dbstrdef = NULL;
ENDSEQ
  return(dbstrdef);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  strdef_ptr - Internal data structure definition
\param  pathes - 
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempStruct"

DBStructDef *Dictionary :: CreateTempStruct (DBStructDef *strdef_ptr, char *pathes, char *strnames_w )
{
  DBFieldList  *dbfieldlist = NULL;
  DBStructDef  *dbstrdef = NULL;
BEGINSEQ
  if ( !(dbfieldlist = DBFieldList::Create(this,strdef_ptr,pathes)) )
                                                     ERROR
  dbstrdef = CreateTempStruct(dbfieldlist,strnames_w);

RECOVER
  delete dbfieldlist;
  dbfieldlist = NULL;
  dbstrdef = NULL;
ENDSEQ
  return(dbstrdef);
}

/******************************************************************************/
/**
\brief  DeleteEnum - Delete enumeration definition



\return term - Termination code

\param  enum_name - Enumeration name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEnum"

logical Dictionary :: DeleteEnum (char *enum_name )
{
  TypeKey      tkey(this,enum_name);
  logical      term = NO;
BEGINSEQ
  if ( !codeset_pi->Get(tkey.GetKey()) )            SDBERR(20)
  
  codeset_pi->Delete();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Dictionary - Create dictionary handle



-------------------------------------------------------------------------------
\brief  i0 - 



\param  cpath - Complete path
\param  accopt - Access mode
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Dictionary"

     Dictionary :: Dictionary (char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, char sysenv )
                     : DBHandle (),
Namespace(this,NULL,AUTO),
  handle_list(NULL),
  extdef_tree(NULL),
  extdef_list(NULL),
  structure_tree(NULL),
  structure_list(NULL),
  namespace_tree(NULL),
  namespace_list(NULL),
  extend_pi(NULL),
  struct_pi(NULL),
  codeset_pi(NULL),
  type_pi(NULL),
  refr_pi(NULL),
  test_opt(YES),
  strpi_locked(NO),
  extpi_locked(NO),
  typepi_locked(NO),
  ext_number(0),
  obh_list(NULL),
  xxdict_lock(NULL),
  last_schemav(0),
  view_pi(NULL),
  viewext_pi(NULL),
  expression_parser(NULL),
  expression_list(NULL),
  temp_struct_id(UNDEF)
{


BEGINSEQ
  InitLists();
  Initialize(cpath,accopt,w_netopt,version_nr,sysenv);
  
  SDBEV1(cpath,UNDEF)
  SDBCERR


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Dictionary"

     Dictionary :: Dictionary ( )
                     : DBHandle (),
Namespace(this,NULL,AUTO),
  handle_list(NULL),
  extdef_tree(NULL),
  extdef_list(NULL),
  structure_tree(NULL),
  structure_list(NULL),
  namespace_tree(NULL),
  namespace_list(NULL),
  extend_pi(NULL),
  struct_pi(NULL),
  codeset_pi(NULL),
  type_pi(NULL),
  refr_pi(NULL),
  test_opt(YES),
  strpi_locked(NO),
  extpi_locked(NO),
  typepi_locked(NO),
  ext_number(0),
  obh_list(NULL),
  xxdict_lock(NULL),
  last_schemav(0),
  view_pi(NULL),
  viewext_pi(NULL),
  expression_parser(NULL),
  expression_list(NULL),
  temp_struct_id(UNDEF)
{

BEGINSEQ
  InitLists();
  SDBCERR
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Dictionary"

     Dictionary :: Dictionary (DBHandle *dbhandle )
                     : DBHandle (),
Namespace(this,NULL,AUTO),
  handle_list(NULL),
  extdef_tree(NULL),
  extdef_list(NULL),
  structure_tree(NULL),
  structure_list(NULL),
  namespace_tree(NULL),
  namespace_list(NULL),
  extend_pi(NULL),
  struct_pi(NULL),
  codeset_pi(NULL),
  refr_pi(NULL),
  type_pi(NULL),
  test_opt(YES),
  strpi_locked(NO),
  extpi_locked(NO),
  typepi_locked(NO),
  ext_number(0),
  obh_list(NULL),
  xxdict_lock(NULL),
  last_schemav(0),
  view_pi(NULL),
  viewext_pi(NULL),
  expression_parser(NULL),
  expression_list(NULL),
  temp_struct_id(UNDEF)

{

BEGINSEQ
  InitLists();
  SDBCERR
  
  db_handle  = NULL;   // mark dictionary as work dictionary
                       // for providing SMCB's and Enumerations, only


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Display - 



\return term - Termination code

\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Display"

logical Dictionary :: Display (char *ppath )
{
  DBStructDef    *strdef;
  FILE           *filptr = NULL;
  int32           indx0  = 0;
  char            area[1024];
  logical         p;
  logical         term   = NO;
BEGINSEQ
  structure_list.Cancel();
  while ( strdef = structure_list.GetNext() )
    strdef->smcbsts.stssini();
{
  PropertyHandle   structs(struct_pi->GetObjectHandle(),"SDB_Structure",PI_Read);
                                                      SDBCERR 
  PropertyHandle  *sys_ident = structs.GPH("sys_ident");
  PropertyHandle  *atyp      = structs.GPH("access_type");
  PropertyHandle  *ityp      = structs.GPH("itype");
  PropertyHandle  *pers      = structs.GPH("smceodaba");
  indx0 = 0;
  while ( structs.Get(indx0++) )
    if ( (p = pers->GetCount() > 0 ? YES : NO) || (ityp->GetInt() && atyp->GetInt() > 0) )
      if ( strdef = ProvideStructDef(sys_ident->GetString()) )
        if ( p )
          strdef->smcbsts.stssfil();
}
{
  PropertyHandle   codesets(codeset_pi->GetObjectHandle(),"SDB_ValueList",PI_Read);
                                                      SDBCERR 
  PropertyHandle  *sys_ident = codesets.GPH("sys_ident");
  indx0 = 0;
  while ( codesets.Get(indx0++) )
    ProvideStructDef(sys_ident->GetString());
}

  if ( !(filptr = fopen(ppath,"wt")) )               SDBERR(187)
  
  fprintf(filptr,"\n Dictionary  ");
  fprintf(filptr,GetLocalDBHandle()->get_db_path());
  fprintf(filptr,"\n");
  fprintf(filptr,"\n SID     Name                                     Version Err Sys Enum Pers IntLen  ExtLen");
  fprintf(filptr,"\n -------------------------------------------------------------------------------------------");
  
  structure_list.Cancel();
  while ( strdef = structure_list.GetNext() )
  {
    strcpy(area,"\n ZZZZ9                                            Z9                        ZZZZZ9  ZZZZZ9");
    gvtxltp(area+ 2,strdef->smcbityp,5);
    memcpy (area+10,strdef->smcbname,ID_SIZE);
    gvtxitp(area+51,strdef->get_schema_ver(),2);
    if ( strdef->smcbsts.stscerr() )
      area[60] = 'X';
    if ( strdef->smcbsts.stscini() )
      area[64] = 'X';
    if ( strdef->smcbstyp == ST_CODE )
      area[68] = 'X';
    if ( strdef->smcbsts.stscfil() )
      area[73] = 'X';
    gvtxltp(area+77,strdef->GetLength(),6);
    gvtxltp(area+85,strdef->get_ext_length(),6);
    fprintf(filptr,area);
  }
  
  fprintf(filptr,"\n\n");
  fclose(filptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCTXIPath - 



\return cpath - Complete path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCTXIPath"

char *Dictionary :: GetCTXIPath ( )
{
  char                 string[41];
  char                *dll_name = "";
  DictionaryHandle     dicthdl;

BEGINSEQ
  ILock(YES);
  
  if ( *ctxi_path )                                  LEAVESEQ

  if ( db_handle )
  {
    dicthdl = DictionaryHandle(this);
    PropertyHandle  db_pi(dicthdl,"ODC_Database",PI_Read);
    if ( db_pi(FIRST_INSTANCE) )
      dll_name = strcpy(string,db_pi.GetPropertyHandle("ctx_interface")->GetString());
  }
  if ( !*dll_name )   
    if ( GetSysVariable("CTXI_DLL") )
      dll_name = GetSysVariable("CTXI_DLL");
  
  if ( !*dll_name )   
    dll_name = "ctxi";

  if ( !GetDLLPath(ctxi_path,dll_name) )             ERROR

RECOVER
  *ctxi_path = ' ';
ENDSEQ
  IUnlock();
  return(*ctxi_path > ' ' ? ctxi_path : NULL);
}

/******************************************************************************/
/**
\brief  GetClientDictionary - 



\return cdictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientDictionary"

CDictionary *Dictionary :: GetClientDictionary ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetDLLPath - 



\return dll_path - 

\param  cpath - Complete path
\param  dll_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDLLPath"

char *Dictionary :: GetDLLPath (char *cpath, char *dll_name )
{
  char                *db_path;
  char                 dirs[129];
  char                 drives[4];
  char                *opath = NULL;
BEGINSEQ
  if ( GetSysVariable("PROGPATH") )
  {
    strcpy(cpath,GetSysVariable("PROGPATH"));
    strcat(filncat(cpath,dll_name,255),".dll");
    if ( IsFile(cpath) )                         LEAVESEQ
    *cpath = 0;
  }
  
  if ( this && (db_path = GetPath()) )
  {
    fildirg (db_path,drives,dirs);
  
    strcat(strcat(strcpy(cpath,drives),dirs),"exe/");
    strcat(strcat(cpath,dll_name),".dll");
    if ( IsFile(cpath) )                         LEAVESEQ
    *cpath = 0;
  
    strcat(strcpy(cpath,drives),dirs);
    strcat(strcat(cpath,dll_name),".dll");
    if ( IsFile(cpath) )                         LEAVESEQ
  }
  
  if ( opath = GetSysVariable("ODABA_PATH") )
  {
    strcat(filncat(strcpy(cpath,opath),dll_name,255),".dll");
    if ( IsFile(cpath) )                         LEAVESEQ
  }
  if ( (opath = GetSysVariable("PROJECT_PATH")) || (opath = ReadSysVariable("PROJECT_PATH")) )
  {
    strcat(filncat(strcpy(cpath,opath),dll_name,255),".dll");
    if ( IsFile(cpath) )                         LEAVESEQ
  }
  strcat(strcpy(cpath,dll_name),".dll");

ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  GetDictionaryHandle - 



\return pdictptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDictionaryHandle"

DictionaryHandle *Dictionary :: GetDictionaryHandle ( )
{
  static DictionaryHandle stat_dicth_ptr;
  return( this ? (DictionaryHandle *)&db_hdl : &stat_dicth_ptr );

}

/******************************************************************************/
/**
\brief  GetExpression - 



\return expr_decl - 

\param  clasname - 
\param  exprname - 
\param  p_liste - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpression"

OPDecl *Dictionary :: GetExpression (char *clasname, char *exprname, ParmList *p_liste )
{
  DBStructDef      *dbstrdef      = NULL;
  OPDecl           *expr_decl_ptr = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  ILock(YES);
  
  if ( clasname )
  {
    if ( !(dbstrdef = ProvideStructDef(clasname)) )    SDBERR(20)
    if ( !(expr_decl_ptr = dbstrdef->GetExprDecl(exprname,NULL,NULL,p_liste,NO,YES)) &&
         !(expr_decl_ptr = dbstrdef->GetExprDecl(exprname,NULL,NULL,p_liste,YES,YES))    )
                                                       ERROR
  }
  else
  {
    if ( !expression_list )                            ERROR
    
    expression_list->GoTop();
    while ( expr_decl_ptr = expression_list->GetNext() )
      if ( !strcmp(exprname,expr_decl_ptr->get_opname()) )
                                                     LEAVESEQ
    ERROR
  }


RECOVER

ENDSEQ
  if ( this ) 
    IUnlock();
  return(expr_decl_ptr);
}

/******************************************************************************/
/**
\brief  GetExtendDef - 



\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  extname - Extent name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtendDef"

DBExtend *Dictionary :: GetExtendDef (char *extname, int32 nsid )
{
  TypeKey      tkey(extname,nsid);

  return( GetExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtendDef"

DBExtend *Dictionary :: GetExtendDef (TypeKey &tkey )
{
  DBExtend    *dbextdef = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  ILock(YES);
  
  if ( dbextdef = extdef_list.Get(tkey,tkey.Exact()) )  
    if ( tkey != dbextdef->fmcbname )                 ERROR

RECOVER
  dbextdef = NULL;
ENDSEQ
  if ( this )
    IUnlock();
  return(dbextdef);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtendDef"

DBExtend *Dictionary :: GetExtendDef (char *scoped_name )
{
  TypeKey      tkey(this,scoped_name);
  return( GetExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  GetExtentType - 



\return strname - Type name
-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentType"

char *Dictionary :: GetExtentType (TypeKey &tkey )
{
  DBExtend       *dbextdef = NULL;
  char           *strname = NULL;
  if ( dbextdef = GetExtendDef(tkey) )
    strname = dbextdef->fmcbtype;

  ILock(YES);

  if ( (*extend_pi)(tkey.GetKey()) )
    strname = extend_pi->GetArea("sys_ident");
  else if ( (*refr_pi)(tkey.GetKey()) )
    strname = refr_pi->GetArea("sys_ident");

  IUnlock();

  return(strname);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  extnames - Extent name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentType"

char *Dictionary :: GetExtentType (char *extnames, int32 nsid )
{
  TypeKey         tkey(extnames,nsid);
  return( GetExtentType(tkey) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentType"

char *Dictionary :: GetExtentType (char *scoped_name )
{
  TypeKey      tkey(this,scoped_name);
  return( GetExtentType(tkey) );

}

/******************************************************************************/
/**
\brief  GetGlobalVariable - 



\return prophdl - 

\param  var_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalVariable"

PropertyHandle *Dictionary :: GetGlobalVariable (char *var_name )
{
  ParmList                 *global_vars;

  global_vars = (ParmList *)GetOPAProcessVariable(PVN_GlobalVariables);
  
  return(global_vars->Get(var_name));


}

/******************************************************************************/
/**
\brief  GetID_SIZE - 



\return size - Field size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID_SIZE"

int16 Dictionary :: GetID_SIZE ( )
{

  return( GetSystemVersion() >= 2 ? ID_SIZE : 16 ); // muﬂ nach Umstellung immer ID_SIZE liefern

}

/******************************************************************************/
/**
\brief  GetLastStructureID - 



\return sid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastStructureID"

int16 Dictionary :: GetLastStructureID ( )
{

  return(1000);

}

/******************************************************************************/
/**
\brief  GetLocalDictionary - 



\return ldictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalDictionary"

LDictionary *Dictionary :: GetLocalDictionary ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetNSPath - 



\return extpath - 

\param  string - 
\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNSPath"

char *Dictionary :: GetNSPath (char *string, TypeKey &tkey )
{
  char                   *pos = NULL;
  char                   *pos1 = NULL;
  char                   *pos2 = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !string || !*string )                         ERROR
    
  pos1 = strchr(string,'.');
  pos2 = strchr(string,'(');
  if ( pos1 || pos2 )
  {
    pos = pos1;
    if ( pos2 && pos2 < pos1 )
      pos = pos2;
    *pos = 0;
  }
  else
    pos = string;
  
  tkey.Initialize(this,string);

  if ( !*pos )
  {
    *pos = '.';
    if ( pos != string )
      pos++;
  }
RECOVER
  pos = NULL;
ENDSEQ
  return(pos);
}

/******************************************************************************/
/**
\brief  GetNamespace - 



\return ns - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  scope_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNamespace"

Namespace *Dictionary :: GetNamespace (char *scope_name )
{
  TypeKey          tkey(this,scope_name,NULL);
  int32            nsid = tkey.GetID();

  return( nsid ? nsid == AUTO 
               ? NULL : GetNamespace(nsid)
               : this );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNamespace"

Namespace *Dictionary :: GetNamespace (TypeKey &tkey )
{

  return( GetNamespace(tkey.GetID()) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNamespace"

Namespace *Dictionary :: GetNamespace (int32 nsid )
{
  Namespace        *ns = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  ILock(YES);
  
  ns = namespace_list((char *)&nsid);
RECOVER
  ns = NULL;
ENDSEQ
  if ( this )
    IUnlock();
  return(ns);
}

/******************************************************************************/
/**
\brief  GetOBHandle - 



\return obhandle - Database Object handle

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOBHandle"

ACObject *Dictionary :: GetOBHandle (uint16 version_nr )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetParser - 



\return parser - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParser"

BNFParser *Dictionary :: GetParser ( )
{

BEGINSEQ
  if ( !expression_parser )
    if ( !(expression_parser = new BNF_OSI(NULL)) )
                                                     ERROR


RECOVER

ENDSEQ
  return(expression_parser);
}

/******************************************************************************/
/**
\brief  GetParserError - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParserError"

char *Dictionary :: GetParserError ( )
{

  return(expression_parser->GetLastError());

}

/******************************************************************************/
/**
\brief  GetSType - 



\return styp - 

\param  typetype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSType"

int32 Dictionary :: GetSType (int32 typetype )
{
  int32     styp = NO;
  switch ( typetype )
  {
    case TYP_Base      : styp = ST_BASE;
                         break;
    case TYP_Structure : styp = ST_USER;
                         break;
    case TYP_Codeset   : styp = ST_CODE;
                         break;
    default            : styp = 0;
  }

  return(styp);
}

/******************************************************************************/
/**
\brief  GetServerDefinition - 



\return dbstructdef - 

\param  strname - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetServerDefinition"

DBStructDef *Dictionary :: GetServerDefinition (char *strname )
{
  DBStructDef            *dbstructdef = NULL;

  return(dbstructdef);
}

/******************************************************************************/
/**
\brief  GetStrDefVersion - 



\return strdef_ptr - Internal data structure definition

\param  tkey - 
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStrDefVersion"

DBStructDef *Dictionary :: GetStrDefVersion (TypeKey &tkey, uint8 schemaversion )
{
  DBStructDef     *strdef_ptr= NULL;
  ACObject        *obhandle;
BEGINSEQ
  ILock(YES);
  if ( !(obhandle = GetOBHandle(schemaversion)) )    ERROR
  DBObjectHandle   temp_object(obhandle);
  PI(SDB_Structure) struct_pi(temp_object,"SDB_Structure",PI_Read);
                                                     SDBCERR
  
  if ( !struct_pi(tkey.GetKey()) || !struct_pi.IsTrue("checked") || 
       ( struct_pi.GPH("smceodaba")->GetID(0L) && !struct_pi.IsTrue("ready") ) )
                                                     SDBERR(136)
      
  if ( !(strdef_ptr = new DBStructDef(tkey,UNDEF,UNDEF,UNDEF,
                                      TYP_Structure,ST_USER,
                                      UNDEF,UNDEF,UNDEF,UNDEF) ) )
                                                     SDBERR(95)
  strdef_ptr->smcbacc = strdef_ptr;
  strdef_ptr->smcbsts.stssold();
  
  if ( strdef_ptr->FillStructure(this,struct_pi) )   ERROR
  if ( strdef_ptr->get_schema_ver() > schemaversion ) 
                                                     SDBERR(243)
RECOVER
  delete strdef_ptr; 
  strdef_ptr = NULL;
ENDSEQ
  IUnlock();
  return(strdef_ptr);
}

/******************************************************************************/
/**
\brief  GetStructDef - Get structure definition



\return strdef - Structure definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  strnames - Type name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *Dictionary :: GetStructDef (char *strnames, int32 nsid )
{
  TypeKey                 tkey(strnames,nsid);

  return( GetStructDef(tkey) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  strnames - Type name
\param  nsid - 
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *Dictionary :: GetStructDef (char *strnames, int32 nsid, uint8 schemaversion )
{
  DBStructDef            *strdef;
BEGINSEQ
  ILock(YES);
  if ( !(strdef = GetStructDef(strnames,nsid)) )     ERROR

if ( strdef->smcbstyp != ST_CODE ) // sollte sp‰ter auch versioniert werden  
  if ( strdef->get_schema_ver() > schemaversion )
    if ( !(strdef = strdef->GetStrDefVersion(this,schemaversion)) )
                                                     ERROR
RECOVER
  strdef = NULL;
ENDSEQ
  IUnlock();
  return(strdef);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *Dictionary :: GetStructDef (TypeKey &tkey )
{
  DBStructDef            *strdef;

BEGINSEQ
  ILock(YES);
  
  if ( strdef = structure_list.Get(tkey,tkey.Exact()) )
    if ( tkey != strdef->smcbname )                     ERROR

RECOVER
  strdef = NULL;
ENDSEQ
  IUnlock();
  return(strdef);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *Dictionary :: GetStructDef (char *scoped_name )
{
  TypeKey                 tkey(this,scoped_name);
  return( GetStructDef(tkey) );

}

/******************************************************************************/
/**
\brief  GetTempName - Get name for temporary extent



\return extname - Extent name

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempName"

char *Dictionary :: GetTempName (char *extnames )
{

BEGINSEQ
  ILock(YES);
  if ( !extnames )                                   SDBERR(99)
  
  if ( !*extnames )
  {
    memcpy(strcpy(extnames,"9999999999999999"),TEMP_EXT,strlen(TEMP_EXT));
    gvtxltp(extnames,ext_number,strlen(extnames));
    ext_number++;
  }

RECOVER

ENDSEQ
  IUnlock();
  return(extnames);
}

/******************************************************************************/
/**
\brief  GetTempStructID - 



\return strid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempStructID"

int32 Dictionary :: GetTempStructID ( )
{

  if ( !temp_struct_id )
    temp_struct_id = GetLastStructureID();

  temp_struct_id++;
  return(temp_struct_id);
}

/******************************************************************************/
/**
\brief  GetThisDictionary - 



\return dictptr - Dictionary handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetThisDictionary"

Dictionary *Dictionary :: GetThisDictionary ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  GetTypeSpec - 



\return term - Termination code

\param  tkey - 
\param  itypptr - 
\param  stypptr - 
\param  atypptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeSpec"

logical Dictionary :: GetTypeSpec (TypeKey &tkey, int16 *itypptr, int16 *stypptr, int16 *atypptr )
{
  StructDef         *strdef;
  logical            reserved = NO;
  int16              ityp;
  int16              styp;
  int16              atyp;
  logical            term = NO;

BEGINSEQ
  ILock(YES);
  
  if ( strdef = GetStructDef(tkey) )
  {
    ityp = strdef->smcbityp;
    styp = strdef->smcbstyp;
    atyp = strdef->smcbatyp;
  }
  else
  {
    PropertyHandle   str_pi(*GetDBObjectHandle(),"SDB_Type",PI_Read);  SDBCERR

    if ( !str_pi(tkey.GetKey()) )                   SDBERR(20)

    ityp = str_pi.GetInt("itype");
    styp = GetSType(str_pi.GetInt("typetype"));
    atyp = str_pi.GetInt("access_type");
  }
    
  if ( itypptr )
    *itypptr = ityp;
  if ( stypptr )
    *stypptr = styp;
  if ( atypptr )
    *atypptr = atyp;

RECOVER
  term    = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  GetValueList - 



\return vlist - 

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValueList"

ENUM_ValueList *Dictionary :: GetValueList (char *extnames )
{
  TypeKey         tkey(this,extnames);
  DBExtend       *extdef;
  ENUM_ValueList *vlist = NULL;
BEGINSEQ
  if ( !(extdef = GetExtendDef(tkey)) )                 ERROR

  vlist = extdef->get_cs_values();
RECOVER
  vlist = NULL;
ENDSEQ
  return(vlist);
}

/******************************************************************************/
/**
\brief  InitLists - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitLists"

void Dictionary :: InitLists ( )
{

  handle_list = new DLL(DBHandle);
  
  extdef_tree = new BinTree(sizeof(DBExtend),offsetof(DBExtend,type_key),
                            sizeof(TypeKey),'C',64);
  extdef_list.SetTree(extdef_tree);
  
  structure_tree = new BinTree(sizeof(DBStructDef),offsetof(DBStructDef,smcbname),
                               sizeof(TypeKey),'C',128);
  structure_list.SetTree(structure_tree);

  namespace_tree = new BinTree(sizeof(Namespace),offsetof(Namespace,namespace_id),
                               sizeof(int32),'I',64);
  namespace_list.SetTree(namespace_tree);


}

/******************************************************************************/
/**
\brief  Initialize - 




\param  cpath - Complete path
\param  accopt - Access mode
\param  w_netopt - Multi-user option
\param  version_nr - Internal version number
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void Dictionary :: Initialize (char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr, char sysenv )
{


  DBHandle::Initialize(NULL,cpath,accopt,w_netopt,version_nr,sysenv);



}

/******************************************************************************/
/**
\brief  IsBasicType - Is type an elementary type?



\return term - Termination code

\param  typenames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasicType"

logical Dictionary :: IsBasicType (char *typenames )
{
  char        *basic_types[] = { "CHAR",
                                 "GUID",
                                 "INT",
                                 "UINT",
                                 "MEMO",
                                 "VOID",
                                 "DATE",
                                 "TIME",
                                 "LOGICAL",
                                 "STRING",
                                 "BIT",
                                 "REAL",
                                 "DATETIME",
                                 "CCHAR",
                                 "BLOB",
                               };
  char                    string[ID_SIZE+1];
  return ( gvtsswt(gvtxbts(string,typenames,ID_SIZE),
                   sizeof(basic_types)/sizeof(basic_types[0]),
                   basic_types) ? YES : NO );

}

/******************************************************************************/
/**
\brief  LocateExtentDef - Search for extent definition



\return extdef - Internal extent definition

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateExtentDef"

DBExtend *Dictionary :: LocateExtentDef (TypeKey &tkey )
{
  DBExtend    *extdef = NULL;
  ILock(YES);
  
  if ( !(extdef = GetExtendDef(tkey)) )
    if ( extend_pi->Get(tkey.GetKey()) )
      extdef = ProvideExtendDef(tkey);
  IUnlock();
  return(extdef);
}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical Dictionary :: Lock (logical wait )
{

  return ( ILock(wait) );

}

/******************************************************************************/
/**
\brief  OpenDictionary - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDictionary"

logical Dictionary :: OpenDictionary ( )
{
  char                   *sys_ver;
  logical                 term = NO;
BEGINSEQ
  dictionary = this;
  
  if ( TestSysVariable("ODABA2","TEST") )
    test_opt = YES;
    
  memset(ctxi_path,0,sizeof(ctxi_path));

  if ( sys_ver = GetSysVariable("SYSTEM_VERSION") )
    sys_version = atoi(sys_ver);
    
  if ( ((SystemDict *)this)->Start() )               ERROR

  obh_list = new GSRT(OBH_ListEntry)(10,sizeof(OBH_ListEntry),2,1,'I',YES);
  OBH_ListEntry   obh_ent(this,version);
  if ( !obh_list->AddEntry(&obh_ent) )               ERROR

  version = CUR_VERSION;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenPIs - 



\return term - Termination code

\param  w_dbhandle - 
\param  init_enums - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenPIs"

logical Dictionary :: OpenPIs (DBHandle *w_dbhandle, logical init_enums )
{
  DBHandle         *dbhandle = w_dbhandle ? w_dbhandle : this;
  StructDef        *strdef;
  BTI(DBStructDef)  cursor(structure_list);
  int32             indx0 = 0;
  logical           term = NO;
BEGINSEQ
  if ( !type_pi )
    if ( !(type_pi = new PropertyHandle(*dbhandle->GetDBObjectHandle(),"SDB_Type",access_mode)) )
                                                      SDBERR(95)
                                                      SDBCERR 
  if ( !struct_pi )
    if ( !(struct_pi = new PropertyHandle(*dbhandle->GetDBObjectHandle(),"SDB_Structure",access_mode)) )
                                                      SDBERR(95)
                                                      SDBCERR 
  if ( !codeset_pi )
    if ( !(codeset_pi = new PropertyHandle(*dbhandle->GetDBObjectHandle(),"SDB_ValueList",access_mode)) )
                                                      SDBERR(95)
                                                      SDBCERR 
  if ( !extend_pi )
    if ( !(extend_pi = new PropertyHandle(*dbhandle->GetDBObjectHandle(),"SDB_Extend",access_mode)) )
                                                      SDBERR(95)
                                                      SDBCERR 
  if ( !refr_pi )
    if ( !(refr_pi = new PropertyHandle(*dbhandle->GetDBObjectHandle(),"SDB_Reference",access_mode)) )
                                                      SDBERR(95)
                                                      SDBCERR 
  if ( !view_pi )
    if ( !(view_pi = new PropertyHandle(*dbhandle->GetDBObjectHandle(),"ODC_View",access_mode)) )
                                                      SDBERR(95)
  PropertyHandle   ph;
  Namespace::Fill(ph);

  SDBRESET

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ParseExpression - 



\return bdata - 

\param  expression - Expression
\param  symbol - 
\param  expr_dup - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParseExpression"

BNFData *Dictionary :: ParseExpression (char *expression, char *symbol, char **expr_dup )
{
  logical      dup   = NO;
  BNFData     *bdata = NULL;
BEGINSEQ
  ILock(YES);
  
  if ( !GetParser() )                                ERROR
  if ( expr_dup )
  {
    expression = *expr_dup = strdup(expression);
    dup = YES;
  }
    
  if ( !(bdata = expression_parser->Analyze(expression,symbol,YES)) )
  {
    SDBError().TraceMessage("Parser error:\n",GetParserError());
    SDBERR(378)
  }
  
// bdata->Print("e:/bnftree",YES);

RECOVER
  if ( expr_dup )
  {
    if ( dup )
      free(*expr_dup);
    *expr_dup = NULL;
  }
ENDSEQ
  IUnlock();
  return(bdata);
}

/******************************************************************************/
/**
\brief  ParseFile - 



\return bdata - 

\param  cpath - Complete path
\param  symbol - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParseFile"

BNFData *Dictionary :: ParseFile (char *cpath, char *symbol )
{
  BNFData     *bdata = NULL;
BEGINSEQ
  if ( !GetParser() )                                ERROR
  
  if ( !(bdata = expression_parser->AnalyzeFile(cpath,symbol,YES)) )
  {
    SDBError().TraceMessage("Parser error:\n",GetParserError());
    SDBERR(378)
  }
RECOVER

ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  ProvExpression - 



\return expr_decl - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  resobj - 
\param  clasname - 
\param  exprname - 
\param  co - 
\param  p_liste - 
\param  w_obhandle - 
\param  operenv_w - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

OPDecl *Dictionary :: ProvExpression (ACObject *resobj, char *clasname, char *exprname, PropertyHandle *co, ParmList *p_liste, ACObject *w_obhandle, OperEnvironment *operenv_w, logical refresh_opt )
{
  DBStructDef      *dbstrdef      = NULL;
  PropertyHandle   *fct_ph        = NULL;
  char              fname[ID_SIZE];
  OPDecl           *expr_decl_ptr = NULL;
BEGINSEQ
  ILock(YES);
  expr_decl_ptr = GetExpression(clasname,exprname,p_liste);
  dbstrdef = ProvideStructDef(clasname);

  if ( refresh_opt && expr_decl_ptr )
  {
    delete expr_decl_ptr;
    expr_decl_ptr = NULL;
  }

  if ( !expr_decl_ptr ) 
  {
    DBObjectHandle      dboh(resobj ? resobj : this);
    PropertyHandle      cls_ph(dboh,"ODC_ImpClass",PI_Read);
    
    if ( !dbstrdef )                                       SDBERR(20)
    TypeKey    tkey(this,clasname);
    if ( cls_ph.Get(tkey.GetKey()) && 
         (fct_ph = cls_ph.GPH("pfunctions")) &&
         fct_ph->Get(gvtxstb(fname,exprname,ID_SIZE)) )
    {
      if ( fct_ph->GPH("imp_type")->GetInt() == MT_OQLExpression )
        expr_decl_ptr = dbstrdef->CreateExprDecl(this,fct_ph,NULL,NULL,co,p_liste,operenv_w);
    }
  }
RECOVER

ENDSEQ
  IUnlock();
  return(expr_decl_ptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  resobj - 
\param  clasname - 
\param  expression - Expression
\param  co - 
\param  w_obhandle - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

OPDecl *Dictionary :: ProvExpression (ACObject *resobj, char *clasname, char *expression, PropertyHandle *co, ACObject *w_obhandle, OperEnvironment *operenv_w )
{
  OPDecl                   *expr_decl = NULL;
  char                     *expr_dup  = NULL;
  char                     *bsymbol;
  char                     *string = expression;
  DBStructDef              *strdef    = NULL;
  BNFData                  *bnf_data  = NULL;
BEGINSEQ
  ILock(YES);
  
  while ( *string == ' ')
    string++;
  if ( *string == '{') {
     bsymbol = "OQLExpression";
  } else {
     bsymbol = "operand";
  }
  if ( !(bnf_data = ParseExpression(expression,bsymbol,&expr_dup)) )   
                                                     ERROR
  
  expr_decl = ProvExpression(resobj,clasname,bnf_data,co,
                             w_obhandle,operenv_w,expr_dup);  

RECOVER
  delete expr_decl;
  expr_decl = NULL;
ENDSEQ
  IUnlock();
  return(expr_decl);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  resobj - 
\param  clasname - 
\param  bnf_data - 
\param  co - 
\param  w_obhandle - 
\param  operenv_w - 
\param  expr_dup_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvExpression"

OPDecl *Dictionary :: ProvExpression (ACObject *resobj, char *clasname, BNFData *bnf_data, PropertyHandle *co, ACObject *w_obhandle, OperEnvironment *operenv_w, char *expr_dup_w )
{
  OPDecl                   *expr_decl = NULL;
  DBStructDef              *strdef    = NULL;
BEGINSEQ
  ILock(YES);
  
  if ( !resobj )
    resobj = this;
    
  if ( clasname )
    if ( !(strdef = ProvideStructDef(clasname)) )    SDBERR(68)
  
  if ( expr_dup_w )
    if ( expr_decl = GetExpression(clasname,expr_dup_w,NULL) ) 
    {
      delete bnf_data;
      free(expr_dup_w);
      LEAVESEQ
    }
  
  if ( bnf_data->GetSymbolCode("OQLSelect","access_path") )
  {
    expr_decl = new OPAccessPathDecl(this,resobj,w_obhandle,strdef,
                                     co->IsValid() ? co : NULL,bnf_data,operenv_w,expr_dup_w);
                                                     OQLCERR
  }
  else // "expr_def","block","sngl_operand"
  {
    expr_decl = new OPExpressionDecl(this,resobj,w_obhandle,strdef,
                                     co->IsValid() ? co : NULL,bnf_data,operenv_w,expr_dup_w);
                                                     OQLCERR
  }

  AddExpression(strdef,expr_decl); 

RECOVER
  delete expr_decl;
  expr_decl = NULL;
ENDSEQ
  IUnlock();
  return(expr_decl);
}

/******************************************************************************/
/**
\brief  ProvFunction - 



\return fctdecl - 

\param  resobj - 
\param  clasname - 
\param  fnames - 
\param  co - 
\param  p_liste - 
\param  recurse_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvFunction"

OPFunctionDecl *Dictionary :: ProvFunction (ACObject *resobj, char *clasname, char *fnames, PropertyHandle *co, ParmList *p_liste, logical recurse_opt )
{
  DBStructDef      *dbstrdef     = NULL;
  PropertyHandle   *fct_ph       = NULL;
  char              fname[ID_SIZE];
  OPFunctionDecl   *fct_decl_ptr = NULL;
BEGINSEQ
  ILock(YES);
  
  if ( !(dbstrdef = ProvideStructDef(clasname)) )    SDBERR(20)
  
  if ( !(fct_decl_ptr = dbstrdef->GetFctDecl(fnames,NULL,co,p_liste,NO,recurse_opt)) &&
       !(fct_decl_ptr = dbstrdef->GetFctDecl(fnames,NULL,co,p_liste,YES,recurse_opt))    )
  {
    DBObjectHandle      dboh(resobj ? resobj : this);
    PropertyHandle      cls_ph(dboh,"ODC_ImpClass",PI_Read);
    
    TypeKey    tkey(this,clasname);
    if ( cls_ph.Get(tkey.GetKey()) && 
         (fct_ph = cls_ph.GPH("pfunctions")) &&
         fct_ph->Get(gvtxstb(fname,fnames,ID_SIZE)) )
    {
      if ( fct_ph->GPH("imp_type")->GetInt() != MT_OQLExpression )
        fct_decl_ptr = dbstrdef->CreateFctDecl(this,fct_ph,NULL,co,p_liste);
    }
    else
      fct_decl_ptr = dbstrdef->CreateFctDecl(fnames);
  }
RECOVER

ENDSEQ
  IUnlock();
  return(fct_decl_ptr);
}

/******************************************************************************/
/**
\brief  ProvideCSDecl - 



\return csdefptr - 

\param  tkey - 
\param  strdefptr - 
\param  itype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideCSDecl"

DBStructDef *Dictionary :: ProvideCSDecl (TypeKey &tkey, DBStructDef *strdefptr, int32 itype )
{
  DBStructDef          *csdefptr  = NULL;
  DBStructDef          *value_str = ProvideStructDef("ENUM_Value");
BEGINSEQ
  ILock(YES);
  
  if ( strdefptr )
  {
    csdefptr = strdefptr;
    csdefptr->smcbityp = itype;
  }
  else
  {
    if ( !(csdefptr = new DBStructDef(tkey,itype,
                                      UNDEF,UNDEF,TYP_Codeset,ST_CODE,0,8,0,0)) )
                                                     SDBERR(95)
    structure_list.Insert(csdefptr);
  }
  
  csdefptr->SetEnumFieldList(this);

RECOVER
  csdefptr = NULL;
ENDSEQ
  IUnlock();
  return(csdefptr);
}

/******************************************************************************/
/**
\brief  ProvideExtendDef - 



\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendDef"

DBExtend *Dictionary :: ProvideExtendDef (char *scoped_name )
{
  TypeKey         tkey(this,scoped_name);

  return( ProvideExtendDef(tkey) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  tkey - 
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendDef"

DBExtend *Dictionary :: ProvideExtendDef (TypeKey &tkey, uint8 schemaversion )
{
  DBExtend               *extdef = NULL;
  DBFieldDef             *fielddef;
  char                    extname[ID_SIZE];
BEGINSEQ
  if ( !this )                                       ERROR

  if ( extdef = ProvideExtendDef(tkey) )
  {
    if ( schemaversion < extdef->get_version() )
      if ( fielddef = extdef->GetDBField(schemaversion) )
        extdef = (DBExtend *)fielddef;
  }

RECOVER
  extdef = NULL;
ENDSEQ
  return(extdef);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendDef"

DBExtend *Dictionary :: ProvideExtendDef (TypeKey &tkey )
{
  SDB_Reference  *refrptr;
  DBExtend       *dbextdef = NULL;
  DBStructDef    *strdef;
BEGINSEQ
  ILock(YES);
  if ( dbextdef = GetExtendDef(tkey) )                LEAVESEQ

  if ( !(dbextdef = CreateExtentDef(tkey)))           ERROR
RECOVER
  delete dbextdef;
  dbextdef = NULL;
ENDSEQ
  IUnlock();
  return(dbextdef);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  ph - 
\param  dbstrdef - Structure definition
\param  baseext - Base extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendDef"

DBExtend *Dictionary :: ProvideExtendDef (PropertyHandle &ph, DBStructDef *dbstrdef, DBExtend *baseext )
{
  TypeKey        tkey;
  DBExtend      *dbextdef = NULL;
BEGINSEQ
  ILock(YES);
  
if ( sys_version <= 17 )
  tkey.Initialize(ph.GetArea("sys_ident"),0);  
else
  tkey.Initialize(this,ph.GetString("scope"),ph.GetArea("sys_ident"));  
  if ( !tkey )                                        SDBERR(99)
  if ( dbextdef = GetExtendDef(tkey) )                LEAVESEQ

  if ( !(dbextdef = new DBExtend(ph,this,dbstrdef,baseext)) ) 
                                                      SDBERR(95)
                                                      SDBCERR 

RECOVER
  delete dbextdef;
  dbextdef = NULL;
ENDSEQ
  IUnlock();
  return(dbextdef);
}

/******************************************************************************/
/**
\brief  ProvideStructDcl - 



\return strdefptr - 
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
#define    MOD_ID  "ProvideStructDcl"

DBStructDef *Dictionary :: ProvideStructDcl (TypeKey &tkey, int16 strsid, int32 intlen, int32 extlen, TYP_TYPES metatype, SDB_ST strtype, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames, logical w_vf_opt, int16 w_schema_version, logical w_versioning, logical glob_identity )
{
  DBStructDef     *strdefptr   = NULL;
  DBStructDef     *prev_strdef = NULL;

BEGINSEQ
  ILock(YES);
  if ( strdefptr = (DBStructDef *)GetStructDef(tkey) ) 
  {
    if ( w_schema_version == strdefptr->get_schema_ver() )
    {  
      if ( strdefptr->Check(strsid,basecount,attrcount,refrcount,rshpcount,idkeynames,w_vf_opt) )
                                                     ERROR
                                                     LEAVESEQ
    }
    if ( w_schema_version > strdefptr->get_schema_ver() )
    {
      if ( strdefptr->Check(strsid) )                ERROR
      RemoveStructDef(tkey);
      prev_strdef = strdefptr;
    }
  }

  if ( !(strdefptr = new DBStructDef(tkey,strsid,intlen,extlen,
                                     metatype,strtype,
                                     basecount,attrcount,refrcount,rshpcount,
                                     idkeynames,w_vf_opt,w_schema_version,w_versioning,glob_identity)) )  
                                                     SDBERR(95)
  strdefptr->set_prev_struct(prev_strdef);
  
  if ( metatype == TYP_Structure || strsid == T_MEMO || strsid == T_BLOB )
    strdefptr->smcbacc = strdefptr;
  
  if ( metatype == TYP_Base )
  {
    if ( strsid == T_MEMO || strsid == T_BLOB )
      strdefptr->smcbacc = strdefptr;
    else
      strdefptr->smcbacc = new acc(NO);
  }
  
  if ( metatype == TYP_Structure && !strsid )
    strdefptr->smcbityp = TEMPSID;
  
  structure_list.Insert(strdefptr);
RECOVER

ENDSEQ
  IUnlock();
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  strnames - Type name
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
#define    MOD_ID  "ProvideStructDcl"

DBStructDef *Dictionary :: ProvideStructDcl (char *strnames, int16 strsid, int32 intlen, int32 extlen, TYP_TYPES metatype, SDB_ST strtype, int16 basecount, int16 attrcount, int16 refrcount, int16 rshpcount, char *idkeynames, logical w_vf_opt, int16 w_schema_version, logical w_versioning, logical glob_identity )
{
  TypeKey tkey(strnames,SYS_NSID);
  return( ProvideStructDcl(tkey,strsid,intlen,extlen,metatype,
                           strtype,basecount,attrcount,refrcount,
                           rshpcount,idkeynames,w_vf_opt,
                           w_schema_version,w_versioning,
                           glob_identity)                    );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDcl"

DBStructDef *Dictionary :: ProvideStructDcl (TypeKey &tkey )
{
  DBStructDef            *strdefptr = NULL;
BEGINSEQ
  ILock(YES);
  if ( !(strdefptr = tkey ? new DBStructDef(tkey,UNDEF,UNDEF,UNDEF,
                                             TYP_Structure,ST_USER,
                                                UNDEF,UNDEF,UNDEF,UNDEF)
                              : new DBStructDef() ) ) SDBERR(95)
                              
  strdefptr->smcbacc = strdefptr;
  structure_list.Insert(strdefptr);
RECOVER

ENDSEQ
  IUnlock();
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  ProvideStructDef - 



\return strdef - Structure definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDef"

DBStructDef *Dictionary :: ProvideStructDef (char *scoped_name )
{
  TypeKey           tkey(this,scoped_name);

  return( ProvideStructDef(tkey) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  scoped_name - 
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDef"

DBStructDef *Dictionary :: ProvideStructDef (char *scoped_name, uint8 schemaversion )
{
  TypeKey           tkey(this,scoped_name);
  DBStructDef      *strdef = NULL;
BEGINSEQ
  if ( !tkey )                                       SDBERR(99)
  
  if ( strdef = GetStructDef(tkey.Name(),tkey.GetID(),schemaversion) )   
    if ( strdef->smcbityp )                          LEAVESEQ
  
  SDBEV1(scoped_name,UNDEF)
  strdef = ProvideStructDef(tkey,schemaversion);


RECOVER
  strdef = NULL;
ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDef"

DBStructDef *Dictionary :: ProvideStructDef (TypeKey &tkey )
{
  DBStructDef      *strdef = NULL;
BEGINSEQ
  if ( strdef = GetStructDef(tkey) )   
    if ( strdef->smcbityp )                          LEAVESEQ
  
  strdef = CreateStructDef(tkey,strdef);
ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  i04 - 



\param  tkey - 
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDef"

DBStructDef *Dictionary :: ProvideStructDef (TypeKey &tkey, uint8 schemaversion )
{
  DBStructDef      *strdef = NULL;
BEGINSEQ
  if ( !(strdef = ProvideStructDef(tkey)) )          ERROR

  if ( schemaversion != CUR_VERSION )
    strdef = GetStructDef(tkey.Name(),tkey.GetID(),schemaversion); 

RECOVER
  strdef = NULL;
ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  sid - 
\param  schemaversion - Scheme version
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStructDef"

DBStructDef *Dictionary :: ProvideStructDef (int16 sid, uint8 schemaversion )
{
  char              strname[ID_SIZE];
  DBStructDef      *strdefptr = NULL;
  int32             indx0 = 0;
  PropertyHandle    strpi;
  TypeKey           tkey;
  logical           reserved = NO;

BEGINSEQ
  ILock(YES);
  *strname = 0;  
  
  while ( strdefptr = structure_list.Get(indx0++) )
    if ( strdefptr->smcbityp == sid )
    {  
      if ( strdefptr->get_schema_ver() == schemaversion )
                                                     LEAVESEQ
      tkey = strdefptr->GetTypeKey();  
      break;
    }
    
  if ( !tkey )
  {
    reserved = Reserve_struct_pi(strpi);
    if ( strpi.SetOrder("sk_TypeID") )     ERROR
    if ( strpi((char *)&sid) )
      strpi.ExtractKey(tkey.GetKey());
    strpi.SetOrder();
  }
    
  if ( !tkey || !(strdefptr = ProvideStructDef(tkey,schemaversion)) )      
                                                     ERROR
RECOVER
  strdefptr = NULL;

ENDSEQ
  Release_struct_pi(reserved);
  IUnlock();
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  ProvideTempStructDef - 



\return strdef - Structure definition

\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideTempStructDef"

DBStructDef *Dictionary :: ProvideTempStructDef (char *scoped_name )
{
  DBStructDef      *strdef = NULL;
  TypeKey           tkey(this,scoped_name);

BEGINSEQ
  SDBEV1(tkey.Name(),ID_SIZE) 
  if ( !(strdef = GetStructDef(tkey)) )
  {
    if ( !(strdef = dictionary->ProvideStructDcl(tkey,dictionary->GetTempStructID(),
                                   UNDEF,UNDEF,TYP_Structure,ST_USER,UNDEF,UNDEF,
                                   UNDEF,UNDEF)) )   ERROR
    strdef->smcbfmcl = new DBFieldList(UNDEF);
  
    strdef->smcbsts.stssusr3();
  }
RECOVER
  strdef = NULL;
ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  ProvideType - 



\return strdef - Structure definition

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideType"

DBStructDef *Dictionary :: ProvideType (PropertyHandle &ph )
{

if ( sys_version > 17 )
{
  TypeKey        tkey(this,ph.GetString("scope"),
                           ph.GetString("ddetype"));
                             
  return( tkey.GetID() >= 0 ? ProvideStructDef(tkey) 
                             : NULL                    );
}
else
{
  TypeKey        tkey(ph.GetString("ddetype"),0);
                             
  return( tkey.GetID() >= 0 ? ProvideStructDef(tkey) 
                             : NULL                    );
}


}

/******************************************************************************/
/**
\brief  ReadSD - 



\return strdefptr - 

\param  strpi - 
\param  tkey - 
\param  strdefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadSD"

DBStructDef *Dictionary :: ReadSD (PropertyHandle &strpi, TypeKey &tkey, DBStructDef *strdefptr )
{

BEGINSEQ
  ILock(YES);
  
  SDBEV1(tkey.Name(),ID_SIZE)
  if ( !tkey )                                       SDBERR(20)
  
  if ( !strdefptr )
    if ( !(strdefptr = ProvideStructDcl(tkey)) )     ERROR
  if ( strdefptr->smcbsts.stscerr() )                SDBIERR(20)
  
  if ( !strpi(tkey.GetKey()) )                       SDBERR(20)
  if ( !strpi.IsTrue("checked") )                    SDBERR(136)

// so geht das nicht. smceodaba ist ein Auslaufmodell und nicht mehr g¸ltig    
//if ( strpi.GPH("smceodaba")->GetID(0L) && !test_opt && 
  if ( !test_opt && !strpi.IsTrue("ready") )         SDBERR(136)
       
  if ( strdefptr->FillStructure(this,strpi) )        ERROR

RECOVER
  if ( strdefptr )
    strdefptr->smcbsts.stsserr();
  strdefptr = NULL;
ENDSEQ
  IUnlock();
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  ReadVD - Create view definition

        The  function creates  a view  definition (DBViewDef) from an externally
        defined view (SDB_View). The structure name

\return structdef - 

\param  tkey - 
\param  strdefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadVD"

DBStructDef *Dictionary :: ReadVD (TypeKey &tkey, DBStructDef *strdefptr )
{

BEGINSEQ
  ILock(YES);
  
  SDBEV1(tkey.Name(),ID_SIZE)
  if ( !tkey )                                      SDBERR(20)
  
  if ( !strdefptr )
    if ( !(strdefptr = ProvideStructDcl(tkey)) )     ERROR
  if ( strdefptr->smcbsts.stscerr() )                SDBERR(20)
  if ( !view_pi->Get(tkey.GetKey()) )               SDBERR(137)
  if ( !view_pi->IsTrue("checked") )                 SDBERR(136)
  
  if ( strdefptr->FillView(this,*view_pi) )          ERROR
  

RECOVER
  strdefptr = NULL;
ENDSEQ
  view_pi->Cancel();
  IUnlock();
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  ReadVL - 



\return csdefptr - 

\param  tkey - 
\param  strdefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadVL"

DBStructDef *Dictionary :: ReadVL (TypeKey &tkey, DBStructDef *strdefptr )
{
  DBFieldList          *fieldlist;
  DBExtend             *extdef;
  DBFieldDef            fmcbstr;
  logical               extcs  = 0;
BEGINSEQ
  ILock(YES);
  
  SDBEV1(tkey.Name(),ID_SIZE)
  
  if ( !codeset_pi->Get(tkey.GetKey()) )             ERROR
  
  if ( !strdefptr )
    if ( !(strdefptr = ProvideCSDecl(tkey,strdefptr,codeset_pi->GetInt("itype"))) )
                                                     ERROR
  
  if ( dictionary )
  {
    if ( !(extdef = CreateExtentDef(tkey)) )         ERROR
    strdefptr->smcbacc = (acc *)extdef->get_cs_values();
    if ( !strdefptr->smcbityp )
      strdefptr->smcbityp = TEMPSID;
    strdefptr->smcbatyp = AT_CODE;
  }
  else 
  {
    strdefptr->smcbacc  = new acc(NO);
    strdefptr->smcbatyp = AT_NONE;
  }
RECOVER
  strdefptr = NULL;
ENDSEQ
  IUnlock();
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  Release_extent_pi - 




\param  reserved - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release_extent_pi"

void Dictionary :: Release_extent_pi (logical reserved )
{

  if ( reserved )
    extpi_locked = NO;


}

/******************************************************************************/
/**
\brief  Release_struct_pi - 




\param  reserved - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release_struct_pi"

void Dictionary :: Release_struct_pi (logical reserved )
{

  if ( reserved )
    strpi_locked = NO;


}

/******************************************************************************/
/**
\brief  Release_type_pi - 




\param  reserved - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release_type_pi"

void Dictionary :: Release_type_pi (logical reserved )
{

  if ( reserved )
    typepi_locked = NO;


}

/******************************************************************************/
/**
\brief  RemoveExpression - 




\param  expr_decl - 
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveExpression"

void Dictionary :: RemoveExpression (OPDecl *expr_decl, DBStructDef *strdef )
{

  if ( strdef )
    strdef->RemExpr(expr_decl);
  else if ( expression_list )
    expression_list->Remove(expr_decl);

// kein delete!! wird aus OPAccessPathDecl Destructor aufgerufen


}

/******************************************************************************/
/**
\brief  RemoveExtentDef - Remove extent definition

        The  function  removes  an  extent  definition  from the dictionary. The
        extent definition is not available globally anymore.

\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveExtentDef"

DBExtend *Dictionary :: RemoveExtentDef (TypeKey &tkey )
{
  DBExtend      *extdef = NULL;
  ILock(YES);
  
  if ( extdef = extdef_list.Remove(tkey.GetKey()) )
    delete extdef;

  IUnlock();
  return(extdef);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  extname - Extent name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveExtentDef"

DBExtend *Dictionary :: RemoveExtentDef (char *extname, int32 nsid )
{
  TypeKey         tkey(extname,nsid);
  return( RemoveExtentDef(tkey) );

}

/******************************************************************************/
/**
\brief  RemoveStructDef - Remove internal structure definition from dictionary



\return strdef - Structure definition
-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveStructDef"

StructDef *Dictionary :: RemoveStructDef (TypeKey &tkey )
{
  StructDef              *strdef = NULL;
  ILock(YES);
  if ( strdef = GetStructDef(tkey) )
    structure_list.RemoveAt();
  IUnlock();
  return(strdef);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  strname - Type name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveStructDef"

StructDef *Dictionary :: RemoveStructDef (char *strname, int32 nsid )
{
  TypeKey    tkey(strname,nsid);
  return ( RemoveStructDef(tkey) );

}

/******************************************************************************/
/**
\brief  Reserve_extent_pi - 



\return reserved - 

\param  extpi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve_extent_pi"

logical Dictionary :: Reserve_extent_pi (PropertyHandle &extpi )
{
  logical                 reserved = NO;
  if ( extpi_locked )
    extpi.Open(*extend_pi);
  else
  {
    reserved = YES;
    extpi_locked = YES;
    extpi.Open(extend_pi);
  }

  return(reserved);
}

/******************************************************************************/
/**
\brief  Reserve_struct_pi - 



\return reserved - 

\param  strpi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve_struct_pi"

logical Dictionary :: Reserve_struct_pi (PropertyHandle &strpi )
{
  logical                 reserved = NO;
  if ( strpi_locked )
    strpi.Open(*struct_pi);
  else
  {
    reserved = YES;
    strpi_locked = YES;
    strpi.Open(struct_pi);
  }

  return(reserved);
}

/******************************************************************************/
/**
\brief  Reserve_type_pi - 



\return reserved - 

\param  type_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve_type_pi"

logical Dictionary :: Reserve_type_pi (PropertyHandle &type_ph )
{
  logical                 reserved = NO;
  if ( typepi_locked )
    type_ph.Open(*type_pi);
  else
  {
    reserved = YES;
    typepi_locked = YES;
    type_ph.Open(type_pi);
  }

  return(reserved);
}

/******************************************************************************/
/**
\brief  SetLastSchemaVersion - 




\param  schema_version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastSchemaVersion"

void Dictionary :: SetLastSchemaVersion (int16 schema_version )
{

  last_schemav = schema_version;

}

/******************************************************************************/
/**
\brief  SetupEnumeration - 



\return term - Termination code

\param  strnames - Type name
\param  value_list - 
\param  base_type - 
\param  ecount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupEnumeration"

logical Dictionary :: SetupEnumeration (char *strnames, ENUM_Value **value_list, char *base_type, int16 ecount )
{
  TypeKey          tkey(strnames,0);
  DBStructDef     *strdefptr = NULL;
  DBExtend        *extdef;
  logical          term      = NO;
BEGINSEQ
// called from csysstr.h
  if ( IsSystemObject() )                            LEAVESEQ
    
  if ( !(strdefptr = (DBStructDef *)GetStructDef(tkey)) )
                                                     SDBERR(20)

  extdef = new DBExtend(this,base_type,value_list,strdefptr,ecount);
  
  strdefptr->Setup(this,extdef->get_cs_values());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupStructDef - 



\return term - Termination code

\param  strnames - Type name
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
#define    MOD_ID  "SetupStructDef"

logical Dictionary :: SetupStructDef (char *strnames, SDB_BaseStruct **baselist, SDB_Attribute **attrlist, SDB_Reference **refrlist, SDB_Relationship **rshplist, SDB_Key *dbklistptr, int16 keycount, int8 w_alignment, int32 w_resid )
{
  TypeKey          tkey(strnames,0);
  DBStructDef     *strdefptr = NULL;
  logical          term = NO;
BEGINSEQ
  if ( !(strdefptr = (DBStructDef *)GetStructDef(tkey)) )
                                                     SDBERR(20)

  if ( !strdefptr->Setup(this,baselist,attrlist,refrlist,rshplist,
                        dbklistptr,keycount,w_alignment,w_resid) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupTempStructures - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTempStructures"

logical Dictionary :: SetupTempStructures ( )
{
  DBStructDef            *strdef;
  DBExtend               *extdef;
  BTI(DBStructDef)        structures(structure_list);
  BTI(DBExtend)           extents(extdef_list);
  int32                   intpos = 0;
  int32                   extpos = 0;
  int32                   netpos = 0;
  int8                    max_aligned = 0;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  ILock(YES);
  
  while ( strdef = structures.Get(indx0++) )
    if ( strdef->smcbsts.stscusr3() )  // temporary structure
      if ( !strdef->Setup(this) )                    ERROR

  indx0 = 0;
  while ( extdef = extents.Get(indx0++) )
    if ( extdef->fmcbvirt )            // temporary extent
    {
      if ( !extdef->GetDBStruct(this) )
        extdef->SetupReference(intpos,extpos,netpos,UNDEF,max_aligned,NO);
      if ( extdef->SetupIndexList() )                ERROR
    }
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
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

logical Dictionary :: Unlock ( )
{
  logical                 term = NO;
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateVersion - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateVersion"

logical Dictionary :: UpdateVersion ( )
{

BEGINSEQ
  while ( (version = GetVersion()) < last_schemav )
  {
    tim::timestp(10);
    NewVersion();                                     SDBCERR
    SetVersion(version+1);
    UpdateVersionList();
  }
RECOVER

ENDSEQ
  return(YES);
}

/******************************************************************************/
/**
\brief  UpdateVersionList - Set current version



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateVersionList"

logical Dictionary :: UpdateVersionList ( )
{
  OBH_ListEntry          *obh_entry;
  int32                   indx = 0;
  logical                 term = NO;
  while ( obh_entry = obh_list->GetEntry(++indx) )
    if ( obh_entry->get_ob_handle() )
      obh_entry->set_version(obh_entry->get_ob_handle()->get_version());
  
  obh_list->SortTable(UNDEF,UNDEF,UNDEF);
  
  
  
  


  return(term);
}

/******************************************************************************/
/**
\brief  ~Dictionary - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Dictionary"

     Dictionary :: ~Dictionary ( )
{
  OPDecl              *expr_decl;
  CloseDictionary();

  if ( expression_list )
    while ( expr_decl = expression_list->GetTail() )
      delete expr_decl;  
  delete expression_list;
  expression_list = NULL;
  
  delete expression_parser;
  expression_parser = NULL;

}


