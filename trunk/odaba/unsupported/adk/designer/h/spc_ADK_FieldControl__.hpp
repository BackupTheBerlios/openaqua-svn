/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADK_FieldControl__

\brief    


\date     $Date: 2006/03/12 19:36:43,03 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_FieldControl___HPP
#define   pc_ADK_FieldControl___HPP

class     pc_ADK_FieldControl__;

#include  <sPropertyHandle.hpp>
#include  <spc_ADK_FieldControl__.hpp>
class  pc_ADK_FieldControl__ :public PropertyHandle
{
protected  :         PropertyHandle                               sys_ident;                                                 //

public     :
                     PropertyHandle                              &get_sys_ident() { return(sys_ident); }
public     :                                     logical Check (int32 start_id, logical recursive );
public     :                                     logical CheckElements (PropertyHandle *prophdl, int32 start_id, logical recursive );
public     :                                     logical CheckExtent (char *data_source );
public     :                                     logical CheckPropertyPath (char *data_source );
public     :                                     logical InitResourceDB (pc_ADK_FieldControl__ &source_control );
public     :                                     logical IsInHierarchy (int32 start_id );
public     :                                                             pc_ADK_FieldControl__ (PropertyHandle *prophdl );
};

#endif
