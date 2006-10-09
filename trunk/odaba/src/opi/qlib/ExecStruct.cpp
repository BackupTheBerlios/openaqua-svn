/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecStruct

\brief    


\date     $Date: 2006/03/12 19:10:29,20 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExecStruct"

#include  <pdefault.h>
#include  <sCTX_Structure.hpp>
#include  <sDBFieldDef.hpp>
#include  <sPropertyHandle.hpp>
#include  <sUCA_Action.hpp>
#include  <sExecStruct.hpp>


/******************************************************************************/
/**
\brief  CreateExpFilter - 


\return action - Simple Action

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExpFilter"

UCA_Action *ExecStruct :: CreateExpFilter ( )
{
  UCA_Action             *action = NULL;
BEGINSEQ
  if ( exp_filter.get_action_type() == ACT_undefined )
                                                     ERROR
  action = struct_context->CreateAction(&exp_filter);
RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  CreateHandler - 


\return action - Simple Action

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateHandler"

UCA_Action *ExecStruct :: CreateHandler ( )
{
  UCA_Action             *action = NULL;
BEGINSEQ
  if ( handler.get_action_type() == ACT_undefined )
                                                     ERROR
  action = struct_context->CreateAction(&handler);
RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  CreateImpFilter - 


\return action - Simple Action

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateImpFilter"

UCA_Action *ExecStruct :: CreateImpFilter ( )
{
  UCA_Action             *action = NULL;
BEGINSEQ
  if ( imp_filter.get_action_type() == ACT_undefined )
                                                     ERROR
  action = struct_context->CreateAction(&imp_filter);
RECOVER
  action = NULL;
ENDSEQ
  return(action);
}

/******************************************************************************/
/**
\brief  ExecStruct - 


-------------------------------------------------------------------------------
\brief i0


\param  struct_pi -
\param  prop_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecStruct"

                        ExecStruct :: ExecStruct (PropertyHandle *struct_pi, PropertyHandle *prop_ptr )
                     : field(prop_ptr),
  create(NO),
  recreate(NO),
  struct_context(NULL),
  exp_filter(),
  imp_filter(),
  handler()
{
  char           *key;
BEGINSEQ
  // das geht schief, wenn der Context auf dem Server läuft!
  struct_context = prop_ptr->GetInstanceContext();
  struct_pi->Get(0L);
  
  imp_filter = *(SimpleAction *)struct_pi->GetPropertyHandle("imp_condition")->GetArea();
  exp_filter = *(SimpleAction *)struct_pi->GetPropertyHandle("exp_condition")->GetArea();
  handler    = *(SimpleAction *)struct_pi->GetPropertyHandle("imp_handler")->GetArea();;
  create     = struct_pi->GetPropertyHandle("create")->IsTrue();
  recreate   = struct_pi->GetPropertyHandle("recreate")->IsTrue();
  
  if ( *(key = struct_pi->GetPropertyHandle("key")->GetArea()) > ' ' )
    if ( prop_ptr->SetOrder(key) )       
    {
      SDBEV1(key,ID_SIZE)
      SDBEV2(prop_ptr->GetDescription()->fmcbname,ID_SIZE)
      SDBERR(211)
    }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecStruct"

                        ExecStruct :: ExecStruct ( )
                     : field(NULL),
  create(NO),
  recreate(NO),
  struct_context(NULL),
  exp_filter(),
  imp_filter(),
  handler()
{



}

/******************************************************************************/
/**
\brief  ~ExecStruct - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExecStruct"

                        ExecStruct :: ~ExecStruct ( )
{



}


