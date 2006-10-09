#include <CoaApplication>
#include <cassert>

int main(int argc, char *argv[])
{

   CoaApplication *app = new CoaApplication("T-Mobile", "LinkTest", argc, argv);
   delete app;

   return -1;
}
