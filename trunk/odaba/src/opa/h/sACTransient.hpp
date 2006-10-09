/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACTransient

\brief    


\date     $Date: 2006/03/12 19:12:16,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACTransient_HPP
#define   ACTransient_HPP

class     ACTransient;

class     ACObject;
class     DBStructDef;
class     inti;
class     node;
#include  <sACNode.hpp>
#pragma pack(8)

class  ACTransient :public ACNode
{

public     :
public     :                                                             ACTransient (ACObject *obhandle, DBStructDef *dbstrdef, char *key_name_w=NULL );
public     : virtual                             inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     : virtual                                                     ~ACTransient ( );
};

#pragma pack()
#endif
