/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACOPSelect

\brief    


\date     $Date: 2006/04/16 17:11:38,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOPSelect_HPP
#define   ACOPSelect_HPP

class     ACOPSelect;

class     ACObject;
class     BNFData;
class     DBStructDef;
class     OperEnvironment;
class     node;
#include  <cPIACC.h>
#include  <sACOPSelect.hpp>
#include  <sACOperation.hpp>
#pragma pack(8)

class  ACOPSelect :public ACOperation
{

public     :
public     :                                                             ACOPSelect (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                                             ACOPSelect (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPSelect (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPSelect (ACOPSelect &selnode_ref );
public     : virtual                             node *CreateCopyNode ( );
public     :                                     logical InitStructure (char *strnames_w=NULL );
public     : virtual                                                     ~ACOPSelect ( );
};

#pragma pack()
#endif
