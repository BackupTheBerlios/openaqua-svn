/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OMenu



\date     $Date: 2006/04/28 16:50:43,67 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OMenu"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sOEventActionControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOResource.hpp>
#include  <sOStyleAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sOMenu.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OMenu :: CastPointer (char *typenames )
{

  return (   !typenames                 ? NULL
           : !strcmp(typenames,"OMenu") ? this
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

int32 OMenu :: CreateInstance (void **instptrp )
{

  *instptrp = new OMenu();
  return(0);

}

/******************************************************************************/
/**
\brief  OMenu

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMenu"

     OMenu :: OMenu ( )
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
#define    MOD_ID  "OMenu"

     OMenu :: OMenu (OEventAction bcOEventAction, OFrameStyle frameStyle )
                     : OEventAction (bcOEventAction),
  frameStyle(frameStyle)
{
/*
  "OMenu("
  +        ADK_EventAction::Generate()
  + ", " + ADK_FrameStyle::Generate()
  + ")";
  !! ReadAction("menu_control")
  !! no Framestyle set in Read
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

logical OMenu :: Read (PropertyHandle *ph )
{
  logical           term = NO;
  ReadAction(ph,"menu_control");
  
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

void OMenu :: Reset ( )
{

  OEventAction::Reset();

}

/******************************************************************************/
/**
\brief  ~OMenu


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OMenu"

     OMenu :: ~OMenu ( )
{

  if ( !Deleting() )
    Reset();

}


