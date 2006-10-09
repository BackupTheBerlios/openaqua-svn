/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TTimeField

\brief    


\date     $Date: 2006/06/20 12:55:58,62 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TTimeField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sODControl.hpp>
#include  <sOFieldControl.hpp>
#include  <sTControl.hpp>
#include  <sTTimeField.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TTimeField :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"TTimeField")    ? this
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

int32 TTimeField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TTimeField();
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

logical TTimeField :: DoCreate ( )
{
  logical      term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                             ERROR

  if ( !ProvideComplexWidget() )                     ERROR
    
  if ( complexWidget->CreateTimeEdit(elementStyle->GetControlName(),
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

logical TTimeField :: DoCreated ( )
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
\brief  TTimeField - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TTimeField"

     TTimeField :: TTimeField ( )
                     : TField ()
{



}


