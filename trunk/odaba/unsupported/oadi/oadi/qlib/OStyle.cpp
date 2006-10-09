/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OStyle



\date     $Date: 2006/04/28 16:54:53,82 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OStyle"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sDBorder.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOStyle.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OStyle :: CastPointer (char *typenames )
{

  return (   !typenames                  ? NULL
           : !strcmp(typenames,"OStyle") ? this
                                         : OResource::CastPointer(typenames) );

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

int32 OStyle :: CreateInstance (void **instptrp )
{
  *instptrp = new OStyle();
  return(0);
}

/******************************************************************************/
/**
\brief  HasBorder

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasBorder"

logical OStyle :: HasBorder ( )
{

  return border ? YES : NO;

}

/******************************************************************************/
/**
\brief  OStyle

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStyle"

     OStyle :: OStyle ( )
                     : OResource (),
  type(ST_undef),
  border(NO),
  border_style()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  itype
\param  border
\param  dborder
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStyle"

     OStyle :: OStyle (OResource bcOResource, int16 itype, logical border, DBorder dborder )
                     : OResource (bcOResource),
  type((ADK_STYLES)itype),
  border(border),
  border_style(dborder)
{
/*
  "OStyle("
  + ADK_Resource::Generate()
  + ", AUTO" // not in Read
  + ", " + border_style.border
  + ", " + border_style.Generate()
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

logical OStyle :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OResource::Read(ph);

  if ( border = ph->GetInt("border_style.border") )
    border_style.Set((ADK_BorderStyles)ph->GetInt("border_style.style"),
                     (ADK_ShadowStyles)ph->GetInt("border_style.shadow_style"),
                     ph->GetInt("border_style.line_width"),
                     ph->GetInt("border_style.line_strength"));
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OStyle :: Reset ( )
{

  border_style.Reset();
  
  OResource::Reset();

}

/******************************************************************************/
/**
\brief  ~OStyle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OStyle"

     OStyle :: ~OStyle ( )
{

  if ( !Deleting() )
    Reset();

}


