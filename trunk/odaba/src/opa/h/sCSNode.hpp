/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    CSNode

\brief    


\date     $Date: 2006/07/18 16:32:43,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSNode_HPP
#define   CSNode_HPP

class     CSNode;

#define  SYS_NSID                                  0
class     ACObject;
class     DBExtend;
class     DBStructDef;
class     ENUM_ValueList;
class     inti;
class     node;
#include  <cPIACC.h>
#include  <sACNode.hpp>
#include  <sCSNode.hpp>
#include  <sTypeKey.hpp>
#include  <sbnode.hpp>
#pragma pack(8)

class  CSNode :public bnode
{
protected  :         ENUM_ValueList                              *value_list;                                                // 
protected  :         char                                         local_order;                                               // 

public     :
                     ENUM_ValueList                              *get_value_list() { return(value_list); }
                     char                                         get_local_order() { return(local_order); }
public     :                                             CSNode (ACObject *obhandle, char *scoped_name );
public     :                                             CSNode (CSNode &csnode );
public     :                                             CSNode (node *parent );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                                logical Close ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual          OPAImpExp             inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     : virtual          OPAImpExp             char *ExtractKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual          OPAImpExp             char *ExtractKey (char *keyptr, kcb *kcbptr, void *instptr );
public     : virtual          OPAImpExp             char *ExtractSortKey (char *keyptr, void *instptr, logical chknode=YES );
public     : virtual          OPAImpExp             char *FirstKey (logical chknode=YES );
public     : virtual          OPAImpExp             void *Get (int32 indx0, logical chknode=YES );
public     : virtual          OPAImpExp             void *Get (char *skey, logical chknode=YES );
public     : virtual          OPAImpExp             int32 GetCount (logical chknode=YES );
public     : virtual          OPAImpExp             EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     : virtual          OPAImpExp             EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual          OPAImpExp             char *GetKey (int32 lindx0, logical chknode=YES );
public     : virtual          OPAImpExp             int16 GetKeyLength ( );
public     : virtual          OPAImpExp             smcb *GetKeySMCB (char *key_name_w=NULL );
public     : virtual          OPAImpExp             node **GetNodePtr (char *prop_path, logical *is_transient=NULL, logical supress_struct_error=NO );
public     : virtual          OPAImpExp             int16 GetSortKeyLength (logical chknode=YES );
public     : virtual          OPAImpExp             smcb *GetSortKeySMCB ( );
public     :                  OPAImpExp             char *GetString ( );
public     : virtual          OPAImpExp             logical IsPositioned ( );
public     : virtual                                logical IsSelected ( );
public     : virtual          OPAImpExp             char *KeyToString (char *key_string, char *key_val, char *key_name_w=NULL );
public     : virtual          OPAImpExp             logical Locate (EB_Number entnr, logical read_opt=YES );
public     : virtual          OPAImpExp             logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     : virtual          OPAImpExp             char *NextKey (char *skey, int16 switch_level=0 );
public     : virtual                                void ResetInstance ( );
public     : virtual          OPAImpExp             logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual                                logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                        void SetOrderKey ( );
public     : virtual          OPAImpExp             char *StringToKey (char *key_string, char *key_name_w=NULL );
public     :                                             ~CSNode ( );
};

#pragma pack()
#endif
