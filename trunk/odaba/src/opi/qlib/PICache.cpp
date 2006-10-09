/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    PICache

\brief    


\date     $Date: 2006/03/12 19:10:32,98 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PICache"

#include  <pdefault.h>
#include  <sPropertyHandle.hpp>
#include  <sRessourceLock.hpp>
#include  <sPICache.hpp>


/******************************************************************************/
/**
\brief  PICache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PICache"

                        PICache :: PICache ( )
                     : DLL(PropertyHandle) (),
  res_lock(NO)
{



}

/******************************************************************************/
/**
\brief  Release - 



\param  ph_ptr - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void PICache :: Release (PropertyHandle *ph_ptr )
{

  res_lock.ILock();

  AddTail(ph_ptr);

  res_lock.IUnlock();

}

/******************************************************************************/
/**
\brief  Reserve - 


\return ph_ptr - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

PropertyHandle PICache :: Reserve ( )
{
  PropertyHandle    *ph = NULL;
  res_lock.ILock();

  if ( !(ph = RemoveTail()) )
    ph = new PropertyHandle();

  res_lock.IUnlock();
  return(ph);
}

/******************************************************************************/
/**
\brief  ~PICache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PICache"

                        PICache :: ~PICache ( )
{
  PropertyHandle       *ph;
  while ( ph = RemoveTail() )
    delete ph;

}


