#include "travelmainwindowmodel.h"

#include <CoaDebug>

TravelMainWindowModel::TravelMainWindowModel(QObject *parent)
: CoaAbstractItemModel(parent)
{
   BEGIN;
}


TravelMainWindowModel::~TravelMainWindowModel()
{
   BEGIN;
}
   



   //Item access
QModelIndex TravelMainWindowModel::index(int row, int column, const QModelIndex &parent) const
{
   return QModelIndex();
}


QModelIndex TravelMainWindowModel::parent(const QModelIndex &child) const
{
   return QModelIndex();
}


bool TravelMainWindowModel::hasChildren ( const QModelIndex & parent) const
{
   return false;
}



   //Reading
int TravelMainWindowModel::rowCount ( const QModelIndex & parent ) const
{
   return 10;
}

int TravelMainWindowModel::columnCount ( const QModelIndex & parent ) const
{
   return 8;
}

QVariant TravelMainWindowModel::data ( const QModelIndex & index, int role ) const
{
   return QVariant();
}



QVariant TravelMainWindowModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   //Check the Role
   if (role != Qt::DisplayRole) {
      return QVariant();
   }


   if (orientation == Qt::Horizontal) {
      //Give Name Columns
      switch(section){
         case 0: return QVariant(tr("Private"));

         case 1: return QVariant(tr("Start"));
         case 2: return QVariant(tr("Mileage"));

         case 3: return QVariant(tr("End"));
         case 4: return QVariant(tr("Mileage"));

         case 5: return QVariant(tr("Driver"));
         case 6: return QVariant(tr("Co-Driver"));
         case 7: return QVariant(tr("Description"));

      }
   }

   return QVariant();
}



   
   //Editing
bool TravelMainWindowModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
   return false;
}




Qt::ItemFlags TravelMainWindowModel::flags ( const QModelIndex & index ) const
{
   return 0;
}


bool TravelMainWindowModel::saveChanges()
{
   BEGIN;
   return false;
}

