/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSRadioGroup



\date     $Date: 2006/04/28 16:55:35,62 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSRadioGroup"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sOSRadioGroup.hpp>


/******************************************************************************/
/**
\brief  AutoResize

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AutoResize"

logical OSRadioGroup :: AutoResize ( )
{

  return ( hscrol || vscrol ? YES : NO );

}

/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSRadioGroup :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OSRadioGroup") ? this
                                               : OStyle::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OSRadioGroup :: CreateInstance (void **instptrp )
{
  *instptrp = new OSRadioGroup();
  return(0);
}

/******************************************************************************/
/**
\brief  GetObjectType

\return typenames

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectType"

char *OSRadioGroup :: GetObjectType ( )
{

  return("OSRadioGroup");

}

/******************************************************************************/
/**
\brief  HasHscrol

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasHscrol"

logical OSRadioGroup :: HasHscrol ( )
{

  return ( this ? hscrol : UNDEF );

}

/******************************************************************************/
/**
\brief  HasVscrol

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasVscrol"

logical OSRadioGroup :: HasVscrol ( )
{

  return ( this ? vscrol : UNDEF );

}

/******************************************************************************/
/**
\brief  OSRadioGroup

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSRadioGroup"

     OSRadioGroup :: OSRadioGroup ( )
                     : OStyle (),
  checked_num(AUTO),
  vertical(0),
  vscrol(NO),
  horizontal(0),
  hscrol(NO),
  label_position(HPS_InnerLeft),
  group_label(YES)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  ichecked_num
\param  ivertical
\param  vscroll
\param  ihorizontal
\param  hscroll
\param  ilabel_position
\param  group_label
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSRadioGroup"

     OSRadioGroup :: OSRadioGroup (OStyle bcOStyle, int16 ichecked_num, int8 ivertical, logical vscroll, int8 ihorizontal, logical hscroll, int16 ilabel_position, logical group_label )
                     : OStyle (bcOStyle),
  checked_num(ichecked_num),
  vertical(ivertical),
  vscrol(vscroll),
  horizontal(ihorizontal),
  hscrol(hscroll),
  label_position((ADK_HoriPos)ilabel_position),
  group_label(group_label)
{
/*
  "OSRadioGroup("
  + ADK_Style::Generate()
  + ", " + checked_num
  + ", " + vertical
  + ", " + vscrol
  + ", " + horizontal
  + ", " + hscrol
  + ", " + label_position
  + ", " + group_label
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

logical OSRadioGroup :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  checked_num    = ph->GetInt("checked_num");
  horizontal     = ph->GetInt("horizontal");
  hscrol         = ph->GetInt("hscrol");
  vertical       = ph->GetInt("vertical");
  vscrol         = ph->GetInt("vscrol");
  label_position = (ADK_HoriPos)ph->GetInt("label_position");
  group_label    = ph->GetInt("group_label");
  
  if ( hscrol || vscrol )
  {
    group_label = NO;
    if ( !border )
    {
      border = YES;
      border_style.Set(BS_Box,BSS_Sunken,1,0);
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSRadioGroup :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ResetBorder


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetBorder"

void OSRadioGroup :: ResetBorder ( )
{
}

/******************************************************************************/
/**
\brief  ~OSRadioGroup


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSRadioGroup"

     OSRadioGroup :: ~OSRadioGroup ( )
{

  if ( !Deleting() )
    Reset();

}


