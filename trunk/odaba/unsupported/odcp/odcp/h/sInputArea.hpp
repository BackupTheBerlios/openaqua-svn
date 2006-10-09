/********************************* Class Declaration ***************************/
/**
\package  ODCP - 
\class    InputArea

\brief    


\date     $Date: 2006/08/28 08:00:20,45 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InputArea_HPP
#define   InputArea_HPP

class     InputArea;

class     CTX_Control;
#include  <sNString.hpp>
class  InputArea
{
protected  :         NString                                      input;                                                     // 
protected  :         CTX_Control                                 *input_ctx;                                                 // 

public     :
                     NString                                     &get_input() { return(input); }
                     CTX_Control                                 *get_input_ctx() { return(input_ctx); }
public     :                  ODCPImpExp            char *GetLine (char *string );
public     :                  ODCPImpExp                 InputArea ( );
public     :                  ODCPImpExp            void SetInputContext (CTX_Control *ctx_ptr );
public     :                  ODCPImpExp                 ~InputArea ( );
};

#endif
