#ifndef __CoaTextDocument_h__
#define __CoaTextDocument_h__

#include <QTextDocument>

class CoaTextDocument: public QTextDocument
{
Q_OBJECT
public:
   CoaTextDocument ( QObject * parent = 0 );
   CoaTextDocument ( const QString & text, QObject * parent = 0 );
   virtual ~CoaTextDocument ();

};


#endif //__CoaTextDocument_h__

