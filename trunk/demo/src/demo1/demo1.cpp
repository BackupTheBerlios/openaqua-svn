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
#include <AquaBase.h>
#include <QApplication>
#include <QString>

const QString sBEGIN = "TestCase: ";
const QString sOK    = " Ok ";
const QString sNOK    = " Not Ok ";

std::ostream& operator<< (std::ostream& out, const QString& string)
{

   out << string.toUtf8().data();
   return out;
}


bool printError(AquaBase::AB_Connection& );
bool ConnectToServer(AquaBase::AB_Connection& );
bool IsConnected(AquaBase::AB_Connection& );
bool UnconnectFromServer(AquaBase::AB_Connection& );
bool GetConnectionID(AquaBase::AB_Connection& );
bool SayHello(AquaBase::AB_Connection& );

int main(int argc, char *argv[])
{
   bool result = true;

   //create a simple Qt Application (without event loop in this case)
   QCoreApplication app( argc,  argv );

   //create a client
   AquaBase::AB_Connection client;

   //do some jobs
   cout << "begin test ..." <<endl;
   result = GetConnectionID(client ); //show error

   if (result) result = ConnectToServer(client); else printError(client);
   if (result) result = IsConnected(client); else printError(client);
   if (result) result = GetConnectionID(client ); else printError(client);
   if (result) result = SayHello(client ); else printError(client);
   if (result) result = UnconnectFromServer(client);
   if (result) result = GetConnectionID(client ); //should show error

   if (result == true){
      cout << "end test without errors" <<endl;
      return 0;
   } else {
      cout << "end test with errors" <<endl;
      return -1;
   }
}


bool ConnectToServer(AquaBase::AB_Connection& client)
{
   cout  << "TestCase: Connect to localhost:6123: ";
   if (client.Connect ("localhost", 6123) == true)
   {
      cout << "success" <<endl;
      return true;
   } else {
      cout << "no success" <<endl;
      return false;
   }
}

bool IsConnected(AquaBase::AB_Connection& client)
{
   cout << "TestCase: Is Connected: ";
   if (client.IsConnected()) cout << "Ok";
   else cout << "Not Ok";
   cout << endl;
   return client.IsConnected();

}

bool GetConnectionID(AquaBase::AB_Connection& client)
{
   cout << "TestCase: GetConnectionID: " << client.GetConnectionID() << endl;
   return true;
}

bool UnconnectFromServer(AquaBase::AB_Connection& client)
{
   cout << "TestCase: Unconnect: Successfull" <<endl;
   client.Disconnect();
   return true;
}



bool SayHello(AquaBase::AB_Connection& client)
{
   cout << "TestCase: SayHello('hello') -> " << client.SayHello("hallo") <<endl;
   return true;
}

bool printError(AquaBase::AB_Connection& client)
{
   AquaBase::AB_Error *error = client.GetDBError ( );
   cout << "printError: " << error->title() << '(' << error->description()<< ')'<< endl;
   return true;
}