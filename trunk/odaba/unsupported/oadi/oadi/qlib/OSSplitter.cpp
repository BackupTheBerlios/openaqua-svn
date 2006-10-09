/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSSplitter



\date     $Date: 2006/04/28 16:56:18,37 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSSplitter"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sOSSplitter.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSSplitter :: CastPointer (char *typenames )
{

  return (   !typenames                      ? NULL
           : !strcmp(typenames,"OSSplitter") ? this
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

int32 OSSplitter :: CreateInstance (void **instptrp )
{
  *instptrp = new OSSplitter();
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

char *OSSplitter :: GetObjectType ( )
{

  return("OSSplitter");

}

/******************************************************************************/
/**
\brief  OSSplitter

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSSplitter"

     OSSplitter :: OSSplitter ( )
                     : OStyle (),
  hwidth(0),
  horizontal(NO)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  hwidth
\param  horizontal
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSSplitter"

     OSSplitter :: OSSplitter (OStyle bcOStyle, int32 hwidth, logical horizontal )
                     : OStyle (bcOStyle),
  hwidth(hwidth),
  horizontal(horizontal)
{
/*
  "OSSplitter("
  + ADK_Style::Generate()
  + ", " + handle_width
  + ", " + horizontal
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

logical OSSplitter :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  hwidth     = ph->GetInt("handle_width");
  horizontal = ph->GetInt("horizontal");

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSSplitter :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSSplitter


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSSplitter"

     OSSplitter :: ~OSSplitter ( )
{

  if ( !Deleting() )
    Reset();

}


