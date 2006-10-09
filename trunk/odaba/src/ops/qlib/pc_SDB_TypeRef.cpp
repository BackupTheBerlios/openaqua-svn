/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    pc_SDB_TypeRef



\date     $Date: 2006/04/10 17:16:55,42 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_TypeRef"

#include  <pops7.h>
#include  <cIncRef_Level.h>
#include  <spc_SDB_TypeRef.hpp>


/******************************************************************************/
/**
\brief  SetCodeLevel


\param  codelev - 
\param  exact
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCodeLevel"

void pc_SDB_TypeRef :: SetCodeLevel (int16 codelev, logical exact )
{
  PropertyHandle   *code_level = GPH("code_level");
  PropertyHandle   *inc_level  = GPH("inc_level");
  if ( !exact )
  {
    codelev = MAX(codelev,code_level->GetInt());
    if ( inc_level->GetInt() >= codelev )
      codelev = 0;
  }

  *code_level = codelev;


}

/******************************************************************************/
/**
\brief  SetIncLevel


\param  inclev - 
\param  exact
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIncLevel"

void pc_SDB_TypeRef :: SetIncLevel (int16 inclev, logical exact )
{
  PropertyHandle   *inc_level = GPH("inc_level");
  if ( !exact )
    inclev = MAX(inclev,inc_level->GetInt());

  *inc_level = inclev;

}

/******************************************************************************/
/**
\brief  SetupReference

\return term

\param  inclev - 
\param  codelev - 
\param  gen_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReference"

logical pc_SDB_TypeRef :: SetupReference (int16 inclev, int16 codelev, logical gen_opt )
{
  PropertyHandle   *classname  = GPH("classname");
  PropertyHandle   *inc_level  = GPH("inc_level");
  PropertyHandle   *code_level = GPH("code_level");
  PropertyHandle   *generated  = GPH("generated");
  PropertyHandle   *type_ref   = GPH("type_ref");
  logical           term       = NO;
BEGINSEQ
  if ( NoWrite() )                                             SDBERR(99)
  
  if ( gen_opt )
    *generated = (logical)YES;
  
  SetIncLevel(inclev,NO);
  SetCodeLevel(codelev,NO);

  TypeKey   type_key(GetDBHandle(),classname->GetString());
  type_ref->Provide(type_key.GetKey());
  
  Save();                                                      SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_TypeRef


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_TypeRef"

                        pc_SDB_TypeRef :: pc_SDB_TypeRef (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


