/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc_ADK_Button_

\brief    Button functions


\date     $Date: 2006/03/12 19:35:28,92 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Button__HPP
#define   pc_ADK_Button__HPP

class     pc_ADK_Button_;

class     PropertyHandle;
#include  <spc_ADK_StyleElement_.hpp>
class  pc_ADK_Button_ :public pc_ADK_StyleElement_
{

public     :
public     :                                     logical SetupButton ( );
public     :                                                             pc_ADK_Button_ (PropertyHandle *prophdl );
public     :                                                             ~pc_ADK_Button_ ( );
};

#endif
