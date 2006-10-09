/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OBrush

\brief    


\date     $Date: 2006/06/23 18:00:52,94 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OBrush"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOADKFactory.hpp>
#include  <sOBitmap.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOBrush.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OBrush :: CastPointer (char *typenames )
{

  return (   !typenames                  ? NULL
           : !strcmp(typenames,"OBrush") ? this
                                         : OResource::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance - 


\return rc - 

\param  instptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OBrush :: CreateInstance (void **instptrp )
{

  *instptrp = new OBrush();
  return(0);

}

/******************************************************************************/
/**
\brief  OBrush - 


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBrush"

     OBrush :: OBrush ( )
                     : OResource(),
DBrush(CR_Foreground),
  bitmap(NULL)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  bcOResource - 
\param  bcDBrush - 
\param  pOBitmap - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OBrush"

     OBrush :: OBrush (OResource bcOResource, DBrush bcDBrush, OBitmap *pOBitmap )
                     : OResource (bcOResource),
DBrush (bcDBrush),
  bitmap(pOBitmap)
{

  if(pOBitmap)
    pixmap.SetPath(pOBitmap->GetPath());
/*
  "OBrush("
  +        ADK_Resource::Generate()
  + ", " + ADK_DBrush::Generate(role,style,color)
  + ", " + bitmap.Generate()
  + ")";
*/

}

/******************************************************************************/
/**
\brief  Read - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OBrush :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OPersistent::Read(ph);

  role   = (ADK_ColorRole)ph->GetInt("role");
  style  = (ADK_BrushStyle)ph->GetInt("style");
  color  = COLOR2DCOLOR(*ph->GPH("color"));
  
  if ( bitmap = CACHE_READ(ph,"bitmap",OBitmap) )
    pixmap.SetPath(bitmap->GetPath());


  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OBrush :: Reset ( )
{

  if ( bitmap )
    bitmap->Release();
  bitmap = NULL;

  *(DBrush *)this = DBrush(CR_Foreground);
  
  OResource::Reset();


}

/******************************************************************************/
/**
\brief  ~OBrush - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OBrush"

     OBrush :: ~OBrush ( )
{

  if ( !Deleting() )
    Reset();

}


