/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinSArrayObjEntry

\brief    


\date     $Date: 2006/03/12 19:21:20,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinSArrayObjEntry"

#include  <pdefault.h>
#include  <sBinSArrayObjEntry.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void BinSArrayObjEntry :: Initialize ( )
{

  object_id  = 0;


}

/******************************************************************************/
/**
\brief  SetIndex - 



\param  entry_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIndex"

void BinSArrayObjEntry :: SetIndex (uint64 entry_index )
{

  object_id = entry_index;


}


