/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/08/30 12:37:23,60 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OMultiLineEdit"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <mOMultiLineEdit.h>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODocument.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOInputHelp.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOSyntaxHighlighter.hpp>
#include  <scfte.hpp>
#include  <sOMultiLineEdit.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OMultiLineEdit :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( !ini)
  {
    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT  (slotPositionChanged()));
    connect(this, SIGNAL(selectionChanged()),
            this, SLOT  (slotPositionChanged()));
  }				
    
  OEHControlValue::ActivateValue(YES,NO);
  
  if ( !ini)
  {
    // j060330 already has a event filter from oehdw :: activate
    // is the viewport event really nessesary?
    //viewport()->installEventFilter(event_filter); 
    
    connect(this, SIGNAL(textChanged()),
            this, SLOT  (storeToValue()));
  }				
  return(term);
}

/******************************************************************************/
/**
\brief  AddHighlightClass - Adds a class of highlightable strings

        This  function adds a class that is  defined by its name (names) and its
        font  (dfont). every expression  in the DLL  expressions is added to the
        class so the highlighter can colorize it.

        this function is used from OADI

\return term - 

\param  names - 
\param  dsyntaxclass - 
\param  dfont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddHighlightClass"

logical OMultiLineEdit :: AddHighlightClass (char *names, DSyntaxClass &dsyntaxclass, DFont &dfont )
{
  char                   *string = NULL;
  logical                 term   = NO;

  if ( !highlighter )
    HiLightSyntax(HL_UserDefined);

  OFont     ofont = dfont.ToOFont();
  highlighter->Class(names,ofont,ofont.get_text_color());
  //j060830: no match operator=, using pointer instead
  DLL(char) *nexpressions = new DLL(char);
  nexpressions = &dsyntaxclass.get_expressions();
  while ( string = nexpressions->GetNext() )
    highlighter->Add(names,string);
  delete nexpressions;

  return(term);
}

/******************************************************************************/
/**
\brief  ClearData - Clears the Control

        and everything you have written. 

        provided to satisfy OEHControlData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OMultiLineEdit :: ClearData ( )
{

  clear();

}

/******************************************************************************/
/**
\brief  DA_FindEntry - Action Find

        Displays  a  basic  find  dialog  when  you never searched for something
        otherwise  the  searched  string  is  found  from  the  current  cursor 
        position.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_FindEntry"

logical OMultiLineEdit :: DA_FindEntry ( )
{

  if ( GetSearchString(this,"MultiLineEdit",NULL) )
    DA_NewFindEntry();

  return(NO);
}

/******************************************************************************/
/**
\brief  DA_GotoLine - Goes to a specific line

        i0: asks the user for a line and calls i1 with it
        i1: sets the cursor to the given line at column 1

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_GotoLine"

logical OMultiLineEdit :: DA_GotoLine ( )
{
  logical                 term = NO;
  bool                    ok   = false;
  iCurrentLine = QInputDialog::getInteger(this
                                         ,SZ2QS("MultiLineEdit") 
                                         ,SZ2QS("Enter Line") 
                                         ,iCurrentLine           /* default */
                                         ,0                      /* min */
                                         ,2147483647             /* max */
                                         ,1                      /* increment */ 
                                         ,&ok );
  if ( ok )
    DA_GotoLine(iCurrentLine);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  iLine - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_GotoLine"

logical OMultiLineEdit :: DA_GotoLine (int32 iLine )
{

  SetTextPosition(DPoint(1,iLine-1));

  return(NO);
}

