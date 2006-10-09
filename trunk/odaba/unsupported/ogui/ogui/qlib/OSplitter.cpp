/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OSplitter



\date     $Date: 2006/03/24 17:01:03,45 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSplitter"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOSplitter.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODialog.hpp>
#include  <sOSplitter.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OSplitter :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  if ( !ini && event_handling )
  {
    connect(ods(),SIGNAL(OnActivated(logical)) ,
            this ,SLOT  (activateHandle()));
    connect(ods(),SIGNAL(OnHandleOpened()) ,
            this ,SLOT  (openValue()));
    connect(ods(),SIGNAL(OnCollectionChanged()),
            this ,SLOT  (loadValue()));         
    connect(ods(),SIGNAL(OnInstanceSelected()),
            this ,SLOT  (loadValue()));         
    connect(ods(),SIGNAL(OnInstanceInserted()),
            this ,SLOT  (loadValue()));         
  }
  
  OEHDataWidget::Activate();


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

logical OSplitter :: Deactivate (logical data_only )
{
  logical          ini  = stscini();
  logical          term = NO;
  OEHDataWidget::Deactivate(data_only);
  
  if ( ini && event_handling && !data_only )
  {
    disconnect(ods(),SIGNAL(OnActivated(logical)) ,
               this ,SLOT  (activateHandle()));
    disconnect(ods(),SIGNAL(OnHandleOpened()) ,
               this ,SLOT  (openValue()));
    disconnect(ods(),SIGNAL(OnCollectionChanged()),
               this ,SLOT  (loadValue()));         
    disconnect(ods(),SIGNAL(OnInstanceSelected()),
               this ,SLOT  (loadValue()));         
    disconnect(ods(),SIGNAL(OnInstanceInserted()),
               this ,SLOT  (loadValue()));         
  }
  


  return(term);
}

/******************************************************************************/
/**
\brief  FrameQ

\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OSplitter :: FrameQ ( )
{

  return(this);

return NULL;
}

/******************************************************************************/
/**
\brief  OSplitter

-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSplitter"

                        OSplitter :: OSplitter (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QSplitter (pODataWidget ? 
           pODataWidget->WidgetQ() : NULL),
OEHDataWidget (pODataWidget,oODataWidget,create_ods)
{

connect(this,SIGNAL(splitterMoved(int,int))
       ,this,SLOT(resizeEvent()));



}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSplitter"

                        OSplitter :: OSplitter (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QSplitter (pODataWidget ? 
           pODataWidget->WidgetQ() : NULL),
OEHDataWidget (pODataWidget,oODataWidget,pODS)
{



}

/******************************************************************************/
/**
\brief  SetCollapsible


\param  toggle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCollapsible"

void OSplitter :: SetCollapsible (bool toggle )
{
int i;
// set collapsible for all widgets
setChildrenCollapsible(toggle);


}

/******************************************************************************/
/**
\brief  SetHandleWidth - 


\return term -

\param  handle_width -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHandleWidth"

logical OSplitter :: SetHandleWidth (int16 handle_width )
{
  logical            term = NO;
  setHandleWidth(handle_width);
  for(int i=0;i<count();i++)
    handle(i)->setWindowOpacity(0.0);
  return(NO);
}

/******************************************************************************/
/**
\brief  WidgetQ

\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OSplitter :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  activateHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "activateHandle"

void OSplitter :: activateHandle ( )
{

  GenerateEvent(DEV_Activated);
//  loadValue();

}

/******************************************************************************/
/**
\brief  createHandle

\return pQSplitterHandle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "createHandle"

QSplitterHandle *OSplitter :: createHandle ( )
{
QSplitterHandle *h = NULL;
// just eye candy
QPalette qp = palette();
qp.setBrush(QPalette::Light,qp.dark());
qp.setBrush(QPalette::Midlight,qp.button());
qp.setBrush(QPalette::Dark,qp.light());
qp.setBrush(QPalette::Mid,qp.button());
qp.setBrush(QPalette::Shadow,qp.button());

h = QSplitter::createHandle();
if(h)
  h->setPalette(qp);

 return h;
}

/******************************************************************************/
/**
\brief  loadValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "loadValue"

void OSplitter :: loadValue ( )
{

  if ( ods()->ProvideItem() >= IST_selected )
    GenerateEvent(DEV_Fill);


}

/******************************************************************************/
/**
\brief  openValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "openValue"

void OSplitter :: openValue ( )
{

  GenerateEvent(DEV_Opened);
    
  loadValue();

}

/******************************************************************************/
/**
\brief  resizeEvent


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "resizeEvent"

void OSplitter :: resizeEvent ( )
{
  QWidget            *pQWidget = NULL;
  QSizePolicy         policy;
  bool                hasGrowing = false;
BEGINSEQ
for(int i=0;i<count() && !hasGrowing;i++){
  pQWidget = widget(i);
  if(!pQWidget)                                     ERROR
  QSizePolicy p = pQWidget->sizePolicy();
  if( orientation() == Qt::Horizontal ){
    if(p.horizontalPolicy() & QSizePolicy::GrowFlag)
      hasGrowing = true;;
  }else{
	if(p.verticalPolicy() & QSizePolicy::GrowFlag)
      hasGrowing = true;;
  }
}
if(hasGrowing){
  QList<int> lsizes = QSplitter::sizes();
  setSizes(lsizes);
}
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OSplitter


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSplitter"

                        OSplitter :: ~OSplitter ( )
{

  OEHDataWidget::Deactivate(NO);

}


