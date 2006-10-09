/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACOPOutput

\brief    


\date     $Date: 2006/03/12 19:11:49,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOPOutput_HPP
#define   ACOPOutput_HPP

class     ACOPOutput;

class     ACObject;
class     BNFData;
class     DBQOutput;
class     DBStructDef;
class     OperEnvironment;
class     node;
#include  <cPIACC.h>
#include  <sACOPOutput.hpp>
#include  <sACOperation.hpp>
#pragma pack(8)

class  ACOPOutput :public ACOperation
{
protected  :         DBQOutput                                   *output ATTR_ALIGN(4);                                      //
protected  :         NString                                      nstring;                                                   

public     :
                     DBQOutput                                   *get_output() { return(output); }
                     NString                                     &get_nstring() { return(nstring); }
public     :                                                             ACOPOutput (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                                             ACOPOutput (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPOutput (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                                             ACOPOutput (ACOPOutput &outnode_ref );
public     : virtual                             node *CreateCopyNode ( );
public     :                                     void *Get (int32 indx0, logical chknode=YES );
public     :                                     void *Get (char *skey, logical chknode=YES );
public     :                                     logical InitOutput (ST_OpCodes op_code );
public     :                                                             ~ACOPOutput ( );
};

#pragma pack()
#endif
