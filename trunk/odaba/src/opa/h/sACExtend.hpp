/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACExtend

\brief    


\date     $Date: 2006/08/26 13:34:28,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACExtend_HPP
#define   ACExtend_HPP

class     ACExtend;

#include  <sDLL.h>
class     ACExtend;
#include  <sDLL.h>
class     ACNode;
#include  <sDLL.h>
class     ACTopNode;
class     ACExtend;
class     ACNode;
class     ACRelationship;
class     DBExtend;
class     DBStructDef;
class     LACObject;
class     binti;
class     bnode;
class     inti;
class     isel;
class     kcb;
class     node;
#include  <cPIACC.h>
#include  <sACTopNode.hpp>
#include  <sEB_Number.hpp>
#include  <sNodeStack.hpp>
#include  <sRessourceLock.hpp>
#include  <sTypeKey.hpp>
#include  <srefTable.hpp>
#pragma pack(8)

class  ACExtend :public TypeKey
{
protected  :         char                                        *extend_path;                                               // 
protected  :         PIACC                                        accmode;                                                   // 
protected  :         ACNode                                      *extend_node;                                               // 
protected  :         DLL(ACExtend)                               *base_extend;                                               // 
protected  :         DLL(ACExtend)                               *deri_extend;                                               // 
protected  :         ACExtend                                    *root_extend;                                               // 
protected  :         EB_Number                                    int_extref;                                                // 
protected  :         DLL(ACNode)                                 *topnode_list;                                              // 
protected  :         LACObject                                   *object_ref;                                                // 
protected  :         RessourceLock                                extent_lock;                                               // 
protected  :         ACExtend                                    *high_extent;                                               // 
protected  :         ACRelationship                              *acrel_node;                                                // 
protected  :         NodeStack                                    node_cache;                                                // 

public     :
                     PIACC                                        get_accmode() { return(accmode); }
                     ACNode                                      *get_extend_node() { return(extend_node); }
                     DLL(ACExtend)                               *get_base_extend() { return(base_extend); }
                     DLL(ACExtend)                               *get_deri_extend() { return(deri_extend); }
                     ACExtend                                    *get_root_extend() { return(root_extend); }
                     EB_Number                                   &get_int_extref() { return(int_extref); }
                     DLL(ACNode)                                 *get_topnode_list() { return(topnode_list); }
                     LACObject                                   *get_object_ref() { return(object_ref); }
                     RessourceLock                               &get_extent_lock() { return(extent_lock); }
                     ACExtend                                    *get_high_extent() { return(high_extent); }
                     ACRelationship                              *get_acrel_node() { return(acrel_node); }
                     NodeStack                                   &get_node_cache() { return(node_cache); }
public     :                                             ACExtend (LACObject *lobhandle, DBExtend *dbextdef, ACExtend *ac_baseext, PIACC accopt, logical extadd=YES );
public     :                                             ACExtend (bnode *base_node, char *extname );
public     :                                             ACExtend (LACObject *lobhandle, char *extnames );
public     :                                             ACExtend (char *extent_path, PIACC accopt, ACRelationship *acrelptr );
public     :                                        logical Add (binti *bintiptr, logical kchkopt=YES, logical read_opt=YES, logical global_add=NO );
public     :                                        logical AddGenericRef (char *fldname, binti *bintiptr );
public     :                                        logical AddGlobal (binti *bintiptr, logical read_opt=YES );
public     :                                        logical AddTopNode (ACNode *acnodeptr );
public     :                                        logical Check ( );
public     :                                        logical CheckAdd (binti *bintiptr );
public     :                                        logical CheckDelete (binti *bintiptr );
public     :                                        logical CheckDisjunct (binti *bintiptr, ACExtend *acextent );
public     :                                        logical CheckIntersect (binti *bintiptr );
public     :                                        logical CheckModify (binti *bintiptr );
public     :                                        logical CheckUnion (binti *bintiptr );
public     :                                        logical Close ( );
public     :                                        logical CloseExtentNode (logical del_opt );
public     :                                        logical CloseTopNodes ( );
public     :                                        inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     :                                        logical DelGenericRef (char *fldname, binti *bintiptr );
public     :                                        logical Delete (binti *bintiptr, logical kchkopt=YES, logical del_dep=YES, logical switch_opt=NO, logical del_inst=NO );
public     :                                        logical DeleteGlobal (EB_Number entnr );
public     :                                        logical DeleteIndex (binti *bintiptr, EB_Number entnr );
public     :                                        logical Get (binti *bintiptr, logical read_opt=YES );
public     :                                        EB_Number GetBaseInstID ( );
public     :                                        int32 GetCount ( );
public     :                                        char *GetExtendName ( );
public     :                                        DBExtend *GetExtentDef ( );
public     :                                        bnode *GetExtentNode ( );
public     :                                        EB_Number GetGlobalID (binti *bintiptr );
public     :                                        EB_Number GetID (binti *bintiptr, logical pif_opt=NO );
public     :                                        EB_Number GetID (int32 lindx0, logical pif_opt=NO );
public     :                                        binti *GetInstance ( );
public     : virtual                                int16 GetMainBase ( );
public     :                                        ACExtend *GetRootExtent ( );
public     :                                        logical GetRootLock (logical global_add=NO );
public     :                                        logical HasNodeChanged (node *nodeptr );
public     :                                        logical ILockObject ( );
public     :                                        logical ILockRoot ( );
public     :                                        logical IUnlockObject (logical locked );
public     :                                        logical IUnlockRoot (logical root_locked );
public     :                                        logical IdentityAdd (binti *bintiptr, char *keyname, logical kchkopt=YES, logical global_add=NO );
public     :                                        logical InitExtendRef (logical extadd=YES );
public     :                                        logical IsLocal ( );
public     :                                        logical IsRoot ( );
public     :                                        logical IsRootLocked ( );
public     :                                        logical IsTemporary ( );
public     :                                        logical LockRoot (logical global_add=NO );
public     :                                        logical NotCreated ( );
public     :                                        logical Open (LACObject *lobhandle, DBExtend *dbextdef, ACExtend *ac_baseext, PIACC accopt, logical extadd=YES );
public     :                                        logical PositionTop (logical chk_opt=NO );
public     :                                        EB_Number Provide (binti *bintiptr, logical read_opt=YES, logical global_add=NO );
public     :                                        logical Refresh ( );
public     :                                        void ReleaseCache ( );
public     :                                        logical ReleaseNode (node *nodeptr );
public     :                                        logical RemoveTopNode (ACNode *acnodeptr );
public     :                                        node *ReserveNode (PIACC accopt );
public     :                                        logical Save (binti *bintiptr );
public     :                                        logical Save ( );
public     :                                        logical SaveReference ( );
public     :                                        char SetAutoIdent (binti *bintiptr, kcb *kcbptr, int attrtype );
public     :                                        logical SetType (char *strnames );
public     :                                        void SetVersion (uint16 version_nr=CUR_VERSION );
public     :                                        logical SetupExtentRef ( );
public     :                                        void SetupRootExt ( );
public     :                                        logical UnlockRoot (logical extlock, logical global_add=NO );
public     :                                        logical Update (binti *bintiptr );
public     :                                        logical Upgrade (ACExtend *ac_baseext, PIACC accopt );
public     :                                        logical Upgrade (ACExtend *ac_baseext );
public     : virtual                                     ~ACExtend ( );
};

#pragma pack()
#endif
