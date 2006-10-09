#ifndef __CoaLCDNumberPlugin_h__
#define __CoaLCDNumberPlugin_h__

#include "coabaseplugin.h"


class CoaLCDNumberPlugin: public CoaDisplayPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaLCDNumberPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
private:

};



#endif
