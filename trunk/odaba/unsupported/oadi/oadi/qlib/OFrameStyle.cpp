/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OFrameStyle



\date     $Date: 2006/04/28 17:15:27,32 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFrameStyle"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sPropertyHandle.hpp>
#include  <sOFrameStyle.hpp>


/******************************************************************************/
/**
\brief  HasClose

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasClose"

logical OFrameStyle :: HasClose ( ) const
{

  return minmax;

}

/******************************************************************************/
/**
\brief  HasMinmax

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasMinmax"

logical OFrameStyle :: HasMinmax ( ) const
{

  return minmax;

}

/******************************************************************************/
/**
\brief  HasMove

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasMove"

logical OFrameStyle :: HasMove ( ) const
{

  return move;

}

/******************************************************************************/
/**
\brief  HasResize

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasResize"

logical OFrameStyle :: HasResize ( )
{

  return resize;

}

/******************************************************************************/
/**
\brief  HasSmallTitle

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasSmallTitle"

logical OFrameStyle :: HasSmallTitle ( ) const
{

  return smallTitle;

}

/******************************************************************************/
/**
\brief  HasTitle

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasTitle"

logical OFrameStyle :: HasTitle ( ) const
{

  return title;

}

/******************************************************************************/
/**
\brief  IsSimpleWindow

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSimpleWindow"

logical OFrameStyle :: IsSimpleWindow ( )
{

 return ( winType == WT_Simple || winType == WT_undefined );

}

/******************************************************************************/
/**
\brief  IsSystemModal

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSystemModal"

logical OFrameStyle :: IsSystemModal ( ) const
{

  return systemModal;

}

/******************************************************************************/
/**
\brief  IsTopAlways

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTopAlways"

logical OFrameStyle :: IsTopAlways ( ) const
{

  return topAlways;

}

/******************************************************************************/
/**
\brief  OFrameStyle

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFrameStyle"

     OFrameStyle :: OFrameStyle ( )
                     : OPersistent (),
  winType(WT_Simple),
  title(NO),
  minmax(NO),
  close(NO),
  move(NO),
  resize(NO),
  systemModal(NO),
  smallTitle(NO),
  topAlways(NO)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  vADK_WinType
\param  has_title
\param  has_minmax
\param  has_close
\param  can_move
\param  can_resize
\param  is_systemModal
\param  has_smallTitle
\param  is_alwaysontop
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFrameStyle"

     OFrameStyle :: OFrameStyle (OPersistent bcOPersistent, ADK_WinType vADK_WinType, logical has_title, logical has_minmax, logical has_close, logical can_move, logical can_resize, logical is_systemModal, logical has_smallTitle, logical is_alwaysontop )
                     : OPersistent (bcOPersistent),
  winType(vADK_WinType),
  title(has_title),
  minmax(has_minmax),
  close(has_close),
  move(can_move),
  resize(can_resize),
  systemModal(is_systemModal),
  smallTitle(has_smallTitle),
  topAlways(is_alwaysontop)
{
/*
  "OFrameStyle("
  +        ADK_Persistent::Generate()
  + ", " + win_type
  + ", " + title
  + ", " + minmax
  + ", " + close
  + ", " + move
  + ", " + resize
  + ", " + system_modal
  + ", " + small_title
  + ", " + top_always
  + ")";
*/
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

logical OFrameStyle :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OPersistent::Read(ph);

  (int&)winType = ph->GetInt("win_type");
  title         = ph->GetInt("title");
  minmax        = ph->GetInt("minmax");
  close         = ph->GetInt("close");
  move          = ph->GetInt("move");
  resize        = ph->GetInt("resize");
  systemModal   = ph->GetInt("system_modal");
  smallTitle    = ph->GetInt("small_title");
  topAlways     = ph->GetInt("top_always");
  return(term);
}

/******************************************************************************/
/**
\brief  WinType

\return term

\param  vADK_WinType
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WinType"

ADK_WinType OFrameStyle :: WinType (ADK_WinType vADK_WinType ) const
{

  return winType == WT_undefined ? vADK_WinType : winType;

}


