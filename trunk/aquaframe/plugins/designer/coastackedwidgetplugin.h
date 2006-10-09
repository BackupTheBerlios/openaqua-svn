#ifndef __CoaStackedWidgetPlugin_h__
#define __CoaStackedWidgetPlugin_h__

#include "coabaseplugin.h"


class CoaStackedWidgetPlugin: public CoaContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaStackedWidgetPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
