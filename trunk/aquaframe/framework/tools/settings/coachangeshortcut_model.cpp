#include "coachangeshortcut_model.h"
#include <CoaDebug>
#include <cassert>
#include <CoaAction>
#include <CoaApplication>
#include <CoaActionFactory>


#include <QKeySequence>
#include <CoaIoStream>
#include <iostream>
#include <QItemSelectionModel>

using namespace std;


CoaActionViewModel::CoaActionViewModel ( QObject *parent )
:QAbstractItemModel ( parent )
{
   BEGIN;


   const QList<int> actionsList = CoaActionFactory::getInstance()->getActionsList();
   m_rows = actionsList.count();

   m_columns = 3;
   m_blocks.clear();
   m_actions.clear();


   //Get the ActionBlocks
   foreach (int iAction, actionsList) {
      CoaAction *action = GETACTION(iAction);
      CoaApplication::processEvents();

      QString block = action->actionBlock();
      QMap<QString, QList<CoaAction*>*>::iterator j;
      j = m_actions.find(block);
      if (j == m_actions.end()) {

         //New Block found
         //add the block plus the action to m_actions
         ++m_rows;
         QList<CoaAction*> *list = new QList<CoaAction*>;
         *list << action;
         m_actions.insert(block, list);
         //add the block the m_blocks
         m_blocks << block;
      } else {
         QList<CoaAction*> *list = *j;
         *list << action;
      }
   }

   //Sort the stuff
   qSort(m_blocks.begin(), m_blocks.end());
   foreach (QList<CoaAction*> *list, m_actions){
      qSort(list->begin(), list->end(), CoaAction::compareActionsOnText);
   }


}


CoaActionViewModel::~CoaActionViewModel ()
{
   BEGIN;
   QList<QList<CoaAction*>*> allLists;
   allLists = m_actions.values();
   m_actions.clear();
   while(!allLists.isEmpty()) {
        delete allLists.takeLast();
   }
}


int CoaActionViewModel::rowCount ( const QModelIndex & parent ) const
{
   Q_UNUSED(parent);
   return m_rows;
}




int CoaActionViewModel::columnCount ( const QModelIndex & parent ) const
{
   Q_UNUSED(parent);
   return m_columns;
}




QVariant CoaActionViewModel::data ( const QModelIndex & index, int role ) const
{

   //Check
   if (!index.isValid())                  return QVariant();
   if (index.row() < 0)                   return QVariant();
   if (index.column() < 0)                return QVariant();

   //React on Roles
   if (role == Qt::DisplayRole){
      if (index.parent().isValid()){
         CoaAction* action = mapIndexToAction(index);
         if (action == 0)     return QVariant();
         switch (index.column()) {
            case 0:           return action->pureText();
            case 1:           return action->toolTip();
            case 2:           {
                                 QMap<CoaAction*, QKeySequence>::const_iterator j;
                                 j = m_changes.find(action);
                                 if (j == m_changes.end()) {
                                    return action->shortcut();
                                 } else {
                                    return m_changes.value(action);
                                 }
                              }
            default:          return QVariant();
         }
      } else {
         //Is a Block
         if (index.column()!=0)  return QVariant();
         if (index.row() < 0  )  return QVariant();
         if (index.row() >= m_blocks.count()) return QVariant();
         return m_blocks.at(index.row());
      }

   //React on Edit Role
   }else  if (role == Qt::EditRole){
      if (index.parent().isValid()){
         CoaAction* action = mapIndexToAction(index);
         if (action == 0)     return QVariant();
         if (index.column() == 2) {
            QMap<CoaAction*, QKeySequence>::const_iterator j;
            j = m_changes.find(action);
            if (j == m_changes.end()) {
               QKeySequence seq = action->shortcut();
               QString str = seq;
               return str;
            } else {
               QKeySequence seq = m_changes.value(action);
               QString str = seq;
               return str;
            }
         }
      }
   }

   //Default
   return QVariant();
}


