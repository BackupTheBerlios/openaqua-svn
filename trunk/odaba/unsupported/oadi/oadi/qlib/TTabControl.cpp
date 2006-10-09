/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TTabControl

\brief    


\date     $Date: 2006/07/18 18:14:30,85 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TTabControl"

#include  <poadi.h>
#include  <sODControl.hpp>
#include  <sODTabControl.hpp>
#include  <sOElementStyle.hpp>
#include  <sOField.hpp>
#include  <sOSTabControl.hpp>
#include  <sOTab.hpp>
#include  <sOWidget.hpp>
#include  <sTTabControl.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 



\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TTabControl :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"TTabControl")  ? this
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

int32 TTabControl :: CreateControl (TControl **tc_ptr )
{

  *tc_ptr = new TTabControl();
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

logical TTabControl :: DoCreate ( )
{
  OSTabControl           *ostyle = Style();
  logical                 dynamic;
  logical                 sta_upper;
  logical                 tb_normal;
  logical                 tb_upper;
  logical                 term = NO;
BEGINSEQ
  if ( TField::DoCreate() )                             ERROR

  tb_upper  = ostyle->get_position() == VPS_InnerBottom || 
              ostyle->get_position() == VPS_OuterBottom  ? NO : YES; 
  sta_upper = ostyle->get_fix_child() == VPS_InnerBottom || 
              ostyle->get_fix_child() == VPS_OuterBottom  ? NO : YES; 
  tb_normal = ostyle->get_shape();
  
  dynamic   = ((OFieldControl *)elementStyle)->get_dynamic();
  
  if ( !complexWidget )
    complexWidget = new ODTabControl(ComplexWidgetParent(),elementStyle->get_sys_ident());
  
  if ( complexWidget->CreateTabControl(elementStyle->GetControlName(),
                                       elementStyle->get_displayLevel(),
                                       tb_upper,tb_normal,sta_upper,dynamic) ) 
                                                     OADIGUICSERR(106)
  complexWidget->SetExtraData(this);

RECOVER
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

logical TTabControl :: DoCreated ( )
{
  logical   term = NO;
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
\brief  Style - 



\return cptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Style"

OSTabControl *TTabControl :: Style ( ) const
{

  return OI_CAST(OSTabControl,style);

}

/******************************************************************************/
/**
\brief  TTabControl - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TTabControl"

     TTabControl :: TTabControl ( )
                     : TField ()
{



}


