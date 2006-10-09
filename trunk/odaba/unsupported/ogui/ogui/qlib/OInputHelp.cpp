/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OInputHelp

\brief    OInputHelp
          Input  Help Aids the  User during Input  with displaying the available
          possibilities in a list and reduce it as the user types.
          the  list  is  a  OListControl  that  can  be  replaced with any other
          control that is capable to handle the data.
          This  control  calculates  the  desired location, requests the Context
          for  a  propertyhandle  that  is suitable, reduces the listcontrol and
          removes it from sight on cancel

\date     $Date: 2006/07/06 12:27:14,91 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OInputHelp"

#include  <pogui7.h>
#include  <cqt.h>
#include  <iostream.h>
#include  <mOInputHelp.h>
#include  <cItemCandidateTypes.h>
#include  <sItemData.hpp>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOListCtl.hpp>
#include  <sOMultiLineEdit.hpp>
#include  <sSyntaxHelp.hpp>
#include  <sOInputHelp.hpp>


/******************************************************************************/
/**
\brief  AddWidget - Add A Widget

        Adds a widget that is activated by one of the activators.
        if  the  activators  are  redundant  the  last  control  added with that
        activators will display

        reparents the widget and installs this eventfilter


\param  pODataWidget - Parent data widget
\param  vlActivators - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddWidget"

void OInputHelp :: AddWidget (ODataWidget *pODataWidget, VECTOR(std_string) &vlActivators )
{
  QWidget     *qwidget = pODataWidget ? pODataWidget->WidgetQ() : NULL;
  QWidget     *qparent = ParentWidgetQ();
  QStringList  slActivators;
  logical      term    = NO;
BEGINSEQ
  if ( !qwidget )                                    ERROR
    
  helpdataControls.push_back(SyntaxHelp(pODataWidget,vlActivators));
  
  if ( !qparent )                                    ERROR
  
  qwidget->setParent(ParentWidgetQ());   // to get it deleted sometime we handle
  qwidget->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool); // make it up borderless but always on top
  qwidget->removeEventFilter(pODataWidget->WidgetQ()); // remove input help for list
  qwidget->installEventFilter(this);     // get the events in this class
  qwidget->hide();                       // make sure nobody sees it before the parser found something

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Commit - Commits the Selection

        Gets  the  Key  From  the  Helping  Widget  and  inserts  it  into  the 
        parentWidget.
        Removes the input text and replaces it with the Key
        A  special trick is done, when the last  char is a (, this will keep the
        ( as expected

        create  a  selection  from  the  position  the help popped up (usaly the
        character  .  or  ->  )  to  the  position  where  the cursor is now, to
        overwrite  this  text  (which  was  typed to find the entry) and set the
        cursor after the new inserted text


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Commit"

void OInputHelp :: Commit ( )
{
  OEHDataWidget  *oeh_parent   = (OEHDataWidget *)Parent();
  char           *key_val      = NULL;
  QString         qsDifference;
  QString         qslcSearchBuffer = sSearchBuffer.toLower();
  logical         term       = NO;
BEGINSEQ
  if ( !helpdataControl )                           ERROR
  key_val = helpdataControl->GetKey();

  if ( !key_val )                                   ERROR
  // only commit when the buffer contents match the already written letters
  qsDifference = QString(key_val);
  if(qsDifference.toLower().indexOf(qslcSearchBuffer)!=0)
    ERROR
  oeh_parent->SetTextSelection(DPoint(iPopupIndex, iPopupParagraph), DPoint(iCurrentIndex,iCurrentParagraph)); 
  ((OMultiLineEdit *)oeh_parent)->DA_Insert(iPopupParagraph,iPopupIndex,key_val);
  oeh_parent->SetTextPosition(DPoint(iPopupIndex + strlen(key_val),
                                     iPopupParagraph));


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Default - Default

        Trys  to  display  the  Default  Helpcontrol,  the  first  one  with  no
        activators.
        before  that the current  line is parsed  for the previous whitespace to
        pop up the correct control when you are already typing something

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Default"

logical OInputHelp :: Default ( )
{
  OEHDataWidget  *oeh_parent   = (OEHDataWidget *)Parent();
  QWidget        *help_widget     = WidgetQ();
  DPoint          cpos;
  int             iParagraph   = 0;
  int             iIndex       = 0;
  int             iStartIndex  = 0;
  std::vector<SyntaxHelp>::iterator it;
  logical         term         = NO;
BEGINSEQ
  if ( help_widget && help_widget->isVisible() )     LEAVESEQ
  if ( !oeh_parent )                                 ERROR
  if (  Update() )                                   ERROR
  if (  Hide() )                                     ERROR
  // find out what the user typed after the selector and before a whitespace
  // be carefull with the indexes beginning with 0 and 1
  iStartIndex = currentLine.lastIndexOf(QRegExp(SZ2QS("\\b")), iCurrentIndex - (iCurrentIndex>1?2:1) ) + 1; // returns indx0 needs indx

  // Move the cursor to the Position of the Blank
  if( iCurrentIndex - iStartIndex >= 1) {
    // activators that require a tailing blank "new " will not work
    // add when between iStartIndex and iCurrentIndex is just blanks
    sSearchBuffer = currentLine.mid(iStartIndex-1,iCurrentIndex-iStartIndex); // uses indx0
    bool bLoN = false;
    for ( int i = 0; i<sSearchBuffer.length() && !bLoN; i++)
      bLoN = bLoN | sSearchBuffer.at(i).isLetterOrNumber();
    if(!bLoN)
      iStartIndex = iCurrentIndex;
    else
      oeh_parent->SetTextPosition(DPoint(iStartIndex+1,iCurrentParagraph));
  }
  
  // Parse for registered String Sequences 
  // if it fails the 'default' control is shown
  // (to pop up the right control)
  lastLine     = SZ2QS("");
  if(!Parse(iCurrentParagraph,iStartIndex))
    LEAVESEQ
     
  // do the show of the found control
  Show(GetControl(QString()),iCurrentParagraph,iStartIndex+1);


RECOVER
term = YES;
ENDSEQ
  // restore the text Position and force scroll
  if(oeh_parent && iCurrentIndex!=(iStartIndex+1)){ // startindex:indx0 currentindex:indx1
    oeh_parent->SetTextPosition(DPoint(iCurrentIndex,iCurrentParagraph));
    MakeSearchBuffer( );
    Find( sSearchBuffer );
  }

return(term);
}

/******************************************************************************/
/**
\brief  Deinitialize - Deinitialize

        removes the eventfilter from the parent widget

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

logical OInputHelp :: Deinitialize ( )
{
  QWidget             *qparent = ParentWidgetQ();
  logical              term    = NO;

BEGINSEQ
  if ( !qparent )                                    ERROR
  qparent->removeEventFilter(this);

/*
new 
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EventProxy - eventproxy

        sends  the proxyevent to the helpdatacontrol. this enables us to use the
        scrollwheel,  up and down in the helpdatacontrol to navigate and cut off
        these events from the parent

\return term - 

\param  proxyEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventProxy"

logical OInputHelp :: EventProxy (QEvent *proxyEvent )
{
  logical                 term = NO;
  BEGIN_ONCE(ignore)
BEGINSEQ
  if ( !helpdataControl )                            ERROR
  // filter out the events that could cause exceptions
  
  // doubleclick - > could cause the commit and the edit in a cell
  if(proxyEvent->type()==QEvent::MouseButtonDblClick)
    return false; 
  QApplication::sendEvent(helpdataControl->WidgetQ(),proxyEvent);

RECOVER
  term = YES;
ENDSEQ
  END_ONCE
  return(term|ignore);
}

/******************************************************************************/
/**
\brief  Find - Find a String

        Finds the String in the helpdataControl and sets it current

\return term - 

\param  search_s - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

logical OInputHelp :: Find (QString search_s )
{
  logical      term = NO;
  QModelIndex  indx = QModelIndex();
  ItemData    *item = NULL;
  QString      szItemKey;
BEGINSEQ
  if ( !helpdataControl )                            ERROR
    
  // make the located item the current
  // search after current
  if(helpdataControl->WidgetQ()->inherits("OListCtl")){
    OListCtl *l = (OListCtl*)helpdataControl;
    item = l->GetCurrentItem();
    if(item)
      indx = item->GetModelIndex();
    item = l->LocateItem(indx,search_s,NO);
    // locate again if no item is found 
    //std::ostringstream ss;
    //ss << search_s.toStdString() << " : "<< std::string(item->get_key_val());
    //std::cerr << ss << std::endl;
    if(item){
      szItemKey = QString(item->get_key_val());
      if(szItemKey.indexOf(search_s)!=0)
        item = NULL;
    }
  }
  if(!item) 
    item = helpdataControl->LocateItem(search_s,NO);
  if(item)
    helpdataControl->SetCurrentItem(item);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetControl - Gets the Control

        when  you give  qsText, the  text is  matched with the activators of the
        added widgets and returns the found widget (if any)

        a  empty qsText  will return  the DefaultControl  with no activators (if
        any)

\return pODataWidget - Parent data widget

\param  qsText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControl"

ODataWidget *OInputHelp :: GetControl (QString qsText )
{
  std::vector<SyntaxHelp>::iterator it;
  ODataWidget                      *matchControl = NULL;
  // get the control with no activators
  // this is the "default" that is displayed 
  // if Parse did not find a registered control
  for ( it  = helpdataControls.begin();
        it != helpdataControls.end() && !matchControl; 
        it++)
    if(qsText.isEmpty())
      matchControl = (*it).GetDefaultControl();
    else
      matchControl = (*it).GetControl(qsText);

  return(matchControl);
}

/******************************************************************************/
/**
\brief  Hide - Hides the Help

        Resets the Geometry and deactivates the Control

        only works if widget is visible

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Hide"

logical OInputHelp :: Hide ( )
{
  QWidget  *help_widget = WidgetQ();
  logical   term        = NO;
BEGINSEQ
  if ( !help_widget )                                LEAVESEQ
  if ( !help_widget->isVisible() )                   LEAVESEQ
  lastLine = currentLine;
  help_widget->hide();

  help_widget->setGeometry(0,0,100,100);
  helpdataControl->Deactivate(YES);
  helpdataControl = NULL;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - Initializes the Control

        Installs a EventFilter into the parent Control

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OInputHelp :: Initialize ( )
{
  QWidget             *qparent = ParentWidgetQ();
  logical              term    = NO;
BEGINSEQ
  if ( Deinitialize() )                              ERROR

  if ( !qparent )                                    ERROR
  qparent->installEventFilter(this);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MakeSearchBuffer - Creates the Searchbuffer

        Calculates the typed string from the popupindex to the currentIndex

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MakeSearchBuffer"

logical OInputHelp :: MakeSearchBuffer ( )
{
  int       len   = UNDEF;
  int       index = UNDEF;
  logical   term  = NO;
BEGINSEQ
  len   = iCurrentIndex-iPopupIndex>0?iCurrentIndex-iPopupIndex:0;
  index = iPopupIndex - 1;  // index will be used as indx0
  
  sSearchBuffer.truncate(0);
  // check if the given values match the currentLine
  if ( index       <= currentLine.length() &&
       index + len <= currentLine.length()     )
    sSearchBuffer = currentLine.mid(index,len);
  else                                               
    ERROR
  // searchbuffer has no blanks
  int iBlank = sSearchBuffer.indexOf(QRegExp(SZ2QS("\\b")));
  // make sure if there are some, the buffer is used truncated
  // to the first blank
  if (iBlank>=0)
    sSearchBuffer = sSearchBuffer.mid(iBlank,sSearchBuffer.length()-iBlank);
RECOVER
  term = YES;
ENDSEQ
 std::cerr << "search for [" << sSearchBuffer.toStdString() << "]";
  return(term);
}

/******************************************************************************/
/**
\brief  OInputHelp - Constructor

        Initializes


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OInputHelp"

     OInputHelp :: OInputHelp (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     :  ODataWidget(pODataWidget,oODataWidget,pODS)
,helpdataControls()
,helpdataControl(NULL)
,currentLine()
,lastLine()
,iPosX(0)
,iPosY(0)
,iCurrentParagraph(0)
,iCurrentIndex(0)
,iPopupParagraph(0)
,iPopupIndex(0)
,sSearchBuffer()
,ignore(NO)
{

  Initialize();

}

/******************************************************************************/
/**
\brief  Parse - Parses changes

        Parse(QWidget) (called from EventFilter)

        updates the current values (cursorposition) and parses

        Parse(int,int) (called from Parse(QWidget))

        finds  the  control  with  parsing  the  beginning  of the line shows or
        updates the control

\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  iParagraph - 
\param  iIndex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parse"

logical OInputHelp :: Parse (int iParagraph, int iIndex )
{
  ODataWidget            *matchControl = NULL;
  logical                 term = NO;
BEGINSEQ
  if(iIndex==0)                                      ERROR     // cannot be (iIndex>0)
  if(iParagraph==0)                                  ERROR     // cannot be (iParagraph>0)
  if(lastLine==currentLine)                          LEAVESEQ  // optimize

  // match string before cursor to a control
  matchControl = GetControl(currentLine.left(iIndex-1));
  if(matchControl){
    // a string matched and a (new) control is found 
    if(Show(matchControl, iParagraph,iIndex))        ERROR
  }else{
    // no control matched, just update the current (if available)
    if(UpdateWidget())                               ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  pQWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parse"

logical OInputHelp :: Parse (QWidget *pQWidget )
{
  logical      term       = NO;
  QWidget      *help_widget     = WidgetQ();

BEGINSEQ
  if ( help_widget && help_widget->isVisible() )     LEAVESEQ
  // update the current textedit values
  if ( Update(pQWidget) )                            ERROR
  
  // do the parsing
  // not wished @ 060704
  //if ( Parse(iCurrentParagraph,iCurrentIndex) )      ERROR
  //lastLine = currentLine;

RECOVER
  term = YES;
ENDSEQ
  return (term);
}

/******************************************************************************/
/**
\brief  RemoveWidget - Removes Widget

        erases the widget from the list of available controls
        does not delete the widget.
        n) and parses

        Parse(int,int) (called from Parse(QWidget))

        finds  the  control  with  parsing  the  beginning  of the line shows or
        updates the control

\return term - 

\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveWidget"

logical OInputHelp :: RemoveWidget (ODataWidget *pODataWidget )
{
  logical                 term = NO;
  std::vector<SyntaxHelp>::iterator it;

  for(it =helpdataControls.begin();
      it!=helpdataControls.end();
      it++
     )
    if((*it).get_pODataWidget() == pODataWidget){
       helpdataControls.erase(it);
       break;
    }

  return(term);
}

/******************************************************************************/
/**
\brief  Show - Show the Input Help

        = (int,int) = 
        * calculates the popupposition
        *  activates  the  widget  (starts  context)  and hides when the created
        propertyhandle has no data
        *  bends the focus to the displayed widget and sets the text position to
        at the popupposition

        = (ODataWidget*,int,int) = 
        Does  noting if the  Control isnt changed,  otherwise Hides the Control,
        makes the given ODataWidget the Current Control and calls Show(int,int)

\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  iParagraph - 
\param  iIndex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

logical OInputHelp :: Show (int iParagraph, int iIndex )
{
  QWidget        *help_widget     = WidgetQ();
  QWidget        *qparent         = ParentWidgetQ();
  OEHDataWidget  *oeh_parent      = (OEHDataWidget *)Parent();
  QRect           rCurrent;
  QPoint          qpoint;
  logical         term            = NO;
  OMultiLineEdit *pOMultiLineEdit = NULL;
  QScrollArea    *pQScrollView    = NULL;
  QRect           qrParagraph;
  QString         indentString;
  QString         qsws;

BEGINSEQ
  if ( !help_widget )                                ERROR
  if ( !helpdataControl )                            ERROR
  if ( !oeh_parent )                                 ERROR
  if ( !qparent )                                    ERROR
  
  pOMultiLineEdit = (OMultiLineEdit*)qparent;
  pQScrollView    = (QScrollArea*)pOMultiLineEdit->WidgetQ();
  iPopupParagraph = iParagraph;
  iPopupIndex     = iIndex;
  // magic geometry  
  rCurrent = help_widget->rect();
  
  // set the cursor to the paragraph iPopupParagraph
  
  qrParagraph  = pOMultiLineEdit->cursorRect();
  indentString = pOMultiLineEdit->GetParagraph(iPopupParagraph).left(iPopupIndex-1);
  qsws.fill(QChar(' '),pOMultiLineEdit->tabStopWidth());
  indentString = indentString.replace(QChar('\t'),qsws);
  
  // position by font size
  QFontMetrics fm(pOMultiLineEdit->GetCurrentFont());
  iPosX = fm.width(indentString);
  iPosY = qrParagraph.top()+qrParagraph.height();
  
  // correct the scrollbar 
  // qt4.1 has a half correct cursor position - that maybe changes
  iPosX -= pQScrollView->horizontalScrollBar()->value();
  //iPosY += pQScrollView->verticalScrollBar()->value();
  
  qpoint   = qparent->mapToGlobal(QPoint(iPosX,iPosY));
  help_widget->setGeometry(qpoint.x(),qpoint.y(),rCurrent.width(),rCurrent.height());
  // activate to start context activity
  helpdataControl->Activate();
  help_widget->show();
  if ( !helpdataControl )                            ERROR
  if ( helpdataControl->GetPropertyHandle()->GetCount() <= 0 )
  { // hide when no data is available
    Hide();                                          ERROR
  }
  // set the searchindex to first item 
  OListCtl *l = (OListCtl*)helpdataControl;
  l->SetCurrentItem(l->get_listCache().index(0,0));
  // bend some focus signals to control the helpdatacontrol
  qparent->setFocus();
  help_widget->setFocusProxy(qparent);
  oeh_parent->SetTextPosition(DPoint(iPopupIndex,iPopupParagraph));



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODataWidget - Parent data widget
\param  iParagraph - 
\param  iIndex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

logical OInputHelp :: Show (ODataWidget *pODataWidget, int iParagraph, int iIndex )
{
  logical term = NO;

BEGINSEQ
  if ( pODataWidget == helpdataControl )             LEAVESEQ 
  if ( Hide() )                                      ERROR
  helpdataControl = pODataWidget;

RECOVER
  term = YES;
ENDSEQ
  return Show( iParagraph, iIndex );
}

/******************************************************************************/
/**
\brief  Test - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test"

void OInputHelp :: Test ( )
{
/* dummy function to test the inputhelp
 helpdataControl new otreev
*/
}

