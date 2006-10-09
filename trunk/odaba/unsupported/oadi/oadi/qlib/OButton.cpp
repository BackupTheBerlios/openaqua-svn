/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OButton



\date     $Date: 2006/05/02 11:37:27,76 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OButton"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOADKFactory.hpp>
#include  <sOEventActionControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOSButton.hpp>
#include  <sOStyleAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sOButton.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OButton :: CastPointer (char *typenames )
{

  return (   !typenames                   ? NULL
           : !strcmp(typenames,"OButton") ? this
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

int32 OButton :: CreateInstance (void **instptrp )
{
  *instptrp = new OButton();
  return(0);
}

/******************************************************************************/
/**
\brief  OButton

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OButton"

     OButton :: OButton ( )
                     : OEventAction (),
  def_opt(NO)

{



}

/******************************************************************************/
/**
\brief  i01


\param  bcOEventAction
\param  frameStyle
\param  def_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OButton"

     OButton :: OButton (OEventAction bcOEventAction, OFrameStyle frameStyle, logical def_opt )
                     : OEventAction (bcOEventAction),
  frameStyle(frameStyle),
  def_opt(def_opt)
{
  style = ADKFACTORY(NULL,OSButton);
/*
  "OButton("
  +        ADK_EventAction::Generate(button_control)
  + ", " + ADK_FrameStyle::Generate()
  + ", " + default
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Open

\return pTControl

\param  tparent
\param  active_f
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

TControl *OButton :: Open (TControl *tparent, logical active_f )
{
  TControl                *t;
// The owner of fieldControl has to be the parental styleAction
  
  if ( t = OpenControl("OButton",tparent,&frameStyle,this) )
    if ( active_f )
      t->Activate();

  return(t);
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

logical OButton :: Read (PropertyHandle *ph )
{
  logical              term = NO;
  ReadAction(ph,"button_control");
  OResource::Read(ph);
  UpdateStyleElement(ph);
  
  def_opt = ph->GetInt("default");

  if ( style && !OI_CAST(OSButton,style) )
  {
    style->Release();
    style = NULL;
  }
    
//  if ( !style )
//    style = ADKFACTORY(NULL,OSButton);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OButton :: Reset ( )
{
  OEventAction::Reset();
  
  def_opt = UNDEF;
}

/******************************************************************************/
/**
\brief  set_position


\param  position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_position"

void OButton :: set_position (DPoint position )
{

  action_control->get_bounds().Origin = position;

}

/******************************************************************************/
/**
\brief  ~OButton


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OButton"

     OButton :: ~OButton ( )
{

  if ( !Deleting() )
    Reset();
}


