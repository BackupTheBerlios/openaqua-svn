/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBExtend

\brief    Database extent
          The  internal  presentation  of  a  database extent is a picture of an
          external  extent  definition.  It  can  be used for providing internal
          extent  definitions  while  running  an  application. You may also use
          DBExtent  constructors for reading external extent definition into the
          internal presentation.
          fmcbvirt - indicates transient (osi) extent.

\date     $Date: 2006/07/31 12:08:08,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBExtend"

#include  <popa7.h>
#ifndef   DLL_DBExtend_HPP
#define   DLL_DBExtend_HPP
#include  <sDBExtend.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sENUM_Value.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sLACObject.hpp>
#include  <sSDB_Extend.hpp>
#include  <sSDB_Index.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_ViewExtent.hpp>
#include  <sStructDef.hpp>
#include  <ssmcb.hpp>
#include  <sDBExtend.hpp>


/******************************************************************************/
/**
\brief  AddEnumValue - 



\return term - Termination code

\param  csentry - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEnumValue"

logical DBExtend :: AddEnumValue (ENUM_Value *csentry )
{
  logical                 term = NO;
BEGINSEQ
  if ( !cs_values )                                  SDBERR(99)

  cs_values->AddValue(csentry);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBExtend - 



-------------------------------------------------------------------------------
\brief  i06 - Define extent frominternal field definition

        The  function  provides  an  extent  definition  fron  an internal field
        definition.  Indexes set in the field  definition are made available for
        the extent.

\param  fielddef - Internal field defintion
\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (DBFieldDef *fielddef, char *extnames )
                     : DBFieldDef (),
  base_extend(new DLL(DBExtend)),
  derived_extends(new DLL(DBExtend)),
  cs_values(NULL),
  intersect(NO),
  union_set(NO),
  disjunct(NO),
  controlled(NO),
  acctype(AT_ODABA),
  copy_def(YES)
{
  char       string[ID_SIZE+1];
// Dictionary::CreateTempExtent
  *(DBFieldDef *)this = *fielddef;

  if ( extnames )
  {
    gvtxstb(fmcbname,extnames,ID_SIZE);
    SetExtent(gvtxbts(string,extnames,ID_SIZE));
  }
  set_mb_number(TEMP_MAIN);
  set_log_reference(YES);            // temporärer Extent
  set_transient(NO);
  set_update(YES);

  SetupNameKey();

}

/******************************************************************************/
/**
\brief  i1 - Dummy constructor

        This constructor creates an empty extent definition.

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend ( )
                     : DBFieldDef(), 
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  union_set(NO), 
  intersect(NO),  
  disjunct(NO),
  controlled(NO), 
  cs_values(NULL),
  acctype(AT_NONE),
  copy_def(NO)
{



}

/******************************************************************************/
/**
\brief  i2 - Define extent from external extent definition

        This  constructor creates  an extent  from an external extent definition
        (SDB_Extent).  The extent  definition is  connected to the dictionary as
        dictionary   resource   (and   thus,   made   globally  available). This
        definition  should not be deleted by the application. It will be deleted
        automatically  by the dictionary. When the definition must be deleted in
        the  application,  use  RemoveExtentDef()  before  to remove it from the
        dictionary.

\param  ph - 
\param  dictptr - Dictionary handle
\param  dbstrdef - Structure definition
\param  baseext - Base extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (PropertyHandle &ph, Dictionary *dictptr, DBStructDef *dbstrdef, DBExtend *baseext )
                     : DBFieldDef(dictptr,ph,dbstrdef,NULL,NO,
NO,NO,NO,ph.GetArea("sys_ident"),NULL), 
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  union_set(ph.IsTrue("union_set")),
  intersect(ph.IsTrue("intersect")),
  disjunct(ph.IsTrue("disjunct")),
  controlled(ph.IsTrue("controlled")),
  cs_values(NULL),
  acctype((SDB_AT)ph.GetInt("ddeatyp")),
  copy_def(NO)
{
  int32         indx0 = 0;
  DBExtend    *extdef;
BEGINSEQ
// LDictionary::CreateExtentDef (hierarchical extent)  
  set_shared(YES);   // kann raus, wenn shared richtig eingetragen ist
  if ( fmcbsmcb->smcbatyp == AT_ODABA )
  {
    set_multikey(YES);
    set_update(YES);
    fmcbrlev = R_REFR;
  }
  
  if ( dbstrdef && dbstrdef->smcbstyp != ST_CODE && memcmp(fmcbtype,dbstrdef->smcbname,ID_SIZE) )
  {
    fmcbityp = 0;
    fmcbsmcb = 0;
    dbstrdef = NULL;
  }

  if ( !dbstrdef || dbstrdef->smcbstyp != ST_CODE )
    if ( !(dbstrdef = GetDBStruct(dictptr)) )        ERROR
  set_version(dbstrdef->get_schema_ver());

  if ( (int)acctype == 8224 )
    acctype = (SDB_AT)dbstrdef->smcbatyp;
  
  SetupNameKey();
  dictptr->get_extdef_list().Insert(this);

  if ( CreateIndexList(ph,dictptr,YES) )     ERROR
    
  PH(&ph,sexbase)
  while ( sexbase(indx0++) )
  {
    extdef = baseext;
    if ( !baseext || memcmp(sexbase.GetArea("sys_ident"),baseext->fmcbname,ID_SIZE) )
      if ( !(extdef = dictptr->ProvideExtendDef(sexbase,dbstrdef,NULL)) )
                                                     ERROR
    if ( extdef )
      base_extend->AddTail(extdef);
  }
  
  indx0 = 0;
  PH(&ph,sexderi)
  while ( sexderi(indx0++) )
  {
    if ( !(extdef = dictptr->ProvideExtendDef(sexderi,dbstrdef,this)) )
                                                     ERROR
    derived_extends->AddTail(extdef);
  }

  if ( dbstrdef->smcbstyp == ST_CODE )               SDBERR(99)

RECOVER
  dictptr->get_extdef_list().Remove(this);

ENDSEQ

}

/******************************************************************************/
/**
\brief  i3 - Define extent from external reference definition

        This   constructor   creates   an   extent   from  an external reference
        definition (SDB_Reference).

\param  dictptr - Dictionary handle
\param  dbrptr - ODABA2 reference definition
\param  dbstrdef - Structure definition
\param  disjopt - Distinct derived extents
\param  unionopt - Union extent
\param  intersopt - Intersect extent
\param  contr_opt - Controlled extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (Dictionary *dictptr, SDB_Reference *dbrptr, DBStructDef *dbstrdef, logical disjopt, logical unionopt, logical intersopt, logical contr_opt )
                     : DBFieldDef(),
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  cs_values(NULL),
  intersect(intersopt),
  union_set(unionopt),
  disjunct(disjopt),
  controlled(contr_opt),
  acctype(dbrptr->get_ddeatyp()),
  copy_def(NO)
{
  SDB_Index *dbilistptr;
  char       string[ID_SIZE+1];
BEGINSEQ
// called from csysstr
  Fill(dbrptr,dictptr,NO);
  
  SetExtent(gvtxbts(string,dbrptr->get_sys_ident(),ID_SIZE));

  set_multikey(YES);
  set_update(YES);
  set_privilege(PI_Share); 
  fmcbrlev  = R_REFR;
  
  if ( !(fmcbsmcb = dbstrdef) )                        SDBERR(20)
  fmcbityp = fmcbsmcb->smcbityp;
    
  SetupNameKey();
  set_version(dbstrdef->get_schema_ver());
    
  if ( (int)acctype == 8224 )
    acctype = (SDB_AT)dbstrdef->smcbatyp;
  
  dbilistptr = (SDB_Index *)dbrptr->get_ddeindx().get_nodeptr();
  dbrptr->get_ddeindx().set_nodeptr(NULL);
  if ( CreateIndexList(dbilistptr,dbrptr->get_ddeprec()) )
                                                     ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i4 - Define extent from external simple reference definition

        This  constructor  creates  an  extent  from a simple external reference
        definition (SDB_Reference).

\param  ph - 
\param  dictptr - Dictionary handle
\param  dbstrdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (PropertyHandle &ph, Dictionary *dictptr, DBStructDef *dbstrdef )
                     : DBFieldDef(dictptr,ph,dbstrdef,NULL,NO,
NO,NO,NO,ph.GetArea("sys_ident"),NULL), 
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  union_set(NO),
  intersect(NO),
  disjunct(NO),
  controlled(NO),
  cs_values(NULL),
  acctype((SDB_AT)ph.GetInt("ddeatyp")),
  copy_def(NO)
{
  int32         indx0 = 0;
BEGINSEQ
  // nur für fremde Extents ->was könnte geprüft werden ??
  //  if ( fmcbsmcb->smcbatyp == AT_ODABA )
  //    multikey = YES;
  //  if ( !dbstrdef || dbstrdef->smcbstyp == ST_CODE )  ERROR

  set_owning(YES);
  set_update(YES);
  fmcbrlev = R_REFR;
  
  SetupNameKey();
  dictptr->get_extdef_list().Insert(this);
  set_version(dbstrdef->get_schema_ver());

  if ( CreateIndexList(ph,dictptr,NO) )              ERROR
RECOVER
  dictptr->get_extdef_list().Remove(this);

ENDSEQ

}

/******************************************************************************/
/**
\brief  i5 - 



\param  dictptr - Dictionary handle
\param  dbstrdef - Structure definition
\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (Dictionary *dictptr, DBStructDef *dbstrdef, PropertyHandle &ph )
                     : DBFieldDef(dictptr,ph,dbstrdef,NULL,NO,
NO,NO,NO,ph.GetArea("sys_ident"),NULL), 
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  union_set(NO),
  intersect(NO),
  disjunct(NO),
  controlled(NO),
  cs_values(NULL),
  acctype((SDB_AT)ph.GetInt("ddeatyp")),
  copy_def(NO)
{

BEGINSEQ
  acctype  = AT_VIEW;
  fmcbrlev = R_REFR;
  
  SetupNameKey();
  dictptr->get_extdef_list().Insert(this);
  set_version(dbstrdef->get_schema_ver());

  if ( CreateIndexList(ph,dictptr,NO) )              ERROR

RECOVER
  dictptr->get_extdef_list().Remove(this);
ENDSEQ

}

/******************************************************************************/
/**
\brief  i6 - Create definition for temporary extent

        This  is a sort  of copy and  rename constructor, that creates a, extent
        definition  according to  the definition  passed to the constructor. The
        new extent definition describes a temporary extent always.

\param  db_ext_ref - 
\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (DBExtend &db_ext_ref, char *extnames )
                     : DBFieldDef (),
  base_extend(new DLL(DBExtend)),
  derived_extends(new DLL(DBExtend)),
  cs_values(db_ext_ref.get_cs_values()),
  intersect(db_ext_ref.get_intersect()),
  union_set(db_ext_ref.get_union_set()),
  disjunct(db_ext_ref.get_disjunct()),
  controlled(NO),
  acctype(db_ext_ref.get_acctype()),
  copy_def(YES)
{
  char       string[ID_SIZE+1];
  *(DBFieldDef *)this = *(DBFieldDef *)&db_ext_ref;

  if ( extnames )
  {
    gvtxstb(fmcbname,extnames,ID_SIZE);
    SetExtent(gvtxbts(string,extnames,ID_SIZE));
  }
  set_mb_number(TEMP_MAIN);
  set_log_reference(YES);            // temporärer Extent
  set_owning(NO);
  set_update(YES);
  
  SetupNameKey();

}

/******************************************************************************/
/**
\brief  i7 - 



\param  dictptr - Dictionary handle
\param  cs_ph - 
\param  dbstrdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (Dictionary *dictptr, PropertyHandle *cs_ph, DBStructDef *dbstrdef )
                     : DBFieldDef(), 
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  union_set(NO),
  intersect(NO),
  disjunct(NO),
  controlled(NO),
  cs_values(NULL),
  acctype(AT_ODABA),
  copy_def(NO)
{
  int32         indx0 = 0;
  DBExtend    *extdef;
BEGINSEQ
  if ( !cs_ph->IsPositioned() )                     SDBERR(99)
  
  type_key.Initialize(dictptr,cs_ph->GetArea("scope"),cs_ph->GetArea("sys_ident"));

  InitEnumExtent(dictptr,dbstrdef,type_key.Name(),type_key.GetID());

  if ( !(cs_values = new ENUM_ValueList(cs_ph->GPH("values"))) )
                                                     SDBERR(95)
                                                     SDBCERR

RECOVER
  dictptr->get_extdef_list().Remove(this);
  delete cs_values;
  cs_values = NULL;

ENDSEQ

}

/******************************************************************************/
/**
\brief  i8 - 



\param  dictptr - Dictionary handle
\param  base_type - 
\param  value_list - 
\param  dbstrdef - Structure definition
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBExtend"

     DBExtend :: DBExtend (Dictionary *dictptr, char *base_type, ENUM_Value **value_list, DBStructDef *dbstrdef, int32 count )
                     : DBFieldDef(), 
  base_extend(new DLL(DBExtend)), 
  derived_extends(new DLL(DBExtend)), 
  union_set(NO),
  intersect(NO),
  disjunct(NO),
  controlled(NO),
  cs_values(NULL),
  acctype(AT_ODABA),
  copy_def(NO)
{
  int32         indx0 = 0;
  DBExtend    *extdef;
BEGINSEQ
  InitEnumExtent(dictptr,dbstrdef,dbstrdef->smcbname,dbstrdef->smcbnsid);
 
  if ( !(cs_values = new ENUM_ValueList(value_list,base_type,count)) )
                                                     SDBERR(95)
                                                     SDBCERR

RECOVER
  dictptr->get_extdef_list().Remove(this);
  delete cs_values;
  cs_values = NULL;

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetBaseExtent - 



\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - Get base extent by position

        This  implementation searches for  the extent in  the extent list at the
        position  in  the  list.  This  function  can  be  used to list all base
        extents  for  an  extent.  The  function  returns  NULL,  when no (more)
        extents could be found at the given position.

\param  extent_pos - Extent position in the list
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseExtent"

DBExtend *DBExtend :: GetBaseExtent (int16 extent_pos )
{
  DBExtend               *extdef = NULL;
  base_extend->GoTop();
  for (; extent_pos >= 0 && (extdef = base_extend->GetNext()); extent_pos-- ) ;
  return(extdef);
}

/******************************************************************************/
/**
\brief  i1 - Get base extent by name

        This  implementation searches for the extent in the extent list with the
        name  passed to the function. The  function returns NULL, when no extent
        with the given name has been foubd in the list of base extents.

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseExtent"

DBExtend *DBExtend :: GetBaseExtent (char *extnames )
{
  DBExtend               *extdef = NULL;
  char                    name[ID_SIZE];
BEGINSEQ
  gvtxstb(name,extnames,ID_SIZE);
  base_extend->GoTop();
  while ( extdef = base_extend->GetNext() )
    if ( !memcmp(name,extdef->get_extend(),ID_SIZE) )   LEAVESEQ

ENDSEQ
  return(extdef);
}

/******************************************************************************/
/**
\brief  GetDerivedExtent - 



\return extdef - Internal extent definition
-------------------------------------------------------------------------------
\brief  i0 - Get derived extent by position

        This  implementation searches for  the extent in  the extent list at the
        position  in  the  list.  This  function can be used to list all derived
        extents  for  an  extent.  The  function  returns  NULL,  when no (more)
        extents could be found at the given position.

\param  extent_pos - Extent position in the list
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDerivedExtent"

DBExtend *DBExtend :: GetDerivedExtent (int16 extent_pos )
{
  DBExtend               *extdef = NULL;

  derived_extends->GoTop();
  for (; extent_pos >= 0 && (extdef = derived_extends->GetNext()); extent_pos-- ) ;
  return(extdef);
}

/******************************************************************************/
/**
\brief  i1 - Get derived extent by name

        This  implementation searches for the extent in the extent list with the
        name  passed to the function. The  function returns NULL, when no extent
        with the given name has been foubd in the list of derived extents.

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDerivedExtent"

DBExtend *DBExtend :: GetDerivedExtent (char *extnames )
{
  DBExtend               *extdef = NULL;
  char                    name[ID_SIZE];
BEGINSEQ
  gvtxstb(name,extnames,ID_SIZE);
  derived_extends->GoTop();
  while ( extdef = derived_extends->GetNext() )
    if ( !memcmp(name,extdef->get_extend(),ID_SIZE) )   LEAVESEQ

ENDSEQ
  return(extdef);
}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 DBExtend :: GetMainBase (ACObject *obhandle )
{

  return (   get_mb_number() == TEMP_MAIN 
           ? obhandle->get_db_handle()->GetTempMain()
           : get_mb_number() );


}

/******************************************************************************/
/**
\brief  GetNameKey - 



\return tkey - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNameKey"

TypeKey &DBExtend :: GetNameKey ( )
{

  return(type_key);

}

/******************************************************************************/
/**
\brief  HasValues - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasValues"

logical DBExtend :: HasValues ( )
{

  return(cs_values ? cs_values->HasValues() : NO);

}

/******************************************************************************/
/**
\brief  InitEnumExtent - 




\param  dictptr - Dictionary handle
\param  dbstrdef - Structure definition
\param  strnames - Type name
\param  nsid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitEnumExtent"

void DBExtend :: InitEnumExtent (Dictionary *dictptr, DBStructDef *dbstrdef, char *strnames, int32 nsid )
{
  int8        maxaln = 0;
  type_key.Initialize(strnames,nsid);
  memcpy(fmcbname,type_key.Name(),ID_SIZE);

  if ( !dbstrdef )
    dbstrdef  = dictptr->GetStructDef(type_key);
  memcpy(fmcbtype,dbstrdef->smcbname,ID_SIZE);

  SetExtent(type_key.Name());

  set_mb_number(TEMP_MAIN);
  set_log_reference(YES);            // temporärer Extent
  set_transient(NO);
  set_update(YES);

  fmcbrlev = R_REFR;
  fmcballoc_opt = YES;

  set_version(dbstrdef->get_schema_ver());
  SetupIntern(dbstrdef,type_key.Name(),NULL,NULL);
  fmcbesu(dbstrdef,0,0,maxaln);
  dictptr->get_extdef_list().Insert(this);



}

/******************************************************************************/
/**
\brief  IsTempExtent - 



\return cond - 

\param  lobhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTempExtent"

logical DBExtend :: IsTempExtent (LACObject *lobhandle )
{

  return ( get_mb_number() == TEMP_MAIN ||
           *fmcbname == '#'             ||
           (lobhandle && get_mb_number() == lobhandle->get_db_handle()->GetTempMain())
           ? YES : NO );


}

/******************************************************************************/
/**
\brief  SetValueList - 



\return cond - 

\param  dictionary - 
\param  vlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValueList"

logical DBExtend :: SetValueList (Dictionary *dictionary, ENUM_ValueList *vlist )
{
  DBStructDef     *strdefptr;
  logical          term = NO;
BEGINSEQ
  if ( cs_values && cs_values != vlist )
    delete cs_values;
  cs_values = vlist;

  SetupNameKey();

  if ( !(strdefptr = dictionary->GetStructDef(type_key)) )
                                                     ERROR

  strdefptr->Setup(dictionary,cs_values);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupNameKey - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNameKey"

void DBExtend :: SetupNameKey ( )
{

  type_key.SetName(fmcbname);
  type_key.SetNamespace(fmcbnsid);

}

/******************************************************************************/
/**
\brief  get_acctype - 



\return acctype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_acctype"

SDB_AT DBExtend :: get_acctype ( )
{


  return(acctype);
}

/******************************************************************************/
/**
\brief  get_disjunct - 



\return disjunct - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_disjunct"

logical DBExtend :: get_disjunct ( )
{


  return(this ? disjunct : NO);
}

/******************************************************************************/
/**
\brief  get_intersect - 



\return intersect - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_intersect"

logical DBExtend :: get_intersect ( )
{


  return(this ? intersect : NO);
}

/******************************************************************************/
/**
\brief  get_union_set - 



\return union_set - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_union_set"

logical DBExtend :: get_union_set ( )
{


  return( this ? union_set : NO);
}

/******************************************************************************/
/**
\brief  set_acctype - 




\param  acctype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_acctype"

void DBExtend :: set_acctype (SDB_AT acctype )
{

  DBExtend::acctype = acctype;

}

/******************************************************************************/
/**
\brief  set_disjunct - 




\param  disjopt - Distinct derived extents
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_disjunct"

void DBExtend :: set_disjunct (logical disjopt )
{

  disjunct = disjopt;

}

/******************************************************************************/
/**
\brief  set_intersect - 




\param  intersopt - Intersect extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_intersect"

void DBExtend :: set_intersect (logical intersopt )
{

  intersect = intersopt;

}

/******************************************************************************/
/**
\brief  set_union_set - 




\param  unionopt - Union extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_union_set"

void DBExtend :: set_union_set (logical unionopt )
{

  union_set = unionopt;

}

/******************************************************************************/
/**
\brief  ~DBExtend - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBExtend"

     DBExtend :: ~DBExtend ( )
{

  delete derived_extends;
  derived_extends = NULL;
  
  delete base_extend;
  base_extend = NULL;
  
  if ( fmcballoc_opt )  // cst vom Extend angelegt
    delete cs_values;
  cs_values = NULL;
  
  if ( !copy_def )
    Release();

  if ( get_prev_field() )
    delete (DBExtend *)get_prev_field();
  set_prev_field(NULL);

}


