#ifndef __CoaPushButton_h_
#define __CoaPushButton_h_

#include <QPushButton>


class CoaPushButton: public QPushButton
{
Q_OBJECT

public:
   CoaPushButton ( QWidget * parent = 0 );
   CoaPushButton ( const QString & text, QWidget * parent = 0 );
   CoaPushButton ( const QIcon & icon, const QString & text, QWidget * parent = 0 );
   virtual ~CoaPushButton();
    
};

#endif
