/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBReaction

\brief    


\date     $Date: 2006/03/12 19:17:08,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBReaction"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sCAU_Action.hpp>
#include  <sCAU_Reaction.hpp>
#include  <sCTX_DBBase.hpp>
#include  <sCTX_Property.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sUCA_CAction.hpp>
#include  <sUCA_CActionList.hpp>
#include  <ssrt.hpp>
#include  <sDBReaction.hpp>


/******************************************************************************/
/**
\brief  Connect - 


\return term - Termination code

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical DBReaction :: Connect (Dictionary *dictptr )
{
  CAU_Action             *caction;
  DBResource             *resource;
  DBStructDef            *strdef;
  DBFieldDef             *flddef;
  PI(CAU_RCT_PathComp)   *path_pi;
  int32                    count;
  int32                    indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  if ( react_id == AUTO )                            LEAVESEQ

  DBObjectHandle   temp_object(dictptr);
  PI(CAU_Reaction)     react_pi(temp_object,"CAU_Reaction",PI_Read);
                                                     SDBCERR
  if ( !react_pi((char *)&react_id) || 
       !(caction = react_pi->get_db_action()(0L)) )  ERROR
       
  type   = react_pi->get_rct_type();
  delay  = react_pi->get_delay();
  active = react_pi->get_rct_path().get_active() ? AUTO : 0;

  if ( !(strdef = (DBStructDef *)dictptr->ProvideStructDef(caction->get_structure())) )
                                                     SDBERR(99)
  if ( *caction->get_property() > ' ' )
  {
    if ( !(flddef = strdef->GetEntry(caction->get_property())) )
                                                     SDBERR(99)
    if ( !(strdef = flddef->GetDBStruct(dictptr)) )  SDBERR(99)
    prop_action = YES;
    resource = flddef->get_resource();
  }
  else
    resource = strdef->get_resource();
  if ( !resource || !(action = resource->get_action_list()->Search(caction->get_sys_ident())) )
                                                     SDBERR(99)

  if ( type == RCT_Path )
  {
    path_pi = &react_pi->get_rct_path().get_property_path();
    count = path_pi->GetCount();
    prop_path.SetAtGrow((int16)count,NULL);
    
    for ( indx0 = 0; indx0 < count; indx0++ )
    {
      path_pi->Get(indx0);
      if ( !(flddef = strdef->GetEntry(path_pi->ExtractKey())) )
                                                     SDBERR(99)
      prop_path[(int16)indx0] = flddef;
      if ( active == AUTO && !flddef->get_inverse() )
        active = (int16)indx0;
    }
    struct_event = react_pi->get_rct_path().get_struct_event();
    if ( active == AUTO )
      active = (int16)count;
  }
RECOVER
  term = YES;
ENDSEQ
  react_id = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  DBReaction - 



\param  rident -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBReaction"

                        DBReaction :: DBReaction (int32 rident )
                     : react_id(UNDEF),
  type(RCT_Self),
  prop_path(int(NULL)),
  delay(RDT_immediately),
  action(NULL),
  active(AUTO),
  struct_event(NO),
  prop_action(NO)
{



}

/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical DBReaction :: Execute (CTX_DBBase *ctxptr )
{
  UCA_CAction            *caction = NULL;
  PropertyHandle                *inst_pi;
  CTX_DBBase             *actctx;
  int32                    indx0 = active-1;
  logical                 term = NO;
BEGINSEQ
  if ( !action || !(actctx = GetActionContext(ctxptr)) )
                                                     LEAVESEQ
  if ( type != RCT_Path || active == 0)
    term = action->Execute(actctx);
  else
  {
    actctx  = GetActiveContext();
    inst_pi = actctx->GetPropertyHandle();
    inst_pi->ToTop();
    
    while ( inst_pi->Get(indx0++) )
      if ( ExecuteInstAct(inst_pi,active-1) )
        term = YES;
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteInstAct - 


\return term - Termination code

\param  inst_pi -
\param  level -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteInstAct"

logical DBReaction :: ExecuteInstAct (PropertyHandle *inst_pi, int16 level )
{
  int32                    indx0 = 0;
  CTX_DBBase             *actctx;
  logical                 term = NO;
  if ( level-- )
  {
    inst_pi = (PropertyHandle *)(((char *)inst_pi->Get().GetData())+prop_path[level]->get_inverse()->fmcbposn);
    while ( inst_pi->Get(indx0++) )
      if ( ExecuteInstAct(inst_pi,level) )
        term = YES;
  }
  else
  {
    actctx = (CTX_DBBase *)inst_pi->GetPropertyContext()->GetStructContext();
    term = action->Execute(actctx);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  GetActionContext - 


\return ctxptr -

\param  ctxptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActionContext"

CTX_DBBase *DBReaction :: GetActionContext (CTX_DBBase *ctxptr )
{
  CTX_DBBase            *actctx;
  PropertyHandle               *inst_pi;
  int32                   indx0;
BEGINSEQ
  switch ( type )
  {
    case RCT_Self : actctx = ctxptr;
                    break;
    case RCT_Up   : actctx = ctxptr->HighDBContext();
                    break;
    case RCT_Path : actctx = ctxptr;
                    if ( struct_event )
                      if ( !(actctx = actctx->HighDBContext()) )
                                                     SDBERR(99)
                    if ( !(actctx = GetActiveContext()) )
                                                     ERROR
                    if ( active == 0 )
                      actctx = (CTX_DBBase *)actctx->GetStructContext();
                    else
                    {
                      if ( !(inst_pi = ((CTX_Property *)actctx)->GetPropertyHandle()) )
                                                     ERROR
                      while ( indx0 >= 0 )
                      {
                        if ( !(inst_pi = inst_pi->GetPropertyHandle(prop_path[indx0--]->get_inverse()->fmcbname)) )
                                                     ERROR
                      }
                    }
                    actctx = (CTX_DBBase *)inst_pi->GetPropertyContext()->GetStructContext();
                    if ( prop_action )  // vorerst nicht erlaubt
                                                     ERROR
                    break;
    default       : actctx = NULL;
  }
    
  if ( !actctx )                                     ERROR
  actctx->set_evt_context(ctxptr);
RECOVER
  actctx = NULL;
ENDSEQ
  return(actctx);
}

/******************************************************************************/
/**
\brief  GetActiveContext - 


\return ctxptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveContext"

CTX_DBBase *DBReaction :: GetActiveContext ( )
{
  CTX_DBBase            *actctx = NULL;
  int32                   indx0;
BEGINSEQ
  if ( struct_event )
    if ( !(actctx = actctx->HighDBContext()) )       SDBERR(99)
  for (indx0 = prop_path.GetSize()-1; indx0 >= active; indx0--)
  {
    if ( memcmp(actctx->GetResourceName(),prop_path[(int16)indx0]->fmcbname,ID_SIZE) )
                                                     ERROR
    if ( !(actctx = actctx->HighDBContext()->HighDBContext()) )
                                                     ERROR
  }
RECOVER
  actctx = NULL;
ENDSEQ
  return(actctx);
}

/******************************************************************************/
/**
\brief  ~DBReaction - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DBReaction"

                        DBReaction :: ~DBReaction ( )
{



}


