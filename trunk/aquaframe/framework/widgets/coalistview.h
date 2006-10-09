#ifndef __CoaListView_h_
#define __CoaListView_h_

#include <QListView>


class CoaListView: public QListView
{
Q_OBJECT

public:
   CoaListView ( QWidget * parent = 0);
   virtual ~CoaListView();

};

#endif

