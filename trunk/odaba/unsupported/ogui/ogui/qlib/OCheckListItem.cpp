/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OCheckListItem

\brief    


\date     $Date: 2006/03/13 21:35:11,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OCheckListItem"

#include  <pogui7.h>
#include  <sItemData.hpp>
#include  <sOCheckListItem.hpp>
#include  <sODSList.hpp>
#include  <sOIconSet.hpp>
#include  <sOListView.hpp>
#include  <sOCheckListItem.hpp>


/******************************************************************************/
/**
\brief  GetChecked - 


\return checked -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChecked"

logical OCheckListItem :: GetChecked ( )
{
  logical checked;
  checked = checkState() == Qt::Checked;
  return(checked);
}

/******************************************************************************/
/**
\brief  GetQListWidgetItem - 


\return pQListWidgetItem -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetQListWidgetItem"

QListWidgetItem *OCheckListItem :: GetQListWidgetItem ( )
{

  return this;

}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OCheckListItem :: Initialize ( )
{

  ItemData::Initialize();
  setFlags( flags() | Qt::ItemIsUserCheckable );


}

/******************************************************************************/
/**
\brief  OCheckListItem - 


-------------------------------------------------------------------------------
\brief  i0


\param  pOListView -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckListItem"

                        OCheckListItem :: OCheckListItem (OListView *pOListView )
                     : OListWidgetItem (pOListView)
{

Initialize();

}

/******************************************************************************/
/**
\brief  i02


\param  pOListView -
\param  pOCheckListItem -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckListItem"

                        OCheckListItem :: OCheckListItem (OListView *pOListView, OCheckListItem *pOCheckListItem )
                     : OListWidgetItem(
  pOListView,
  (OListWidgetItem*)pOCheckListItem
)
{

Initialize();

}

/******************************************************************************/
/**
\brief  i03


\param  pOListView -
\param  pos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCheckListItem"

                        OCheckListItem :: OCheckListItem (OListView *pOListView, int pos )
                     : OListWidgetItem(
  pOListView
)
{



}

/******************************************************************************/
/**
\brief  ProvideNew - 


\return pItemData - ItemData

\param  is_first_item -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideNew"

ItemData *OCheckListItem :: ProvideNew (logical is_first_item )
{
  ItemData   *pItemData = NULL;
  int         iRow      = 0;
  int         nRow      = 0;
BEGINSEQ
  pItemData = new OCheckListItem((OListView *)listView(),this);
  if(!pItemData)                                     ERROR
  
  if ( !is_first_item ) {
    iRow = Index();
    nRow = pItemData->Index();
    listView()->InsertItem(iRow+1,listView()->TakeItem(nRow));
  }
RECOVER
  pItemData = NULL;
ENDSEQ
  return( pItemData );
}

/******************************************************************************/
/**
\brief  SetChecked - 


\return term -

\param  toggle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetChecked"

logical OCheckListItem :: SetChecked (bool toggle )
{
  logical                 term = NO;
  setCheckState(toggle?Qt::Checked:Qt::Unchecked);
  return(term);
}

/******************************************************************************/
/**
\brief  SetText - 



\param  column -
\param  pODSList -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void OCheckListItem :: SetText (int column, ODSList *pODSList )
{

  pODSList->ValueInit();
  OListWidgetItem::SetText(column,pODSList->Value());

  if ( pODSList->get_layout()->get_normal_pixmap() )
    SetPixmap(0,pODSList->get_layout()->get_normal_pixmap());


}

/******************************************************************************/
/**
\brief  stateChange - 



\param  state -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stateChange"

void OCheckListItem :: stateChange (bool state )
{

  //QCheckListItem::stateChange(state);

/* emit ((OListView*) listView())->OnItemChecked( this, s );
*/


}

/******************************************************************************/
/**
\brief  ~OCheckListItem - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OCheckListItem"

                        OCheckListItem :: ~OCheckListItem ( )
{

  ResetCurrent();


}


