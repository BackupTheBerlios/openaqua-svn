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



#ifndef __AB_Connection_h__
#define __AB_Connection_h__

#include <QObject>
#include <QString>
#include <QPointer>
#include <QVariant>
//#include "ab_datasource.h"


class ODABAClient;
namespace AquaBase
{
   class AB_Error;

   /**


   @class AB_Connection
   @brief Provides Connection to a ODABA Server

   To run client server applications you must create a ODABA client instance.
   To support several connections to different servers you can create one
   or more clients within your application.

   When connecting to different servers you must create one client
   for each server. You can open several clients in an application.
   The first client, however, is considered to be the main client.
   The main client should be the last client closed in an application.
   After closing the main client you can open another main client.
   Since there is no hierarchy defined between clients the system will not check.


   */
   class AB_Connection: public QObject
   {
      Q_OBJECT

   public:
      //!@brief Constructor
      AB_Connection( QObject *const parent = 0 );
      virtual ~AB_Connection();

      //!@brief create an connection
      bool Connect ( const QString& server_name, unsigned int host_port = 6123, const QString& cache = "" );

      //!@brief the very same like Connect (at this moment!)
      bool Initialize ( const QString& server_name, unsigned int host_port = 6123, const QString& cache = "" );

      //!@brief Close an open connection
      bool Disconnect ( );

      //!@brief is the client connected to a server
      bool IsConnected ( );

      //!@brief return the hostname of the connected server
      const QString GetHost ( ) const;

      //!@brief return the Port number of the connected server
      unsigned int GetPort ( ) const;

      QPointer<AquaBase::AB_Error>GetDBError ( );

      //!@brief Ping
      const QString SayHello ( const QString& );

      //!@brief return a Client Connection object
      AB_Connection *const createClient();
   protected:

      bool Open ( const QString& inipath );
      void Initialize ( const QString& inipath );

      bool Exist ( const QString& cpath );
      bool Close ( );


      QString GetDataSource ( int indx0 );

      bool SetServerVariable ( const QString& var_name, const QString& var_string );
      QString GetServerVariable ( const QString& var_name );

   private:
      friend class AB_DataSource;
      ODABAClient *m_client;
      AB_Connection( ODABAClient * const, QObject *const parent = 0);//for internal use only
      AB_Connection(const AB_Connection& p); //doesn't exist
      AB_Connection &operator= ( AB_Connection &client_ref );//doesn't exist

   private:
      operator bool ( );

   };
};
#endif //__AB_Connection_h__
