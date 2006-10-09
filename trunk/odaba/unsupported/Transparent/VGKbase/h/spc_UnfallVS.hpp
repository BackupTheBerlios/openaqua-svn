/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_UnfallVS

\brief    


\date     $Date: 2006/07/21 11:52:05,10 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_UnfallVS_HPP
#define   pc_UnfallVS_HPP

class     pc_UnfallVS;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc_Action.hpp>
class  pc_UnfallVS :public pc_Action
{

public     :
public     :                                        logical CalculateVersicherungssumme ( );
public     :                                             pc_UnfallVS (PropertyHandle *prophdl );
public     :                                             pc_UnfallVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
