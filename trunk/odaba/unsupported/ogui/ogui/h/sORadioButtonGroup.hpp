/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORadioButtonGroup

\brief    Radio Button Group


\date     $Date: 2006/03/13 21:34:30,29 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ORadioButtonGroup_HPP
#define   ORadioButtonGroup_HPP

class     ORadioButtonGroup;

class     DBorder;
class     ItemData;
class     ODS;
class     ODataWidget;
class     ORadioButton;
class     ORadioButtonItem;
#include  <sOListCtl.hpp>
#include  <sOListCtrl.hpp>
class  ORadioButtonGroup :public OListCtrl,
public QWidget
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         logical                                      auto_resize;                                               //
protected  :         QSize                                        minimum_size;                                              //
protected  :         ORadioButton                                *radiobutton;                                               //
protected  :         logical                                      hori_strip;                                                //
protected  :         int32                                        strips;                                                    //

public     :
                     logical                                      get_auto_resize() { return(auto_resize); }
                     ORadioButton                                *get_radiobutton() { return(radiobutton); }
public     :                                     QList<QRadioButton*> &Buttons ( );
public     : virtual                             void ClearData ( );
public     :                                     ItemData *CreateItem (ItemData *pItemDataParent, ItemData *pItemDataAfter );
public     :                                     ItemData *FirstChild ( );
public     :                                     ItemData *GetCheckedButton ( );
public     :                                                             ORadioButtonGroup (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical auto_size=NO, int32 no_strips=1, logical hori_strip=NO );
public     :                                     logical RemoveItems ( );
public     :                                     logical SetActive (int32 indx0 );
public     : virtual                             void SetFrameStyle (DBorder *pDBorder );
public     :                                     QWidget *WidgetQ ( );
public     :                                     int32 childCount ( );
public     :                                     void storeToValue ( );
public     :                                     logical updateLayout ( );
public     :                                     void xxBlockSignals (logical block_opt );
public     : virtual                             void xxFillList ( );
public     : virtual                             QFrame *xxFrameQ ( );
public     : virtual                             int32 xxGetListPosition (int32 indx0 );
public     : virtual                             void xxHandleOpened (logical chk_visible );
public     :                                     void xxResize ( );
public     : virtual                             ItemData *xxcreateItem ( );
public     : virtual                             ItemData *xxremoveItems (ItemData *pItemData );
public     :                                                             ~ORadioButtonGroup ( );
};

#endif
