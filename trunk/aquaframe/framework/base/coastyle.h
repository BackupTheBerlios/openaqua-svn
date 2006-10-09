#ifndef __CoaStyle_h__
#define __CoaStyle_h__

#include <QCommonStyle>

class CoaStyle: public QStyle
{
Q_OBJECT
public:
   CoaStyle ();
   virtual ~CoaStyle ();

   //virtual void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

};

#endif //__CoaStyle_h__

