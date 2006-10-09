/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TRadioGroup



\date     $Date: 2006/04/28 15:22:29,68 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TRadioGroup"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODControl.hpp>
#include  <sOElementStyle.hpp>
#include  <sTRadioGroup.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TRadioGroup :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TRadioGroup")  ? this
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

int32 TRadioGroup :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TRadioGroup();
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

logical TRadioGroup :: DoCreate ( )
{
  OSRadioGroup           *ostyle = Style();
  char                   *text   = NULL;
  int                     no_strips;
  logical                 hori_strip;
  logical                 term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                          ERROR

  if ( !ProvideComplexWidget() )                     ERROR
  
  if ( hori_strip = ostyle->get_horizontal() > 0 ? YES : NO )
    no_strips = ostyle->get_horizontal();
  else
    if ( !(no_strips = ostyle->get_vertical()) )
      no_strips = 1;
  
  if ( ostyle->get_group_label() )
    text = (char *)elementStyle->get_textDefinitions().GetTitle();
    
  if ( complexWidget->CreateRadioButtons(elementStyle->GetControlName(),text,
                                         elementStyle->get_displayLevel(),
                                         ostyle->AutoResize(),
                                         no_strips,hori_strip) )         
                                                     OADIGUICSERR(106)
  complexWidget->SetExtraData(this);

RECOVER
  RemoveComplexWidget();
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

logical TRadioGroup :: DoCreated ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( TField::DoCreated() )                         ERROR 
  
  complexWidget->UpdateScrollBars(Style()->HasHscrol(),Style()->HasVscrol());

//  if ( complexWidget->Activate() )                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Style

\return pOSRadioGroup

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSRadioGroup *TRadioGroup :: Style ( )
{

  return OI_CAST(OSRadioGroup,style);

}

/******************************************************************************/
/**
\brief  TRadioGroup


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TRadioGroup"

     TRadioGroup :: TRadioGroup ( )
                     : TField ()
{
}


