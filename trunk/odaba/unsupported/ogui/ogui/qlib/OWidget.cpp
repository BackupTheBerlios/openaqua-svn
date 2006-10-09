/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OWidget

\brief    


\date     $Date: 2006/07/24 20:32:56,71 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWidget"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <sODataWidget.hpp>
#include  <sOFont.hpp>
#include  <sOWidgetDesignMode.hpp>
#include  <sOWidgetDesignModeBase.hpp>
#include  <sOWidgetDesignModeFactory.hpp>
#include  <sOWidget.hpp>

int32 widg_count = 0;

/******************************************************************************/
/**
\brief  ActivateDesignMode - 




\param  fDmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateDesignMode"

void OWidget :: ActivateDesignMode (logical fDmode )
{

  in_design_mode = fDmode;

  UpdateState();

}

/******************************************************************************/
/**
\brief  DisableDesignMode - sets widget into application mode




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableDesignMode"

void OWidget :: DisableDesignMode ( )
{

  delete    design_mode;
  design_mode    = NULL;
  
  in_design_mode = NO;

  UpdateState();

}

/******************************************************************************/
/**
\brief  EnableDesignMode - sets widget into designmode



\return designer_mode - 

\param  dmode_factory - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableDesignMode"

OWidgetDesignModeBase *OWidget :: EnableDesignMode (OWidgetDesignModeFactory *dmode_factory )
{

BEGINSEQ
  if ( design_mode )                                 LEAVESEQ
    
  if ( !dmode_factory )
    design_mode = (OWidgetDesignModeBase*) new OWidgetDesignMode(this);
  else
    design_mode = dmode_factory->CreateDM(this);
    
  if ( design_mode )
    in_design_mode = YES;

  GetDataWidget()->ods()->ActivateDesignMode(YES);
  UpdateState();

ENDSEQ
  return(design_mode);
}

/******************************************************************************/
/**
\brief  EnableTestRecordMode - Enables Recording of tests



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableTestRecordMode"

logical OWidget :: EnableTestRecordMode ( )
{

  test_record_mode = true;
  return(NO);
}

/******************************************************************************/
/**
\brief  GetBackgroundColor - get background color

        Returns the Background Color of the Widget.
        r  the  control.  Usually,  this  function is overloaded in the specific
        control  classes.  The  base  calss  implements  the  following  default
        actions:
        F1 - Help

\return dcolor - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBackgroundColor"

DColor OWidget :: GetBackgroundColor ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  return (   qwidget 
           ? QCOLOR2DCOLOR(qwidget->palette().color(QPalette::Background))
           : DColor()  );

}

/******************************************************************************/
/**
\brief  GetDataWidget - Get data widget

        The  function returns the data widget, when the object is a ODataWidget.
        When  the object  is not  an ODataWidget,  the function returns the next
        higher parent, which is an ODataWidget.

\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataWidget"

ODataWidget *OWidget :: GetDataWidget ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetDecision - 



\return button0 - 

\param  title_text - 
\param  text - 
\param  button0 - 
\param  button1 - 
\param  button2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

int OWidget :: GetDecision (char *title_text, char *text, int button0, int button1, int button2 )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  return ( QMessageBox::question(this ? qwidget : NULL,
                                 SZ2QS(title_text),SZ2QS(text),
                                 button0,button1,button2)  );

}

/******************************************************************************/
/**
\brief  GetDesignMode - 



\return design_mode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDesignMode"

OWidgetDesignModeBase *OWidget :: GetDesignMode ( )
{

  return(design_mode);

}

/******************************************************************************/
/**
\brief  GetFont - get font

        Returns the Font Object of the Widget.
        n  the object is  a ODataWidget. When  the object is not an ODataWidget,
        the function returns the next higher parent, which is an ODataWidget.

\return dfont - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

DFont OWidget :: GetFont ( )
{
  QWidget    *qwidget = this ? WidgetQ() : (QWidget*) NULL;
  return   qwidget
          ? OFont(qwidget->font(),
                  qwidget->palette().color(QPalette::Foreground),
                  qwidget->palette().color(QPalette::Background)).ToDFont()
          : OFont().ToDFont()               ;


}

/******************************************************************************/
/**
\brief  GetForegroundColor - get foreground color

        Returns the Foreground Color of the Widget.
        object  is  a  ODataWidget.  When  the object is not an ODataWidget, the
        function returns the next higher parent, which is an ODataWidget.

\return dcolor - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetForegroundColor"

DColor OWidget :: GetForegroundColor ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  return (   qwidget 
           ? QCOLOR2DCOLOR(qwidget->palette().color(QPalette::Foreground))
           : DColor()     );

}

/******************************************************************************/
/**
\brief  GetMaxQSizeType - 



\return qSizeType - 

\param  qSizeType - 
\param  size_policy - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMaxQSizeType"

QSizePolicy::Policy __cdecl OWidget :: GetMaxQSizeType (QSizePolicy::Policy qSizeType, ADK_SizeType size_policy )
{

  switch ( GetQSizeType(size_policy) )
  {
    case QSizePolicy::Fixed            : 
           break;
           
    case QSizePolicy::MinimumExpanding : 
           if ( qSizeType != QSizePolicy::Ignored   &&
                qSizeType != QSizePolicy::Expanding    )
             qSizeType = QSizePolicy::MinimumExpanding;
           break;
           
    case QSizePolicy::Expanding        : 
           if ( qSizeType != QSizePolicy::Ignored )
             qSizeType = QSizePolicy::Expanding;
           break;
           
    case QSizePolicy::Preferred        : 
    default                            : 
           if ( qSizeType == QSizePolicy::Fixed )
             qSizeType = QSizePolicy::Preferred;
  }
  return(qSizeType);
}

/******************************************************************************/
/**
\brief  GetName - 



\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *OWidget :: GetName ( )
{
  QWidget           *qwidget = this ? WidgetQ() : NULL;
  static QByteArray  static_qba;
  return (   qwidget 
           ? QS2SZ_P(qwidget->objectName(),static_qba) 
           : NULL );

}

/******************************************************************************/
/**
\brief  GetPosition - get position

        Returns the Position of the Widget relativ to its Parent.

\return dpoint - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

DPoint OWidget :: GetPosition ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  return (   qwidget 
           ? QPOINT2DPOINT(WidgetQ()->pos()) 
           : DPoint() );

}

/******************************************************************************/
/**
\brief  GetQSizeType - 



\return qSizeType - 

\param  size_policy - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetQSizeType"

QSizePolicy::Policy __cdecl OWidget :: GetQSizeType (ADK_SizeType size_policy )
{

  switch ( size_policy )
  {
    case SIZE_Fixed     : return (QSizePolicy::Fixed);  
    case SIZE_Minimal   : return (QSizePolicy::Minimum);
    case SIZE_Grow      : return (QSizePolicy::Expanding);
    case SIZE_Span      : return (QSizePolicy::Maximum);
    case SIZE_undefined : 
    default             : return (QSizePolicy::Preferred);
  }
  


}

/******************************************************************************/
/**
\brief  GetSize - get size

        Returns the Size of the Widget.

\return dsize - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSize"

DSize OWidget :: GetSize ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  return (   qwidget 
           ? QSIZE2DSIZE(WidgetQ()->size()) 
           : DSize()        );

}

/******************************************************************************/
/**
\brief  HasEdit - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasEdit"

logical OWidget :: HasEdit ( )
{

  return ( has_edit );

}

/******************************************************************************/
/**
\brief  HasFocus - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasFocus"

logical OWidget :: HasFocus ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  return ( qwidget ? qwidget->hasFocus() : NO );


}

/******************************************************************************/
/**
\brief  InDesignMode - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InDesignMode"

logical OWidget :: InDesignMode ( )
{

  return ( this ? in_design_mode : NO );

}

/******************************************************************************/
/**
\brief  IsEnabled - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnabled"

logical OWidget :: IsEnabled ( )
{

  return(enabled);

}

/******************************************************************************/
/**
\brief  IsInDesignMode - is designmode on/off

        liefert true wenn sich das widget im designmode befindet.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInDesignMode"

logical OWidget :: IsInDesignMode ( )
{

  return ( design_mode != NULL );

}

/******************************************************************************/
/**
\brief  IsInTestRecordMode - is in testrecordmode

        indicates that we record the events

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInTestRecordMode"

logical OWidget :: IsInTestRecordMode ( )
{

  return test_record_mode;

}

/******************************************************************************/
/**
\brief  IsReadOnly - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReadOnly"

logical OWidget :: IsReadOnly ( )
{

  return(readOnly);

}

/******************************************************************************/
/**
\brief  Move - 

        Moves the Widget along the Vector passed as Argument.
        Returns the new Position as GetPosition would do.

\return dpoint - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  rcDPoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

DPoint OWidget :: Move (const DPoint &rcDPoint )
{

  SetPosition(GetPosition() + rcDPoint);
  return(GetPosition());
}

/******************************************************************************/
/**
\brief  i01 - 



\param  x - 
\param  y - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

DPoint OWidget :: Move (int x, int y )
{

  return( Move(DPoint(x,y)) );

}

/******************************************************************************/
/**
\brief  OWidget - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWidget"

     OWidget :: OWidget ( )
                     :   enabled(YES),
  readOnly(NO),
  has_edit(NO),
  in_design_mode(NO),
  design_mode(NULL),
  test_record_mode(FALSE),
  visible(NO),
  is_destroying(NO)
{

widg_count++;


}

/******************************************************************************/
/**
\brief  Parent - 



\return pOWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

OWidget *OWidget :: Parent ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  RecordTest - Recording a Event

        stores a event

\return term - 

\param  pQObject - 
\param  pQEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecordTest"

logical OWidget :: RecordTest (QObject *pQObject, QEvent *pQEvent )
{
  logical                 term = NO;
BEGINSEQ
  QFile         f( SZ2QS("events.rec") );
  QTextStream   stream(&f);
  QString       data;
  QTextStream   sdata(&data,QIODevice::WriteOnly);
  
  /* create data from eventtype */
  switch(pQEvent->type()){
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
      /* mouseevent */
      sdata << "mouse|type:" << pQEvent->type();
      sdata << "|x:"         << ((QMouseEvent*)pQEvent)->x();
      sdata << "|y:"         << ((QMouseEvent*)pQEvent)->y();
      sdata << "|button:"    << ((QMouseEvent*)pQEvent)->button();
      sdata << "|state:"     << ((QMouseEvent*)pQEvent)->modifiers();
      break;
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
      /* mouseevent */
      sdata << "key|type:" << pQEvent->type();
      sdata << "|key:"     << ((QKeyEvent*)pQEvent)->key();
      sdata << "|text:"    << ((QKeyEvent*)pQEvent)->text();
      sdata << "|state:"   << ((QKeyEvent*)pQEvent)->modifiers();
      break;
    case QEvent::Shortcut:
    case QEvent::ContextMenu:
      sdata << "other|type:" << pQEvent->type();
      break;
    default:
      LEAVESEQ
  }
  /* write event to file */
  if ( !f.open( QIODevice::WriteOnly | QIODevice::Append ) )
                                                     ERROR
  stream << QS2SZ(data);  
  stream << "|obj:" << pQObject->metaObject()->className();
  stream << "|name:" << pQObject->objectName();
  if(pQObject->parent()){
    stream << "|pobj:"<< pQObject->parent()->metaObject()->className();
    stream << "|pname:" << pQObject->parent()->objectName();
  }
  stream << endl;
  f.close();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetBackgroundColor - set background color

        Sets the Background Color of the Widget.
        Argument.
        Returns the new Position as GetPosition would do.


