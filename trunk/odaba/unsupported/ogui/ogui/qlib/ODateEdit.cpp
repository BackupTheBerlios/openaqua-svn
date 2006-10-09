/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODateEdit

\brief    


\date     $Date: 2006/07/31 19:54:56,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODateEdit"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mODateEdit.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sQGridLayout.hpp>
#include  <sQPushButton.hpp>
#include  <scfte.hpp>
#include  <sODateEdit.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ODateEdit :: Activate ( )
{
  logical             ini  = stscini();
  logical             term = NO;
  if ( OEHControlValue::Activate() )
    term = YES;
  
  if ( !ini && event_handling )
  {
    connect(this  ,SIGNAL(dateChanged(const QDate &)),
            this  ,SLOT  (storeToValue()));         
  }
    connect(this  ,SIGNAL(customContextMenuRequested(const QPoint &)),
            this  ,SLOT  (slotContextMenu ()));         

  return(term);
}

/******************************************************************************/
/**
\brief  ClearData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void ODateEdit :: ClearData ( )
{

  setDate(QDate());


}

/******************************************************************************/
/**
\brief  DA_PickDate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DA_PickDate"

logical ODateEdit :: DA_PickDate ( )
{
  logical                 term = NO;
  pickDate();
  return(term);
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

logical ODateEdit :: Deactivate (logical data_only )
{
  logical             ini  = stscini();
  logical             term = NO;
  if ( ini && event_handling && !data_only )
  {
    disconnect(this  ,SIGNAL(dateChanged(const QDate &)),
               this  ,SLOT  (storeToValue()));         
  }
  disconnect(this  ,SIGNAL(customContextMenuRequested(const QPoint &)),
             this  ,SLOT  (slotContextMenu ()));         
  
  OEHControlValue::Deactivate(data_only);
  

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

int8 ODateEdit :: ExecuteAction (char *act_names )
{
  char      actname[ID_SIZE];
  cfte     *cfteptr;
  char      executed = AUTO;  // action not found

BEGINSEQ

  static cfte acttbl[] = 
  { 
    /* provide a calendar to pick a date */
    cfte( "PickDate",        ALINK( this, ODateEdit , DA_PickDate ) ), 
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
\brief  FillData - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void ODateEdit :: FillData ( )
{
  dbdt               dt;
  dt = ods()->ValueGetDate();
  if(dt.IsEmpty()){
    setDate(QDate(1752,9,14));
  }else{
    setDate(QDate(dt.GetYear(),dt.GetMonth(),dt.GetDay()));
    SetFormat((DataFormSpec)dfs::GetDateFormat());
  }


}

/******************************************************************************/
/**
\brief  Init - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical ODateEdit :: Init ( )
{
  logical                 term = NO;
  dbdt                    dt(1);
  setMinimumDate(QDate(dt.GetYear(),dt.GetMonth(),dt.GetDay()));
  setContextMenuPolicy(Qt::CustomContextMenu);
  return(term);
}

/******************************************************************************/
/**
\brief  ODateEdit - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODateEdit"

     ODateEdit :: ODateEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QDateEdit(QDate(1752,9,14),pODataWidget ? pODataWidget->WidgetQ() : NULL)
, OEHControlValue(pODataWidget, oODataWidget, create_ods)
, pickWindow(NULL)
, pickCalendar(NULL)
, pickButton(NULL)
, buttonSize(25)
, defaultformat()

{

  Init();

}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODateEdit"

     ODateEdit :: ODateEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QDateEdit(QDate(1752,9,14),pODataWidget ? pODataWidget->WidgetQ() : NULL)
, OEHControlValue(pODataWidget, oODataWidget, pODS)
, pickWindow(NULL)
, pickCalendar(NULL)
, pickButton(NULL)
, buttonSize(25)
, defaultformat()
{

  Init();

}

/******************************************************************************/
/**
\brief  i02 - 



\param  pQWidget - 
\param  oODataWidget - Owning data widget
\param  pODS_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODateEdit"

     ODateEdit :: ODateEdit (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS_w )
                     : QDateEdit(QDate(1752,9,14),pQWidget)
, OEHControlValue(oODataWidget, oODataWidget, pODS_w)
, pickWindow(NULL)
, pickCalendar(NULL)
, pickButton(NULL)
, buttonSize(25)
, defaultformat()
{

  Init();

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

logical ODateEdit :: ProvideContextMenu (QObject *watched )
{
  logical                 term = NO;
  /* well i hacked the contextmenu
     it is not a menu anymore
   */
  pickDate();
  term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  SetButtonSize - sets the default button size for the calendar days 21px seems the minimum optimum lesser means spacing between days, more does produce a larger control



\return term - 

\param  width - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetButtonSize"

