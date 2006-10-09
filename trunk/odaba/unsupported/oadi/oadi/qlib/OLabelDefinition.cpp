/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OLabelDefinition



\date     $Date: 2006/04/28 14:05:22,59 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OLabelDefinition"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sOLabelDefinition.hpp>


/******************************************************************************/
/**
\brief  HasShowLabel

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasShowLabel"

logical OLabelDefinition :: HasShowLabel ( ) const
{

  return showLabel;

}

/******************************************************************************/
/**
\brief  HoriPos

\return term

\param  vADK_HoriPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HoriPos"

ADK_HoriPos OLabelDefinition :: HoriPos (ADK_HoriPos vADK_HoriPos ) const
{

  return horiPos == HPS_undefined ? vADK_HoriPos : horiPos;

}

/******************************************************************************/
/**
\brief  OLabelDefinition

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OLabelDefinition"

     OLabelDefinition :: OLabelDefinition ( )
                     : OPersistent (),
  showLabel(0),
  horiPos(HPS_undefined),
  vertPos(VPS_undefined),
  textPosition(HPS_undefined),
  size()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  showLabel
\param  horiPos
\param  vertPos
\param  textPosition
\param  dsize
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OLabelDefinition"

     OLabelDefinition :: OLabelDefinition (OPersistent bcOPersistent, logical showLabel, int16 horiPos, int16 vertPos, int16 textPosition, DSize dsize )
                     : OPersistent (bcOPersistent),
  showLabel(showLabel),
  horiPos((ADK_HoriPos)horiPos),
  vertPos((ADK_VertPos)vertPos),
  textPosition((ADK_HoriPos)textPosition),
  size(dsize)
{

/*
  "OLabelDefinition("
  +        ADK_Persistent::Generate()
  + ", " + show_label
  + ", " + hori_pos
  + ", " + verti_pos
  + ", " + text_position
  + ", " + size.Generate(DSize)
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

logical OLabelDefinition :: Read (PropertyHandle *ph )
{
  DSize                   nsize;
  int32                   number;
  logical                 term = NO;
  OPersistent::Read(ph);

  if ( number = ph->GetInt("show_label") )
    showLabel = number;
  if ( number = ph->GetInt("text_position") )
    (int&)textPosition = number;
  if ( number = ph->GetInt("hori_pos") )
    (int&)horiPos = number;
  if ( number = ph->GetInt("verti_pos") )
    (int&)vertPos = number;
  
  nsize = OSZ2DSIZE(*PHREF(ph->GPH("size")));
  if ( nsize.Width ) 
    size.Width = nsize.Width;
  if ( nsize.Height ) 
    size.Height = nsize.Height;

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OLabelDefinition :: Reset ( )
{
  showLabel    = NO;
  horiPos      = HPS_OuterLeft;
  vertPos      = VPS_OuterTop;
  textPosition = HPS_InnerLeft;
  size         = DSize();

}

/******************************************************************************/
/**
\brief  Size

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Size"

const DSize &OLabelDefinition :: Size ( ) const
{

  return size;

}

/******************************************************************************/
/**
\brief  TextPosition

\return term

\param  vADK_HoriPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TextPosition"

ADK_HoriPos OLabelDefinition :: TextPosition (ADK_HoriPos vADK_HoriPos ) const
{

  return textPosition == HPS_undefined ? vADK_HoriPos : textPosition;

}

/******************************************************************************/
/**
\brief  VertPos

\return term

\param  vADK_VertPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VertPos"

ADK_VertPos OLabelDefinition :: VertPos (ADK_VertPos vADK_VertPos ) const
{

  return vertPos == VPS_undefined ? vADK_VertPos : vertPos;

}


