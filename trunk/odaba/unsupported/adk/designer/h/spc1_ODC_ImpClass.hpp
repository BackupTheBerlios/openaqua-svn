/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_ImpClass



\date     $Date: 2006/05/31 16:22:22,07 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ODC_ImpClass_HPP
#define   pc1_ODC_ImpClass_HPP

class     pc1_ODC_ImpClass;

#include  <sGSRT.h>
class     ODE_Project;
class     ODE_Project;
class     pc_ClassFunctImpInputHelp;
class     pc_ClassInputHelp;
class     pc_ClassMemberInputHelp;
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc1_SDB_Structure.hpp>
class  pc1_ODC_ImpClass :public pc1_SDB_Structure
{

public     :
public     :                                        logical CheckContextClass (char *base_context, char *prjnames, CTX_Control *high_ctx );
public     :                                        logical CheckReferencedClass (char *typenames, GSRT(ODE_Project) *ref_projects, CTX_Control *high_ctx );
public     :                                        logical CreateReferencedClass (PropertyHandle *new_ODE_TypeRef_ph );
public     :                                        logical GetContextInterface ( );
public     :                                        PropertyHandle *GetMember (char *memnames, char search_type );
public     :                                        PropertyHandle *GetMember (PropertyHandle *memb_ph, char *memnames );
public     :                                        logical GetTemplate (char *clsnames );
public     :                                        logical InitClass (logical ini_opt );
public     :                                        logical InitContextClass (char *base_context, char *prjnames );
public     :                                        logical InitCreate (char *base_context );
public     :                                        logical InitExecuteFunction ( );
public     :                                        logical InitFunction ( );
public     :                                        logical IsImplemented (TypeKey &type_key, logical exist_only );
public     :                                        char *LocateSource (int32 &line_ref, int32 &findx0_ref, int32 &iindx0_ref );
public     :                                        logical ProvideContextClass (PropertyHandle *res_ph, CTX_Control *high_ctx, logical *ret_edit );
public     :                                        logical ProvideContextInterface (logical gui_opt, NString &nstring );
public     :                                        logical ProvideProjectRef (char *modnames, CTX_Control *high_ctx );
public     :                                        logical ProvideReferencedClass (PropertyHandle *source_ph, char *modnames, CTX_Control *high_ctx );
public     :                                        logical SetupClassList (pc_ClassInputHelp *class_input_pc, GSRT(ODE_Project) *ref_projects, logical base_opt );
public     :                                        logical SetupExecuteFunction (CTX_Control *high_ctx );
public     :                                        logical SetupFunctImpList (char *fctname, pc_ClassFunctImpInputHelp *functimp_input_pc, ODE_Project *ode_project, logical base_opt );
public     :                                        logical SetupMemberList (pc_ClassMemberInputHelp *member_input_pc, ODE_Project *ode_project, logical base_opt, logical direct_access );
public     :                                             pc1_ODC_ImpClass (DBObjectHandle &obhandle, PIACC accopt );
public     :                                             pc1_ODC_ImpClass (PropertyHandle *prophdl );
};

#endif
