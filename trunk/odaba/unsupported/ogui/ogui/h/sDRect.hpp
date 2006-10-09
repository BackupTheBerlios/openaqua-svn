/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DRect



\date     $Date: 2006/03/13 21:33:38,09 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DRect_HPP
#define   DRect_HPP

class     DRect;

#include  <sDPoint.hpp>
#include  <sDRect.hpp>
#include  <sDSize.hpp>
#pragma pack(4)

class  DRect
{
public     :         DPoint                                       Origin;                                                    
public     :         DSize                                        Size;                                                      

public     :
public     :         OGUI7ImpExp                 DPoint BottomRight ( ) const{

  return DPoint( Origin.X + Size.Width - 1, Origin.Y + Size.Height - 1 );

}

public     :         OGUI7ImpExp                 logical Contains (const DPoint &rcDPoint ){

  return rcDPoint.X >= Origin.X && 
         rcDPoint.Y >= Origin.Y &&
         rcDPoint.X -  Origin.X < Size.Width &&
         rcDPoint.Y -  Origin.Y < Size.Height;


}

public     :         OGUI7ImpExp                                         DRect (const DPoint &rcDPointTL, const DPoint &rcDPointBR )                     : Origin( rcDPointTL ),
Size( rcDPointBR.X - rcDPointTL.X + 1,
      rcDPointBR.Y - rcDPointTL.Y + 1 )

{



}

public     :         OGUI7ImpExp                                         DRect ( )                     : Origin(),Size()
{



}

public     :         OGUI7ImpExp                                         DRect (const DPoint &rcDPoint, const DSize &rcDSize )                     : Origin( rcDPoint ),
Size( rcDSize )
{



}

public     :         OGUI7ImpExp                                         DRect (int left, int top, int width, int height )                     : Origin(left,top),
Size(width,height)
{



}

public     :         OGUI7ImpExp                 logical operator!= (const DRect &rcDRect ) const{

  return Origin != rcDRect.Origin ||
         Size   != rcDRect.Size;

}

public     :         OGUI7ImpExp                 logical operator== (const DRect &rcDRect ) const{

  return Origin == rcDRect.Origin && 
         Size   == rcDRect.Size;

}

};

#pragma pack()
#endif
