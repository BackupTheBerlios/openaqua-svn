/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TDateField

\brief    


\date     $Date: 2006/06/20 12:55:42,51 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TDateField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sODControl.hpp>
#include  <sOFieldControl.hpp>
#include  <sTControl.hpp>
#include  <sTDateField.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TDateField :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"TDateField")    ? this
                                                : TField::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateControl - 


\return rc - 

\param  tc_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateControl"

int32 TDateField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TDateField();
  return(0);

}

/******************************************************************************/
/**
\brief  DoCreate - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TDateField :: DoCreate ( )
{
  logical      term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                             ERROR

  if ( !ProvideComplexWidget() )                     ERROR
    
  if ( complexWidget->CreateDateEdit(elementStyle->GetControlName(),
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
\brief  DoCreated - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreated"

logical TDateField :: DoCreated ( )
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
\brief  TDateField - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TDateField"

     TDateField :: TDateField ( )
                     : TField ()
{



}


