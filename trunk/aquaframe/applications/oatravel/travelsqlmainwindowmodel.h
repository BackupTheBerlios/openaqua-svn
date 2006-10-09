#ifndef __TravelSqlMainWindowModel_h__
#define __TravelSqlMainWindowModel_h__


#include <CoaSqlTableModel>

class TravelSqlMainWindowModel: public CoaSqlTableModel
{
public:
   explicit TravelSqlMainWindowModel ( QObject * parent = 0, QSqlDatabase db = QSqlDatabase() );

   //!destructor
   virtual ~TravelSqlMainWindowModel();

   //Item access
   virtual bool saveChanges();

   virtual int rowCount ( const QModelIndex & parent = QModelIndex() );
};

#endif //__TravelSqlMainWindowModel_h__


