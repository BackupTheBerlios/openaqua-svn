/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExecAlloc

\brief    


\date     $Date: 2006/03/12 19:09:58,62 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExecAlloc_HPP
#define   ExecAlloc_HPP

class     ExecAlloc;

#ifndef   DPA_ExecFieldAlloc_HPP
#define   DPA_ExecFieldAlloc_HPP
#include  <sExecFieldAlloc.hpp>
#include  <sDPA.h>
#endif
#include  <sExecStruct.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  ExecAlloc
{
protected  :         ExecStruct                                   int_field;                                                 //
protected  :         ExecStruct                                   ext_field;                                                 //
protected  :         DPA(ExecFieldAlloc)                          field_allocs;                                              //
protected  :         logical                                      top_alloc;                                                 //

public     :
                     ExecStruct                                  &get_int_field() { return(int_field); }
                     ExecStruct                                  &get_ext_field() { return(ext_field); }
                     DPA(ExecFieldAlloc)                         &get_field_allocs() { return(field_allocs); }
                     logical                                      get_top_alloc() { return(top_alloc); }
public     :                                     logical CheckError (ExecStruct &srcefield, void *srce_inst );
public     :                                     logical CopyCollections (void *targ_inst, void *srce_inst, logical exp_opt, logical new_inst );
public     :                                     logical CopyDirect (void *targ_inst, void *srce_inst, logical exp_opt );
public     :                                                             ExecAlloc (PropertyHandle &alloc_pi, PropertyHandle *intfield, PropertyHandle *extfield, logical w_topalc=NO );
public     :                                                             ExecAlloc ( );
public     :                                     logical Execute (logical exp_opt );
public     :                                                             ~ExecAlloc ( );
};

#pragma pack()
#endif
