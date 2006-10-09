/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Include

\brief    


\date     $Date: 2006/03/13 21:30:33,29 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Include_HPP
#define   ODC_Include_HPP

class     ODC_Include;

#ifndef   P_ODC_FunctImp_HPP
#define   P_ODC_FunctImp_HPP
#include  <sPI.hpp>
class       ODC_FunctImp;
PI_dcl     (ODC_FunctImp)
#endif
#ifndef   P_ODC_ImpClass_HPP
#define   P_ODC_ImpClass_HPP
#include  <sPI.hpp>
class       ODC_ImpClass;
PI_dcl     (ODC_ImpClass)
#endif
#ifndef   P_ODC_Main_HPP
#define   P_ODC_Main_HPP
#include  <sPI.hpp>
class       ODC_Main;
PI_dcl     (ODC_Main)
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
#include  <sFileMemo.hpp>
#pragma pack(8)

class  ODC_Include :public FileMemo
{
protected  :         PI(ODC_Project)                              projects;                                                  
protected  :         PI(ODC_ImpClass)                             systemincl_ref;                                            
protected  :         PI(ODC_ImpClass)                             beg_class_incls;                                           
protected  :         PI(ODC_ImpClass)                             after_class_incls;                                         
protected  :         PI(ODC_ImpClass)                             userincl_ref;                                              
protected  :         PI(ODC_ImpClass)                             end_class_incls;                                           
protected  :         PI(ODC_PFunction)                            before_impls_incls;                                        
protected  :         PI(ODC_PFunction)                            after_impls_incls;                                         
protected  :         PI(ODC_FunctImp)                             before_impl_incls;                                         
protected  :         PI(ODC_FunctImp)                             after_impl_incls;                                          
protected  :         PI(ODC_Main)                                 user_main_incls;                                           
protected  :         PI(ODC_Main)                                 system_main_incls;                                         

public     :
                     PI(ODC_Project)                             &get_projects() { return(projects); }
                     PI(ODC_ImpClass)                            &get_systemincl_ref() { return(systemincl_ref); }
                     PI(ODC_ImpClass)                            &get_beg_class_incls() { return(beg_class_incls); }
                     PI(ODC_ImpClass)                            &get_after_class_incls() { return(after_class_incls); }
                     PI(ODC_ImpClass)                            &get_userincl_ref() { return(userincl_ref); }
                     PI(ODC_ImpClass)                            &get_end_class_incls() { return(end_class_incls); }
                     PI(ODC_PFunction)                           &get_before_impls_incls() { return(before_impls_incls); }
                     PI(ODC_PFunction)                           &get_after_impls_incls() { return(after_impls_incls); }
                     PI(ODC_FunctImp)                            &get_before_impl_incls() { return(before_impl_incls); }
                     PI(ODC_FunctImp)                            &get_after_impl_incls() { return(after_impl_incls); }
                     PI(ODC_Main)                                &get_user_main_incls() { return(user_main_incls); }
                     PI(ODC_Main)                                &get_system_main_incls() { return(system_main_incls); }
};

#pragma pack()
#endif
