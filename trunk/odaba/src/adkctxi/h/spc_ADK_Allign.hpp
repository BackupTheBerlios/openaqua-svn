/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_Allign



\date     $Date: 2006/05/23 13:05:02,62 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Allign_HPP
#define   pc_ADK_Allign_HPP

class     pc_ADK_Allign;

#include  <sPropertyHandle.hpp>
class  pc_ADK_Allign :public PropertyHandle
{

public     :
public     :                                        logical Setup (logical in_grid, logical in_dockwin );
public     :                                             pc_ADK_Allign (PropertyHandle *prophdl );
public     :                                             ~pc_ADK_Allign ( );
};

#endif
