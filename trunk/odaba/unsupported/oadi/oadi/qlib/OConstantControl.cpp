/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OConstantControl



\date     $Date: 2006/04/27 19:42:15,56 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OConstantControl"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sPropertyHandle.hpp>
#include  <sOConstantControl.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OConstantControl :: CastPointer (char *typenames )
{

  return (   !typenames                            ? NULL
           : !strcmp(typenames,"OConstantControl") ? this
                                                   : OStyleAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  OConstantControl

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OConstantControl"

     OConstantControl :: OConstantControl ( )
                     : OStyleAction (),
  inner_distance(0)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyleAction
\param  grid_size
\param  inner_distance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OConstantControl"

     OConstantControl :: OConstantControl (OStyleAction bcOStyleAction, DSize grid_size, int16 inner_distance )
                     : OStyleAction (bcOStyleAction),
  grid_size(grid_size),
  inner_distance(inner_distance)
{
  if(grid_size.Width==AUTO && grid_size.Height==AUTO)
    this->grid_size      = DSize(align.get_horiCells(),align.get_vertCells());
  if(inner_distance == AUTO)
    this->inner_distance = distance;
    

/*
  "OConstantControl("
  + ADK_StyleAction::Generate()
  + ", DSize(AUTO,AUTO)"   // from style action
  + ", AUTO"               // from style action
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

logical OConstantControl :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyleAction::Read(ph);
  
  grid_size      = DSize(align.get_horiCells(),align.get_vertCells());
  inner_distance = distance;

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OConstantControl :: Reset ( )
{

  grid_size = DSize();

  OStyleAction::Reset();


}

/******************************************************************************/
/**
\brief  ~OConstantControl


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OConstantControl"

     OConstantControl :: ~OConstantControl ( )
{
  if ( !Deleting() )
    Reset();
}


