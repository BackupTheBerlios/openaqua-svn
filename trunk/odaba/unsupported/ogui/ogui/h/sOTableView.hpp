/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OTableView

\brief    TableView
          class provides a model/view implementation of a table view
          "

\date     $Date: 2006/05/24 14:12:52,34 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTableView_HPP
#define   OTableView_HPP

class     OTableView;

class     ItemData;
class     ODS;
class     ODataWidget;
#include  <sOListCtl.hpp>
#include  <sQModelIndex.hpp>
class  OTableView :public QTableView,
public OListCtl
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         OSettings                                    settings;                                                  // 
protected  :         int32                                        iScrollY;                                                  // 

public     :
                     OSettings                                   &get_settings() { return(settings); }
                     int32                                        get_iScrollY() { return(iScrollY); }
public     :                  OGUIImpExp            logical Activate ( );
public     :                  OGUIImpExp            logical Deactivate (logical data_only=NO );
public     :                                        int8 FocusOutEvent ( );
public     : virtual                                QFrame *FrameQ ( );
public     : virtual                                OHeaderView *Header ( );
public     :                                        void Initialize (logical multi_sel, logical transposed );
public     : virtual                                QAbstractItemView *ItemViewQ ( );
public     : virtual                                void ListChanged (logical chk_visible );
public     :                  OGUIImpExp                 OTableView (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical multi_sel_w=NO, logical transpose_w=NO );
public     : public slots:                          void OnCurrentRowChanged (ItemData *pItemData );
public     : virtual                                QWidget *WidgetQ ( );
public     : public slots:                          void currentChanged (const QModelIndex &qt_current, const QModelIndex &qt_previous );
public     :                                        void scrollRestore ( );
public     :                                        void scrollStore ( );
public     :                                             ~OTableView ( );
};

#endif
