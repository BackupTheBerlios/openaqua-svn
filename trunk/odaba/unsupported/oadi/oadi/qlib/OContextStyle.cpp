/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OContextStyle



\date     $Date: 2006/04/28 16:40:08,31 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OContextStyle"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sOContextStyle.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOContextStyle.hpp>


/******************************************************************************/
/**
\brief  Align

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Align"

OAlign *OContextStyle :: Align ( ) const
{

  return (OAlign*) &align;

}

/******************************************************************************/
/**
\brief  Bounds

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Bounds"

const DRect &OContextStyle :: Bounds ( ) const
{

  return bounds;

}

/******************************************************************************/
/**
\brief  CellAt

\return term

\param  rcDPoint
\param  rADK_HoriPos
\param  rADK_VertPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CellAt"

logical OContextStyle :: CellAt (const DPoint &rcDPoint, ADK_HoriPos rADK_HoriPos, ADK_VertPos rADK_VertPos ) const
{
  const DMargin  &m    = align.Margin();
  const DPoint   &p    = rcDPoint;
  const DSize    &s    = bounds.Size;
  logical         term = NO;
BEGINSEQ
  if ( p.X < 0 )                                     ERROR

  if ( p.X < m.Left ) 
    rADK_HoriPos = HPS_OuterLeft;
  else if ( p.X < m.Left + s.Width ) 
    rADK_HoriPos = HPS_InnerLeft;
  else if ( p.X < m.Left + s.Width + m.Right ) 
    rADK_HoriPos= HPS_OuterRight;
  else                                               ERROR

  if ( p.Y < 0 )                                     ERROR
  if ( p.Y < m.Top ) 
    rADK_VertPos = VPS_OuterTop;
  else if ( p.Y < m.Top + s.Height ) 
    rADK_VertPos = VPS_InnerTop;
  else if ( p.Y < m.Top + s.Height + m.Bottom ) 
    rADK_VertPos= VPS_OuterBottom;
  else                                               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ChildDisplayLevel

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChildDisplayLevel"

int OContextStyle :: ChildDisplayLevel ( ) const
{

  return childDisplayLevel;

}

/******************************************************************************/
/**
\brief  DisplayLevel

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayLevel"

int OContextStyle :: DisplayLevel ( )
{

  return displayLevel;

}

/******************************************************************************/
/**
\brief  IsAutoOpen

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAutoOpen"

logical OContextStyle :: IsAutoOpen ( )
{

  return autoOpen;

}

/******************************************************************************/
/**
\brief  IsChecked

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsChecked"

logical OContextStyle :: IsChecked ( )
{

  return checked;

}

/******************************************************************************/
/**
\brief  IsDisabled

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDisabled"

logical OContextStyle :: IsDisabled ( )
{

  return disabled;

}

/******************************************************************************/
/**
\brief  IsHidden

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsHidden"

logical OContextStyle :: IsHidden ( )
{

  return hidden;

}

/******************************************************************************/
/**
\brief  IsOuterElement

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOuterElement"

logical OContextStyle :: IsOuterElement ( )
{

  return ( autoOpen &&
           (align.get_vert() == VPS_OuterTop    || 
            align.get_vert() == VPS_OuterBottom ||
            align.get_hori() == HPS_OuterLeft   ||
            align.get_hori() == HPS_OuterRight    ) );


}

/******************************************************************************/
/**
\brief  IsSeparate

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSeparate"

logical OContextStyle :: IsSeparate ( )
{

  return separate;

}

/******************************************************************************/
/**
\brief  LabelPosition

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LabelPosition"

OLabelDefinition *OContextStyle :: LabelPosition ( ) const
{

  return (OLabelDefinition*) &labelPosition;

}

/******************************************************************************/
/**
\brief  MapFromCell

\return term

\param  rcDPoint
\param  vADK_HoriPos
\param  vADK_VertPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MapFromCell"

DPoint OContextStyle :: MapFromCell (const DPoint &rcDPoint, ADK_HoriPos vADK_HoriPos, ADK_VertPos vADK_VertPos )
{
  DPoint          p(rcDPoint);
  const DMargin  &m = align.Margin(); 
  const DSize    &s = bounds.Size;
  switch( vADK_HoriPos )
  {
  case HPS_OuterLeft:  p.X = -p.X + m.Left;             break;
  case HPS_InnerLeft:  p.X = p.X + m.Left;              break;
  case HPS_Center:     p.X = p.X + (m.Left+s.Width/2);  break;
  case HPS_InnerRight: p.X = -p.X + (m.Left+s.Width);   break;
  case HPS_OuterRight: p.X = p.X + (m.Left+s.Width);    break;
  }

  switch( vADK_VertPos )
  {
    case VPS_OuterTop:    p.Y = -p.Y + m.Top;             break;
    case VPS_InnerTop:    p.Y = p.Y + m.Top;              break;
    case VPS_Center:      p.Y = p.Y + (m.Top+s.Height/2); break;
    case VPS_InnerBottom: p.Y = -p.Y + (m.Top+s.Height);  break;
    case VPS_OuterBottom: p.Y = p.Y + (m.Top+s.Height);   break;
  }

return p;
}

/******************************************************************************/
/**
\brief  MapToCell

\return term

\param  rcDPoint
\param  vADK_HoriPos
\param  vADK_VertPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MapToCell"

DPoint OContextStyle :: MapToCell (const DPoint &rcDPoint, ADK_HoriPos vADK_HoriPos, ADK_VertPos vADK_VertPos )
{
  DPoint          p( rcDPoint );
  const DMargin  &m = align.Margin();
  const DSize    &s = bounds.Size;
  switch ( vADK_HoriPos )
  {
    case HPS_OuterLeft:  p.X = -(p.X - m.Left);           break;
    case HPS_InnerLeft:  p.X = p.X - m.Left;              break;
    case HPS_Center:     p.X = p.X - (m.Left+s.Width/2);  break;
    case HPS_InnerRight: p.X = -(p.X - (m.Left+s.Width)); break;
    case HPS_OuterRight: p.X = p.X - (m.Left+s.Width);    break;
  }

  switch ( vADK_VertPos )
  {
    case VPS_OuterTop:    p.Y = -(p.Y - m.Top);            break;
    case VPS_InnerTop:    p.Y = p.Y - m.Top;               break;
    case VPS_Center:      p.Y = p.Y - (m.Top+s.Height/2);  break;
    case VPS_InnerBottom: p.Y = -(p.Y - (m.Top+s.Height)); break;
    case VPS_OuterBottom: p.Y = p.Y - (m.Top+s.Height);    break;
  }

return p;
}

/******************************************************************************/
/**
\brief  OContextStyle

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OContextStyle"

     OContextStyle :: OContextStyle ( )
                     : OPersistent (),
  autoOpen(YES),
  separate(NO),
  mouse_tracking(NO),
  hidden(NO),
  disabled(NO),
  checked(NO),
  docking_area(NO),
  accept_drop(NO),
  displayLevel(1),
  distance(0),
  bounds(),
  align(),
  labelPosition(),
  textDefinitions(),
  childDisplayLevel(1)
{



}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  autoOpen
\param  separate
\param  mouse_tracking
\param  hidden
\param  disabled
\param  checked
\param  docking_area
\param  accept_drop
\param  displayLevel
\param  distance
\param  bounds
\param  align
\param  labelPosition
\param  textDefinitions
\param  childDisplayLevel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OContextStyle"

     OContextStyle :: OContextStyle (OPersistent bcOPersistent, logical autoOpen, logical separate, logical mouse_tracking, logical hidden, logical disabled, logical checked, logical docking_area, logical accept_drop, int16 displayLevel, int32 distance, DRect bounds, OAlign &align, OLabelDefinition labelPosition, OText textDefinitions, int childDisplayLevel )
                     : OPersistent (bcOPersistent),
  autoOpen(autoOpen),
  separate(separate),
  mouse_tracking(mouse_tracking),
  hidden(hidden),
  disabled(disabled),
  checked(checked),
  docking_area(docking_area),
  accept_drop(accept_drop),
  displayLevel(displayLevel),
  distance(distance),
  bounds(bounds),
  align(align),
  labelPosition(labelPosition),
  textDefinitions(textDefinitions),
  childDisplayLevel(childDisplayLevel)
{
/* 
  " OContextStyle( "
   +        OPersistent::Generate()
   + ", " + auto_open
   + ", " + separate
   + ", " + mouse_tracking
   + ", " + hidden
   + ", " + disabled
   + ", " + checked
   + ", " + docking_window
   + ", " + accept_drop
   + ", " + display_level
   + ", " + distance
   + ", DRect(!!&DPoint(position), !!&DSize(size.width,size.height))"
   + ", " + allign.Generate()
   + ", " + label_position.Generate()
   + ", " + text_definitions.Generate()
   + ", 1" //childdisplaylevel - unset
   + ")";
*/
}

