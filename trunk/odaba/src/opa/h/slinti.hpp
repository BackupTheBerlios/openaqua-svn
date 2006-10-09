/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    linti

\brief    


\date     $Date: 2006/03/12 19:14:32,87 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   linti_HPP
#define   linti_HPP

class     linti;

class     DBStructDef;
class     node;
#include  <sbinti.hpp>
class  linti :public binti
{

public     :
public     :                                     logical CreateSubNodes (node *nodeptr, void *instptr );
public     :                                                             linti (node *nodeptr, DBStructDef *strdef, void *instptr );
public     :                                                             ~linti ( );
};

#endif
