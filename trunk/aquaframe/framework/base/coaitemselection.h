#ifndef __CoaItemSelection_h__
#define __CoaItemSelection_h__

#include <QItemSelection>

class CoaItemSelection: public QItemSelection {
public:
   CoaItemSelection ();
   CoaItemSelection ( const QModelIndex & topLeft, const QModelIndex &bottomRight );
};

#endif //__CoaItemSelection_h__

