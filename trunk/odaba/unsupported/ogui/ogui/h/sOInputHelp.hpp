/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OInputHelp

\brief    OInputHelp
          Input  Help Aids the  User during Input  with displaying the available
          possibilities in a list and reduce it as the user types.
          the  list  is  a  OListControl  that  can  be  replaced with any other
          control that is capable to handle the data.
          This  control  calculates  the  desired location, requests the Context
          for  a  propertyhandle  that  is suitable, reduces the listcontrol and
          removes it from sight on cancel

\date     $Date: 2006/03/20 12:11:12,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OInputHelp_HPP
#define   OInputHelp_HPP

class     OInputHelp;

#ifndef   VECTOR_SyntaxHelp_HPP
#define   VECTOR_SyntaxHelp_HPP
#include  <sSyntaxHelp.hpp>
#include  <sVECTOR.h>
#endif
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     ODS;
class     OMultiLineEdit;
class     SyntaxHelp;
#include  <sODataWidget.hpp>
class  OInputHelp :public QObject,
public ODataWidget
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         VECTOR(SyntaxHelp)                           helpdataControls;                                          //
protected  :         ODataWidget                                 *helpdataControl;                                           //
protected  :         QString                                      currentLine;                                               //
protected  :         QString                                      lastLine;                                                  //
protected  :         int32                                        iPosX;                                                     //
protected  :         int32                                        iPosY;                                                     //
protected  :         int32                                        iCurrentIndex;                                             //
protected  :         int32                                        iCurrentParagraph;                                         //
protected  :         int32                                        iPopupIndex;                                               //
protected  :         int32                                        iPopupParagraph;                                           //
protected  :         QString                                      sSearchBuffer;                                             //
protected  :         logical                                      ignore;                                                    //

public     :
                     VECTOR(SyntaxHelp)                          &get_helpdataControls() { return(helpdataControls); }
public     :         OGUIImpExp                  void AddWidget (ODataWidget *pODataWidget, VECTOR(std_string) &vlActivators );
public     :                                     void Commit ( );
public     :                                     logical Default ( );
public     :                                     logical Deinitialize ( );
public     :                                     logical EventProxy (QEvent *proxyEvent );
protected  :                                     logical Find (QString search_s );
protected  :                                     ODataWidget *GetControl (QString qsText );
public     :                                     logical Hide ( );
public     :                                     logical Initialize ( );
public     :                                     logical MakeSearchBuffer ( );
public     :         OGUIImpExp                                          OInputHelp (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     logical Parse (int iParagraph, int iIndex );
public     :                                     logical Parse (QWidget *pQWidget );
public     :                                     logical RemoveWidget (ODataWidget *pODataWidget );
public     :                                     logical Show (int iParagraph, int iIndex );
public     :                                     logical Show (ODataWidget *pODataWidget, int iParagraph, int iIndex );
public     :                                     void Test ( );
public     :                                     logical TestTextPosition ( );
public     :                                     logical Update (QWidget *pQWidget );
public     :                                     logical Update ( );
public     :                                     logical UpdateWidget ( );
public     :                                     QWidget *WidgetQ ( );
protected  :                                     bool eventFilter (QObject *pQObject, QEvent *pQEvent );
public     :         OGUIImpExp                                          ~OInputHelp ( );
};

#endif
