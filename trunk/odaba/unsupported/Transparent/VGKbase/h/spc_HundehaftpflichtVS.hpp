/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_HundehaftpflichtVS

\brief    


\date     $Date: 2006/07/21 16:36:05,79 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_HundehaftpflichtVS_HPP
#define   pc_HundehaftpflichtVS_HPP

class     pc_HundehaftpflichtVS;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc_Action.hpp>
class  pc_HundehaftpflichtVS :public pc_Action
{

public     :
public     :                                        logical SetupAnzahlHunde ( );
public     :                                             pc_HundehaftpflichtVS (PropertyHandle *prophdl );
public     :                                             pc_HundehaftpflichtVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
