#ifndef __CoaToolBoxPlugin_h__
#define __CoaToolBoxPlugin_h__

#include "coabaseplugin.h"


class CoaToolBoxPlugin: public CoaContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaToolBoxPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
