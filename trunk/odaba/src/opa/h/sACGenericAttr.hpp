/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACGenericAttr

\brief    


\date     $Date: 2006/04/11 11:29:37,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACGenericAttr_HPP
#define   ACGenericAttr_HPP

class     ACGenericAttr;

class     ACProperty;
class     CTX_Base;
class     DBFieldDef;
class     inti;
class     node;
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sACGenericAttr.hpp>
#include  <sACReference.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  ACGenericAttr :public ACReference
{
protected  :         int                                          attr_type ATTR_ALIGN(4);                                   // 
protected  :         int32                                        inst_off;                                                  // 
protected  :         logical                                      no_modify;                                                 // 

public     :
                     int                                         &get_attr_type() { return(attr_type); }
                     int32                                        get_inst_off() { return(inst_off); }
public     :                                                             ACGenericAttr (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt );
public     :                                                             ACGenericAttr (ACGenericAttr &acgnoderef );
public     :                                                             ACGenericAttr ( );
public     : virtual OPAImpExp                   void *Add (int32 lindx0, logical global_add=NO );
public     :                                     logical AddGenAttribute ( );
public     : virtual                             logical CopyReference (inti *srceinti, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     : virtual                             int32 CopySet (node *srcenode, logical check_inverse, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all, logical chknode=YES );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual OPAImpExp                   logical Delete (int32 lindx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     :                                     int GetGenAttrType (char *attrstr );
public     :                                     EB_Number GetID (int32 indx0, logical chknode=YES, logical pif_opt=NO );
public     :                                     EB_Number GetID (char *keyptr, logical chknode=YES, logical pif_opt=NO );
public     : virtual                             logical Initialize (void *instptr, logical set_init=YES );
public     :                                     void *Modify (logical chknode=YES );
public     :                                     logical PrepareGenAttribute ( );
public     :                                     logical ResetGenAttribute ( );
public     : virtual                             logical SetGenAttribute (int attrtype, char *attrstr );
public     : virtual                             logical SetGenAttribute (char *fldnames, int attrtype, char *attrstr );
public     : virtual                             logical SetGenAttribute ( );
public     : virtual                             logical SetGenAttribute (void *instptr );
public     :                                     logical SetGenKey ( );
public     : virtual                             logical SetupNode (logical create_ref, logical retain_mod );
public     : virtual                                                     ~ACGenericAttr ( );
};

#pragma pack()
#endif
