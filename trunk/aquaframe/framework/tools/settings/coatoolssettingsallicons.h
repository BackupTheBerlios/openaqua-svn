#ifndef __CoaToolsSettingsAllIcons_h__
#define __CoaToolsSettingsAllIcons_h__

#include <CoaSettingsWidget>
#include <CoaMap>
#include <CoaString>


class QHBoxLayout;

class CoaToolsSettingsAllIcons: public CoaSettingsWidget
{
Q_OBJECT
public:
   CoaToolsSettingsAllIcons( QWidget * const parent = 0, Qt::WFlags f = 0 );
   virtual  ~CoaToolsSettingsAllIcons();

   virtual void makeLayoutWidgetButtons(CoaToolButton *const button);
   virtual bool canApplyDefaults() const;

public slots:
   virtual bool applyChanges();
   virtual bool applyDefaults();
   void addSettingsWidget(CoaSettingsWidget *const widget);
   void remSettingsWidget(CoaSettingsWidget *const widget);

private:
   void buildGui();

   QVBoxLayout                  *m_mainLayout;
   CoaMap<CoaString, QObject*>  m_widgetGroups;

};


#endif //__CoaToolsSettingsAllIcons_h__

