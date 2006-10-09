/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACRelationship

\brief    


\date     $Date: 2006/08/30 18:15:19,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACRelationship_HPP
#define   ACRelationship_HPP

class     ACRelationship;

#include  <sDLL.h>
class     ACRelationship;
#include  <sDLL.h>
class     PropertyHandle;
#include  <sGSRT.h>
class     PropertyHandle;
class     ACExtend;
class     ACProperty;
class     ACStructure;
class     CTX_Base;
class     DBFieldDef;
class     binti;
class     inti;
class     isel;
class     node;
#include  <cPIACC.h>
#include  <sACReference.hpp>
#include  <sACRelationship.hpp>
#include  <sACSubNode.hpp>
#include  <sCheckOptions.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  ACRelationship :public ACReference
{
protected  :         ACExtend                                    *system_node;                                               // 
protected  :         DLL(PropertyHandle)                         *derived_nodes;                                             // 

public     :
                     ACExtend                                    *get_system_node() { return(system_node); }
                     DLL(PropertyHandle)                         *get_derived_nodes() { return(derived_nodes); }
public     :                                             ACRelationship (node *nodeptr, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt );
public     :                                             ACRelationship (ACExtend *sysnode, DBFieldDef *dbfield_ptr, PIACC accopt );
public     :                                             ACRelationship ( );
public     :                                             ACRelationship (ACRelationship &acrelref );
public     : virtual                                void *Add (int32 lindx0, logical global_add=NO );
public     : virtual                                logical AddGenericRef (char *fldname );
public     : virtual                                void *AddInstance (binti *bintiptr, int32 lindx0 );
public     :                                        logical AddInvDeriGenRef (char *fldname );
public     :                                        logical AddInversGenRef (char *fldname );
public     :                                        logical AddInverse (logical global_add=NO );
public     : virtual                                logical AddReference (node *srcenode, int32 lindx0 );
public     : virtual                                PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                        logical CheckDBCollection (NString &nresult, CheckOptions check_opts );
public     :                                        logical CheckDBInverseRefs (NString &nresult, logical repair );
public     :                                        logical CheckInverse (node *srce_node );
public     :                                        logical CheckOrder (logical root_opt );
public     : virtual                                logical Close ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                logical DelGenericRef (char *fldname );
public     :                                        logical DelInvDeriGenRef (char *fldname );
public     :                                        logical DelInversGenRef (char *fldname );
public     : virtual                                logical Delete (int32 lindx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     :                                        logical DeleteDepend (logical del_dep=YES );
public     :                                        logical DeleteDerived (logical del_opt );
public     : virtual          OPAImpExp             logical DeleteIndex (logical gen_events );
public     :                                        logical DeleteInvDeri (char *extnames );
public     :                                        logical DeleteInverse (char *extnames, binti *bintiptr, logical is_root, logical del_dep=YES );
public     :                                        logical GenInvDeriRef ( );
public     : virtual                                node *GetExtentNode ( );
public     : virtual                                EB_Number GetGlobalID ( );
public     :                                        ACRelationship *GetInverse (logical optimize, binti *bintiptr_w=NULL );
public     :                                        ACRelationship *GetInverseI ( );
public     : virtual                                int16 GetMainBase ( );
public     : virtual                                ACExtend *GetSystemNode ( );
public     : virtual                                logical InitReference ( );
public     :                                        logical IsBaseCollection ( );
public     :                                        void Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt );
public     : virtual                                logical ProvideExtendNode ( );
public     :                                        void *ProvideInstance (int32 lindx0, logical global_add=NO );
public     : virtual                                logical ProvideInti (EB_Number entnr );
public     : virtual                                logical ProvideInti (int16 sid );
public     :                                        void ResetIntern (int32 indx0, logical exist );
public     : virtual                                logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                        char SetAutoIdent ( );
public     :                                        logical UpdateInvDeri ( );
public     :                                        logical UpdateInverse (logical keymod );
public     : virtual                                     ~ACRelationship ( );
};

#pragma pack()
#endif
