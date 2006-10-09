/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OLayout

\brief    


\date     $Date: 2006/06/26 12:00:18,61 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OLayout"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sDLayout.hpp>
#include  <sOADKFactory.hpp>
#include  <sOBitmap.hpp>
#include  <sOBrush.hpp>
#include  <sOColorGroup.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOLayout.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OLayout :: CastPointer (char *typenames )
{

  return (   !typenames                   ? NULL
           : !strcmp(typenames,"OLayout") ? this
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

int32 OLayout :: CreateInstance (void **instptrp )
{

  *instptrp = new OLayout();
  return(0);

}

/******************************************************************************/
/**
\brief  DoDestroying - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoDestroying"

void OLayout :: DoDestroying ( )
{

  Reset();

}

/******************************************************************************/
/**
\brief  OLayout - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OLayout"

     OLayout :: OLayout ( )
                     : OResource (),
DLayout (),
  lshape(NULL),
  lactive(NULL),
  linactive(NULL),
  ldisabled(NULL)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  bcOResource - 
\param  bcDLayout - 
\param  lshape - 
\param  lactive - 
\param  linactive - 
\param  ldisabled - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OLayout"

     OLayout :: OLayout (OResource bcOResource, DLayout bcDLayout, OBitmap *lshape, OColorGroup *lactive, OColorGroup *linactive, OColorGroup *ldisabled )
                     : OResource (bcOResource),
DLayout (bcDLayout),
  lshape(lshape),
  lactive(lactive),
  linactive(linactive),
  ldisabled(ldisabled)
{
  int32          i;
    for ( i = 0; i < 20; i++ )
    {
      active[i]   = lactive   ? (DBrush *)lactive->GetBrush(i)   : (DBrush *)NULL;
      inactive[i] = linactive ? (DBrush *)linactive->GetBrush(i) : (DBrush *)NULL;
      disabled[i] = ldisabled ? (DBrush *)ldisabled->GetBrush(i) : (DBrush *)NULL;
    }

/* 
  "OLayout("
  +        ADK_Resource::Generate()
  + ", " + ADK_DLayout::Generate() // no mention in read
  + ", " + shape.Generate()
  + ", " + active.Generate()
  + ", " + inactive.Generate()
  + ", " + disabled.Generate()
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

logical OLayout :: Read (PropertyHandle *ph )
{
  int                     i;
  logical                 term = NO;
  OResource::Read(ph);

  if ( lshape = CACHE_READ(ph,"shape",OBitmap) )
    shape.SetPath(lshape->GetPath());

  if ( lactive = CACHE_READ(ph,"active",OColorGroup) )
    for ( i = 0; i < 20; i++ )
      active[i] = lactive->GetBrush(i);

  if ( linactive = CACHE_READ(ph,"inactive",OColorGroup) )
    for ( i = 0; i < 20; i++ )
      inactive[i] = linactive->GetBrush(i);

  if ( ldisabled = CACHE_READ(ph,"disabled",OColorGroup) )
    for ( i = 0; i < 20; i++ )
      disabled[i] = ldisabled->GetBrush(i);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OLayout :: Reset ( )
{

  if ( lshape )
    lshape->Release();
  lshape = NULL;

  if ( lactive )
    lactive->Release();
  lactive = NULL;
  
  if ( linactive )
    linactive->Release();
  linactive = NULL;

  
  if ( ldisabled )
    ldisabled->Release();
  ldisabled = NULL;

  *(DLayout *)this = DLayout();
  OResource::Reset();



}

/******************************************************************************/
/**
\brief  ~OLayout - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OLayout"

     OLayout :: ~OLayout ( )
{

  if ( !Deleting() )
    Reset();
  DLayout::Reset(NO);// removes references set by Read (would assert otherwise)

}


