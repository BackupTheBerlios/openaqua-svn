/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    pc_ODC_Main



\date     $Date: 2006/05/09 17:23:03,04 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_Main_HPP
#define   pc_ODC_Main_HPP

class     pc_ODC_Main;

#include  <spc_ODC_compile_object_base.hpp>
class  pc_ODC_Main :public pc_ODC_compile_object_base
{

public     :
public     :                                        char *GetCompileCommand (NString &nstring );
public     :                                             pc_ODC_Main (PropertyHandle *prophdl );
};

#endif
