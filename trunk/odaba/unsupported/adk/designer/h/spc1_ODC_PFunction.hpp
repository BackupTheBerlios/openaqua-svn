/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_PFunction



\date     $Date: 2006/05/23 13:14:11,04 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ODC_PFunction_HPP
#define   pc1_ODC_PFunction_HPP

class     pc1_ODC_PFunction;

class     pODE;
#include  <cMethodTypes.h>
#include  <sPropertyHandle.hpp>
class  pc1_ODC_PFunction :public PropertyHandle
{

public     :
public     :                                        MethodTypes GetImplementationType (CTX_GUIBase *ctxptr, logical setup_opt );
public     :                                        logical InitializePFunction (PropertyHandle *impcls_ph, pODE *ode_ctx );
public     :                                        logical InitializePFunction (PropertyHandle *func_ph );
public     :                                        logical IsConstructor ( );
public     :                                        logical IsNewInstance ( );
public     :                                        logical ProvideConstructor ( );
public     :                                        logical ProvideDestructor (logical virtual_opt );
public     :                                        char ProvideImplementation ( );
public     :                                             pc1_ODC_PFunction (PropertyHandle *prophdl );
};

#endif
