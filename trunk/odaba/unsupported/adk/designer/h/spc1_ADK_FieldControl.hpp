/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADK_FieldControl



\date     $Date: 2006/05/23 13:01:39,39 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ADK_FieldControl_HPP
#define   pc1_ADK_FieldControl_HPP

class     pc1_ADK_FieldControl;

#include  <sPropertyHandle.hpp>
class  pc1_ADK_FieldControl :public PropertyHandle
{
protected  :         PropertyHandle                               sys_ident;                                                 

public     :
                     PropertyHandle                              &get_sys_ident() { return(sys_ident); }
public     :                                        logical Check (int32 start_id, logical recursive );
public     :                                        logical CheckElements (PropertyHandle *prophdl, int32 start_id, logical recursive );
public     :                                        logical CheckExtent (char *data_source );
public     :                                        logical CheckPropertyPath (char *data_source );
public     :                                        logical InitResourceDB (pc1_ADK_FieldControl &source_control );
public     :                                        logical IsInHierarchy (int32 start_id );
public     :                                             pc1_ADK_FieldControl (PropertyHandle *prophdl );
};

#endif
