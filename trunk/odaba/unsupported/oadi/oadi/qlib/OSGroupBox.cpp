/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSGroupBox



\date     $Date: 2006/04/28 16:54:35,31 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSGroupBox"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sOSGroupBox.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSGroupBox :: CastPointer (char *typenames )
{

  return (   !typenames                      ? NULL
           : !strcmp(typenames,"OSGroupBox") ? this
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

int32 OSGroupBox :: CreateInstance (void **instptrp )
{
  *instptrp = new OSGroupBox();
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

char *OSGroupBox :: GetObjectType ( )
{

  return("OSGroupBox");

}

/******************************************************************************/
/**
\brief  OSGroupBox

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSGroupBox"

     OSGroupBox :: OSGroupBox ( )
                     : OStyle (),
  vertical(NO)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  vertical
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSGroupBox"

     OSGroupBox :: OSGroupBox (OStyle bcOStyle, logical vertical )
                     : OStyle (bcOStyle),
  vertical(vertical)
{
/*
  "OSGroupBox("
  +        ADK_Style::Generate()
  + ", " + vertical
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

logical OSGroupBox :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  vertical = ph->GetInt("vertical");

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSGroupBox :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSGroupBox


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSGroupBox"

     OSGroupBox :: ~OSGroupBox ( )
{

  if ( !Deleting() )
    Reset();

}


