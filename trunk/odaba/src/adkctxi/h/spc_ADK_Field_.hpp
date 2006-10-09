/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc_ADK_Field_

\brief    


\date     $Date: 2006/03/12 19:35:31,01 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Field__HPP
#define   pc_ADK_Field__HPP

class     pc_ADK_Field_;

#include  <sPropertyHandle.hpp>
#include  <spc_ADK_StyleElement_.hpp>
class  pc_ADK_Field_ :public pc_ADK_StyleElement_
{

public     :
public     :                                     logical IsInitialized ( );
public     :                                     logical NewField (char *propnames, int32 posx, int32 posy );
public     :                                     logical SetupColumn ( );
public     :                                     logical SetupDataSource (char *propnames, char *type_string, logical coll_opt );
public     :                                     logical SetupField ( );
public     :                                     logical SetupFromFieldControl (PropertyHandle *prophdl );
public     :                                     logical SetupRegion ( );
public     :                                     logical SetupTitle (char *propnames );
public     :                                                             pc_ADK_Field_ (PropertyHandle *prophdl );
};

#endif
