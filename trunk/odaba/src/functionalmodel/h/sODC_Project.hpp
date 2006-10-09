/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_Project



\date     $Date: 2006/05/10 19:45:48,82 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Project_HPP
#define   ODC_Project_HPP

class     ODC_Project;

#ifndef   P_ODC_BaseContext_HPP
#define   P_ODC_BaseContext_HPP
#include  <sPI.hpp>
class       ODC_BaseContext;
PI_dcl     (ODC_BaseContext)
#endif
#ifndef   P_ODC_Environment_HPP
#define   P_ODC_Environment_HPP
#include  <sPI.hpp>
class       ODC_Environment;
PI_dcl     (ODC_Environment)
#endif
#ifndef   P_ODC_ImpClass_HPP
#define   P_ODC_ImpClass_HPP
#include  <sPI.hpp>
class       ODC_ImpClass;
PI_dcl     (ODC_ImpClass)
#endif
#ifndef   P_ODC_Include_HPP
#define   P_ODC_Include_HPP
#include  <sPI.hpp>
class       ODC_Include;
PI_dcl     (ODC_Include)
#endif
#ifndef   P_ODC_ProjRef_HPP
#define   P_ODC_ProjRef_HPP
#include  <sPI.hpp>
class       ODC_ProjRef;
PI_dcl     (ODC_ProjRef)
#endif
#ifndef   P_ODC_Project_HPP
#define   P_ODC_Project_HPP
#include  <sPI.hpp>
class       ODC_Project;
PI_dcl     (ODC_Project)
#endif
#include  <cCompileStates.h>
#include  <sODC_Module.hpp>
#pragma pack(8)

class  ODC_Project :public ODC_Module
{
protected  :         char                                         proj_path[256];                                            
protected  :         char                                         resource_base[64];                                         
protected  :         char                                         path_names[20][32];                                        
protected  :         PI(ODC_ProjRef)                              proj_references;                                           
protected  :         PI(ODC_BaseContext)                          basecontexts;                                              
protected  :         PI(ODC_Include)                              proj_include;                                              
protected  :         PI(ODC_Project)                              ref_projects;                                              
protected  :         PI(ODC_Environment)                          environment;                                               
protected  :         PI(ODC_Project)                              sub_projects;                                              
protected  :         PI(ODC_Project)                              parent_project;                                            
protected  :         PI(ODC_ImpClass)                             proj_classes;                                              

public     :
                     char                                        *get_proj_path() { return(proj_path); }
                     char                                        *get_resource_base() { return(resource_base); }
                     PI(ODC_ProjRef)                             &get_proj_references() { return(proj_references); }
                     PI(ODC_BaseContext)                         &get_basecontexts() { return(basecontexts); }
                     PI(ODC_Include)                             &get_proj_include() { return(proj_include); }
                     PI(ODC_Project)                             &get_ref_projects() { return(ref_projects); }
                     PI(ODC_Environment)                         &get_environment() { return(environment); }
                     PI(ODC_Project)                             &get_sub_projects() { return(sub_projects); }
                     PI(ODC_Project)                             &get_parent_project() { return(parent_project); }
                     PI(ODC_ImpClass)                            &get_proj_classes() { return(proj_classes); }
public     :                                        char *GetDocFileName (PropertyHandle *prophdl, NString &nstring, char *doc_type );
public     :                                        char *GetProjectPath (PropertyHandle *prophdl, NString &nstring, char *folder_type );
};

#pragma pack()
#endif
