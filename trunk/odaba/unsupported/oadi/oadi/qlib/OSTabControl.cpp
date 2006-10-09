/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSTabControl



\date     $Date: 2006/04/28 16:56:36,53 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSTabControl"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sOSTabControl.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSTabControl :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OSTabControl") ? this
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

int32 OSTabControl :: CreateInstance (void **instptrp )
{
  *instptrp = new OSTabControl();
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

char *OSTabControl :: GetObjectType ( )
{

  return("OSTabControl");

}

/******************************************************************************/
/**
\brief  OSTabControl

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSTabControl"

     OSTabControl :: OSTabControl ( )
                     : OStyle (),
  position(),
  shape(),
  fix_child()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  iposition
\param  ishape
\param  ifix_child
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSTabControl"

     OSTabControl :: OSTabControl (OStyle bcOStyle, int16 iposition, int8 ishape, int8 ifix_child )
                     : OStyle (bcOStyle),
  position((ADK_VertPos)iposition),
  shape((ADK_Shape)ishape),
  fix_child((ADK_VertPos)ifix_child)
{
/*
  "OSTabControl("
  + ADK_Style::Generate()
  + ", " + position
  + ", " + shape
  + ", " + fixed_area
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

logical OSTabControl :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  position  = (ADK_VertPos)ph->GetInt("position");
  shape     = (ADK_Shape)ph->GetInt("shape");
  fix_child = (ADK_VertPos)ph->GetInt("fixed_area");
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSTabControl :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSTabControl


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSTabControl"

     OSTabControl :: ~OSTabControl ( )
{

  if ( !Deleting() )
    Reset();

}


