/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    ORichTextEdit



\date     $Date: 2006/03/29 12:29:13,72 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ORichTextEdit"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <mORichTextEdit.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHActionList.hpp>
#include  <sOEHDataWidgetEventFilter.hpp>
#include  <sOFont.hpp>
#include  <sOIconSet.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOStatusBar.hpp>
#include  <sOToolBar.hpp>
#include  <scfte.hpp>
#include  <sORichTextEdit.hpp>


/******************************************************************************/
/**
\brief  Activate

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ORichTextEdit :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  
  OEHControlValue::ActivateValue(YES,NO);
  
  if ( !ini)
  {
    // j060330 oehdatawidget::activate does that
    //viewport()->installEventFilter(event_filter);
    connect(this, SIGNAL(textChanged()),
            this, SLOT  (storeToValue()));
  }				
  return(term);
}

/******************************************************************************/
/**
\brief  DA_TextAlign - 


\return term - 

\param  TextAlignment - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextAlign"

logical ORichTextEdit :: DA_TextAlign (Qt::Alignment TextAlignment )
{
  

  GetBlockFormat();
  blockformat.setAlignment(TextAlignment);
  SetBlockFormat();


  return(NO);
}

/******************************************************************************/
/**
\brief  DA_TextAlignHCenter - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextAlignHCenter"

logical ORichTextEdit :: DA_TextAlignHCenter ( )
{

  return DA_TextAlign(Qt::AlignHCenter);

}

/******************************************************************************/
/**
\brief  DA_TextAlignJustify - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextAlignJustify"

logical ORichTextEdit :: DA_TextAlignJustify ( )
{

  return DA_TextAlign(Qt::AlignJustify);

}

/******************************************************************************/
/**
\brief  DA_TextAlignLeft - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextAlignLeft"

logical ORichTextEdit :: DA_TextAlignLeft ( )
{

  return DA_TextAlign(Qt::AlignLeft);

}

/******************************************************************************/
/**
\brief  DA_TextAlignRight - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextAlignRight"

logical ORichTextEdit :: DA_TextAlignRight ( )
{

  return DA_TextAlign(Qt::AlignRight);

}

/******************************************************************************/
/**
\brief  DA_TextBold - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextBold"

logical ORichTextEdit :: DA_TextBold ( )
{
  QFont  cfont;
  GetCharFormat();
  cfont = charformat.font();
  cfont.setBold(!cfont.bold());
  charformat.setFont(cfont);
  SetCharFormat();
  return(NO);
}

/******************************************************************************/
/**
\brief  DA_TextColor - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextColor"

logical ORichTextEdit :: DA_TextColor ( )
{
  logical                 term = NO;
  QColor                  col;
  QBrush                  cbrush;
BEGINSEQ
  GetCharFormat();
  cbrush = charformat.foreground();  
  col = QColorDialog::getColor(cbrush.color(),this);
  
  if ( !col.isValid() )                     ERROR
  cbrush.setColor(col);
  charformat.setForeground(cbrush);
  SetCharFormat();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DA_TextFont - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0


\param  pOFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextFont"

logical ORichTextEdit :: DA_TextFont (OFont *pOFont )
{

  GetCharFormat();
  charformat.setFont((QFont)*pOFont);
  SetCharFormat();
  return(NO);
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextFont"

logical ORichTextEdit :: DA_TextFont ( )
{
  logical                 term = NO;
  bool                    ok   = NO;
  QFont                   font;
  font = QFontDialog::getFont( &ok, currentFont(), this );
  if ( ok ) 
    DA_TextFont((OFont*)&font);
  return (term);
}

/******************************************************************************/
/**
\brief  DA_TextFontBigger - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextFontBigger"

logical ORichTextEdit :: DA_TextFontBigger ( )
{
  logical term           = NO;
  GetCharFormat();
  term  = ( DA_TextSize(charformat.font().pointSize()+1) );
  return term;
}

/******************************************************************************/
/**
\brief  DA_TextFontSmaller - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextFontSmaller"

logical ORichTextEdit :: DA_TextFontSmaller ( )
{
  logical              term = NO;
  GetCharFormat();
  term  = ( DA_TextSize(charformat.font().pointSize()+1) );
  return term;
}

/******************************************************************************/
/**
\brief  DA_TextItalic - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextItalic"

logical ORichTextEdit :: DA_TextItalic ( )
{
  QFont cfont;
  GetCharFormat();
  cfont = charformat.font();
  cfont.setItalic(!cfont.italic());
  charformat.setFont(cfont);
  SetCharFormat();
  return(NO);
}

/******************************************************************************/
/**
\brief  DA_TextSize - 


\return term - 

\param  iSize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextSize"

logical ORichTextEdit :: DA_TextSize (int32 iSize )
{
  QFont cfont;
  GetCharFormat();
  cfont = charformat.font();
  cfont.setPointSize(iSize);
  charformat.setFont(cfont);
  SetCharFormat();


  return NO;
}

/******************************************************************************/
/**
\brief  DA_TextStrikeOut - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextStrikeOut"

logical ORichTextEdit :: DA_TextStrikeOut ( )
{
  logical                 term = NO;
  QFont                   cfont;
  GetCharFormat();
  cfont = charformat.font();
  cfont.setStrikeOut(!cfont.strikeOut());
  charformat.setFont(cfont);
  SetCharFormat();
  return(term);
}

/******************************************************************************/
/**
\brief  DA_TextStyle - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextStyle"

logical ORichTextEdit :: DA_TextStyle ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  DA_TextStyleIndent - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0


\param  distance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextStyleIndent"

logical ORichTextEdit :: DA_TextStyleIndent (int32 distance )
{
  QTextListFormat listFormat;
  QTextList      *list  = NULL;
BEGINSEQ
  list = textCursor().currentList();
  if(!list) {
    listFormat.setIndent(distance);
    SetListFormat(listFormat);
    LEAVESEQ
  }
  listFormat = list->format();
  /* weird: relative value
  if(distance)  
    listFormat.setIndent(listFormat.indent() + distance);
  else
  */
    listFormat.setIndent(distance);
  SetListFormat(listFormat);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextStyleIndent"

