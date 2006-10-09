/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ReferenceObject



\date     $Date: 2006/05/31 19:15:24,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ReferenceObject"

#include  <pdefault.h>
#include  <sReferenceObject.hpp>


/******************************************************************************/
/**
\brief  Exist

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical ReferenceObject :: Exist ( )
{

  return( use_count > 0 ? YES : NO);

}

/******************************************************************************/
/**
\brief  ILock

\return term - Success

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical ReferenceObject :: ILock (logical wait )
{

  return(  this ? res_lock.ILock(wait) : YES );

}

/******************************************************************************/
/**
\brief  IUnlock

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical ReferenceObject :: IUnlock ( )
{

  return(  this ? res_lock.IUnlock() : YES );

}

/******************************************************************************/
/**
\brief  IsLocked

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocked"

logical ReferenceObject :: IsLocked ( )
{

  return(  res_lock.IsLocked() );

}

/******************************************************************************/
/**
\brief  ReferenceObject


\param  activate_llist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReferenceObject"

     ReferenceObject :: ReferenceObject (logical activate_llist )
                     : use_count(1),
  res_lock(activate_llist)
{
}

/******************************************************************************/
/**
\brief  Release

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

logical ReferenceObject :: Release ( )
{
  logical                 del_inst = UNDEF;
  logical                 cond = NO;
BEGINSEQ
  if ( !this || use_count <= 0 )                    LEAVESEQ

  ILock(YES);
    
  if ( use_count == 1 )
  {
    use_count = 0;
    cond = YES;
    IUnlock();
    delete this;
  }
  else  
  {
    --use_count;
    IUnlock();
  }


ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Reserve


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

void ReferenceObject :: Reserve ( )
{

  if ( this && use_count > 0 )
  {
    ILock(YES);
    use_count++;
    IUnlock();
  }

}

/******************************************************************************/
/**
\brief  ResetUseCount


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetUseCount"

void ReferenceObject :: ResetUseCount ( )
{

  use_count = 0;

}

/******************************************************************************/
/**
\brief  ~ReferenceObject


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ReferenceObject"

     ReferenceObject :: ~ReferenceObject ( )
{
}


