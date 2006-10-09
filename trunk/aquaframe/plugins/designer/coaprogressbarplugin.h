#ifndef __CoaProgressBarPlugin_h__
#define __CoaProgressBarPlugin_h__

#include "coabaseplugin.h"


class CoaProgressBarPlugin: public CoaDisplayPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaProgressBarPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
