#ifndef __CoaMenuBar_h__
#define __CoaMenuBar_h__

#include <QMenuBar>

class QWidget;
class CoaActionGroup;
class CoaAction;

class CoaMenuBar: public QMenuBar
{
   Q_OBJECT

public:

   CoaMenuBar( QWidget * parent = 0 );
   virtual ~CoaMenuBar();

   void addActionGroup(CoaActionGroup * grp);

private:

};

#endif //__CoaObject_h__
