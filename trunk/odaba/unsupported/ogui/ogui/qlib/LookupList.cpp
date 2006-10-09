/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    LookupList

\brief    


\date     $Date: 2006/03/13 21:35:09,46 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LookupList"

#include  <pogui7.h>
#include  <clookupl.h>
#include  <sLookupList.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term -

\param  pkey -
\param  pobj -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical LookupList :: Add (void *pkey, void *pobj )
{

  posCacheValid = NO;

  ITEM   it;
  it.key = pkey;
  it.obj = pobj;

  return BinaryList::Add(&it);

}

/******************************************************************************/
/**
\brief  GetByIndex - 


\return res -

\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetByIndex"

void *LookupList :: GetByIndex (int index )
{

  pITEM   p = (pITEM) _GetByIndex(index);

  return p ? p->obj : NULL;

}

/******************************************************************************/
/**
\brief  GetByKey - 


\return res -

\param  pkey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetByKey"

void *LookupList :: GetByKey (void *pkey )
{

  pITEM p = (pITEM) BinaryList::GetByKey(pkey);

  return p ? p->obj : NULL;


}

/******************************************************************************/
/**
\brief  GetKeyByIndex - 


\return res -

\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyByIndex"

void *LookupList :: GetKeyByIndex (int index )
{

  pITEM p  = (pITEM) _GetByIndex(index);

  return p ? p->key : NULL;

}

/******************************************************************************/
/**
\brief  LookupList - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LookupList"

                        LookupList :: LookupList ( )
                     : BinaryList (sizeof(ITEM),TRUE),
  posCache(),
  posCacheValid(NO)
{



}

/******************************************************************************/
/**
\brief  OnAddItem - 



\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnAddItem"

void LookupList :: OnAddItem (void *pitem )
{



}

/******************************************************************************/
/**
\brief  OnCopyKey - 



\param  pkey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnCopyKey"

void LookupList :: OnCopyKey (void *pkey )
{



}

/******************************************************************************/
/**
\brief  OnDeleteItem - 



\param  pitem - Pointer to the item
\param  fFree -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnDeleteItem"

void LookupList :: OnDeleteItem (void *pitem, logical fFree )
{

  pITEM pi  = (pITEM)pitem;

  if ( fFree) 
    OnFree(pi->key,pi->obj);

}

/******************************************************************************/
/**
\brief  OnFree - 



\param  pkey -
\param  pobj -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnFree"

void LookupList :: OnFree (void *pkey, void *pobj )
{



}

/******************************************************************************/
/**
\brief  OnGetKey - 


\return pitem - Pointer to the item

\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnGetKey"

void *LookupList :: OnGetKey (void *pitem )
{

  return ((pITEM)pitem)->key;

}

/******************************************************************************/
/**
\brief  OnInsert - 



\param  ppitem -
\param  ppkey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnInsert"

void LookupList :: OnInsert (void **ppitem, void **ppkey )
{



}

/******************************************************************************/
/**
\brief  OnInsertItem - 



\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnInsertItem"

void LookupList :: OnInsertItem (void *pitem )
{

  pITEM   pi = (pITEM)pitem;

  OnInsert(&pi->key,&pi->obj);

}

/******************************************************************************/
/**
\brief  _GetByIndex - 


\return res -

\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "_GetByIndex"

void *LookupList :: _GetByIndex (int index )
{
  void     *res = NULL;
BEGINSEQ
  if ( posCacheValid )
  {
    if ( posCacheIndex + 1 == index )
    {
      if ( BinaryList::GetNextPosition(posCache) )      ERROR
      posCacheIndex++;
      res = BinaryList::GetAt(posCache);
      LEAVESEQ
    }
    else if ( posCacheIndex == index )
    {
      res = BinaryList::GetAt(posCache);
      LEAVESEQ
    }
  }
  
  if ( BinaryList::GetPositionByIndex(posCache,index) ) ERROR
  posCacheIndex = index;
  posCacheValid = YES;
  res = BinaryList::GetAt(posCache);

RECOVER
  res = NULL;
ENDSEQ
  return(res);
}


