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



#ifndef __AB_DataSource_h__
#define __AB_DataSource_h__

#include <QObject>
#include <QString>
#include "ab_connection.h"

class DataSourceHandle;
namespace AquaBase
{

   class AB_DataSource: public QObject
   {
      Q_OBJECT

   public:
      AB_DataSource( AB_Connection& , QObject *const parent = 0 );
      virtual ~AB_DataSource();

      bool Open();

      /**
      */
      bool BeginTransaction ( );
      bool RollBack ( );
      bool CommitTransaction ( );

   private:
      DataSourceHandle *m_client;
      AB_Connection& m_connection;

   private:
      operator bool ( );
      AB_DataSource &operator= ( AB_DataSource & );
      AB_DataSource();

   };
};
#endif //__AB_DataSource_h__

#if 0


ODABAClient client;                                                    //
DictionaryHandle dictionary;                                                //
DatabaseHandle reshandle;                                                 //
DatabaseHandle dbhandle;                                                  //
DBObjectHandle object_handle;                                             //
PropertyHandle *extent_pi;                                                 //
char data_source[ 41 ];                                           //
char server_name[ 64 ];                                           //
int32 server_port;                                               //
char connection_name[ 256 ];                                      //
char dict_path[ 256 ];                                            //
char res_path[ 256 ];                                             //
char db_path[ 256 ];                                              //
char workspace[ 256 ];                                            //
char object_name[ 41 ];                                           //
char struct_name[ 41 ];                                           //
char extent_name[ 41 ];                                           //
char inst_key[ 256 ];                                             //
uint16 system_version;                                            //
logical online_version;                                            //
char sys_appl;                                                  //
logical collopt;                                                   //
int16 transaction;                                               //
uint16 version;                                                   //
uint16 schema_version;                                            //
PIACC accmode;                                                   //
logical netopt;                                                    //
logical client_connected;                                          //
logical client_created;                                            //
logical dict_opened;                                               //
logical res_opened;                                                //
logical base_opened;                                               //
logical object_opened;                                             //
logical extent_opened;                                             //


int16 get_transaction()
{
   return ( transaction );
}
logical get_client_connected()
{
   return ( client_connected );
}
logical get_client_created()
{
   return ( client_created );
}
logical get_dict_opened()
{
   return ( dict_opened );
}
logical get_res_opened()
{
   return ( res_opened );
}
logical get_base_opened()
{
   return ( base_opened );
}
logical get_object_opened()
{
   return ( object_opened );
}
logical get_extent_opened()
{
   return ( extent_opened );
}


OPIImpExp logical Close ( );

OPIImpExp logical CloseDBObject ( );

OPIImpExp logical CloseDatabase ( );

OPIImpExp logical CloseDictionary ( );

OPIImpExp logical CloseProperty ( );

OPIImpExp logical CloseResourceDB ( );


OPIImpExp logical Connect ( ODABAClient &odaba_client );

OPIImpExp DataSourceHandle ( );

OPIImpExp logical Disconnect ( );

OPIImpExp ODABAClient &GetClient ( );

void Initialize ( );

OPIImpExp logical Open ( ODABAClient &odaba_client, PIACC acc_mod = PI_Read );

OPIImpExp logical Open ( ODABAClient &odaba_client, char *ini_file, char *datasource_name );

OPIImpExp logical Open ( ODABAClient &odaba_client, char *datasource_name );

OPIImpExp DBObjectHandle &OpenDBObject ( );

OPIImpExp DatabaseHandle &OpenDatabase ( );

OPIImpExp DictionaryHandle &OpenDictionary ( PIACC accopt );

OPIImpExp PropertyHandle *OpenProperty ( char *extname );

OPIImpExp DatabaseHandle &OpenResourceDB ( );

void ResetObjectHandle ( );

OPIImpExp logical SetConnectionName ( char *cache_string = NULL );

OPIImpExp logical SetDBObject ( DBObjectHandle &ohandle, char *w_objname = NULL );

OPIImpExp logical SetDataSource ( DataSourceHandle *dbdefptr );

OPIImpExp logical SetDatabase ( DatabaseHandle &db_handle, char *w_basepath = NULL );

OPIImpExp logical SetDictionary ( DictionaryHandle &dictptr, char *w_dictpath = NULL );

OPIImpExp logical SetResourceDB ( DatabaseHandle &db_handle, char *w_basepath = NULL );

OPIImpExp logical SetVariables ( char *datasource_name );

OPIImpExp logical Setup ( char *ini_file, char *datasource_name );

OPIImpExp logical SetupVariables ( char *datasource_name );

DictionaryHandle &get_dictionary ( );

DBObjectHandle &get_object_handle ( );

DatabaseHandle &get_res_handle ( );

OPIImpExp DataSourceHandle &operator= ( DataSourceHandle &datasource_ref );

OPIImpExp ~DataSourceHandle ( );
};

#endif
