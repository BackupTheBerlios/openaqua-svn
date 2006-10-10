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



#ifndef __Connection_cpp__
#define __Connection_cpp__

#include <QObject>
#include <QString>
#include <QPointer>
#include "AquaBase.h"

/**

@class Connection

To run client server applications you must create a ODABA client instance.
 To support several connections to different servers you can create one
 or more clients within your application.

When connecting to different servers you must create one client
for each server. You can open several clients in an application.
The first client, however, is considered to be the main client.
The main client should be the last client closed in an application.
After closing the main client you can open another main client.
Since there is no hierarchy defined between clients the system will not check.



@brief simplyfied interface for odaba access

*/

class ODABAClient;
namespace AquaBase
{
   class AB_Error;
   class AB_Connection: public QObject
   {
      Q_OBJECT

   public:
      AB_Connection( QObject *const parent = 0 );
      //Connection (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
      //Connection ( );
      //Connection (const Connection &client_refc );
      //Connection (CClient *cclient_ptr );
      virtual ~AB_Connection();
      bool Connect ( const QString& server_name, unsigned int host_port = 6123, const QString& cache = "" );
      bool Disconnect ( );
      bool IsConnected ( );
      int GetConnectionID ( );
      bool ShutDown ( const bool close_system = true );
      QPointer<AquaBase::AB_Error>GetDBError ( );
      //OdabaDBObjectHandle *OpenDataSource ( const QString& datasource_name );

      //!@brief simple Ping
      const QString SayHello (const QString&);


   protected:

      bool Open ( const QString& inipath );
      void Initialize ( const QString& inipath );
      bool KillClient ( int client_id, int wait_sec = 300, bool send_message = true );

      const QString GetHost ( ) const;
      unsigned int GetPort ( ) const;

      bool Exist ( const QString& cpath );
      bool Close ( );
      bool BackupDB ( const QString& cpath, const QString& target, const unsigned int wait_time = 300 );
      //bool CheckDB (const QString& dict_path, const QString& cpath, CheckOptions check_opts, char *source, int32 wait_sec=300 );
      bool PackDatabase ( const QString& cpath, const QString& temp_path = QString() );
      bool RestoreDB ( const QString& cpath, const QString& source, int wait_sec = 300 );


      QString GetDataSource ( int indx0 );
      //QString GetDBError ( );
      bool StartPause ( const int wait_sec = 300 );
      void StopPause ( );


      bool SetServerVariable ( const QString& var_name, const QString& var_string );
      QString GetServerVariable ( const QString& var_name );

      bool StatDisplay ( const QString& dbpath, const QString& ppath );
      bool SysInfoDisplay ( const QString& dbpath, const QString& ppath );
      bool DictDisplay ( const QString& dbpath, const QString& ppath );


   private:
      ODABAClient *m_client;
      QString m_host_name;
      unsigned int m_host_port;

   private:
      operator bool ( );
      AB_Connection &operator= ( AB_Connection &client_ref );
      //CClient *GetClientPtr ( ) const;
      //logical Open (CClient *cclient_ptr );
      //logical Open (const Connection &client_refc );

   };
};
#endif //__Connection_cpp__
