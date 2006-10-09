#ifndef __CoaSqlTableModel_h__
#define __CoaSqlTableModel_h__

#include <QSqlTableModel>

#include <CoaSqlDatabase>


class CoaSqlTableModel: public QSqlTableModel {
Q_OBJECT

public:
   explicit CoaSqlTableModel ( QObject * parent = 0, QSqlDatabase db = CoaSqlDatabase() );
   virtual ~CoaSqlTableModel ();
   QSqlDatabase database () const;


   //virtual void QSqlTableModel::setQuery ( const QSqlQuery & query );

};

#endif //__CoaSqlTableModel_h__

