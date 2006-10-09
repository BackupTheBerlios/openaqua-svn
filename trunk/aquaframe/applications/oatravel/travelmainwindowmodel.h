#ifndef __TravelMainWindowModel_h__
#define __TravelMainWindowModel_h__


#include <CoaAbstractItemModel>

class TravelMainWindowModel: public CoaAbstractItemModel
{
public:
   TravelMainWindowModel(QObject *parent=0);
   //!destructor
   virtual ~TravelMainWindowModel();

   //Item access
   QModelIndex index(int row, int column, const QModelIndex &parent) const;
   QModelIndex parent(const QModelIndex &child) const;
   virtual bool hasChildren ( const QModelIndex & parent) const;

   //Reading
   virtual int rowCount ( const QModelIndex & parent ) const;
   virtual int columnCount ( const QModelIndex & parent ) const;
   virtual QVariant data ( const QModelIndex & index, int role ) const;
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

   //Editing
   virtual bool setData ( const QModelIndex & index, const QVariant & value, int role );
   virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
   virtual bool saveChanges();
};

#endif //__TravelMainWindowModel_h__


