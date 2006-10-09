/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FunctLink

\brief    


\date     $Date: 2006/03/12 19:13:23,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FunctLink_HPP
#define   FunctLink_HPP

class     FunctLink;

class     Dictionary;
class     ParmList;
class     PropertyHandle;
class     vcls;
#include  <sFunctLink.hpp>
#pragma pack(8)

class  FunctLink
{
protected  :         vcls                                        *vclsptr;                                                   //
protected  :         OCTP                                         flnkfct;                                                   //
protected  :         CCTP                                         flnkcfct;                                                  

public     :
                     vcls                                        *get_vclsptr() { return(vclsptr); }
                     OCTP                                        &get_flnkfct() { return(flnkfct); }
                     CCTP                                        &get_flnkcfct() { return(flnkcfct); }
public     :                                     logical Check (PropertyHandle *return_value, PropertyHandle *co, ParmList *parameters, logical convopt );
public     :         opa7ImpExp                  logical Execute (PropertyHandle *co, PropertyHandle *retval, ParmList *parameters, char *implname, ExecutionTypes exectype );
public     :         opa7ImpExp                                          FunctLink (OCTP fctptr );
public     :         opa7ImpExp                                          FunctLink (CCTP cfctptr );
public     :         opa7ImpExp                                          FunctLink ( );
public     :         opa7ImpExp                                          FunctLink (FunctLink &flink );
public     :         opa7ImpExp                  logical SetFunctionPtr (DictionaryHandle dicthdl, char *co_type, char *fname, logical check_opt=NO );
public     :         opa7ImpExp                  void SetInstance (vcls *vclsinst );
public     :         opa7ImpExp                                          ~FunctLink ( );
};

#pragma pack()
#endif