/******************************************************************************/
/**
\brief  DA_Indent - Indent the Text

        inserts qsTabcharacter at the beginning of each selected line

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Indent"

logical OMultiLineEdit :: DA_Indent ( )
{

  return ( SetIndent(1) );

}

/******************************************************************************/
/**
\brief  DA_Insert - Inserts text

        Inserts the text at the given position

\return term - 

\param  iLine - 
\param  iColumn - 
\param  szText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_Insert"

logical OMultiLineEdit :: DA_Insert (int32 iLine, int32 iColumn, char *szText )
{
  logical                 term = NO;
  QString                 qsText, qsws;
  QRegExp                 rxWS(SZ2QS("^\\s+"));
  qsText = SZ2QS(szText);
  
  if ( qsText.contains(SZ2QS("\n")) )
  {
    // indent qsText before insert
    qsws.fill(qcTabCharacter,iColumn);
    qsws = SZ2QS("\n") + qsws;
    qsText.replace(QRegExp(SZ2QS("\n")),qsws);
  }
  
  RemoveSelectedText(0);
  InsertText(qsText,DPoint(iColumn,iLine));


  

  return(term);
}

/******************************************************************************/
/**
\brief  DA_NewFindEntry - Continues to find text

        searches  for a previously given text  from the current position or asks
        for searchtext if you never entered some

        sets the found  text selected

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_NewFindEntry"

logical OMultiLineEdit :: DA_NewFindEntry ( )
{
  DPoint              pos;
  pos = GetTextPosition();  
  pos.X += find_text.length();
  
  if ( find_text.isEmpty() ) 
    DA_FindEntry();
  else  
    if ( !find(find_text,0) )
      find(find_text,0);

  return(NO);
}

/******************************************************************************/
/**
\brief  DA_UnIndent - Unindents text

        removes  qstabcharackter (or  any whitespaces)  from the begining of the
        line

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_UnIndent"

logical OMultiLineEdit :: DA_UnIndent ( )
{

  return ( SetIndent(-1) );

}

/******************************************************************************/
/**
\brief  DA_ZoomIn - Maximizes the Window

        enables  the textedit to take all space to the parent toplevel widget to
        have maximum edit place

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ZoomIn"

logical OMultiLineEdit :: DA_ZoomIn ( )
{
  BEGIN_ONCE(ignore)
  ODataWidget  *newDParent = zoom_out_odw ? zoom_out_odw : GetFreeWindow();
  QWidget      *newParent  = newDParent   ? newDParent->WidgetQ()
                                          : topLevelWidget();
  QGridLayout  *orglayout  = NULL;
BEGINSEQ
  if ( !orgParent )                                  LEAVESEQ

  if ( in_context_menu )
    clearFocus();

  // restore the widget position by putting it in its
  // previous layout and give back its col and rowspan
  if(newParent && newParent->layout())
    newParent->layout()->removeWidget(this);
  orglayout = (QGridLayout*)orgParent->layout();
  orglayout->addWidget(this,zoomrow,zoomcol,zoomrowspan,zoomcolspan);
  orgParent = NULL;
  if ( in_context_menu )
    setFocus(Qt::OtherFocusReason);

ENDSEQ
  END_ONCE
  return(NO);
}

/******************************************************************************/
/**
\brief  DA_ZoomOut - Restores the Widget

        Restores the Widgetsize from previously maximized (DA_ZoomIn) textedit

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_ZoomOut"

logical OMultiLineEdit :: DA_ZoomOut ( )
{
  BEGIN_ONCE(ignore)
  ODataWidget  *newDParent = zoom_out_odw ? zoom_out_odw : GetFreeWindow();
  QWidget      *newParent  = newDParent   ? newDParent->WidgetQ()
                                          : topLevelWidget();
  QGridLayout  *newLayout  = NULL;
BEGINSEQ
  if ( orgParent )                                   LEAVESEQ
  if ( !newParent )                                  ERROR
  orgParent = (QWidget *)parent();
  
  newLayout = (QGridLayout*)orgParent->layout();
  if(!newLayout)                                     ERROR

  if ( in_context_menu )
    clearFocus();

  // store the current position of the widget
  newLayout ->getItemPosition(newLayout->indexOf(this)
                             ,&zoomrow
                             ,&zoomcol
                             ,&zoomrowspan
                             ,&zoomcolspan
                             );
  newLayout->removeWidget(this);
  // put this into the newparent layout
  // overlapping everything
  newLayout = (QGridLayout*)newParent->layout();
  if(!newLayout)                                     ERROR
  // this triggers focus out which will trigger zoomin:
  newLayout->addWidget(this,0,0,newLayout->columnCount(),newLayout->rowCount());
  // make sure nothing is before the widget
  raise();
  if ( in_context_menu )
    setFocus(Qt::OtherFocusReason);


RECOVER

ENDSEQ
  END_ONCE
  return(NO);
}

/******************************************************************************/
/**
\brief  DPoint2Position - Converts a DPoint to a Position

        the dpoint is in text coordinates beginning with 1:1
        the Position is in QTextEdit(4.1) coordinates (characters from 0)

\return position - 

\param  position - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DPoint2Position"

int32 OMultiLineEdit :: DPoint2Position (DPoint &position )
{
  int                     iPos = NO;
  QTextDocument          *doc = NULL;
  QTextBlock              textblock;
BEGINSEQ
  // y begins@1
  // x begins@1
  if(!(doc = document()))                            ERROR
  textblock = doc->begin();
  int line=1;
  while(textblock.isValid()){
    if(line == position.Y){
      iPos = textblock.position()+(position.X-1);
      LEAVESEQ
    }
    line++;
    textblock = textblock.next();
  }


RECOVER
  iPos = -1;
ENDSEQ
  return(iPos);
}

/******************************************************************************/
/**
\brief  Deactivate - 



\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OMultiLineEdit :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( ini && !data_only )
  {
    disconnect(this, SIGNAL(textChanged()),
               this, SLOT  (storeToValue()));
  }
  
  OEHControlValue::DeactivateValue(YES,NO,data_only);
  
  if ( ini & !data_only )
  {
    disconnect(this, SIGNAL(cursorPositionChanged()),
               this, SLOT  (slotPositionChanged())); 		         
  
    if ( highlight_type == HL_none )
      disconnect(this, SIGNAL(returnPressed()),
                 this, SLOT(slotIndent()));
  }				


  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return term - 

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 OMultiLineEdit :: ExecuteAction (char *act_names )
{
  char      actname[ID_SIZE];
  cfte     *cfteptr;
  char      executed = AUTO;  // action not found

BEGINSEQ
  static cfte acttbl[] = 
  { 
    cfte( "GotoLine",        ALINK( this, OMultiLineEdit, DA_GotoLine ) ), 
    cfte( "Indent",          ALINK( this, OMultiLineEdit, DA_Indent ) ), 
    cfte( "UnIndent",        ALINK( this, OMultiLineEdit, DA_UnIndent ) ), 
  };
  static srt  cftesrt( sizeof( acttbl )/CFTE, CFTE, UNDEF, UNDEF, UNDEF, (char * )acttbl, NO );

  if ( !cftesrt.srtkln( ) )
    cftesrt.srtsor( CFTE_KPS, CFTE_KLN, CFTE_KTP );

  if ( cfteptr = (cfte * )cftesrt.srtigt( cftesrt.srtssr( gvtxstb( actname, act_names, ID_SIZE ) ) ) )
  {
    cfteptr->LINKINST( this );
    if ( cfteptr->ActionCall( ) )
      ; // *fixme* nachrichtenausgabe   OGUIDISPLAY_ERROR
      
    executed = YES;
  }
  else
    executed = OEHDataWidget::ExecuteAction(act_names);
  

RECOVER
  executed = NO;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  FillData - Fills the control with data

        first  removes all content then rereads the data from the ods value (the
        probably cached value)


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OMultiLineEdit :: FillData ( )
{


  BlockSignals(YES);
  clear();
  BlockSignals(NO);
  SetText(ods()->Value());
  



}

/******************************************************************************/
/**
\brief  FocusInEvent - Event when widget is entered

        the  focusinevent sets  (if not  HL_none) the  highlight of the paragaph
        background

\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusInEvent"

int8 OMultiLineEdit :: FocusInEvent ( )
{
  int8   executed = NO;
  //QTextCursor c(document());
  in_context_menu = NO;
  SetHighLightParagraphBackground(YES);

  // give the document a real cursor
  // SetTextPosition(DPoint(0,0));
  if(QTextCursor()==textCursor())
    SetTextPosition(DPoint(0,0));

  OEHDataWidget::FocusInEvent();
  return(NO);
}

/******************************************************************************/
/**
\brief  FocusOutEvent - Event when leaving the Widget

        returns from the zoom mode (when auto_zoom_in is set)
        removes the highlight of the current paragraph
        stores the current selection and scrolling

\return executed - Action executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FocusOutEvent"

int8 OMultiLineEdit :: FocusOutEvent ( )
{

BEGINSEQ
  if ( in_context_menu )                             LEAVESEQ
  if ( !in_context_menu && auto_zoom_in )
    DA_ZoomIn();
    
  SetHighLightParagraphBackground(NO);
  scrollStore();

// disable during debug of input help
//  if ( input_help && !input_help->HasFocus()  && input_help->IsVisible())
//    input_help->Hide();

  OEHDataWidget::FocusOutEvent();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  FrameQ - 



\return pQFrame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OMultiLineEdit :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetCurrentFont - 



\return font - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentFont"

QFont OMultiLineEdit :: GetCurrentFont ( ) const
{
  QFont font;
  // overload this to update the current font according to block
  font = QWidget::font();

  return font;

}

/******************************************************************************/
/**
\brief  GetIndex - line index

        returns the charactercount for the line the given cursor is in

\return count - 

\param  crQTextCursor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 OMultiLineEdit :: GetIndex (const QTextCursor &crQTextCursor )
{
  QTextBlock           b;
  int                  column = 1;
  // begins @ 1
  b = crQTextCursor.block();
  column = crQTextCursor.position() - b.position() + 1;

  return(column);
}

/******************************************************************************/
/**
\brief  GetLine - returns line

        returns the line (block/paragraph) the given cursor is in

\return count - 

\param  crQTextCursor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLine"

int32 OMultiLineEdit :: GetLine (const QTextCursor &crQTextCursor )
{
  logical                 term = NO;
  QTextBlock              b,cb;
  int                     line = 1;
BEGINSEQ
  // begins @ 1
  cb = crQTextCursor.block();
  for(b = document()->begin();b!=document()->end();b = b.next()){
    if(b==cb)                                        LEAVESEQ
    line++;
  }


ENDSEQ
  return(line);
}

/******************************************************************************/
/**
\brief  GetParagraph - get line text

        returns the text of the given line

\return qsText - 

\param  iParagraph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParagraph"

QString OMultiLineEdit :: GetParagraph (int iParagraph )
{
  QTextBlock b;
  int        line = 1;
  b = document()->begin();
  
  while(b.isValid()){
    if(line==iParagraph)
      return b.text();
    line++;
    b = b.next();
  }
  return QString("");

}

/******************************************************************************/
/**
\brief  GetText - gets the control text

        returns the control text in plain text. 
        ! richtextedit will return the control text as html;

\return qsText - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetText"

QString OMultiLineEdit :: GetText ( ) const
{

  return document()->toPlainText();

}

/******************************************************************************/
/**
\brief  GetTextPosition - gets a dpoint for a position

        returns  a  dpoint  (lines/index)  for  the  given  cursor  (i01) or the
        current cursor

\return position - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextPosition"

DPoint OMultiLineEdit :: GetTextPosition ( )
{
  DPoint         position(iCurrentIndex,iCurrentLine);

  // begins @ 1
  position = GetTextPosition(textCursor());

  return(position);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  crQTextCursor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextPosition"

DPoint OMultiLineEdit :: GetTextPosition (const QTextCursor &crQTextCursor )
{
  DPoint position;
  position.X = GetIndex(crQTextCursor);
  position.Y = GetLine(crQTextCursor);

  return position;
}

/******************************************************************************/
/**
\brief  GetTextSelection - gets the current selection

        sets  the  referenced  DPoints  rstart_point,  rend_point to the current
        selection

\return term - 

\param  rstart_point - 
\param  rend_point - 
\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextSelection"

logical OMultiLineEdit :: GetTextSelection (DPoint &rstart_point, DPoint &rend_point, int32 indx0 )
{
  logical                 term = NO;
  int                     istart,iend;
  QTextCursor             cursor;
  cursor = textCursor();
  istart = cursor.selectionStart();
  iend   = cursor.selectionEnd();
  cursor.setPosition(istart);
  rstart_point = GetTextPosition(cursor);
  cursor.setPosition(iend);
  rend_point = GetTextPosition(cursor);


  return(term);
}

/******************************************************************************/
/**
\brief  HiLightDefaultElements - creates a set of highlight rules

        creates the most basic keywords for the c++ language

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HiLightDefaultElements"

logical OMultiLineEdit :: HiLightDefaultElements ( )
{
  logical                 term = NO;
  QFont                   fixfont(SZ2QS( "COURIER" ), 10);
  QColor                  ckeyword(0,0,255);
  QColor                  cokeyword( 23, 164, 8 );
  QColor                  cnumber( 255, 0, 0 );
  QColor                  cstring( 0, 80, 0) ;
  QColor                  coperator( 0, 0, 255 ) ;
  QColor                  cpreprocessor( 80, 80, 255);
  QColor                  ccomment( 80, 80, 80 );
  

BEGINSEQ
  if( !highlighter )                                 ERROR
  // setup syntax items for cpp 
  
  // keywords 
  highlighter->Class( "keyword", fixfont, ckeyword );
  highlighter->Add( "keyword", "\\bauto\\b" );
  highlighter->Add( "keyword", "\\bbreak\\b" );
  highlighter->Add( "keyword", "\\bbool\\b" );
  highlighter->Add( "keyword", "\\bcase\\b" );
  highlighter->Add( "keyword", "\\bchar\\b" );
  highlighter->Add( "keyword", "\\bclass\\b" );
  highlighter->Add( "keyword", "\\bconst\\b" );
  highlighter->Add( "keyword", "\\bcontinue\\b" );
  highlighter->Add( "keyword", "\\bdefault\\b" );
  highlighter->Add( "keyword", "\\bdo\\b" );
  highlighter->Add( "keyword", "\\bdouble\\b" );
  highlighter->Add( "keyword", "\\bdefined\\b" );
  highlighter->Add( "keyword", "\\belse\\b" );
  highlighter->Add( "keyword", "\\benum\\b" );
  highlighter->Add( "keyword", "\\bextern\\b" );
  highlighter->Add( "keyword", "\\bfloat\\b" );
  highlighter->Add( "keyword", "\\bfor\\b" );
  highlighter->Add( "keyword", "\\bgoto\\b" );
  highlighter->Add( "keyword", "\\bif\\b" );
  highlighter->Add( "keyword", "\\bint\\b" );
  highlighter->Add( "keyword", "\\blong\\b" );
  highlighter->Add( "keyword", "\\bregister\\b" );
  highlighter->Add( "keyword", "\\breturn\\b" );
  highlighter->Add( "keyword", "\\bshort\\b" );
  highlighter->Add( "keyword", "\\bsigned\\b" );
  highlighter->Add( "keyword", "\\bsizeof\\b" );
  highlighter->Add( "keyword", "\\bstatic\\b" );
  highlighter->Add( "keyword", "\\bstruct\\b" );
  highlighter->Add( "keyword", "\\bswitch\\b" );
  highlighter->Add( "keyword", "\\btypedef\\b" );
  highlighter->Add( "keyword", "\\bunion\\b" );
  highlighter->Add( "keyword", "\\bunsigned\\b" );
  highlighter->Add( "keyword", "\\bvoid\\b" );
  highlighter->Add( "keyword", "\\bvolatile\\b" );
  highlighter->Add( "keyword", "\\bwhile\\b" );
  // odaba keywords // 
  highlighter->Class( "okeyword", fixfont, cokeyword );
  highlighter->Add( "okeyword", "\\bERROR\\b" );
  highlighter->Add( "okeyword", "\\bLEAVESEQ\\b" );
  highlighter->Add( "okeyword", "\\bUNDEF\\b" );
  highlighter->Add( "okeyword", "\\bNULL\\b" );
  highlighter->Add( "okeyword", "\\bERIC\\b" );
  highlighter->Add( "okeyword", "\\bFIRST_INSTANCE\\b" );
  highlighter->Add( "okeyword", "\\bLAST_INSTANCE\\b" );
  highlighter->Add( "okeyword", "\\bSDBCERR\\b" );
  highlighter->Add( "okeyword", "\\blogical\\b" );
  highlighter->Add( "okeyword", "\\bint8\\b" );
  highlighter->Add( "okeyword", "\\bint16\\b" );
  highlighter->Add( "okeyword", "\\bint32\\b" );
  highlighter->Add( "okeyword", "\\bint64\\b" );
  highlighter->Add( "okeyword", "\\bYES\\b" );
  highlighter->Add( "okeyword", "\\bNO\\b" );
  // numbers //
  highlighter->Class( "number", fixfont, cnumber );
  highlighter->Add( "number", "\\b\\d+\\b" );
  // strings //
  highlighter->Class( "string", fixfont, cstring);
  // well thats tricky - i don't understand it too :)
//  highlighter->Add( "string", "\\\"", "([^(\\\\){1}]|(\\\\){2}|[^(\\\\){3}]|(\\\\){4})\\\"" );
   highlighter->Add( "string", "\\\".*[^\\\\\"]\\\"");
  // does not highlight ""  highlighter->Add( "string", "\\\"", "([^\\\\]|\\\\\\\\)\\\"|\\\"" );
  //operators
  
  highlighter->Class( "operator", fixfont, coperator);
  highlighter->Add( "operator", "\\=" );
  highlighter->Add( "operator", "\\!" );
  highlighter->Add( "operator", "\\?" );
  highlighter->Add( "operator", "\\>" );
  highlighter->Add( "operator", "\\<" );
  highlighter->Add( "operator", "\\+" );
  highlighter->Add( "operator", "\\-" );
  highlighter->Add( "operator", "\\|" );
  highlighter->Add( "operator", "\\*" );
  highlighter->Add( "operator", "\\~" );
  highlighter->Add( "operator", "\\&" );
  highlighter->Add( "operator", "\\^" );
  // preprocessor //
  highlighter->Class( "preprocessor", fixfont, cpreprocessor );
  highlighter->Add( "preprocessor", "#.+\\b" );
  // comments //
  highlighter->Class( "comment", fixfont, ccomment );
  highlighter->Add( "comment", "\\/\\/.*$" );
  // block comment //
  highlighter->Add( "comment", "\\/\\*", "\\*\\/" );

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  HiLightSyntax - manages the syntaxhighlighter

        removes  (HL_none)  or  creates  the  highlighter  and  the  paragraph 
        background. when the type changed from the last call.
        creates   the   highlighter   and   the   default   keyword   ruleset  
        (HL_StandardCode || HL_ExtendedStandardCode)
        "


\param  hl_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HiLightSyntax"

void OMultiLineEdit :: HiLightSyntax (HighLighting hl_type )
{

BEGINSEQ
  if ( highlight_type == hl_type )                   LEAVESEQ
  highlight_type = hl_type;
    
  if ( hl_type == HL_none )
  {
  
    if ( highlighter ) 
      delete highlighter;
    highlighter = NULL;
       
    bHighLightParagraphBackground = NO;
  }
  else
  {
    bHighLightParagraphBackground = YES;
    
    if ( !highlighter )
    {
      highlighter = new OSyntaxHighlighter(this); 
      if ( hl_type == HL_StandardCode || hl_type == HL_ExtendedStandardCode )
        HiLightDefaultElements();
    }
    
  }
  SetHighLightParagraphBackground(bHighLightParagraphBackground);

  slotPositionChanged();

ENDSEQ
  //return(highlighter);
}

/******************************************************************************/
/**
\brief  Initialize - Initializes the Control

        accepts drops
        sets highlightin and wordwraps and tabstops

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OMultiLineEdit :: Initialize ( )
{
  logical                 term = NO;
  has_edit = YES;
  setAcceptDrops(TRUE);
  
  HighLighting hl_type = highlight_type;
  highlight_type = HL_none;
  if ( hl_type != HL_none )
  {
    setFont(QFont(SZ2QS("Courier"),10));
    setWordWrapMode(QTextOption::NoWrap);
    setLineWrapMode(QTextEdit::NoWrap);    
    HiLightSyntax(hl_type);  
  }
  else
  {
    setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    setFont(QFont(SZ2QS("SansSerif"),10));
  }
  
  QFontMetrics  m(font());
  setTabStopWidth(iTabWidth * m.width(SZ2QS(" ")));
  intern_cursor = QTextCursor(document());
  return(term);
}

/******************************************************************************/
/**
\brief  InsertText - Insert Text

        Inserts  the given  text (rcqsText)  to the  given position and sets the
        cursor to the position+rcqsText <- please confirm!

\return term - 

\param  rcqsText - 
\param  dposition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertText"

logical OMultiLineEdit :: InsertText (const QString &rcqsText, DPoint dposition )
{
  logical                 term = NO;
  QTextCursor             cursor;
  cursor = textCursor();
  cursor.setPosition(DPoint2Position(dposition));
  cursor.insertText(rcqsText);
  setTextCursor(cursor);

  return(term);
}

/******************************************************************************/
/**
\brief  LineRect - calculates the line rect

        returns  a qrect that  outlines the current  line beginnig to the widget
        borders

\return crect - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LineRect"

QRect OMultiLineEdit :: LineRect ( )
{
  QRect crect = cursorRect();
  QRect wrect = geometry();

  crect.setX(0);
  crect.setY(crect.y());
  crect.setWidth(wrect.width());
  crect.setHeight(crect.height());

// used int paintEvent

  return(crect);
}

/******************************************************************************/
/**
\brief  OMultiLineEdit - 



\return term - 

\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
\param  hl_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMultiLineEdit"

     OMultiLineEdit :: OMultiLineEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w, HighLighting hl_type )
                     : QTextEdit(pODataWidget ? pODataWidget->WidgetQ() : NULL ),
OEHControlValue(pODataWidget,oODataWidget,pODS_w),
  orgParent(NULL),
  orgRect(),
  maxLayout(NULL),
  in_context_menu(NO),
  odocument(NULL),
  highlight_type(hl_type),
  highlighter(NULL),
  bOverwrite(NO),
  bHighLightParagraphBackground(NO),
  paragraphHighlightBackground(QColor(255,255,127)),
  iCurrentIndex(0),
  iCurrentLine(0),
  iTabWidth(4),
  pos_drop(0,0),
  pos_before_drop(0,0),
  qcTabCharacter('\t'),
  settings(SZ2QS("OMultilineEdit"),this),
  lastLineRect(),
  defaultmenu(NULL),
  defaultmenuaction(NULL)
{

BEGINSEQ
  OGUICERR
  
  Initialize();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ProvideContextMenu - 



\return term - 

\param  watched - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideContextMenu"

logical OMultiLineEdit :: ProvideContextMenu (QObject *watched )
{
  logical         term = NO;
  logical         first = NO;
BEGINSEQ
  if ( !context_menu )
  {
    if ( !(context_menu = new OPopupMenu( this, this )) )
                                                     OGUIERR(95)
  }
  if(defaultmenuaction && context_menu) 
    context_menu->removeAction(defaultmenuaction);
  if(defaultmenu) 
    delete defaultmenu;
  else 
    first = true;
  defaultmenu = createStandardContextMenu();
  defaultmenu->setTitle(SZ2QS("Default"));
  defaultmenuaction = context_menu->addMenu(defaultmenu);
  // do this just for the first time 
  if(first)
    context_menu->SetupActions(oeh()->FindAction(NULL,"___ContextMenu",NO));
  
  oeh()->SetActionDisabled("ZoomOut",NULL,orgParent ? YES : NO );
  oeh()->SetActionDisabled("ZoomIn" ,NULL,orgParent ? NO  : YES );
  oeh()->SetActionDisabled("ImportFile" ,NULL,IsReadOnly());
  
  in_context_menu = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveSelectedText - 



\return term - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveSelectedText"

logical OMultiLineEdit :: RemoveSelectedText (int32 indx0 )
{
  logical                 term = NO;
  /* remove text for selection [indx0] */
 
  textCursor().removeSelectedText();
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultReactions - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OMultiLineEdit :: SetDefaultReactions ( )
{
  logical                 term = NO;
  OEHDataWidget::SetDefaultReactions();
  
  SetGUIDefReaction(NULL,"___ContextMenu",NULL);
  
  SetGUIDefReaction("ZoomOut"     ,OEHShortcut("Ctrl++"),"___ContextMenu");
  SetGUIDefReaction("ZoomIn"      ,OEHShortcut("Ctrl+-"),"___ContextMenu");
  SetGUIDefReaction("ImportFile"  ,OEHShortcut("CTRL+I"),"___ContextMenu")->SetSeparated(YES);
    
  SetGUIDefReaction("GotoLine",    OEHShortcut("CTRL+G"),"___ContextMenu")->SetSeparated(YES);
  SetGUIDefReaction("FindEntry",   OEHShortcut("CTRL+F"),"___ContextMenu");
  SetGUIDefReaction("NewFindEntry",OEHShortcut("F3")    ,"___ContextMenu");

  if ( highlight_type != HL_none )
  {
    SetGUIDefReaction("Indent"    ,OEHShortcut("Tab"));
    SetGUIDefReaction("UnIndent"  ,OEHShortcut("SHIFT+BackTab"));
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetDocument - sets the document

        sets the given document to be used for managing the content.
        deletes  the highlighter before the acctual SET and after that recreates
        the highlighter

\return term - 

\param  pODocument - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDocument"

logical OMultiLineEdit :: SetDocument (ODocument *pODocument )
{
  logical                 term = NO;
BEGINSEQ
  if( !pODocument )                                  ERROR
  if(highlighter)
    delete highlighter;
  highlighter=NULL;
  setDocument(odocument); 
  // set (member highlight_type to none so
  // highligtsyntax will do anything
  HighLighting hl_type = highlight_type;
  highlight_type = HL_none;
  HiLightSyntax(hl_type);

  intern_cursor = QTextCursor(document());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetHighLightParagraphBackground - 



\return term - 

\param  toggle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHighLightParagraphBackground"

logical OMultiLineEdit :: SetHighLightParagraphBackground (bool toggle )
{

BEGINSEQ
  if( !bHighLightParagraphBackground )               LEAVESEQ
  
  viewport()->update(lastLineRect);
  if(toggle)
    viewport()->update(LineRect());

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetIndent - 



\return term - 

\param  iDirection - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIndent"

logical OMultiLineEdit :: SetIndent (int32 iDirection )
{
  QRegExp                 rxWS(SZ2QS("^\\s+"));
  QRegExp                 rxWSS(SZ2QS("^\\s+$"));
  QString                 qsws;
  QString                 qsLine;
  DPoint                  start,end;
  int                     iLine   = 0;
  int                     iLen    = 0;


BEGINSEQ
  iTabWidth = 1;
  
  if( GetTextSelection(start,end,0) )                ERROR
  
  BlockSignals(YES);
  
  for ( iLine = start.Y; iLine<=end.Y; iLine++ )
  {
    if ( iDirection > 0 )
    {
     /* add iTabWidth to each selected paragraph */
      qsws.fill(qcTabCharacter,iTabWidth*iDirection);
      InsertText(qsws,DPoint(1,iLine));
    }
    else
    {
      /* sub iTabWidth form each selected paragraph */
      qsLine = GetParagraph(iLine);
      QTextCursor current = textCursor();
      if ( rxWS.indexIn(qsLine,0) != -1 )
      {
        iLen = rxWS.cap(0).length();
        if ( iLen > iTabWidth*abs(iDirection) )
          SetTextSelection(DPoint(1,iLine),DPoint(iTabWidth*abs(iDirection)+1,iLine),0);
        else
          SetTextSelection(DPoint(1,iLine),DPoint(iLen+1,iLine),0);
        RemoveSelectedText(0);
      }
      setTextCursor(current);
    }
  }
  // select the complete block after indent
  SetTextSelection(DPoint(1,start.Y),DPoint(GetParagraph(end.Y).length()+1,end.Y),0);
  
  BlockSignals(NO);
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OMultiLineEdit :: SetReadOnly (logical fReadOnly )
{

  setReadOnly(fReadOnly);


}

/******************************************************************************/
/**
\brief  SetText - 




\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void OMultiLineEdit :: SetText (const QString &qscText )
{

  document()->setPlainText( qscText );
  scrollRestore();

}

/******************************************************************************/
/**
\brief  SetTextPosition - 




\param  dposition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextPosition"

void OMultiLineEdit :: SetTextPosition (DPoint dposition )
{
  QTextCursor                cursor;

  //setFocus(); // 060412 can kill inputhelp (because parser->output,settexposition removes inputhelp (multilineedit,focusout) while in inputhelp::show
  cursor = textCursor();
  // sometimes the cursor is invalid (no ->d in qt) so later it crashes
  // this is a qtfix against the segfault in void QTextEdit::mouse*Event(QMouseEvent *e)
  if ( cursor == QTextCursor() )  
    cursor = intern_cursor;       
  
  cursor.clearSelection();
  cursor.setPosition(DPoint2Position(dposition));
  setTextCursor(cursor);
  ensureCursorVisible();

}

/******************************************************************************/
/**
\brief  SetTextSelection - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  start_pos - 
\param  length - 
\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void OMultiLineEdit :: SetTextSelection (int32 start_pos, int32 length, int32 indx0 )
{
  QTextCursor     cursor;
  setFocus();
  cursor = textCursor();
  cursor.clearSelection();
  cursor.setPosition(start_pos);
  cursor.setPosition(start_pos + length,QTextCursor::KeepAnchor);
  setTextCursor(cursor);



}

/******************************************************************************/
/**
\brief  i01 - 



\param  start_point - 
\param  end_point - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void OMultiLineEdit :: SetTextSelection (DPoint start_point, DPoint end_point )
{
  QTextCursor                cursor;
  int                        iStart,iEnd;
  iStart = DPoint2Position(start_point);
  iEnd   = DPoint2Position(end_point);
  SetTextSelection(iStart,iEnd-iStart,0);


}

/******************************************************************************/
/**
\brief  i02 - 



\param  start_point - 
\param  end_point - 
\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void OMultiLineEdit :: SetTextSelection (DPoint start_point, DPoint end_point, int32 indx0 )
{

BEGINSEQ
  if(indx0 != 0)                                     ERROR
  SetTextSelection(start_point,end_point);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OMultiLineEdit :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  canInsertFromMimeData - 



\return canInsert - 

\param  cpQMimeData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "canInsertFromMimeData"

bool OMultiLineEdit :: canInsertFromMimeData (const QMimeData *cpQMimeData ) const
{
  bool canInsert = true;
BEGINSEQ

  if(!cpQMimeData)                                   ERROR
  if ( cpQMimeData->hasFormat("application/vnd.odaba.propertyhandle") )
                                                     LEAVESEQ
  if ( cpQMimeData->hasFormat("text/plain") )
                                                     LEAVESEQ
  if ( cpQMimeData->hasFormat("text/xml") )
                                                     LEAVESEQ
  if ( cpQMimeData->hasFormat("text/html") )
                                                     LEAVESEQ
  ERROR

RECOVER
  canInsert = false;
ENDSEQ
  return canInsert;
}

/******************************************************************************/
/**
\brief  contextMenuEvent - 




\param  pQContextMenuEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "contextMenuEvent"

void OMultiLineEdit :: contextMenuEvent (QContextMenuEvent *pQContextMenuEvent )
{

BEGINSEQ
  if(!pQContextMenuEvent)                           ERROR
  
  ContextMenuEvent(this
  ,pQContextMenuEvent->x()
  ,pQContextMenuEvent->y());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  dnd_drop - drop action

        inserts plain text at the current cursor position

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop"

logical OMultiLineEdit :: dnd_drop ( )
{
  logical                 term = YES;
  QTextCursor             c;

BEGINSEQ
  if ( decoded_text.isNull() )                       ERROR
  
  c = cursorForPosition(drop_point);
  c.insertText(decoded_text);
  setTextCursor(c);

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_end - ends the dnd action

        returns the cursor to where it was before the drop
        and calls baseclass

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_end"

logical OMultiLineEdit :: dnd_drop_end ( )
{

  SetTextPosition(pos_before_drop);
  
  ODragAndDrop::dnd_drop_end();
  return(NO);
}

/******************************************************************************/
/**
\brief  dnd_drop_init - initializies dnd

        stores the current cursor position

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_init"

logical OMultiLineEdit :: dnd_drop_init ( )
{

  pos_before_drop = GetTextPosition();

  return(YES);
}

/******************************************************************************/
/**
\brief  dnd_drop_move - action during move

        does  nothing, but should  scroll the widget  when the mouse is near the
        borders

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_move"

logical OMultiLineEdit :: dnd_drop_move ( )
{

  // if at upper and lower boundarys: scroll
  // not implemented yet
  return(NO);
}

/******************************************************************************/
/**
\brief  insertFromMimeData - 




\param  cpQMimeData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "insertFromMimeData"

void OMultiLineEdit :: insertFromMimeData (const QMimeData *cpQMimeData )
{

  QTextEdit::insertFromMimeData(cpQMimeData);

}

/******************************************************************************/
/**
\brief  keyPressEvent - 




\param  pQKeyEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "keyPressEvent"

void OMultiLineEdit :: keyPressEvent (QKeyEvent *pQKeyEvent )
{
  bool tcf = false; // tab changes focus
  QKeyEvent *pTabEvent = NULL;
  if ( textCursor().hasSelection() &&
       ( (pQKeyEvent->key() == Qt::Key_Tab     && pQKeyEvent->modifiers() != Qt::ControlModifier)  ||
         (pQKeyEvent->key() == Qt::Key_Backtab && pQKeyEvent->modifiers() != Qt::ControlModifier)  ||
         pQKeyEvent->key() == Qt::Key_Less  ||
         pQKeyEvent->key() == Qt::Key_Greater  ) ){
    pQKeyEvent->accept();
  }else  if ((   pQKeyEvent->key() == Qt::Key_Tab
              || pQKeyEvent->key() == Qt::Key_Backtab
             ) && pQKeyEvent->modifiers() == Qt::ControlModifier){
    // resend the tab as focus changing event
    tcf = tabChangesFocus();
    setTabChangesFocus(true);
    pTabEvent = new QKeyEvent(QEvent::KeyPress,pQKeyEvent->key(),Qt::NoModifier);
    QCoreApplication::instance()->sendEvent(this,pTabEvent); 
    delete pTabEvent;
    setTabChangesFocus(tcf);
  }else
    QTextEdit::keyPressEvent( pQKeyEvent );
  
    
  if(pQKeyEvent->key() == Qt::Key_Return)
    slotIndent();

// TODO: not sure with inputhelp
//  if ( pQKeyEvent->key() == Key_Escape && orgParent ) 
//    DA_ZoomIn();



}

/******************************************************************************/
/**
\brief  paintEvent - PaintEvent

        Overload
        paints the background of a line if nessesary


\param  pQPaintEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "paintEvent"

void OMultiLineEdit :: paintEvent (QPaintEvent *pQPaintEvent )
{
 QColor bc = paragraphHighlightBackground;
 QRect  r;
  if(bHighLightParagraphBackground && hasFocus()){
    QPainter p(viewport());
    r = LineRect();
    p.setClipping(false);
    p.setPen(Qt::NoPen);
    p.setBrush(bc);
    p.drawRect(r);
    lastLineRect = r;
  }
  
  QTextEdit::paintEvent(pQPaintEvent);


}

/******************************************************************************/
/**
\brief  scrollContentsBy - 




\param  scrollx - 
\param  scrolly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scrollContentsBy"

void OMultiLineEdit :: scrollContentsBy (int scrollx, int scrolly )
{

SetHighLightParagraphBackground(NO);
QTextEdit::scrollContentsBy(scrollx,scrolly);
SetHighLightParagraphBackground(YES);



}

/******************************************************************************/
/**
\brief  scrollRestore - restores widget state

        restores a previously saved state of 
        selection
        scrolling (Y)
        and cursorposition
        from the registry
        SET and after that recreates the highlighter


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scrollRestore"

void OMultiLineEdit :: scrollRestore ( )
{
  int32     objid    = 0;
  int       iScrollY = 0;
  int       iStart   = 0;
  int       iEnd     = 0;
  int       iLength  = 0;
  QString   qsInstance;
BEGINSEQ

  pos_drop.X = 0;
  pos_drop.Y = 0;
  
  if ( !(iLength = GetText().size()) )              ERROR
  if ( !(objid = ods()->InstGetObjID()) )           ERROR
  
  qsInstance.setNum(objid);
  settings.Restore(qsInstance,iScrollY,0);
  settings.Restore(qsInstance + SZ2QS("_selection_start"), iStart, 0);
  settings.Restore(qsInstance + SZ2QS("_selection_end"), iEnd, 0);
  

  if((!iStart&&!iEnd) || iLength<iStart || iLength<iEnd)
                                                    ERROR
  intern_cursor.setPosition(iStart);
  //intern_cursor.setPosition(iEnd,QTextCursor::KeepAnchor);
  setTextCursor(intern_cursor);

  if ( iScrollY )
  {
    //let qt some time to fill the control so i the
    //scrollvalue will be available-
    QCoreApplication::instance()->processEvents(QEventLoop::AllEvents,300); // update the control so it can scroll
    verticalScrollBar()->setValue(iScrollY);
  }

RECOVER
    // give the edit a cursor that will not display with |
  setTextCursor(QTextCursor());
ENDSEQ

}

/******************************************************************************/
/**
\brief  scrollStore - stores widget state

        stores the state state of 
        selection
        scrolling (Y)
        and cursorposition
        in the registry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scrollStore"

void OMultiLineEdit :: scrollStore ( )
{
int iScrollY = 0;
int32 objid  = 0;
QString qsInstance;
BEGINSEQ

objid = ods()->InstGetObjID();
if(!objid)                                          ERROR

iScrollY = verticalScrollBar()->value();
qsInstance.setNum(objid);
settings.Store(qsInstance,iScrollY);
settings.Store(qsInstance + SZ2QS("_selection_start"), textCursor().selectionStart());
settings.Store(qsInstance + SZ2QS("_selection_end"), textCursor().selectionEnd());

settings.SetTimeout(qsInstance,"runtime");
settings.SetTimeout(qsInstance + SZ2QS("_selection_start"),"runtime");
settings.SetTimeout(qsInstance + SZ2QS("_selection_end"),"runtime");

settings.Store();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotIndent - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotIndent"

void OMultiLineEdit :: slotIndent ( )
{
  QString   qsLine;
  QString   qsws;
  QRegExp   rxWS(SZ2QS("^\\s+"));
  QRegExp   rxWSS(SZ2QS("^\\s+$"));
  QRegExp   rxWSAdd1(SZ2QS("\\{\\s*$"));
  QRegExp   rxWSAdd2(SZ2QS("\\)\\s*$"));
  DPoint    pos;
  int       ilen   = 0;


BEGINSEQ
  if ( highlight_type == HL_none )                   LEAVESEQ

  pos = GetTextPosition();
  
  /* get previous line - we pressed enter and the signal occurs after changing the cursor */
  qsLine = GetParagraph(pos.Y-1);
  
  /* match whitespaces of qsLine and adjust the number of whitespaces */
  if ( rxWS.indexIn(qsLine,0) != -1 )
    ilen = rxWS.cap(0).length();
  if ( rxWSAdd1.indexIn(qsLine,0) == pos.X)
    ilen += 1;
  if ( rxWSAdd2.indexIn(qsLine,0) == pos.X)
    ilen += 1;
  /* on empty lines \n is counted as whitespace */
  //if ( rxWSS.indexIn(qsLine,0) != -1 )
  //  ilen -= 1;
  qsws.fill(qcTabCharacter,ilen - rxWS.cap(0).length());
  qsws = qsws.insert(0,rxWS.cap(0) );
  if( qsws.length()>0)  //>=iTabWidth)
    InsertText(qsws,DPoint(1,pos.Y));   
  
  SetTextPosition(DPoint(ilen+1,pos.Y));
ENDSEQ

}

/******************************************************************************/
/**
\brief  slotPositionChanged - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  iParagraph - 
\param  iIndex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotPositionChanged"

void OMultiLineEdit :: slotPositionChanged (int iParagraph, int iIndex )
{
  QString qsPosition;

BEGINSEQ
  if ( highlight_type == HL_none )                   LEAVESEQ
  
  if ( iCurrentLine == iParagraph+1 && iCurrentIndex == iIndex+1 )
                                                     LEAVESEQ
  
  if( bHighLightParagraphBackground && LineRect()!=lastLineRect){
    viewport()->update(LineRect());   // draw current line
    viewport()->update(lastLineRect); // remove last block
  }
  
  
  iCurrentLine  = iParagraph + 1;
  iCurrentIndex = iIndex     + 1;
  if(get_input_help())
    get_input_help()->TestTextPosition();
  GenerateEvent(GEV_Selected);
ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotPositionChanged"

void OMultiLineEdit :: slotPositionChanged ( )
{
  DPoint               pos;
  pos = GetTextPosition();
  slotPositionChanged(pos.Y,pos.X);

}

/******************************************************************************/
/**
\brief  slotSelectionChanged - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotSelectionChanged"

void OMultiLineEdit :: slotSelectionChanged ( )
{

  if( bHighLightParagraphBackground){
    viewport()->update(lastLineRect); // remove last block
  }


}

/******************************************************************************/
/**
\brief  startDrag - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "startDrag"

void OMultiLineEdit :: startDrag ( )
{

  ODragAndDrop::dragEvent();

}

/******************************************************************************/
/**
\brief  storeToValue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void OMultiLineEdit :: storeToValue ( )
{
  QString qsOldNL(QChar(0x0d));
  QString qsValue;
  qsOldNL.append(QChar(0x0a));
  qsValue = GetText().replace(QChar(0x0a),qsOldNL);
  StoreToValue(qsValue);
  


}


