/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF) - Context that communicates with the output area
\class    pc_ODC_FunctImp

\brief    


\date     $Date: 2006/04/06 15:57:33,17 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_FunctImp_HPP
#define   pc_ODC_FunctImp_HPP

class     pc_ODC_FunctImp;

#include  <cMethodTypes.h>
#include  <sPropertyHandle.hpp>
class  pc_ODC_FunctImp :public PropertyHandle
{

public     :
public     :                                     logical ExistDescription (char *names );
public     :                                     MethodTypes GetImplementationType (CTX_GUIBase *ctxptr, logical setup_opt );
public     :                                     logical InitializeImplementations (PropertyHandle *source_ph );
public     :                                     logical IsConstructor ( );
public     :                                     logical SetupCodeBlocks (CTX_GUIBase *ctxptr );
public     :                                                             pc_ODC_FunctImp (PropertyHandle *prophdl );
};

#endif
