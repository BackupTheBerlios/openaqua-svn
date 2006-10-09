/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Module

\brief    


\date     $Date: 2006/03/13 21:30:33,56 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Module_HPP
#define   ODC_Module_HPP

class     ODC_Module;

#ifndef   P_ODC_Database_HPP
#define   P_ODC_Database_HPP
#include  <sPI.hpp>
class       ODC_Database;
PI_dcl     (ODC_Database)
#endif
#ifndef   P_ODC_Error_HPP
#define   P_ODC_Error_HPP
#include  <sPI.hpp>
class       ODC_Error;
PI_dcl     (ODC_Error)
#endif
#ifndef   P_ODC_ErrorClass_HPP
#define   P_ODC_ErrorClass_HPP
#include  <sPI.hpp>
class       ODC_ErrorClass;
PI_dcl     (ODC_ErrorClass)
#endif
#ifndef   P_ODC_Executable_HPP
#define   P_ODC_Executable_HPP
#include  <sPI.hpp>
class       ODC_Executable;
PI_dcl     (ODC_Executable)
#endif
#ifndef   P_ODC_ImpClass_HPP
#define   P_ODC_ImpClass_HPP
#include  <sPI.hpp>
class       ODC_ImpClass;
PI_dcl     (ODC_ImpClass)
#endif
#ifndef   P_ODC_Module_HPP
#define   P_ODC_Module_HPP
#include  <sPI.hpp>
class       ODC_Module;
PI_dcl     (ODC_Module)
#endif
#ifndef   P_ODC_NamedObject_HPP
#define   P_ODC_NamedObject_HPP
#include  <sPI.hpp>
class       ODC_NamedObject;
PI_dcl     (ODC_NamedObject)
#endif
#ifndef   P_ODC_PFunction_HPP
#define   P_ODC_PFunction_HPP
#include  <sPI.hpp>
class       ODC_PFunction;
PI_dcl     (ODC_PFunction)
#endif
#ifndef   P_ODC_View_HPP
#define   P_ODC_View_HPP
#include  <sPI.hpp>
class       ODC_View;
PI_dcl     (ODC_View)
#endif
class     ODC_Database;
#include  <cCompileStates.h>
#include  <sSDB_NameSpace.hpp>
#pragma pack(8)

class  ODC_Module :public SDB_NameSpace
{
protected  :         int32                                        odaba2_version ATTR_ALIGN(4);                              
protected  :         logical                                      odaba2_productio;                                          
protected  :         logical                                      req_genincl;                                               
protected  :         logical                                      is_modified;                                               
protected  :         CompileStates                                req_compile;                                               
protected  :         logical                                      no_compile;                                                
protected  :         logical                                      proj_busy;                                                 
protected  :         char                                         ctx_interface[40];                                         
protected  :         PI(ODC_ErrorClass)                           error_class;                                               
protected  :         PI(ODC_Error)                                errors;                                                    
protected  :         PI(ODC_NamedObject)                          named_objects;                                             
protected  :         PI(ODC_Module)                               sub_modules;                                               
protected  :         PI(ODC_Module)                               parent_module;                                             
protected  :         PI(ODC_Module)                               module_ref;                                                
protected  :         PI(ODC_ImpClass)                             classes;                                                   
protected  :         PI(ODC_View)                                 views;                                                     
protected  :         PI(ODC_Database)                             database;                                                  
protected  :         PI(ODC_PFunction)                            function_descr;                                            //
protected  :         PI(ODC_PFunction)                            pfunctions;                                                //
protected  :         PI(ODC_Executable)                           main_functions;                                            //

public     :
                     int32                                        get_odaba2_version() { return(odaba2_version); }
                     logical                                      get_odaba2_productio() { return(odaba2_productio); }
                     logical                                      get_req_genincl() { return(req_genincl); }
                     logical                                      get_is_modified() { return(is_modified); }
                     CompileStates                                get_req_compile() { return(req_compile); }
                     logical                                      get_no_compile() { return(no_compile); }
                     logical                                      get_proj_busy() { return(proj_busy); }
                     char                                        *get_ctx_interface() { return(ctx_interface); }
                     PI(ODC_ErrorClass)                          &get_error_class() { return(error_class); }
                     PI(ODC_Error)                               &get_errors() { return(errors); }
                     PI(ODC_NamedObject)                         &get_named_objects() { return(named_objects); }
                     PI(ODC_Module)                              &get_sub_modules() { return(sub_modules); }
                     PI(ODC_Module)                              &get_parent_module() { return(parent_module); }
                     PI(ODC_Module)                              &get_module_ref() { return(module_ref); }
                     PI(ODC_ImpClass)                            &get_classes() { return(classes); }
                     PI(ODC_View)                                &get_views() { return(views); }
                     PI(ODC_Database)                            &get_database() { return(database); }
                     PI(ODC_PFunction)                           &get_function_descr() { return(function_descr); }
                     PI(ODC_PFunction)                           &get_pfunctions() { return(pfunctions); }
                     PI(ODC_Executable)                          &get_main_functions() { return(main_functions); }
};

#pragma pack()
#endif
