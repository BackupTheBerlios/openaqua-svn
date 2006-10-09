/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF) - Context that communicates with the output area
\class    ODE_Output

\brief    


\date     $Date: 2006/04/10 18:27:04,23 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODE_Output_HPP
#define   ODE_Output_HPP

class     ODE_Output;

class  ODE_Output
{
protected  :         NBuffer                                      output;                                                    // 
protected  :         CTX_Control                                 *output_ctx;                                                // 
protected  :         CTX_Control                                 *target_ctx;                                                // Context that communicates with the output area

public     :
                     NBuffer                                     &get_output() { return(output); }
                     CTX_Control                                 *get_output_ctx() { return(output_ctx); }
                     CTX_Control                                 *get_target_ctx() { return(target_ctx); }
public     :                                     logical DisplayOutput ( );
public     :                                     CTX_Control *GetTargetContext ( );
public     :                                     void MessageOutput (char *string, Error *pError );
public     :                                                             ODE_Output ( );
public     :                                     logical ScrollToEnd ( );
public     :                                     void SetOutputContext (CTX_Control *ctx_ptr );
public     :                                     void SetTargetContext (CTX_Control *ctx_ptr );
public     :                                     logical SetupOutput (char *string, logical clear_opt=YES );
public     :                                                             ~ODE_Output ( );
};

#endif
