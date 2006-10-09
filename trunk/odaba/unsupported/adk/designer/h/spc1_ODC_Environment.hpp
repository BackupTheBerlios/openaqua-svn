/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_Environment



\date     $Date: 2006/05/30 19:25:02,68 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ODC_Environment_HPP
#define   pc1_ODC_Environment_HPP

class     pc1_ODC_Environment;

#include  <cProjectImplementationType.h>
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc1_ODC_Environment :public PropertyHandle
{

public     :
public     :                                        logical InitExternalResources (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring );
public     :                                        logical ProvideEnvironment (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring );
public     :                                             pc1_ODC_Environment (PropertyHandle *prophdl );
};

#endif
