/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODelegate

\brief    Delegate for view and edit modelitems
          this  class is used  to manipulate the  default behaviour of the items
          in a list or a table

\date     $Date: 2006/03/13 21:34:05,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODelegate_HPP
#define   ODelegate_HPP

class     ODelegate;

class     ODS;
class     ODSList;
class     ODataWidget;
class     PropertyHandle;
class  ODelegate :public QItemDelegate
{
protected  :         QRect                                        rData;                                                     //
protected  :         QRect                                        rIcon;                                                     //
protected  :         QRect                                        rDecoration;                                               //

public     :
public     :                                     logical CheckBox (QWidget *pQWidget, const QModelIndex &model_index, const QStyleOptionViewItem &crQStyleOptionViewItem ) const;
public     :                                     logical ComboBox (QPainter *pQPainter, const QStyleOptionViewItem &crQStyleOptionViewItem );
protected  :                                     ODSList *GetODS (const QModelIndex &model_index ) const;
protected  :                                     std_string GetType (ODSList *pODSList ) const;
protected  :                                     ODataWidget *GetWidget (ODSList *pODSList, QWidget *pQWidget ) const;
protected  :                                     ODataWidget *GetWidget (const QModelIndex &model_index, QWidget *pQWidget ) const;
public     :         OGUI7ImpExp                                         ODelegate (QObject *pQObject );
public     :                                     QWidget *createEditor (QWidget *pQWidget, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const;
public     :                                     void setEditorData (QWidget *pQWidget, const QModelIndex &model_index ) const;
public     :                                     void setModelData (QWidget *pQWidget, QAbstractItemModel *pQAbstractItemModel, const QModelIndex &model_index ) const;
public     :                                     void updateEditorGeometry (QWidget *pQWidget, const QStyleOptionViewItem &crQStyleOptionViewItem, const QModelIndex &model_index ) const;
};

#endif
