/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DMargin

\brief    


\date     $Date: 2006/03/13 21:33:37,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DMargin_HPP
#define   DMargin_HPP

class     DMargin;

#pragma pack(4)

class  DMargin
{
public     :         int                                          Left;                                                      //
public     :         int                                          Top;                                                       //
public     :         int                                          Right;                                                     //
public     :         int                                          Bottom;                                                    //

public     :
public     :         OGUI7ImpExp                                         DMargin ( );
public     :         OGUI7ImpExp                 logical IsEmpty ( );
public     :         OGUI7ImpExp                 int32 Maximum ( );
public     :         OGUI7ImpExp                                         DMargin (int left, int top, int right, int bottom )                     : Left(left),
  Top(top),
  Right(right),
  Bottom(bottom)
{



}

};

#pragma pack()
#endif
