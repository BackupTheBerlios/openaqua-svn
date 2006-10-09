/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_Main



\date     $Date: 2006/05/10 20:39:15,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Main_HPP
#define   ODC_Main_HPP

class     ODC_Main;

#ifndef   P_ODC_ClassRef_HPP
#define   P_ODC_ClassRef_HPP
#include  <sPI.hpp>
class       ODC_ClassRef;
PI_dcl     (ODC_ClassRef)
#endif
#ifndef   P_ODC_Include_HPP
#define   P_ODC_Include_HPP
#include  <sPI.hpp>
class       ODC_Include;
PI_dcl     (ODC_Include)
#endif
#ifndef   P_ODC_Variable_HPP
#define   P_ODC_Variable_HPP
#include  <sPI.hpp>
class       ODC_Variable;
PI_dcl     (ODC_Variable)
#endif
#include  <cCompileStates.h>
#include  <cProgramLanguage.h>
#include  <sODC_PFunction.hpp>
#pragma pack(8)

class  ODC_Main :public ODC_PFunction
{
protected  :         logical                                      opt_debug;                                                 
protected  :         ProgramLanguage                              opt_language;                                              
protected  :         CompileStates                                req_compile;                                               
protected  :         logical                                      no_compile;                                                
protected  :         PI(ODC_Include)                              mincl_system;                                              
protected  :         PI(ODC_Include)                              mincl_user;                                                

public     :
                     logical                                      get_opt_debug() { return(opt_debug); }
                     ProgramLanguage                              get_opt_language() { return(opt_language); }
                     CompileStates                                get_req_compile() { return(req_compile); }
                     logical                                      get_no_compile() { return(no_compile); }
                     PI(ODC_Include)                             &get_mincl_system() { return(mincl_system); }
                     PI(ODC_Include)                             &get_mincl_user() { return(mincl_user); }
};

#pragma pack()
#endif
