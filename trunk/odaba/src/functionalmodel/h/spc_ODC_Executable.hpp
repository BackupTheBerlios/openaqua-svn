/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_Executable

\brief    


\date     $Date: 2006/06/04 10:51:11,71 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_Executable_HPP
#define   pc_ODC_Executable_HPP

class     pc_ODC_Executable;

class     PropertyHandle;
#include  <cClassModLevel.h>
#include  <cCompileStates.h>
#include  <sNString.hpp>
#include  <spc_ODC_compile_object_base.hpp>
class  pc_ODC_Executable :public pc_ODC_compile_object_base
{

public     :
public     :                                        char *GetCompileCommand (NString &nstring );
public     :                                        char *GetLinkCommand (NString &nstring );
public     :                                             pc_ODC_Executable (PropertyHandle *prophdl );
};

#endif
