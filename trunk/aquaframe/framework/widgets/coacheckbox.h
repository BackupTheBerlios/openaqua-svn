#ifndef __CoaCheckBox_h_
#define __CoaCheckBox_h_

#include <QCheckBox>


class CoaCheckBox: public QCheckBox
{
Q_OBJECT

public:
   CoaCheckBox ( QWidget * parent = 0 );
   CoaCheckBox ( const QString & text, QWidget * parent = 0 );
   virtual ~CoaCheckBox();
    
};

#endif
