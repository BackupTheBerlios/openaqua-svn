/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TCheckBoxField



\date     $Date: 2006/04/28 15:21:01,07 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TCheckBoxField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOCheckBox.hpp>
#include  <sODControl.hpp>
#include  <sOFieldControl.hpp>
#include  <sTCheckBoxField.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TCheckBoxField :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"TCheckBoxField")? this
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

int32 TCheckBoxField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TCheckBoxField();
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

logical TCheckBoxField :: DoCreate ( )
{
  OCheckBox   *cb;
  logical      term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                             ERROR

  if ( !ProvideComplexWidget() )                     ERROR
    
  if ( complexWidget->CreateCheckBox(elementStyle->GetControlName(),
                                     elementStyle->get_displayLevel()) )
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

logical TCheckBoxField :: DoCreated ( )
{
  logical    term = NO;
BEGINSEQ
  if ( TField::DoCreated() )                         ERROR
  
//  if ( complexWidget->Activate() )                   ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  TCheckBoxField

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TCheckBoxField"

     TCheckBoxField :: TCheckBoxField ( )
                     : TField ()
{


}


