#include "coalabel.h"
#include <CoaDebug>



CoaLabel::CoaLabel ( QWidget * const parent, Qt::WFlags f )
      : QLabel( parent, f )
      , IoaDataSetWidget()
{
   BEGIN;
}



CoaLabel::CoaLabel ( const CoaString & text, QWidget * const parent, Qt::WFlags f )
      : QLabel( text, parent, f )
{
   BEGIN;
}



CoaLabel::~CoaLabel()
{
   BEGIN;
}


void CoaLabel::updateValue(const QVariant& v)
{
   BEGIN;
   setText(v.toString());
}

