/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    ODC_FunctImp



\date     $Date: 2006/05/10 20:01:24,84 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_FunctImp_HPP
#define   ODC_FunctImp_HPP

class     ODC_FunctImp;

#ifndef   P_ODC_Include_HPP
#define   P_ODC_Include_HPP
#include  <sPI.hpp>
class       ODC_Include;
PI_dcl     (ODC_Include)
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
#ifndef   P_ODC_Variable_HPP
#define   P_ODC_Variable_HPP
#include  <sPI.hpp>
class       ODC_Variable;
PI_dcl     (ODC_Variable)
#endif
#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
class     PropertyHandle;
class     SDB_Member;
#include  <cProgramLanguage.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  ODC_FunctImp :public SDB_Resource
{
protected  :         logical                                      inline_funct;                                              
protected  :         logical                                      no_compile;                                                
protected  :         logical                                      sequence;                                                  
protected  :         logical                                      recover;                                                   
protected  :         char                                         head_line[513];                                            
protected  :         int16                                        linecount;                                                 
protected  :         int16                                        init_count;                                                
protected  :         int16                                        start_count;                                               
protected  :         int16                                        code_count;                                                
protected  :         int16                                        error_count;                                               
protected  :         int16                                        term_count;                                                
protected  :         PI(ODC_Variable)                             globals;                                                   
protected  :         PI(mem)                                      init_code;                                                 
protected  :         PI(mem)                                      start_code;                                                
protected  :         PI(mem)                                      code;                                                      
protected  :         PI(mem)                                      error_code;                                                
protected  :         PI(mem)                                      term_code;                                                 
protected  :         PI(ODC_Variable)                             parameters;                                                
protected  :         PI(ODC_PFunction)                            function;                                                  
protected  :         PI(ODC_Include)                              incl_before_impl;                                          
protected  :         PI(ODC_Include)                              incl_after_impl;                                           

public     :
                     logical                                      get_inline_funct() { return(inline_funct); }
                     logical                                      get_no_compile() { return(no_compile); }
                     logical                                      get_sequence() { return(sequence); }
                     logical                                      get_recover() { return(recover); }
                     char                                        *get_head_line() { return(head_line); }
                     int16                                        get_linecount() { return(linecount); }
                     int16                                        get_init_count() { return(init_count); }
                     int16                                        get_start_count() { return(start_count); }
                     int16                                        get_code_count() { return(code_count); }
                     int16                                        get_error_count() { return(error_count); }
                     int16                                        get_term_count() { return(term_count); }
                     PI(ODC_Variable)                            &get_globals() { return(globals); }
                     PI(mem)                                     &get_init_code() { return(init_code); }
                     PI(mem)                                     &get_start_code() { return(start_code); }
                     PI(mem)                                     &get_code() { return(code); }
                     PI(mem)                                     &get_error_code() { return(error_code); }
                     PI(mem)                                     &get_term_code() { return(term_code); }
                     PI(ODC_Variable)                            &get_parameters() { return(parameters); }
                     PI(ODC_PFunction)                           &get_function() { return(function); }
                     PI(ODC_Include)                             &get_incl_before_impl() { return(incl_before_impl); }
                     PI(ODC_Include)                             &get_incl_after_impl() { return(incl_after_impl); }
public     :                                        char *GetCIFunctName (PropertyHandle *prophdl, NString &nstring );
public     :                                        char *GetCIRetValue (PropertyHandle *prophdl, NString &nstring );
public     :                                        char *GetCOMParmList (PropertyHandle *prophdl, NString &nstring, logical prototyp );
public     :                                        char *GetParmCallList (PropertyHandle *prophdl, NString &nstring );
public     :                                        char *GetParmList (PropertyHandle *prophdl, NString &nstring, logical prototyp );
public     :                                        logical IsIFImplement (char *if_imp_praefix );
public     :                                        logical SetLineCount (PropertyHandle *prophdl, char *propnames, int16 line_cnt );
public     :                                        logical UpdatePrototype (PropertyHandle *prophdl );
public     :                                        logical UpdateSource (PropertyHandle *prophdl );
};

#pragma pack()
#endif