bool CoaActionViewModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
   BEGIN;


   //Some checks
   if (role != Qt::EditRole)      RETURN(false);
   if (!index.isValid())          RETURN(false);
   if (index.internalId() == -1)  RETURN(false);
   if (index.column() != 2)       RETURN(false);


   //get and check the KeySequence
   QKeySequence sequence(value.toString());
   if (!value.toString().isEmpty()){
      if (!sequence) {
         WRN(QString("Got bad QKeySequence <%1>").arg(value.toString()));
         RETURN(false);
      }
   }

   //Store the changes
   CoaAction *action = mapIndexToAction(index);
   if (action == 0)               RETURN(false);
   m_changes[action] = sequence;

   //Inform other objects about changes
   emit dataChanged(index, index);
   emit haveUnsavedShortcuts(true);

   //Bye bye
   RETURN(true);

}


CoaAction*  CoaActionViewModel::mapIndexToAction(const QModelIndex& index) const
{

   if (!index.isValid())          return 0;
   if (!index.parent().isValid()) return 0;
   if (index.row() < 0  )         return 0;
   if (index.column()<0)          return 0;
   if (index.internalId()==-1)    return 0;
   if (index.column()>=m_columns) return 0;

   QString block = m_blocks.at(index.parent().row());
   QList<CoaAction*> *list = m_actions.value(block);

   if (index.row() >= list->count())  return 0;
   return list->at(index.row());

}


Qt::ItemFlags CoaActionViewModel::flags ( const QModelIndex & index ) const
{
   if (!index.isValid())
      return Qt::ItemIsEnabled| Qt::ItemIsSelectable;

   if (index.column() == 2) {
      return QAbstractItemModel::flags(index) | Qt::ItemIsEditable| Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
   } else {
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;;
   }
}




QModelIndex CoaActionViewModel::index(int row, int column, const QModelIndex &parent) const
{

   //Check
   if (row    < 0 )         return QModelIndex();
   if (column < 0 )         return QModelIndex();
   if (column >= m_columns) return QModelIndex();


   //Parent
   //cerr <<"PARENT=" << parent <<endl;
   if (!parent.isValid()) {
      //is Top Level Index
      if (column > 0)                return QModelIndex();
      if (row >= m_blocks.count())   return QModelIndex();
      return createIndex(row, column, -1);

   } else {
      //Is a action
      if (column > 2)                        return QModelIndex();
      if (parent.row() >= m_blocks.count())  return QModelIndex();
      QString block = m_blocks.at(parent.row());
      QList<CoaAction*> *list = m_actions.value(block);
      if (row >= list->count())              return QModelIndex();
      return createIndex(row, column, parent.row());
   }

   return QModelIndex();
}



/**
@brief Returns the parent of the model item with the given index.
*/
QModelIndex CoaActionViewModel::parent(const QModelIndex &index) const
{
   if (!index.isValid())           return QModelIndex();
   if (index.internalId() == -1)   return QModelIndex();
   return createIndex(index.internalId(),0,-1);
}





bool CoaActionViewModel::hasChildren ( const QModelIndex & index) const {
        if (!index.isValid()) return true;
        if (index.internalId() == -1) return true;
        return false;
}




/**

Method returns nothing. Except it is a DisplayRole.
*/
QVariant CoaActionViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   //BEGIN;

   //Check the Role
   if (role != Qt::DisplayRole) {
      return QVariant();
   }


   if (orientation == Qt::Horizontal) {
      //Give Name Columns
      switch(section){
         case 0: return QVariant(tr("Action"));
         case 1: return QVariant(tr("Description"));
         case 2: return QVariant(tr("Shortcut"));
      }
   }

   return QVariant();
}


void CoaActionViewModel::saveChangedShortcuts()
{
   BEGIN;
   QMap<CoaAction*, QKeySequence>::const_iterator i = m_changes.constBegin();
   while (i != m_changes.constEnd()) {
      CoaAction *action = i.key();
      action->setShortcut(i.value());
      i++;
   }
   m_changes.clear();
   emit haveUnsavedShortcuts(false);
}



void CoaActionViewModel::loadDefaultShortcuts(const QModelIndexList& list)
{
   BEGIN;
   QModelIndex index;

   foreach(index, list) {
      CoaAction *action = mapIndexToAction(index);
      if (action != 0) {
         setData(index, action->defaultShortcut(), Qt::EditRole);
      }
   }
}

