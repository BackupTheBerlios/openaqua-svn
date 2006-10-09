#ifndef __CoaTextBrowser_h__
#define __CoaTextBrowser_h__

#include <QTextBrowser>

class QMenu;
class QContextMenuEvent;

class CoaTextBrowser: public QTextBrowser
{
Q_OBJECT

public:
   CoaTextBrowser(QWidget *parent = 0);

   QMenu *createStandardContextMenu();

protected:
   virtual void contextMenuEvent(QContextMenuEvent *e);
   Q_DISABLE_COPY(CoaTextBrowser);


};



#endif
