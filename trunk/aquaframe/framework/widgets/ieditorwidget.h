#ifndef __IoaEditorWidget_h__
#define __IoaEditorWidget_h__


#include <QObject>

class IoaEditorWidget: public QObject
{
Q_OBJECT
public:
   IoaEditorWidget(){};
   virtual ~IoaEditorWidget(){};
//   virtual void copy () = 0;
//   virtual void cut () = 0;
};


#endif //__IoaEditorWidget_h__
