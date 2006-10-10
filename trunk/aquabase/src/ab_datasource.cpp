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

//for the odaba DataSource
#include  <csos4mac.h>
#include  <igvtx.h>
#include  <igvts.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <codaba2.h>
#include  <sDataSourceHandle.hpp>





#include <iostream>
using namespace std;

/**



*/

AquaBase::AB_DataSource::AB_DataSource(AB_Connection& c , QObject *const parent  )
      : QObject( parent )
      , m_connection(c)
{
   m_client = new DataSourceHandle();
}


AquaBase::AB_DataSource::~AB_DataSource()
{
   delete m_client;
}

bool AquaBase::AB_DataSource::BeginTransaction ( )
{
   cerr << "begin transaction not supported" <<endl;
}


bool AquaBase::AB_DataSource::RollBack ( )
{
   cerr << "roll back transaction not supported" <<endl;
}


bool AquaBase::AB_DataSource::CommitTransaction ( )
{
   cerr << "commit transaction not supported" <<endl;
}



