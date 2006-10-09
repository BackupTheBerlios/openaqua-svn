/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    OPA_Variables

\brief    SOS-Process variables


\date     $Date: 2006/03/12 19:13:42,67 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPA_Variables_HPP
#define   OPA_Variables_HPP

class     OPA_Variables;

class     DLL_Handle;
class     Error;
#include  <sOPA_Variables.hpp>
#include  <sSOS_Variables.hpp>
#pragma pack(8)

class  OPA_Variables :public SOS_Variables
{

public     :
public     : virtual opa7ImpExp                  void *CreateProcessVariable (ProcessVariableNames pv_name );
public     :         opa7ImpExp                                          OPA_Variables (ProcessVariables *proc_variables );
public     : virtual opa7ImpExp                  void ReleaseProcessVariable (ProcessVariableNames pv_name );
public     : virtual opa7ImpExp                                          ~OPA_Variables ( );
};

#pragma pack()
#endif
