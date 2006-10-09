#ifndef __CoaSplitter_h__
#define __CoaSplitter_h__

#include <QSplitter>


class CoaSplitter: public QSplitter
{
Q_OBJECT

public:
   CoaSplitter (QWidget *parent = 0);
   CoaSplitter (Qt::Orientation orientation, QWidget * parent = 0 );
   virtual ~CoaSplitter ();

    
};



#endif
