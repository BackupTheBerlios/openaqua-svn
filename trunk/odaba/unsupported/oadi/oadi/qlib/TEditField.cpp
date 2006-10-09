/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TEditField



\date     $Date: 2006/05/03 23:23:15,71 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TEditField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <cHighLighting.h>
#include  <sODControl.hpp>
#include  <sOElementStyle.hpp>
#include  <sOHighlightRule.hpp>
#include  <sOHighlighter.hpp>
#include  <sOMultiLineEdit.hpp>
#include  <sOSEdit.hpp>
#include  <sOSingleLineEdit.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTEditField.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TEditField :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TEditField")   ? this
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

int32 TEditField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TEditField();
  return(0);

}

/******************************************************************************/
/**
\brief  DoCreate - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TEditField :: DoCreate ( )
{
  OSEdit          *edit_style = Style();
  OHighlighter    *ohl        = NULL;
  HighLighting     hl_type    = HL_none;
  logical          term       = NO;
BEGINSEQ
// 0.5 (45)
  if ( TField::DoCreate() )                          ERROR

  if ( !ProvideComplexWidget() )                     ERROR

statistics5.Start();
  if ( edit_style->get_multiLine() )
  {
    if ( edit_style->get_rich_text() )
    {
      if ( complexWidget->CreateRichTextEdit(elementStyle->GetControlName(),
                                             elementStyle->get_displayLevel()) )
                                                     OADIGUICERR
    }
    else
    {
      if ( ohl = edit_style->get_highlighter() )
        hl_type = HL_UserDefined;
      if ( TestSysVariable("CODE_EDITOR","YES") )
        hl_type = ohl ? HL_ExtendedStandardCode : HL_StandardCode;
        
      if ( complexWidget->CreateMultiLineEdit(elementStyle->GetControlName(),
                                              elementStyle->get_displayLevel(),
                                              hl_type) )
                                                     OADIGUICERR
      SetupHighlightRules(ohl);
    }
  }
  else 
  {
    if ( complexWidget->CreateSingleLineEdit(elementStyle->GetControlName(),
                                             elementStyle->get_displayLevel(),
                                             edit_style->HasPassword()) )
                                                     OADIGUICERR
  }
  
  complexWidget->SetExtraData(this);
RECOVER
  RemoveComplexWidget();
  term = YES;
ENDSEQ
statistics5.Stop();
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

logical TEditField :: DoCreated ( )
{
  logical   term = NO;
BEGINSEQ
  if ( TField::DoCreated() )                         ERROR
  
  complexWidget->UpdateScrollBars(Style()->HasHscrol(),Style()->HasVscrol());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupHighlightRules

\return term

\param  shl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupHighlightRules"

logical TEditField :: SetupHighlightRules (OHighlighter *shl )
{
  OHighlightRule         *hr;
  OSyntaxClass           *sc;
  logical                 term = NO;
BEGINSEQ
  if ( !shl )                                        LEAVESEQ
    
  DLL(OHighlightRule) hr_list(shl->get_rules());
  while ( hr = hr_list.GetNext() )
  {
    DLL(OSyntaxClass) sc_list(hr->get_syntax_classes());
    while ( sc = sc_list.GetNext() )
      complexWidget->AddHighlightClass(hr->get_sys_ident(),*sc,*hr->get_font());
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Style

\return cptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSEdit *TEditField :: Style ( ) const
{

  return OI_CAST(OSEdit,style);

}

/******************************************************************************/
/**
\brief  TEditField


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TEditField"

     TEditField :: TEditField ( )
                     : TField ()
{


}


