/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    SystemDict

\brief    


\date     $Date: 2006/08/26 12:55:17,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SystemDict"

#include  <popa7.h>
#include  <OGUIDdef.h>
#ifndef   DLL_DBExtend_HPP
#define   DLL_DBExtend_HPP
#include  <sDBExtend.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sDBExtend.hpp>
#include  <sENUM_Value.hpp>
#include  <sSDB_Attribute.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Index.hpp>
#include  <sSDB_Key.hpp>
#include  <sSDB_Relationship.hpp>
#include  <sSystemDict.hpp>


/******************************************************************************/
/**
\brief  ProvideExtendDef - 



\return dbextdef - Extent definition

\param  sdbref - 
\param  disjopt - Distinct derived extents
\param  unionopt - Union extent
\param  intersopt - Intersect extent
\param  contr_opt - Controlled extent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendDef"

DBExtend *SystemDict :: ProvideExtendDef (SDB_Reference sdbref, logical disjopt, logical unionopt, logical intersopt, logical contr_opt )
{
  DBStructDef   *strdefptr;
  DBExtend      *oldext;
  DBExtend      *dbextdef;
BEGINSEQ
  TypeKey    tkey(sdbref.get_ddetype(),SYS_NSID);
  if ( !(strdefptr = GetStructDef(tkey)) )         SDBERR(20)

  if ( !(dbextdef = new DBExtend(this,&sdbref,strdefptr,disjopt,unionopt,intersopt,contr_opt)) ) 
                                                   SDBERR(95)
  if ( oldext = GetExtendDef(dbextdef->fmcbname,SYS_NSID) )
  {
    extdef_list.Remove(oldext); 
    dbextdef->SetPrevious(oldext);
  }
  extdef_list.Insert(dbextdef);

RECOVER
  dbextdef = NULL;
ENDSEQ
  return(dbextdef);
}

/******************************************************************************/
/**
\brief  Start - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical SystemDict :: Start ( )
{
  SystemDict  *dictptr = this;
  DBStructDef *structdef;
  DBStructDef *prev_structdef;

  ProvideStructDcl("CHAR"    ,T_CHAR    ,1    ,1    ,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("CCHAR"   ,T_CCHAR   ,1    ,1    ,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("DATE"    ,T_DATE    ,4    ,4    ,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("TIME"    ,T_TIME    ,4    ,4    ,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("LOGICAL" ,T_LO      ,1    ,1    ,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("INT"     ,T_INT     ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("UINT"    ,T_UINT    ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("VOID"    ,T_VOID    ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("MEMO"    ,T_MEMO    ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("BLOB"    ,T_BLOB    ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("STRING"  ,T_STRING  ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("OGUID"   ,T_GUID    ,16   ,16   ,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("GUID"    ,T_GUID    ,16   ,16   ,TYP_Base,ST_BASE,0,0,0,0);  // für Umstellung auf V8
  ProvideStructDcl("BIT"     ,T_BIT     ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("REAL"    ,T_REAL    ,UNDEF,UNDEF,TYP_Base,ST_BASE,0,0,0,0);
  ProvideStructDcl("PI"      ,ERIC      ,UNDEF,UNDEF,TYP_Structure,ST_SYS,0,0,0,0);
  dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("VOID","VOID",RL_direct,0,0,0,"",N,N,0), N,0,N,N,N,0,Y,NULL,0),N,N,N,N);
  
  StartBegin();  
  
//  StartVersion7();  // für Umstellung auf Systemversion 18
//  StartVersion7x(); // für Umstellung auf Systemversion 18
//  StartExtra7();    // für Umstellung auf Systemversion 18

if ( sys_version >=18 || sys_version == CUR_VERSION ) // not provided for SYSTEM_VERSION==17
{
  StartCurrent();  
  StartCurrentX();  
  StartExtra();  
}
  return(NO);
}

/******************************************************************************/
/**
\brief  StartBegin - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartBegin"

logical SystemDict :: StartBegin ( )
{
  SystemDict  *dictptr = this;
//bitte kleinschreibung fuer projekte beachten (unx kompatibilitaet)
#include <opi/h/csysstr.h>
#include <ops/h/csysstrE.h>
#include <sos/h/csysstr.h>  // Besonderheiten für CTX_Base beachten (csysstr.sav)

  return(NO);
}

/******************************************************************************/
/**
\brief  StartCurrent - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartCurrent"

logical SystemDict :: StartCurrent ( )
{
  SystemDict  *dictptr = this;
 #include <ops/h/csysstr.h>

// nur für Umstellung auf V8 erforderlich
 SDB_Index    ri_SDB_Type_SDB_TypeCSTemp[] = {
               SDB_Index("ik_Ident",SET_LARG,Y,N,Y,N,0),
              };
 dictptr->ProvideExtendDef(SDB_Reference(SDB_Member("SDB_TypeCSTemp","SDB_Type",RL_direct,0,0,0,"",N,N,0), N,0,Y,Y,N,0,N,ri_SDB_Type_SDB_TypeCSTemp,1,Y,Y,N),N,N,N,YES);
// ende Umstellung
  return(NO);
}

/******************************************************************************/
/**
\brief  StartCurrentX - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartCurrentX"

logical SystemDict :: StartCurrentX ( )
{
  SystemDict  *dictptr = this;
//  #include <OPS7/h/csysstrx.h>
  #include <ops/h/csysstrx.h>

  return(NO);
}

/******************************************************************************/
/**
\brief  StartExtra - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartExtra"

logical SystemDict :: StartExtra ( )
{
  SystemDict  *dictptr = this;
#ifndef __unix__
//  #include <oodbc7/h/csysstr.h>  wird für OODBC benötigt
#endif
  
//  #include <OPS7/h/fm_csysstr.h>
#include <functionalmodel/h/csysstr.h>
//060421:opa7 gibts nicht mehr!  #include <opa7/h/csysstr.h>
#include <opa/h/csysstr.h>
//  #include <OPI7/h/csysstr.h>

  return(NO);
}

/******************************************************************************/
/**
\brief  SystemDict - 




\param  cpath - Complete path
\param  accopt - Access mode
\param  w_netopt - Multi-user option
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemDict"

     SystemDict :: SystemDict (char *cpath, PIACC accopt, logical w_netopt, char sysenv )
                     : Dictionary (cpath,accopt,w_netopt,USHORTMAX,sysenv)
{



}

/******************************************************************************/
/**
\brief  ~SystemDict - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SystemDict"

     SystemDict :: ~SystemDict ( )
{



}


