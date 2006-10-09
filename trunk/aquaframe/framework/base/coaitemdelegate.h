#ifndef __CoaItemDelegate_h__
#define __CoaItemDelegate_h__

#include <QItemDelegate>

class CoaItemDelegate: public QItemDelegate
{
Q_OBJECT
public:
   explicit CoaItemDelegate ( QObject * parent = 0 );
   virtual ~CoaItemDelegate ();

};

#endif //__CoaItemDelegate_h__

