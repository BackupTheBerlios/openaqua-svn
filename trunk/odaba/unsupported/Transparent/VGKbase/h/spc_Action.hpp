/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_Action

\brief    


\date     $Date: 2006/07/21 12:36:25,68 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_Action_HPP
#define   pc_Action_HPP

class     pc_Action;

class     PropertyHandle;
#include  <cImportStatus.h>
#include  <sDatabaseHandle.hpp>
#include  <spcBase_SharedData.hpp>
class  pc_Action :public pcBase_SharedData
{

public     :
public     :                                        logical CalculateAblauf ( );
public     :                                        char *CalculateBetreffAusgangsNotiz (NString &nstring );
public     :                                        char *CalculateBetreffAusgangsNotiz (NString &nstring, char kenner, int32 id, logical clear_opt=YES );
public     :                                        char *CalculateBetreffPoliceNotiz (NString &nstring );
public     :                                        char *CalculateBetreffPoliceNotiz (NString &nstring, char kenner, int32 id, logical clear_opt=YES );
public     :                                        char *CalculateBetreffUebermittlungsNotiz (NString &nstring );
public     :                                        char *CalculateBetreffUebermittlungsNotiz (NString &nstring, char kenner, int32 id, logical clear_opt=YES );
public     :                                        int32 CheckForPolice ( );
public     :                                        int32 CheckForPolicierung ( );
public     :                                        char *GetIdentString (NString &nstring, logical key_opt, logical clear_opt=YES );
public     :                                        char *GetIdentString (NString &nstring, char kenner, int32 id, logical clear_opt=YES );
public     :                                        logical SetImportStatus (ImportStatus import_status, logical reset_opt );
public     :                                        int32 SetPoliciert ( );
public     :                                        int32 SetStatus (int32 status );
public     :                                        int32 SetZurPolicierung ( );
public     :                                             pc_Action (PropertyHandle *prophdl );
public     :                                             pc_Action (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
