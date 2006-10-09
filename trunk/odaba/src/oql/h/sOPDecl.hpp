/********************************* Class Declaration ***************************/
/**
\package  OQL
\class    OPDecl



\date     $Date: 2006/05/20 16:34:06,92 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPDecl_HPP
#define   OPDecl_HPP

class     OPDecl;

class     BNFData;
class     OPParmList;
class     OperEnvironment;
class     ParmList;
class     node;
#include  <sOPBase.hpp>
#include  <sPropertyHandle.hpp>
class  OPDecl :public OPBase
{
protected  :         char                                         impl_name[40];                                             
protected  :         char                                         type_name[40];                                             

public     :
                     char                                        *get_impl_name() { return(impl_name); }
                     char                                        *get_type_name() { return(type_name); }
public     :                                        logical CallDecl (OperEnvironment *operenv, PropertyHandle *co, ParmList *parm_list, int8 set_operation=NO );
public     :                                        logical CallDecl (OperEnvironment *operenv, PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     :                                        logical CallIntern (PropertyHandle *co, int8 set_operation=NO );
public     :                                        logical CallIntern2 (PropertyHandle *co, int8 set_operation=NO );
public     :                                        logical Check (PropertyHandle *retval, PropertyHandle *co, ParmList *parm_list, logical convopt );
public     :                                        ParmList *CreatPrototypeParmList ( );
public     :                                        logical CreateDecl (PropertyHandle *impl_ph );
public     :                                        OPBase *CreateMember (BNFData *btype, BNFData *bdecl );
public     :                                        logical CreateVariable (BNFData *bdata, logical is_global );
public     :                                        logical DeInitParameters ( );
public     :                                        logical InitParameters (OPParmList *call_parms );
public     :                                        logical InitParameters (ParmList *parm_list );
public     : virtual                                logical InitResult (PropertyHandle *co );
public     : virtual                                logical InitResult ( );
public     :                                        logical IsAccessPath ( );
public     :                                        logical IsExpression ( );
public     :                                        logical IsFunction ( );
public     : virtual                                logical IsVirtual ( );
public     :                                        logical ListCallStack (int32 count );
public     :                                             OPDecl (OPBase *parent_node );
public     : virtual                                logical Position (int32 count );
public     :                                        logical PrintCallStack (int32 level );
public     :                                             ~OPDecl ( );
};

#endif
