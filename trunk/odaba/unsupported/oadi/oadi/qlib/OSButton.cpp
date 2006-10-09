/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSButton



\date     $Date: 2006/04/28 16:52:24,01 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSButton"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sOSButton.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSButton :: CastPointer (char *typenames )
{

  return (   !typenames                    ? NULL
           : !strcmp(typenames,"OSButton") ? this
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

int32 OSButton :: CreateInstance (void **instptrp )
{
  *instptrp = new OSButton();
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

char *OSButton :: GetObjectType ( )
{

  return("OSButton");

}

/******************************************************************************/
/**
\brief  OSButton

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSButton"

     OSButton :: OSButton ( )
                     : OStyle (),
  button_type(BT_PushButton),
  toggle(NO),
  tristate(NO)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  button_type
\param  toggle
\param  tristate
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSButton"

     OSButton :: OSButton (OStyle bcOStyle, int16 button_type, logical toggle, logical tristate )
                     : OStyle (bcOStyle),
  button_type((ADK_ButtonType)button_type),
  toggle(toggle),
  tristate(tristate)
{
/*
  "OSButton("
  +        ADK_Style::Generate()
  + ", " + button_type
  + ", " + toggle
  + ", " + tristate
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

logical OSButton :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  button_type = (ADK_ButtonType)ph->GetInt("button_type");
  toggle      = ph->GetInt("toggle");
  tristate    = ph->GetInt("tristate");

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSButton :: Reset ( )
{
  OStyle::Reset();
}

/******************************************************************************/
/**
\brief  ~OSButton


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSButton"

     OSButton :: ~OSButton ( )
{
  if ( !Deleting() )
    Reset();
}


