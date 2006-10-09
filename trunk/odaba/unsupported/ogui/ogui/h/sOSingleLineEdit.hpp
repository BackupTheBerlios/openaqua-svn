/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSingleLineEdit

\brief    


\date     $Date: 2006/03/13 21:34:37,89 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSingleLineEdit_HPP
#define   OSingleLineEdit_HPP

class     OSingleLineEdit;

class     ODSTree;
class     ODataWidget;
class     OEHEvent;
#include  <sDPoint.hpp>
#include  <sODS.hpp>
#include  <sOEHControlValue.hpp>
#pragma pack(4)

class  OSingleLineEdit :public QLineEdit,
public OEHControlValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //
protected  :         QRegExp                                     *rxMask;                                                    //
protected  :         QRegExpValidator                            *rxMaskValidator;                                           //
protected  :         ODSTree                                     *ods_ref;                                                   //

public     :
                     QRegExp                                     *get_rxMask() { return(rxMask); }
                     QRegExpValidator                            *get_rxMaskValidator() { return(rxMaskValidator); }
                     ODSTree                                     *get_ods_ref() { return(ods_ref); }
public     : virtual OGUI7ImpExp                 logical Activate ( );
protected  :                                     private slots: void ClearData ( );
public     : virtual OGUI7ImpExp                 logical Deactivate (logical data_only=NO );
protected  :                                     private slots: void FillData ( );
public     : virtual                             DPoint GetTextPosition ( );
public     :                                     logical Initialize (logical pwd_opt=NO );
public     :         OGUI7ImpExp                                         OSingleLineEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical pwd_opt=NO );
public     :         OGUI7ImpExp                                         OSingleLineEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical pwd_opt=NO );
public     :         OGUI7ImpExp                                         OSingleLineEdit (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS, logical pwd_opt=NO );
public     :         OGUI7ImpExp                                         OSingleLineEdit (QWidget *pQWidget, ODataWidget *oODataWidget, logical create_ods, logical pwd_opt=NO );
public     : virtual                             logical ProvideContextMenu (QObject *watched );
public     :                                     logical SetDefaultReactions ( );
public     :                                     logical SetFlat (bool toggle=FALSE );
public     :                                     void SetReadOnly (logical fReadOnly );
public     : virtual                             void SetTextPosition (DPoint &position );
public     : virtual                             void SetTextSelection (int32 start_pos, int32 length );
public     : virtual                             void SetTextSelection (DPoint start_point, DPoint end_point );
public     :                                     logical UseDefaultHeight ( );
public     :                                     QWidget *WidgetQ ( );
public     :                                     logical getEnabled ( );
protected  :                                     private slots: void initValue ( );
public     :                                     logical setMask (char *szMask, char bCaseSensitive );
protected  :                                     private slots: void storeToValue ( );
public     :                                     void updateSelection ( );
public     :                                                             ~OSingleLineEdit ( );
};

#pragma pack()
#endif
