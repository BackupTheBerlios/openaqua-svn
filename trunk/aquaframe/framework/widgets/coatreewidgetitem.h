#ifndef __CoaTreeWidgetItem_h_
#define __CoaTreeWidgetItem_h_


#include <QTreeWidgetItem>


class CoaTreeWidgetItem: public QTreeWidgetItem
{
public:
   CoaTreeWidgetItem ( int type = Type );
   CoaTreeWidgetItem ( QTreeWidget * parent, int type = Type );
   CoaTreeWidgetItem ( QTreeWidget * parent, QTreeWidgetItem * preceding, int type = Type );
   CoaTreeWidgetItem ( QTreeWidgetItem * parent, int type = Type );
   CoaTreeWidgetItem ( QTreeWidgetItem * parent, QTreeWidgetItem * preceding, int type = Type );

   virtual ~CoaTreeWidgetItem();

};

#endif

