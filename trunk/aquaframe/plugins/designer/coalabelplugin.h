#ifndef __CoaLabelPlugin_h__
#define __CoaLabelPlugin_h__

#include "coabaseplugin.h"


class CoaLabelPlugin: public CoaDisplayPlugin
{
    Q_OBJECT
    //Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaLabelPlugin( QObject *parent = 0);

    virtual QWidget *createWidget(QWidget *parent);
    virtual QIcon icon() const;
    //virtual QString domXml() const;

private:

};



#endif
