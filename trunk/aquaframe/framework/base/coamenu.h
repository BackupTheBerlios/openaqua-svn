#ifndef __CoaMenu_h__
#define __CoaMenu_h__

#include <QMenu>

class QWidget;
class CoaActionGroup;
class CoaAction;

class CoaMenu: public QMenu
{
   Q_OBJECT

public:

   CoaMenu( QWidget * parent = 0 );
   CoaMenu ( const QString & title, QWidget * parent = 0 );
   virtual ~CoaMenu();

   void addActionGroup(CoaActionGroup * grp);

private:

};

#endif //__CoaObject_h__
