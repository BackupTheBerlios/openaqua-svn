/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TSplitter



\date     $Date: 2006/04/28 15:22:42,37 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TSplitter"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODWindow.hpp>
#include  <sOElementStyle.hpp>
#include  <sOSSplitter.hpp>
#include  <sTSplitter.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TSplitter :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TSplitter")    ? this
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

int32 TSplitter :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TSplitter();
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

logical TSplitter :: DoCreate ( )
{
  OSSplitter         *osplitter = Style();
  logical             term = NO;
BEGINSEQ
// 0.1 (4)
  if ( TField::DoCreate() )                          ERROR

  if ( !complexWidget )
    if ( !(complexWidget = ComplexWidgetParent()->CreateSubWindow(elementStyle->get_sys_ident())) )
                                                     OADIERR(95)
  
  if ( complexWidget->CreateClientArea(elementStyle->GetControlName(),
                                       NO,
                                       elementStyle->get_displayLevel(),
                                       YES, 
                                       WT_Splitter,!osplitter->get_horizontal(),NO) )
                                                     ERROR
  complexWidget->SetExtraData(this);
  
  if ( osplitter->get_hwidth() )
    complexWidget->SetHandleWidth(osplitter->get_hwidth());

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

logical TSplitter :: DoCreated ( )
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

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSSplitter *TSplitter :: Style ( ) const
{

//  return (OSWindow *)style;
  return OI_CAST(OSSplitter,style);

}

/******************************************************************************/
/**
\brief  TSplitter

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TSplitter"

     TSplitter :: TSplitter ( )
                     : TField ()
{


}


