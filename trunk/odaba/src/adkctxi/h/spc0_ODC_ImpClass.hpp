/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc0_ODC_ImpClass



\date     $Date: 2006/03/12 19:35:28,23 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_ODC_ImpClass_HPP
#define   pc0_ODC_ImpClass_HPP

class     pc0_ODC_ImpClass;

#include  <sPropertyHandle.hpp>
class  pc0_ODC_ImpClass :public PropertyHandle
{

public     :
public     :                                     logical IsIFClass ( );
public     :                                     logical IsIFClass_Pref (char *if_imp_praefix );
public     :                                     void ResCompileState ( );
public     :                                                             pc0_ODC_ImpClass (PropertyHandle *prophdl );
};

#endif
