/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TGroupBox



\date     $Date: 2006/04/28 15:34:08,15 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TGroupBox"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODControl.hpp>
#include  <sODWindow.hpp>
#include  <sOElementStyle.hpp>
#include  <sOSGroupBox.hpp>
#include  <sTGroupBox.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TGroupBox :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TGroupBox")   ? this
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

int32 TGroupBox :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TGroupBox();
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

logical TGroupBox :: DoCreate ( )
{
  OSGroupBox         *ogroupbox = Style();
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
                                       WT_GroupBox,ogroupbox->get_vertical(),NO) )
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

logical TGroupBox :: DoCreated ( )
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

OSGroupBox *TGroupBox :: Style ( ) const
{

//  return (OSWindow *)style;
  return OI_CAST(OSGroupBox,style);

}

/******************************************************************************/
/**
\brief  TGroupBox

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TGroupBox"

     TGroupBox :: TGroupBox ( )
                     : TField ()
{


}


