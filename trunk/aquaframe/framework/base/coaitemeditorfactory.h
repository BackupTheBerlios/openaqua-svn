#ifndef __CoaItemEditorFactory_h__
#define __CoaItemEditorFactory_h__

#include <QItemEditorFactory>

class CoaItemEditorFactory: public QItemEditorFactory
{
public: 
   CoaItemEditorFactory ();
   virtual ~CoaItemEditorFactory ();
   virtual QWidget * createEditor ( QVariant::Type type, QWidget * parent ) const;
};


#endif //__CoaItemEditorFactory_h__

