/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_ImpClass

\brief    


\date     $Date: 2006/06/03 20:12:01,15 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_ImpClass_HPP
#define   pc_ODC_ImpClass_HPP

class     pc_ODC_ImpClass;

class     PropertyHandle;
#include  <cClassModLevel.h>
#include  <cCompileStates.h>
#include  <spc_ODC_compile_object_base.hpp>
class  pc_ODC_ImpClass :public pc_ODC_compile_object_base
{

public     :
public     :                                        logical DeleteExternalResources ( );
public     :                                        logical ExpressionsOnly ( );
public     :                                        char *GetCompileCommand (NString &nstring );
public     :                                        logical HasActions ( );
public     :                                        logical HasProperty (char *propnames );
public     :                                        logical IsExprClass ( );
public     :                                        logical IsIFClass ( );
public     :                                        logical IsIFClass_Pref (char *if_imp_praefix );
public     :                                        logical PC_ClassAttr_Setup (PropertyHandle *attr_ph, PropertyHandle *srce_member );
public     :                                        logical PC_Class_Setup (PropertyHandle *str_ph );
public     :                                        logical SetupReferences ( );
public     :                                        logical SetupReferences (PropertyHandle *member_ph, logical base_opt=NO );
public     :                                             pc_ODC_ImpClass (PropertyHandle *prophdl );
};

#endif