\param  rDColor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBackgroundColor"

void OWidget :: SetBackgroundColor (DColor &rDColor )
{
  QWidget       *qwidget = this ? WidgetQ() : NULL;
  QPalette       palette;

  if ( qwidget && rDColor.IsValid() )
  {
    palette.setColor(qwidget->backgroundRole(),DCOLOR2QCOLOR(rDColor));
    qwidget->setPalette(palette);  
  }



}

/******************************************************************************/
/**
\brief  SetEnabled - 




\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEnabled"

void OWidget :: SetEnabled (logical fEnabled )
{

  enabled = fEnabled;

  UpdateEnabled();

}

/******************************************************************************/
/**
\brief  SetFocus - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFocus"

logical OWidget :: SetFocus ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  logical     term    = NO;
BEGINSEQ
  if ( !qwidget )                                  ERROR
  
  qwidget->setFocus();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetFont - set font

        Sets the Font Object of the Widget.


\param  rDFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void OWidget :: SetFont (DFont &rDFont )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  OFont       ofont(rDFont);
  if ( qwidget )
  {
    qwidget->setFont(ofont);
    SetTextColor(rDFont.get_text_color());
    SetBackgroundColor(rDFont.get_bg_color());
  }



}

/******************************************************************************/
/**
\brief  SetPosition - set position

        Set the Position of the Widget relativ to its Parent.

-------------------------------------------------------------------------------
\brief  i00 - 



\param  rcDPoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void OWidget :: SetPosition (const DPoint &rcDPoint )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  if ( qwidget )
    qwidget->move(DPOINT2QPOINT(rcDPoint));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  x - 
\param  y - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

void OWidget :: SetPosition (int x, int y )
{

SetPosition(DPoint(x,y));

}

/******************************************************************************/
/**
\brief  SetReadOnly - Set Control to read-only state

        The  control is  set into  the read-only  state, which shows the control
        with  a disabled lable  and which does  not allow entering data into the
        control.  Context  menu  and  actions  for the control are still active.
        Passinf  true  (YES)  to  the  function will enable the read-only state,
        passing false (NO) will disable the read-only state.


\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OWidget :: SetReadOnly (logical fReadOnly )
{

  UpdateReadOnly(readOnly = fReadOnly);

}

/******************************************************************************/
/**
\brief  SetSize - set size

        Sets the Size of the Widget.

-------------------------------------------------------------------------------
\brief  i00 - 



\param  rcDSize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void OWidget :: SetSize (const DSize &rcDSize )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  if ( qwidget && rcDSize.IsValid() )
    qwidget->resize(DSIZE2QSIZE(rcDSize));

}

/******************************************************************************/
/**
\brief  i01 - 



\param  x - 
\param  y - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void OWidget :: SetSize (int x, int y )
{

  SetSize(DSize(x,y));

}

/******************************************************************************/
/**
\brief  SetTextColor - 




\param  rDColor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

void OWidget :: SetTextColor (DColor &rDColor )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  QPalette    palette;
  if ( qwidget && rDColor.IsValid() )
  {
    palette.setColor(qwidget->foregroundRole(),DCOLOR2QCOLOR(rDColor));
    qwidget->setPalette(palette);  
  }



}

/******************************************************************************/
/**
\brief  SetToggleMode - 




\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetToggleMode"

void OWidget :: SetToggleMode (logical fEnabled )
{



}

/******************************************************************************/
/**
\brief  SetVisible - 




\param  fEnabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVisible"

void OWidget :: SetVisible (logical fEnabled )
{

  visible = fEnabled;



}

/******************************************************************************/
/**
\brief  SetWidgetBusy - 



\return term - 

\param  toggle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWidgetBusy"

logical OWidget :: SetWidgetBusy (bool toggle )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
  logical     term    = NO;
BEGINSEQ
  if ( !qwidget )                                    ERROR
    
  if ( toggle )
    qwidget->setCursor(Qt::BusyCursor);
  else
    qwidget->unsetCursor();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateEnabled - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateEnabled"

void OWidget :: UpdateEnabled ( )
{
  QWidget    *qwidget = this ? WidgetQ() : NULL;
BEGINSEQ
  if ( !qwidget )                                    ERROR
    
  if ( in_design_mode )
    qwidget->setEnabled(enabled);
  else
    qwidget->setEnabled(enabled && getEnabled());

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  UpdateReadOnly - 




\param  fReadOnly - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateReadOnly"

void OWidget :: UpdateReadOnly (logical fReadOnly )
{



}

/******************************************************************************/
/**
\brief  UpdateState - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateState"

void OWidget :: UpdateState ( )
{

  UpdateEnabled();
  UpdateReadOnly(readOnly);

}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OWidget :: WidgetQ ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  getEnabled - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OWidget :: getEnabled ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ~OWidget - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWidget"

     OWidget :: ~OWidget ( )
{

  delete design_mode;
  design_mode = NULL;

widg_count--;
}


