/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    SDB_Type

\brief    Data types
          Data types are defined as data types of different categories. 
          Structures  of different types can be defined depending on the purpose
          of  use.  Usually,  structures  are  user-defined  types.  Internally,
          however,  key  structures  are  created  from  key  definitions  for a
          structure.  System structures refer  to structure definitions provided
          by  ODABA.  View  structures  are structures, which are implemented as
          views. 
          '

\date     $Date: 2006/04/13 14:24:27,64 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Type"

#include  <pops7.h>
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#ifndef   P_SDB_TypeRef_HPP
#define   P_SDB_TypeRef_HPP
#include  <sPI.hpp>
class       SDB_TypeRef;
PI_dcl     (SDB_TypeRef)
#endif
#include  <sSDB_Property.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Structure.hpp>
#include  <ssmcb.hpp>
#include  <sSDB_Type.hpp>


/******************************************************************************/
/**
\brief  CheckType - 


\return term

\param  dbhandle - 
\param  typtyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckType"

logical SDB_Type :: CheckType (DatabaseHandle &dbhandle, TYP_TYPES typtyp )
{
  TypeKey   type_key(sys_ident,namespace_id);
  logical   term = NO;
BEGINSEQ
  if ( typtyp == TYP_undefined )                     LEAVESEQ
    
  PI(SDB_Structure)   dbs_pi(dbhandle,"SDB_Structure",PI_Read);
                                                     SDBCERR
  if ( dbs_pi(type_key.GetKey()) )
  {
    if ( typtyp == TYP_Structure )                   LEAVESEQ
                                                     ERROR
  }

  PI(SDB_CodeSet)     cs_pi(dbhandle,"SDB_CodeSet",PI_Read);
                                                     SDBCERR
  if ( cs_pi(type_key.GetKey()) )  
  {
    if ( typtyp == TYP_Codeset )                     LEAVESEQ
                                                     ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExistCodeSet - 


\return ityp

\param  dbhandle - 
\param  datype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistCodeSet"

int16 __cdecl SDB_Type :: ExistCodeSet (DatabaseHandle &dbhandle, char *datype )
{
  TypeKey   type_key(datype,0);
  int16     ityp = UNDF;
BEGINSEQ
// --> pc_SDB_Type::GetTypeInfo(scoped_name,pstyp,pityp,idkeyn)

  PI(SDB_Type)  dbc_pi(dbhandle,"SDB_CodeSet",PI_Read); 
                                                     SDBCERR
  if ( dbc_pi(type_key.GetKey()) )
    if ( !(ityp = dbc_pi->get_itype()) )
      ityp = YES;
RECOVER
  ityp = UNDF;
ENDSEQ
  return(ityp);
}

/******************************************************************************/
/**
\brief  ExistStructure - 


\return ityp

\param  dbhandle - 
\param  datype - 
\param  pstyp - 
\param  idkeyn - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistStructure"

int16 __cdecl SDB_Type :: ExistStructure (DatabaseHandle &dbhandle, char *datype, int16 *pstyp, char *idkeyn )
{
  TypeKey      type_key(datype,0);
  int16        ityp = UNDF;
BEGINSEQ
// --> pc_SDB_Type::GetTypeInfo(scoped_name,pstyp,pityp,idkeyn)

  if ( pstyp )
    *pstyp   = UNDEF;
  if ( idkeyn )
    *idkeyn = ' ';  

  PI(SDB_Structure)  dbs_pi(dbhandle,"SDB_Structure",PI_Read);     
                                                     SDBCERR
  if ( dbs_pi(type_key.GetKey()) )
  {
    if ( !(ityp = dbs_pi->get_itype()) )
      ityp = YES;
    if ( pstyp )
      *pstyp = dbs_pi->get_smcestyp();
    if ( idkeyn )
      memcpy(idkeyn,dbs_pi->get_smceiksm(),ID_SIZE);
  }
RECOVER
  ityp = UNDF;
ENDSEQ
  return(ityp);
}

/******************************************************************************/
/**
\brief  GetAlignInfo - 


\return term

\param  strname - 
\param  propname - 
\param  size_info - 
\param  offset_info - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAlignInfo"

logical __cdecl SDB_Type :: GetAlignInfo (char *strname, char *propname, int16 &size_info, int16 &offset_info )
{
  char         strnames[ID_SIZE+1];  
  logical      term = NO;
  size_info   = 0;
  offset_info = 0;
  
  gvtxbts(strnames,strname,sizeof(strnames)-1);
  if ( !strcmp("SDB_Property",strnames) )
  {
#include <sSDB_Property.hpp>
    SDB_Property    testinst;
    testinst.GetAlignInfo(propname,size_info,offset_info);
  }
  else if ( !strcmp("SDB_Reference",strnames) )
  {
#include <sSDB_Reference.hpp>
    SDB_Reference   testinst;
    testinst.GetAlignInfo(propname,size_info,offset_info);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  GetTypeInfo - 


\return term

\param  dbhandle - 
\param  datype - 
\param  pstyp - 
\param  pityp - 
\param  idkeyn - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeInfo"

logical __cdecl SDB_Type :: GetTypeInfo (DatabaseHandle &dbhandle, char *datype, int16 *pstyp, int16 *pityp, char *idkeyn )
{
  logical      term = NO;
BEGINSEQ
// --> pc_SDB_Type::GetTypeInfo(scoped_name,pstyp,pityp,idkeyn)
  *pityp   = UNDEF;
  *pstyp   = UNDEF;
  *idkeyn = ' ';  

  SDBEV1(datype,ID_SIZE)
  SDBEV2(datype,ID_SIZE)

  if ( *datype == ' ' )                                ERROR
  
  if ( *pityp = dbhandle.GetDictionary().BaseType(datype) )
  {
    *pstyp = ST_BASE;                                   LEAVESEQ
  }  

  if ( *pityp = SDB_Type::ExistCodeSet(dbhandle,datype) )
  {
    *pstyp = ST_CODE;                                   LEAVESEQ
  }  

  if ( *pityp = SDB_Type::ExistStructure(dbhandle,datype,pstyp,idkeyn) ) 
                                                       LEAVESEQ
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetTypeType - 


\return typtyp - 

\param  dbhandle - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeType"

TYP_TYPES __cdecl SDB_Type :: GetTypeType (DatabaseHandle &dbhandle, char *names )
{
  TypeKey        type_key(names,0);
  TYP_TYPES      typtyp = TYP_undefined;
BEGINSEQ
  PI(SDB_Type)      typ_pi(dbhandle,"SDB_Type",PI_Read);
                                                     SDBCERR
  if ( typ_pi(type_key.GetKey()) )
  {
    typtyp = typ_pi->get_typetype();                 LEAVESEQ
  }
  
  PI(SDB_Type)      dsc_pi(dbhandle,"ODS_Class",PI_Read);  
                                                     SDBCERR
  if ( dsc_pi(type_key.GetKey()) )
  {
    typtyp = dsc_pi->get_typetype();                 LEAVESEQ
  }
  
  PI(SDB_Structure) dbs_pi(dbhandle,"SDB_Structure",PI_Read);
                                                     SDBCERR
  if ( dbs_pi(type_key.GetKey()) )
  {
    typtyp = dbs_pi->get_typetype();                 LEAVESEQ
  }
  
RECOVER

ENDSEQ
  return(typtyp);
}

/******************************************************************************/
/**
\brief  SDB_Type - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Type"

                        SDB_Type :: SDB_Type ( )
                     : SDB_Resource (),
  itype(UNDEF),
  access_type(AT_NONE),
  impl_ref()
{



}

/******************************************************************************/
/**
\brief  SetAccessType - 



\param  acctype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAccessType"

void SDB_Type :: SetAccessType (SDB_AT acctype )
{

  if ( this )
    access_type = acctype;

}

/******************************************************************************/
/**
\brief  SetInternType - 



\param  interntyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInternType"

void SDB_Type :: SetInternType (int16 interntyp )
{

  if ( this )
    itype = interntyp;

}

/******************************************************************************/
/**
\brief  SetType - 



\param  typtyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

void SDB_Type :: SetType (TYP_TYPES typtyp )
{

  if ( this )
    typetype = typtyp;

}

/******************************************************************************/
/**
\brief  ~SDB_Type - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Type"

                        SDB_Type :: ~SDB_Type ( )
{



}


