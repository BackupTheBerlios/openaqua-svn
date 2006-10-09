/***************************************************************************
*   Copyright (C) 2006 by Andrey Behrens   *
*   Andrey.Behrens@openaqua.de   *
*   *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or    *
*   (at your option) any later version.*
*   *
*   This program is distributed in the hope that it will be useful,*
*   but WITHOUT ANY WARRANTY; without even the implied warranty of *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  *
*   GNU General Public License for more details.    *
*   *
*   You should have received a copy of the GNU General Public License    *
*   along with this program; if not, write to the   *
*   Free Software Foundation, Inc.,   *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.     *
***************************************************************************/

#include "odabaclient.h"
#include <QApplication>

//for the ODABAClient
#include  <csos4mac.h>
#include  <igvtx.h>
#include  <igvts.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <codaba2.h>

#include  <pdefault.h>
#include  <sObjectReferenceHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sCClient.hpp>
#include  <cApplicationTypes.h>


#define MAKE_LOC_STRING( qstr , cstr )    char cstr[255];  strncpy(cstr, qstr.toLocal8Bit().constData(), 254); cstr[255]='\0';



OdabaClient::OdabaClient( QObject *const parent )
      : QObject( parent )
{
   m_client = new ODABAClient();
}




OdabaClient::~OdabaClient()
{
   delete m_client;
}


bool OdabaClient::Open (const QString& inipath )
{
   //MAKE_LOC_STRING( server_name , sn );
   MAKE_LOC_STRING( inipath , ip );
   MAKE_LOC_STRING( qApp->applicationDirPath() , pp );
   MAKE_LOC_STRING( qApp->applicationName() , an );

   logical r = m_client->Open(ip, an, pp);

   assert( qApp->applicationName() == an );
   assert( qApp->applicationDirPath() == pp );
   assert(inipath == ip);
   return (r==0?true:false);
}




void OdabaClient::Initialize (const QString& inipath )
{
   //MAKE_LOC_STRING( server_name , sn );
   MAKE_LOC_STRING( inipath , ip );
   MAKE_LOC_STRING( qApp->applicationDirPath() , pp );
   MAKE_LOC_STRING( qApp->applicationName() , an );

   m_client->Initialize(ip, an, pp);

   assert( qApp->applicationName() == an );
   assert( qApp->applicationDirPath() == pp );
   assert(inipath == ip);

}


bool OdabaClient::KillClient (int client_id, int wait_sec, bool send_message)
{
   logical s = 0;
   if (send_message == false) s = FALSE;
   logical r = m_client->KillClient (client_id, wait_sec, s);
   return (r==0?true:false);
}

/**

@warning The hostname and -port could be changed!
*/

bool OdabaClient::Connect (const QString& server_name, unsigned int host_port, const QString& cache )
{
   if (IsConnected ( ) == true) Disconnect();

   #warning  "non const string use should be fixed"

   //make char array from servername;
   MAKE_LOC_STRING( server_name , sn );
   MAKE_LOC_STRING( cache , cn );

   //connect
   if (m_client -> Connect(sn, host_port, cn) != 0){
      assert(server_name == sn);
      assert(cache == cn);

      m_host_name = "";
      m_host_port = 0;
      return false;
   } else {
      assert(server_name == sn);
      assert(cache == cn);

      m_host_name = sn;
      m_host_port = host_port;
      return true;
   }
}

bool OdabaClient::IsConnected ( )
{
   if (m_client->IsConnected() == 0)
      return true;
   else
      return false;
}



void OdabaClient::Disconnect ( )
{
   m_client->Disconnect();
}

int OdabaClient::GetConnectionID ( )
{
   return m_client->GetConnectionID ();
}

const QString OdabaClient::GetHost ( ) const
{
   return m_host_name;
}


unsigned int OdabaClient::GetPort ( ) const
{
   return m_host_port;
}


bool OdabaClient::BackupDB (const QString& cpath, const QString& target, const unsigned int wait_sec )
{
   MAKE_LOC_STRING( cpath , c );
   MAKE_LOC_STRING( target , t );


   //logical BackupDB (char *cpath, char *target, int32 wait_sec=300 );
   logical r = m_client->BackupDB(c,t,wait_sec);
   assert(cpath == c);
   assert(target == t);

   return (r==0?true:false);

}

bool OdabaClient::ShutDown (const bool close_system)
{
   if (close_system) {
      m_client->ShutDown (YES);
   } else {
      m_client->ShutDown (NO);
   }
}


bool OdabaClient::Exist (const QString& cpath )
{
   MAKE_LOC_STRING( cpath , c );
   logical r = m_client->Exist(c);
   assert(cpath == c);
   return (r==0?true:false);

}

bool OdabaClient::StartPause (const int wait_sec )
{
   m_client->StartPause(wait_sec);
}



void OdabaClient::StopPause ( )
{
   m_client->StopPause();
}


QString OdabaClient::GetDataSource (int indx0 )
{
   return m_client->GetDataSource (indx0);
}


bool OdabaClient::SetServerVariable (const QString& var_name, const QString& var_string )
{
   MAKE_LOC_STRING( var_name , n );
   MAKE_LOC_STRING( var_string , s );

   logical r = m_client->StatDisplay(n, s);
   assert(var_name == n);
   assert(var_string == s);

   return (r==0?true:false);
}


QString OdabaClient::GetServerVariable (const QString& var_name )
{
   MAKE_LOC_STRING( var_name , n );
   QString r = m_client->GetServerVariable(n);
   assert(var_name == n);
   return r;
}




bool OdabaClient::StatDisplay (const QString& dbpath, const QString& ppath )
{
   MAKE_LOC_STRING( dbpath , d );
   MAKE_LOC_STRING( ppath , p );

   logical r = m_client->StatDisplay(d, p);
   assert(dbpath == d);
   assert(ppath == p);

   return (r==0?true:false);

}






bool OdabaClient::SysInfoDisplay (const QString& dbpath, const QString& ppath )
{
   MAKE_LOC_STRING( dbpath , d );
   MAKE_LOC_STRING( ppath , p );

   logical r = m_client->SysInfoDisplay(d, p);
   assert(dbpath == d);
   assert(ppath == p);

   return (r==0?true:false);

}

bool OdabaClient::DictDisplay (const QString& dbpath, const QString& ppath )
{
   MAKE_LOC_STRING( dbpath , d );
   MAKE_LOC_STRING( ppath , p );

   logical r = m_client->DictDisplay(d, p);
   assert(dbpath == d);
   assert(ppath == p);

   return (r==0?true:false);

}


bool OdabaClient::PackDatabase (const QString& cpath, const QString& temp_path)
{
   MAKE_LOC_STRING( cpath , c );
   MAKE_LOC_STRING( temp_path , t );

   logical r;
   if (temp_path == QString()){
      r = m_client->PackDatabase(c, 0);
      assert(cpath == c);

   } else {
      r = m_client->PackDatabase(c, t);
      assert(cpath == c);
      assert(temp_path == t);
   }

   return (r==0?true:false);
}
bool OdabaClient::RestoreDB (const QString& cpath, const QString& source, int wait_sec )
{
   MAKE_LOC_STRING( cpath , c );
   MAKE_LOC_STRING( source , s );
   logical r = m_client->RestoreDB(c, s, wait_sec);
}


//QString OdabaClient::GetDBError ( )
//{
//   return m_client->GetDBError();
//}