logical ORichTextEdit :: DA_TextStyleIndent ( )
{

  return DA_TextStyleIndent(1);

}

/******************************************************************************/
/**
\brief  DA_TextStyleList - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextStyleList"

logical ORichTextEdit :: DA_TextStyleList ( )
{
  QTextListFormat listFormat;
  QTextList       *list = NULL;

  list = textCursor().currentList();
  if (!list) {
    listFormat.setStyle(QTextListFormat::ListDisc);
    SetListFormat(listFormat);    
  }else{ // this is a toggle action
    listFormat.setIndent(0);
    SetListFormat(listFormat);
  }


  return(NO);
}

/******************************************************************************/
/**
\brief  DA_TextStyleUnIndent - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextStyleUnIndent"

logical ORichTextEdit :: DA_TextStyleUnIndent ( )
{

  return DA_TextStyleIndent(-1);

}

/******************************************************************************/
/**
\brief  DA_TextUnderline - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_TextUnderline"

logical ORichTextEdit :: DA_TextUnderline ( )
{
  QFont cfont;
  GetCharFormat();
  cfont = charformat.font();
  cfont.setUnderline(!cfont.underline());
  charformat.setFont(cfont);
  SetCharFormat();
  return(NO);
}

/******************************************************************************/
/**
\brief  Deactivate

\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical ORichTextEdit :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( ini && !data_only )
  {
    disconnect(this, SIGNAL(textChanged()),
               this, SLOT  (storeToValue()));
  }
  
  OEHControlValue::DeactivateValue(YES,NO,data_only);
  
  if ( ini && !data_only )
  {
    disconnect(this, SIGNAL(currentFontChanged(const QFont &)),   
               this, SLOT  (slotFontChanged(const QFont &)));
    disconnect(this, SIGNAL(currentColorChanged(const QColor &)),
               this, SLOT  (slotColorChanged(const QColor &)));
    disconnect(this, SIGNAL(selectionChanged()),
               this, SLOT  (slotSelectionChanged()));
  }


  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteAction

\return term - 

\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 ORichTextEdit :: ExecuteAction (char *act_names )
{
  char      actname[ID_SIZE];
  cfte     *cfteptr;
  char      executed = AUTO;  // action not found

BEGINSEQ
  static cfte acttbl[] = 
  { 
    cfte( "TextAlign",          ALINK( this, ORichTextEdit, DA_TextAlign ) ), 
    cfte( "TextBold",           ALINK( this, ORichTextEdit, DA_TextBold ) ), 
    cfte( "TextFont",           ALINK( this, ORichTextEdit, DA_TextFont ) ), 
    cfte( "TextFontBigger",     ALINK( this, ORichTextEdit, DA_TextFontBigger ) ), 
    cfte( "TextFontSmaller",    ALINK( this, ORichTextEdit, DA_TextFontSmaller ) ), 
    cfte( "TextColor",          ALINK( this, ORichTextEdit, DA_TextColor ) ), 
    cfte( "TextItalic",         ALINK( this, ORichTextEdit, DA_TextItalic ) ), 
    cfte( "TextSize",           ALINK( this, ORichTextEdit, DA_TextSize ) ), 
    cfte( "TextStyle",          ALINK( this, ORichTextEdit, DA_TextStyle ) ), 
    cfte( "TextStyleUL",        ALINK( this, ORichTextEdit, DA_TextStyleList ) ), 
    cfte( "TextStyleIndent",    ALINK( this, ORichTextEdit, DA_TextStyleIndent ) ), 
    cfte( "TextStyleUnIndent",  ALINK( this, ORichTextEdit, DA_TextStyleUnIndent ) ), 
    cfte( "TextUnderline",      ALINK( this, ORichTextEdit, DA_TextUnderline ) ),
    cfte( "TextStrikeOut",      ALINK( this, ORichTextEdit, DA_TextStrikeOut ) )
   ,cfte( "TextAlignLeft",      ALINK( this, ORichTextEdit, DA_TextAlignLeft ) )
   ,cfte( "TextAlignRight",     ALINK( this, ORichTextEdit, DA_TextAlignRight ) )
   ,cfte( "TextAlignHCenter",   ALINK( this, ORichTextEdit, DA_TextAlignHCenter ) )
   ,cfte( "TextAlignJustify",   ALINK( this, ORichTextEdit, DA_TextAlignJustify ) )
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
    executed = OMultiLineEdit::ExecuteAction(act_names);

  

RECOVER
  executed = NO;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  FillData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void ORichTextEdit :: FillData ( )
{
  QString           qlvalue;

  int               nlpos;
  QString           nl(SZ2QS("\r\n"))
                   ,htmlnl(SZ2QS("</p><p>"));
  clear();
  
  qlvalue = ods()->Value();
  if ( !qlvalue.isEmpty() )
  {
    if ( qlvalue.indexOf(SZ2QS("<html>")) == -1 )
    {
      while( (nlpos=qlvalue.indexOf(nl))!=-1 )
        qlvalue.replace(nlpos,nl.length(),htmlnl);
      qlvalue.append(SZ2QS("</p>"));
      qlvalue.insert(0,SZ2QS("<p>"));
    }
  }

  SetText(qlvalue);
  



}

/******************************************************************************/
/**
\brief  FrameQ

\return pQFrame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *ORichTextEdit :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetBlockFormat - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBlockFormat"

void ORichTextEdit :: GetBlockFormat ( )
{

blockformat = textCursor().blockFormat();

}

/******************************************************************************/
/**
\brief  GetCharFormat - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCharFormat"

void ORichTextEdit :: GetCharFormat ( )
{

charformat = textCursor().charFormat();

}

/******************************************************************************/
/**
\brief  ORichTextEdit

\return term - 

\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ORichTextEdit"

                        ORichTextEdit :: ORichTextEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : OMultiLineEdit(pODataWidget,oODataWidget,pODS_w,HL_none)
 ,menubar(NULL)
 ,statusbar(NULL)
 ,toolbar(NULL)
 ,status_codeposition(NULL)
 ,pQFontFamilyWidget(NULL)
 ,pQFontSizeWidget(NULL)
 ,blockformat()
 ,charformat()
{

BEGINSEQ
  OGUICERR
  
  has_edit = YES;
  
  setLineWrapMode(QTextEdit::WidgetWidth);
  setAcceptDrops(true);
  setAcceptRichText(true);
  setAutoFormatting(QTextEdit::AutoAll); // bullet list by typin *
  connect(this,SIGNAL(currentCharFormatChanged (QTextCharFormat))
         ,this,SLOT(slotFormatChanged(QTextCharFormat))
         );
  connect(this,SIGNAL(cursorPositionChanged ())
         ,this,SLOT(slotCursorPositionChanged())
         );
    

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ProvideContextMenu

\return term - 

\param  watched - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideContextMenu"

logical ORichTextEdit :: ProvideContextMenu (QObject *watched )
{
  logical           is_created  = context_menu ? YES : NO;
  logical           is_read_only = IsReadOnly();
  logical           term         = NO;
BEGINSEQ
  if ( OMultiLineEdit::ProvideContextMenu(watched) ) ERROR
  
  oeh()->SetActionDisabled("TextBold",           NULL, is_read_only);
  oeh()->SetActionDisabled("TextItalic",         NULL, is_read_only);
  oeh()->SetActionDisabled("TextUnderline",      NULL, is_read_only);
  oeh()->SetActionDisabled("TextAlign",          NULL, is_read_only);
  oeh()->SetActionDisabled("TextSize",           NULL, is_read_only);
  oeh()->SetActionDisabled("TextColor",          NULL, is_read_only);
  oeh()->SetActionDisabled("TextFont",           NULL, is_read_only);
  oeh()->SetActionDisabled("TextFontBigger",     NULL, is_read_only);
  oeh()->SetActionDisabled("TextFontSmaller",    NULL, is_read_only);
  oeh()->SetActionDisabled("TextStyle",          NULL, is_read_only);
  oeh()->SetActionDisabled("TextStyleUL",        NULL, is_read_only);
  oeh()->SetActionDisabled("TextStyleParagraph", NULL, is_read_only);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideToolBar - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideToolBar"

logical ORichTextEdit :: ProvideToolBar ( )
{
  logical                 term = NO;
BEGINSEQ
  if(toolbar)                                        LEAVESEQ
  toolbar = new OToolBar(this,this,(ODS*)NULL);
  // fonts
  if(!pQFontFamilyWidget){
    pQFontFamilyWidget = new QComboBox(toolbar->WidgetQ());
    QFontDatabase qFontDB;
    pQFontFamilyWidget->addItems(qFontDB.families());
    toolbar->addWidget(pQFontFamilyWidget);
    connect(pQFontFamilyWidget,SIGNAL(currentIndexChanged(QString)),this,SLOT(slotSetFontFamily(QString)));
    pQFontFamilyWidget->setEditable(true);
  }
  // fontSize
  if(!pQFontSizeWidget){
    pQFontSizeWidget = new QComboBox(toolbar->WidgetQ());
    QString s;
    QList<int> sizes = QFontDatabase::standardSizes();
    foreach(int i,sizes)
      pQFontSizeWidget->addItem(s.setNum(i));
    toolbar->addWidget(pQFontSizeWidget);
    connect(pQFontSizeWidget,SIGNAL(currentIndexChanged(QString)),this,SLOT(slotSetFontSize(QString)));
    pQFontSizeWidget->setEditable(true);
  }
  
  toolbar->SetupActions(oeh()->FindAction(NULL,"Format",NO));
  
  slotFormatChanged(textCursor().charFormat());


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetBlockFormat - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBlockFormat"

void ORichTextEdit :: SetBlockFormat ( )
{

textCursor().setBlockFormat(blockformat);

}

/******************************************************************************/
/**
\brief  SetCharFormat - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCharFormat"

void ORichTextEdit :: SetCharFormat ( )
{

textCursor().setCharFormat(charformat);

}

/******************************************************************************/
/**
\brief  SetDefaultReactions

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical ORichTextEdit :: SetDefaultReactions ( )
{

  OMultiLineEdit::SetDefaultReactions();
  
  OEHAction *formataction = SetGUIDefReaction("Format","Format","___ContextMenu");
  
  SetGUIDefReaction("TextBold",          OEHShortcut("CTRL+B"),"Format");
  SetGUIDefReaction("TextItalic",        OEHShortcut("CTRL+I"),"Format");
  SetGUIDefReaction("TextUnderline",     OEHShortcut("CTRL+U"),"Format");
  SetGUIDefReaction("TextStrikeOut",     OEHShortcut("CTRL+O"),"Format");
  
  SetGUIDefReaction("TextStyleUL",       OEHShortcut("CTRL+L"),"Format");
 
  SetGUIDefReaction("TextStyleIndent",   OEHShortcut("TAB")      ,"Format");
  SetGUIDefReaction("TextStyleUnIndent", OEHShortcut("SHIFT+TAB"),"Format");
  
  SetGUIDefReaction("TextFontBigger",    OEHShortcut("SHIFT+Greater"),"Format");
  SetGUIDefReaction("TextFontSmaller",   OEHShortcut("SHIFT+Less")   ,"Format");
  SetGUIDefReaction("TextColor",         OEHShortcut("")        ,"Format");
  SetGUIDefReaction("TextFont",          OEHShortcut("")        ,"Format");
  
  formataction->get_childs()->SetIcons();
  formataction = SetGUIDefReaction("Text Alignment","Alignment","Format");
  
  SetGUIDefReaction("TextAlignLeft",     OEHShortcut("ALT+A,L") ,"Alignment");
  SetGUIDefReaction("TextAlignRight",    OEHShortcut("ALT+A,R") ,"Alignment");
  SetGUIDefReaction("TextAlignHCenter",  OEHShortcut("ALT+A,C") ,"Alignment");
  SetGUIDefReaction("TextAlignJustify",  OEHShortcut("ALT+A,J") ,"Alignment");
  
  formataction->get_childs()->SetIcons();
  formataction->SetGrouped(YES);

  return(NO);
}

/******************************************************************************/
/**
\brief  SetListFormat - 


\return term - 

\param  crQTextListFormat - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetListFormat"

logical ORichTextEdit :: SetListFormat (const QTextListFormat &crQTextListFormat )
{
  logical                 term = NO;
  QTextList              *l = NULL;
  QTextCursor             c(textCursor());
  QTextBlock              b;
  bool                    removed;
  l = c.currentList();
  b = document()->findBlock(c.selectionStart());
  while(b.isValid() && b.position() <= textCursor().selectionEnd()){
    if(l){
      removed = false;
      for(int i = 0; !removed && i< l->count();i++){
        if (l->item(i) == b){
          l->removeItem(i);
          removed = true;
        }
      }
    }
    c.setPosition(b.position());
    c.setPosition(b.position() + b.length() - 1,QTextCursor::KeepAnchor);
    QTextList *tl = c.createList(crQTextListFormat);
    /* crashes when indent == 0
    if(crQTextListFormat.indent() == 0)
      while(!tl->isEmpty())
        tl->removeItem(0);
     */
    b = b.next();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetText - 



