#include "workbench.h"

#include <CoaApplication>
#include <cassert>
#include <CoaGuiThreadMaker>


int main(int argc, char *argv[])
{

   CoaApplication *app = new CoaApplication("T-Mobile", "actioneditor", argc, argv, true);
   int i = -1;
   {
      CoaGuiThreadMaker *threadmaker = new CoaGuiThreadMaker(app);
      Workbench *workbench = new Workbench(threadmaker);
      workbench->initialize();
      i = app->exec();
      delete workbench;
      delete threadmaker;
   }
   delete app;

   return i;
}

