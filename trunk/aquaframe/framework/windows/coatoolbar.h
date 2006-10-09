#ifndef __CoaToolBar_h__
#define __CoaToolBar_h__

#include <QToolBar>

class QWidget;
class CoaActionGroup;
class CoaAction;

class CoaToolBar: public QToolBar
{
   Q_OBJECT

public:

   CoaToolBar ( const QString & title, QWidget * parent = 0 );
   CoaToolBar ( QWidget * parent = 0 );
   virtual ~CoaToolBar();

   void addActionGroup(CoaActionGroup * grp);
   void addAction(CoaAction *const action);

private:
   CoaToolBar ( const CoaToolBar& );

};

#endif //__CoaObject_h__
