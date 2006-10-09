/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    ODesktop



\date     $Date: 2006/04/29 21:12:36,65 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODesktop"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOFrameStyle.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sODesktop.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *ODesktop :: CastPointer (char *typenames )
{

  return (   !typenames                       ? NULL
           : !strcmp(typenames,"ODesktop")    ? this
           : !strcmp(typenames,"OFrameStyle") ? (OFrameStyle *)this
                                              : OStyleAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  ODesktop

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODesktop"

     ODesktop :: ODesktop ( )
                     : OStyleAction (),
OFrameStyle ()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyleAction
\param  bcOFrameStyle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODesktop"

     ODesktop :: ODesktop (OStyleAction bcOStyleAction, OFrameStyle bcOFrameStyle )
                     : OStyleAction (bcOStyleAction),
OFrameStyle (bcOFrameStyle)
{
  style = new OStyle;
/*
  "ODesktop("
  +        ADK_StyleAction::Generate()
  + ", " + ADK_FrameStyle::Generate()
  + ")";

*/
}

/******************************************************************************/
/**
\brief  Open

\return pTControl

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

TControl *ODesktop :: Open ( )
{
  TControl                 *t = NULL;
  t = OpenControl("ODesktop",NULL,this,this);
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

logical ODesktop :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
BEGINSEQ
  if ( OStyleAction::Read(ph) )                       ERROR
  if ( OFrameStyle::Read(ph) )                        ERROR

  if ( style )
    style->Release();
  style = new OStyle;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void ODesktop :: Reset ( )
{
  OStyleAction::Reset();
//  OFrameStyle::Reset();  hats nicht, muss aber auch nicht, weil alles neu gelesen wird
}

/******************************************************************************/
/**
\brief  ~ODesktop


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODesktop"

     ODesktop :: ~ODesktop ( )
{
  if ( !Deleting() )
    Reset();
}


