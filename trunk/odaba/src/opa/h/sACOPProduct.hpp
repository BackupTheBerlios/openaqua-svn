/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACOPProduct



\date     $Date: 2006/03/12 19:11:50,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOPProduct_HPP
#define   ACOPProduct_HPP

class     ACOPProduct;

class     ACObject;
class     BNFData;
class     DBExtend;
class     DBStructDef;
class     OperEnvironment;
class     PropertyHandle;
class     inti;
class     kcb;
class     node;
#include  <cPIACC.h>
#include  <sACOperation.hpp>
#pragma pack(8)

class  ACOPProduct :public ACOperation
{

public     :
public     :                                                             ACOPProduct (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                                             ACOPProduct (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPProduct (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPProduct (ACOPProduct &prodnode_ref );
public     : virtual                             node *CreateCopyNode ( );
public     :                                     logical InitStructure (char *strnames_w=NULL );
public     : virtual                                                     ~ACOPProduct ( );
};

#pragma pack()
#endif
