#ifndef __CoaFramePlugin_h__
#define __CoaFramePlugin_h__

#include "coabaseplugin.h"


class CoaFramePlugin: public CoaContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaFramePlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
