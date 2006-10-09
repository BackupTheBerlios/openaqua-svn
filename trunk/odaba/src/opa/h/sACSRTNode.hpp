/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACSRTNode

\brief    


\date     $Date: 2006/04/03 14:19:54,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACSRTNode_HPP
#define   ACSRTNode_HPP

class     ACSRTNode;

class     ACObject;
class     CTX_Base;
class     DBFieldDef;
class     DBStructDef;
class     inti;
class     ksrt;
class     node;
#include  <cDB_Event.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sEB_Number.hpp>
#include  <sbnode.hpp>
class  ACSRTNode :public bnode
{
protected  :         ksrt                                        *list ATTR_ALIGN(4);                                        // 

public     :
public     :                                                             ACSRTNode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr );
public     :                                     void *Add (int32 lindx0, logical global_add=NO );
public     :                                     void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     :                                     logical Cancel (logical chknode=YES );
public     :                                     logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                     logical Close ( );
public     :                                     inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     :                                     logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     :                                     logical Delete (char *skey, logical chknode=YES );
public     :                                     void *Duplicate (char *keyptr, PIREPL db_replace=REPL_none, logical chknode=YES );
public     :                                     char *FirstKey (logical chknode=YES );
public     :                                     void *Get (int32 indx0, logical chknode=YES );
public     :                                     void *Get (char *skey, logical chknode=YES );
public     :                                     void *Get ( );
public     :                                     int32 GetCount (logical chknode=YES );
public     :                                     EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                     EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     :                                     void *GetInitInstance (logical set_init=YES );
public     :                                     int16 GetInstModCount ( );
public     :                                     char *GetKey (int32 lindx0, logical chknode=YES );
public     :                                     int16 GetRefModCount ( );
public     :                                     logical Locate (EB_Number entnr, logical read_opt=YES );
public     :                                     logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                     void *Move (node *srcenode, PIREPL db_replace=REPL_none, char *w_newkey=NULL, logical chknode=YES );
public     :                                     logical MoveDown ( );
public     :                                     logical MoveUp ( );
public     :                                     char *NextKey (char *skey, int16 switch_level=0 );
public     :                                     logical Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     : virtual                             int32 Position (int32 count, logical chknode=YES );
public     :                                     void *Provide (char *skey, logical global_add=NO );
public     :                                     void *Provide (int32 lindx0, logical global_add=NO );
public     :                                     void *Provide (void *datarea, logical global_add=NO );
public     :                                     logical Rename (char *identkey, logical chknode=YES );
public     :                                     logical Reset ( );
public     :                                     logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                     logical Select (node *nodeptr, char *expression, int32 min_inst=AUTO );
public     :                                     logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                     void *SetupInstance (DB_Event intevent );
public     :                                                             ~ACSRTNode ( );
};

#endif
