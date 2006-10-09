/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_FunctImp



\date     $Date: 2006/05/23 13:33:57,07 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ODC_FunctImp_HPP
#define   pc1_ODC_FunctImp_HPP

class     pc1_ODC_FunctImp;

#include  <cMethodTypes.h>
#include  <sPropertyHandle.hpp>
class  pc1_ODC_FunctImp :public PropertyHandle
{

public     :
public     :                                        logical ExistDescription (char *names );
public     :                                        MethodTypes GetImplementationType (CTX_GUIBase *ctxptr, logical setup_opt );
public     :                                        logical InitializeImplementations (PropertyHandle *source_ph );
public     :                                        logical IsConstructor ( );
public     :                                        logical SetupCodeBlocks (CTX_GUIBase *ctxptr );
public     :                                             pc1_ODC_FunctImp (PropertyHandle *prophdl );
};

#endif
