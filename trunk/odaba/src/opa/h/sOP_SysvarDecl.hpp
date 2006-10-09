//******************************************************************/
//* OP_SysvarDecl - Operation-Deklaration für Systemvariablen
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OPA7/OPA7.dev
//*
//*  ODE Version 2.1                                   2003/11/14
//******************************************************************/
#ifndef   OP_SysvarDecl_HPP 
#define   OP_SysvarDecl_HPP 





class     ParmList;
#include  <sOperationDecl.hpp>
#include  <sPropertyHandle.hpp>


#pragma pack(8)

 class   OP_SysvarDecl   : 
                                  public  OperationDecl

{
 protected  :         char                                         sysvar_names[41] ATTR_ALIGN(4);                            // 




public     : 



  public    : virtual opa7ImpExp        PropertyHandle Execute (PropertyHandle *co, ParmList *parameters );
  public    :         opa7ImpExp                                OP_SysvarDecl (char *opnames, char *impnames, PropertyHandle *return_value );
  public    : virtual opa7ImpExp                                ~OP_SysvarDecl ( );




};


#pragma pack()
#endif

