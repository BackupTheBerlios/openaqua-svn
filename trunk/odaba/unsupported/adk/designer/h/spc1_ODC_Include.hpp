/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_Include



\date     $Date: 2006/05/30 15:32:20,90 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ODC_Include_HPP
#define   pc1_ODC_Include_HPP

class     pc1_ODC_Include;

#include  <cProjectImplementationType.h>
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc1_ODC_Include :public PropertyHandle
{

public     :
public     :                                        logical InitExternalResource (ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring );
public     :                                        char *ProjectIncludeName (NString &nstring );
public     :                                        logical ProvideProjectInclude (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring );
public     :                                             pc1_ODC_Include (PropertyHandle *prophdl );
};

#endif
