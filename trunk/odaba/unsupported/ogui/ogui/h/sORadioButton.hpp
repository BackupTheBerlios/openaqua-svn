/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORadioButton

\brief    Radio button
          Radio  buttons are  value lists  with one  possible selection. A radio
          button works similar to drop down combo boxes.
          q4 the buttongroup manages the storage of the buttons with no visual

\date     $Date: 2006/03/13 21:34:29,89 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ORadioButton_HPP
#define   ORadioButton_HPP

class     ORadioButton;

class     DBorder;
class     ODataWidget;
class     OEHControlList;
class     OEHEvent;
class     OListCtl;
class     ORadioButtonGroup;
#include  <sODS.hpp>
#include  <sOEHControlListValue.hpp>
#include  <sOWidget.hpp>
#pragma pack(4)

class  ORadioButton :public QScrollArea,
public OEHControlListValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //
protected  :         ORadioButtonGroup                           *buttonGroup;                                               //

public     :
                     ORadioButtonGroup                           *get_buttonGroup() { return(buttonGroup); }
public     : virtual                             logical Activate ( );
public     :                                     public slots: void ClearData ( );
public     :                                     QString CurrentText ( );
public     : virtual                             logical Deactivate (logical data_only=NO );
public     :                                     void FillData ( );
public     :                                     void FillList ( );
public     : virtual                             QFrame *FrameQ ( );
public     :                                     void Initialize (char *label_text, logical auto_size=NO, int32 no_strips=1, logical hori_strip=NO );
public     : virtual                             OListCtl *ListControl ( );
public     :         OGUI7ImpExp                                         ORadioButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, char *label_text, logical auto_size=NO, ODS *pODS_w=NULL, int32 no_strips=1, logical hori_strip=NO );
protected  : virtual OGUI7ImpExp                 void OnSetupListCaption (ODS &rODSList, ODS &rODSCaption, logical fSetup );
public     : virtual                             void SetFrameStyle (DBorder *pDBorder );
public     :                                     void SetReadOnly (logical fReadOnly );
public     :                                     QWidget *WidgetQ ( );
public     :                                     logical getEnabled ( );
public     :                                     void resizeEvent (QResizeEvent *pQResizeEvent );
public     :                                     void storeToValue ( );
public     : virtual OGUI7ImpExp                                         ~ORadioButton ( );
};

#pragma pack()
#endif
