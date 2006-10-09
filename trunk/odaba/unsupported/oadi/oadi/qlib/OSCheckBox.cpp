/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSCheckBox



\date     $Date: 2006/04/28 16:53:38,82 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSCheckBox"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOSCheckBox.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSCheckBox :: CastPointer (char *typenames )
{

  return (   !typenames                      ? NULL
           : !strcmp(typenames,"OSCheckBox") ? this
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

int32 OSCheckBox :: CreateInstance (void **instptrp )
{
  *instptrp = new OSCheckBox();
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

char *OSCheckBox :: GetObjectType ( )
{

  return("OSCheckBox");

}

/******************************************************************************/
/**
\brief  OSCheckBox

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSCheckBox"

     OSCheckBox :: OSCheckBox ( )
                     : OStyle ()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSCheckBox"

     OSCheckBox :: OSCheckBox (OStyle bcOStyle )
                     : OStyle (bcOStyle)
{
/*
  "OSCheckBox("
  + ADK_Style::Generate()
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSCheckBox :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSCheckBox


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSCheckBox"

     OSCheckBox :: ~OSCheckBox ( )
{

  if ( !Deleting() )
    Reset();

}


