/***************************************************************************
 *   Copyright (C) 2006 by Andrey Behrens   *
 *   Andrey.Behrens@openaqua.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



#include <iostream>
using namespace std;
#include <odabaclient.h>
#include <QApplication>
#include <QString>

bool ConnectToServer(OdabaClient& );
bool UnconnectFromServer(OdabaClient& );

int main(int argc, char *argv[])
{
   bool result = true;
   
   //create a simple Qt Application (without event loop in this case)
   QCoreApplication app( argc,  argv );
   
   //create a client
   OdabaClient client;
   
   //do some jobs
   cout << "begin test ..." <<endl;
   result = ConnectToServer(client);
   if (result) result = UnconnectFromServer(client);
   
   if (result == true){
      cout << "end test without errors" <<endl;
      return 0;
   } else {
      cout << "end test with errors" <<endl;
      return -1;
   }
}


bool ConnectToServer(OdabaClient& client)
{
   cout << "Connect to localhost:6123: ";
   if (client.Connect ("localhost", 6123) == true)
   {
      cout << "success" <<endl; 
      return true;
   } else {
      cout << "no success" <<endl; 
      return false;
   }
}

bool UnconnectFromServer(OdabaClient& client)
{
   cout << "Unconnect: Successfull" <<endl;
   client.Disconnect();
   return true;
}
