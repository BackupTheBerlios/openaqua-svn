/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACOPWhere



\date     $Date: 2006/03/12 19:11:51,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOPWhere_HPP
#define   ACOPWhere_HPP

class     ACOPWhere;

class     ACObject;
class     BNFData;
class     DBStructDef;
class     OPExpressionDecl;
class     OperEnvironment;
class     node;
#include  <cPIACC.h>
#include  <sACOPJoin.hpp>
#include  <sACOperation.hpp>
#pragma pack(8)

class  ACOPWhere :public ACOperation
{
protected  :         OPExpressionDecl                            *condition ATTR_ALIGN(4);                                   //

public     :
                     OPExpressionDecl                            *get_condition() { return(condition); }
public     :                                                             ACOPWhere (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                                             ACOPWhere (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPWhere (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPWhere (ACOPJoin &joinnode_ref );
public     :                                     logical CreateCondition (char *strnames_w=NULL );
public     : virtual                             node *CreateCopyNode ( );
public     :                                     logical InitStructure (char *strnames_w=NULL );
public     : virtual                                                     ~ACOPWhere ( );
};

#pragma pack()
#endif
