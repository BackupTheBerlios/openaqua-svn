/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ODC_Project



\date     $Date: 2006/05/23 21:12:03,03 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ODC_Project_HPP
#define   pc1_ODC_Project_HPP

class     pc1_ODC_Project;

#include  <sGSRT.h>
class     ODE_Project;
class     pc_ClassInputHelp;
#include  <cProjectImplementationType.h>
#include  <sDatabaseHandle.hpp>
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc1_ODC_Project :public PropertyHandle
{

public     :
public     :                                        char *GetInterfaceClassName (char *init_string );
public     :                                        char *GetProjectPath (NString &nstring, char *folder_type, char *init_string );
public     :                                        logical InitExternalResources (CTX_GUIBase *ctxptr, ProjectImplementationType pimpl_type, logical ini_opt, NString &nstring );
public     :                                        logical InitResourceDB (char *prjnames, PropertyHandle *source_ph );
public     :                                        logical IsImplemented (logical read_opt );
public     :                                        logical NewProject (CTX_GUIBase *ctxptr, char *prj_names, logical ini_opt, NString &nstring );
public     :                                             pc1_ODC_Project (PropertyHandle *prophdl );
public     :                                             pc1_ODC_Project (DatabaseHandle &db_handle, PIACC accopt );
};

#endif
