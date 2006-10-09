#ifndef __CoaToolButton_h__
#define __CoaToolButton_h__

#include <QToolButton>


class CoaToolButton: public QToolButton 
{
   Q_OBJECT
public:
  CoaToolButton ( QWidget * parent = 0 );
  virtual ~CoaToolButton ();

  
};

#endif //__CoaToolButton_h__


