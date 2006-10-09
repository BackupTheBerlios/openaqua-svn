/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_Actor

\brief    


\date     $Date: 2006/07/17 18:23:09,17 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_Actor_HPP
#define   pc_Actor_HPP

class     pc_Actor;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spcBase_SharedData.hpp>
class  pc_Actor :public pcBase_SharedData
{

public     :
public     :                                        char *CalculateBetreffAusgangsNotiz (NString &nstring );
public     :                                        char *GetIdentString (NString &nstring, logical key_opt, logical clear_opt=YES );
public     :                                             pc_Actor (PropertyHandle *prophdl );
public     :                                             pc_Actor (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
