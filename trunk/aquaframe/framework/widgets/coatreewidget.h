#ifndef __CoaTreeWidget_h_
#define __CoaTreeWidget_h_

#include <QTreeWidget>


class CoaTreeWidget: public QTreeWidget
{
Q_OBJECT

public:
   CoaTreeWidget ( QWidget * parent = 0);
   virtual ~CoaTreeWidget();

};

#endif

