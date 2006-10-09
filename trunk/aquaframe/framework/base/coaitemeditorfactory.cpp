#include "coaitemeditorfactory.h"

#include <CoaDebug>
#include <cassert>


CoaItemEditorFactory::CoaItemEditorFactory ()
: QItemEditorFactory()
{
   BEGIN;
}



CoaItemEditorFactory::~CoaItemEditorFactory ()
{
   BEGIN;
}



QWidget * CoaItemEditorFactory::createEditor ( QVariant::Type type, QWidget * parent ) const
{
   BEGIN;
   QWidget *result = QItemEditorFactory::createEditor(type, parent);
   return result;
}


