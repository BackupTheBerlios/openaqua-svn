/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OColorGroup

\brief    


\date     $Date: 2006/06/23 18:00:31,73 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OColorGroup"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sDPixmap.hpp>
#include  <sOADKFactory.hpp>
#include  <sOBrush.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOColorGroup.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OColorGroup :: CastPointer (char *typenames )
{

  return (   !typenames                       ? NULL
           : !strcmp(typenames,"OColorGroup") ? this
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

int32 OColorGroup :: CreateInstance (void **instptrp )
{

  *instptrp = new OColorGroup();
  return(0);

}

/******************************************************************************/
/**
\brief  GetBrush - 


\return obrush - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBrush"

OBrush *OColorGroup :: GetBrush (int32 indx0 )
{

  return ( indx0 >= 0 && indx0 < 20 ? brushs[indx0] : NULL);

}

/******************************************************************************/
/**
\brief  OColorGroup - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OColorGroup"

     OColorGroup :: OColorGroup ( )
                     : OResource (),
  brushs()
{

  memset(brushs,0,sizeof(brushs));

}

/******************************************************************************/
/**
\brief  i01 - 


\param  bcOResource - 
\param  pOBrush - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OColorGroup"

     OColorGroup :: OColorGroup (OResource bcOResource, OBrush **pOBrush )
                     : OResource (bcOResource),
  brushs()
{

  memset(brushs,0,sizeof(brushs));
  for(int i = 0; i<20 && pOBrush[i]; i++)
    brushs[i] = pOBrush[i];
/*
  "OColorGroup("
  +        ADK_Resource::Generate()
  + ", " + colors.GenerateList() !! read
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

logical OColorGroup :: Read (PropertyHandle *ph )
{
  OBrush                 *brush = NULL;
  ADK_ColorRole           brush_role;
  PropertyHandle         *color_ph;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  OResource::Read(ph);

  color_ph = ph->GPH("colors");
  while ( color_ph->Get(indx0++) )
  {
    brush = CACHE_READ(color_ph,NULL,OBrush);  
    brush_role = brush->GetRole();
    if ( brush_role >= 20 || brush_role < 0 )        OADIERR(99)
      
    brushs[brush_role] = brush;
    brush              = NULL;
  }

RECOVER
  delete brush;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OColorGroup :: Reset ( )
{
  int32     indx0 = 0;
  while ( indx0 < 20 )
  {
    brushs[indx0]->Release();
    brushs[indx0] = NULL;
    indx0++;
  }

  OResource::Reset();

}

/******************************************************************************/
/**
\brief  ~OColorGroup - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OColorGroup"

     OColorGroup :: ~OColorGroup ( )
{

  if ( !Deleting() )
    Reset();

}


