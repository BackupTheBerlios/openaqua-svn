/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OBitmap



\date     $Date: 2006/04/28 16:12:38,60 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OBitmap"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sOBitmap.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OBitmap :: CastPointer (char *typenames )
{

  return (   !typenames                   ? NULL
           : !strcmp(typenames,"OBitmap") ? this
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

int32 OBitmap :: CreateInstance (void **instptrp )
{
  *instptrp = new OBitmap();
  return(0);
}

/******************************************************************************/
/**
\brief  OBitmap

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBitmap"

     OBitmap :: OBitmap ( )
                     : OResource (),
DPixmap ()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  bcDPixmap
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBitmap"

     OBitmap :: OBitmap (OResource bcOResource, DPixmap bcDPixmap )
                     : OResource (bcOResource),
DPixmap (bcDPixmap)
{
/*
  "OBitmap("
  +        ADK_Resource::Generate()
  + ", " + ADK_DPixmap::Generate(path)
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

logical OBitmap :: Read (PropertyHandle *ph )
{
  char       *str;
  logical     term = NO;
  OResource::Read(ph);

  if ( (str = ph->GetString("path")) && *str )
    SetPath(str);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OBitmap :: Reset ( )
{
  *(DPixmap *)this = DPixmap();
  
  OResource::Reset();

}

/******************************************************************************/
/**
\brief  ~OBitmap


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OBitmap"

     OBitmap :: ~OBitmap ( )
{
  if ( !Deleting() )
    Reset();
}


