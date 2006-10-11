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

#include "ab_dictionary.h"

//for the odaba dictionary
#include  <csos4mac.h>
#include  <igvtx.h>
#include  <igvts.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <codaba2.h>
#include  <sDictionary.hpp>




#include <iostream>
using namespace std;

/**



*/

AquaBase::AB_Dictionary::AB_Dictionary( AquaBase::AB_DataSource& parent)
      : QObject( &parent )
      , m_clientHandle(parent.m_client->OpenDictionary(PI_Write))
{
   m_clientDict = m_clientHandle.get_dictionary();
}




AquaBase::AB_Dictionary::~AB_Dictionary()
{
   m_clientHandle.Close();
}

