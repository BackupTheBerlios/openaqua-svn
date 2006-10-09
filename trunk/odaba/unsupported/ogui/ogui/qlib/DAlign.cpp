/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DAlign

\brief    


\date     $Date: 2006/03/13 21:34:58,79 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DAlign"

#include  <pogui7.h>
#include  <sDAlign.hpp>


/******************************************************************************/
/**
\brief  Arrange - 


\return cADK_ArrangeType -

\param  vADK_ArrangeType -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Arrange"

ADK_ArrangeType DAlign :: Arrange (ADK_ArrangeType vADK_ArrangeType ) const
{

return arrange == AT_undefined ? vADK_ArrangeType : arrange;

}

/******************************************************************************/
/**
\brief  DAlign - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DAlign"

                        DAlign :: DAlign ( )
                     :   hori(HPS_InnerLeft),
  vert(VPS_InnerTop),
  horiCells(1),
  horiSizing(SIZE_Fixed),
  horiSizingRate(0),
  vertCells(1),
  vertSizing(SIZE_Fixed),
  vertSizingRate(0),
  margin(0,0,0,0),
  arrange(AT_Absolut),
  position(POS_Parent)
{



}

/******************************************************************************/
/**
\brief  i01


\param  vADK_HoriPos -
\param  vADK_VertPos -
\param  vADK_HoriCells -
\param  vADK_HoriSizeType -
\param  vADK_HoriSizingRate -
\param  vADK_VertCells -
\param  vADK_VertSizeType
\param  vADK_VertSizingRate -
\param  vDMargin -
\param  vADK_ArrangeType -
\param  vADK_PosType -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DAlign"

                        DAlign :: DAlign (ADK_HoriPos vADK_HoriPos, ADK_VertPos vADK_VertPos, int vADK_HoriCells, ADK_SizeType vADK_HoriSizeType, int vADK_HoriSizingRate, int vADK_VertCells, ADK_SizeType vADK_VertSizeType, int vADK_VertSizingRate, DMargin vDMargin, ADK_ArrangeType vADK_ArrangeType, ADK_PosType vADK_PosType )
                     :  hori(vADK_HoriPos)
,vert(vADK_VertPos)
,horiCells(vADK_HoriCells)
,horiSizing(vADK_HoriSizeType)
,horiSizingRate(vADK_HoriSizingRate)

,vertCells(vADK_VertCells)
,vertSizing(vADK_VertSizeType)
,vertSizingRate(vADK_VertSizingRate)

,margin(vDMargin)
,arrange(vADK_ArrangeType)
,position(vADK_PosType)
{

 /* convenience constructor to construct objects from script */

}

