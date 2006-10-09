/********************************* Class Declaration ***************************/
/**
\package  ODCP - 
\class    OutputArea

\brief    


\date     $Date: 2006/08/28 07:59:50,50 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OutputArea_HPP
#define   OutputArea_HPP

class     OutputArea;

class     CTX_Control;
class  OutputArea
{
protected  :         NBuffer                                      output;                                                    // 
protected  :         CTX_Control                                 *output_ctx;                                                // 
protected  :         CTX_Control                                 *target_ctx;                                                // 

public     :
                     NBuffer                                     &get_output() { return(output); }
                     CTX_Control                                 *get_output_ctx() { return(output_ctx); }
                     CTX_Control                                 *get_target_ctx() { return(target_ctx); }
public     :                  ODCPImpExp            logical DisplayOutput ( );
public     :                  ODCPImpExp            CTX_Control *GetTargetContext ( );
public     :                  ODCPImpExp            void MessageOutput (char *string, Error *pError );
public     :                  ODCPImpExp                 OutputArea ( );
public     :                  ODCPImpExp            logical ScrollToEnd ( );
public     :                  ODCPImpExp            void SetOutputContext (CTX_Control *ctx_ptr );
public     :                  ODCPImpExp            void SetTargetContext (CTX_Control *ctx_ptr );
public     :                  ODCPImpExp            logical SetupOutput (char *string, logical clear_opt=YES );
public     :                  ODCPImpExp                 ~OutputArea ( );
};

#endif
