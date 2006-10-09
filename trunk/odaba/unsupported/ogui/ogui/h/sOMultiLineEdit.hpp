/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OMultiLineEdit

\brief    RichTextEdit
          The provided actions cover the most used style actions:
          alignment,  bold, italics, underline, strikout,  color, font, size and
          list
          while  the first  actions are  very simple  and intuitive to use there
          are some limitations:
          you  cannot remove  a listitem  once it  is a listitem - it technicaly
          stays a listitem forever, but is not visible as one
          you  cannot change  the document  font for multiple paragraphs without
          loosing other formats (underlines and colors)
          the  size of the data in the  control is doubled even trippled because
          it now contains a lot of style data.
          == drag and drop ==
          dnd works as expected:
          from  any text source the plain text will appear at the position where
          you drop it

          there are two ways to get the image to display:
          create a local copy of the image at the disk the ogui80.dll exists:
          ogui80.dll ist in d:/dll/ogui80.dll
          "/images/logos/run.png" will be found as d:/images/logos/run.png
          "images/logos/run.png" will be found d:/dll/images/logos/run.png

\date     $Date: 2006/07/31 20:21:30,05 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OMultiLineEdit_HPP
#define   OMultiLineEdit_HPP

class     OMultiLineEdit;

class     ODS;
class     ODataWidget;
class     ODocument;
class     OSyntaxHighlighter;
#include  <cHighLighting.h>
#include  <sDFont.hpp>
#include  <sDPoint.hpp>
#include  <sDSyntaxClass.hpp>
#include  <sOEHControlValue.hpp>
#include  <sOInputHelp.hpp>
#include  <sOSettings.hpp>
#pragma pack(4)

