/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSWindow



\date     $Date: 2006/04/28 16:56:56,20 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSWindow"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOSWindow.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSWindow :: CastPointer (char *typenames )
{

  return (   !typenames                    ? NULL
           : !strcmp(typenames,"OSWindow") ? this
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

int32 OSWindow :: CreateInstance (void **instptrp )
{
  *instptrp = new OSWindow();
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

char *OSWindow :: GetObjectType ( )
{

  return("OSWindow");

}

/******************************************************************************/
/**
\brief  HasHscrol

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasHscrol"

logical OSWindow :: HasHscrol ( )
{

  return ( this ? hscrol : UNDEF );

}

/******************************************************************************/
/**
\brief  HasVscrol

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasVscrol"

logical OSWindow :: HasVscrol ( )
{

  return ( this ? vscrol : UNDEF );

}

/******************************************************************************/
/**
\brief  IsWorkspace

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWorkspace"

logical OSWindow :: IsWorkspace ( ) const
{

  return ( this ? workspace : UNDEF );

}

/******************************************************************************/
/**
\brief  OSWindow

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSWindow"

     OSWindow :: OSWindow ( )
                     : OStyle (),
  workspace(NO),
  vscrol(UNDEF),
  hscrol(UNDEF)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  is_workspace
\param  vscroll
\param  hscroll
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSWindow"

     OSWindow :: OSWindow (OStyle bcOStyle, logical is_workspace, logical vscroll, logical hscroll )
                     : OStyle (bcOStyle),
  workspace(is_workspace),
  vscrol(vscroll),
  hscrol(hscroll)
{
/*
  "OSWindow("
  + ADK_Style::Generate()
  + ", " + workspace
  + ", " + vscroll
  + ", " + hscroll
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

logical OSWindow :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  workspace = ph->GPH("workspace")->IsTrue();
  vscrol    = ph->GPH("vscrol")->IsTrue();
  hscrol    = ph->GPH("hscrol")->IsTrue();

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSWindow :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSWindow


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSWindow"

     OSWindow :: ~OSWindow ( )
{

  if ( !Deleting() )
    Reset();

}


