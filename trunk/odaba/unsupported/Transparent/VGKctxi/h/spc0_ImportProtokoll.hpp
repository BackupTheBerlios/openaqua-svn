/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_ImportProtokoll

\brief    


\date     $Date: 2006/07/06 15:31:00,48 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_ImportProtokoll_HPP
#define   pc0_ImportProtokoll_HPP

class     pc0_ImportProtokoll;

class     TP_ImportGlobals;
#include  <cImportStatus.h>
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0Base_VS.hpp>
class  pc0_ImportProtokoll :public PropertyHandle
{

public     :
public     :                                        logical CheckStatus (ImportStatus import_status );
public     :                                        char *GetImportFolder (NString &nstring );
public     :                                        logical ImportOpenXMLActions ( );
public     :                                        logical ImportXMLActions (int32 id );
public     :                                        logical ImportXMLActions (TP_ImportGlobals *imp_globals );
public     :                                        logical ImportXMLActions (pc0Base_VS &VS_pc, DatabaseHandle &xml_dbhandle, char *xml_extnames, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportXMLActions ( );
public     :                                        logical InitializeImportXMLActions (char *xml_string );
public     :                                        logical SetStatus (ImportStatus import_status, logical reset_opt );
public     :                                        logical WriteMessages (NString &nstring, logical clear_opt=YES );
public     :                                        logical WriteMessages (char *string, logical clear_opt=YES );
public     :                                        logical WriteXMLActionsFile (char *xml_string );
public     :                                             pc0_ImportProtokoll (PropertyHandle *prophdl );
public     :                                             pc0_ImportProtokoll (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
