/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACOPGroupBy

\brief    


\date     $Date: 2006/03/12 19:11:48,67 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOPGroupBy_HPP
#define   ACOPGroupBy_HPP

class     ACOPGroupBy;

class     ACOPGroupBy;
class     ACObject;
class     BNFData;
class     DBFieldList;
class     DBStructDef;
class     OPExpressionDecl;
class     OperEnvironment;
class     node;
#include  <cPIACC.h>
#include  <sACOperation.hpp>
#pragma pack(8)

class  ACOPGroupBy :public ACOperation
{
protected  :         OPExpressionDecl                            *grouping_op ATTR_ALIGN(4);                                 //

public     :
public     :                                                             ACOPGroupBy (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                                             ACOPGroupBy (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPGroupBy (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPGroupBy (ACOPGroupBy &groupnode_ref );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual                             DBFieldList *CreateFields ( );
public     :                                     logical InitStructure (char *strnames_w=NULL );
public     : virtual                                                     ~ACOPGroupBy ( );
};

#pragma pack()
#endif
