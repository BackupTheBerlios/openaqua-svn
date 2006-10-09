/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OCheckListItem

\brief    


\date     $Date: 2006/03/13 21:33:45,34 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OCheckListItem_HPP
#define   OCheckListItem_HPP

class     OCheckListItem;

class     ItemData;
class     OCheckListItem;
class     ODSList;
class     OListView;
#include  <sOListWidgetItem.hpp>
class  OCheckListItem :public OListWidgetItem
{

public     :
public     : virtual                             logical GetChecked ( );
public     : virtual                             QListWidgetItem *GetQListWidgetItem ( );
public     : virtual                             void Initialize ( );
public     :         OGUI7ImpExp                                         OCheckListItem (OListView *pOListView );
public     :         OGUI7ImpExp                                         OCheckListItem (OListView *pOListView, OCheckListItem *pOCheckListItem );
public     :         OGUI7ImpExp                                         OCheckListItem (OListView *pOListView, int pos );
public     : virtual                             ItemData *ProvideNew (logical is_first_item=NO );
public     :                                     logical SetChecked (bool toggle=FALSE );
public     :                                     void SetText (int column, ODSList *pODSList );
public     : virtual                             void stateChange (bool state );
public     : virtual                                                     ~OCheckListItem ( );
};

#endif
