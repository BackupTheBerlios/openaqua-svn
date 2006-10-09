//******************************************************************/
//* OperationDecl - Declaration einer Operation
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2005/01/24
//******************************************************************/
#ifndef   OperationDecl_HPP 
#define   OperationDecl_HPP 





class     ParmList;
class     dbf;
#include  <sOperationDecl.hpp>
#include  <sPropertyHandle.hpp>
#include  <svcls.hpp>


#pragma pack(8)

 class   OperationDecl   : 
                                  public  vcls

{
 public     :         char                                         op_name[40] ATTR_ALIGN(4);                                 // Name der OPeration
 protected  :         char                                         impl_name[8] ;                                             // 
 protected  :         PropertyHandle                               retval ;                                                   // DBField für den Rückgabewert
 protected  :         ParmList                                    *parmlist ;                                                 // Liste der Parameterdeclarationen
 protected  :         logical                                      static_opt ;                                               // 
 public     :         ST_OpCodes                                   op_code ;                                                  // 




public     : 
                      char                                        *get_impl_name( ) { return(impl_name); }
                      PropertyHandle                              &get_retval( ) { return(retval); }
                      ParmList                                    *get_parmlist( ) { return(parmlist); }
                      logical                                      get_static_opt( ) { return(static_opt); }



  public    : virtual                   logical Check (PropertyHandle *return_value, PropertyHandle *co, ParmList *parameters, logical convopt );
  public    : static  opa7ImpExp        OperationDecl *__far __cdecl Create (FunctionTypes fttype, char *opnames, char *impnames, PropertyHandle *return_value, ParmList *parameters );
  public    : virtual opa7ImpExp        PropertyHandle Execute (PropertyHandle *co, ParmList *variables, ParmList *parameters );
  public    :         opa7ImpExp                                OperationDecl (char *fct_name, char *imp_name, logical stat_opt, ST_OpCodes st_op_code );
  public    :         opa7ImpExp                                OperationDecl ( );
  public    :         opa7ImpExp                                OperationDecl (const OperationDecl &opdecl_refc );
  public    : virtual opa7ImpExp        logical SetOBHandle (ACObject *obhandle );
  public    : virtual opa7ImpExp                                ~OperationDecl ( );




};


#pragma pack()
#endif

