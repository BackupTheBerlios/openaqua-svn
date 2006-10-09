/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0Base_VS

\brief    


\date     $Date: 2006/07/06 11:06:51,65 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0Base_VS_HPP
#define   pc0Base_VS_HPP

class     pc0Base_VS;

class     TP_ImportGlobals;
#include  <cImportStatus.h>
#include  <sDatabaseHandle.hpp>
#include  <sKey.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_Action.hpp>
class  pc0Base_VS :public pc_Action
{

public     :
public     :                                        logical CheckImportStatus (ImportStatus import_status );
public     :                                        logical CheckValidExistence (Key key, TP_ImportGlobals *imp_globals );
public     :                                        logical CreateVS (char kenner, int32 id, TP_ImportGlobals *imp_globals );
public     :                                        logical Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportArbeitgeber (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportBestand (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical ImportBestandVV (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportDaten (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportFuehrerscheinVN (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportKinderVN (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportOD (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals, logical vn_opt );
public     : virtual                                logical ImportResult (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     : virtual                                logical ImportSebststaendig (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals, logical vn_opt );
public     :                                        logical ImportVS (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals );
public     :                                        logical SaveVS (TP_ImportGlobals *imp_globals );
public     :                                             pc0Base_VS (PropertyHandle *prophdl );
public     :                                             pc0Base_VS (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
