/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ORichTextEdit



\date     $Date: 2006/03/13 21:34:31,40 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ORichTextEdit_HPP
#define   ORichTextEdit_HPP

class     ORichTextEdit;

class     ODS;
class     ODataWidget;
class     OFont;
class     OPopupMenu;
class     OStatusBar;
class     OToolBar;
#include  <sDPoint.hpp>
#include  <sOMultiLineEdit.hpp>
#pragma pack(4)

class  ORichTextEdit :public OMultiLineEdit
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    
protected  :         OPopupMenu                                  *menubar;                                                   //
protected  :         OStatusBar                                  *statusbar;                                                 //
protected  :         OToolBar                                    *toolbar;                                                   //
protected  :         QLabel                                      *status_codeposition;                                       //
protected  :         QTextBlockFormat                             blockformat;                                               //
protected  :         QTextCharFormat                              charformat;                                                //
protected  :         QComboBox                                   *pQFontFamilyWidget;                                        //
protected  :         QComboBox                                   *pQFontSizeWidget;                                          //

public     :
                     OPopupMenu                                  *get_menubar() { return(menubar); }
                     OToolBar                                    *get_toolbar() { return(toolbar); }
public     : virtual OGUI7ImpExp                 logical Activate ( );
public     :                                     logical DA_TextAlign (Qt::Alignment TextAlignment );
public     :                                     logical DA_TextAlignHCenter ( );
public     :                                     logical DA_TextAlignJustify ( );
public     :                                     logical DA_TextAlignLeft ( );
public     :                                     logical DA_TextAlignRight ( );
public     :                                     logical DA_TextBold ( );
public     :                                     logical DA_TextColor ( );
public     :                                     logical DA_TextFont (OFont *pOFont );
public     :                                     logical DA_TextFont ( );
public     :                                     logical DA_TextFontBigger ( );
public     :                                     logical DA_TextFontSmaller ( );
public     :                                     logical DA_TextItalic ( );
public     :                                     logical DA_TextSize (int32 iSize );
public     :                                     logical DA_TextStrikeOut ( );
public     :                                     logical DA_TextStyle ( );
public     :                                     logical DA_TextStyleIndent (int32 distance );
public     :                                     logical DA_TextStyleIndent ( );
public     :                                     logical DA_TextStyleList ( );
public     :                                     logical DA_TextStyleUnIndent ( );
public     :                                     logical DA_TextUnderline ( );
public     : virtual OGUI7ImpExp                 logical Deactivate (logical data_only=NO );
public     : virtual                             int8 ExecuteAction (char *act_names );
protected  :                                     private slots: void FillData ( );
public     : virtual                             QFrame *FrameQ ( );
protected  :                                     void GetBlockFormat ( );
protected  :                                     void GetCharFormat ( );
public     :         OGUI7ImpExp                                         ORichTextEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
public     : virtual                             logical ProvideContextMenu (QObject *watched );
public     :         OGUI7ImpExp                 logical ProvideToolBar ( );
protected  :                                     void SetBlockFormat ( );
protected  :                                     void SetCharFormat ( );
public     : virtual                             logical SetDefaultReactions ( );
public     :                                     logical SetListFormat (const QTextListFormat &crQTextListFormat );
public     :                                     void SetText (const QString &qscText );
public     :                                     QWidget *WidgetQ ( );
public     :                                     logical dnd_can_decode (const QMimeData *pQMimeData );
public     :                                     logical dnd_drop ( );
public     :         OGUI7ImpExp                 OStatusBar *get_statusbar ( );
protected  : virtual                             void keyPressEvent (QKeyEvent *pQKeyEvent );
public     :                                     public slots: void slotCursorPositionChanged ( );
public     :                                     public slots: void slotFormatChanged (const QTextCharFormat &crQTextCharFormat );
public     :                                     public slots: void slotSetFontFamily (const QString &qscText );
public     :                                     public slots: void slotSetFontSize (const QString &qscText );
public     :                                     void startDrag ( );
protected  :                                     private slots: void storeToValue ( );
};

#pragma pack()
#endif
