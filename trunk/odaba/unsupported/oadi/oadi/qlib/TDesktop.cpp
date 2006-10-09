/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TDesktop



\date     $Date: 2006/04/28 15:19:53,18 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TDesktop"

#include  <poadi.h>
#include  <sOApplicationO.hpp>
#include  <sODDesktop.hpp>
#include  <sODesktopO.hpp>
#include  <sOElementStyle.hpp>
#include  <sOField.hpp>
#include  <sTControl.hpp>
#include  <sTProjectManager.hpp>
#include  <sTDesktop.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TDesktop :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TDesktop")     ? this
                                               : TWidgetControl::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateControl

\return rc

\param  tc_ptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateControl"

int32 TDesktop :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TDesktop();
  return(0);

}

/******************************************************************************/
/**
\brief  DoCreate

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TDesktop :: DoCreate ( )
{
  logical term = NO;
BEGINSEQ
  complexWidget = new ODDesktop(); // setzt frameInnerWidget und frameOuterWidget

  elementStyle->SetSize(((ODDesktop *)complexWidget)->GetSize());

  if ( TWidgetControl::DoCreate() )                     ERROR


RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  TDesktop

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TDesktop"

     TDesktop :: TDesktop ( )
                     : TWidgetControl ()
{


}

/******************************************************************************/
/**
\brief  ~TDesktop


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TDesktop"

     TDesktop :: ~TDesktop ( )
{

}


