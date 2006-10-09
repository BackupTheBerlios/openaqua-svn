/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc0_ODC_PFunction



\date     $Date: 2006/03/12 19:35:28,50 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_ODC_PFunction_HPP
#define   pc0_ODC_PFunction_HPP

class     pc0_ODC_PFunction;

#include  <sPropertyHandle.hpp>
class  pc0_ODC_PFunction :public PropertyHandle
{

public     :
public     :                                     logical IsIFFunction (char *if_imp_praefix );
public     :                                                             pc0_ODC_PFunction (PropertyHandle *prophdl );
};

#endif
