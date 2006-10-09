/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OItemDelegate

\brief    


\date     $Date: 2006/08/23 21:29:13,09 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OItemDelegate_HPP
#define   OItemDelegate_HPP

class     OItemDelegate;

class     OEHDataWidget;
class     OListCtl;
#include  <sQModelIndex.hpp>
class  OItemDelegate :public QItemDelegate
{
protected  :         OListCtl                                    *list_control;                                              // 

public     :
                     OListCtl                                    *get_list_control() { return(list_control); }
public     :                                        logical IsCheckColumn (const QModelIndex &model_index ) const;
public     :                                             OItemDelegate (OListCtl *pOListCtl );
public     : virtual                                QWidget *createEditor (QWidget *pqwParent, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const;
public     : virtual                                void paint (QPainter *pQPainter, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const;
public     : virtual                                void setModelData (QWidget *pQWidget, QAbstractItemModel *pQAbstractItemModel, const QModelIndex &model_index ) const;
public     :                                        void updateEditorGeometry (QWidget *pQWidget, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &crQModelIndex );
public     : virtual                                     ~OItemDelegate ( );
};

#endif
