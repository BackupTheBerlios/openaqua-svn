/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACOPJoin



\date     $Date: 2006/03/12 19:11:49,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOPJoin_HPP
#define   ACOPJoin_HPP

class     ACOPJoin;

class     ACObject;
class     BNFData;
class     DBFieldList;
class     DBStructDef;
class     OperEnvironment;
class     node;
#include  <cPIACC.h>
#include  <sACOPJoin.hpp>
#include  <sACOperation.hpp>
#pragma pack(8)

class  ACOPJoin :public ACOperation
{

public     :
public     :                                                             ACOPJoin (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                                             ACOPJoin (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPJoin (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPJoin (ACOPJoin &joinnode_ref );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual                             DBFieldList *CreateFields ( );
public     :                                     logical InitStructure (char *strnames_w=NULL );
public     : virtual                                                     ~ACOPJoin ( );
};

#pragma pack()
#endif
