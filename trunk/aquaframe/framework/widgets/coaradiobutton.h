#ifndef __CoaRadioButton_h_
#define __CoaRadioButton_h_

#include <QRadioButton>


class CoaRadioButton: public QRadioButton
{
Q_OBJECT

public:
   CoaRadioButton ( QWidget * parent = 0 );
   CoaRadioButton ( const QString & text, QWidget * parent = 0 );
   virtual ~CoaRadioButton();
    
};

#endif
