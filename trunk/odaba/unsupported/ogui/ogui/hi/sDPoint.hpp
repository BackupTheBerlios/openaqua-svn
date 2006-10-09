/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DPoint

\brief    


\date     $Date: 2006/03/13 21:33:37,92 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DPoint_HPP
#define   DPoint_HPP

class     DPoint;

#include  <sDPoint.hpp>
#pragma pack(4)

class  DPoint
{
public     :         int                                          X;                                                         
public     :         int                                          Y;                                                         

public     :
public     :                                     DPoint &GetOrientationFromEdge ( );
public     :                                     DPoint operator+ (const DPoint &rcDPoint );
public     :         OGUI7ImpExp                                         DPoint (const int cx, const int cy )                     :   X(cx), 
  Y(cy)
{



}

public     :         OGUI7ImpExp                                         DPoint ( )                     :   X(0),
  Y(0)
{



}

public     :         OGUI7ImpExp                 logical operator!= (const DPoint &rcDPoint ) const{

  return X != rcDPoint.X || Y != rcDPoint.Y;

}

public     :         OGUI7ImpExp                 DPoint operator- (const DPoint &rcDPoint ) const{

  return DPoint( X - rcDPoint.X, Y - rcDPoint.Y );

}

public     :         OGUI7ImpExp                 logical operator== (const DPoint &rcDPoint ) const{

  return X == rcDPoint.X && Y == rcDPoint.Y;

}

};

#pragma pack()
#endif
