/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OFont_



\date     $Date: 2006/04/28 16:44:07,56 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFont_"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sDFont.hpp>
#include  <sOResource.hpp>
#include  <sPropertyHandle.hpp>
#include  <sResourceCache.hpp>
#include  <sTProjectManager.hpp>
#include  <sOFont_.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OFont_ :: CastPointer (char *typenames )
{

  return (   !typenames                  ? NULL
           : !strcmp(typenames,"OFont_") ? this
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

int32 OFont_ :: CreateInstance (void **instptrp )
{
  *instptrp = new OFont_();
  return(0);
}

/******************************************************************************/
/**
\brief  OFont_

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFont_"

     OFont_ :: OFont_ ( )
                     : OResource (),
DFont ()
{

}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  bcDFont
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFont_"

     OFont_ :: OFont_ (OResource bcOResource, DFont bcDFont )
                     : OResource (bcOResource),
DFont (bcDFont)
{
/*
  "OFont_("
  +        ADK_Resource::Generate()
  + ", " + ADK_DFont::Generate()
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

logical OFont_ :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OResource::Read(ph);

  FromADKFont(ph);

  return(term);
}

/******************************************************************************/
/**
\brief  ReadFromResource

\return pOFont

\param  font_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadFromResource"

OFont_ *__cdecl OFont_ :: ReadFromResource (char *font_name )
{
  OFont_          *pOFont = NULL;
  if ( font_name && *font_name ) 
    pOFont = TProjectManager::TPM->Cache()->ReadFont(font_name);

  return(pOFont);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OFont_ :: Reset ( )
{
  *(DFont *)this = DFont();
  
  OResource::Reset();
}

/******************************************************************************/
/**
\brief  ~OFont_

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OFont_"

     OFont_ :: ~OFont_ ( )
{

  if ( !Deleting() )
    Reset();

}


