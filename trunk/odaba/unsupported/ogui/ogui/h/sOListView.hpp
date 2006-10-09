/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OListView

\brief    


\date     $Date: 2006/08/01 13:35:56,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OListView_HPP
#define   OListView_HPP

class     OListView;

class     ODS;
class     ODataWidget;
#include  <sOListCtl.hpp>
#include  <sQModelIndex.hpp>
class  OListView :public QListView,
public OListCtl
{
protected  :                                                      Q_OBJECT;                                                  // 

public     :
public     : virtual                                logical Activate ( );
public     : virtual                                logical Deactivate (logical data_only=NO );
public     : virtual                                QFrame *FrameQ ( );
public     :                                        void Initialize (logical multi_sel, int8 sort_order=0, logical check_items=NO );
public     : virtual                                QAbstractItemView *ItemViewQ ( );
public     :                                             OListView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical multi_sel_w=NO, int8 sort_order=0, logical check_items=NO );
public     :                                             OListView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical multi_sel_w=NO, int8 sort_order=0, logical check_items=NO );
public     : signals:                               void OnCurrentRowChanged (ItemData *pItemData );
public     : virtual                                void SetSpacing (int16 inner_dist );
public     : virtual                                QWidget *WidgetQ ( );
public     : public slots:                          void currentChanged (const QModelIndex &qt_current, const QModelIndex &qt_previous );
public     : virtual                                bool eventFilter (QObject *pQObject, QEvent *pQEvent );
public     :                                             ~OListView ( );
};

#endif
