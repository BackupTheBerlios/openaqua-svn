#ifndef __CoaCheckBoxPlugin_h__
#define __CoaCheckBoxPlugin_h__

#include "coabaseplugin.h"


class CoaCheckBoxPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaCheckBoxPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
private:

};



#endif
