/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    DMCLayoutItem

\brief    


\date     $Date: 2006/07/05 14:04:35,61 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DMCLayoutItem"

#include  <podcp8.h>
#include  <cqt.h>
#include  <sDMCLayoutItem.hpp>


/******************************************************************************/
/**
\brief  DMCLayoutItem - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DMCLayoutItem"

     DMCLayoutItem :: DMCLayoutItem ( )
                     : QLayoutItem(),
rectangle(0, 0, 100, 100)
{



}

/******************************************************************************/
/**
\brief  expandingDirections - 



\return direction - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "expandingDirections"

Qt::Orientations DMCLayoutItem :: expandingDirections ( ) const
{


return Qt::Vertical | Qt::Horizontal;
}

/******************************************************************************/
/**
\brief  geometry - 



\return rect - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "geometry"

QRect DMCLayoutItem :: geometry ( ) const
{


return rectangle;
}

/******************************************************************************/
/**
\brief  isEmpty - 



\return qtterm - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isEmpty"

bool DMCLayoutItem :: isEmpty ( ) const
{


return false;
}

/******************************************************************************/
/**
\brief  maximumSize - 



\return size - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "maximumSize"

QSize DMCLayoutItem :: maximumSize ( ) const
{


return QSize(4096, 4096);
}

/******************************************************************************/
/**
\brief  minimumSize - 



\return size - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "minimumSize"

QSize DMCLayoutItem :: minimumSize ( ) const
{


return QSize(1, 1);
}

/******************************************************************************/
/**
\brief  setGeometry - 




\param  rqRect - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setGeometry"

void DMCLayoutItem :: setGeometry (const QRect &rqRect )
{

rectangle = rqRect;


}

/******************************************************************************/
/**
\brief  sizeHint - 



\return size - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sizeHint"

QSize DMCLayoutItem :: sizeHint ( ) const
{


return QSize(1, 1);
}


