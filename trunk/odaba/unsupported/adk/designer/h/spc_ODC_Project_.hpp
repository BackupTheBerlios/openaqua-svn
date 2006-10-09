/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ODC_Project_



\date     $Date: 2006/05/19 19:06:17,81 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_Project__HPP
#define   pc_ODC_Project__HPP

class     pc_ODC_Project_;

#include  <sGSRT.h>
class     ODE_Project;
class     pc_ClassInputHelp;
#include  <sDatabaseHandle.hpp>
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc_ODC_Project_ :public PropertyHandle
{

public     :
public     :                                        logical InitExternalResources (NString &nstring, char *impl_env );
public     :                                        logical InitResourceDB (char *prjnames, PropertyHandle *source_ph );
public     :                                        logical IsImplemented (logical read_opt );
public     :                                        logical NewProject (char *prj_names );
public     :                                             pc_ODC_Project_ (PropertyHandle *prophdl );
public     :                                             pc_ODC_Project_ (DatabaseHandle &db_handle, PIACC accopt );
};

#endif
