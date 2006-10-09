/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    sSDB_ValueList



\date     $Date: 2006/05/03 17:35:59,56 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_ValueList"

#include  <pops7.h>
#include  <ssSDB_ValueList.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  CTX_Structure_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_ValueList :: Create (CTX_Structure **CTX_Structure_ptrp )
{

  *CTX_Structure_ptrp = new sSDB_ValueList();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreated

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sSDB_ValueList :: DBCreated ( )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  logical            term    = NO;
  *GPH("typetype")    = "TYP_Codeset";
  *GPH("access_type") = "AT_CODE";
  return(term);
}

/******************************************************************************/
/**
\brief  sSDB_ValueList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_ValueList"

     sSDB_ValueList :: sSDB_ValueList ( )
                     : CTX_Structure()
{
}

/******************************************************************************/
/**
\brief  ~sSDB_ValueList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_ValueList"

     sSDB_ValueList :: ~sSDB_ValueList ( )
{
}


