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
#include "AquaBase.h"

class DataSourceHandle;
namespace AquaBase
{

   class AB_DataSource: public QObject
   {
      Q_OBJECT

   public:
      AB_DataSource( AquaBase::AB_Connection& );
      virtual ~AB_DataSource();

      bool Open(bool readOnly=true);
      bool Close();

      //!@begin a transaction
      bool BeginTransaction ( );
      bool RollBack ( );
      bool CommitTransaction ( );

   protected:
      //DatabaseHandle &OpenDatabase ( );

   private:
      friend class AquaBase::AB_Dictionary;
      DataSourceHandle *m_client;

      AquaBase::AB_Connection& m_connection;

   private:
      operator bool ( );
      AB_DataSource(  ); //not defined
      AB_DataSource &operator= ( AB_DataSource & );

   };
};
#endif //__AB_DataSource_h__