class  OMultiLineEdit :public QTextEdit,
public OEHControlValue
{
protected  :         QTextCursor                                  intern_cursor;                                             // 
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         QWidget                                     *orgParent;                                                 // 
protected  :         QRect                                        orgRect;                                                   // 
protected  :         QHBoxLayout                                 *maxLayout;                                                 // zoomed layout
protected  :         logical                                      in_context_menu;                                           // 
protected  :         HighLighting                                 highlight_type;                                            // contextmenu
protected  :         logical                                      bOverwrite;                                                // contextmenu
protected  :         logical                                      bHighLightParagraphBackground;                             // contextmenu
public     :         QColor                                       paragraphHighlightBackground;                              // contextmenu
protected  :         int32                                        iCurrentIndex;                                             // contextmenu
protected  :         int32                                        iCurrentLine;                                              // contextmenu
protected  :         int8                                         iTabWidth;                                                 // contextmenu
protected  :         DPoint                                       pos_drop;                                                  // contextmenu
protected  :         DPoint                                       pos_before_drop;                                           // contextmenu
protected  :         QChar                                        qcTabCharacter;                                            // contextmenu
protected  :         OSettings                                    settings;                                                  // contextmenu
public     :         OSyntaxHighlighter                          *highlighter;                                               // 
protected  :         ODocument                                   *odocument;                                                 // document
protected  :         QRect                                        lastLineRect;                                              // 
protected  :         int                                          zoomrow;                                                   // 
protected  :         int                                          zoomcol;                                                   // 
protected  :         int                                          zoomrowspan;                                               // 
protected  :         int                                          zoomcolspan;                                               // 
protected  :         QMenu                                       *defaultmenu;                                               // 
protected  :         QAction                                     *defaultmenuaction;                                         // 

public     :
                     QTextCursor                                 &get_intern_cursor() { return(intern_cursor); }
                     logical                                      get_in_context_menu() { return(in_context_menu); }
                     HighLighting                                &get_highlight_type() { return(highlight_type); }
                     logical                                      get_bHighLightParagraphBackground() { return(bHighLightParagraphBackground); }
                     int32                                        get_iCurrentIndex() { return(iCurrentIndex); }
                     int32                                        get_iCurrentLine() { return(iCurrentLine); }
                     int8                                         get_iTabWidth() { return(iTabWidth); }
                     QChar                                       &get_qcTabCharacter() { return(qcTabCharacter); }
                     OSettings                                   &get_settings() { return(settings); }
                     QMenu                                       *get_defaultmenu() { return(defaultmenu); }
                     QAction                                     *get_defaultmenuaction() { return(defaultmenuaction); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     :                  OGUIImpExp            logical AddHighlightClass (char *names, DSyntaxClass &dsyntaxclass, DFont &dfont );
public     : virtual                                void ClearData ( );
public     :                                        logical DA_FindEntry ( );
public     :                                        logical DA_GotoLine ( );
public     :                                        logical DA_GotoLine (int32 iLine );
public     :                                        logical DA_Indent ( );
public     : virtual          OGUIImpExp            logical DA_Insert (int32 iLine, int32 iColumn, char *szText );
public     :                                        logical DA_NewFindEntry ( );
public     :                                        logical DA_UnIndent ( );
public     : virtual                                logical DA_ZoomIn ( );
public     : virtual                                logical DA_ZoomOut ( );
public     :                                        int32 DPoint2Position (DPoint &position );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     : virtual                                int8 ExecuteAction (char *act_names );
protected  : private slots:                         void FillData ( );
public     : virtual                                int8 FocusInEvent ( );
public     : virtual                                int8 FocusOutEvent ( );
public     : virtual                                QFrame *FrameQ ( );
public     : virtual                                QFont GetCurrentFont ( ) const;
protected  :                                        int32 GetIndex (const QTextCursor &crQTextCursor );
protected  :                                        int32 GetLine (const QTextCursor &crQTextCursor );
public     :                                        QString GetParagraph (int iParagraph );
public     :                                        QString GetText ( ) const;
public     :                                        DPoint GetTextPosition ( );
public     :                                        DPoint GetTextPosition (const QTextCursor &crQTextCursor );
public     :                                        logical GetTextSelection (DPoint &rstart_point, DPoint &rend_point, int32 indx0 );
public     :                  OGUIImpExp            logical HiLightDefaultElements ( );
public     :                  OGUIImpExp            void HiLightSyntax (HighLighting hl_type=HL_none );
public     :                                        logical Initialize ( );
public     :                                        logical InsertText (const QString &rcqsText, DPoint dposition );
public     :                                        QRect LineRect ( );
public     :                  OGUIImpExp                 OMultiLineEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL, HighLighting hl_type=HL_none );
public     : virtual                                logical ProvideContextMenu (QObject *watched );
public     :                                        logical RemoveSelectedText (int32 indx0 );
public     : virtual                                logical SetDefaultReactions ( );
public     :                  OGUIImpExp            logical SetDocument (ODocument *pODocument );
public     :                                        logical SetHighLightParagraphBackground (bool toggle=FALSE );
public     :                                        logical SetIndent (int32 iDirection );
public     :                                        void SetReadOnly (logical fReadOnly );
public     : virtual                                void SetText (const QString &qscText );
public     : virtual                                void SetTextPosition (DPoint dposition );
public     : virtual          OGUIImpExp            void SetTextSelection (int32 start_pos, int32 length, int32 indx0 );
public     : virtual          OGUIImpExp            void SetTextSelection (DPoint start_point, DPoint end_point );
public     : virtual          OGUIImpExp            void SetTextSelection (DPoint start_point, DPoint end_point, int32 indx0 );
public     :                                        QWidget *WidgetQ ( );
public     :                                        bool canInsertFromMimeData (const QMimeData *cpQMimeData ) const;
public     :                                        void contextMenuEvent (QContextMenuEvent *pQContextMenuEvent );
public     :                                        logical dnd_drop ( );
public     :                                        logical dnd_drop_end ( );
public     :                                        logical dnd_drop_init ( );
public     :                                        logical dnd_drop_move ( );
protected  :                                        void insertFromMimeData (const QMimeData *cpQMimeData );
protected  : virtual                                void keyPressEvent (QKeyEvent *pQKeyEvent );
protected  :                                        void paintEvent (QPaintEvent *pQPaintEvent );
protected  : virtual                                void scrollContentsBy (int scrollx, int scrolly );
public     :                                        void scrollRestore ( );
public     :                                        void scrollStore ( );
public     : public slots:                          void slotIndent ( );
public     : public slots:                          void slotPositionChanged (int iParagraph, int iIndex );
public     : public slots:                          void slotPositionChanged ( );
public     : public slots:                          void slotSelectionChanged ( );
public     :                                        void startDrag ( );
protected  : private slots:                         void storeToValue ( );
};

#pragma pack()
#endif
