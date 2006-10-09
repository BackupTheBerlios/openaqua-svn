/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OComboBoxEventFilter



\date     $Date: 2006/05/18 14:30:12,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OComboBoxEventFilter_HPP
#define   OComboBoxEventFilter_HPP

class     OComboBoxEventFilter;

class     OComboBox;
class  OComboBoxEventFilter :public QObject
{
protected  :         OComboBox                                   *cbox;                                                      // 
protected  :         logical                                      hadfocus;                                                  

public     :
public     :                                             OComboBoxEventFilter (OComboBox *pOComboBox );
public     : virtual                                bool eventFilter (QObject *watched, QEvent *pQEvent );
public     : virtual                                     ~OComboBoxEventFilter ( );
};

#endif
