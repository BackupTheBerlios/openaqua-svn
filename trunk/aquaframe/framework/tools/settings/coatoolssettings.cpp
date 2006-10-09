#include "coatoolssettings.h"
#include "coatoolssettingsallicons.h"
#include "coachangeshortcutwidget.h"
#include "coachangedebugwidget.h"

#include <CoaDebug>

#include <CoaStackedWidget>
#include <CoaToolBar>
#include <CoaAction>
#include <CoaPushButton>
#include <CoaWidget>
#include <CoaSettingsWidget>
#include <CoaToolBar>
#include <CoaFormFactory>


#include <QHBoxLayout>
#include <QIcon>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaToolsSettings);


//CoaToolsSettings::CoaToolsSettings(const QString& objectName,  CoaWorkbench *const parent, Qt::WFlags flags)
CoaToolsSettings::CoaToolsSettings()
: CoaToolWindow("CoaToolsSettings", 0)
, m_setWidgetAllIcons(0)
, m_btnApply(0)
, m_btnClose(0)
, m_btnDefault(0)

{
   BEGIN;
   REGISTERSINGLETON("CoaToolsSettings");
   setWindowTitle(tr("Settings[*]", "dont touch the [*]"));
   buildGui();
   assert(m_toolBar);
   assert(m_widgetStack);
   readSettings();


   //remove all default pages in WidgetStack
   while(m_widgetStack->count() > 0){
      m_widgetStack->setCurrentIndex(0);
      m_widgetStack->removeWidget(m_widgetStack->currentWidget());
   }

   //create some default Widgets
   m_setWidgetAllIcons = new CoaToolsSettingsAllIcons();
   addSettingsWidget(m_setWidgetAllIcons);
   m_toolBar->addSeparator();

   addSettingsWidget(new CoaSettingsWidgetChangeShortcut());
#ifdef DEBUG
   addSettingsWidget(new CoaSettingsWidgetChangeDebug());
#endif

   m_widgetStack->setCurrentIndex(0);
   dirtyStateChanged();
}


CoaToolsSettings::~CoaToolsSettings()
{
   BEGIN;
   INSTANCE=0;
   UNREGISTERSINGLETON("CoaToolsSettings");
}


void CoaToolsSettings::buildGui()
{
   BEGIN;
   m_widgetStack = new CoaStackedWidget;
   //m_widgetStack->setBackgroundRole(QPalette::Base);
   setCentralWidget(m_widgetStack);

   m_btnDefault  = new CoaPushButton(tr("Default"));
   m_btnApply    = new CoaPushButton(tr("Apply"));
   m_btnClose    = new CoaPushButton(tr("Close"));

   m_btnDefault->setEnabled(false);
   m_btnApply->setEnabled(false);

   addButton(m_btnDefault);
   addButtonStretch();
   addButton(m_btnApply);
   addButton(m_btnClose);

   connect(m_btnDefault,  SIGNAL(clicked (bool)),       this, SLOT(applyDefaults()));
   connect(m_btnApply,    SIGNAL(clicked (bool)),       this, SLOT(applyChanges()));
   connect(m_btnClose,    SIGNAL(clicked (bool)),       this, SLOT(close()));

   buildToolBar();
}



void CoaToolsSettings::buildToolBar()
{
   BEGIN;
   m_toolBar = new CoaToolBar(this);
   assert(m_toolBar);
   addToolBar(m_toolBar);
   makeLayoutToolBar(m_toolBar);
}


bool CoaToolsSettings::applyChanges()
{
   BEGIN;

   if (isWindowModified() != true) {RETURN(true);}
   int errorCount = 0;

   //apply Changes
   for (int i = 0; i<m_widgetStack->count(); ++i){
      QWidget *qwidget = m_widgetStack->widget(i);
      CoaSettingsWidget *widget = dynamic_cast<CoaSettingsWidget*>(qwidget);
      if (widget != 0){
         if (widget->isDirty() == true && widget->applyChanges() != true){
            ++errorCount;
         }
      }
   }


   if (errorCount == 0) {
      RETURN(true);
   } else {
      RETURN(false);
   }

}

