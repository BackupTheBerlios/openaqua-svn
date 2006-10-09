/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_PFunction



\date     $Date: 2006/04/27 12:45:16,98 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_PFunction_HPP
#define   ODC_PFunction_HPP

class     ODC_PFunction;

#ifndef   P_ODC_FunctGroup_HPP
#define   P_ODC_FunctGroup_HPP
#include  <sPI.hpp>
class       ODC_FunctGroup;
PI_dcl     (ODC_FunctGroup)
#endif
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
class     PropertyHandle;
#include  <sODC_Function.hpp>
#pragma pack(8)

class  ODC_PFunction :public ODC_Function
{
protected  :         int16                                        linecount;                                                 
protected  :         logical                                      const_val;                                                 
protected  :         logical                                      pure_funct;                                                
protected  :         logical                                      exportfunction;                                            
protected  :         PI(ODC_FunctImp)                             implementation_descr;                                      
protected  :         PI(ODC_FunctImp)                             implementations;                                           
protected  :         PI(ODC_ImpClass)                             classx;                                                    
protected  :         PI(ODC_Include)                              incl_before_impls;                                         
protected  :         PI(ODC_Include)                              incl_after_impls;                                          
protected  :         PI(ODC_FunctGroup)                           function_group;                                            
protected  :         PI(ODC_Module)                               module;                                                    

public     :
                     int16                                        get_linecount() { return(linecount); }
                     logical                                      get_const_val() { return(const_val); }
                     logical                                      get_pure_funct() { return(pure_funct); }
                     PI(ODC_FunctImp)                            &get_implementation_descr() { return(implementation_descr); }
                     PI(ODC_FunctImp)                            &get_implementations() { return(implementations); }
                     PI(ODC_ImpClass)                            &get_classx() { return(classx); }
                     PI(ODC_Include)                             &get_incl_before_impls() { return(incl_before_impls); }
                     PI(ODC_Include)                             &get_incl_after_impls() { return(incl_after_impls); }
                     PI(ODC_FunctGroup)                          &get_function_group() { return(function_group); }
                     PI(ODC_Module)                              &get_module() { return(module); }
public     :                                        logical SetLineCount (PropertyHandle *prophdl, int32 linecnt );
};

#pragma pack()
#endif