logical ODateEdit :: SetButtonSize (int width )
{
logical term = NO;
BEGINSEQ
  if(width<5 || width>100)                          ERROR
  buttonSize = width;

RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  SetFormat - 



\return term - 

\param  dbdtFormat - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFormat"

logical ODateEdit :: SetFormat (const DataFormSpec dbdtFormat )
{
logical term = NO;
BEGINSEQ
switch ( dbdtFormat )
{
case DFS_TTMMJJ_punkt   :
  setDisplayFormat("dd.MM.yy");
  break;
case DFS_TTMMJJJJ_punkt :
  setDisplayFormat("dd.MM.yyyy");
  break;
case DFS_YYMMDD_slash   :
  setDisplayFormat("yy/MM/dd");
  break;
case DFS_YYMMDD_point   :
  setDisplayFormat("yy.MM.dd");
  break;
case DFS_TTMMJJ         :
  setDisplayFormat("dd.MM.yy");
  break;
case DFS_TTMMJJJJ       :
  setDisplayFormat("dd.MM.yyyy");
  break;
case DFS_YYMMDD         :
  setDisplayFormat("yy.MM.dd");
  break;
case DFS_YYYYMMDD       :
  setDisplayFormat("yyyy.MM.dd");
  break;
case DFS_Default        : 
  setDisplayFormat(defaultformat);
  break;
default                 : 
  ERROR
  break;
}

RECOVER
term = YES;
ENDSEQ
return term;
}

/******************************************************************************/
/**
\brief  SetReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void ODateEdit :: SetReadOnly (logical fReadOnly )
{

//  fehlt noch
setEnabled(!fReadOnly);

}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return this - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODateEdit :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  changeCalendar - 



\return term - 

\param  pickDate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "changeCalendar"

logical ODateEdit :: changeCalendar (QDate pickDate )
{
  logical                 term = NO;
  int                     i    = 0;
  QDate                   today(QDate::currentDate())
                         ,curDate(pickDate.year(),pickDate.month(),1)
                         ,qdFirst(curDate);
  int                     iDayOfMonth = 0;
  QObject                *cobj = NULL;
  QList<QPushButton*>    buttons;
  QList<QLabel*>         weeknumbers;
  QPalette               pdaybutton;
  QPalette               psdaybutton;
  QPalette               pcdaybutton;
  // set styles
  pcdaybutton.setColor(QPalette::Window,QColor("white"));
  pcdaybutton.setColor(QPalette::WindowText,QColor("black"));
  pcdaybutton.setColor(QPalette::Button,QColor("green"));
  pcdaybutton.setColor(QPalette::ButtonText,QColor("black"));
  // set styles
  psdaybutton.setColor(QPalette::Window,QColor("white"));
  psdaybutton.setColor(QPalette::WindowText,QColor("black"));
  psdaybutton.setColor(QPalette::Button,QColor("blue"));
  psdaybutton.setColor(QPalette::ButtonText,QColor("black"));
  // set styles
  pdaybutton.setColor(QPalette::Window,QColor("white"));
  pdaybutton.setColor(QPalette::WindowText,QColor("black"));
  pdaybutton.setColor(QPalette::Button,QColor("white"));
  pdaybutton.setColor(QPalette::ButtonText,QColor("black"));

  if (!pickCalendar) createCalendar();
  if(!pickWindow->isVisible())
    pickWindow->move(QCursor::pos());
      
  /* change day buttons */

  buttons = pickCalendar->findChildren<QPushButton *>();
  curDate = curDate.addDays(-1 * qdFirst.dayOfWeek());
  for( i = 0; i< buttons.size() ; i++){
    cobj = (QObject*)buttons[i];
    if(   std_string(cobj->metaObject()->className()) 
       == std_string("QPushButton")){
      curDate = curDate.addDays(1);
      ((QPushButton*)cobj)->setText(QString::number(curDate.day()));
      if(curDate.month()==pickDate.month()){
	      ((QPushButton*)cobj)->setEnabled(true);
	      /* highlight special days */
	      if(curDate==date())
		      ((QPushButton*)cobj)->setPalette(psdaybutton);
		  else if(curDate==today)
		      ((QPushButton*)cobj)->setPalette(pcdaybutton);
		  else
		  	  ((QPushButton*)cobj)->setPalette(pdaybutton);
	  }else{
	      ((QPushButton*)cobj)->setPalette(QPalette());
	      ((QPushButton*)cobj)->setEnabled(false);
	  }
    }
  }
  /* change weeknumbers */
  // beware: first qlabels are days
  weeknumbers = pickCalendar->findChildren<QLabel*>();
  curDate = qdFirst;
  curDate = curDate.addDays(-1 * qdFirst.dayOfWeek());
  for( i = 7; i< weeknumbers.size(); i++){
    cobj = (QObject*)weeknumbers[i];
    if(   std_string(cobj->metaObject()->className()) 
       == std_string("QLabel")){
      curDate = curDate.addDays(7);
      ((QLabel*)cobj)->setText(QString::number(curDate.weekNumber()));
    }
  }
  pickMonthDrop->setCurrentIndex(pickDate.month()-1);
  pickMonthDrop->view()->scrollTo(pickMonthDrop->view()->currentIndex());

  pickYearDrop->setCurrentIndex(pickDate.year()-minimumDate().year());
  QModelIndex mi;
  mi = pickYearDrop->model()->index(pickYearDrop->currentIndex()+50,0);
  pickYearDrop->view()->scrollTo(mi);
  pickDateCurrent = pickDate;

  return(term);
}

