/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORadioButtonGroup

\brief    Radio Button Group


\date     $Date: 2006/03/13 21:36:10,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ORadioButtonGroup"

#include  <pogui7.h>
#include  <mORadioButtonGroup.h>
#include  <sDBorder.hpp>
#include  <sItemData.hpp>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sORadioButton.hpp>
#include  <sORadioButtonItem.hpp>
#include  <sORadioButtonGroup.hpp>


/******************************************************************************/
/**
\brief  Buttons - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Buttons"

QList<QRadioButton*> &ORadioButtonGroup :: Buttons ( )
{

return findChildren<QRadioButton *>();

}

/******************************************************************************/
/**
\brief  ClearData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void ORadioButtonGroup :: ClearData ( )
{

  QList<QRadioButton *> members;
  QList<QRadioButton *>::Iterator it;
members = Buttons();
for(it = members.begin();it!=members.end();it++)
  (*it)->setChecked(false);


}

/******************************************************************************/
/**
\brief  CreateItem - 


\return pItemData - ItemData

\param  pItemDataParent -
\param  pItemDataAfter -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateItem"

ItemData *ORadioButtonGroup :: CreateItem (ItemData *pItemDataParent, ItemData *pItemDataAfter )
{
  ItemData               *pItemData;
  pItemData = new ORadioButtonItem(this);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  FirstChild - 


\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstChild"

ItemData *ORadioButtonGroup :: FirstChild ( )
{
  ItemData               *pItemData;
  QList<QRadioButton *> members;
  
  members = Buttons();
  pItemData = ItemData::GetItemData((*members.begin()));
  return(pItemData);
}

/******************************************************************************/
/**
\brief  GetCheckedButton - 


\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCheckedButton"

ItemData *ORadioButtonGroup :: GetCheckedButton ( )
{
  ItemData             *pItemData = NULL;
  QList<QRadioButton *> members;
  QList<QRadioButton *>::Iterator it;
BEGINSEQ
members = Buttons();

for(it = members.begin();it!=members.end();it++)
  if(ItemData::GetItemData((*it))->GetChecked()){
    pItemData = ItemData::GetItemData(*it);
    LEAVESEQ
  }
ENDSEQ
  return(pItemData);
}

/******************************************************************************/
/**
\brief  ORadioButtonGroup - 


\return term -

\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
\param  auto_size - Determin size dynamically
\param  no_strips - Number of strips
\param  hori_strip - Horizontal orientation
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ORadioButtonGroup"

                        ORadioButtonGroup :: ORadioButtonGroup (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical auto_size, int32 no_strips, logical hori_strip )
                     : OListCtrl(pODataWidget,oODataWidget,NULL)
,QWidget(pODataWidget->WidgetQ())
,radiobutton((ORadioButton*)pODataWidget)
,auto_resize(auto_size)
,strips(no_strips)
,hori_strip(hori_strip)
{



}

/******************************************************************************/
/**
\brief  RemoveItems - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveItems"

logical ORadioButtonGroup :: RemoveItems ( )
{
  logical                  term = NO;
  QList<QRadioButton *> members;
  QList<QRadioButton *>::Iterator it;
members = Buttons();

for(it = members.begin();it!=members.end();it++)
  delete *it;
  return(term);
}

/******************************************************************************/
/**
\brief  SetActive - 


\return term -

\param  indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActive"

logical ORadioButtonGroup :: SetActive (int32 indx0 )
{
  logical                  term = NO;
  QList<QRadioButton *> members;
  QList<QRadioButton *>::Iterator it;
members = Buttons();
for(it = members.begin();it!=members.end();it++, indx0--)
  if(indx0==0)
    (*it)->setChecked(true);

  return(term);
}

/******************************************************************************/
/**
\brief  SetFrameStyle - 



\param  pDBorder -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFrameStyle"

void ORadioButtonGroup :: SetFrameStyle (DBorder *pDBorder )
{



}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ORadioButtonGroup :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  childCount - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "childCount"

int32 ORadioButtonGroup :: childCount ( )
{
  int                      count = 0;
  QList<QRadioButton *> members;
  QList<QRadioButton *>::Iterator it;
members = Buttons();

for(it = members.begin();it!=members.end();it++)
  count++;
  return count;
}

/******************************************************************************/
/**
\brief  storeToValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void ORadioButtonGroup :: storeToValue ( )
{

  radiobutton->storeToValue();


}

/******************************************************************************/
/**
\brief  updateLayout - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateLayout"

logical ORadioButtonGroup :: updateLayout ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !GetLayout() )                                OGUIERR(99)
  if ( !olayout )                                    ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  xxBlockSignals - 



\param  block_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxBlockSignals"

void ORadioButtonGroup :: xxBlockSignals (logical block_opt )
{

BEGINSEQ
/*
  if ( signalsBlocked() == block_opt )               LEAVESEQ
  
  listCache.BlockSignals(block_opt);
  
  blockSignals(block_opt);
  
  if ( !event_handling )
    ((ORadioButton *)parent())->BlockSignals(block_opt);   // OComboBox
*/
ENDSEQ

}

