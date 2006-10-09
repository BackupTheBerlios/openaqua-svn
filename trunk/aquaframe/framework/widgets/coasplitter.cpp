#include "coasplitter.h"
#include <CoaDebug>

CoaSplitter::CoaSplitter (QWidget *parent)
:QSplitter(parent)
{
   BEGIN;
}

CoaSplitter::CoaSplitter (Qt::Orientation orientation, QWidget * parent )
:QSplitter(orientation, parent)
{
   BEGIN;
}

CoaSplitter::~CoaSplitter ()
{
   BEGIN;
}

