//******************************************************************/
//* FunctionDecl - Funktiondeclaration
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2005/01/24
//******************************************************************/
#ifndef   FunctionDecl_HPP 
#define   FunctionDecl_HPP 





class     ParmList;
#include  <sFunctLink.hpp>
#include  <sFunctionDecl.hpp>
#include  <sOperationDecl.hpp>
#include  <sPropertyHandle.hpp>


#pragma pack(8)

 class   FunctionDecl   : 
                                  public  OperationDecl,
                                  public  FunctLink

{




public     : 



  public    : virtual opa7ImpExp        logical Check (PropertyHandle *return_value, PropertyHandle *co, ParmList *parameters, logical convopt );
  public    : virtual opa7ImpExp        PropertyHandle Execute (PropertyHandle *co, ParmList *variables, ParmList *parameters );
  public    :         opa7ImpExp                                FunctionDecl (char *imp_name, PropertyHandle *return_value, ParmList *parameters, FunctLink &flink, logical stat_opt, char *fct_name );
  public    :         opa7ImpExp                                FunctionDecl ( );
  public    :         opa7ImpExp                                FunctionDecl (PropertyHandle *fct_pi, char *co_type );
  public    :         opa7ImpExp                                FunctionDecl (char *co_type, char *opname );
  public    :         opa7ImpExp                                FunctionDecl (FunctionDecl &fctdecl_ref );
  public    :                           FunctionDecl &operator= (FunctionDecl &fctdecl_ref );
  public    : virtual opa7ImpExp                                ~FunctionDecl ( );




};


#pragma pack()
#endif

