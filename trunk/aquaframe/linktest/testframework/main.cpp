#include <CoaApplication>
#include <cassert>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
   cout << "ITS BEGINS" <<endl;
   
   CoaApplication *app = new CoaApplication("T-Mobile", "LinkTest", argc, argv);
   assert(app);
   delete app;

   cout << "ITS COMES to an end" <<endl;

   return 0;
}
