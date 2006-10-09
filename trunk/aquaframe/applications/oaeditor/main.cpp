#include <CoaApplication>
//#include <CoaWorkbench>
//#include <CoaGuiThreadMaker>
#include <cassert>
//#include "mainwindow.h"


int main(int argc, char *argv[])
{

   Q_INIT_RESOURCE(oaeditor);

   CoaApplication *app = new CoaApplication("T-Mobile", "OpenAqua Xml-Editor", argc, argv);
   
   int i = -1;
#if 0   
   {
      CoaGuiThreadMaker threadmaker(app);
      CoaWorkbench workbench(&threadmaker);
      workbench.registerMainWindow(new MainWindow());
      i = app->exec();
   }
#endif
   delete app;
   return i;
}
