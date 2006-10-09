#ifndef __CoaLineEditPlugin_h__
#define __CoaLineEditPlugin_h__

#include "coabaseplugin.h"


class CoaLineEditPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaLineEditPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
