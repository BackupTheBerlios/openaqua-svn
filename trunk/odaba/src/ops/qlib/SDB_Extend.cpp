/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/16|13:28:01,81}|(REF)
\class    SDB_Extend

\brief    ODABA Extent
          Odaba  extents are specific collections, which allow storing instances
          on  a  database  object  level  in  an  ODABA  database.  Extents  are
          properties  of  database  objects  and  exist outside of any structure
          definition.  Extents are associated with a structure type, which might
          refer  to  VOID  type  for  untypical extends or to the base structure
          type  for  weak-typed  extents.  An  extent  may  define  one  or more
          indexes, but must have an identifying key index. 
          Typically,  there is  one extent  defined, which  does not have a base
          extents.  This is  called the  root extent,  which contains all global
          instances of the given type. 
          te.  Auto-ident keys  provide automatic  numbers for instances created
          in the collection.
          Key  components  may  define  ascending (default) or descending order.
          Since  this can be defined  on the level of  key components, it is not
          the  key  itself,  which  is  ascending or descending. Those modes can
          also  be mixed, which creates ascending/descending keys. Since this is
          not  an index feature,  several keys with  the same attributes must be
          defined  for  supporting  ascending  and descending orders at the same
          time.

\date     $Date: 2006/03/21 18:29:41,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Extend"

#include  <pops7.h>
#ifndef   P_SDB_ODABA_Str_HPP
#define   P_SDB_ODABA_Str_HPP
#include  <sPI.hpp>
class       SDB_ODABA_Str;
PI_dcl     (SDB_ODABA_Str)
#endif
#include  <sSDB_Index.hpp>
#include  <sSDB_ODABA_Str.hpp>
#include  <sSDB_Extend.hpp>


/******************************************************************************/
/**
\brief  AddToODABAStr - 


\return term

\param  pers_pi -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddToODABAStr"

logical SDB_Extend :: AddToODABAStr (PI(SDB_ODABA_Str) *pers_pi )
{
  int32       indx0 = 0;
  logical    term  = NO;
BEGINSEQ
  SDBEV1(sys_ident,ID_SIZE)
  SDBEV2(pers_pi->Get()->get_sys_ident(),ID_SIZE)
  
  if ( memcmp(ddetype,pers_pi->Get()->get_sys_ident(),ID_SIZE) )
  {
    if ( memcmp(ddetype,sys_ident,ID_SIZE) )
      memcpy(ddetype,pers_pi->Get()->get_sys_ident(),ID_SIZE);
  }
  
  TypeKey   ext_key(sys_ident,0);
  pers_pi->Get()->get_smceextd().Provide(ext_key.GetKey()); 
                                                     SDBCERR
  while ( sexbase(indx0++) )
    if ( sexbase->AddToODABAStr(pers_pi) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  dbhandle -
\param  strname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical SDB_Extend :: Initialize (DatabaseHandle &dbhandle, char *strname )
{
  logical                 term = NO;
  SDB_Reference::Initialize(dbhandle,strname);
  memcpy(ddetype,strname,ID_SIZE);
  if ( memcmp(sys_ident,strname,ID_SIZE) )
    owning = NO;
  
  create          = YES;
  clustered       = NO;
  update          = YES;
  multikey        = YES;

  controlled      = YES;
  intersect       = NO;
  union_set       = NO;
  disjunct        = NO;
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeCSRoot - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeCSRoot"

logical SDB_Extend :: InitializeCSRoot ( )
{

  owning = YES;
  create = YES;
  memcpy(ddetype,sys_ident,ID_SIZE);
  return(NO);
}

/******************************************************************************/
/**
\brief  ProvideExtendDef - 


\return term

\param  dbhandle -
\param  extname -
\param  strname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtendDef"

logical __cdecl SDB_Extend :: ProvideExtendDef (DatabaseHandle &dbhandle, char *extname, char *strname )
{
  SDB_Extend    *extptr = NULL;
  logical        term   = NO;
BEGINSEQ
  TypeKey          ext_key(extname,0);
  PI(SDB_Extend)   ext_pi(dbhandle,"SDB_Extend",PI_Write);  
                                                     SDBCERR
  extptr = ext_pi.Provide(ext_key.GetKey());         SDBCERR
  
  if ( *extptr->get_ddetype() > ' ' )
  {  
    if ( !memcmp(extptr->get_ddetype(),strname,ID_SIZE) ) LEAVESEQ
                                                     SDBERR(124)
  }
  
  if ( ext_pi.NoWrite() )                            LEAVESEQ
  
  if ( extptr->Initialize(dbhandle,strname) )        ERROR
  
  ext_pi.Modify();                                   SDBCERR
  ext_pi.Save();                                     SDBCERR
RECOVER
  if ( SDBERROR == 124 )
  {
    SDBEV1(extname,ID_SIZE)
    SDBEV2(strname,ID_SIZE)
  }
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideStrRoot - 


\return term

\param  dbhandle -
\param  strname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStrRoot"

logical __cdecl SDB_Extend :: ProvideStrRoot (DatabaseHandle &dbhandle, char *strname )
{
  logical        term = NO;
BEGINSEQ
  if ( !memcmp(strname,"MEMO ",5) )                  LEAVESEQ

  if ( ProvideExtendDef(dbhandle,strname,strname) )  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


