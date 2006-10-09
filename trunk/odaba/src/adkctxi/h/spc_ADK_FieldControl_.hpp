/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc_ADK_FieldControl_

\brief    


\date     $Date: 2006/03/12 19:35:30,14 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_FieldControl__HPP
#define   pc_ADK_FieldControl__HPP

class     pc_ADK_FieldControl_;

#include  <sPropertyHandle.hpp>
class  pc_ADK_FieldControl_ :public PropertyHandle
{

public     :
public     :                                     logical AddColumn (char *propnames, int32 indx0 );
public     :                                     logical AddField (char *propnames, int32 posx, int32 posy );
public     :                                     logical AddRegion (char *propnames, int32 indx0 );
public     :                                     logical AddTabControl (int32 posx, int32 posy );
public     :                                                             pc_ADK_FieldControl_ (PropertyHandle *prophdl );
};

#endif
