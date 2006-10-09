/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OActionControl



\date     $Date: 2006/04/27 15:04:25,37 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OActionControl"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOADKFactory.hpp>
#include  <sOCAU_Action.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOActionControl.hpp>


/******************************************************************************/
/**
\brief  Action

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Action"

OCAU_Action *OActionControl :: Action ( ) const
{

  return ( this ? action : NULL );

}

/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OActionControl :: CastPointer (char *typenames )
{

  return (   !typenames                          ? NULL
           : !strcmp(typenames,"OActionControl") ? this
                                                 : OElementStyle::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  OActionControl

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OActionControl"

     OActionControl :: OActionControl ( )
                     : OElementStyle (),
  action(NULL)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOElementStyle
\param  pOCAU_Action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OActionControl"

     OActionControl :: OActionControl (OElementStyle bcOElementStyle, OCAU_Action *pOCAU_Action )
                     : OElementStyle (bcOElementStyle),
  action(pOCAU_Action)
{
/* 
  "OActionControl("
  +        ADK_OElementStyle::Generate()
  + ", " + action.Generate()
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

logical OActionControl :: Read (PropertyHandle *ph )
{
  PropertyHandle    *ep;
  logical            term = NO;
  OElementStyle::Read(ph);

  action = CACHE_READ(ph,"action",OCAU_Action);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OActionControl :: Reset ( )
{
  if ( action )
    action->Release();
  action = NULL;

  OElementStyle::Reset();
}

/******************************************************************************/
/**
\brief  ~OActionControl


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OActionControl"

     OActionControl :: ~OActionControl ( )
{
  if ( !Deleting() )
    Reset();
}


