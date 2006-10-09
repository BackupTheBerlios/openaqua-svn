/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassEDTree



\date     $Date: 2006/06/01 16:49:31,81 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassEDTree"

#include  <pdesign.h>
#include  <spODE.hpp>
#include  <spc1_ODC_PFunction.hpp>
#include  <scClassEDTree.hpp>


/******************************************************************************/
/**
\brief  AfterInsertImpClass

\return term - 

\param  class_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AfterInsertImpClass"

logical cClassEDTree :: AfterInsertImpClass (PropertyHandle *class_ph )
{
  pODE    *ode_ctx  = ODEContext(this);
  logical  started  = NO;
  logical  term     = NO;
BEGINSEQ
  if ( !ode_ctx )                                    LEAVESEQ
    
  pc1_ODC_ImpClass   class_pc(class_ph);
  if ( class_pc.IsNewInstance() )
  {
    started = class_pc.StartRTA() ? YES : NO;
    term    = class_pc.InitClass(ODEOptionIsOn(this,"AutoInitialize"));
    class_pc.StopRTA(started);
    
    DoAfterSelect();
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AfterInsertPFunction

\return term - 

\param  funct_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AfterInsertPFunction"

logical cClassEDTree :: AfterInsertPFunction (PropertyHandle *funct_ph )
{
  pODE    *ode_ctx  = ODEContext(this);
  logical  started  = NO;
  logical  term     = NO;
BEGINSEQ
  if ( !ode_ctx )                                    LEAVESEQ
    
  pc1_ODC_PFunction   pfunc_pc(funct_ph);
  if ( pfunc_pc.IsNewInstance() )
  {
    started = pfunc_pc.StartRTA() ? YES : NO;
    term    = pfunc_pc.InitializePFunction(NULL,ode_ctx);
    pfunc_pc.StopRTA(started);
    
    DoAfterSelect();
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassEDTree :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassEDTree();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterDeleteData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterDeleteData"

int8 cClassEDTree :: DoAfterDeleteData ( )
{
  int16            state = UserState1();
  PropertyHandle   type_ph;
BEGINSEQ
  if ( !state )                                       LEAVESEQ
  SetUserState1(NO);

  switch ( state )
  {
    case 1 : // ODC_PFunction
       if ( !dependend_object.NoWrite() )
         dependend_object.Delete();
       break;
       
    case 2 : // ODC_ImpClass
       dependend_object.ExecuteInstanceAction("DeleteExternalResources",NULL);
       if ( !dependend_object.NoWrite() )
       {
         if ( GetDecisionYes(18,dependend_object.GPH("sys_ident")->GetString()) )
         {
           type_ph.Open(dependend_object.GetDBHandle(),"SDB_Type",PI_Update);
           type_ph.Get(dependend_object.ExtractKey());
         }
         dependend_object.Delete();
         type_ph.Delete();
       }
       break;
  }

  dependend_object.Close();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterInsertData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInsertData"

int8 cClassEDTree :: DoAfterInsertData ( )
{
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
  char             executed = NO;
  if ( prophdl->IsA("ODC_PFunction") )
    AfterInsertPFunction(prophdl);
  else if ( prophdl->IsA("ODC_ImpClass") )
    AfterInsertImpClass(prophdl);

  return(executed);
}

/******************************************************************************/
/**
\brief  DoAfterSelect

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cClassEDTree :: DoAfterSelect ( )
{
  pODE            *ode_ctx       = ODEContext(this);
  PropertyHandle  *prophdl       = GetCurrentPropertyHandle();
  PropertyHandle  *tab_ph        = prophdl;
  CTX_Control     *ced_ctx       = NULL;
  CTX_Control     *ws_tab_ctx    = NULL;
  smcb            *keysmcb       = NULL;
  char            *tab_keystring = NULL;
  char             keyarea[512];
  char             executed      = NO;
BEGINSEQ
  if ( !ode_ctx )                                    ERROR
  if ( !(ced_ctx = (CTX_Control *)GetHighContext("klasseditor")) ) 
                                                     ERROR
  if ( !(ws_tab_ctx = ced_ctx->GetControlContext("class_ws.class_stack")) )
                                                     ERROR

  if ( prophdl->IsA("ODC_ImpClass") && *last_function > ' ' )
  {
    prophdl = prophdl->GPH("pfunctions");
    if ( !(prophdl->Get(last_function)) )
      prophdl = tab_ph;
  }
  
  if ( prophdl->IsA("ODC_PFunction") )
    if ( !(tab_ph = prophdl->GetParentProperty()) )
      tab_ph = prophdl;
    else
      if ( prophdl->Exist() )
        prophdl->ExtractSortKey(last_function);

  if ( keysmcb = tab_ph->GetKeySMCB() )
    tab_keystring = tab_ph->KeyToString(keyarea,tab_ph->ExtractKey(),keysmcb->smcbname);
          
  ws_tab_ctx->SetParm(tab_ph->GetCurrentType(),
                      tab_keystring,
                      tab_ph != prophdl ? prophdl->GPH("sys_ident")->GetString() : NULL);
  ws_tab_ctx->ExecuteFunction("Synchronize");

  cSDBResource_Base::DoAfterSelect();

  if ( prophdl )
    ode_ctx->SetDocumentPH(prophdl);

  SetApplicationTitle();

RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  DoBeforeClose

\return excuted

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

int8 cClassEDTree :: DoBeforeClose ( )
{

  dependend_object.Close();
  return(NO);
}

/******************************************************************************/
/**
\brief  DoBeforeDataSet

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDataSet"

int8 cClassEDTree :: DoBeforeDataSet ( )
{
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
  int8             executed = NO;
  if ( prophdl->IsA("ODC_Project") )
    SetLineFont("bold_violette",0);
  return(executed);
}

/******************************************************************************/
/**
\brief  DoBeforeDeleteData

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDeleteData"

int8 cClassEDTree :: DoBeforeDeleteData ( )
{
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
  PropertyHandle  *parent   = NULL;
  char             executed = NO;
  SetUserState1(NO);

  parent = prophdl->GetParentProperty();
  
  if ( prophdl->IsA("ODC_PFunction") )
  {
    SetPFunctionNotInit();              // das kann alles weg, wenn CE_Delete Event erst beim Beender der Read-TA gefeuert wird

    if ( parent->IsA("ODC_ImpClass") )
      switch ( *ODEOption(this,"DeleteDescriptionWithImplementation") )
      {
        case 'Y' : SetUserState1(1);               break;
        case 'N' : SetUserState1(NO);              break; 
        case 'A' :
        default  : if ( GetDecisionYes(12,prophdl->GPH("sys_ident")->GetString()) )
                   {
                     dependend_object.Open(*parent->GPH("function_descr"));
                     if ( dependend_object.Get(prophdl->ExtractKey()) )   
                       SetUserState1(1);
                   }
      }
  }    
  else if ( prophdl->IsA("ODC_ImpClass") )
  {
    if ( parent->IsA("ODC_Module") )
    {
      dependend_object.Open(prophdl->GetDBHandle(),"ODC_ImpClass",PI_Update);
      if ( dependend_object.Get(prophdl->ExtractKey()) )   
        SetUserState1(2);
{
PropertyHandle *ph = dependend_object.GPH("module");
if ( !ph->Get(FIRST_INSTANCE) )
dependend_object.ToTop();
if ( dependend_object.Get(prophdl->ExtractKey()) )   
ph->Get(FIRST_INSTANCE);
}
    }    
  }
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return 

\param  fname
\param  chk_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cClassEDTree :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetClassName",ALINK(this,cClassEDTree,GetClassName)),
                           cfte("InsertOverloadFunction",ALINK(this,cClassEDTree,InsertOverloadFunction)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = cSDBResource_Base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClassName

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClassName"

logical cClassEDTree :: GetClassName ( )
{
  PropertyHandle  *prophdl  = GetClassPH();
  SetResult(prophdl->GPH("sys_ident")->GetString());
  return(prophdl ? NO : YES);
}

/******************************************************************************/
/**
\brief  GetClassPH

\return prophdl - Property handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClassPH"

PropertyHandle *cClassEDTree :: GetClassPH ( )
{
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
BEGINSEQ
  if ( prophdl->IsA("ODC_PFunction") )
    prophdl = prophdl->GetParentProperty();

  if ( prophdl->IsA("ODC_ImpClass") )                LEAVESEQ

  ERROR
RECOVER

ENDSEQ
  return(prophdl);
}

/******************************************************************************/
/**
\brief  InsertOverloadFunction

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertOverloadFunction"

logical cClassEDTree :: InsertOverloadFunction ( )
{
  pODE            *ode_ctx  = ODEContext(this);
  PropertyHandle  *prophdl  = GetClassPH();
  PropertyHandle  *func_ph  = prophdl->GPH("pfunctions");
  PropertyHandle  *sel_ph   = GetClassPH();
  logical          term     = NO;
BEGINSEQ
  if ( !ode_ctx )                                    ERROR
  if ( prophdl->NoWrite() )                          ERROR

  TypeKey  type_key(prophdl->GetString("sys_ident"),prophdl->GetInt("namespace_id"));
  
  if ( !(sel_ph = ode_ctx->GetMemberInputHelpPH(type_key,NULL,UNDEF,NO)) )
                                                     ERROR
  if ( ExecuteWindow(sel_ph,"ClassMemberInputHelp","Edit",NO) )
                                                     ERROR
  if ( !sel_ph->Exist() )                            ERROR
    
  if ( func_ph->Get(sel_ph->ExtractKey()) )
    DisplayMessage(16,sel_ph->ExtractKey(),type_key.Name());
  else
  {
    SetPFunctionNotInit();
    func_ph->Add(sel_ph->ExtractKey());              P_SDBCERR
    AfterInsertPFunction(func_ph);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetApplicationTitle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetApplicationTitle"

void cClassEDTree :: SetApplicationTitle ( )
{
  pODE            *ode_ctx  = ODEContext(this);
  PropertyHandle  *prophdl  = GetCurrentPropertyHandle();
  NString          ntitle;
  logical          first = YES;

  while ( prophdl && !prophdl->IsA("ODC_Project") )
  {
    if ( !first )
      ntitle.Insert(0,".");
    first = NO;
    ntitle.Insert(0,prophdl->GetString("sys_ident"));
    prophdl = prophdl->GetCollectionProperty();
  }
  
  ode_ctx->SetApplicationTitle(NULL,NULL,ntitle);
}

/******************************************************************************/
/**
\brief  SetPFunctionNotInit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPFunctionNotInit"

void cClassEDTree :: SetPFunctionNotInit ( )
{
  pODE            *ode_ctx  = ODEContext(this);
  CTX_Control     *edit_ctx = ode_ctx ? ode_ctx->GetImpClassContext() : NULL;
  if ( edit_ctx )
    edit_ctx->ExecuteFunction("SetPFunctionNotInit");

}

/******************************************************************************/
/**
\brief  cClassEDTree


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassEDTree"

     cClassEDTree :: cClassEDTree ( )
                     : cSDBResource_Base (),
  dependend_object()
{
  memset(last_function,' ',sizeof(last_function));
}

/******************************************************************************/
/**
\brief  ~cClassEDTree


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassEDTree"

     cClassEDTree :: ~cClassEDTree ( )
{

}


