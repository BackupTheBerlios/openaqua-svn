#ifndef __CoaFrame_h__
#define __CoaFrame_h__

#include <QFrame>


class CoaFrame: public QFrame
{
Q_OBJECT

public:
   CoaFrame(QWidget *parent = 0);
protected:
   void drawFrame(QPainter *);

};



#endif
