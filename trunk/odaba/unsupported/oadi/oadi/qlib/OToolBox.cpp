/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OToolBox



\date     $Date: 2006/04/28 16:56:36,40 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OToolBox"

#include  <poadi.h>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sOToolBox.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OToolBox :: CastPointer (char *typenames )
{

  return (   !typenames                    ? NULL
           : !strcmp(typenames,"OToolBox") ? this
                                           : OEventAction::CastPointer(typenames) );

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

int32 OToolBox :: CreateInstance (void **instptrp )
{

  *instptrp = new OToolBox();
  return(0);

}

/******************************************************************************/
/**
\brief  OToolBox

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolBox"

     OToolBox :: OToolBox ( )
                     : OEventAction (),
  frameStyle()
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOEventAction
\param  frameStyle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolBox"

     OToolBox :: OToolBox (OEventAction bcOEventAction, OFrameStyle frameStyle )
                     : OEventAction (bcOEventAction),
  frameStyle(frameStyle)
{
/*
  "OToolBox("
  + ADK_EventAction::Generate()
  + ", " + frameStyle.Generate() !! not in read
  + ")";
  ReadAction("box_control");
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

logical OToolBox :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  ReadAction(ph,"box_control");
  
  OResource::Reset();
  OStyleElement::Read(ph);
  

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OToolBox :: Reset ( )
{

  OEventAction::Reset();

}

/******************************************************************************/
/**
\brief  ~OToolBox


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OToolBox"

     OToolBox :: ~OToolBox ( )
{
  if ( !Deleting() )
    Reset();
}


