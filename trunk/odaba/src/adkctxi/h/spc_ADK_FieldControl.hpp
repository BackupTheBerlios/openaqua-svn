/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_FieldControl



\date     $Date: 2006/05/23 13:05:19,53 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_FieldControl_HPP
#define   pc_ADK_FieldControl_HPP

class     pc_ADK_FieldControl;

#include  <sPropertyHandle.hpp>
class  pc_ADK_FieldControl :public PropertyHandle
{

public     :
public     :                                        logical AddColumn (char *propnames, int32 indx0 );
public     :                                        logical AddField (char *propnames, int32 posx, int32 posy );
public     :                                        logical AddRegion (char *propnames, int32 indx0 );
public     :                                        logical AddTabControl (int32 posx, int32 posy );
public     :                                             pc_ADK_FieldControl (PropertyHandle *prophdl );
};

#endif
