/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    pc_SDB_ValueList

\brief    


\date     $Date: 2006/07/12 19:27:33,43 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_ValueList"

#include  <pops7.h>
#include  <spc_SDB_ValueList.hpp>


/******************************************************************************/
/**
\brief  GetDocFileName - 



\return filenames - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *pc_SDB_ValueList :: GetDocFileName (NString &nstring )
{

  nstring = "c";

  if ( IsPositioned() )
    nstring.Append(GPH("sys_ident")->GetString());

  nstring.Append(".h");
  return(nstring);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

\param  basetype - 
\param  scope - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical pc_SDB_ValueList :: Initialize (char *basetype, char *scope )
{
  logical                 term = NO;
  *GPH("scope")       = scope;
  *GPH("base_type")   = (char*)(basetype ? basetype : " ");
  *GPH("typetype")    = (int32)TYP_Codeset;
  *GPH("access_type") = (int32)AT_CODE;
  
  PH(this,itype)
  if ( !itype.GetInt() )
    itype = GetDBHandle().GetNewTypeID();

  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_ValueList - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_ValueList"

     pc_SDB_ValueList :: pc_SDB_ValueList (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


