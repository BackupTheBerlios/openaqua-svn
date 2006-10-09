#include "coaitemselection.h"
#include <CoaDebug>
#include <cassert>


CoaItemSelection::CoaItemSelection ()
: QItemSelection()
{
   BEGIN;
}



CoaItemSelection::CoaItemSelection ( const QModelIndex & topLeft, const QModelIndex &bottomRight )
: QItemSelection(topLeft, bottomRight)
{
   BEGIN;
}


