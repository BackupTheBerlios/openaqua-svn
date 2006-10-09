/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACProperty

\brief    


\date     $Date: 2006/08/30 18:04:12,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACProperty_HPP
#define   ACProperty_HPP

class     ACProperty;

class     ACObject;
class     CTX_Base;
class     DBFieldDef;
class     DBStructDef;
class     FieldDef;
class     StructAccess;
class     binti;
class     inti;
class     isel;
class     ref;
class     refTable;
class     smcb;
#include  <cPIACC.h>
#include  <cPIADEF.h>
#include  <cPIREPL.h>
#include  <sACNode.hpp>
#include  <sACProperty.hpp>
#include  <sEB_Number.hpp>
#include  <snode.hpp>
#pragma pack(8)

class  ACProperty :public ACNode
{
protected  :         EB_Number                                    nodecln;                                                   // 
protected  :         int32                                        nodeoff;                                                   // 
protected  :         StructAccess                                *struct_access;                                             // 

public     :
                     EB_Number                                   &get_nodecln() { return(nodecln); }
                     int32                                        get_nodeoff() { return(nodeoff); }
                     StructAccess                                *get_struct_access() { return(struct_access); }
public     :                                             ACProperty (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     :                                             ACProperty ( );
public     :                                             ACProperty (ACProperty &acpnoderef );
public     : virtual                                logical CancelNode ( );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                        logical CheckNewID ( );
public     : virtual                                logical Close ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                inti *CreateInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical init_nodes=YES );
public     :                                        logical DeleteReference ( );
public     : virtual                                int32 GetDimension (logical chknode=YES );
public     : virtual                                EB_Number GetGlobalID ( );
public     : virtual                                int16 GetMainBase ( );
public     :                                        logical InitIsel (int16 mbnumber, void *instptr );
public     : virtual                                logical InitReference ( );
public     :                                        logical IsNewReference (logical create_ref );
public     :                                        logical Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     : virtual                                logical ProvideInti (EB_Number entnr );
public     : virtual                                logical ProvideInti (int16 sid );
public     : virtual                                void ResetInstance ( );
public     : virtual                                logical SetupNode (logical create_ref, logical retain_mod );
public     :                                        logical SetupNode_intern (binti *bintiptr, logical create_ref, logical retain_mod );
public     :                                        void set_nodecln (EB_Number clnumber );
public     : virtual                                     ~ACProperty ( );
};

#pragma pack()
#endif