bool CoaToolsSettings::applyDefaults()
{
   BEGIN;

   if (m_btnClose->isEnabled() != true) {RETURN(true);}
   int errorCount = 0;


   if (QMessageBox::Yes !=
       QMessageBox::question ( this, COAAPP->applicationName(),
                               tr("Do you want to load default settings for the selected parts?"),
                               QMessageBox::Yes|QMessageBox::Default,
                               QMessageBox::No
                             )
      )
   {
      RETURN(false);
   }


   //apply defaults
   for (int i = 0; i<m_widgetStack->count(); ++i){
      QWidget *qwidget = m_widgetStack->widget(i);
      CoaSettingsWidget *widget = dynamic_cast<CoaSettingsWidget*>(qwidget);
      if (widget != 0){
         if (widget->canApplyDefaults() == true && widget->applyDefaults() != true){
            ++errorCount;
         }
      }
   }


   if (errorCount == 0) {
      RETURN(true);
   } else {
      RETURN(false);
   }

}



bool CoaToolsSettings::addSettingsWidget(CoaSettingsWidget *const widget)
{
   BEGIN;

   //some checks
   assert(m_widgetStack);
   assert(m_toolBar);
   assert(widget);
   if (widget == 0 ) RETURN(false);

   if (m_widgetStack->indexOf(widget) >= 0){
      RETURN(false); //the widget already existst
   }

   //add the widget to the stack, the widget list, the toolbar
   m_widgetStack->addWidget(widget);
   m_toolBar->addAction(widget->widgetAction());

   connect(widget, SIGNAL(signalIsDirty(const bool)),                     this, SLOT(dirtyStateChanged()));
   connect(widget, SIGNAL(signalCanApplyDefaults(const bool)),            this, SLOT(defaultStateChanged()));
   connect(widget, SIGNAL(signalWantToBeShown(CoaSettingsWidget *const)), this, SLOT(showWidget(CoaSettingsWidget *const)));

   m_setWidgetAllIcons->addSettingsWidget(widget);
   RETURN(true);
}



void CoaToolsSettings::remSettingsWidget(CoaSettingsWidget *const widget)
{
   BEGIN;
   const int currentIndex = m_widgetStack->indexOf(widget);
   if (currentIndex == m_widgetStack->currentIndex()){
      m_widgetStack->setCurrentIndex(0);
   }
   m_widgetStack->removeWidget(widget);
   m_setWidgetAllIcons->remSettingsWidget(widget);
   m_toolBar->removeAction(widget->widgetAction());
   disconnect(widget, 0, 0, 0);
}



void CoaToolsSettings::dirtyStateChanged()
{
   BEGIN;

   //try to find a dirty widget
   for (int i = 0; i<m_widgetStack->count(); ++i){
      QWidget *qwidget = m_widgetStack->widget(i);
      CoaSettingsWidget *widget = dynamic_cast<CoaSettingsWidget*>(qwidget);
      if (widget != 0){
         if (widget->isDirty() == true){
            m_btnApply->setDisabled(false);
            setWindowModified(true);
            return;
         }
      }
   }


   //otherwise the window is clear
   m_btnApply->setDisabled(true);
   setWindowModified(false);
}


void CoaToolsSettings::defaultStateChanged()
{
   BEGIN;

   //try to find a dirty widget
   for (int i = 0; i<m_widgetStack->count(); ++i){
      QWidget *qwidget = m_widgetStack->widget(i);
      CoaSettingsWidget *widget = dynamic_cast<CoaSettingsWidget*>(qwidget);
      if (widget != 0){
         if (widget->canApplyDefaults() == true){
            m_btnDefault->setEnabled(true);
            return;
         }
      }
   }


   //otherwise the window is clear
   m_btnApply->setDisabled(true);
   setWindowModified(false);
}



void CoaToolsSettings::showWidget(CoaSettingsWidget *const widget)
{
   BEGIN;
   m_widgetStack->setCurrentWidget(widget);
   m_btnDefault->setEnabled(false);
}



void CoaToolsSettings::makeLayoutWindow(CoaToolsSettings *const window)
{
   BEGIN;
   assert(window);
   if (window == 0) return;
}



void CoaToolsSettings::makeLayoutToolBar(CoaToolBar *const toolBar)
{
   BEGIN;
   assert(toolBar);
   if (toolBar == 0) return;
   toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

}


void CoaToolsSettings::makeLayoutToolbarButtons(CoaToolButton *const button)
{
   BEGIN;
   assert(button);
   if (button == 0) return;

}



