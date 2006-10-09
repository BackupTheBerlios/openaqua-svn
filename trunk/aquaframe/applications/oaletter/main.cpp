#include <CoaApplication>
#include "letterworkbench.h"
#include <cassert>
#include <CoaGuiThreadMaker>


#include <QMainWindow>

int main(int argc, char *argv[])
{

   CoaApplication *app = new CoaApplication("T-Mobile", "OpenAqua Letter", argc, argv, true);
   int i = -1;
   {
      CoaGuiThreadMaker *threadmaker = new CoaGuiThreadMaker(app);
      LetterWorkbench *workbench = new LetterWorkbench(threadmaker);
      workbench->initialize();
      i = app->exec();
      delete workbench;
      delete threadmaker;
   }
   delete app;

   return i;
}

