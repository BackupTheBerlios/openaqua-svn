#ifndef __CoaSqlConnectionWidgetPlugin_h__
#define __CoaSqlConnectionWidgetPlugin_h__

#include "coabaseplugin.h"


class CoaSqlConnectionWidgetPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaSqlConnectionWidgetPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
