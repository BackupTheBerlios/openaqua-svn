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



#ifndef __OdabaDBObjectHandle_h__
#define __OdabaDBObjectHandle_h__

#include <QObject>
#include <QString>
#include "odaba_namespace.h"




/**

@class OdabaClient


*/

class OdabaDBObjectHandle: public QObject  {
Q_OBJECT
public:

   OdabaDBObjectHandle(QObject *const parent=0);
   virtual ~OdabaDBObjectHandle();


public:

private:
  DBObjectHandle    *m_handle;


};

#endif // __OdabaDBObjectHandle_h__
