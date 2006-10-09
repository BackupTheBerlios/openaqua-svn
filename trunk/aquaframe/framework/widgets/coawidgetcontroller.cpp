#include "coawidgetcontroller.h"
#include <CoaDebug>


CoaWidgetController::CoaWidgetController(QObject *const parent)
: CoaThread("wgt_cont", parent)
{
   BEGIN;
}



CoaWidgetController::~CoaWidgetController()
{
   BEGIN;
   m_mutex.lock();
   m_widgets.clear();
   m_mutex.unlock();
}

void CoaWidgetController::registerWidget(IoaDatabaseWidget *widget)
{
   BEGIN;
   if (widget == 0) return;
   if (! widget->databaseEnabled()) return;
   m_mutex.lock();
   m_widgets.insert(widget);
   m_mutex.unlock();
}

void CoaWidgetController::registerWidget(QWidget *widget)
{
   BEGIN;

#if 0   
   if (widget == 0) return;
   CoaLineEdit *w = static_cast<CoaLineEdit*>(widget);
   if (w == 0) return;

   IoaDatabaseWidget *e = static_cast<IoaDatabaseWidget*>(w);
   if (e == 0) return;
   registerWidget(e);
#endif
}


void CoaWidgetController::unregisterWidget(QWidget *widget)
{
   BEGIN;
#if 0
   if (widget == 0) return;
   CoaLineEdit *w = static_cast<CoaLineEdit*>(widget);
   if (w == 0) return;

   IoaDatabaseWidget *e = static_cast<IoaDatabaseWidget*>(w);
   if (e == 0) return;
   unregisterWidget(e);
#endif
}

void CoaWidgetController::unregisterWidget(IoaDatabaseWidget *widget)
{
   BEGIN;
   if (widget == 0) return;
   m_mutex.lock();
   if (m_widgets.contains(widget)){
      m_widgets.remove(widget);
   }
   m_mutex.unlock();

}

void CoaWidgetController::registerWidgets(const QList<QWidget *>& widgets)
{
   BEGIN;

   foreach (QWidget *w, widgets) {
      registerWidget(w);
   }
}


void CoaWidgetController::unregisterWidgets(const QList<QWidget *>& widgets)
{
   BEGIN;
   foreach (QWidget *w, widgets) {
      unregisterWidget(w);
   }
}

//EOF
