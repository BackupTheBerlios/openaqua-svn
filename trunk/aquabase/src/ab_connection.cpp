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

#include "ab_connection.h"
#include "ab_error.h"
#include <QApplication>


   //for the Connection
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

#include <iostream>
using namespace std;

/**



*/

AquaBase::AB_Connection::AB_Connection( QObject *const parent )
      : QObject( parent )
{
   m_client = new ODABAClient();
}




AquaBase::AB_Connection::~AB_Connection()
{
   delete m_client;
}


bool AquaBase::AB_Connection::Open ( const QString& inipath )
{
   //MAKE_LOC_STRING( server_name , sn );
   MAKE_LOC_STRING( inipath , ip );
   MAKE_LOC_STRING( qApp->applicationDirPath() , pp );
   MAKE_LOC_STRING( qApp->applicationName() , an );

   logical r = m_client->Open( ip, an, pp );

   assert( qApp->applicationName() == an );
   assert( qApp->applicationDirPath() == pp );
   assert( inipath == ip );
   return ( r == 0 ? true : false );
}




void AquaBase::AB_Connection::Initialize ( const QString& inipath )
{
   //MAKE_LOC_STRING( server_name , sn );
   MAKE_LOC_STRING( inipath , ip );
   MAKE_LOC_STRING( qApp->applicationDirPath() , pp );
   MAKE_LOC_STRING( qApp->applicationName() , an );

   m_client->Initialize( ip, an, pp );

   assert( qApp->applicationName() == an );
   assert( qApp->applicationDirPath() == pp );
   assert( inipath == ip );

}


bool AquaBase::AB_Connection::KillClient ( int client_id, int wait_sec, bool send_message )
{
   logical s = TRUE;
   if ( send_message == false )
      s = FALSE;
   logical r = m_client->KillClient ( client_id, wait_sec, s );
   return ( r == NO ? true : false );
}

/**

This function establishs a connection to the server.
When not connecting the cleint to a server the client runs in local mode.
When running in local mode all resources are located on th client machine.

When being connected to a server you can access ressources located on the
server or on the local machine by setting the "local_resources"-parameter
when constructing dictionary or database handles.

When connecting several times for closing the connection you must disconnect
as often as you have connected to the server. When the client is connected
once it cannot be connected to another server until the open connection is closed.

@param server_name is the IP adress or a hostname of a server
@param host_port is the port number of a server. Default is 6123
@param cache ????
@result true - connection established

@warning The hostname and -port could be changed!
*/

bool AquaBase::AB_Connection::Connect ( const QString& server_name, unsigned int host_port, const QString& cache )
{
   if ( IsConnected ( ) == true )
      Disconnect();

   //make char array from servername;
   MAKE_LOC_STRING( server_name , sn );
   MAKE_LOC_STRING( cache , cn );

   //connect
   if ( m_client -> Connect( sn, host_port, cn ) == YES )
   {
      assert( server_name == sn );
      assert( cache == cn );

      m_host_name = "";
      m_host_port = 0;
      return false;
   }
   else
   {
      assert( server_name == sn );
      assert( cache == cn );

      m_host_name = sn;
      m_host_port = host_port;
      return true;
   }
}

bool AquaBase::AB_Connection::IsConnected ( )
{
   return ( m_client->IsConnected() );
}




/**

This method close the an existing connection

@warning Please make shure that all resources are closed before disconnecting
the client. Disconnecting the client before closing all opened handles may
cause problems and not all changes are stored.


@result true - in any cases
*/
bool AquaBase::AB_Connection::Disconnect ( )
{
   //const bool result = ShutDown();
   const bool result = true;
   m_client->Disconnect();
   return result;
}


/**

@result is 0 - what ever happens

*/
int AquaBase::AB_Connection::GetConnectionID ( )
{
   return m_client->GetConnectionID ();
}

const QString AquaBase::AB_Connection::GetHost ( ) const
{
   return m_host_name;
}


unsigned int AquaBase::AB_Connection::GetPort ( ) const
{
   return m_host_port;
}


bool AquaBase::AB_Connection::BackupDB ( const QString& cpath, const QString& target, const unsigned int wait_sec )
{
   MAKE_LOC_STRING( cpath , c );
   MAKE_LOC_STRING( target , t );


   //logical BackupDB (char *cpath, char *target, int32 wait_sec=300 );
   logical r = m_client->BackupDB( c, t, wait_sec );
   assert( cpath == c );
   assert( target == t );

   return ( r == 0 ? true : false );

}