/******************************************************************************/
/**
\brief  GetEdge - 


\return edge -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEdge"

DPoint DAlign :: GetEdge ( )
{
  int  h = 0;
  int  v = 0;

BEGINSEQ
  if ( Arrange(AT_Absolut) == AT_Grid )              LEAVESEQ
  
  switch ( Hori(HPS_InnerLeft) )
  {
    case HPS_InnerLeft  : h = -1; break;
    case HPS_OuterLeft  : h =  1; break;
    case HPS_InnerRight : h =  1; break;
    case HPS_OuterRight : h = -1; break;
    case HPS_Center     : h =  0; break;
  }
  switch ( Vert(VPS_InnerTop) )
  {
    case VPS_InnerTop    : v = -1; break; 
    case VPS_OuterTop    : v =  1; break;
    case VPS_InnerBottom : v =  1; break;
    case VPS_OuterBottom : v = -1; break;
    case VPS_Center      : v =  0; break;
  }
ENDSEQ
  return(DPoint(h,v));
}

/******************************************************************************/
/**
\brief  GetOrientation - 


\return orientation -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOrientation"

DPoint DAlign :: GetOrientation ( )
{
  int h, v;

  switch( Hori(HPS_InnerLeft) )
  {
    case HPS_OuterLeft: h= -1; break;
    case HPS_OuterRight: h= 1; break;
    default: h= 0; break;
  }

  switch( Vert(VPS_InnerTop) )
  {
    case VPS_OuterTop: v= -1; break;
    case VPS_OuterBottom: v= 1; break;
    default: v= 0; break;
  }


  return DPoint( h, v );
}

/******************************************************************************/
/**
\brief  Hori - 


\return term -

\param  vADK_HoriPos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Hori"

ADK_HoriPos DAlign :: Hori (ADK_HoriPos vADK_HoriPos ) const
{

  return hori == HPS_undefined ? vADK_HoriPos : hori;

}

/******************************************************************************/
/**
\brief  HoriCells - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HoriCells"

int DAlign :: HoriCells ( ) const
{

  return horiCells;

}

/******************************************************************************/
/**
\brief  HoriSizing - 


\return term -

\param  vADK_SizeType -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HoriSizing"

ADK_SizeType DAlign :: HoriSizing (ADK_SizeType vADK_SizeType ) const
{

  return horiSizing == SIZE_undefined ? vADK_SizeType : horiSizing;

}

/******************************************************************************/
/**
\brief  HoriSizingRate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HoriSizingRate"

int DAlign :: HoriSizingRate ( ) const
{

  return horiSizingRate;

}

/******************************************************************************/
/**
\brief  IsInside - 


\return cond -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInside"

logical DAlign :: IsInside ( )
{

  return ( (hori == HPS_undefined || hori == HPS_InnerRight ||
            hori == HPS_InnerLeft || hori == HPS_Center)     &&
           (vert == VPS_undefined || vert == VPS_InnerBottom ||
            vert == VPS_InnerTop  || vert == VPS_Center)       );

}

/******************************************************************************/
/**
\brief  Margin - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Margin"

const DMargin &DAlign :: Margin ( ) const
{

  return margin;

}

/******************************************************************************/
/**
\brief  Position - 


\return term -

\param  vADK_PosType -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

ADK_PosType DAlign :: Position (ADK_PosType vADK_PosType ) const
{

  return position == POS_undefined ? vADK_PosType : position;

}

/******************************************************************************/
/**
\brief  SetGrow - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGrow"

void DAlign :: SetGrow ( )
{

  horiSizing = SIZE_Grow;
  vertSizing = SIZE_Grow;

}

/******************************************************************************/
/**
\brief  SetHori - 



\param  vADK_HoriPos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHori"

void DAlign :: SetHori (ADK_HoriPos vADK_HoriPos )
{

  hori= vADK_HoriPos;

}

/******************************************************************************/
/**
\brief  SetVert - 



\param  vADK_VertPos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVert"

void DAlign :: SetVert (ADK_VertPos vADK_VertPos )
{

  vert= vADK_VertPos;

}

/******************************************************************************/
/**
\brief  ToQAlignment - 


\return qt_align -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToQAlignment"

Qt::Alignment DAlign :: ToQAlignment ( )
{
  Qt::Alignment            align;
  if ( horiSizing == SIZE_Fixed )
    switch ( hori )
    {
      case HPS_InnerLeft  :
      case HPS_OuterLeft  : align |= Qt::AlignLeft;
                            break;
      case HPS_InnerRight :
      case HPS_OuterRight : align |= Qt::AlignRight;
                            break;
      default             : align |= Qt::AlignHCenter;
    }
  
  if ( vertSizing == SIZE_Fixed )
    switch ( vert )
    {
      case VPS_InnerBottom:
      case VPS_OuterBottom: align |= Qt::AlignBottom;
                            break;
      case VPS_InnerTop   :
      case VPS_OuterTop   : align |= Qt::AlignTop;
                            break;
      default             : align |= Qt::AlignVCenter;
    }

  return(align);
}

/******************************************************************************/
/**
\brief  Vert - 


\return term -

\param  vADK_VertPos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Vert"

ADK_VertPos DAlign :: Vert (ADK_VertPos vADK_VertPos ) const
{

  return vert == VPS_undefined ? vADK_VertPos : vert;

}

/******************************************************************************/
/**
\brief  VertCells - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VertCells"

int DAlign :: VertCells ( ) const
{

  return vertCells;

}

/******************************************************************************/
/**
\brief  VertSizing - 


\return term -

\param  vADK_SizeType -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VertSizing"

ADK_SizeType DAlign :: VertSizing (ADK_SizeType vADK_SizeType ) const
{

  return vertSizing == SIZE_undefined ? vADK_SizeType : vertSizing;

}

/******************************************************************************/
/**
\brief  VertSizingRate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VertSizingRate"

int DAlign :: VertSizingRate ( ) const
{

  return vertSizingRate;

}


