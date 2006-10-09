/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cTableEditor

\brief    


\date     $Date: 2006/03/12 19:37:26,31 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cTableEditor"

#include  <pdesign.h>
#include  <sNString.hpp>
#include  <scTableEditor.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return

\param  ctx_ctl_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cTableEditor :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cTableEditor();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoBeforeDrop

\return executed -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDrop"

int8 cTableEditor :: DoBeforeDrop ( )
{
  char                    executed      = NO;
  PropertyHandle        * attr_ph       = NULL;
  PropertyHandle        * field_ph      = NULL;
  PropertyHandle        * parent        = NULL;
  char                  * prop_path;
  NString                 field_opts    = "";
  char                  * field_name    = NULL;
  CTX_Control           * field_context = NULL;
BEGINSEQ
  PropertyHandle    *drop_ph    = GetDropPropertyHandle();
  char              *drop_txt   = GetDropText();
  DPoint             drop_pos   = GetDropPosition();
  int                drop_index = GetDropIndex();
  logical            is_local   = IsLocalDrop();

  if ( is_local )                                    ERROR
  
  field_opts += drop_txt;
  field_opts += ",";
  field_opts += drop_index;
  
  prop_path = GetPropertyHandle()->GetPropertyPath();
  parent    = GetPropertyHandle()->GetParentProperty();
  if ( !strcmp(prop_path,"ADK_StyleAction.columns") )
    parent->ExecuteInstanceAction("AddColumn", field_opts);
  else if ( !strcmp(prop_path,"ADK_StyleAction.regions") )
    parent->ExecuteInstanceAction("AddRegion", field_opts);
  executed = YES;

  ExecuteAction("Refresh", ACT_Function);
RECOVER
  return CTX_Control::DoBeforeDrop();
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cTableEditor


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cTableEditor"

                        cTableEditor :: cTableEditor ( )
                     : cSDBResource_Base ()
{



}

/******************************************************************************/
/**
\brief  ~cTableEditor - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cTableEditor"

                        cTableEditor :: ~cTableEditor ( )
{



}


