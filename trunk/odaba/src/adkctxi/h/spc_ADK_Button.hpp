/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_Button

\brief    Button functions


\date     $Date: 2006/05/23 13:05:06,84 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Button_HPP
#define   pc_ADK_Button_HPP

class     pc_ADK_Button;

class     PropertyHandle;
#include  <spc_ADK_StyleElement.hpp>
class  pc_ADK_Button :public pc_ADK_StyleElement
{

public     :
public     :                                        logical SetupButton ( );
public     :                                             pc_ADK_Button (PropertyHandle *prophdl );
public     :                                             ~pc_ADK_Button ( );
};

#endif
