/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TListBoxField

\brief    


\date     $Date: 2006/06/20 12:59:20,37 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TListBoxField"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOComboBox.hpp>
#include  <sOComboListBox.hpp>
#include  <sODControl.hpp>
#include  <sODSItem.hpp>
#include  <sODataSource.hpp>
#include  <sOField.hpp>
#include  <sOFieldControl.hpp>
#include  <sOListLayout.hpp>
#include  <sOListView.hpp>
#include  <sOSListBox.hpp>
#include  <sTListBoxField.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 


\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TListBoxField :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TListBoxField")? this
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

int32 TListBoxField :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TListBoxField();
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

logical TListBoxField :: DoCreate ( )
{
  OSListBox         *lstyle = Style();  
  logical            check  = lstyle->get_check_box();
  logical            msel   = lstyle->get_multisel();
  logical            sort   = lstyle->get_sorted();
  logical            transposed = lstyle->get_transposed();
  logical            term   = NO;
BEGINSEQ
// 7,2 (73)
  if ( TField::DoCreate() )                          ERROR

  if ( !ProvideComplexWidget() )                     ERROR
  
statistics5.Start();
  if ( lstyle->get_tree() )
    term = complexWidget->CreateTreeView(elementStyle->GetControlName(),check,msel,
                                         sort,elementStyle->get_displayLevel(),lstyle->get_fast_list());
  else if ( lstyle->get_table_grid() )
    term = complexWidget->CreateTable(elementStyle->GetControlName(),msel,transposed,
                                      elementStyle->get_displayLevel());
  else
    switch ( (lstyle->get_edit() ? 1 : 0) + (lstyle->get_drop() ? 2 : 0) )
    {
      case 0+0 : term = complexWidget->CreateListView(elementStyle->GetControlName(),check,msel,
                                                      sort,elementStyle->get_displayLevel(),lstyle->get_fast_list());
                 break;
      case 1+0 : term = complexWidget->CreateComboListBox(elementStyle->GetControlName(),check,msel,
                                                          sort,elementStyle->get_displayLevel());
                 break;
      case 0+2 : term = complexWidget->CreateComboBox(elementStyle->GetControlName(),NO,
                                                      sort,elementStyle->get_displayLevel());
                 break;
      case 1+2 : term = complexWidget->CreateComboBox(elementStyle->GetControlName(),YES,
                                                      sort,elementStyle->get_displayLevel());
                 break;
      default  : ;
    }
  
  if ( term )                                       OADIGUICERR

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
\brief  DoCreated - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreated"

logical TListBoxField :: DoCreated ( )
{
  logical             term  = NO;
BEGINSEQ
//  if ( !b )
//    b = new BListBoxField(this);
  
  if ( TField::DoCreated() )                         ERROR

  complexWidget->UpdateScrollBars(Style()->get_hscrol(),Style()->get_vscrol());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Style - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSListBox *TListBoxField :: Style ( ) const
{

  return OI_CAST(OSListBox,style);

}

/******************************************************************************/
/**
\brief  TListBoxField - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TListBoxField"

     TListBoxField :: TListBoxField ( )
                     : TField ()
{



}


