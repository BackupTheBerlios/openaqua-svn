/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cPropertyTable

\brief    


\date     $Date: 2006/03/12 19:37:21,45 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cPropertyTable"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <scPropertyTable.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc -

\param  ctx_ctl_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cPropertyTable :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cPropertyTable();
  return(NO);

}

/******************************************************************************/
/**
\brief  Update

\return term -

\param  ph_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical cPropertyTable :: Update (PropertyHandle *ph_ptr )
{
  logical                 term        = NO;
  CTX_Control           * tab_context = NULL;
BEGINSEQ
  if ( ph_ptr->Inherits("ADK_FieldControl") )
  {
    SetDisplayLevel(PTM_Control);
    tab_context = GetFieldContext("control");
  }
  else if ( ph_ptr->Inherits("ADK_Field") )
  {
    SetDisplayLevel(PTM_Field);
    tab_context = GetFieldContext("field");
  }
  else if ( ph_ptr->Inherits("ADK_Button") )
  {
    SetDisplayLevel(PTM_Button);
    tab_context = GetFieldContext("button");
  }
  else if ( ph_ptr->Inherits("ADK_Constant") )
  {
    SetDisplayLevel(PTM_Constant);
    tab_context = GetFieldContext("constant");
  }
  else if ( ph_ptr->Inherits("ADK_Menu") )
  {
    SetDisplayLevel(PTM_Menu);
    tab_context = GetFieldContext("menu");
  }
  else                                           OADIERR(98)

  if ( ! tab_context )                               OADIERR(99)
  tab_context->SetPropertyHandle(ph_ptr, YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cPropertyTable


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cPropertyTable"

                        cPropertyTable :: cPropertyTable ( )
{



}

/******************************************************************************/
/**
\brief  ~cPropertyTable


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cPropertyTable"

                        cPropertyTable :: ~cPropertyTable ( )
{



}


