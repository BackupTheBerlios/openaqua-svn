/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_FunctGroup

\brief    


\date     $Date: 2006/03/13 21:30:31,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_FunctGroup_HPP
#define   ODC_FunctGroup_HPP

class     ODC_FunctGroup;

#ifndef   P_ODC_ImpClass_HPP
#define   P_ODC_ImpClass_HPP
#include  <sPI.hpp>
class       ODC_ImpClass;
PI_dcl     (ODC_ImpClass)
#endif
#ifndef   P_ODC_PFunction_HPP
#define   P_ODC_PFunction_HPP
#include  <sPI.hpp>
class       ODC_PFunction;
PI_dcl     (ODC_PFunction)
#endif
class     ODC_ImpClass;
class     ODC_PFunction;
#include  <sSDB_Resource.hpp>
class  ODC_FunctGroup :public SDB_Resource
{
protected  :         PI(ODC_ImpClass)                             imp_class;                                                 
protected  :         PI(ODC_PFunction)                            functions;                                                 

public     :
                     PI(ODC_ImpClass)                            &get_imp_class() { return(imp_class); }
                     PI(ODC_PFunction)                           &get_functions() { return(functions); }
};

#endif
