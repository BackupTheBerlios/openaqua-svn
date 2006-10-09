/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Type



\date     $Date: 2006/05/14 13:13:52,59 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Type"

#include  <pops7.h>
#include  <spc_SDB_Type.hpp>


/******************************************************************************/
/**
\brief  GetTypeInfo

\return term
-------------------------------------------------------------------------------
\brief  i00


\param  scoped_name
\param  pstyp
\param  pityp
\param  patyp
\param  idkeyn
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeInfo"

logical pc_SDB_Type :: GetTypeInfo (char *scoped_name, int32 *pstyp, int32 *pityp, int32 *patyp, char *idkeyn )
{
  PropertyHandle  *impl_ref = NULL;
  int32            ityp     = UNDEF;
  int32            styp     = UNDEF;
  int32            atyp     = UNDEF;
  logical          term     = NO;
BEGINSEQ
  if ( idkeyn )
    *idkeyn = 0;  

  if ( *scoped_name <= ' ' )                        ERROR
  
  if ( ityp = GetDictionary().BaseType(scoped_name) )
  {
    styp = ST_BASE;
    atyp = AT_ODABA;
  }
  else 
  {
    TypeKey   tkey(GetDBHandle(),scoped_name);
    if ( !Get(tkey.GetKey()) )                      ERROR
    if ( GetTypeInfo(pstyp ? &styp : NULL,
                     pityp ? &ityp : NULL,
                     patyp ? &atyp : NULL,idkeyn) ) ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  if ( pityp )
    *pityp   = ityp;
  if ( pstyp )
    *pstyp   = styp;
  if ( patyp )
    *patyp   = atyp;
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  pstyp
\param  pityp
\param  patyp
\param  idkeyn
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeInfo"

logical pc_SDB_Type :: GetTypeInfo (int32 *pstyp, int32 *pityp, int32 *patyp, char *idkeyn )
{
  PropertyHandle  *impl_ref = NULL;
  int32            ityp     = UNDEF;
  int32            styp     = UNDEF;
  int32            atyp     = UNDEF;
  logical          term     = NO;
BEGINSEQ
  if ( idkeyn )
    *idkeyn = 0;  

  if ( !IsPositioned() )                            ERROR
  
  ityp = GPH("itype")->GetInt();
  atyp = GPH("access_type")->GetInt();
    
  if ( !patyp && !idkeyn )                          LEAVESEQ

  if ( IsA("SDB_Structure") || IsA("SDB_ValueList") )
    impl_ref = this;
  else
    if ( !(impl_ref = GPH("impl_ref"))->Get(FIRST_INSTANCE) )
                                                    ERROR
  
  if ( impl_ref->IsA("SDB_ValueList") )
  {
    styp = ST_CODE;
    atyp = AT_ODABA;
  }
  else if ( impl_ref->IsA("SDB_Structure") )
  {
    styp = impl_ref->GPH("smcestyp")->GetInt();
    if ( idkeyn )
      strcpy(idkeyn,impl_ref->GPH("smceiksm")->GetString());
  }
  else                                            ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( pityp )
    *pityp   = ityp;
  if ( pstyp )
    *pstyp   = styp;
  if ( patyp )
    *patyp   = atyp;
  return(term);
}

/******************************************************************************/
/**
\brief  GetTypeKey

\return tkey

\param  tkey
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeKey"

TypeKey &pc_SDB_Type :: GetTypeKey (TypeKey &tkey )
{

BEGINSEQ
  tkey.Initialize("",0);
  
  if ( !IsPositioned() )                            ERROR
  
  tkey.Initialize(GetString("sys_ident"),
                  GetInt("namespace_id"));
RECOVER

ENDSEQ
  return(tkey);
}

/******************************************************************************/
/**
\brief  IsBaseType

\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBaseType"

logical pc_SDB_Type :: IsBaseType ( )
{

  return (   IsPositioned() &&
             GPH("smcestyp")->GetInt() == ST_BASE 
           ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsPersistent

\return cond - 

\param  pityp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPersistent"

logical pc_SDB_Type :: IsPersistent (int32 *pityp )
{
  int32       styp = 0;
  int32       atyp = 0;
  logical     cond = YES;
BEGINSEQ
  if ( GetTypeInfo(&styp,pityp,&atyp,NULL) )        ERROR

  switch ( styp )
  {
    case ST_BASE :                                  LEAVESEQ
    case ST_CODE :                                  LEAVESEQ
    default      : if ( atyp == AT_ODABA )          LEAVESEQ
  }

  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ScopedName

\return string

\param  string
\param  leng
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ScopedName"

char *pc_SDB_Type :: ScopedName (char *string, int16 leng )
{
  TypeKey    tkey;
  *string = 0;
  
  GetTypeKey(tkey);
  tkey.ScopedName(GetDBHandle(),string,leng);
  return(string);
}

/******************************************************************************/
/**
\brief  pc_SDB_Type

-------------------------------------------------------------------------------
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Type"

     pc_SDB_Type :: pc_SDB_Type (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{
}

/******************************************************************************/
/**
\brief  i01


\param  dbhandle - 
\param  accopt_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Type"

     pc_SDB_Type :: pc_SDB_Type (DatabaseHandle &dbhandle, PIACC accopt_w )
                     : PropertyHandle(dbhandle,"SDB_Type",accopt_w)
{
}

/******************************************************************************/
/**
\brief  i02


\param  dbhandle - 
\param  strnames
\param  accopt_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Type"

     pc_SDB_Type :: pc_SDB_Type (DatabaseHandle &dbhandle, char *strnames, PIACC accopt_w )
                     : PropertyHandle(dbhandle,strnames,accopt_w)
{
}


