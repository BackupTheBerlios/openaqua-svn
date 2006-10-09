#ifndef __CoaTextEditPlugin_h__
#define __CoaTextEditPlugin_h__

#include "coabaseplugin.h"


class CoaTextEditPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaTextEditPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
