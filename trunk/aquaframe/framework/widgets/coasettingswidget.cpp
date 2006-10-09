#include "coasettingswidget.h"
#include <CoaDebug>

#include <CoaAction>


CoaSettingsWidget::CoaSettingsWidget ( QWidget * const parent, Qt::WFlags f )
: CoaWidget(parent, f)
, m_widgetAction(0)
{
   BEGIN;
   setGroupName(tr("Application"));
}



CoaSettingsWidget::~CoaSettingsWidget()
{
   BEGIN;
}

CoaAction *const CoaSettingsWidget::widgetAction()
{
   BEGIN;

   if (m_widgetAction == 0) {
      m_widgetAction = new CoaAction(this);
      connect(m_widgetAction, SIGNAL(triggered (bool)), this, SLOT(actionTriggered ()));
   }
   RETURN(m_widgetAction);
}

QIcon CoaSettingsWidget::icon()
{
   BEGIN;
   CoaAction *action = widgetAction();
   assert(action);
   return action->icon();
}


void CoaSettingsWidget::setIcon(const QIcon& icon)
{
   BEGIN;
   CoaAction *action = widgetAction();
   assert(action);
   action->setIcon(icon);
}


void CoaSettingsWidget::setIcon(const QString& filename)
{
   BEGIN;
   CoaAction *action = widgetAction();
   assert(action);
   action->setIcon(filename);
}


CoaString CoaSettingsWidget::shortName()
{
   BEGIN;
   CoaAction *action = widgetAction();
   assert(action);
   RETURN(action->iconText());
}


void CoaSettingsWidget::setShortName(const CoaString& name)
{
   BEGIN;
   CoaAction *action = widgetAction();
   assert(action);
   action->setIconText(name);
}


void CoaSettingsWidget::setDirty(const bool isDirty)
{
   BEGIN;
   setWindowModified(isDirty);
   emit signalIsDirty(isDirty);
}



bool CoaSettingsWidget::isDirty()
{
   BEGIN;
   RETURN(isWindowModified());
}



CoaString CoaSettingsWidget::groupName() const
{
   BEGIN;
   RETURN(m_groupName);
}


void CoaSettingsWidget::setGroupName(const CoaString& group)
{
   BEGIN;
   m_groupName = group;
}

void CoaSettingsWidget::actionTriggered ()
{
   BEGIN;
   emit signalWantToBeShown(this);
}
