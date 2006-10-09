/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    DBIndexList



\date     $Date: 2006/05/31 18:39:43,46 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBIndexList"

#include  <popa7.h>
#include  <sDBIndexList.hpp>


/******************************************************************************/
/**
\brief  DBIndexList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBIndexList"

     DBIndexList :: DBIndexList ( )
                     : DLO(DBIndex) (),
ReferenceObject (NO)
{
}

/******************************************************************************/
/**
\brief  GetIndexName

\return index_name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexName"

char *DBIndexList :: GetIndexName (int32 indx0 )
{
  char    *index_name = NULL;
  DBIndex *dbindex    = 0;
  kcb     *kcbptr;
  ILock(YES);
  GoTop();
  while (indx0 >= 0)
  {
    if ( !(dbindex = GetNext()) )
      break;
    indx0--;
  }
  if ( dbindex )
  {
    if ( kcbptr = dbindex->get_key_def() )
      index_name = kcbptr->scbsmcb->smcbname;
  }
  IUnlock();
  return (index_name);
}

/******************************************************************************/
/**
\brief  ~DBIndexList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBIndexList"

     DBIndexList :: ~DBIndexList ( )
{
  DBIndex  *indexptr;
  if ( this && IsOwner() )
    while ( indexptr = RemoveTail() )
      delete indexptr;

}


