/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ODE_Project



\date     $Date: 2006/05/23 13:32:54,28 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODE_Project_HPP
#define   ODE_Project_HPP

class     ODE_Project;

#include  <sGSRT.h>
class     ODE_Project;
class     pODE;
class     pc1_ODC_PFunction;
class     pc_ClassMemberInputHelp;
#include  <sDatabaseHandle.hpp>
#include  <sODE_Helper.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc1_ODC_ImpClass.hpp>
#include  <spc1_ODC_Project.hpp>
#include  <spc1_SDB_Structure.hpp>
#include  <spc_ClassInputHelp.hpp>
#pragma pack(8)

class  ODE_Project :public ODE_Helper
{
protected  :         char                                         project_name[41];                                          // 
protected  :         logical                                      implemented;                                               // 
protected  :         GSRT(ODE_Project)                           *ref_projects;                                              
protected  :         DatabaseHandle                               db_handle;                                                 
protected  :         pc1_ODC_Project                              project;                                                   
protected  :         pc1_ODC_ImpClass                             project_classes;                                           
protected  :         pc1_ODC_ImpClass                             impclasses;                                                
protected  :         pc1_SDB_Structure                            structures;                                                
protected  :         PropertyHandle                               enums;                                                     
protected  :         pc_ClassInputHelp                            input_help;                                                

public     :
                     char                                        *get_project_name() { return(project_name); }
                     logical                                      get_implemented() { return(implemented); }
                     GSRT(ODE_Project)                           *get_ref_projects() { return(ref_projects); }
                     DatabaseHandle                              &get_db_handle() { return(db_handle); }
                     pc1_ODC_Project                             &get_project() { return(project); }
                     pc1_ODC_ImpClass                            &get_project_classes() { return(project_classes); }
                     pc1_ODC_ImpClass                            &get_impclasses() { return(impclasses); }
                     pc1_SDB_Structure                           &get_structures() { return(structures); }
                     PropertyHandle                              &get_enums() { return(enums); }
                     pc_ClassInputHelp                           &get_input_help() { return(input_help); }
public     :                                        void ClosePHs ( );
public     :                                        logical DeinitRefProjects ( );
public     :                                        void Deinitialize ( );
public     :                                        PropertyHandle *GetClassInputHelpPH (logical refresh_opt );
public     :                                        PropertyHandle *GetFunctionInputHelpPH (TypeKey &type_key, char *codestring, int32 textpos, logical refresh_opt );
public     :                                        pc1_ODC_ImpClass *GetImplementedClass (TypeKey &type_key );
public     :                                        pc1_ODC_ImpClass *GetImplementedClass (PropertyHandle *class_ph );
public     :                                        pc_ClassMemberInputHelp *GetMemberInputHelpPH (TypeKey &type_key, char *codestring, int32 offset, logical refresh_opt );
public     :                                        logical InitRefProjects ( );
public     :                                        logical Initialize (PropertyHandle *prophdl );
public     :                                        logical InitializePFunction (pc1_ODC_PFunction *pfunct_pc, TypeKey &type_key, pODE *ode_ctx );
public     :                                             ODE_Project ( );
public     :                                        logical OpenPHs (char *prjnames, PIACC accopt );
public     :                                        logical ProvideType (TypeKey &type_key, pc1_ODC_ImpClass *impcls_pc, PropertyHandle *cs_ph, logical no_struct, CTX_Control *high_ctx );
public     :                                             ~ODE_Project ( );
};

#pragma pack()
#endif
