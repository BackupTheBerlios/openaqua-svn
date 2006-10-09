#ifndef __CoaToolsChangeShortCuts_Model_h__
#define __CoaToolsChangeShortCuts_Model_h__

#include <CoaDialog>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QList>
#include <QMap>
#include <QModelIndexList>

class CoaAction;



/////////////////////////////////////////////////////////////////
//A Data Modell to view / edit Actions

class CoaActionViewModel: public QAbstractItemModel {
Q_OBJECT
public:

   //Constructors
   CoaActionViewModel ( QObject *parent = 0 );
   virtual ~CoaActionViewModel ();

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

signals:
   void haveUnsavedShortcuts(const bool flag);


public slots:
   void saveChangedShortcuts();
   void loadDefaultShortcuts(const QModelIndexList& list);

private:
   CoaAction*  mapIndexToAction(const QModelIndex& index) const;
   int                                 m_rows;
   int                                 m_columns;
   QList<QString>                      m_blocks;
   QMap<QString, QList<CoaAction*>*>   m_actions;
   QMap<CoaAction*, QKeySequence>      m_changes;
};


#endif //__CoaToolsChangeShortCuts_Model_h__