\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

void ORichTextEdit :: SetText (const QString &qscText )
{

  document()->setHtml(qscText);
  scrollRestore();

}

/******************************************************************************/
/**
\brief  WidgetQ

\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ORichTextEdit :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  dnd_can_decode - adds new decodable mimetypes
        text/html is accepted on dragEnterEvent

\return term - 

\param  pQMimeData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_can_decode"

logical ORichTextEdit :: dnd_can_decode (const QMimeData *pQMimeData )
{
  bool          term = NO;
BEGINSEQ
  if(!pQMimeData)                                    ERROR
  term = ODragAndDrop::dnd_can_decode(pQMimeData);
  term|= pQMimeData->hasFormat("text/html");
RECOVER
  term = NO;
ENDSEQ
  return((logical)term);
}

/******************************************************************************/
/**
\brief  dnd_drop - implements the drop action
        inserts html text when available

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop"

logical ORichTextEdit :: dnd_drop ( )
{
  logical                 term = NO;
  QTextCursor c = cursorForPosition(drop_point);
  if(drop_event && drop_event->mimeData()->hasFormat("text/html")){
    QString droptext = drop_event->mimeData()->html();
    QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(droptext);
    c.insertFragment(fragment);   
    setTextCursor(c);
  }else{
    OMultiLineEdit::dnd_drop();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  get_statusbar - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_statusbar"

OStatusBar *ORichTextEdit :: get_statusbar ( )
{

BEGINSEQ
  if ( statusbar )                                   LEAVESEQ
    
  statusbar = new OStatusBar(this,this,NO);
  
  /* default elements */
  if ( !status_codeposition )
    status_codeposition = new QLabel(this);
  
  /* add elements permanent */  
  
  statusbar->addWidget(status_codeposition,      0);

