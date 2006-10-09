#ifndef __CoaPushButtonPlugin_h__
#define __CoaPushButtonPlugin_h__

#include "coabaseplugin.h"


class CoaPushButtonPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaPushButtonPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
private:

};



#endif
