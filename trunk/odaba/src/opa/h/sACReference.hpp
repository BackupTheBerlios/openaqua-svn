/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACReference

\brief    


\date     $Date: 2006/08/30 18:13:00,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACReference_HPP
#define   ACReference_HPP

class     ACReference;

class     ACNode;
class     ACProperty;
class     ACStructure;
class     CTX_Base;
class     DBFieldDef;
class     StructAccess;
class     node;
#include  <cPIACC.h>
#include  <sACReference.hpp>
#include  <sACSubNode.hpp>
#pragma pack(8)

class  ACReference :public ACSubNode
{
protected  :         logical                                      owning_ref;                                                // 

public     :
                     logical                                      get_owning_ref() { return(owning_ref); }
public     :                                             ACReference (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt );
public     :                                             ACReference (ACProperty *acpnodeptr, logical refopt=NO );
public     :                                             ACReference ( );
public     :                                             ACReference (ACReference &acrefref );
public     : virtual                                void *Add (int32 lindx0, logical global_add=NO );
public     : virtual                                logical AddGenericRef (char *fldname );
public     : virtual                                logical AddReference (node *srcenode, int32 lindx0 );
public     :                                        char CheckDel (int32 lindx0, logical chknode=YES );
public     :                                        char CheckDelSet (logical chknode=YES );
public     : virtual                                logical Close ( );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual                                logical DelGenericRef (char *fldname );
public     : virtual                                logical Delete (int32 indx0, logical chknode=YES, logical del_dep=YES, logical del_inst=NO );
public     : virtual                                int16 GetMainBase ( );
public     :                                        void Open (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, int32 extoff, PIACC accopt );
public     : virtual                                logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual                                     ~ACReference ( );
};

#pragma pack()
#endif