/******************************************************************************/
/**
\brief  xxFillList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxFillList"

void ORadioButtonGroup :: xxFillList ( )
{
 /* 
  QButton           *rbi;
  ItemData          *last_lvi;
  logical            term = NO;
BEGINSEQ
  if ( !count() )
    createItem();
  if ( !(rbi = find(0)) )                        OGUIERR(99)
  
  last_lvi = listCache.SetRegionItemData((GetItemDataPtr(rbi)),NULL,NO);
    
  removeItems(last_lvi);
  
  if ( !auto_resize )
  {
    setInsideSpacing(0);
    setInsideMargin(0);
    adjustSize();
    minimum_size = size();
  }
  Resize();
RECOVER

ENDSEQ
*/
}

/******************************************************************************/
/**
\brief  xxFrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxFrameQ"

QFrame *ORadioButtonGroup :: xxFrameQ ( )
{

  return NULL;//return(this);

}

/******************************************************************************/
/**
\brief  xxGetListPosition - 


\return pos -

\param  indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxGetListPosition"

int32 ORadioButtonGroup :: xxGetListPosition (int32 indx0 )
{


 return(indx0);

// das sollte Aufgabe der Basisklasse sein, dann kann die Funktion weg!

}

/******************************************************************************/
/**
\brief  xxHandleOpened - 



\param  chk_visible -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxHandleOpened"

void ORadioButtonGroup :: xxHandleOpened (logical chk_visible )
{

//  OListCtl::HandleOpened(NO);

}

/******************************************************************************/
/**
\brief  xxResize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxResize"

void ORadioButtonGroup :: xxResize ( )
{
/*  int          col_no  = columns();
  int          item_no = count();
  int          cols    = col_no;
  int          rows    = col_no;
  QSize        s       = size();
  QSize        new_s   = parentWidget()->size();
  Orientation  o       = orientation();
  int          nm;
  int          nh;
  int          nhr;
  int          nhc;
  int          elements;

  if ( !auto_resize )
  {
    // hier berechnen wir die optimalen Abstände zwischen den Zeilen und Spalten (nh) 
    // und am Rand (nm) in Pixel.
  
    if ( o == Horizontal )
      rows = (item_no + col_no - 1)/col_no;
    else
      cols = (item_no + col_no - 1)/col_no;
      
    if ( rows > 0 && (nhr = new_s.height() - minimum_size.height() ) > 0 )
      nhr = nhr/(rows+1);
    if ( cols > 0 && (nhc = new_s.width() - minimum_size.width() ) > 0 )
      nhc = nhc/(cols+1);
    
    nm = nh = nhr<nhc?nhr:nhc;
    elements = nh == nhr ? rows : cols;
    
    while ( elements > 1 && nm  < 7 && nh > 0 )
    {
      nm += (elements-1)/2;
      nh--;
    }
     
    setInsideSpacing(nh);
    setInsideMargin(nm);
    setFixedSize(new_s);
    adjustSize();
updateGeometry();    
  }
  else
  {  
    // das ganze theater muss zur groessenregulierung sein - sonst macht adjustSize nix  
    clearWState(WState_Resized);
    clearWState(WState_Polished);
    QString t = title();  
    setTitle(QString());  
    setTitle(t);  
  
    adjustSize();
  }
*/
}

/******************************************************************************/
/**
\brief  xxcreateItem - 


\return pItemData - ItemData

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxcreateItem"

ItemData *ORadioButtonGroup :: xxcreateItem ( )
{

 return NULL;
 // return ( new ORadioButtonItem(this) );

}

/******************************************************************************/
/**
\brief  xxremoveItems - 


\return term -

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxremoveItems"

ItemData *ORadioButtonGroup :: xxremoveItems (ItemData *pItemData )
{
/*  QButton    *pQButton;
  int              bid;
BEGINSEQ
  if ( !pItemData  )  
    if ( pQButton = find(0) )  
      pItemData = GetItemDataPtr(pQButton);
  if ( !pItemData )                                 LEAVESEQ
  
  pQButton = (ORadioButtonItem *)pItemData;
  
  bid = id(pQButton);
  while ( pQButton = find(bid++) )
  {
    delete pQButton;
  }
ENDSEQ
*/  return NULL;
}

/******************************************************************************/
/**
\brief  ~ORadioButtonGroup - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ORadioButtonGroup"

                        ORadioButtonGroup :: ~ORadioButtonGroup ( )
{



}


