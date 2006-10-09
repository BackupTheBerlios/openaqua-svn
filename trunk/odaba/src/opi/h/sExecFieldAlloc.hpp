/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecFieldAlloc

\brief    


\date     $Date: 2006/03/12 19:09:59,39 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExecFieldAlloc_HPP
#define   ExecFieldAlloc_HPP

class     ExecFieldAlloc;

class     ExecAlloc;
#include  <sExecField.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  ExecFieldAlloc
{
protected  :         ExecField                                    int_field;                                                 
protected  :         ExecField                                    ext_field;                                                 
protected  :         ExecAlloc                                   *struct_alloc;                                              

public     :
                     ExecField                                   &get_int_field() { return(int_field); }
                     ExecField                                   &get_ext_field() { return(ext_field); }
                     ExecAlloc                                   *get_struct_alloc() { return(struct_alloc); }
public     :                                     logical CopyCollection (void *targ_inst, void *srce_inst, logical exp_opt, logical new_inst );
public     :                                     logical CopyDirect (void *targ_inst, void *srce_inst, logical exp_opt );
public     :                                                             ExecFieldAlloc (PropertyHandle &falloc_pi, PropertyHandle *intfield, PropertyHandle *extfield );
public     :                                                             ExecFieldAlloc ( );
public     :                                                             ~ExecFieldAlloc ( );
};

#pragma pack()
#endif
