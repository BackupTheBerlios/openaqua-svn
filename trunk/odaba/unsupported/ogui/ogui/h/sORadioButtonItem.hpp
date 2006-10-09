/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORadioButtonItem

\brief    


\date     $Date: 2006/03/13 21:34:30,79 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ORadioButtonItem_HPP
#define   ORadioButtonItem_HPP

class     ORadioButtonItem;

class     ODSList;
class     ORadioButtonGroup;
#include  <sItemData.hpp>
class  ORadioButtonItem :public QRadioButton,
public ItemData
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         ORadioButtonGroup                           *buttonGroup;                                               //

public     :
                     ORadioButtonGroup                           *get_buttonGroup() { return(buttonGroup); }
public     : virtual                             logical GetChecked ( );
public     : virtual                             QRadioButton *GetQRadioButton ( );
public     : virtual                             QString GetText (int column );
public     : virtual                             int Index ( );
public     :                                                             ORadioButtonItem (ORadioButtonGroup *pORadioButtonGroup );
public     :                                     ItemData *ProvideNew (logical is_first_item=NO );
public     : virtual                             void SetPixmap (int column, QPixmap *pQPixmap );
public     : virtual                             void SetText (int column, ODSList *pODSList );
public     : virtual                             void SetText (ODSList *pODSList );
public     : virtual                             void SetText (int column, QString qsText );
public     :                                     public slots: void doClicked ( );
public     : virtual                                                     ~ORadioButtonItem ( );
};

#endif
