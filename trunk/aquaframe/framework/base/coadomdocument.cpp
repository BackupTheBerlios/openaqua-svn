#include "coadomdocument.h"
#include <CoaDebug>




CoaDomDocument::CoaDomDocument ()
: QDomDocument()
{
   BEGIN;
}

CoaDomDocument::CoaDomDocument ( const QString & name )
: QDomDocument(name)
{
   BEGIN;
}

CoaDomDocument::CoaDomDocument ( const QDomDocumentType & doctype )
: QDomDocument(doctype)
{
   BEGIN;
}

CoaDomDocument::CoaDomDocument ( const QDomDocument & x )
: QDomDocument(x)
{
   BEGIN;
}



CoaDomDocument::~CoaDomDocument()
{
   BEGIN;
}
