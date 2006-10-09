#include "coasettings.h"



CoaSettings::CoaSettings(QObject * parent)
:QSettings(parent)
{
}


CoaSettings::CoaSettings( const QString & organization, const QString & application, QObject * parent)
:QSettings(organization, application, parent)
{
}


CoaSettings::~CoaSettings()
{
}
