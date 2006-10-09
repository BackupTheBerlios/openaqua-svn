/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACTransientReference

\brief    


\date     $Date: 2006/03/12 19:12:17,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACTransientReference_HPP
#define   ACTransientReference_HPP

class     ACTransientReference;

#include  <sDPA.h>
class     inti;
class     CTX_Base;
class     DBFieldDef;
class     DBStructDef;
class     inti;
class     node;
#include  <cPIACC.h>
#include  <sACTransientReference.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#pragma pack(8)

class  ACTransientReference :public bnode
{
protected  :         PropertyHandle                               property_handle ATTR_ALIGN(4);                             //

public     :
                     PropertyHandle                              &get_property_handle() { return(property_handle); }
public     :                                                             ACTransientReference ( );
public     :                                                             ACTransientReference (ACTransientReference &actnode_ref );
public     :                                                             ACTransientReference (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt );
public     :                                                             ACTransientReference (node *nodeptr );
public     : virtual opa7ImpExp                  void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual opa7ImpExp                  logical Cancel (logical chknode=YES );
public     : virtual                             logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                             logical Close ( );
public     :                                     void *CopyData ( );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual                             inti *CreateInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical init_nodes=YES );
public     : virtual opa7ImpExp                  char *FirstKey (logical chknode=YES );
public     : virtual opa7ImpExp                  void *Get (int32 indx0, logical chknode=YES );
public     : virtual opa7ImpExp                  void *Get (char *skey, logical chknode=YES );
public     : virtual                             int32 GetAt (int32 lindx0, int16 direction, logical chknode=YES );
public     : virtual opa7ImpExp                  int32 GetCount (logical chknode=YES );
public     : virtual                             node *GetNode (logical autoini=NO );
public     :                                     node **GetNodePtr ( );
public     :                                     logical Init (void *instptr );
public     : virtual opa7ImpExp                  logical IsPositioned ( );
public     : virtual opa7ImpExp                  logical IsSelected ( );
public     : virtual                             logical IsTransient ( );
public     :                                     logical IsValid ( );
public     : virtual opa7ImpExp                  logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     : virtual opa7ImpExp                  char *NextKey (char *skey, int16 switch_level=0 );
public     : virtual                             logical Open (node *nodeptr, DBFieldDef *dbfield_ptr );
public     : virtual                             logical Open ( );
public     :                                     node *PositionTop_intern ( );
public     : virtual opa7ImpExp                  void *Provide (char *skey, logical global_add=NO );
public     : virtual opa7ImpExp                  void *Provide (int32 lindx0, logical global_add=NO );
public     :                                     logical ResetNode (logical reset_all );
public     : virtual opa7ImpExp                  logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                     logical SaveData ( );
public     : virtual                             logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     : virtual                             logical SetTransientProperty (node *nodptr );
public     : virtual opa7ImpExp                  logical Switch (int32 indx0 );
public     : virtual                             node *ValidateNode (logical crt_opt );
public     : virtual                                                     ~ACTransientReference ( );
};

#pragma pack()
#endif
