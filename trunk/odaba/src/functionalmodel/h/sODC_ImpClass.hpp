/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_ImpClass



\date     $Date: 2006/05/11 17:12:25,90 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_ImpClass_HPP
#define   ODC_ImpClass_HPP

class     ODC_ImpClass;

#ifndef   P_ODC_FunctGroup_HPP
#define   P_ODC_FunctGroup_HPP
#include  <sPI.hpp>
class       ODC_FunctGroup;
PI_dcl     (ODC_FunctGroup)
#endif
#ifndef   P_ODC_Include_HPP
#define   P_ODC_Include_HPP
#include  <sPI.hpp>
class       ODC_Include;
PI_dcl     (ODC_Include)
#endif
#ifndef   P_ODC_Module_HPP
#define   P_ODC_Module_HPP
#include  <sPI.hpp>
class       ODC_Module;
PI_dcl     (ODC_Module)
#endif
#ifndef   P_ODC_PFunction_HPP
#define   P_ODC_PFunction_HPP
#include  <sPI.hpp>
class       ODC_PFunction;
PI_dcl     (ODC_PFunction)
#endif
#ifndef   P_ODC_Project_HPP
#define   P_ODC_Project_HPP
#include  <sPI.hpp>
class       ODC_Project;
PI_dcl     (ODC_Project)
#endif
#ifndef   P_ODC_Variable_HPP
#define   P_ODC_Variable_HPP
#include  <sPI.hpp>
class       ODC_Variable;
PI_dcl     (ODC_Variable)
#endif
#ifndef   P_SDB_TypeRef_HPP
#define   P_SDB_TypeRef_HPP
#include  <sPI.hpp>
class       SDB_TypeRef;
PI_dcl     (SDB_TypeRef)
#endif
class     PropertyHandle;
#include  <cClassModLevel.h>
#include  <cCompileStates.h>
#include  <cProgramLanguage.h>
#include  <cRTTI_Types.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Structure.hpp>
#pragma pack(8)

class  ODC_ImpClass :public SDB_Structure
{
protected  :         dttm                                         date_time;                                                 
protected  :         CompileStates                                req_compile;                                               
protected  :         logical                                      req_genincl;                                               
protected  :         ClassModLevel                                mod_level;                                                 
protected  :         ProgramLanguage                              opt_language;                                              
protected  :         logical                                      opt_debug;                                                 
protected  :         logical                                      no_compile;                                                
protected  :         logical                                      opt_export;                                                
protected  :         logical                                      expandable;                                                
protected  :         RTTI_Types                                   rtti_type;                                                 
protected  :         char                                         reserve[12];                                               
protected  :         logical                                      expansion;                                                 
protected  :         PI(mem)                                      template_parms;                                            
protected  :         PI(ODC_PFunction)                            function_descr;                                            
protected  :         PI(ODC_PFunction)                            pfunctions;                                                
protected  :         PI(SDB_TypeRef)                              class_ref;                                                 
protected  :         PI(ODC_Variable)                             constants;                                                 
protected  :         PI(ODC_Variable)                             externals;                                                 
protected  :         PI(ODC_Include)                              incl_system;                                               
protected  :         PI(ODC_Include)                              incl_user;                                                 
protected  :         PI(ODC_Include)                              incl_beg_class;                                            
protected  :         PI(ODC_Include)                              incl_end_class;                                            
protected  :         PI(ODC_Include)                              incl_after_class;                                          
protected  :         PI(ODC_Project)                              proj_class_ref;                                            
protected  :         PI(ODC_FunctGroup)                           function_groups;                                           
protected  :         PI(ODC_Module)                               module;                                                    

public     :
                     dttm                                        &get_date_time() { return(date_time); }
                     CompileStates                                get_req_compile() { return(req_compile); }
                     logical                                      get_req_genincl() { return(req_genincl); }
                     ClassModLevel                                get_mod_level() { return(mod_level); }
                     ProgramLanguage                              get_opt_language() { return(opt_language); }
                     logical                                      get_opt_debug() { return(opt_debug); }
                     logical                                      get_no_compile() { return(no_compile); }
                     logical                                      get_opt_export() { return(opt_export); }
                     logical                                      get_expandable() { return(expandable); }
                     RTTI_Types                                   get_rtti_type() { return(rtti_type); }
                     char                                        *get_reserve() { return(reserve); }
                     logical                                      get_expansion() { return(expansion); }
                     PI(mem)                                     &get_template_parms() { return(template_parms); }
                     PI(ODC_PFunction)                           &get_function_descr() { return(function_descr); }
                     PI(ODC_PFunction)                           &get_pfunctions() { return(pfunctions); }
                     PI(SDB_TypeRef)                             &get_class_ref() { return(class_ref); }
                     PI(ODC_Variable)                            &get_constants() { return(constants); }
                     PI(ODC_Variable)                            &get_externals() { return(externals); }
                     PI(ODC_Include)                             &get_incl_system() { return(incl_system); }
                     PI(ODC_Include)                             &get_incl_user() { return(incl_user); }
                     PI(ODC_Include)                             &get_incl_beg_class() { return(incl_beg_class); }
                     PI(ODC_Include)                             &get_incl_end_class() { return(incl_end_class); }
                     PI(ODC_Include)                             &get_incl_after_class() { return(incl_after_class); }
                     PI(ODC_Project)                             &get_proj_class_ref() { return(proj_class_ref); }
                     PI(ODC_Module)                              &get_module() { return(module); }
public     :                                        logical ExpressionsOnly (PropertyHandle *prophdl );
public     :                                        char *GetDocFileName (PropertyHandle *prophdl, NString &nstring, char *doc_type, logical if_opt );
public     :                                        logical IsExprClass (PropertyHandle *prophdl );
public     :                                        logical IsIFClass (PropertyHandle *prophdl, char *if_imp_praefix );
public     : static                                 char *__cdecl LanguageExt (NString &nstring, DatabaseHandle &dbhandle, char *clsnames );
};

#pragma pack()
#endif
