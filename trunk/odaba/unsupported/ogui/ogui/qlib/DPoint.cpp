/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    DPoint

\brief    


\date     $Date: 2006/08/29 19:40:29,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DPoint"

#include  <pogui7.h>
#include  <sDPoint.hpp>


/******************************************************************************/
/**
\brief  GetOrientationFromEdge - 



\return orientation - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrientationFromEdge"

DPoint &DPoint :: GetOrientationFromEdge ( )
{

  DPoint ret( X ? -X : 1, Y ? -Y : 1  );
  return ret;

}

/******************************************************************************/
/**
\brief  operator+ - 



\return dpoint - 

\param  rcDPoint - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

DPoint DPoint :: operator+ (const DPoint &rcDPoint )
{

  return DPoint( X + rcDPoint.X, Y + rcDPoint.Y );

}


