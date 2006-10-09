/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORadioButtonItem

\brief    


\date     $Date: 2006/03/13 21:36:11,39 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ORadioButtonItem"

#include  <pogui7.h>
#include  <mORadioButtonItem.h>
#include  <sItemData.hpp>
#include  <sODSList.hpp>
#include  <sORadioButton.hpp>
#include  <sORadioButtonGroup.hpp>
#include  <sORadioButtonItem.hpp>


/******************************************************************************/
/**
\brief  GetChecked - 


\return checked -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChecked"

logical ORadioButtonItem :: GetChecked ( )
{
  logical            checked = false;
  checked = isChecked();
  return(checked);
}

/******************************************************************************/
/**
\brief  GetQRadioButton - 


\return pQRadioButton -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetQRadioButton"

QRadioButton *ORadioButtonItem :: GetQRadioButton ( )
{

  return this;

}

/******************************************************************************/
/**
\brief  GetText - 


\return qsText -

\param  column -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

QString ORadioButtonItem :: GetText (int column )
{
  QString                 qsText;
  qsText = text();
  return(qsText);
}

/******************************************************************************/
/**
\brief  Index - 


\return index -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Index"

int ORadioButtonItem :: Index ( )
{
  int                     index;

  return(index);
}

/******************************************************************************/
/**
\brief  ORadioButtonItem - Konstruktor



\param  pORadioButtonGroup -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ORadioButtonItem"

                        ORadioButtonItem :: ORadioButtonItem (ORadioButtonGroup *pORadioButtonGroup )
                     : ItemData (pORadioButtonGroup->childCount())
,QRadioButton(
pORadioButtonGroup->WidgetQ()
)
,buttonGroup(pORadioButtonGroup)
{

  connect(this ,SIGNAL(clicked()),
          this ,SLOT(doClicked()));


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

ItemData *ORadioButtonItem :: ProvideNew (logical is_first_item )
{
  ItemData               *pItemData = NULL;
  pItemData = new ORadioButtonItem(buttonGroup);
  return(pItemData);
}

/******************************************************************************/
/**
\brief  SetPixmap - 



\param  column -
\param  pQPixmap -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPixmap"

void ORadioButtonItem :: SetPixmap (int column, QPixmap *pQPixmap )
{

  setIcon(pQPixmap ? *pQPixmap : QPixmap());

}

/******************************************************************************/
/**
\brief  SetText - 


-------------------------------------------------------------------------------
\brief  i00


\param  column -
\param  pODSList -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void ORadioButtonItem :: SetText (int column, ODSList *pODSList )
{

  pODSList->ValueInit();
  setText(pODSList->Value());

}

/******************************************************************************/
/**
\brief  i01


\param  pODSList -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void ORadioButtonItem :: SetText (ODSList *pODSList )
{

  pODSList->ValueInit();
  setText(pODSList->Value());

}

/******************************************************************************/
/**
\brief  i02


\param  column -
\param  qsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void ORadioButtonItem :: SetText (int column, QString qsText )
{

BEGINSEQ
  if(column != 0 )                                   ERROR
  setText(qsText);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  doClicked - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doClicked"

void ORadioButtonItem :: doClicked ( )
{

  buttonGroup->storeToValue();

}

/******************************************************************************/
/**
\brief  ~ORadioButtonItem - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ORadioButtonItem"

                        ORadioButtonItem :: ~ORadioButtonItem ( )
{




}