/**

Usually the last Connection handle referring to the client will
shut down the client when being destructed. In some cases, e.g.
when creating a client with an ini-file and using system services as
data catalogue or error logs, some system references are still active
and referring to the main client. To be sure that the main client is closed
properly you should use the ShutDown() function before destructing the client.
Make sure that there are no other references to the client in your application anymore.

The function will delete all resources associated with the client and close
the client. When the client is the default or main client, which has
been created automatically, the function will close the main client.

@result true = success

*/

bool AquaBase::AB_Connection::ShutDown ( const bool close_system )
{
   if ( close_system )
   {
      if ( m_client->ShutDown ( YES ) == YES )
         return false;
      else
         return true;
   }
   else
   {
      if ( m_client->ShutDown ( NO ) == YES )
         return false;
      else
         return true;
   }
}


bool AquaBase::AB_Connection::Exist ( const QString& cpath )
{
   MAKE_LOC_STRING( cpath , c );
   logical r = m_client->Exist( c );
   assert( cpath == c );
   return ( r == 0 ? true : false );

}

bool AquaBase::AB_Connection::StartPause ( const int wait_sec )
{
   m_client->StartPause( wait_sec );
}



void AquaBase::AB_Connection::StopPause ( )
{
   m_client->StopPause();
}


QString AquaBase::AB_Connection::GetDataSource ( int indx0 )
{
   return m_client->GetDataSource ( indx0 );
}


bool AquaBase::AB_Connection::SetServerVariable ( const QString& var_name, const QString& var_string )
{
   MAKE_LOC_STRING( var_name , n );
   MAKE_LOC_STRING( var_string , s );

   logical r = m_client->StatDisplay( n, s );
   assert( var_name == n );
   assert( var_string == s );

   return ( r == 0 ? true : false );
}


QString AquaBase::AB_Connection::GetServerVariable ( const QString& var_name )
{
   MAKE_LOC_STRING( var_name , n );
   QString r = m_client->GetServerVariable( n );
   assert( var_name == n );
   return r;
}




bool AquaBase::AB_Connection::StatDisplay ( const QString& dbpath, const QString& ppath )
{
   MAKE_LOC_STRING( dbpath , d );
   MAKE_LOC_STRING( ppath , p );

   logical r = m_client->StatDisplay( d, p );
   assert( dbpath == d );
   assert( ppath == p );

   return ( r == 0 ? true : false );

}






bool AquaBase::AB_Connection::SysInfoDisplay ( const QString& dbpath, const QString& ppath )
{
   MAKE_LOC_STRING( dbpath , d );
   MAKE_LOC_STRING( ppath , p );

   logical r = m_client->SysInfoDisplay( d, p );
   assert( dbpath == d );
   assert( ppath == p );

   return ( r == 0 ? true : false );

}

bool AquaBase::AB_Connection::DictDisplay ( const QString& dbpath, const QString& ppath )
{
   MAKE_LOC_STRING( dbpath , d );
   MAKE_LOC_STRING( ppath , p );

   logical r = m_client->DictDisplay( d, p );
   assert( dbpath == d );
   assert( ppath == p );

   return ( r == 0 ? true : false );

}


bool AquaBase::AB_Connection::PackDatabase ( const QString& cpath, const QString& temp_path )
{
   MAKE_LOC_STRING( cpath , c );
   MAKE_LOC_STRING( temp_path , t );

   logical r;
   if ( temp_path == QString() )
   {
      r = m_client->PackDatabase( c, 0 );
      assert( cpath == c );

   }
   else
   {
      r = m_client->PackDatabase( c, t );
      assert( cpath == c );
      assert( temp_path == t );
   }

   return ( r == 0 ? true : false );
}



bool AquaBase::AB_Connection::RestoreDB ( const QString& cpath, const QString& source, int wait_sec )
{
   MAKE_LOC_STRING( cpath , c );
   MAKE_LOC_STRING( source , s );
   logical r = m_client->RestoreDB( c, s, wait_sec );
}

QPointer<AquaBase::AB_Error>AquaBase::AB_Connection::GetDBError ( )
{
   return (new AquaBase::AB_Error(this, m_client->GetDBError ()));
}


/**
*/
const QString AquaBase::AB_Connection::SayHello (const QString& s)
{
   MAKE_LOC_STRING( s , ss );
   return (m_client->SayHello(ss, s.size()));
}

#if 0
OdabaDBObjectHandle *AquaBase::AB_Connection::OpenDataSource ( const QString& datasource_name )
{
   return new OdabaDBObjectHandle( this );
}

#endif