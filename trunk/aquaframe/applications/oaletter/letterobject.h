#ifndef __LetterObject_h__
#define __LetterObject_h__

#include <CoaBusinessObject>
#include <CoaApplicationWindow>


class LetterObject: public CoaApplicationWindow
{
Q_OBJECT


public:
   LetterObject();
   virtual ~LetterObject();
   virtual void createMainWindow();

private:


};

#endif //__LetterObject_h__


