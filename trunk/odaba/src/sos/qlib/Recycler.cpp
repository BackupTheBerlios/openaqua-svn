/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    Recycler

\brief    


\date     $Date: 2006/03/12 19:21:56,32 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Recycler"

#include  <pdefault.h>
#include  <sHashEntry.hpp>
#include  <sRessourceLock.hpp>
#include  <sRecycler.hpp>


/******************************************************************************/
/**
\brief  Add - 



\param  hash_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void Recycler :: Add (HashEntry *hash_entry )
{

  lock.ILock();
    
  if ( count < 100000 )
  {
    count++;
    hash_entry->next = head;
    head             = hash_entry;
  } 
  else 
    delete hash_entry;
    
  lock.IUnlock();


}

/******************************************************************************/
/**
\brief  Recycler


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Recycler"

                        Recycler :: Recycler ( )
                     :   lock(YES),
  head(NULL),
  count(0)
{



}

/******************************************************************************/
/**
\brief  Take - 


\return hash_entry -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Take"

HashEntry *Recycler :: Take ( )
{
  HashEntry              *hash_entry;
  lock.ILock();
    
  if ( hash_entry = head )
  {
    head = hash_entry->next;
    count--;
  }

  lock.IUnlock();
  return hash_entry;
}

/******************************************************************************/
/**
\brief  ~Recycler


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Recycler"

                        Recycler :: ~Recycler ( )
{



}


