#ifndef __CoaDomDocument_h__
#define __CoaDomDocument_h__

#include <QDomDocument>


class CoaDomDocument: public QDomDocument
{
public:

   CoaDomDocument ();
   CoaDomDocument ( const QString & name );
   CoaDomDocument ( const QDomDocumentType & doctype );
   CoaDomDocument ( const QDomDocument & x );
   virtual ~CoaDomDocument();



private:

};

#endif //__CoaDomDocument_h__
