/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OEHControlList

\brief    Base class for all list data widgets


\date     $Date: 2006/03/29 13:33:52,62 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHControlList_HPP
#define   OEHControlList_HPP

class     OEHControlList;

class     ItemData;
class     ODS;
class     ODSRegion;
class     ODataWidget;
#include  <sOEHControlData.hpp>
#include  <sOEHDataWidget.hpp>
class  OEHControlList :public OEHControlData
{
protected  :         ItemData                                    *cur_item ATTR_ALIGN(4);                                    // 
protected  :         std_string                                   lastKey;                                                   // Last key value
protected  :         int                                          lastIndex;                                                 // Last item index
protected  :         int32                                        lastInstID;                                                // 
protected  :         ODS                                         *lastODS;                                                   // 

public     :
                     ItemData                                    *get_cur_item() { return(cur_item); }
                     std_string                                  &get_lastKey() { return(lastKey); }
                     int                                         &get_lastIndex() { return(lastIndex); }
                     ODS                                         *get_lastODS() { return(lastODS); }
public     : virtual                             logical Activate ( );
public     :                                     logical ActivateList (logical ignore_evthandling=NO );
public     : virtual                             logical DA_FindEntry ( );
public     : virtual                             logical DA_FindEntry (char *skey, logical cur_opt=YES );
public     : virtual                             logical DA_Refresh ( );
public     : virtual                             logical Deactivate (logical data_only=NO );
public     :                                     logical DeactivateList (logical ignore_evthandling=NO, logical data_only=NO );
public     : virtual                             char *GetKey ( );
public     : virtual                             ItemData *GetNextListItem (ItemData *pItemData );
public     : virtual                             void HandleActivated ( );
public     :                                     logical IsCurItem (ItemData *pItemData, logical recursive );
public     :                                     logical IsCurItem (ItemData *pItemData, ItemData *cur_item_parent );
public     : virtual                             void ListChanged (logical chk_visible );
public     :                                                             OEHControlList (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                                             OEHControlList (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     logical ProvideContextMenu (QObject *watched );
public     : virtual                             void RemoveItem (ItemData *pItemData );
public     : virtual                             void ResetCurrentItem (ItemData *pItemData );
public     : virtual                             logical SetDefaultReactions ( );
public     :                                     void SetLastID (int32 inst_id );
public     :                                     logical SetLastKey (ODS *pODS );
public     : virtual                             void UpdateControl ( );
public     :                                     void doInstanceInserted ( );
public     :                                     void doInstanceRemoved ( );
public     :                                     void doInstanceUpdated ( );
public     :                                     void set_cur_item (ItemData *pItemData );
public     :                                                             ~OEHControlList ( );
};

#endif
