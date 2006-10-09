#ifndef __CoaTextEdit_h__
#define __CoaTextEdit_h__

#include <QTextEdit>

class QMenu;
class QContextMenuEvent;


class CoaTextEdit: public QTextEdit
{
Q_OBJECT

public:
   CoaTextEdit(QWidget *parent = 0);

   QMenu *createStandardContextMenu();

protected:
   virtual void contextMenuEvent(QContextMenuEvent *e);
   Q_DISABLE_COPY(CoaTextEdit);

};



#endif
