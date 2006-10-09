#ifndef __CoaAbstractItemModel_h__
#define __CoaAbstractItemModel_h__
#include <QAbstractItemModel>

#include <CoaSet>

class CoaMainWindow;

class CoaAbstractItemModel: public QAbstractItemModel {
Q_OBJECT
public:
   CoaAbstractItemModel(QObject *parent=0);
   virtual ~CoaAbstractItemModel();
   virtual bool saveChanges() = 0;

   void addMasterWindow(QObject *const window);
   void remMasterWindow(QObject *const window);

   void setContentDirty(const bool flag=true);


   virtual QModelIndex index(int row, int column, const QModelIndex &parent) const = 0;

   /**
   @brief Return the parent for a given QModelIndex.

   A common implementation looks like

   @code
   QModelIndex FooModel::parent(const QModelIndex &child) const
   {
      if (!child.isValid())   return QModelIndex(); //check parameter
      ModelItem *childItem =  static_cast<ModelItem*>(index.internalPointer()); //get a pointer to the matching tree item
      ModelItem *parentItem = static_cast<ModelItem*>(childItem->parent()); //get a pointer to the parent

      if (parentItem == rootItem) return QModelIndex(); //root has no parents
      return createIndex(parentItem->row(), 0, parentItem); //create a ModelIndex for the parent
   }
   @endcode

   */
   virtual QModelIndex parent(const QModelIndex &child) const = 0;


signals:
   void allDataChanged();


private:
   CoaSet <QObject*>   m_masterSet;

};
#endif
