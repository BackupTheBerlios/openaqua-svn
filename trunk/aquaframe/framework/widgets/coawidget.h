#ifndef __CoaWidget_h_
#define __CoaWidget_h_

#include <QWidget>


class CoaWidget: public QWidget
{
Q_OBJECT

public:
   CoaWidget ( QWidget * const parent = 0, Qt::WFlags f = 0 );
   virtual ~CoaWidget();

};

#endif

