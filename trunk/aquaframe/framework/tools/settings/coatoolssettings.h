#ifndef __CoaToolsSettings_h__
#define __CoaToolsSettings_h__

#include <CoaToolWindow>
#include <CoaMakros>


class CoaStackedWidget;
class CoaToolBar;
class CoaPushButton;
class CoaToolButton;

class CoaToolsSettingsAllIcons;
class CoaSettingsWidget;

class CoaToolsSettings: public CoaToolWindow
{
Q_OBJECT

public:
   bool addSettingsWidget(CoaSettingsWidget *const widget);
   void remSettingsWidget(CoaSettingsWidget *const widget);

   virtual void makeLayoutWindow(CoaToolsSettings *const window);
   virtual void makeLayoutToolBar(CoaToolBar *const toolBar);
   virtual void makeLayoutToolbarButtons(CoaToolButton *const button);

public slots:
   virtual bool applyChanges();
   virtual bool applyDefaults();
   void dirtyStateChanged();
   void defaultStateChanged();
   void showWidget(CoaSettingsWidget *const widget);

private:
   void buildGui();
   void buildToolBar();

   CoaStackedWidget                   *m_widgetStack;
   CoaToolBar                         *m_toolBar;
   CoaToolsSettingsAllIcons           *m_setWidgetAllIcons;

   CoaPushButton                      *m_btnApply;
   CoaPushButton                      *m_btnClose;
   CoaPushButton                      *m_btnDefault;


   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaToolsSettings);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaToolsSettings);
   COAMAKRO_NO_COMPARE(CoaToolsSettings);


};

#endif //__CoaToolsSettings_h__

