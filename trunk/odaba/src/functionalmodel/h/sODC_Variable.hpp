/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_Variable



\date     $Date: 2006/05/10 20:49:08,29 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Variable_HPP
#define   ODC_Variable_HPP

class     ODC_Variable;

#ifndef   P_ODC_Executable_HPP
#define   P_ODC_Executable_HPP
#include  <sPI.hpp>
class       ODC_Executable;
PI_dcl     (ODC_Executable)
#endif
#ifndef   P_ODC_FunctImp_HPP
#define   P_ODC_FunctImp_HPP
#include  <sPI.hpp>
class       ODC_FunctImp;
PI_dcl     (ODC_FunctImp)
#endif
#ifndef   P_ODC_Function_HPP
#define   P_ODC_Function_HPP
#include  <sPI.hpp>
class       ODC_Function;
PI_dcl     (ODC_Function)
#endif
#ifndef   P_ODC_ImpClass_HPP
#define   P_ODC_ImpClass_HPP
#include  <sPI.hpp>
class       ODC_ImpClass;
PI_dcl     (ODC_ImpClass)
#endif
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Member.hpp>
#pragma pack(8)

class  ODC_Variable :public SDB_Member
{
protected  :         logical                                      initialize;                                                
protected  :         logical                                      const_val;                                                 
protected  :         logical                                      external;                                                  
protected  :         logical                                      in;                                                        // Input parameter
protected  :         logical                                      out;                                                       // Output parameter
protected  :         PI(ODC_ImpClass)                             externals_ref;                                             
protected  :         PI(ODC_ImpClass)                             constants_ref;                                             
protected  :         PI(ODC_Function)                             retvals;                                                   
protected  :         PI(ODC_FunctImp)                             parameters;                                                
protected  :         PI(ODC_Executable)                           main_functions;                                            

public     :
                     logical                                      get_initialize() { return(initialize); }
                     logical                                      get_const_val() { return(const_val); }
                     logical                                      get_external() { return(external); }
                     logical                                      get_in() { return(in); }
                     logical                                      get_out() { return(out); }
                     PI(ODC_ImpClass)                            &get_externals_ref() { return(externals_ref); }
                     PI(ODC_ImpClass)                            &get_constants_ref() { return(constants_ref); }
                     PI(ODC_Function)                            &get_retvals() { return(retvals); }
                     PI(ODC_FunctImp)                            &get_parameters() { return(parameters); }
                     PI(ODC_Executable)                          &get_main_functions() { return(main_functions); }
public     :                                        char *GetCastType (PropertyHandle *prophdl, NString &nstring );
};

#pragma pack()
#endif
