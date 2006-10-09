#include "coasupportwidgets.h"

//load ContainerWidgets
#include "coagroupboxplugin.h"
#include "coatoolboxplugin.h"
#include "coatabwidgetplugin.h"
#include "coastackedwidgetplugin.h"
#include "coaframeplugin.h"
#include "coadockwidgetplugin.h"

//Load Display Widgets
#include "coalabelplugin.h"
#include "coatextbrowserplugin.h"
#include "coalcdnumberplugin.h"
#include "coaprogressbarplugin.h"
#include "coapushbuttonplugin.h"
#include "coaradiobuttonplugin.h"
#include "coatoolbuttonplugin.h"
#include "coatableviewplugin.h"


//load other stuff
#include "coatexteditplugin.h"
#include "coamainwindow_plugin.h"
#include "coalineeditplugin.h"
#include "coasqlconnectionwidgetplugin.h"
#include "coacheckboxplugin.h"


CoaSupportWidgets::CoaSupportWidgets(QObject *parent)
    : QObject(parent)
{
   //Add Container Widgets
    m_plugins.append(new CoaGroupBoxPlugin(this));
    m_plugins.append(new CoaToolBoxPlugin(this));

    //the following widgets needs some special setup
    //m_plugins.append(new CoaTabWidgetPlugin(this));
    //m_plugins.append(new CoaStackedWidgetPlugin(this));
    //m_plugins.append(new CoaFramePlugin(this));
    //m_plugins.append(new CoaDockWidgetPlugin(this));

   //Add Display Widgets
    m_plugins.append(new CoaLabelPlugin(this));
    m_plugins.append(new CoaTextBrowserPlugin(this));
    m_plugins.append(new CoaLCDNumberPlugin(this));
    m_plugins.append(new CoaProgressBarPlugin(this));
    m_plugins.append(new CoaPushButtonPlugin(this));
    m_plugins.append(new CoaRadioButtonPlugin(this));
    m_plugins.append(new CoaToolButtonPlugin(this));
    m_plugins.append(new CoaTableViewPlugin(this));

    //Add other Widgets
    m_plugins.append(new CoaTextEditPlugin(this));
    m_plugins.append(new CoaLineEditPlugin(this));
    m_plugins.append(new CoaCheckBoxPlugin(this));
    m_plugins.append(new CoaSqlConnectionWidgetPlugin(this));

    //m_plugins.append(new CoaMainWindowPlugin(this));

}

QList<QDesignerCustomWidgetInterface*> CoaSupportWidgets::customWidgets() const
{
    return m_plugins;
}

Q_EXPORT_PLUGIN(CoaSupportWidgets)


