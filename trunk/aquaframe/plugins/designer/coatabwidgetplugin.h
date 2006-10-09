#ifndef __CoaTabWidgetPlugin_h__
#define __CoaTabWidgetPlugin_h__

#include "coabaseplugin.h"


class CoaTabWidgetPlugin: public CoaContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaTabWidgetPlugin( QObject *parent = 0);

    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;


private:

};



#endif
