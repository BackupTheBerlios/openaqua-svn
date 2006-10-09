/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OCBitmap

\brief    


\date     $Date: 2006/07/09 14:35:43,20 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OCBitmap"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOADKFactory.hpp>
#include  <sOBitmap.hpp>
#include  <sPropertyHandle.hpp>
#include  <sResourceCache.hpp>
#include  <sTProjectManager.hpp>
#include  <sOCBitmap.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 



\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OCBitmap :: CastPointer (char *typenames )
{

  return (   !typenames                    ? NULL
           : !strcmp(typenames,"OCBitmap") ? this
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

int32 OCBitmap :: CreateInstance (void **instptrp )
{

  *instptrp = new OCBitmap();
  return(0);

}

/******************************************************************************/
/**
\brief  GetActiveBitmap - 



\return bitmap - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveBitmap"

OBitmap *OCBitmap :: GetActiveBitmap ( )
{

  return(this ? active : NULL);

}

/******************************************************************************/
/**
\brief  GetDisabledBitmap - 



\return bitmap - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDisabledBitmap"

OBitmap *OCBitmap :: GetDisabledBitmap ( )
{

  return(this ? disabled : NULL);

}

/******************************************************************************/
/**
\brief  GetInactiveBitmap - 



\return bitmap - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInactiveBitmap"

OBitmap *OCBitmap :: GetInactiveBitmap ( )
{

  return(this ? inactive : NULL);

}

/******************************************************************************/
/**
\brief  OCBitmap - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCBitmap"

     OCBitmap :: OCBitmap ( )
                     : OResource (),
  active(NULL),
  inactive(NULL),
  disabled(NULL)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  bcOResource - 
\param  pOBitmapActive - 
\param  pOBitmapInactive - 
\param  pOBitmapDisabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OCBitmap"

     OCBitmap :: OCBitmap (OResource bcOResource, OBitmap *pOBitmapActive, OBitmap *pOBitmapInactive, OBitmap *pOBitmapDisabled )
                     : OResource (bcOResource),
  active(pOBitmapActive),
  inactive(pOBitmapInactive),
  disabled(pOBitmapDisabled)
{

/*
  "OCBitmap("
  +        ADK_Resource::Generate()
  + ", " + aktiv_bitmap.Generate()
  + ", " + inaktiv_bitmap.Generate()
  + ", " + disabled_bitmap.Generate()
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

logical OCBitmap :: Read (PropertyHandle *ph )
{
  PropertyHandle         *bm;
  logical                 term = NO;
  OResource::Read(ph);
/* Bitmaps selbst können nicht in den Cache geschrieben werden
   da es attributes in ADK_Bitmap sind
  active   = CACHE_READ(ph, "aktiv_bitmap",   OBitmap);
  inactive = CACHE_READ(ph, "inaktiv_bitmap", OBitmap);
  disabled = CACHE_READ(ph, "disabled_bitmap", OBitmap);
*/
  bm     = PHREF(ph->GPH("aktiv_bitmap") );
  if ( !bm->GPH("path")->IsEmpty() )
  {
    active = ADKFACTORY(bm,OBitmap);  
    active->Read(bm);
  }

  bm       = PHREF(ph->GPH("inaktiv_bitmap") );
  if ( !bm->GPH("path")->IsEmpty() )
  {
    inactive = ADKFACTORY(bm,OBitmap);  
    inactive->Read(bm);
  }
  
  bm       = PHREF(ph->GPH("disabled_bitmap") );
  if ( !bm->GPH("path")->IsEmpty() )
  {
    disabled = ADKFACTORY(bm,OBitmap);  
    disabled->Read(bm);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ReadFromResource - 



\return pOCBitmap - 

\param  bitmap_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadFromResource"

OCBitmap *__cdecl OCBitmap :: ReadFromResource (char *bitmap_name )
{
  OCBitmap      *pOCBitmap = NULL;
  if ( bitmap_name && *bitmap_name ) 
    pOCBitmap = TProjectManager::TPM->Cache()->ReadBitmap(bitmap_name);

  return(pOCBitmap);
}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OCBitmap :: Reset ( )
{

  delete active;
  active = NULL;

  delete inactive;
  inactive = NULL;

  delete disabled;
  disabled = NULL;

  OResource::Reset();

}

/******************************************************************************/
/**
\brief  ~OCBitmap - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OCBitmap"

     OCBitmap :: ~OCBitmap ( )
{

  if ( !Deleting() )
    Reset();

}


