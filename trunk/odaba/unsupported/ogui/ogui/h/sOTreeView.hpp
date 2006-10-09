/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OTreeView

\brief    


\date     $Date: 2006/08/22 17:42:06,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTreeView_HPP
#define   OTreeView_HPP

class     OTreeView;

class     DBObjectHandle;
class     ItemData;
class     ODS;
class     ODSRegion;
class     OHeaderView;
class     QAbstractItemView;
#include  <sDPoint.hpp>
#include  <sODataWidget.hpp>
#include  <sOListCtl.hpp>
#include  <sQModelIndex.hpp>
class  OTreeView :public QTreeView,
public OListCtl
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         QString                                      inputbuffer_s;                                             // 
protected  :         int                                          dnd_scroll_timer_id;                                       // 
protected  :         int                                          dnd_scroll_timer_direction;                                // 
protected  :         int                                          dnd_expand_timer_id;                                       // 
protected  :         QModelIndex                                  dnd_expand_timer_index;                                    // 
protected  :         int                                          input_timer_id;                                            // 
protected  :         ItemData                                    *inputitem;                                                 // 
protected  :         QLabel                                      *inputtip;                                                  // 
protected  :         QRect                                        lastinputitemrect;                                         // 

public     :
                     QRect                                       &get_lastinputitemrect() { return(lastinputitemrect); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     :                                        logical AutoExpand (const QModelIndex &model_index );
public     :                                        logical AutoScroll (const QModelIndex &model_index );
public     : virtual                                logical Deactivate (logical data_only=NO );
public     : virtual                                logical ExpandIndex (const QModelIndex &model_index );
public     : virtual                                QFrame *FrameQ ( );
public     : virtual                                OHeaderView *Header ( );
public     :                                        void Initialize (logical multi_sel, int8 sort_order=0, logical tree_opt=YES, logical check_items=NO );
public     :                                        logical InputHide ( );
protected  :                                        QRect InputItemRect ( );
public     :                                        logical InputScroll (const QString &qscText );
public     :                                        logical InputShow (const QString &qscText );
public     :                                        logical InputUpdate (const QString &qscText );
public     :                                        logical InputUpdate (int count );
public     : virtual                                logical IsItemExpanded (ItemData *pItemData );
public     : virtual                                QAbstractItemView *ItemViewQ ( );
public     : virtual                                ItemData *NextItem (ItemData *pItemData );
public     :                  OGUIImpExp                 OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical multi_sel_w=NO, int8 sort_order=0, logical tree_opt=YES, logical check_items=NO );
public     :                  OGUIImpExp                 OTreeView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical multi_sel_w=NO, int8 sort_order=0, logical tree_opt=YES, logical check_items=NO );
public     : public slots:                          void OnCurrentRowChanged (ItemData *pItemData );
public     : virtual                                ItemData *PreviousItem (ItemData *pItemData );
public     :                                        logical Scroll (int32 iDirection );
public     : virtual                                QWidget *WidgetQ ( );
public     : public slots:                          void currentChanged (const QModelIndex &qt_current, const QModelIndex &qt_previous );
public     : virtual          OGUIImpExp            logical dnd_drop ( );
public     :                                        logical dnd_drop_end ( );
public     :                                        logical dnd_drop_move ( );
public     :                                        bool eventFilter (QObject *pQObject, QEvent *pQEvent );
public     :                                        void paintEvent (QPaintEvent *pQPaintEvent );
public     : public slots:                          void rowsAboutToBeRemoved (const QModelIndex &mi_parent, int start_index, int end_index );
public     : public slots:                          void slotItemCollapsed (const QModelIndex &model_index );
public     : public slots:                          void slotItemExpanded (const QModelIndex &model_index );
protected  :                                        void timerEvent (QTimerEvent *pQTimerEvent );
public     :                                             ~OTreeView ( );
};

#endif
