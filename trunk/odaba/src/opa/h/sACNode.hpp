/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACNode

\brief    


\date     $Date: 2006/04/09 12:11:38,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACNode_HPP
#define   ACNode_HPP

class     ACNode;

#include  <sDLL.h>
class     ACNode;
#include  <sDPA.h>
class     inti;
#ifndef   DLL_dbf_HPP
#define   DLL_dbf_HPP
#include  <sdbf.hpp>
#include  <sDLL.h>
#endif
class     ACObject;
class     CTX_Base;
class     DBFieldDef;
class     DBStructDef;
class     PropertyHandle;
class     dbf;
class     inti;
class     isel;
class     kcb;
#include  <cPIACC.h>
#include  <sACNode.hpp>
#include  <sEB_Number.hpp>
#include  <sLNode.hpp>
#include  <snode.hpp>
#pragma pack(8)

class  ACNode :public LNode
{
protected  :         uint16                                       version ATTR_ALIGN(4);                                     // 

public     :
                     uint16                                       get_version() { return(version); }
public     :         OPAImpExp                                           ACNode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     :         OPAImpExp                                           ACNode ( );
public     :         OPAImpExp                                           ACNode (ACNode &acnode_ref );
public     : virtual OPAImpExp                   logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual OPAImpExp                   node *CreateCopyNode ( );
public     :                                     logical Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     :                                     logical PrevVersion ( );
public     : virtual OPAImpExp                   logical SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual OPAImpExp                   logical SetupNode (logical create_ref, logical retain_mod );
public     :                                     logical UpdateCurIndex (logical setup, logical overwrite=NO );
public     : virtual OPAImpExp                                           ~ACNode ( );
};

#pragma pack()
#endif
