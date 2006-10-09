#include "letterobject.h"
#include <CoaDebug>
#include <CoaFormFactory>


LetterObject::LetterObject()
:CoaApplicationWindow("LetterObject")
{
   BEGIN;
   createMainWindow();
}


LetterObject::~LetterObject()
{
   BEGIN;
}


void LetterObject::createMainWindow()
{
   BEGIN;
   Q_INIT_RESOURCE(oaletter);
}
