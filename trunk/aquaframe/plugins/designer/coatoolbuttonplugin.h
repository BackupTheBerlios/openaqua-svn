#ifndef __CoaToolButtonPlugin_h__
#define __CoaToolButtonPlugin_h__

#include "coabaseplugin.h"


class CoaToolButtonPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaToolButtonPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
