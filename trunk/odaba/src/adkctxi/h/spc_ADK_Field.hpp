/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_Field

\brief    


\date     $Date: 2006/05/23 13:05:15,71 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Field_HPP
#define   pc_ADK_Field_HPP

class     pc_ADK_Field;

#include  <sPropertyHandle.hpp>
#include  <spc_ADK_StyleElement.hpp>
class  pc_ADK_Field :public pc_ADK_StyleElement
{

public     :
public     :                                        logical IsInitialized ( );
public     :                                        logical NewField (char *propnames, int32 posx, int32 posy );
public     :                                        logical SetupColumn ( );
public     :                                        logical SetupDataSource (char *propnames, char *type_string, logical coll_opt );
public     :                                        logical SetupField ( );
public     :                                        logical SetupFromFieldControl (PropertyHandle *prophdl );
public     :                                        logical SetupRegion ( );
public     :                                        logical SetupTitle (char *propnames );
public     :                                             pc_ADK_Field (PropertyHandle *prophdl );
};

#endif
