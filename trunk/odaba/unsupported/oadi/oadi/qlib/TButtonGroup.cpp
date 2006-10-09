/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TButtonGroup



\date     $Date: 2006/04/28 15:20:48,87 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TButtonGroup"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODControl.hpp>
#include  <sODWindow.hpp>
#include  <sOElementStyle.hpp>
#include  <sOSButtonGroup.hpp>
#include  <sTButtonGroup.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TButtonGroup :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"TButtonGroup")  ? this
                                                : TField::CastPointer(typenames) );

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

int32 TButtonGroup :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TButtonGroup();
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

logical TButtonGroup :: DoCreate ( )
{
  OSButtonGroup      *obuttongroup = Style();
  logical             term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                          ERROR

  if ( !complexWidget )
    if ( !(complexWidget = ComplexWidgetParent()->CreateSubWindow(elementStyle->get_sys_ident())) )
                                                     OADIERR(95)
  
  if ( complexWidget->CreateClientArea(elementStyle->GetControlName(),
                                       NO,
                                       elementStyle->get_displayLevel(),
                                       YES, 
                                       WT_ButtonGroup,obuttongroup->get_vertical(),
                                       obuttongroup->get_exclusive()) )
                                                     ERROR
  complexWidget->SetExtraData(this);
  
  if ( elementStyle->get_docking_area() )
    complexWidget->CreateDockingArea();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoCreated

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreated"

logical TButtonGroup :: DoCreated ( )
{
  DAlign      *align;
  logical term = NO;
BEGINSEQ
  if ( TField::DoCreated() )                         ERROR
  if ( !complexWidget )                              ERROR
  
  align = elementStyle->Align();
//  if ( align->get_arrange() == AT_Grid )
//    complexWidget->CreateLayout(DSize(0,0),align->get_margin());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Style

\return style

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSButtonGroup *TButtonGroup :: Style ( ) const
{

//  return (OSWindow *)style;
  return OI_CAST(OSButtonGroup,style);

}

/******************************************************************************/
/**
\brief  TButtonGroup

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TButtonGroup"

     TButtonGroup :: TButtonGroup ( )
                     : TField ()
{


}


