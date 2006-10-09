/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF) - Context that communicates with the output area
\class    pc_ODC_PFunction

\brief    


\date     $Date: 2006/04/06 15:45:28,03 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_PFunction_HPP
#define   pc_ODC_PFunction_HPP

class     pc_ODC_PFunction;

class     pODE;
#include  <cMethodTypes.h>
#include  <sPropertyHandle.hpp>
class  pc_ODC_PFunction :public PropertyHandle
{

public     :
public     :                                     MethodTypes GetImplementationType (CTX_GUIBase *ctxptr, logical setup_opt );
public     :                                     logical InitializePFunction (PropertyHandle *impcls_ph, pODE *ode_ctx );
public     :                                     logical InitializePFunction (PropertyHandle *func_ph );
public     :                                     logical IsConstructor ( );
public     :                                     logical IsNewInstance ( );
public     :                                     logical ProvideConstructor ( );
public     :                                     logical ProvideDestructor (logical virtual_opt );
public     :                                     char ProvideImplementation ( );
public     :                                                             pc_ODC_PFunction (PropertyHandle *prophdl );
};

#endif
