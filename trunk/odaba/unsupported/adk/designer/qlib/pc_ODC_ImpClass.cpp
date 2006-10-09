/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ODC_ImpClass



\date     $Date: 2006/04/28 16:05:01,90 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_ImpClass"

#include  <pdesign.h>
#ifndef   GSRT_ODE_Project_HPP
#define   GSRT_ODE_Project_HPP
#include  <sODE_Project.hpp>
#include  <sGSRT.h>
#endif
#include  <sODE_Project.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_ClassFunctImpInputHelp.hpp>
#include  <spc_ClassInputHelp.hpp>
#include  <spc_ClassMemberInputHelp.hpp>
#include  <spc_ODC_PFunction.hpp>
#include  <spc_ODC_Project_.hpp>
#include  <spc_SDB_Resource.hpp>
#include  <spc_ODC_ImpClass.hpp>


/******************************************************************************/
/**
\brief  CheckContextClass

\return term - 

\param  base_context
\param  prjnames
\param  high_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckContextClass"

logical pc_ODC_ImpClass :: CheckContextClass (char *base_context, char *prjnames, CTX_Control *high_ctx )
{
  logical         term    = NO;
BEGINSEQ
  if ( pc_SDB_Structure_::CheckContextClass(base_context,prjnames,high_ctx) )
                                                     ERROR
  if ( ProvideProjectRef(prjnames,high_ctx) )        ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckReferencedClass

\return term - 

\param  typenames
\param  ref_projects
\param  high_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckReferencedClass"

logical pc_ODC_ImpClass :: CheckReferencedClass (char *typenames, GSRT(ODE_Project) *ref_projects, CTX_Control *high_ctx )
{
  PropertyHandle  idkey(typenames);
  PropertyHandle *mod_ref    = GPH("module");
  PropertyHandle *mod_ident  = mod_ref->GPH("sys_ident");
  ODE_Project    *odeprj     = NULL;
  int32           indx0      = 0;
  logical         term       = NO;
BEGINSEQ
  if ( !Get(idkey) )                                 ERROR
  if ( !high_ctx )                                   LEAVESEQ

  if ( !mod_ref->Get(FIRST_INSTANCE) )
    high_ctx->DisplayMessage(13);
  else if ( ref_projects )
    while ( odeprj = ref_projects->GetEntry(++indx0) )
      if ( *mod_ident == odeprj->get_project_name() )
                                                     LEAVESEQ
  high_ctx->DisplayMessage(14,mod_ident->GetString());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateReferencedClass

\return term - 

\param  new_ODE_TypeRef_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReferencedClass"

logical pc_ODC_ImpClass :: CreateReferencedClass (PropertyHandle *new_ODE_TypeRef_ph )
{
  PropertyHandle *type_name = new_ODE_TypeRef_ph->GPH("type_name");
  PropertyHandle *project   = new_ODE_TypeRef_ph->GPH("project");
  PropertyHandle *prg_lang  = new_ODE_TypeRef_ph->GPH("prg_lang");
  logical         term      = NO;
BEGINSEQ
  if ( !*type_name->GetString() )                    ERROR
    
  Add(*type_name);                                   P_SDBCERR

  if ( *project->GetString() > ' ' )
    GPH("module")->Add(*project);

  *GPH("opt_language") = *prg_lang;
  
  Save();                                            P_SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetImplemented

\return term - 

\param  type_key
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplemented"

logical pc_ODC_ImpClass :: GetImplemented (TypeKey &type_key )
{
  PropertyHandle *module     = NULL;
  PropertyHandle *module_ref = NULL;
  logical         cond       = YES;

BEGINSEQ
  if ( !Get(type_key.GetKey()) )                     ERROR
    
  module = GPH("module");
  while ( module->Get(0) )
    if ( !(module_ref = module->GPH("module_ref")) || !module_ref->Get(0) ) 
      module = module->GPH("module_parent");
    else
      break;

  if ( !module_ref || !module_ref->IsPositioned() || 
       !module_ref->IsA("ODC_Project")             ) ERROR

  pc_ODC_Project_  project(module_ref);
  if ( !project.IsImplemented(YES) )                 ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetMember

\return mem_ph
-------------------------------------------------------------------------------
\brief  i0


\param  memnames
\param  search_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *pc_ODC_ImpClass :: GetMember (char *memnames, char search_type )
{
  PropertyHandle         *prophdl = NULL;
  switch ( search_type )
  {
    case 'A' : prophdl = GetMember(GPH("smcepdde"),memnames);
               break;
    case 'B' : prophdl = GetMember(GPH("smcebase"),memnames);
               break;
    case 'R' : prophdl = GetMember(GPH("smcepref"),memnames);
               break;
    case 'P' : prophdl = GetMember(GPH("smcershp"),memnames);
               break;
    case 'F' : prophdl = GetMember(GPH("pfunctions"),memnames);
               break;
    case 'M' : if ( !(prophdl = GetMember(GPH("pfunctions"),memnames)) )
    case 'S' :    if ( !(prophdl = GetMember(GPH("smcepdde"),memnames)) )
                   if ( !(prophdl = GetMember(GPH("smcebase"),memnames)) )
                     if ( !(prophdl = GetMember(GPH("smcepref"),memnames)) )
                       prophdl = GetMember(GPH("smcershp"),memnames);
               break;
  }

  if ( !prophdl )
  {
    if ( search_type == 'M' )
      search_type = 'S';
    if ( !strncmp(memnames,"get_",4) )  // generated ODE function
      prophdl = GetMember(memnames+4,search_type);
  }

  return(prophdl);
}

/******************************************************************************/
/**
\brief  i01


\param  memb_ph
\param  memnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PropertyHandle *pc_ODC_ImpClass :: GetMember (PropertyHandle *memb_ph, char *memnames )
{
  PropertyHandle       idkey(memnames);


  return ( memb_ph->Get(idkey) ? memb_ph : NULL);


}

/******************************************************************************/
/**
\brief  InitContextClass

\return term - 

\param  base_context
\param  prjnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitContextClass"

logical pc_ODC_ImpClass :: InitContextClass (char *base_context, char *prjnames )
{
  pc_ODC_PFunction   pfunct_pc(GPH("pfunctions"));
  logical            term       = NO;
BEGINSEQ
  if ( pc_SDB_Structure_::InitContextClass(base_context) )
                                                     ERROR
  *GPH("opt_language") = "PL_CPP";
  
  if ( ProvideProjectRef(prjnames,NULL) )            ERROR
  if ( pfunct_pc.ProvideConstructor() )              ERROR
  if ( pfunct_pc.ProvideDestructor(YES) )            ERROR
  if ( InitCreate(base_context) )                    ERROR
  
  ExecuteInstanceAction("SetupReferences",NULL);
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitCreate

\return term - 

\param  base_context
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitCreate"

logical pc_ODC_ImpClass :: InitCreate (char *base_context )
{
  PropertyHandle    *sys_ident  = GPH("sys_ident");
  PropertyHandle    *pfunctions = GPH("pfunctions");
  PropertyHandle    *impls      = pfunctions->GPH("implementations");
  PropertyHandle    *code       = impls->GPH("code");
  PropertyHandle    *tpl_functs = NULL;
  PropertyHandle     ph_Create("Create");
  char               idkey[ID_SIZE];
  logical            term       = NO;
BEGINSEQ
  if ( !base_context || strncmp(base_context,"CTX_",4) )
                                                     ERROR
  PropertyHandle   tpl_classes(GetDBHandle(),"ODC_ImpClass",PI_Read);
                                                     P_SDBCERR
  tpl_functs     = tpl_classes.GPH("pfunctions");
  
  strcat(strcat(strcpy(idkey,"<"),base_context),">");
  PropertyHandle phidkey(idkey);
  if ( tpl_classes.Get(phidkey) &&
       tpl_functs->Get(ph_Create)    )
  {
    pfunctions->Copy(*tpl_functs);                   P_SDBCERR
    if ( !impls->Get(FIRST_INSTANCE) )               ERROR
    code->ReplaceText("%CTX_IMP_CLASS%",sys_ident->GetString());
    Save();
  }
  else if ( !pfunctions->Get(ph_Create) )
  {
    // standard-init
    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitExecuteFunction

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExecuteFunction"

logical pc_ODC_ImpClass :: InitExecuteFunction ( )
{
  PropertyHandle    *sys_ident  = GPH("sys_ident");
  PropertyHandle    *pfunctions = GPH("pfunctions");
  PropertyHandle    *base       = GPH("smcebase");
  PropertyHandle    *impls      = pfunctions->GPH("implementations");
  PropertyHandle    *code       = impls->GPH("code");
  PropertyHandle    *tpl_functs = NULL;
  PropertyHandle     ph_tplclass("<CTX_Base>");
  PropertyHandle     ph_ExecuteFunction("ExecuteFunction");
  std::string        code_string;
  std::string        repline;
  std::string        actline;
  std::string        actlines;
  int32              indx0      = 0;
  int32              start_pos  = 0;
  int32              end_pos    = 0;
  int32              parm_pos   = 0;
  logical            started    = NO;
  logical            term       = NO;
BEGINSEQ
  started = StartRTA() ? YES : NO;
  base->Get(FIRST_INSTANCE);
  
  PropertyHandle   tpl_classes(GetDBHandle(),"ODC_ImpClass",PI_Read);
                                                     P_SDBCERR
  tpl_functs     = tpl_classes.GPH("pfunctions");
  PropertyHandle phph_tplclass(ph_tplclass);
  if ( tpl_classes.Get(phph_tplclass) &&
       tpl_functs->Get(ph_ExecuteFunction)    )
  {
    pfunctions->Copy(*tpl_functs);                   P_SDBCERR
    if ( !impls->Get(FIRST_INSTANCE) )               ERROR
    code->ReplaceText("%CTX_CLASS_NAME%",sys_ident->GetString());
    code->ReplaceText("%CTX_CLASS_BASE%",base->GPH("sys_ident")->GetString());
    
    code_string = code->GetString();
    if ( (start_pos = code_string.find("%r%")) >= 0 &&
         (end_pos   = code_string.find("\n",start_pos+3)) >= 0 )
    {
      repline = code_string.substr(start_pos+3,end_pos-start_pos-2);

      PropertyHandle   pfunct_copy(*pfunctions);
      PropertyHandle  *funct_ident = pfunct_copy.GPH("sys_ident");
      PropertyHandle  *action      = pfunct_copy.GPH("action");
      
      while ( pfunct_copy.Get(indx0++) )
        if ( action->IsTrue() )
        {
          actline = repline;
          while ( (parm_pos = actline.find("%CTX_FUNCTION_NAME%")) >= 0 )
            actline.replace(parm_pos,19,funct_ident->GetString());
          actlines += actline;
        }
      
      code_string.replace(start_pos,end_pos - start_pos +1,actlines);
      *code = (char *)code_string.c_str();
    }
    Save();
  }
  else if ( !pfunctions->Get(ph_ExecuteFunction) )
  {
    // standard-init
    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  StopRTA(started);
  return(term);
}

/******************************************************************************/
/**
\brief  InitFunction

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitFunction"

logical pc_ODC_ImpClass :: InitFunction ( )
{
  PropertyHandle    *pfunctions = GPH("pfunctions");
  PropertyHandle     template_ident("<Function>");
  Key                save_key;
  char               keyarea[MAX_KEYLEN];
  logical            term       = NO;
BEGINSEQ
  PropertyHandle   tpl_fct(GetDBHandle(),"ODC_PFunction",PI_Read);
                                                     P_SDBCERR
  if ( pfunctions->IsPositioned() )
    save_key = pfunctions->ExtractSortKey(Key(keyarea));

  if ( tpl_fct.Get(save_key) || tpl_fct.Get(template_ident) )
  {
    pfunctions->Copy(tpl_fct,save_key,REPL_local);   P_SDBCERR
  }
  else 
  {
    // standard-init
    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateSource

\return source_part_name

\param  line_ref
\param  findx0_ref
\param  iindx0_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateSource"

char *pc_ODC_ImpClass :: LocateSource (int32 &line_ref, int32 &findx0_ref, int32 &iindx0_ref )
{
  PropertyHandle     functions(*this,"pfunctions");
  PropertyHandle    *impls      = functions.GPH("implementations");
  PropertyHandle    *linecount  = impls->GPH("linecount");
  PropertyHandle    *init_c_ph  = impls->GPH("init_count");
  PropertyHandle    *start_c_ph = impls->GPH("start_count");
  PropertyHandle    *code_c_ph  = impls->GPH("code_count");
  PropertyHandle    *error_c_ph = impls->GPH("error_count");
  PropertyHandle    *term_c_ph  = impls->GPH("term_count");
  int32              line       = line_ref;
  int32              init_      = 0;
  int32              start_     = 0;
  int32              code_      = 0;
  int32              error_     = 0;
  int32              term_      = 0;
  int32              findx0     = 0;
  int32              iindx0     = 0;
  char              *area       = NULL;

BEGINSEQ
  while ( functions.Get(findx0++) )
  {
    iindx0 = 0;
    while ( impls->Get(iindx0++) )
    {
      if ( line < linecount->GetInt() )
        LEAVESEQ

      findx0_ref = findx0-1;
      iindx0_ref = iindx0-1;
      init_      = init_c_ph->GetInt();
      
      if ( line < (start_ = start_c_ph->GetInt()) )
      {
        area     = "init";
        line_ref = line - init_ +1;
        LEAVESEQ
      }
      else if ( line < (code_ = code_c_ph->GetInt()) )
      {
        area     = "start";
        line_ref = line - start_ +1;
        LEAVESEQ
      }
      else if ( line < (error_ = error_c_ph->GetInt()) )
      {
        area     = "code";
        line_ref = line - code_ +1;
        LEAVESEQ
      }
      else if ( line < (term_ = term_c_ph->GetInt()) )
      {
        area     = "error";
        line_ref = line - error_ +1;
        LEAVESEQ
      }
      else
      {
        area     = "term";
        line_ref = line - term_ +1;
      }
    }
  }

  findx0_ref = 0;
  iindx0_ref = 0;
  line_ref   = 0;
  area       = NULL;

ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  ProvideContextClass

\return term - 

\param  res_ph
\param  high_ctx
\param  ret_edit
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideContextClass"

logical pc_ODC_ImpClass :: ProvideContextClass (PropertyHandle *res_ph, CTX_Control *high_ctx, logical *ret_edit )
{
  DictionaryHandle   dictionary   = high_ctx ? high_ctx->ReserveResourceDictionary() : (DictionaryHandle)NULL;
  CTX_Project       *proj_ctx     = high_ctx->GetProjectContext();
  PropertyHandle    *impl_class   = NULL;
  PropertyHandle    *project      = NULL;
  PropertyHandle    *edit         = NULL;
  char              *base_context = NULL;
  char              *prjnames     = NULL;
  logical            term         = NO;
BEGINSEQ
  if ( !high_ctx || !res_ph->Exist() || !proj_ctx )  P_ERR(99)
  
  if ( !proj_ctx->ExecuteFunction("GetProjectName") )
    prjnames = proj_ctx->GetResult();
  
  PropertyHandle  def_prophdl(dictionary,"DefineContext");
                                                     P_SDBCERR
  impl_class   = def_prophdl.GPH("impl_class");
  project      = def_prophdl.GPH("project");
  edit         = def_prophdl.GPH("edit");
  base_context = pc_SDB_Resource(res_ph).GetContextType();
  
  *def_prophdl.GPH("resource_type") = (char*)(base_context ?(char*) base_context : "");
  *def_prophdl.GPH("resource_name") = *res_ph->GPH("sys_ident");
  *impl_class                       = "";
  *project                          = (char*)(prjnames ? prjnames : "");
  *edit                             = YES;

  while ( impl_class->IsEmpty() || project->IsEmpty() )
    if ( high_ctx->ExecuteWindow(&def_prophdl,"DefineContext","Edit",NO) )
                                                     ERROR
  
  if ( !Get(*impl_class) )
  {
    Add(*impl_class);                                P_SDBCERR
    InitContextClass(base_context,project->GetString());
  }
  else
    CheckContextClass(base_context,project->GetString(),high_ctx);
      
  if ( P_ERROR )
    high_ctx->DisplayMessage();

  if ( edit->IsTrue() && IsPositioned() )
    *ret_edit = YES;
RECOVER
  term = YES;
ENDSEQ
  if ( high_ctx )
    high_ctx->ReleaseResourceDictionary();
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideProjectRef

\return term - 

\param  modnames
\param  high_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideProjectRef"

logical pc_ODC_ImpClass :: ProvideProjectRef (char *modnames, CTX_Control *high_ctx )
{
  PropertyHandle *module  = GPH("module");
  logical         term    = NO;
BEGINSEQ
  if ( !modnames || !*modnames )                     LEAVESEQ
    
  if ( module->Get(FIRST_INSTANCE) )
  {
    if ( !strcmp(module->GPH("sys_ident")->GetString(),modnames) )
                                                     LEAVESEQ
    if ( !high_ctx->GetDecision(5,module->GPH("sys_ident")->GetString(),modnames) )
                                                     LEAVESEQ
    module->Delete();
  }
  PropertyHandle phmodnames(modnames);
  module->Add(phmodnames);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideReferencedClass

\return term - 

\param  source_ph
\param  modnames
\param  high_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideReferencedClass"

logical pc_ODC_ImpClass :: ProvideReferencedClass (PropertyHandle *source_ph, char *modnames, CTX_Control *high_ctx )
{
  PropertyHandle *source_ident = source_ph->GPH("sys_ident");
  PropertyHandle *module       = GPH("module");
  logical         term         = NO;
BEGINSEQ
  if ( !source_ph->IsPositioned() )                  ERROR
    
  if ( !Get(*source_ident) )
  {
    Add(*source_ident);                              P_SDBCERR
    *GPH("opt_language") = *source_ph->GPH("opt_language");
  }
  
  if ( !module->Get(FIRST_INSTANCE) )
  {
    module->Add(module->StringToKey(modnames));  P_SDBCERR
  }
  else
    if ( high_ctx )
      if ( *module->GPH("sys_ident") != modnames )
        high_ctx->DisplayMessage(12,module->GPH("sys_ident")->GetString(),modnames);
  
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupClassList

\return term - 

\param  class_input_pc
\param  ref_projects
\param  base_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupClassList"

logical pc_ODC_ImpClass :: SetupClassList (pc_ClassInputHelp *class_input_pc, GSRT(ODE_Project) *ref_projects, logical base_opt )
{
  ODE_Project  *odeprj = NULL;
  int32         indx0  = 0;
  logical       term   = NO;
BEGINSEQ
  if ( class_input_pc->SetupList(this,base_opt) )
    term = YES;
  
  if ( !ref_projects )                               LEAVESEQ
    
  while ( odeprj = ref_projects->GetEntry(++indx0) )
    if ( odeprj->get_project_classes().SetupClassList(class_input_pc,NULL,YES) )
      term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupExecuteFunction

\return term - 

\param  high_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupExecuteFunction"

logical pc_ODC_ImpClass :: SetupExecuteFunction (CTX_Control *high_ctx )
{
  PropertyHandle    *pfunctions = GPH("pfunctions");
  PropertyHandle     exec_fname("ExecuteFunction");
  char              *result     = NULL;
  logical            has_action = UNDEF;
  logical            term       = NO;
BEGINSEQ
  if ( ExecuteInstanceAction("HasActions",NULL) )    ERROR
  if ( !(result = GetActionResult()) )               ERROR
  has_action = *result == 'Y' ? YES : NO;
  
  if ( pfunctions->Get(exec_fname) )
  {
    if ( !high_ctx->GetDecision(has_action ? 11: 10) )
                                                     LEAVESEQ
    pfunctions->Delete(AUTO,YES,YES);
  }
  
  if ( has_action )
    if ( InitExecuteFunction() )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupFunctImpList

\return term - 

\param  fctname
\param  functimp_input_pc
\param  ode_project
\param  base_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupFunctImpList"

logical pc_ODC_ImpClass :: SetupFunctImpList (char *fctname, pc_ClassFunctImpInputHelp *functimp_input_pc, ODE_Project *ode_project, logical base_opt )
{
  PropertyHandle   funct_key(fctname);
  PropertyHandle  *funct_ph = GPH("pfunctions");
  PropertyHandle  *base_ph  = GPH("smcebase");
  pc_ODC_ImpClass *class_pc = NULL;
  int32            indx0    = 0;
  logical          term     = NO;
BEGINSEQ
  if ( !funct_ph->Get(funct_key) )                   LEAVESEQ
    
  if ( functimp_input_pc->SetupList(funct_ph->GPH("implementations"),base_opt) )
    term = YES;
    
  if ( base_ph->GetCount() <= 0 )                    LEAVESEQ
    
  pc_ODC_ImpClass copy_pc(*this);
  base_ph = copy_pc.GPH("smcebase");  
  while ( base_ph->Get(indx0++) )
  {
    TypeKey     type_key(base_ph->GetString("sys_ident"),base_ph->GetInt("namespace_id"));
    if ( class_pc = ode_project->GetImplementedClass(type_key) )
      if ( class_pc->SetupFunctImpList(fctname,functimp_input_pc,ode_project,YES) )
        term = YES;
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupMemberList

\return term - 

\param  member_input_pc
\param  ode_project
\param  base_opt
\param  direct_access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupMemberList"

logical pc_ODC_ImpClass :: SetupMemberList (pc_ClassMemberInputHelp *member_input_pc, ODE_Project *ode_project, logical base_opt, logical direct_access )
{
  PropertyHandle  *base_ph  = GPH("smcebase");
  pc_ODC_ImpClass *class_pc = NULL;
  int32            indx0    = 0;
  logical          term     = NO;
BEGINSEQ
  if ( member_input_pc->SetupList(GPH("smcepdde"),OT_Attribute,base_opt,direct_access) )
    term = YES;
  if ( member_input_pc->SetupList(GPH("smcepref"),OT_Reference,base_opt,direct_access) )
    term = YES;
  if ( member_input_pc->SetupList(GPH("smcershp"),OT_Relationship,base_opt,direct_access) )
    term = YES;
  if ( member_input_pc->SetupList(GPH("pfunctions"),OT_Function,base_opt,direct_access) )
    term = YES;
  
  if ( base_ph->GetCount() <= 0 )                    LEAVESEQ
    
  pc_ODC_ImpClass copy_pc(*this);
  base_ph = copy_pc.GPH("smcebase");  
  while ( base_ph->Get(indx0++) )
  {
    TypeKey     type_key(base_ph->GetString("sys_ident"),base_ph->GetInt("namespace_id"));
    if ( class_pc = ode_project->GetImplementedClass(type_key) )
      if ( class_pc->SetupMemberList(member_input_pc,ode_project,YES,direct_access) )
        term = YES;
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_ImpClass - Konstruktor


-------------------------------------------------------------------------------
\brief  i0


\param  obhandle
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_ImpClass"

     pc_ODC_ImpClass :: pc_ODC_ImpClass (DBObjectHandle &obhandle, PIACC accopt )
                     : pc_SDB_Structure_ (obhandle,"ODC_ImpClass",accopt)
{
}

/******************************************************************************/
/**
\brief  i01


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_ImpClass"

     pc_ODC_ImpClass :: pc_ODC_ImpClass (PropertyHandle *prophdl )
                     : pc_SDB_Structure_ (prophdl)
{
}


