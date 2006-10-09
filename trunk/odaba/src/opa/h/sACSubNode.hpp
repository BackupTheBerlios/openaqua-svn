/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACSubNode

\brief    


\date     $Date: 2006/08/30 18:08:40,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACSubNode_HPP
#define   ACSubNode_HPP

class     ACSubNode;

#include  <sDPA.h>
class     isel;
class     ACObject;
class     ACStructure;
class     CTX_Base;
class     DBFieldDef;
class     StructAccess;
class     node;
#include  <cPIACC.h>
#include  <sACNode.hpp>
#include  <sACProperty.hpp>
#include  <sACSubNode.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  ACSubNode :public ACProperty
{

public     :
public     :                                             ACSubNode (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt );
public     :                                             ACSubNode (ACSubNode &subnoderef );
public     :                                             ACSubNode ( );
public     : virtual                                PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                                logical Close ( );
public     : virtual                                node *CreateCopyNode ( );
public     :                                        void Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt );
public     : virtual                                     ~ACSubNode ( );
};

#pragma pack()
#endif
