/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_StyleElement



\date     $Date: 2006/05/23 13:05:27,93 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_StyleElement_HPP
#define   pc_ADK_StyleElement_HPP

class     pc_ADK_StyleElement;

#include  <sPropertyHandle.hpp>
class  pc_ADK_StyleElement :public PropertyHandle
{

public     :
public     :                                        logical SetupFromParent ( );
public     :                                             pc_ADK_StyleElement (PropertyHandle *prophdl );
public     :                                             ~pc_ADK_StyleElement ( );
};

#endif
