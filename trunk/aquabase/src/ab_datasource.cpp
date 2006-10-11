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

#include "ab_datasource.h"
#include "ab_error.h"

//for the odaba DataSource
#include  <csos4mac.h>
#include  <igvtx.h>
#include  <igvts.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <codaba2.h>
#include  <sDataSourceHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>



#include <iostream>
using namespace std;

/**



*/

AquaBase::AB_DataSource::AB_DataSource(AB_Connection& c  )
      : QObject( &c )
      , m_connection(c)
{
   m_client = new DataSourceHandle();
}


AquaBase::AB_DataSource::~AB_DataSource()
{
   delete m_client;
}


/**

Data sources provide simple transaction control. Data
source transactions cannot be nested, i.e. when a transaction
is running for the datasource no other transaction
can be started.

Using nested transactions is possible with the DBObjectHandle.

@see RollBack ( )
@see CommitTransaction ( )
*/
bool AquaBase::AB_DataSource::BeginTransaction ( )
{
   return (!m_client->BeginTransaction());
}


/**
*/
bool AquaBase::AB_DataSource::RollBack ( )
{
   return (!m_client->RollBack());
}


/**
*/
bool AquaBase::AB_DataSource::CommitTransaction ( )
{
   return (!m_client->CommitTransaction());
}


bool AquaBase::AB_DataSource::Open(bool readOnly)
{
   if (readOnly == true) {
      return (!m_client->Open(*m_connection.m_client, PI_Read ));
   } else {
      return (!m_client->Open(*m_connection.m_client, PI_Write));
   }

}



bool AquaBase::AB_DataSource::Close()
{
   return (!m_client->Close());
}


/**
Database handle must be created for accessing data in
an ODABA database. An ODABA database must be connected
with a dictionary, which defines the object model
for the database.
*/
//DatabaseHandle &AquaBase::AB_DataSource::OpenDatabase ( )
//{
//   return m_client->OpenDatabase();
//}


