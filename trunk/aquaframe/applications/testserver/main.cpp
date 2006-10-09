#include "dialog.h"
#include <CoaApplication>
#include <cassert>
#include <CoaGuiThreadMaker>


int main(int argc, char *argv[])
{

   CoaApplication *app = new CoaApplication("T-Mobile", "testserver", argc, argv, true);
   int i = -1;
   {
      CoaGuiThreadMaker *threadmaker = new CoaGuiThreadMaker(app);

      Dialog dialog;
      dialog.show();
      i = dialog.exec();
      
      delete threadmaker;
   }
   delete app;

   return i;
}


