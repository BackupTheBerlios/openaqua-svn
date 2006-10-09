/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecStruct

\brief    


\date     $Date: 2006/03/12 19:09:59,56 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExecStruct_HPP
#define   ExecStruct_HPP

class     ExecStruct;

class     CTX_Structure;
class     DBFieldDef;
class     PropertyHandle;
class     UCA_Action;
#include  <sSimpleAction.hpp>
#pragma pack(8)

class  ExecStruct
{
protected  :         PropertyHandle                              *field;                                                     //
protected  :         CTX_Structure                               *struct_context;                                            //
protected  :         logical                                      create;                                                    //
protected  :         logical                                      recreate;                                                  //
protected  :         SimpleAction                                 exp_filter;                                                //
protected  :         SimpleAction                                 imp_filter;                                                //
protected  :         SimpleAction                                 handler;                                                   //

public     :
                     PropertyHandle                              *get_field() { return(field); }
                     CTX_Structure                               *get_struct_context() { return(struct_context); }
                     logical                                      get_create() { return(create); }
                     logical                                      get_recreate() { return(recreate); }
                     SimpleAction                                &get_exp_filter() { return(exp_filter); }
                     SimpleAction                                &get_imp_filter() { return(imp_filter); }
                     SimpleAction                                &get_handler() { return(handler); }
public     :                                     UCA_Action *CreateExpFilter ( );
public     :                                     UCA_Action *CreateHandler ( );
public     :                                     UCA_Action *CreateImpFilter ( );
public     :                                                             ExecStruct (PropertyHandle *struct_pi, PropertyHandle *prop_ptr );
public     :                                                             ExecStruct ( );
public     :                                                             ~ExecStruct ( );
};

#pragma pack()
#endif
