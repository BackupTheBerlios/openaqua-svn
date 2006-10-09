#include "coachangedebug_model.h"
#include <CoaDebug>

#include <CoaAction>
#include <CoaApplication>
#include <CoaDebugThread>

#include <CoaIoStream>
#include <iostream>

#include <QItemSelectionModel>



CoaDebugSettingsModel::CoaDebugSettingsModel ( QObject *parent )
:CoaAbstractItemModel ( parent )
{
//   BEGIN;


   m_columns = 2;

   loadFileList();

   connect (CoaDebugThread::getInstance(), SIGNAL(gotNewFileForDebugging(const QString, const int)),
            this, SLOT (setNewFile(const QString, const int)),
            Qt::QueuedConnection
            );

}


CoaDebugSettingsModel::~CoaDebugSettingsModel ()
{
//   BEGIN;
}


int CoaDebugSettingsModel::rowCount ( const QModelIndex & parent ) const
{
   Q_UNUSED(parent);
   return m_files.count();
}




int CoaDebugSettingsModel::columnCount ( const QModelIndex & parent ) const
{
   Q_UNUSED(parent);
   return m_columns;
}




QVariant CoaDebugSettingsModel::data ( const QModelIndex & index, int role ) const
{
   //Check
   if (!index.isValid())                  return QVariant();
   if (index.row() < 0)                   return QVariant();
   if (index.column() < 0)                return QVariant();
   if (index.model() != this)             return QVariant();

   if (index.column() >= 2) return QVariant();
   if (index.row() >= m_files.count()) return QVariant();

   QPair<QString, CoaDebug::DebugLevel> pair = m_files.at(index.row());


   if (role == Qt::DisplayRole){
      if (index.column() == 0) return pair.first;
      if (index.column() == 1) return CoaDebug::mapLevelToString(pair.second);
      return QVariant();


   }else  if (role == Qt::ToolTipRole){
      if (index.column() == 0) return pair.first;
      if (index.column() == 1) return CoaDebug::mapLevelToString(pair.second);
      return QVariant();


   }else  if (role == Qt::StatusTipRole){
      if (index.column() == 0) return pair.first;
      if (index.column() == 1) return CoaDebug::mapLevelToString(pair.second);
      return QVariant();


   }else  if (role == Qt::WhatsThisRole){
      if (index.column() == 0) return pair.first;
      if (index.column() == 1) return CoaDebug::mapLevelToString(pair.second);
      return QVariant();


   //React on Edit Role
   }else  if (role == Qt::EditRole){
      if (index.column() == 1)  return pair.second;
      return QVariant();
   }

   //Default
   return QVariant();
}




bool CoaDebugSettingsModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
   BEGIN;

   //Some checks
   //Check
   if (role != Qt::EditRole)           RETURN(false);
   if (!index.isValid())               RETURN(false);
   if (index.row() < 0)                RETURN(false);
   if (index.column() != 1)            RETURN(false);
   if (index.row() >= m_files.count()) RETURN(false);


   //Match strings to a debug level
   CoaDebug::DebugLevel level = CoaDebug::mapIntToLevel(value.toInt());

   //Get the filename
   QPair<QString, CoaDebug::DebugLevel> pair = m_files.at(index.row());
   QString  file  = pair.first;

   //Inform the debug threads
   CoaDebug::getInstance()->setDebugLevelForFile(file, level);

   //change data
   m_files.replace(index.row(), qMakePair(file, level));

   //Inform other objects about changes
   emit dataChanged(index, index);

   //Bye bye
   RETURN(true);
}


bool CoaDebugSettingsModel::saveChanges()
{
  BEGIN;
  bool result=false;
  RETURN(result);
}



Qt::ItemFlags CoaDebugSettingsModel::flags ( const QModelIndex & index ) const
{
   if (!index.isValid())
      return Qt::ItemIsEnabled| Qt::ItemIsSelectable;

   if (index.column() == 1) {
      return QAbstractItemModel::flags(index) | Qt::ItemIsEditable| Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
   } else {
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;;
   }
}




QModelIndex CoaDebugSettingsModel::index(int row, int column, const QModelIndex &parent) const
{
   Q_UNUSED(parent);

   //Check
   if (row    < 0 )         return QModelIndex();
   if (column < 0 )         return QModelIndex();
   if (column >= m_columns) return QModelIndex();

   return createIndex(row, column, -1);
}



/**

*/
QModelIndex CoaDebugSettingsModel::parent(const QModelIndex &index) const
{
   Q_UNUSED(index);
   return QModelIndex();
}





bool CoaDebugSettingsModel::hasChildren ( const QModelIndex & index) const {
   Q_UNUSED(index);
   return false;
}




/**

Method returns nothing. Except it is a DisplayRole.
*/
QVariant CoaDebugSettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   //BEGIN;

   //Check the Role
   if (role != Qt::DisplayRole) {
      return QVariant();
   }


   if (orientation == Qt::Horizontal) {
      //Give Name Columns
      switch(section){
         case 0: return QVariant(tr("File"));
         case 1: return QVariant(tr("Level"));
      }
   }

   return QVariant();
}




///////////////////////////////////////////////////////////////////////////
void CoaDebugSettingsModel::setNewFile(const QString file, const int l)
{
   BEGIN;
   CoaDebug::DebugLevel level = CoaDebug::mapIntToLevel(l);
   QPair<QString, CoaDebug::DebugLevel> pair(file, level);
   if (m_files.indexOf(pair) == -1) {
      m_files.append(pair);
      qSort(m_files.begin(), m_files.end());
      reset();
      emit allDataChanged();
   }

}




///////////////////////////////////////////////////////////////////////////
void CoaDebugSettingsModel::loadFileList()
{
   BEGIN
   m_files.clear();

   //Get a list from all files
   QMap<QString, CoaDebug::DebugLevel> files = CoaDebugThread::getInstance()->getKnownFiles();

   //make QList with a pair<file, level>
   QMap<QString, CoaDebug::DebugLevel>::const_iterator i = files.constBegin();
   while (i != files.constEnd()) {
      //INF(QString("DebugLevel <%1>: %2").arg(i.key()).arg(i.value()));
      m_files.append(qMakePair(i.key(), i.value()));
      ++i;
   }

}


///////////////////////////////////////////////////////////////////////////
void CoaDebugSettingsModel::setDefault(const QModelIndexList& list)
{
   BEGIN;

   QModelIndex index;
   foreach(index, list) {
      setData(index, CoaDebug::DEFAULT, Qt::EditRole);
   }

}

