#ifndef __CoaComboBox_h_
#define __CoaComboBox_h_

#include <QComboBox>


class CoaComboBox: public QComboBox
{
Q_OBJECT

public:
   CoaComboBox ( QWidget * parent = 0);
   virtual ~CoaComboBox();


public slots:
   void emitDataChanged ();

signals:
   void dataChanged ( QWidget *itself);

};

#endif

