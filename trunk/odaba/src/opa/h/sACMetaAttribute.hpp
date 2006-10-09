/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACMetaAttribute

\brief    


\date     $Date: 2006/08/25 16:46:06,59 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACMetaAttribute_HPP
#define   ACMetaAttribute_HPP

class     ACMetaAttribute;

class     ACExtend;
class     CTX_Base;
class     DBFieldDef;
class     node;
#include  <cADT_Types.h>
#include  <cMAT_Types.h>
#include  <cNodeTypes.h>
#include  <cPIACC.h>
#include  <sACMetaAttribute.hpp>
#include  <sEB_Number.hpp>
#include  <sbnode.hpp>
#pragma pack(8)

class  ACMetaAttribute :public bnode
{

public     :
public     :                                             ACMetaAttribute (node *nodeptr, DBFieldDef *dbfield_ptr );
public     :                                             ACMetaAttribute (ACMetaAttribute &mattrnode_ref );
public     : virtual                                logical CheckModify ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                node *CreateSubNode (node *nodeptr, NodeTypes nodtype, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     : virtual                                void *Get (int32 indx0, logical chknode=YES );
public     : virtual                                int32 GetCount (logical chknode=YES );
public     : virtual                                EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                int16 GetInstModCount ( );
public     : virtual          OPAImpExp             char *GetString ( );
public     : virtual                                logical IsAutoPosition ( );
public     : virtual                                logical IsPositioned ( );
public     : virtual                                logical IsSelected ( );
public     : virtual                                logical IsWrite ( );
public     : virtual                                void *Modify (logical chknode=YES );
public     :                                        void *Provide (int32 lindx0, logical global_add=NO );
public     : virtual          OPAImpExp             logical Store ( );
public     : virtual                                logical Switch (int32 indx0 );
public     : virtual                                     ~ACMetaAttribute ( );
};

#pragma pack()
#endif
