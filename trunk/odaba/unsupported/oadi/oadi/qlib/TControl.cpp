/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TControl

\brief    Control interface
          The  control  interface  procides  the  connection between the control
          resource  definition  and  the  GUI  object  for displaying the design
          resource.  Control  interfaces  can  be  more specialized as widget or
          menu items. 
          Control  interfaces  form  a  hierarchy,  which  is  implemented  as 
          children/parent relationship.

\date     $Date: 2006/04/30 19:05:43,78 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TControl"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOAction.hpp>
#include  <sOElementStyle.hpp>
#include  <sOFieldControl.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOStyle.hpp>
#include  <sOWidget.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sTWidgetControl.hpp>
#include  <sTControl.hpp>


/******************************************************************************/
/**
\brief  Activate


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

void TControl :: Activate ( )
{


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

void *TControl :: CastPointer (char *typenames )
{
  return (   !typenames                      ? NULL
           : !strcmp(typenames,"TControl")   ? this
                                             : TComponent::CastPointer(typenames) );
}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void TControl :: Close ( )
{
  if ( elementStyle )
    elementStyle->Release();
  elementStyle = NULL;
  
  TComponent::Close();


}

/******************************************************************************/
/**
\brief  Create

\return term

\param  pTControl
\param  pOElementStyle
\param  pOFrameStyle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical TControl :: Create (TControl *pTControl, OElementStyle *pOElementStyle, OFrameStyle *pOFrameStyle )
{
  logical                 term = NO;
BEGINSEQ
  pOElementStyle->Reserve();
  elementStyle = pOElementStyle;

  style        = elementStyle->Style();
  frameStyle   = pOFrameStyle;

  if ( TComponent::Create(pTControl) )                ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FieldControl

\return fcontrol

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldControl"

OFieldControl *TControl :: FieldControl ( )
{

  return OI_CAST(OFieldControl,elementStyle);

}

/******************************************************************************/
/**
\brief  IsCreated

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCreated"

logical TControl :: IsCreated ( )
{

  return(elementStyle ? YES : NO);

}

/******************************************************************************/
/**
\brief  Show


\param  fShow
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

void TControl :: Show (logical fShow )
{


}

/******************************************************************************/
/**
\brief  TControl

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TControl"

     TControl :: TControl ( )
                     : TComponent (),
  elementStyle(NULL),
  style(NULL),
  frameStyle(NULL)
{


}

/******************************************************************************/
/**
\brief  ~TControl

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TControl"

     TControl :: ~TControl ( )
{

  Deleting();
  Close();

}


