/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TButtonBoxField

\brief    


\date     $Date: 2006/06/20 12:55:50,53 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TButtonBoxField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sODControl.hpp>
#include  <sOFieldControl.hpp>
#include  <sTControl.hpp>
#include  <sTButtonBoxField.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TButtonBoxField :: CastPointer (char *typenames )
{

  return (   !typenames                           ? NULL
           : !strcmp(typenames,"TButtonBoxField") ? this
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

int32 TButtonBoxField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TButtonBoxField();
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

logical TButtonBoxField :: DoCreate ( )
{
  logical      term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                             ERROR

  if ( !ProvideComplexWidget() )                     ERROR
    
  if ( complexWidget->CreateToolBox(elementStyle->GetControlName(),
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

logical TButtonBoxField :: DoCreated ( )
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
\brief  TButtonBoxField - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TButtonBoxField"

     TButtonBoxField :: TButtonBoxField ( )
                     : TField ()
{



}


