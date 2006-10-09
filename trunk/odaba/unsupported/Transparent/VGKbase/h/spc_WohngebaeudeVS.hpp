/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_WohngebaeudeVS

\brief    


\date     $Date: 2006/07/21 11:57:46,40 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_WohngebaeudeVS_HPP
#define   pc_WohngebaeudeVS_HPP

class     pc_WohngebaeudeVS;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc_Action.hpp>
class  pc_WohngebaeudeVS :public pc_Action
{

public     :
public     :                                        logical CalculateVersicherungssumme ( );
public     :                                             pc_WohngebaeudeVS (PropertyHandle *prophdl );
public     :                                             pc_WohngebaeudeVS (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
