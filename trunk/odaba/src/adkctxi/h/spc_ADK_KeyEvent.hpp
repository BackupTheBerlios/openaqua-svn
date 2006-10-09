/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_KeyEvent



\date     $Date: 2006/05/23 13:05:23,07 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_KeyEvent_HPP
#define   pc_ADK_KeyEvent_HPP

class     pc_ADK_KeyEvent;

#include  <sPropertyHandle.hpp>
class  pc_ADK_KeyEvent :public PropertyHandle
{

public     :
public     :                                        logical SetKeyString ( );
public     :                                             pc_ADK_KeyEvent (PropertyHandle *ph );
};

#endif