ENDSEQ
  return statusbar;
}

/******************************************************************************/
/**
\brief  keyPressEvent


\param  pQKeyEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "keyPressEvent"

void ORichTextEdit :: keyPressEvent (QKeyEvent *pQKeyEvent )
{

  if ( ( textCursor().hasSelection() &&
         ( pQKeyEvent->key() == Qt::Key_Tab       ||
           pQKeyEvent->key() == Qt::Key_Backtab   ||
           pQKeyEvent->key() == Qt::Key_Less  ||
           pQKeyEvent->key() == Qt::Key_Greater  ) ) ||
       ( pQKeyEvent->modifiers() & Qt::ControlModifier &&
         ( pQKeyEvent->key() == Qt::Key_B         ||
           pQKeyEvent->key() == Qt::Key_I         ||
           pQKeyEvent->key() == Qt::Key_U         ||
           pQKeyEvent->key() == Qt::Key_L            ) )     )
    pQKeyEvent->accept();
  else
    QTextEdit::keyPressEvent( pQKeyEvent );

}

/******************************************************************************/
/**
\brief  slotCursorPositionChanged - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotCursorPositionChanged"

void ORichTextEdit :: slotCursorPositionChanged ( )
{

GetBlockFormat();
switch(blockformat.alignment()){
  case Qt::AlignRight:
    oeh()->SetActionToggled("TextAlignRight", NULL,YES);
    break;
  case Qt::AlignHCenter:
    oeh()->SetActionToggled("TextAlignHCenter", NULL,YES);
    break;
  case Qt::AlignJustify:
    oeh()->SetActionToggled("TextAlignJustify", NULL,YES );
    break;
  case 0:
  case Qt::AlignLeft:
  default:
    oeh()->SetActionToggled("TextAlignLeft", NULL,YES);
}

oeh()->SetActionToggled("TextStyleUL",   NULL,textCursor().currentList()!=NULL);



}

/******************************************************************************/
/**
\brief  slotFormatChanged - 



\param  crQTextCharFormat - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotFormatChanged"

void ORichTextEdit :: slotFormatChanged (const QTextCharFormat &crQTextCharFormat )
{

BEGINSEQ
if(!oeh())                                           ERROR
oeh()->SetActionToggled("TextBold",      NULL,crQTextCharFormat.font().bold());
oeh()->SetActionToggled("TextItalic",    NULL,crQTextCharFormat.font().italic());
oeh()->SetActionToggled("TextUnderline", NULL,crQTextCharFormat.font().underline());
oeh()->SetActionToggled("TextStrikeOut", NULL,crQTextCharFormat.font().strikeOut());

if(pQFontFamilyWidget)
  pQFontFamilyWidget->lineEdit()->setText( crQTextCharFormat.font().family());

if(pQFontSizeWidget){
  pQFontSizeWidget->setAutoCompletion(false);
  pQFontSizeWidget->lineEdit()->setText( QString::number( crQTextCharFormat.font().pointSize() ) );
  pQFontSizeWidget->setAutoCompletion(true);
}

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotSetFontFamily - 



\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotSetFontFamily"

void ORichTextEdit :: slotSetFontFamily (const QString &qscText )
{

GetCharFormat();
QFont f = charformat.font();
f.setFamily(qscText);
charformat.setFont(f);
SetCharFormat();


}

/******************************************************************************/
/**
\brief  slotSetFontSize - 



\param  qscText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotSetFontSize"

void ORichTextEdit :: slotSetFontSize (const QString &qscText )
{
bool ok = true;
BEGINSEQ
int size = qscText.toUInt(&ok);
if(!ok)                                              ERROR
DA_TextSize(size);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  startDrag


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "startDrag"

void ORichTextEdit :: startDrag ( )
{

  ODragAndDrop::dragEvent();

}

/******************************************************************************/
/**
\brief  storeToValue


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void ORichTextEdit :: storeToValue ( )
{

  StoreToValue( document()->toHtml() );


}


