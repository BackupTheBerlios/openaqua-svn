/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OPAccessPath

\brief    


\date     $Date: 2006/04/20 19:11:53,68 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPAccessPath_HPP
#define   OPAccessPath_HPP

class     OPAccessPath;

class     BNFData;
class     OPAccessPath;
class     OPBase;
class     OPParmList;
class     OperEnvironment;
class     ParmList;
class     PropertyHandle;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPVariable.hpp>
class  OPAccessPath :public OPVariable
{
protected  :         OPAccessPath                                *path_ext;                                                  // 
protected  :         int32                                        ext_index;                                                 // 
protected  :         logical                                      is_coll_operand;                                           // 
protected  :         logical                                      intern_expr;                                               // 
protected  :         PropertyHandle                              *local_co;                                                  // 
protected  :         PIStack                                      source_stack;                                              

public     :
                     OPAccessPath                                *get_path_ext() { return(path_ext); }
                     logical                                      get_is_coll_operand() { return(is_coll_operand); }
                     logical                                      get_intern_expr() { return(intern_expr); }
                     PropertyHandle                              *get_local_co() { return(local_co); }
public     : virtual                             logical Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     :                                     ExecReturnCodes Execute ( );
public     : virtual                             logical Get ( );
public     :                                     node *GetAccessNode ( );
public     :                                     node *GetLastNode ( );
public     :                                     ExecReturnCodes InitSource ( );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                     DBStructDef *LocalScope ( );
public     : virtual                             logical Next ( );
public     :                                                             OPAccessPath (DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *pext_bnf, int32 indx0, logical lscope );
public     :                                     logical Position (int32 &count_ref );
public     :                                     logical Position (logical backward );
public     : virtual                             logical Previous ( );
public     :                                     void ResetValue ( );
public     :                                     OPAccessPath *Setup (DBStructDef *classref, OPBase *parent_node );
public     :                                     logical SetupOQLElements ( );
public     :                                     logical SetupPathElement ( );
public     :                                     logical SetupSource ( );
public     :                                     void SetupSourceHandle ( );
public     :                                     logical SetupSourceOperation ( );
public     : virtual                             logical ToTop (logical recursive );
public     :                                                             ~OPAccessPath ( );
};

#endif
