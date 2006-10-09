/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    sSDB_BaseStruct



\date     $Date: 2006/05/13 18:04:40,64 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_BaseStruct"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <ssSDB_BaseStruct.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  strctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_BaseStruct :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_BaseStruct();
  return(NO);

}

/******************************************************************************/
/**
\brief  DBCreate

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical sSDB_BaseStruct :: DBCreate ( )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  *prophdl->GPH("ddeprv") = "ODC_public";
  return(NO);
}

/******************************************************************************/
/**
\brief  SetDefaultsForSpecialType

\return term

\param  dbhandle - 
\param  propnames
\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultsForSpecialType"

logical sSDB_BaseStruct :: SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  if ( !typenames || *typenames <= ' ' )
    typenames = propnames;

  return ( ((SDB_BaseStruct *)prophdl->Get().GetData())->
              Fill(dbhandle,propnames,typenames,NULL)     );


}

/******************************************************************************/
/**
\brief  sSDB_BaseStruct


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_BaseStruct"

     sSDB_BaseStruct :: sSDB_BaseStruct ( )
                     : sSDB_Member_base ()
{
}

/******************************************************************************/
/**
\brief  ~sSDB_BaseStruct


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_BaseStruct"

     sSDB_BaseStruct :: ~sSDB_BaseStruct ( )
{
}


