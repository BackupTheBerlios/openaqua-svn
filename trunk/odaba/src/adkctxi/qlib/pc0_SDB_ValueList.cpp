/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi - 
\class    pc0_SDB_ValueList

\brief    


\date     $Date: 2006/06/22 18:58:08,65 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_SDB_ValueList"

#include  <padkctxi.h>
#include  <spc_SDB_Member.hpp>
#include  <spc0_SDB_ValueList.hpp>


/******************************************************************************/
/**
\brief  IsEnumeration - 


\return cond - 

\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

logical pc0_SDB_ValueList :: IsEnumeration (PropertyHandle *prophdl )
{
  NString     nstring;
  logical     cond = YES;
BEGINSEQ
  TypeKey    type_key(prophdl->GetDBHandle(),pc_SDB_Member(prophdl).GetScopedType(nstring));
  if ( !Get(type_key.GetKey()) )                    ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  pc0_SDB_ValueList - 



\param  obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_SDB_ValueList"

     pc0_SDB_ValueList :: pc0_SDB_ValueList (DBObjectHandle &obhandle )
                     : PropertyHandle (obhandle,"SDB_ValueList",PI_Read)
{



}


