#include <CoaApplication>
#include "travelworkbench.h"
#include <cassert>
#include <CoaGuiThreadMaker>
//#include <CoaStyle>



#include <QMainWindow>

int main(int argc, char *argv[])
{

   //CoaStyle style;
   //CoaApplication::setStyle(&style);
   CoaApplication *app = new CoaApplication("T-Mobile", "oatravel", argc, argv, true);
   int i = -1;
   {
      CoaGuiThreadMaker *threadmaker = new CoaGuiThreadMaker(app);
      TravelWorkbench *workbench = new TravelWorkbench(threadmaker);
      workbench->initialize();
      i = app->exec();
      delete workbench;
      delete threadmaker;
   }
   delete app;

   return i;
}

