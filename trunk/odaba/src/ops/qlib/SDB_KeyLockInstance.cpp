/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_KeyLockInstance

\brief    Key lock instance
          A  key  lock  instance  defines  the key, that is locked in the index.
          Keys  might be locked  by different users,  which are identified by an
          owner  identifier. Keys  can be  locked multiple,  but each key can be
          locked, however, only by one owner (workspace or database session).

\date     $Date: 2006/03/13 21:30:19,65 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_KeyLockInstance"

#include  <pops7.h>
#include  <sSDB_KeyLockInstance.hpp>



