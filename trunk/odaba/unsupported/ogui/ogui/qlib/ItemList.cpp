/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ItemList

\brief    Item list
          An  item list is a list of  ItemData objects, which is usually part of
          a ItemTreeModel.

\date     $Date: 2006/08/24 16:53:10,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ItemList"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sItemRegion.hpp>
#include  <sItemRegionList.hpp>
#include  <sItemList.hpp>


/******************************************************************************/
/**
\brief  Clear - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ItemList :: Clear ( )
{
  int          count     = GetSize();
  ItemData    *pItemData = NULL;
  while ( count-- )
  {
    if ( pItemData = GetAt(count) )
      if ( !pItemData->get_heading() )
        delete pItemData;
    RemoveLast(1);
  }


}

/******************************************************************************/
/**
\brief  CreateItem - 



\return pItemData - ItemData

\param  pItemRegion - 
\param  index0 - 
\param  start_row - 
\param  insert_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateItem"

ItemData *ItemList :: CreateItem (ItemRegion *pItemRegion, int index0, int start_row, logical insert_opt )
{
  ItemData      *pItemData = NULL;
  pItemData = new ItemData(pItemRegion,index0+start_row);
  
  SetItem(pItemData,index0,insert_opt);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  GetIndexForDBIndex - 



\return index0 - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexForDBIndex"

int ItemList :: GetIndexForDBIndex (int32 indx0 )
{
  int        count     = 0;
  int        index0    = 0;
  ItemData  *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);
    if ( pItemData->get_lastIndex() >= indx0 )       LEAVESEQ
  }

  index0 = GetSize();
RECOVER

ENDSEQ
  return(index0);
}

/******************************************************************************/
/**
\brief  ItemByDBIndex - 



\return pItemData - ItemData

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByDBIndex"

ItemData *ItemList :: ItemByDBIndex (int32 indx0 )
{
  int        count     = 0;
  int        index0    = 0;
  ItemData  *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);
    if ( pItemData->IsItemDBIndex(indx0) )           LEAVESEQ
  }

  ERROR
RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByKey - 



\return pItemData - ItemData

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByKey"

ItemData *ItemList :: ItemByKey (char *skey )
{
  int           count     = 0;
  int           index0    = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);       
    if ( pItemData->IsItemKey(skey) )                LEAVESEQ
  }

  ERROR
RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByLOID - 



\return pItemData - ItemData

\param  objid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByLOID"

ItemData *ItemList :: ItemByLOID (int32 objid )
{
  int           count     = 0;
  int           index0    = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);       
    if ( pItemData->IsItemLOID(objid) )              LEAVESEQ
  }

  ERROR
RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemByValue - 



\return pItemData - ItemData

\param  pQString - 
\param  col - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemByValue"

ItemData *ItemList :: ItemByValue (QString &pQString, int col )
{
  int           count     = 0;
  int           index0    = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);       
    if ( pItemData->IsItemValue(pQString,col) )      LEAVESEQ
  }

  ERROR
RECOVER
  pItemData = NULL;
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ItemList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ItemList"

     ItemList :: ItemList ( )
                     : DPA(ItemData) (0)
{



}

/******************************************************************************/
/**
\brief  RemoveItem - 



\return pItemData - ItemData

\param  index0 - 
\param  remove_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItem"

ItemData *ItemList :: RemoveItem (int index0, logical remove_opt )
{
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( index0 >= GetSize() )                         ERROR
    
  pItemData = GetAt(index0);
  
  if ( remove_opt || index0 == GetSize()-1 )
    RemoveAt(index0,1);
  else
    SetAt(index0,NULL);

  delete pItemData;
RECOVER

ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  RemoveRegion - 




\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveRegion"

void ItemList :: RemoveRegion (int32 region_id )
{
  int           count     = 0;
  int           index0    = 0;
  ItemData     *pItemData = NULL;
  for ( count = GetSize(); index0 < count; index0++ )
    if ( pItemData = GetAt(index0) )
      if ( pItemData->get_children() )
        pItemData->get_children()->RemoveRegion(region_id);


}

/******************************************************************************/
/**
\brief  SetItem - 



\return term - 

\param  pItemData - ItemData
\param  index0 - 
\param  insert_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetItem"

logical ItemList :: SetItem (ItemData *pItemData, int index0, logical insert_opt )
{

BEGINSEQ
  if ( index0 == AUTO )
    index0 = GetSize();
    
  if ( index0 >= GetSize() )
    SetAtGrow(index0,pItemData);
  else if ( insert_opt )
    InsertAt(index0,pItemData);
  else if ( GetAt(index0) )                          OGUIERR(99)
  else
    SetAt(index0,pItemData);
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetupDBIndex - 




\param  index0 - 
\param  diff - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDBIndex"

void ItemList :: SetupDBIndex (int index0, int32 diff )
{
  int           count     = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);       
    pItemData->setup_lastIndex(diff);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetupItemRows - 




\param  index0 - 
\param  start_row - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupItemRows"

void ItemList :: SetupItemRows (int index0, int start_row )
{
  int           count     = 0;
  ItemData     *pItemData = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  for ( count = GetSize(); index0 < count; index0++ )
  {
    pItemData = GetAt(index0);       
    pItemData->set_row(index0 + start_row);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ItemList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ItemList"

     ItemList :: ~ItemList ( )
{



}


