#include "coatextdocument.h"
#include <CoaDebug>

CoaTextDocument::CoaTextDocument ( QObject * parent)
: QTextDocument(parent)
{
   BEGIN;
}



CoaTextDocument::CoaTextDocument ( const QString & text, QObject * parent)
: QTextDocument(text, parent)
{
   BEGIN;
}



CoaTextDocument::~CoaTextDocument ()
{
   BEGIN;
}



