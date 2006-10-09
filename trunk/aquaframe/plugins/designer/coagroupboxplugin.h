#ifndef __CoaGroupBoxPlugin_h__
#define __CoaGroupBoxPlugin_h__

#include "coabaseplugin.h"


class CoaGroupBoxPlugin: public CoaContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaGroupBoxPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
