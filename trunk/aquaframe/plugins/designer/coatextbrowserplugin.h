#ifndef __CoaTextBrowserPlugin_h__
#define __CoaTextBrowserPlugin_h__

#include "coabaseplugin.h"


class CoaTextBrowserPlugin: public CoaDisplayPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaTextBrowserPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
