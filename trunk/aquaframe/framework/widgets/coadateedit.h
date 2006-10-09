#ifndef __CoaDateEdit_h_
#define __CoaDateEdit_h_

#include <QDateEdit>
#include <QDate>

class CoaDateEdit: public QDateEdit
{
Q_OBJECT

public:
   CoaDateEdit ( QWidget * parent = 0);
   CoaDateEdit ( const QDate & date, QWidget * parent = 0 );
   virtual ~CoaDateEdit();
    
};

#endif

