/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADK_Resource



\date     $Date: 2006/05/23 13:07:06,00 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ADK_Resource_HPP
#define   pc1_ADK_Resource_HPP

class     pc1_ADK_Resource;

class     pc1_ADK_Resource;
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc1_ADK_Resource :public PropertyHandle
{
protected  :         PropertyHandle                               sys_resource;                                              

public     :
                     PropertyHandle                              &get_sys_resource() { return(sys_resource); }
public     :                                        logical InitResourceDB (pc1_ADK_Resource &source_resource );
public     :                                             pc1_ADK_Resource (DBObjectHandle &obhandle, char *clsnames, PIACC accopt );
};

#endif
