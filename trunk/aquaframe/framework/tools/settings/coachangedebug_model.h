#ifndef __CoaToolsChangeShortCuts_Model_h__
#define __CoaToolsChangeShortCuts_Model_h__

//#include <CoaDialog>
#include <CoaDebug>
#include <CoaAbstractItemModel>

#include <QModelIndex>
#include <QVariant>
#include <QList>
#include <QModelIndexList>
#include <QPair>

class CoaAction;





/////////////////////////////////////////////////////////////////
//A Data Modell to view / edit Actions

class CoaDebugSettingsModel: public CoaAbstractItemModel {
Q_OBJECT
public:

   //Constructors
   CoaDebugSettingsModel ( QObject *parent = 0 );
   virtual ~CoaDebugSettingsModel ();

   //Item access
   virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
   virtual QModelIndex parent(const QModelIndex &child) const;
   virtual bool hasChildren ( const QModelIndex & parent) const;

   //Reading
   virtual int rowCount ( const QModelIndex & parent = QModelIndex()) const;
   virtual int columnCount ( const QModelIndex & parent ) const;
   virtual QVariant data ( const QModelIndex & index, int role ) const;
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

   //Editing
   virtual bool setData ( const QModelIndex & index, const QVariant & value, int role );
   virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;
   virtual void setDefault(const QModelIndexList& list);
   virtual bool saveChanges();


public slots:
   void setNewFile(const QString, const int);

private:
   void loadFileList();

   int                                           m_columns;
   QList<QPair<QString, CoaDebug::DebugLevel> >  m_files;
};


#endif //__CoaToolsChangeShortCuts_Model_h__