/******************************************************************************/
/**
\brief  createCalendar - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createCalendar"

logical ODateEdit :: createCalendar ( )
{
  logical                 term = NO;
  int                     i, day, week, pCindex = 1;
  QGridLayout            *grid = NULL;
  QPushButton            *pbDay;
  QLabel                 *pbLabel;
  QString                 qsWeekNumber;
  QPalette                pcalendar;


  /* create popup window that holds all elements */
  if(pickWindow){
    //delete pickWindow;
    return NO;
  }
  pickWindow = new QWidget(this,Qt::Popup);
  pickWindowGrid = new QGridLayout(pickWindow);
  
  /* create navigation */
  pickMonthDrop = new QComboBox(pickWindow);
  for(i=1;i<=12;i++)
    pickMonthDrop->addItem(QDate::longMonthName(i));  
  connect(pickMonthDrop,SIGNAL(activated(int)),this,SLOT(pickMonth(int)));
  pickYearDrop = new QComboBox(pickWindow);
  for(i=minimumDate().year();i<=maximumDate().year();i++)
    pickYearDrop->addItem(QString::number(i));
  connect(pickYearDrop,SIGNAL(activated(int)),this,SLOT(pickYear(int)));
    
  QPushButton *pbPrevMonth = new QPushButton(SZ2QS("<"),pickWindow);
  QPushButton *pbNextMonth = new QPushButton(SZ2QS(">"),pickWindow);
  QPushButton *pbClearDate = new QPushButton(SZ2QS("x"),pickWindow);
  pbPrevMonth->setMaximumWidth(buttonSize);
  pbPrevMonth->setFlat(true);
  pbNextMonth->setMaximumWidth(buttonSize);
  pbNextMonth->setFlat(true);
  pbClearDate->setMaximumWidth(buttonSize);
  pbClearDate->setFlat(true);
 
  
  connect(pbNextMonth,SIGNAL(clicked()),this,SLOT(pickNextMonth()));
  connect(pbPrevMonth,SIGNAL(clicked()),this,SLOT(pickPrevMonth()));
  connect(pbClearDate,SIGNAL(clicked()),this,SLOT(resetDate()));
  
  pickWindowGrid->addWidget(pbPrevMonth,0,0);
  pickWindowGrid->addWidget(pickYearDrop,0,1);
  pickWindowGrid->addWidget(pickMonthDrop,0,2);
  pickWindowGrid->addWidget(pbNextMonth,0,3);
  pickWindowGrid->addWidget(pbClearDate,0,4);
  pickWindowGrid->setMargin(0);
  pickWindowGrid->setSpacing(0);
  
  /* create seperate widget for calendar days for clean lineup */
  pcalendar.setColor(QPalette::Window,QColor("white"));
  pcalendar.setColor(QPalette::WindowText,QColor("black"));
  pcalendar.setColor(QPalette::Base,QColor("white"));
  pcalendar.setColor(QPalette::Button,QColor("white"));
  
  pickCalendar = new QWidget(pickWindow);
  pickCalendar->setPalette(pcalendar);
  grid         = new QGridLayout(pickCalendar);
  grid->setMargin(0);
  grid->setSpacing(0);
  /* buttongroup to receive a indexed signal (dont know how to do that with QPushButtons) */
  QButtonGroup *pickDays = new QButtonGroup(pickCalendar);


