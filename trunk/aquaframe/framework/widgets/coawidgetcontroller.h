#ifndef __CoaWidgetController_h_
#define __CoaWidgetController_h_

#include <CoaThread>
#include <CoaSet>
#include <CoaLineEdit>
#include <IoaDatabaseWidget>
#include <CoaMakros>
#include <QMutex>

class CoaWidgetController: public CoaThread {
Q_OBJECT
public:
   CoaWidgetController(QObject *const parent = 0);
   virtual ~CoaWidgetController();
   void registerWidget(QWidget *widget);
   void unregisterWidget(QWidget *widget);

   void registerWidgets(const QList<QWidget *>& widgets);
   void unregisterWidgets(const QList<QWidget *>& widgets);

private:
   void registerWidget(IoaDatabaseWidget *widget);
   void unregisterWidget(IoaDatabaseWidget *widget);

   CoaSet<IoaDatabaseWidget*> m_widgets;
   QMutex m_mutex;

   COAMAKRO_NO_COPYCONSTRUCTOR(CoaWidgetController);
   COAMAKRO_NO_COMPARE(CoaWidgetController);

};

#endif //__CoaWidgetController__

