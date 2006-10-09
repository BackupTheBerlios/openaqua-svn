/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACTopNode

\brief    


\date     $Date: 2006/08/30 13:08:39,42 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACTopNode_HPP
#define   ACTopNode_HPP

class     ACTopNode;

class     ACExtend;
class     ACObject;
class     DBFieldDef;
class     DBStructDef;
class     inti;
class     node;
#include  <cPIACC.h>
#include  <sACNode.hpp>
#include  <sACTopNode.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  ACTopNode :public ACNode
{
protected  :         ACExtend                                    *system_node;                                               // 

public     :
                     ACExtend                                    *get_system_node() { return(system_node); }
public     :                                             ACTopNode (ACExtend *sysnode, PIACC accopt, char *w_instptr=NULL );
public     :                                             ACTopNode (ACObject *obhandle, DBFieldDef *dbfield_def );
public     :                                             ACTopNode (ACTopNode &topnode_ref );
public     : virtual                                void *Add (int32 lindx0, logical global_add=NO );
public     : virtual                                logical AddGenericRef (char *fldname );
public     : virtual                                PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                                logical Close ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                inti *CreateInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical init_nodes=YES );
public     : virtual                                logical DelGenericRef (char *fldname );
public     : virtual                                logical Delete (int32 lindx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual                                logical DeleteIndex (logical gen_events );
public     : virtual                                logical DeleteIndexEntry ( );
public     :                                        int32 GetCount (logical chknode=YES );
public     : virtual                                node *GetExtentNode ( );
public     : virtual                                EB_Number GetGlobalID ( );
public     :                                        EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                        EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual                                int16 GetMainBase ( );
public     : virtual                                ACExtend *GetSystemNode ( );
public     :                                        logical InitNode ( );
public     :                                        logical IsTempExtent ( );
public     :                                        logical Open (PIACC accopt, char *w_instptr=NULL );
public     : virtual                                logical Refresh ( );
public     : virtual                                logical Release ( );
public     : virtual                                logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual                                     ~ACTopNode ( );
};

#pragma pack()
#endif