//pickDays->hide();
  // QLabel 0-6 (labeling the days)
  connect(pickDays,SIGNAL(buttonClicked(int)),this,SLOT(pickDay(int)));
  /* column header */
  for(day = 0; day < 7; day++){
    pbLabel = new QLabel("<b>" + QDate::shortDayName(day+1) + "</b>",pickCalendar);
    grid->addWidget(pbLabel,1,day+1);
    pbLabel->setMinimumWidth(buttonSize);
    pbLabel->setMaximumWidth(buttonSize);
  }
  // QLabel 7 - 14
  /* create buttons for 6 weeks */
  for(week =  0; week < 6; week++){
    /* label for weeknumbering */
    pbLabel = new QLabel(qsWeekNumber.sprintf("<b>week%i</b>",week),pickCalendar);
    pbLabel->setMinimumWidth(buttonSize);
    pbLabel->setMaximumWidth(buttonSize);
    pbLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    pbLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    grid->addWidget(pbLabel,week+2,0);
    for(day = 0; day < 7; day++){
      pbDay = new QPushButton(pickCalendar);
      pbDay->setMinimumWidth(buttonSize);
      pbDay->setMaximumWidth(buttonSize);
      pbDay->setFlat(true);
      pickDays->addButton(pbDay,pCindex); 
      pCindex++;
      grid->addWidget(pbDay,week+2,day+1);
    }
  }
  pickWindowGrid->addWidget(pickCalendar,1,0,1,5);
  return(term);
}

/******************************************************************************/
/**
\brief  paintEvent - 




\param  pQPaintEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "paintEvent"

void ODateEdit :: paintEvent (QPaintEvent *pQPaintEvent )
{
QPalette pInvalid,pValid;

  pInvalid.setColor(QPalette::Background,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::Foreground,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::Text,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::Button,pValid.color(QPalette::Base));
  pInvalid.setColor(QPalette::ButtonText,pValid.color(QPalette::Base));

  if(date()<=QDate(1870,1,1)){
    setPalette(pInvalid);
  }else{
    setPalette(pValid);
  }
  
  QDateEdit::paintEvent(pQPaintEvent);


}

/******************************************************************************/
/**
\brief  pickDate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickDate"

void ODateEdit :: pickDate ( )
{
QDate dt;

  dt = date();
  if(dt<=QDate(1870,1,1)){
    dt = QDate::currentDate();
  }
  changeCalendar(dt);
  pickWindow->show();
  


}

/******************************************************************************/
/**
\brief  pickDay - 




\param  iDay - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickDay"

void ODateEdit :: pickDay (int iDay )
{
  QDate newDate(pickDateCurrent);
  QDate qdFirst(newDate.year(),newDate.month(),1);
  newDate = newDate.addDays(-1 * qdFirst.dayOfWeek() 
                            + (  1 
                               + iDay 
                               - pickDateCurrent.day()
                              )
                           );  
  setDate(QDate(newDate));
  /* remove pickwindow */
  pickWindow->hide();


}

/******************************************************************************/
/**
\brief  pickMonth - 




\param  iMonth - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickMonth"

void ODateEdit :: pickMonth (int iMonth )
{

BEGINSEQ
  if(!pickMonthDrop)                                LEAVESEQ
  if(iMonth==-1)                                    ERROR
  QDate displaydate(pickDateCurrent.year()
                   ,iMonth+1
                   ,1);
  if(displaydate.daysInMonth()<pickDateCurrent.day())
	  displaydate.addDays(pickDateCurrent.day());
  else
	  displaydate.addDays(displaydate.daysInMonth());
  changeCalendar(displaydate);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  pickNextMonth - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickNextMonth"

void ODateEdit :: pickNextMonth ( )
{

  pickScroll(1);

}

/******************************************************************************/
/**
\brief  pickPrevMonth - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickPrevMonth"

void ODateEdit :: pickPrevMonth ( )
{

  pickScroll(-1);

}

/******************************************************************************/
/**
\brief  pickScroll - 




\param  iDelta - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickScroll"

void ODateEdit :: pickScroll (int iDelta )
{

  QDate displaydate = pickDateCurrent.addMonths(iDelta);
  pickMonthDrop->setCurrentIndex(displaydate.month()-1);
  pickYearDrop->setCurrentIndex(displaydate.year()-minimumDate().year());

  changeCalendar(displaydate);


}

/******************************************************************************/
/**
\brief  pickYear - 




\param  iYear - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pickYear"

void ODateEdit :: pickYear (int iYear )
{

BEGINSEQ
  if(!pickYearDrop)                                  LEAVESEQ
  QDate displaydate(pickYearDrop->currentText().toInt()
                   ,pickDateCurrent.month()
                   ,pickDateCurrent.day());

  changeCalendar(displaydate);
ENDSEQ

}

/******************************************************************************/
/**
\brief  resetDate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "resetDate"

void ODateEdit :: resetDate ( )
{

  StoreToValue(dbdt());
  pickWindow->hide();
  FillData();

}

/******************************************************************************/
/**
\brief  slotContextMenu - provides a contextmenu for the custom signal

        calls  pickdate instead of  the contextmenu functions  - this is ensured
        through the initialisation of the (q)widget


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotContextMenu"

void ODateEdit :: slotContextMenu ( )
{

  pickDate();

}

/******************************************************************************/
/**
\brief  storeToValue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void ODateEdit :: storeToValue ( )
{

  StoreToValue(dbdt(date().day(),date().month(),date().year()));


}


