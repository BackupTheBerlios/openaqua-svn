/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassFunctionEdit

\brief    


\date     $Date: 2006/06/01 16:43:01,14 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassFunctionEdit_HPP
#define   cClassFunctionEdit_HPP

class     cClassFunctionEdit;

#include  <sODE_SearchReplace.hpp>
#include  <sPropertyHandle.hpp>
class  cClassFunctionEdit :public CTX_Control
{
protected  :         ODE_SearchReplace                            search_replace;                                            // 

public     :
                     ODE_SearchReplace                           &get_search_replace() { return(search_replace); }
public     :                                        logical CheckSave ( );
public     :                                        logical Compile ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        logical DistributeSearchReplace ( );
public     :                                        logical DistributeSearchReplace (ODE_SearchReplace *ode_search_replace );
public     : virtual                                int8 DoAfterOpen ( );
public     : virtual                                int8 DoBeforeClose ( );
public     :                                        logical ErrorLookup ( );
public     :                                        logical ExecSearchReplace ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical FindEntry ( );
public     :                                        logical GenerateInclude ( );
public     :                                        CTX_Control *GetImplementationContext ( );
public     :                                        CTX_Control *GetPFunctionContext ( );
public     :                                        logical Goto ( );
public     :                                        logical GotoLine ( );
public     :                                        logical GotoLine (char *line_string );
public     :                                        logical InputHelp ( );
public     :                                        logical RenameEntry ( );
public     :                                        logical SearchReplace (logical do_replace );
public     :                                        logical SelectPFunction ( );
public     :                                        logical SetPFunctionNotInit ( );
public     :                                        logical SetupOutput (char *string, logical clear_opt=YES );
public     :                                        int32 StartClassAction (logical write_opt, logical reserve_opt );
public     :                                        logical StopClassAction (logical reserve_opt, int32 cur_pfunct_indx0 );
public     :                                        logical Update ( );
public     :                                             cClassFunctionEdit ( );
public     :                                             ~cClassFunctionEdit ( );
};

#endif
