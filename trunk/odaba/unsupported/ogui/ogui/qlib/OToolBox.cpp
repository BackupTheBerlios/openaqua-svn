/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OToolBox

\brief    Toolbox for a Toggleable Controlstack
          the  toolbox accepts a endless count  of odatawidgets, that are hidden
          (TODO:settings) by default and assigned to a button.
          When  pressing the assigned  button the odw  shows, moving all buttons
          below to get space.
          several odws can be visible at the same time.

\date     $Date: 2006/03/13 21:36:19,17 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OToolBox"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOToolBox.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOToolBox.hpp>


/******************************************************************************/
/**
\brief  AddWidget - Appends a Widget
        Appends the given Widget to the list and provides its button

        //TODO check reparent

        //TODO insert at position

\return indx0 -
-------------------------------------------------------------------------------
\brief  i00


\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddWidget"

int32 OToolBox :: AddWidget (ODataWidget *pODataWidget )
{
  QPushButton            *tButton = NULL;
BEGINSEQ
    if(!pODataWidget)                                ERROR
    if(!pODataWidget->WidgetQ())                     ERROR
    
    items.push_back(pODataWidget);
    sizes.push_back(pODataWidget->WidgetQ()->rect().height());
    
    tButton = new QPushButton(SZ2QS("-"), this);
    tButton->setCheckable(true);
    toggler->addButton(tButton,items.size()-1);

    stack->addWidget(tButton);
    stack->addWidget(pODataWidget->WidgetQ());

    //TODO:settings
    HideWidget(items.size()-1);

RECOVER

ENDSEQ
  return(items.size()-1);
}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  qsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddWidget"

int32 OToolBox :: AddWidget (ODataWidget *pODataWidget, QString qsText )
{
  int indx0 = 0;
  indx0 = AddWidget(pODataWidget);
  SetLabel(indx0, qsText);
  return indx0;
}

/******************************************************************************/
/**
\brief  GetButton - Returns the Button
        Returns  the Button  with the  given index.  the returned pointer can be
        used  to set things like pixmaps or  even uglyer stuff (hide the button)
        for the desperate context

\return pQAbstractButton -

\param  indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetButton"

QAbstractButton *OToolBox :: GetButton (int32 indx0 )
{
  QAbstractButton    *pQAbstractButton = NULL;
BEGINSEQ
  if(indx0<0||(unsigned int)indx0>items.size())      ERROR

  if(!(pQAbstractButton=toggler->button(indx0)))     ERROR
RECOVER
  pQAbstractButton = NULL;
ENDSEQ
  return(pQAbstractButton);
}

/******************************************************************************/
/**
\brief  GetWidget - Returns a Widget by Index
        NULL if out of range

\return pODataWidget - Parent data widget

\param  indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWidget"

ODataWidget *OToolBox :: GetWidget (int32 indx0 )
{
  ODataWidget            *pODataWidget = NULL;
BEGINSEQ
  if(indx0<0||(unsigned int)indx0>items.size())      ERROR
  pODataWidget = items[indx0];
RECOVER
  pODataWidget = NULL;
ENDSEQ
  return(pODataWidget);
}

/******************************************************************************/
/**
\brief  HideWidget - Hides the Widget
        with the indx0

        updates the height of the scrollview

\return term -

\param  indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HideWidget"

logical OToolBox :: HideWidget (int32 indx0 )
{
  logical                 term = NO;
  ODataWidget            *odw  = NULL;
  QWidget                *qw   = NULL;
BEGINSEQ
  if(indx0<0||(unsigned int)indx0>=items.size())     ERROR
  if(!(odw = items[indx0]))                          ERROR
  if(!(qw  = odw->WidgetQ()))                        ERROR
  
  stack->removeWidget(qw);
  qw->hide();

  UpdateSize();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - Initializes
        Constructs the Boxlayouts and ScrollArea

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OToolBox :: Initialize ( )
{
  logical                 term = NO;
  box           = new QVBoxLayout(this);
  toggler       = new QButtonGroup(this);
  toggler->setExclusive(false);
  scrollarea    = new QScrollArea(this);
  scrollsurface = new QWidget(scrollarea);
  stack         = new QVBoxLayout(scrollsurface);
  
  box->addWidget(scrollarea);
  scrollarea->setWidget(scrollsurface);

  connect(toggler,SIGNAL(buttonClicked(int)),this,SLOT(slotToggle(int)));
  return(term);
}

/******************************************************************************/
/**
\brief  OToolBox - Constructs



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolBox"

                        OToolBox :: OToolBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     :  ODataWidget(pODataWidget,oODataWidget,pODS)
,QWidget(pODataWidget?pODataWidget->WidgetQ():NULL)
,box(NULL)
,toggler(NULL)
,scrollarea(NULL)
,scrollsurface(NULL)
,stack(NULL)

{

  Initialize();

}

/******************************************************************************/
/**
\brief  SetLabel - Sets the Label for the Button
        Changes  the  Label  for  the  Button that toggles the Widget Visible or
        Hidden.

\return term -

\param  indx0 -
\param  qsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLabel"

logical OToolBox :: SetLabel (int32 indx0, QString qsText )
{
  logical                 term = NO;
  QAbstractButton        *button = NULL;
BEGINSEQ
  if(!(button=GetButton(indx0)))                     ERROR

  button->setText(qsText);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ShowWidget - Shows the Widget
        with indx0
        updates the scollview height

\return term -

\param  indx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowWidget"

logical OToolBox :: ShowWidget (int32 indx0 )
{
  logical                 term = NO;
  ODataWidget            *odw  = NULL;
  QWidget                *qw   = NULL;
  QAbstractButton        *qpb  = NULL;
  int                     row  = 0;
BEGINSEQ
  if(indx0<0||indx0>=items.size())                   ERROR
  if(!(odw = items[indx0]))                          ERROR
  if(!(qw  = odw->WidgetQ()))                        ERROR
  if(!(qpb = GetButton(indx0)))                      ERROR
  row = stack->indexOf(qpb);
  
  stack->insertWidget(row+1, qw);
  qw->resize(qw->size().width(),sizes[indx0]);
  qw->show();

  UpdateSize();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateSize - Updates the Size
        Each  time a widget is toggled the height of the scollarea widget has to
        be changed in order to provide only as much space as nessesary

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateSize"

logical OToolBox :: UpdateSize ( )
{
  logical                 term = NO;
  QWidget                *qw = NULL;
  QLayoutItem            *li = NULL;
  int                     indx0 = 0
                         ,height = 0
                         ,width = 0
                         ,i = 0;
  QSize                   scrollbarsize;
BEGINSEQ
  if(!scrollarea->verticalScrollBar())                     ERROR
  if(!scrollarea->widget())                                ERROR

  // top and bottom spacing
  height+=stack->spacing()*2;
  while(li = stack->itemAt(indx0++))
    if( qw = li->widget() )
      if( qw->inherits("QPushButton")) // push buttons are handled as widgets
        height+=qw->rect().height();
      else  // the odws had sizes when they where added
        for(i = 0; i<items.size();i++)
          if(items[i] && items[i]->WidgetQ()==qw)
            height+=sizes[i];
  height+=stack->spacing()*indx0;
  width = scrollarea->viewport()->rect().width();
  if(scrollarea->verticalScrollBar()->isHidden()){
    scrollbarsize = scrollarea->verticalScrollBar()->size();
    if(scrollbarsize.width()==101) // qt bug - scollbars not shown yet
      width-=16; // guess maybe bad in other systems
    else
      width-=scrollbarsize.width();
  }
  scrollarea->widget()->resize(width,height);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  slotToggle - slot for all the buttons
        decides what to do (hide|show)


\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotToggle"

void OToolBox :: slotToggle (int index )
{
  QAbstractButton         *b;
BEGINSEQ
  if(index<0 ||(unsigned int)index>=items.size())    ERROR
  if(!items[index] || !items[index]->WidgetQ())      ERROR
  if(!(b = GetButton(index) ) )                      ERROR
  if(items[index]->WidgetQ()->isHidden()){
    ShowWidget(index);
    b->setChecked(true);
  }else{
    HideWidget(index);
	b->setChecked(false);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OToolBox - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OToolBox"

                        OToolBox :: ~OToolBox ( )
{



}


