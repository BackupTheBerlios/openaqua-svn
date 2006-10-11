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



#ifndef __AB_Dictionary_h__
#define __AB_Dictionary_h__

#include <QObject>
#include <QString>
#include "ab_datasource.h"

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

class DictionaryHandle;
class Dictionary;
namespace AquaBase
{

   class AB_Dictionary: public QObject
   {
      Q_OBJECT

   public:
      AB_Dictionary( AquaBase::AB_DataSource& );
      virtual ~AB_Dictionary();

   private:
      friend class AB_DataSource;
      DictionaryHandle &m_clientHandle;
      AB_Dictionary( ); //not defined

   private:
      Dictionary *m_clientDict;
      operator bool ( );
      AB_Dictionary &operator= ( AB_Dictionary & );

   };
};
#endif //__AB_Dictionary_h__
