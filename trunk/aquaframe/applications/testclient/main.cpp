#include "workbench.h"

#include <CoaApplication>
#include <cassert>
#include <CoaGuiThreadMaker>


#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
   CoaApplication *app = new CoaApplication("T-Mobile", "testclient", argc, argv, true);

   assert(app);
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

