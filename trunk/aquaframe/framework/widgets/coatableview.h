#ifndef __CoaTableView_h_
#define __CoaTableView_h_

#include <QTableView>

class CoaMenu;


class CoaTableView: public QTableView
{
Q_OBJECT

public:
   CoaTableView ( QWidget * parent = 0);
   virtual ~CoaTableView();

   virtual void setModel ( QAbstractItemModel * model );

protected:
   CoaMenu *createStandardContextMenu();
   virtual void contextMenuEvent ( QContextMenuEvent * e );


public slots:
    void slotSortOnColumn(const int col);


};

#endif

