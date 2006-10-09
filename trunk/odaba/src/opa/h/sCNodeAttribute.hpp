/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    CNodeAttribute

\brief    


\date     $Date: 2006/08/30 17:27:10,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CNodeAttribute_HPP
#define   CNodeAttribute_HPP

class     CNodeAttribute;

class     CTX_Base;
class     DBFieldDef;
class     node;
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <sCNode.hpp>
#include  <sCNodeAttribute.hpp>
class  CNodeAttribute :public CNode
{

public     :
public     :                                             CNodeAttribute (node *nodeptr, NodeTypes nodtype, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 intoff, PIACC accopt );
public     :                                             CNodeAttribute (CNodeAttribute &cnattr_ref );
public     : virtual                                PIACC ChangeMode (PIACC newmode, char chkopt=AUTO );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                                logical CheckModify ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                void *Get (int32 lindx0, logical chknode=YES );
public     : virtual                                int32 GetCount (logical chknode=YES );
public     : virtual                                EB_Number GetID (int32 lindx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                int16 GetInstModCount ( );
public     : virtual                                char *GetKey (int32 lindx0, logical chknode=YES );
public     : virtual                                int16 GetRefModCount ( );
public     : virtual          OPAImpExp             logical IsAutoPosition ( );
public     : virtual          OPAImpExp             logical IsWrite ( );
public     : virtual                                void *Modify (logical chknode=YES );
public     : virtual                                void *Provide (int32 lindx0, logical global_add=NO );
public     : virtual                                void *Provide (char *skey, logical global_add=NO );
public     : virtual                                void *Provide (void *datarea, logical global_add=NO );
public     : virtual                                logical Switch (int32 indx0 );
public     :                                             ~CNodeAttribute ( );
};

#endif
