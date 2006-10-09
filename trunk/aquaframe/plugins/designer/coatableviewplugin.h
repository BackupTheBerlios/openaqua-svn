#ifndef __CoaTableViewPlugin_h__
#define __CoaTableViewPlugin_h__

#include "coabaseplugin.h"


class CoaTableViewPlugin: public CoaBasePlugin
{
   Q_OBJECT
         Q_INTERFACES(QDesignerCustomWidgetInterface)

   public:
      CoaTableViewPlugin( QObject *parent = 0);
    
      virtual QWidget *createWidget(QWidget *parent);
   private:

};



#endif
