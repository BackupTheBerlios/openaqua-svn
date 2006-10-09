#ifndef __CoaSettingsWidget_h__
#define __CoaSettingsWidget_h__

#include <CoaWidget>
#include <CoaString>


#include <QIcon>


class CoaAction;


class CoaSettingsWidget: public CoaWidget
{
Q_OBJECT

public:
   CoaSettingsWidget ( QWidget * const parent = 0, Qt::WFlags f = 0 );
   virtual ~CoaSettingsWidget();

   QIcon icon();
   void setIcon(const QIcon&);
   void setIcon(const QString& filename);

   CoaString shortName();
   void setShortName(const CoaString&);

   CoaString groupName() const;
   void setGroupName(const CoaString&);

   bool isDirty();

   virtual CoaAction *const widgetAction();

   virtual bool canApplyDefaults() const = 0;


signals:
   void signalIsDirty(const bool);
   void signalWantToBeShown(CoaSettingsWidget *const widget);
   void signalCanApplyDefaults(const bool);


public slots:
   virtual bool applyChanges()  = 0;
   virtual bool applyDefaults() = 0;
   void setDirty(const bool isDirty);

private slots:
   void actionTriggered ();

private:
   QIcon       m_settingIcon;
   CoaString   m_groupName;
   CoaAction   *m_widgetAction;

};

#endif //__CoaSettingsWidget_h__

