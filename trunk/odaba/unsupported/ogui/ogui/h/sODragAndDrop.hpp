/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODragAndDrop

\brief    ODragAndDrop enables Objects to handle Drag and drop
          Encapsulates QT DnD events to simple functions

\date     $Date: 2006/06/14 13:40:46,21 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODragAndDrop_HPP
#define   ODragAndDrop_HPP

class     ODragAndDrop;

class     DatabaseHandle;
class     DictionaryHandle;
class     ODragObject;
class     OEHDataWidget;
#include  <cDragAndDropActions.h>
#include  <cDragAndDropTypes.h>
#include  <sDPoint.hpp>
#include  <sPropertyHandle.hpp>
class  ODragAndDrop
{
protected  :         OEHDataWidget                               *oeh_widget;                                                // 
protected  :         DatabaseHandle                              *decoded_dbhandle;                                          // 
protected  :         DictionaryHandle                            *decoded_dictionaryhandle;                                  // 
protected  :         PropertyHandle                              *decoded_propertyhandle;                                    // 
protected  :         QString                                      decoded_text;                                              // 
protected  :         Qt::DropAction                               drop_action;                                               // 
protected  :         logical                                      drop_islocal;                                              // 
protected  :         int32                                        drop_index;                                                // 
protected  :         QPoint                                       drop_point;                                                // 
protected  :         QWidget                                     *pQDropSource;                                              // 
protected  :         int32                                        drop_type;                                                 // 
protected  :         QTime                                        qtDropStart;                                               // 
protected  :         QDropEvent                                  *drop_event;                                                // 

public     :
                     OEHDataWidget                               *get_oeh_widget() { return(oeh_widget); }
                     PropertyHandle                              *get_decoded_propertyhandle() { return(decoded_propertyhandle); }
                     QString                                     &get_decoded_text() { return(decoded_text); }
                     Qt::DropAction                              &get_drop_action() { return(drop_action); }
                     logical                                      get_drop_islocal() { return(drop_islocal); }
                     int32                                        get_drop_index() { return(drop_index); }
                     QPoint                                      &get_drop_point() { return(drop_point); }
                     QWidget                                     *get_pQDropSource() { return(pQDropSource); }
                     QDropEvent                                  *get_drop_event() { return(drop_event); }
public     : virtual                                char *GetNewKey (PropertyHandle *ph, char *text1, char *text2 );
public     :                                        logical IsLocalDrop (QWidget *pQWidget );
public     :                  OGUIImpExp                 ODragAndDrop ( );
public     :                                        logical UpdateDropType ( );
public     :                                        int dnd_allow (PropertyHandle *pphTarget );
public     : virtual                                logical dnd_can_decode (const QMimeData *pQMimeData );
public     :                                        logical dnd_copy (PropertyHandle *pphTarget, PropertyHandle *pphSource, int iPos );
public     : virtual          OGUIImpExp            logical dnd_drag_init ( );
public     : virtual          OGUIImpExp            logical dnd_drop ( );
public     : virtual          OGUIImpExp            logical dnd_drop_end ( );
public     : virtual          OGUIImpExp            logical dnd_drop_init ( );
public     : virtual          OGUIImpExp            logical dnd_drop_move ( );
public     :                                        logical dnd_drop_propertyhandle (PropertyHandle *pPropertyHandle );
public     :                                        logical dnd_link (PropertyHandle *pphTarget, PropertyHandle *pphSource, int iPos );
public     :                                        logical dnd_move (PropertyHandle *pphTarget, PropertyHandle *pphSource, int iPos );
protected  : static                                 logical __cdecl dnd_test (PropertyHandle *pphTarget, PropertyHandle *pphSource );
public     :                                        logical dragEnterEvent (QDragEnterEvent *pQDragEnterEvent );
public     :                                        logical dragEvent ( );
public     :                                        logical dragLeaveEvent (QDragLeaveEvent *pQDragLeaveEvent );
public     :                                        logical dragMoveEvent (QDragMoveEvent *pQDragMoveEvent );
public     : virtual                                QDrag *dragObject ( );
public     :                                        logical dropEvent (QDropEvent *pQDropEvent );
public     :                                        logical xxdnd_drop_pos_after (DPoint point, const QRect &rcQRect );
public     :                                        logical xxdnd_drop_pos_after (const QRect &rcQRect );
};

#endif
