/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACShareBase

\brief    


\date     $Date: 2006/03/12 19:12:13,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACShareBase_HPP
#define   ACShareBase_HPP

class     ACShareBase;

class     ACExtend;
class     ACProperty;
class     ACStructure;
class     CTX_Base;
class     DBFieldDef;
class     kcb;
class     node;
#include  <cPIACC.h>
#include  <sACRelationship.hpp>
#include  <sACShareBase.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  ACShareBase :public ACRelationship
{
protected  :         logical                                      autoid_key ATTR_ALIGN(4);                                  //

public     :
                     logical                                      get_autoid_key() { return(autoid_key); }
public     :                                                             ACShareBase (node *nodeptr, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, PIACC accopt );
public     :                                                             ACShareBase (DBFieldDef *dbfield_ptr, void *instptr );
public     :                                                             ACShareBase ( );
public     :                                                             ACShareBase (ACShareBase &basenode_ref );
public     : virtual                             void *Add (int32 lindx0, logical global_add=NO );
public     : virtual                             logical Close ( );
public     : virtual                             node *CreateCopyNode ( );
public     :                                     EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                     EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     :                                     logical HasBaseAutoIdKey ( );
public     :                                     logical Locate (EB_Number entnr, logical read_opt=YES );
public     :                                     char SetAutoIdent (kcb *kcbptr, int attrtype );
public     : virtual                             logical SetupNode (logical create_ref, logical retain_mod );
public     : virtual                                                     ~ACShareBase ( );
};

#pragma pack()
#endif
