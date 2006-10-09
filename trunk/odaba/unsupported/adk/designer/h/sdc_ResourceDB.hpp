/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    dc_ResourceDB



\date     $Date: 2006/05/23 14:22:51,84 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dc_ResourceDB_HPP
#define   dc_ResourceDB_HPP

class     dc_ResourceDB;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc1_ADK_Class.hpp>
#include  <spc1_ODC_Project.hpp>
class  dc_ResourceDB :public DatabaseHandle
{
protected  :         pc1_ADK_Class                                adk_classes;                                               
protected  :         pc1_ODC_Project                              odc_project;                                               

public     :
                     pc1_ADK_Class                               &get_adk_classes() { return(adk_classes); }
                     pc1_ODC_Project                             &get_odc_project() { return(odc_project); }
public     :                                        logical InitResourceDB (dc_ResourceDB *source_dc, char *extnames );
public     :                                        logical InitResourceDB (dc_ResourceDB *source_dc, char *extnames, char *inst_key );
public     :                                        logical InitResourceDB_DE (dc_ResourceDB *source_dc );
public     :                                        logical InitResourceDB_KE (dc_ResourceDB *source_dc );
public     :                                             dc_ResourceDB (DatabaseHandle &db_handle, PIACC accopt );
};

#endif
