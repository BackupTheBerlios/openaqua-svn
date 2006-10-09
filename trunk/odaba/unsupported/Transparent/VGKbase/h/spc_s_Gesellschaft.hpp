/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_s_Gesellschaft

\brief    


\date     $Date: 2006/07/18 12:16:30,90 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_s_Gesellschaft_HPP
#define   pc_s_Gesellschaft_HPP

class     pc_s_Gesellschaft;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spcBase_NotizHaving.hpp>
class  pc_s_Gesellschaft :public pcBase_NotizHaving
{

public     :
public     :                                        char *CalculateBetreffAusgangsNotiz (NString &nstring );
public     :                                        char *GetIdentString (NString &nstring, logical key_opt, logical clear_opt=YES );
public     :                                             pc_s_Gesellschaft (PropertyHandle *prophdl );
public     :                                             pc_s_Gesellschaft (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
