/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    SOS_Variables

\brief    SOS-Process variables


\date     $Date: 2006/03/12 19:20:16,82 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SOS_Variables_HPP
#define   SOS_Variables_HPP

class     SOS_Variables;

class     Error;
class     dfs;
class     svel;
class     trcc;
#include  <cProcessVariableNames.h>
#include  <sANY_Variables.hpp>
#include  <sProcessVariables.hpp>
#include  <sSOS_Variables.hpp>
#pragma pack(8)

class  SOS_Variables :public ANY_Variables
{

public     :
public     : virtual SOS7ImpExp                  void *CreateProcessVariable (ProcessVariableNames pv_name );
public     : virtual SOS7ImpExp                  void ReleaseProcessVariable (ProcessVariableNames pv_name );
public     :         SOS7ImpExp                                          SOS_Variables (ProcessVariables *proc_variables );
public     : virtual SOS7ImpExp                                          ~SOS_Variables ( );
};

#pragma pack()
#endif
