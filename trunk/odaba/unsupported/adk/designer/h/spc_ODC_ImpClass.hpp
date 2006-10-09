/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF)
\class    pc_ODC_ImpClass

\brief    


\date     $Date: 2006/03/16 15:18:02,50 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_ImpClass_HPP
#define   pc_ODC_ImpClass_HPP

class     pc_ODC_ImpClass;

#include  <sGSRT.h>
class     ODE_Project;
class     ODE_Project;
class     pc_ClassFunctImpInputHelp;
class     pc_ClassInputHelp;
class     pc_ClassMemberInputHelp;
#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_SDB_Structure_.hpp>
class  pc_ODC_ImpClass :public pc_SDB_Structure_
{

public     :
public     :                                     logical CheckContextClass (char *base_context, char *prjnames, CTX_Control *high_ctx );
public     :                                     logical CheckReferencedClass (char *typenames, GSRT(ODE_Project) *ref_projects, CTX_Control *high_ctx );
public     :                                     logical CreateReferencedClass (PropertyHandle *new_ODE_TypeRef_ph );
public     :                                     logical GetImplemented (TypeKey &type_key );
public     :                                     PropertyHandle *GetMember (char *memnames, char search_type );
public     :                                     PropertyHandle *GetMember (PropertyHandle *memb_ph, char *memnames );
public     :                                     logical InitContextClass (char *base_context, char *prjnames );
public     :                                     logical InitCreate (char *base_context );
public     :                                     logical InitExecuteFunction ( );
public     :                                     logical InitFunction ( );
public     :                                     char *LocateSource (int32 &line_ref, int32 &findx0_ref, int32 &iindx0_ref );
public     :                                     logical ProvideContextClass (PropertyHandle *res_ph, CTX_Control *high_ctx, logical *ret_edit );
public     :                                     logical ProvideProjectRef (char *modnames, CTX_Control *high_ctx );
public     :                                     logical ProvideReferencedClass (PropertyHandle *source_ph, char *modnames, CTX_Control *high_ctx );
public     :                                     logical SetupClassList (pc_ClassInputHelp *class_input_pc, GSRT(ODE_Project) *ref_projects, logical base_opt );
public     :                                     logical SetupExecuteFunction (CTX_Control *high_ctx );
public     :                                     logical SetupFunctImpList (char *fctname, pc_ClassFunctImpInputHelp *functimp_input_pc, ODE_Project *ode_project, logical base_opt );
public     :                                     logical SetupMemberList (pc_ClassMemberInputHelp *member_input_pc, ODE_Project *ode_project, logical base_opt, logical direct_access );
public     :                                                             pc_ODC_ImpClass (DBObjectHandle &obhandle, PIACC accopt );
public     :                                                             pc_ODC_ImpClass (PropertyHandle *prophdl );
};

#endif
