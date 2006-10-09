/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DSize

\brief    


\date     $Date: 2006/03/13 21:33:38,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSize_HPP
#define   DSize_HPP

class     DSize;

#include  <sDSize.hpp>
#pragma pack(4)

class  DSize
{
public     :         int                                          Width;                                                     
public     :         int                                          Height;                                                    

public     :
public     :                                     logical IsValid ( ) const;
public     :         OGUI7ImpExp                 DSize operator+ (const DSize &rcDSize );
public     :         OGUI7ImpExp                                         DSize (int width, int height )                     : Width(width),
Height(height)
{



}

public     :         OGUI7ImpExp                                         DSize ( )                     : Width(0),Height(0)
{



}

public     :         OGUI7ImpExp                 logical operator!= (const DSize &rcDSize ) const{

  return Width  != rcDSize.Width || 
         Height != rcDSize.Height;

}

public     :         OGUI7ImpExp                 logical operator== (const DSize &rcDSize ) const{

  return Width  == rcDSize.Width && 
         Height == rcDSize.Height;

}

};

#pragma pack()
#endif
