/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ItemList

\brief    Item list
          An  item list is a list of  ItemData objects, which is usually part of
          a ItemTreeModel.

\date     $Date: 2006/08/24 16:51:23,10 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ItemList_HPP
#define   ItemList_HPP

class     ItemList;

#ifndef   DPA_ItemData_HPP
#define   DPA_ItemData_HPP
#include  <sItemData.hpp>
#include  <sDPA.h>
#endif
class     ItemData;
class     ItemRegion;
class  ItemList :public DPA(ItemData)
{

public     :
public     :                                        void Clear ( );
public     :                                        ItemData *CreateItem (ItemRegion *pItemRegion, int index0, int start_row, logical insert_opt );
public     :                                        int GetIndexForDBIndex (int32 indx0 );
public     :                                        ItemData *ItemByDBIndex (int32 indx0 );
public     :                                        ItemData *ItemByKey (char *skey );
public     :                                        ItemData *ItemByLOID (int32 objid );
public     :                                        ItemData *ItemByValue (QString &pQString, int col );
public     :                                             ItemList ( );
public     :                                        ItemData *RemoveItem (int index0, logical remove_opt );
public     :                                        void RemoveRegion (int32 region_id );
public     :                                        logical SetItem (ItemData *pItemData, int index0, logical insert_opt );
public     :                                        void SetupDBIndex (int index0, int32 diff );
public     :                                        void SetupItemRows (int index0, int start_row );
public     :                                             ~ItemList ( );
};

#endif
