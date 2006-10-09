/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACBaseStruct

\brief    


\date     $Date: 2006/03/12 19:11:39,59 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACBaseStruct_HPP
#define   ACBaseStruct_HPP

class     ACBaseStruct;

class     CTX_Base;
class     DBFieldDef;
class     node;
#include  <cPIACC.h>
#include  <sACAttribute.hpp>
#pragma pack(8)

class  ACBaseStruct :public ACAttribute
{

public     :
public     :                                                             ACBaseStruct (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt );
public     : virtual                                                     ~ACBaseStruct ( );
};

#pragma pack()
#endif
