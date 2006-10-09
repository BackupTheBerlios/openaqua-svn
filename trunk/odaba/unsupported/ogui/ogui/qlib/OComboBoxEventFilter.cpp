/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OComboBoxEventFilter

\brief    


\date     $Date: 2006/07/05 21:07:24,37 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OComboBoxEventFilter"

#include  <pogui7.h>
#include  <sOComboBox.hpp>
#include  <sOListView.hpp>
#include  <sOComboBoxEventFilter.hpp>


/******************************************************************************/
/**
\brief  OComboBoxEventFilter - 




\param  pOComboBox - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OComboBoxEventFilter"

     OComboBoxEventFilter :: OComboBoxEventFilter (OComboBox *pOComboBox )
                     : QObject (),
  cbox(pOComboBox),
  hadfocus(NO)
{



}

/******************************************************************************/
/**
\brief  eventFilter - 



\return vbool - 

\param  watched - 
\param  pQEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eventFilter"

bool OComboBoxEventFilter :: eventFilter (QObject *watched, QEvent *pQEvent )
{

  if ( watched && pQEvent )
  {
    switch ( pQEvent->type() )
    {
      case QEvent::ChildAdded:
          // j 060330: very often on the same object
          //if ( cbox->lineEdit() ) 
          //  cbox->lineEdit()->installEventFilter(this);
          //cbox->get_listbox()->installEventFilter(this);
          break;
        
      case QEvent::FocusIn:
          if ( !hadfocus )
          {
            hadfocus = YES;   
            if ( watched != cbox ) 
              QApplication::sendEvent(cbox,pQEvent);
          }
          break;
        
      case QEvent::FocusOut:
          if ( hadfocus && !( cbox->get_listbox()->isVisible() ) )
          {
            hadfocus = NO;
            if ( watched != cbox ) 
              QApplication::sendEvent(cbox,pQEvent);
          }
          break;
        
      case QEvent::Hide:
          if ( hadfocus && watched == cbox->get_listbox() && !cbox->hasFocus() )
          {
            hadfocus = NO;
            QFocusEvent fo(QEvent::FocusOut);
            QApplication::sendEvent(cbox,&fo);
          }
          break;
      case QEvent::EnabledChange:
          if ( watched != cbox ) 
              QApplication::sendEvent(cbox,pQEvent);
          break;
      case QEvent::Show:
          if (watched == cbox->get_listbox())
          {
			QWidget* popup = 0;
			QObjectList objects = cbox->children();
			for(int i = 0; i < objects.size(); ++i)
			{
				QObject* obj = objects.at(i);
				if(obj->inherits("QComboBoxPrivateContainer")){
					popup = qobject_cast<QWidget*>(obj);
		            QRect  csize = cbox->get_listbox()->geometry();
	                popup->resize(csize.width()<120?120:csize.width()
	                             ,csize.height()<100?100:csize.height());

				    break;
				}
            }
          }
    }
  }

  return QObject::eventFilter(watched,pQEvent);
}

/******************************************************************************/
/**
\brief  ~OComboBoxEventFilter - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OComboBoxEventFilter"

     OComboBoxEventFilter :: ~OComboBoxEventFilter ( )
{



}


