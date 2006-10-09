/********************************* Class Declaration ***************************/
/**
\package  OQL
\class    OPVariable



\date     $Date: 2006/05/26 13:50:59,79 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPVariable_HPP
#define   OPVariable_HPP

class     OPVariable;

class     ACObject;
class     BNFData;
class     OPParmList;
class     node;
#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>
#include  <sOPVariable.hpp>
#include  <sPropertyHandle.hpp>
class  OPVariable :public OPBase
{
protected  :         BNFData                                     *parm_bnf;                                                  
protected  :         logical                                      default_parm;                                              
protected  :         int64                                        last_type_id;                                              // Expression variables
protected  :         int64                                        last_instid;                                               
protected  :         logical                                      xx_selection;                                              // Automatic selection
protected  :         logical                                      on_top;                                                    
protected  :         int8                                         is_set_operand;                                            // Set operand
protected  :         logical                                      local_scope;                                               
protected  :         PropertyHandle                               save_co;                                                   

public     :
                     BNFData                                     *get_parm_bnf() { return(parm_bnf); }
                     logical                                      get_xx_selection() { return(xx_selection); }
                     logical                                      get_on_top() { return(on_top); }
                     int8                                         get_is_set_operand() { return(is_set_operand); }
                     logical                                      get_local_scope() { return(local_scope); }
public     :                                        ExecReturnCodes Execute ( );
public     :                                        ExecReturnCodes ExecuteParameter (int32 indx0 );
public     :                                        ExecReturnCodes ExecuteParameters (int32 indx0 );
public     :                                        ExecReturnCodes ExecuteSource ( );
public     :                                        ExecReturnCodes ExecuteStatement (int32 indx0 );
public     :                                        ExecReturnCodes ExecuteStatements (int32 indx0 );
public     :                                        logical Get ( );
public     : virtual                                OPVariable *GetVariable ( );
public     : virtual                                logical IsSetOperand ( );
public     :                                        logical Next ( );
public     :                                             OPVariable (DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                        logical Previous ( );
public     :                                        void ResetValue ( );
public     :                                        void RestoreCO ( );
public     :                                        void SaveCO ( );
public     :                                        DBFieldDef *SetupFieldDef (BNFData *bdata );
public     :                                        logical SetupParameters ( );
public     :                                        OPBase *SetupParmHandle (BNFData *bparms );
public     :                                        logical ToTop (logical recursive );
public     : virtual                                     ~OPVariable ( );
};

#endif
