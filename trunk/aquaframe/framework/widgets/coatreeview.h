#ifndef __CoaTreeView_h_
#define __CoaTreeView_h_

#include <QTreeView>


class CoaTreeView: public QTreeView
{
Q_OBJECT

public:
   CoaTreeView ( QWidget * parent = 0);
   virtual ~CoaTreeView();
    
};

#endif

