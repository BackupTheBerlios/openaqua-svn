#ifndef __CoaDockWidgetPlugin_h__
#define __CoaDockWidgetPlugin_h__

#include "coabaseplugin.h"


class CoaDockWidgetPlugin: public CoaContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaDockWidgetPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
