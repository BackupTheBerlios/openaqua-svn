#ifndef __CoaRadioButtonPlugin_h__
#define __CoaRadioButtonPlugin_h__

#include "coabaseplugin.h"


class CoaRadioButtonPlugin: public CoaBasePlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaRadioButtonPlugin( QObject *parent = 0);
    
    virtual QWidget *createWidget(QWidget *parent);
private:

};



#endif
