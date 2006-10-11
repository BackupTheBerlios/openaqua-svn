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
#include <QDataStream>


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


#define MAKE_LOC_STRING( qstr , cstr )    char cstr[qstr.size()+200];  strncpy(cstr, qstr.toLocal8Bit().constData(), qstr.size()+200); cstr[qstr.size()+200]='\0';

#include <iostream>
using namespace std;

/**



*/


AquaBase::AB_Connection::AB_Connection( ODABAClient * const c, QObject *const parent)
      : QObject( parent )
{
   if (c == 0) {
      m_client = new ODABAClient();
   } else {
      m_client = new ODABAClient (*c);
   }


}

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
   //cerr << "Connect to server=" << sn << endl;
   //cerr << "Connect to port=" << host_port << endl;
   return (!m_client -> Connect( sn, host_port, cn ));
}


bool AquaBase::AB_Connection::Initialize ( const QString& server_name, unsigned int host_port, const QString& cache )
{
   return Connect(server_name, host_port, cache);
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
   m_client->Disconnect();
   return true;
}




const QString AquaBase::AB_Connection::GetHost ( ) const
{
   if ( m_client->GetHost ( ) == 0 )
      return "";
   else
      return m_client->GetHost ( );

}


unsigned int AquaBase::AB_Connection::GetPort ( ) const
{
   m_client->GetPort ( );
}





bool AquaBase::AB_Connection::Exist ( const QString& cpath )
{
   MAKE_LOC_STRING( cpath , c );
   logical r = m_client->Exist( c );
   assert( cpath == c );
   return ( r == 0 ? true : false );

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














QPointer<AquaBase::AB_Error>AquaBase::AB_Connection::GetDBError ( )
{
   return ( new AquaBase::AB_Error( this, m_client->GetDBError () ) );
}


/**
Send a value to the Odaba Server and reads the returned value (which should be the same)
Its the counterpart of the Unix echo command

The data will NOT be encoded.
*/
const QString AquaBase::AB_Connection::SayHello ( const QString& s )
{
   MAKE_LOC_STRING( s , ss );
   return ( m_client->SayHello( ss, s.size() ) );
}

/**

With this function can You get a client object

*/
AquaBase::AB_Connection::AB_Connection *const AquaBase::AB_Connection:: createClient()
{
   return new AB_Connection(m_client, this);
}

#if 0
OdabaDBObjectHandle *AquaBase::AB_Connection::OpenDataSource ( const QString& datasource_name )
{
   return new OdabaDBObjectHandle( this );
}

#endif
