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



#ifndef __odabaclient_cpp__
#define __odabaclient_cpp__

#include <QObject>
#include <QString>


class ODABAClient; //forward declaration for the original odabas client object

/**

@class OdabaClient
@brief simplyfied interface for odaba access

*/

class OdabaClient: public QObject  {
Q_OBJECT
private:


public:
   OdabaClient(QObject *const parent=0);
   //ODABAClient (char *inipath, char *application_name=NULL, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
   //ODABAClient ( );
   //ODABAClient (const ODABAClient &client_refc );
   //ODABAClient (CClient *cclient_ptr );
   virtual ~OdabaClient();

   bool Open (const QString& inipath);
   void Initialize (const QString& inipath);
   bool KillClient (int client_id, int wait_sec=300, bool send_message=true );


   bool Connect (const QString& server_name, unsigned int host_port=6123, const QString& cache = "" );
   void Disconnect ( );
   bool IsConnected ( );
   int GetConnectionID ( );
   const QString GetHost ( ) const;
   unsigned int GetPort ( ) const;

   bool Exist (const QString& cpath );
   bool Close ( );
   bool BackupDB (const QString& cpath, const QString& target, const unsigned int wait_time = 300);
   //bool CheckDB (const QString& dict_path, const QString& cpath, CheckOptions check_opts, char *source, int32 wait_sec=300 );
   bool PackDatabase (const QString& cpath, const QString& temp_path=QString() );
   bool RestoreDB (const QString& cpath, const QString& source, int wait_sec=300 );


   QString GetDataSource (int indx0 );
   //QString GetDBError ( );
   bool ShutDown (const bool close_system=true );
   bool StartPause (const int wait_sec=300 );
   void StopPause ( );


   bool SetServerVariable (const QString& var_name, const QString& var_string );
   QString GetServerVariable (const QString& var_name );

   bool StatDisplay (const QString& dbpath, const QString& ppath );
   bool SysInfoDisplay (const QString& dbpath, const QString& ppath );
   bool DictDisplay (const QString& dbpath, const QString& ppath );


private:
   ODABAClient    *m_client;
   QString         m_host_name;
   unsigned int    m_host_port;

private:
   operator bool ( );
   OdabaClient &operator= (OdabaClient &client_ref );
   //CClient *GetClientPtr ( ) const;
   //logical Open (CClient *cclient_ptr );
   //logical Open (const ODABAClient &client_refc );

};


#endif //__odabaclient_cpp__

#if 0

public     :                                     logical CloseDataSource (DBObjectHandle &dbo_handle );
public     :         OPI7ImpExp                  QString SayHello (void *testdata, uint32 size );
public     :                                     DBObjectHandle *OpenDataSource (char *datasource_name, PIACC accopt );
public     :         OPI7ImpExp                  logical SendClientMessage (int32 client_id, char *mtext, char *mtitle=NULL, char mtype=0 );


#endif