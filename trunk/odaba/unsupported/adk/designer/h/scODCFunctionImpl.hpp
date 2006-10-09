/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cODCFunctionImpl

\brief    


\date     $Date: 2006/06/03 15:05:23,42 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cODCFunctionImpl_HPP
#define   cODCFunctionImpl_HPP

class     cODCFunctionImpl;

class     ODE_SearchReplace;
class     PropertyHandle;
#include  <scNotifyHighContext.hpp>
#include  <scSDBResource_Base.hpp>
class  cODCFunctionImpl :public cSDBResource_Base
{
protected  :         CTX_Control                                 *ctx_init;                                                  // 
protected  :         CTX_Control                                 *ctx_start;                                                 // 
protected  :         CTX_Control                                 *ctx_code;                                                  // 
protected  :         CTX_Control                                 *ctx_error;                                                 // 
protected  :         CTX_Control                                 *ctx_term;                                                  // 

public     :
public     :                                        logical Changed ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterFillData ( );
public     : virtual                                int8 DoAfterOpen ( );
public     :                                        logical ExecSearchReplace ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GotoLine ( );
public     :                                        logical InputHelp ( );
public     :                                        logical InputHelp (logical enable_opt );
public     :                                        logical SearchReplace (ODE_SearchReplace *ode_search_replace, CTX_Control *context );
public     :                                        logical SwitchInitStart (int32 display_level );
public     :                                             cODCFunctionImpl ( );
public     : virtual                                     ~cODCFunctionImpl ( );
};

#endif