/******************************************************************************/
/**
\brief  TestTextPosition - Tests the text Position

        Tests  the position of  the cursor and  hides the helpdatacontrol if the
        cursor is not in the right place:
        * other paragraph
        * currentIndex
        * currentindex > searchbuffer.length

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TestTextPosition"

logical OInputHelp :: TestTextPosition ( )
{
  OEHDataWidget  *oeh_parent = (OEHDataWidget *)Parent();
  DPoint          cpos;
  logical         term       = NO;

BEGINSEQ
  if( !oeh_parent )                                  ERROR
  if( !helpdataControl )                             ERROR
  if( !helpdataControl->WidgetQ()->isVisible() )     ERROR
  
  Update();
  // not the same line anymore
  if( iPopupParagraph != iCurrentParagraph )
    return Hide();
  // not before popup
  if( iPopupIndex > iCurrentIndex)
    return Hide();
  // just to space
  MakeSearchBuffer();
  if( iCurrentIndex - iPopupIndex > sSearchBuffer.length() + 1) 
    return Hide();

RECOVER
  term = YES;
ENDSEQ
  return (term);
}

/******************************************************************************/
/**
\brief  Update - updates the variables

        = (QWidget) =

        updates the global variables used by most functions:
        * index,paragraph
        * currentLine
        = () = 
        Wrapper call with ParentWidgetQ()

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pQWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical OInputHelp :: Update (QWidget *pQWidget )
{
  OEHDataWidget  *oeh_parent   = (OEHDataWidget *)Parent();
  OMultiLineEdit *pOMultiLineEdit = (OMultiLineEdit*)(QTextEdit*)pQWidget;
  logical         term         = NO;
  DPoint          cpos;

BEGINSEQ
  if(! oeh_parent )                                  ERROR
  if(! pQWidget )                                    ERROR
  if(! pOMultiLineEdit )                             ERROR
  
  cpos              = oeh_parent->GetTextPosition();
  
  iCurrentIndex = cpos.X;
  iCurrentParagraph = cpos.Y; 
 
  // receive the data where to put the popuplist
  
  currentLine  = pOMultiLineEdit->GetParagraph(iCurrentParagraph);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical OInputHelp :: Update ( )
{

  return Update( ParentWidgetQ() );

}

/******************************************************************************/
/**
\brief  UpdateWidget - Updates the Current Widget

        Updates the Current helpdatacontrol if its visible

        finds  the  current  typed  text  in  the  widget  or  hides  when  the 
        searchbuffer is invalid

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateWidget"

logical OInputHelp :: UpdateWidget ( )
{
  logical                 term = NO;
BEGINSEQ
  if(!helpdataControl)                               ERROR
  if(!helpdataControl->WidgetQ()->isVisible())       ERROR
  
  if(!MakeSearchBuffer() ){
    if( Find(sSearchBuffer) )                        ERROR
  }else{
    if( Hide() )                                     ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - WidgetQ

        returns the WidgetQ of the HelpdataControl if any

\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OInputHelp :: WidgetQ ( )
{

  return ( helpdataControl ? helpdataControl->WidgetQ() : NULL );

}

/******************************************************************************/
/**
\brief  eventFilter - event filter

        for actions to take general

        MinimizeApp (HIDE) - Hide control

        KeyRelease - Parse the input for activators

        MouseClicks - Commit the current selection only if control is visible

        Mousewheel,  Up,  Down,  PageUp,  PageDown  -  Send  this  events to the
        Control

        Enter, (, Esc - Hide the Control</li>
        <li>Enter, ( - Commit the current selection

        Backspace - Hide when searchbuffer is empty

        Space, ), Comma - Hide the control

\return term - 

\param  pQObject - 
\param  pQEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eventFilter"

bool OInputHelp :: eventFilter (QObject *pQObject, QEvent *pQEvent )
{
  bool                       handled = false;
  QKeyEvent                 *k = NULL;
  QChar                      qkey = 0;
BEGINSEQ
  if(! pQEvent )                                     ERROR
  // filter:all
  switch (pQEvent->type()){ 
    case QEvent::Hide:
      return !Hide();
    case QEvent::KeyRelease:
      // parse text input 
      // invalid keys are bs & movement
      qkey = QChar(((QKeyEvent*)pQEvent)->text()[0]);
      if (qkey.isPrint() ) //ikey >= ' ' && ikey < 127 )
        Parse(ParentWidgetQ());
      break;
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonDblClick:
      Commit();
      handled = true;
      return !Hide();
    case QEvent::KeyPress:
      k = (QKeyEvent*)pQEvent;
      // special action: popup the help control according the already typed
      if(   k->key() == Qt::Key_Space 
         && k->modifiers() & Qt::ControlModifier){
        k->accept();
        handled = !Default();                            
        LEAVESEQ
      }
    default:
      break;
  }
   
  // nothing to do if no Control is displayed
  // filter: all
  if(! helpdataControl )                             LEAVESEQ
  if(! helpdataControl->WidgetQ() )                  LEAVESEQ
  if(! helpdataControl->WidgetQ()->isVisible() )     LEAVESEQ
  
  if(pQEvent->type()== QEvent::Wheel)
    handled = !EventProxy(pQEvent);
  
  // nothing to do if event isnt a keypress
  // filter: keypressed
  if( pQEvent->type() != QEvent::KeyPress )          LEAVESEQ
  
  // what keys
  switch(k->key()){
    // commit selection and hide control
    case Qt::Key_Return:
    case Qt::Key_Enter:
      k->accept(); // eat the return
      handled = true;
    case Qt::Key_ParenLeft:
      Commit();
    case Qt::Key_Escape: // just hide control
    case Qt::Key_Space: // accept the user typed data and ignore help
    case Qt::Key_ParenRight:
    case Qt::Key_Comma:
      //handled = !Hide() // prevented , and ()
      Hide();
      break;
    case Qt::Key_Backspace:
      if(!sSearchBuffer.isEmpty()) // hide when the reason of inputhelp has vanished
        break; 
      handled = !Hide();
      break;    
    // navigation to helpdataControl
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
        handled = !EventProxy(pQEvent);
    default:
      break;
  }

RECOVER
  handled = false;
ENDSEQ
  return (handled);
}

/******************************************************************************/
/**
\brief  ~OInputHelp - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OInputHelp"

     OInputHelp :: ~OInputHelp ( )
{



}


