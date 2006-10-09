/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DAlign

\brief    


\date     $Date: 2006/03/13 21:33:34,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DAlign_HPP
#define   DAlign_HPP

class     DAlign;

#include  <cADK_ArrangeType.h>
#include  <cADK_HoriPos.h>
#include  <cADK_PosType.h>
#include  <cADK_SizeType.h>
#include  <cADK_VertPos.h>
#include  <sDMargin.hpp>
#include  <sDPoint.hpp>
#include  <sDRect.hpp>
#pragma pack(4)

class  DAlign
{
protected  :         ADK_HoriPos                                  hori;                                                      //
protected  :         ADK_VertPos                                  vert;                                                      //
protected  :         int                                          horiCells;                                                 //
protected  :         ADK_SizeType                                 horiSizing;                                                //
protected  :         int                                          horiSizingRate;                                            //
protected  :         int                                          vertCells;                                                 //
protected  :         ADK_SizeType                                 vertSizing;                                                //
protected  :         int                                          vertSizingRate;                                            //
protected  :         DMargin                                      margin;                                                    //
protected  :         ADK_ArrangeType                              arrange;                                                   //
protected  :         ADK_PosType                                  position;                                                  //

public     :
                     ADK_HoriPos                                  get_hori() { return(hori); }
                     ADK_VertPos                                  get_vert() { return(vert); }
                     int                                         &get_horiCells() { return(horiCells); }
                     ADK_SizeType                                 get_horiSizing() { return(horiSizing); }
                     int                                         &get_horiSizingRate() { return(horiSizingRate); }
                     int                                         &get_vertCells() { return(vertCells); }
                     ADK_SizeType                                 get_vertSizing() { return(vertSizing); }
                     int                                         &get_vertSizingRate() { return(vertSizingRate); }
                     DMargin                                     &get_margin() { return(margin); }
                     ADK_ArrangeType                              get_arrange() { return(arrange); }
                     ADK_PosType                                  get_position() { return(position); }
public     :                                     ADK_ArrangeType Arrange (ADK_ArrangeType vADK_ArrangeType ) const;
public     :         OGUI7ImpExp                                         DAlign ( );
public     :         OGUI7ImpExp                                         DAlign (ADK_HoriPos vADK_HoriPos, ADK_VertPos vADK_VertPos, int vADK_HoriCells, ADK_SizeType vADK_HoriSizeType, int vADK_HoriSizingRate, int vADK_VertCells, ADK_SizeType vADK_VertSizeType, int vADK_VertSizingRate, DMargin vDMargin, ADK_ArrangeType vADK_ArrangeType, ADK_PosType vADK_PosType );
public     :         OGUI7ImpExp                 DPoint GetEdge ( );
public     :         OGUI7ImpExp                 DPoint GetOrientation ( );
public     :                                     ADK_HoriPos Hori (ADK_HoriPos vADK_HoriPos ) const;
public     :                                     int HoriCells ( ) const;
public     :                                     ADK_SizeType HoriSizing (ADK_SizeType vADK_SizeType ) const;
public     :                                     int HoriSizingRate ( ) const;
public     :                                     logical IsInside ( );
public     :         OGUI7ImpExp                 const DMargin &Margin ( ) const;
public     :                                     ADK_PosType Position (ADK_PosType vADK_PosType ) const;
public     :         OGUI7ImpExp                 void SetGrow ( );
public     :         OGUI7ImpExp                 void SetHori (ADK_HoriPos vADK_HoriPos );
public     :         OGUI7ImpExp                 void SetVert (ADK_VertPos vADK_VertPos );
public     :                                     Qt::Alignment ToQAlignment ( );
public     :                                     ADK_VertPos Vert (ADK_VertPos vADK_VertPos ) const;
public     :                                     int VertCells ( ) const;
public     :                                     ADK_SizeType VertSizing (ADK_SizeType vADK_SizeType ) const;
public     :                                     int VertSizingRate ( ) const;
};

#pragma pack()
#endif