/******************************************************************************/
/**
\brief  Position

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

const DPoint &OContextStyle :: Position ( ) const
{

  return bounds.Origin;

}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OContextStyle :: Read (PropertyHandle *ph )
{
  DSize     nsize;
  int32     number;
  logical   term = NO;
  OPersistent::Read(ph);

  align.Read(PHREF(ph->GPH("allign")));

  bounds.Origin = OPS2DPOINT(*PHREF(ph->GPH("position")));

  nsize = OSZ2DSIZE(*PHREF(ph->GPH("size")));
  if ( nsize.Width ) 
    bounds.Size.Width = nsize.Width;
  if ( nsize.Height ) 
    bounds.Size.Height = nsize.Height;

  displayLevel   = ph->GetInt("display_level");
  distance       = ph->GetInt("distance");
  separate       = ph->GetInt("separate");
  mouse_tracking = ph->GetInt("mouse_tracking");
  hidden         = ph->GetInt("hidden");
  disabled       = ph->GetInt("disabled");
  checked        = ph->GetInt("checked");
  docking_area   = ph->GetInt("docking_window");
  accept_drop    = ph->GetInt("accept_drop");
  autoOpen       = ph->GetInt("auto_open");

  labelPosition.Read(PHREF(ph->GPH("label_position")));
  textDefinitions.Read(PHREF(ph->GPH("text_definitions")));
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OContextStyle :: Reset ( )
{
  align.Reset();
  labelPosition.Reset();
  textDefinitions.Reset();
  
  bounds              = DRect();
  autoOpen            = YES;
  separate            = NO;
  mouse_tracking      = NO;
  hidden              = NO;
  disabled            = NO;
  checked             = NO;
  docking_area        = NO;
  accept_drop         = NO;
  displayLevel        = 1;
  distance            = 0;
  childDisplayLevel   = 1;
    

}

/******************************************************************************/
/**
\brief  SetDisplayLevel


\param  dsp_level
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

void OContextStyle :: SetDisplayLevel (int16 dsp_level )
{

  displayLevel = dsp_level;

}

/******************************************************************************/
/**
\brief  SetPosition

\return term

\param  rcDPoint
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPosition"

logical OContextStyle :: SetPosition (const DPoint &rcDPoint )
{

  bounds = DRect(rcDPoint,bounds.Size);


  return(NO);
}

/******************************************************************************/
/**
\brief  SetSize

\return term

\param  rcDSize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

logical OContextStyle :: SetSize (const DSize &rcDSize )
{

  bounds = DRect(bounds.Origin,rcDSize);
  return(NO);
}

/******************************************************************************/
/**
\brief  Size

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Size"

const DSize &OContextStyle :: Size ( ) const
{

  return bounds.Size;

}

/******************************************************************************/
/**
\brief  TextDefinitions

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TextDefinitions"

OText *OContextStyle :: TextDefinitions ( ) const
{

  return (OText*) &textDefinitions;

}

/******************************************************************************/
/**
\brief  set_accept_drop


\param  drop_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_accept_drop"

void OContextStyle :: set_accept_drop (logical drop_opt )
{

  accept_drop = drop_opt;

}

/******************************************************************************/
/**
\brief  ~OContextStyle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OContextStyle"

     OContextStyle :: ~OContextStyle ( )
{
  Reset();
}


